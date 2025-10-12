import requests
import pandas as pd
import time
import re
import json
import os

# === CẤU HÌNH API KEY ===
NOTION_API_KEY = os.getenv("NOTION_TOKEN")  # 🔑 Đặt API key tại đây
# For production, use environment variables. For testing, ensure this is your SECRET key.

HEADERS = {
    "Authorization": f"Bearer {NOTION_API_KEY}",
    "Notion-Version": "2022-06-28",
    "Content-Type": "application/json"
}

# === CHUẨN HÓA PAGE ID ===
def normalize_page_id(raw_id):
    raw_id = raw_id.strip().replace("-", "")
    if len(raw_id) == 32:
        return f"{raw_id[0:8]}-{raw_id[8:12]}-{raw_id[12:16]}-{raw_id[16:20]}-{raw_id[20:]}"
    if re.match(r"^[0-9a-f]{8}-([0-9a-f]{4}-){3}[0-9a-f]{12}$", raw_id, re.IGNORECASE):
        return raw_id
    print(f"⚠️ ID '{raw_id}' không giống ID 32 ký tự hoặc UUID chuẩn.")
    return raw_id

# === LẤY TẤT CẢ BLOCK VÀ CON BLOCK ===
def get_all_blocks(block_id):
    normalized_block_id = normalize_page_id(block_id)
    url = f"https://api.notion.com/v1/blocks/{normalized_block_id}/children?page_size=100"
    blocks = []
    has_more = True
    start_cursor = None
    retries = 3
    retry_delay = 5

    # print(f"DEBUG: Initial call to get_all_blocks for: {normalized_block_id}")

    while has_more:
        current_attempt = 0
        success = False
        data = {} # Ensure data is defined outside try
        while current_attempt < retries:
            try:
                params = {"start_cursor": start_cursor} if start_cursor else {}
                # print(f"DEBUG: Fetching blocks for {normalized_block_id}, cursor: {start_cursor}")
                response = requests.get(url, headers=HEADERS, params=params, timeout=15)
                response.raise_for_status()
                data = response.json()
                success = True
                break
            except requests.exceptions.HTTPError as e:
                current_attempt += 1
                print(f"⚠️ Lỗi HTTP khi lấy block (thử lại {current_attempt}/{retries}): {e.response.status_code} - {e.response.text[:200]}")
                if e.response.status_code == 401:
                    print("❌ Lỗi 401: Unauthorized. Kiểm tra API Key và quyền Integration.")
                    return []
                if e.response.status_code == 404:
                    print(f"❌ Lỗi 404: Block ID '{normalized_block_id}' không tìm thấy hoặc không có quyền.")
                    return []
                if current_attempt >= retries:
                    print(f"❌ Không thể lấy block cho {normalized_block_id} sau {retries} lần thử.")
                    return blocks # Return what we have so far
                time.sleep(retry_delay * current_attempt)
            except requests.exceptions.RequestException as e:
                current_attempt += 1
                print(f"⚠️ Lỗi kết nối khi lấy block (thử lại {current_attempt}/{retries}): {e}")
                if current_attempt >= retries:
                    print(f"❌ Không thể lấy block cho {normalized_block_id} sau {retries} lần thử.")
                    return blocks
                time.sleep(retry_delay * current_attempt)
        
        if not success:
            return blocks

        results = data.get("results", [])
        for block in results:
            # print(f"DEBUG: Fetched block: {block.get('id')}, type: {block.get('type')}")
            blocks.append(block)
            if block.get("has_children"):
                # print(f"DEBUG: Block {block['id']} has children, fetching recursively...")
                time.sleep(0.35) 
                # The current script flattens all child blocks.
                # Reconstructing nested structure for upload is complex and not handled here.
                # This means children of toggles, columns, etc., will be appended at the top level.
                child_blocks = get_all_blocks(block["id"])
                if child_blocks:
                    blocks.extend(child_blocks)
                # print(f"DEBUG: Finished fetching children for {block['id']}")

        has_more = data.get("has_more", False)
        start_cursor = data.get("next_cursor")
        if has_more:
            time.sleep(0.35)
    return blocks

# === CHUYỂN BLOCKS THÀNH DATAFRAME (REVISED) ===
def blocks_to_dataframe(blocks_input):
    data_for_df = []
    for block in blocks_input:
        block_type = block["type"]
        
        # Data to store for each block
        # We'll primarily pass the raw_block and then extract/process specific parts in the combination step
        df_row = {
            "id": block["id"],
            "type": block_type,
            "raw_block": block # Store the entire raw block
        }
        data_for_df.append(df_row)
        
    return pd.DataFrame(data_for_df)

# === PROCESS RICH TEXT ARRAY TO SPLIT INLINE EQUATIONS AND PRESERVE ANNOTATIONS ===
def process_rich_text_array(input_rich_text_array):
    if not input_rich_text_array:
        return []

    output_rich_text_array = []
    # Regex from original format_content_for_notion
    pattern = r"(\$\$([\s\S]*?)\$\$)|(\$([^\$\n]*?)\$)" 

    for rt_item in input_rich_text_array:
        if rt_item["type"] == "text":
            text_content = rt_item["text"]["content"]
            annotations = rt_item.get("annotations")
            href = rt_item["text"].get("link", {}).get("url") if rt_item["text"].get("link") else None # Correctly get href

            current_pos = 0
            item_had_equation = False
            for match in re.finditer(pattern, text_content):
                item_had_equation = True
                start_match, end_match = match.span()

                # 1. Text before equation
                if start_match > current_pos:
                    preceding_text_obj = {
                        "type": "text",
                        "text": {"content": text_content[current_pos:start_match]}
                    }
                    if annotations: preceding_text_obj["annotations"] = annotations
                    if href: preceding_text_obj["text"]["link"] = {"url": href}
                    output_rich_text_array.append(preceding_text_obj)

                # 2. Equation
                expression_content = ""
                if match.group(1):  # $$...$$
                    expression_content = match.group(2).strip()
                elif match.group(3):  # $...$
                    expression_content = match.group(4).strip()

                if expression_content:
                    output_rich_text_array.append({
                        "type": "equation",
                        "equation": {"expression": expression_content}
                        # Annotations generally don't apply to equation objects directly
                    })
                elif match.group(0): # Handle empty delimiters like "$ $" or "$$ $$" as text
                    empty_delimiter_obj = {
                        "type": "text",
                        "text": {"content": match.group(0)}
                    }
                    if annotations: empty_delimiter_obj["annotations"] = annotations
                    if href: empty_delimiter_obj["text"]["link"] = {"url": href}
                    output_rich_text_array.append(empty_delimiter_obj)
                
                current_pos = end_match
            
            # 3. Text after the last equation (or the whole text if no equations)
            if current_pos < len(text_content):
                remaining_text_obj = {
                    "type": "text",
                    "text": {"content": text_content[current_pos:]}
                }
                if annotations: remaining_text_obj["annotations"] = annotations
                if href: remaining_text_obj["text"]["link"] = {"url": href}
                output_rich_text_array.append(remaining_text_obj)
            elif not item_had_equation and text_content: # No equations, add original text item (or if it was empty)
                 output_rich_text_array.append(rt_item) # Add as is, preserving all original fields
            elif not item_had_equation and not text_content: # Original item was empty text
                 output_rich_text_array.append(rt_item)


        else: # For non-text items (e.g., existing equations, mentions), pass them through
            output_rich_text_array.append(rt_item)

    # Filter out text objects that became empty string content IF they were not originally empty
    # This can happen if splitting "$formula$" from "text$formula$text" results in ""
    # However, Notion allows empty rich text objects for empty paragraphs.
    # Let's keep them for now, Notion API handles empty rich_text array by creating an empty block.
    # final_array = [p for p in output_rich_text_array if not (p["type"] == "text" and not p["text"]["content"])]
    # If an original empty text object was passed, it should remain.
    return output_rich_text_array


# === KẾT HỢP DỮ LIỆU THEO CẤU TRÚC NOTION API (REVISED) ===
def combine_blocks_for_api(df):
    api_blocks = []
    for _, row in df.iterrows():
        raw_block = row["raw_block"]
        block_type = row["type"]
        block_specific_data = raw_block.get(block_type, {})

        # --- Common properties to extract and preserve ---
        # Color (for blocks that support it)
        color = block_specific_data.get("color")
        
        # Rich text content (main content for most blocks, or caption for media/code)
        source_rich_text = block_specific_data.get("rich_text", [])
        if block_type in ["image", "video", "file", "pdf", "embed", "bookmark", "code"]:
            source_rich_text = block_specific_data.get("caption", []) # Captions are rich_text

        processed_rich_text = process_rich_text_array(source_rich_text)
        
        # --- Construct payload based on block type ---
        payload_content = {}

        if block_type in ["paragraph", "heading_1", "heading_2", "heading_3",
                          "bulleted_list_item", "numbered_list_item",
                          "quote", "callout", "toggle", "to_do"]:
            payload_content = {"rich_text": processed_rich_text}
            if color and color != "default":
                payload_content["color"] = color
            
            if block_type == "to_do":
                payload_content["checked"] = block_specific_data.get("checked", False)
            if block_type == "callout":
                payload_content["icon"] = block_specific_data.get("icon") # Will be None if not present
            # Children for toggle are not handled for upload in this flattened structure

        elif block_type == "code":
            # Code block's main content is also rich_text, but usually a single plain text item.
            # We should NOT process its main content for equations, but take it as is.
            # Its caption (handled above by 'processed_rich_text') CAN have equations.
            code_body_rich_text = block_specific_data.get("rich_text", []) # The actual code
            payload_content = {
                "rich_text": code_body_rich_text, # Use raw rich_text for code body
                "caption": processed_rich_text,   # Use processed rich_text for caption
                "language": block_specific_data.get("language", "plain text")
            }
        
        elif block_type == "divider":
            payload_content = {} # Divider has no specific content beyond its type

        elif block_type == "equation": # Standalone equation block
            payload_content = {"expression": block_specific_data.get("expression", "")}

        elif block_type in ["image", "video", "file", "pdf", "embed", "bookmark"]:
            payload_content = {"caption": processed_rich_text}
            if block_specific_data.get("type") == "external":
                payload_content["external"] = {"url": block_specific_data.get("external", {}).get("url")}
            elif block_specific_data.get("type") == "file": # Notion hosted file
                 payload_content["file"] = {"url": block_specific_data.get("file", {}).get("url")}
                 # expiry_time is read-only
            
            # For embed, bookmark, link_preview, the URL is directly under block_specific_data
            if "url" in block_specific_data and block_type in ["embed", "bookmark", "link_preview"]: # link_preview is read-only from API
                 payload_content["url"] = block_specific_data["url"]

        # Add more block types as needed (table, column_list, synced_block are complex)
        else:
            # print(f"ℹ️ Skipping unhandled or simple block type for API construction: {block_type}")
            continue # Skip blocks we don't know how to reconstruct

        # Final block object for the API
        if payload_content is not None: # Ensure we have something to send
            api_block = {"type": block_type, block_type: payload_content}
            api_blocks.append(api_block)

    return api_blocks

# === UPLOAD THEO TỪNG BATCH ===
def upload_to_notion(page_id, blocks_to_upload):
    normalized_page_id = normalize_page_id(page_id)
    url = f"https://api.notion.com/v1/blocks/{normalized_page_id}/children"
    batch_size = 100
    num_batches = (len(blocks_to_upload) + batch_size - 1) // batch_size
    all_successful = True

    for i in range(num_batches):
        batch_start_index = i * batch_size
        batch_end_index = batch_start_index + batch_size
        batch = blocks_to_upload[batch_start_index:batch_end_index]
        payload = {"children": batch}

        # DEBUG: Save payload of a specific batch if needed
        # if i == 0: # Example: Save first batch
        #     with open(f"debug_batch_{i+1}_payload.json", "w", encoding="utf-8") as f:
        #         json.dump(payload, f, indent=2, ensure_ascii=False)
        #     print(f"DEBUG: Saved payload for batch {i+1} to debug_batch_{i+1}_payload.json")


        retries_upload = 3
        current_attempt_upload = 0
        print(f"📤 Đang chuẩn bị upload batch {i + 1}/{num_batches} ({len(batch)} blocks) tới page {normalized_page_id}...")

        while current_attempt_upload < retries_upload:
            try:
                response = requests.patch(url, headers=HEADERS, json=payload, timeout=30)
                response.raise_for_status()
                print(f"✅ Uploaded batch {i + 1}/{num_batches}")
                break
            except requests.exceptions.HTTPError as e:
                print(f"❌ Lỗi HTTP khi upload batch {i + 1}: {e.response.status_code}")
                error_detail = "No error text."
                try: error_detail = e.response.json()
                except json.JSONDecodeError: error_detail = e.response.text
                print(f"   Response: {error_detail}")
                
                if e.response.status_code == 400:
                    print("   Lỗi 400: Payload có thể bị sai định dạng. Kiểm tra JSON.")
                    problematic_batch_file = f"error_batch_{i+1}_payload.json"
                    try:
                        with open(problematic_batch_file, "w", encoding='utf-8') as f:
                            json.dump(payload, f, indent=2, ensure_ascii=False)
                        print(f"   Problematic batch payload saved to {problematic_batch_file}")
                    except Exception as ex_save:
                        print(f"   Không thể lưu problematic batch: {ex_save}")
                    all_successful = False # Mark as not fully successful
                    # For 400, retrying same payload is usually futile. Stop trying for this batch.
                    break 
                
                current_attempt_upload += 1
                if current_attempt_upload >= retries_upload:
                    print(f"❌ Không thể upload batch {i + 1} sau {retries_upload} lần thử.")
                    all_successful = False
                    break 
                print(f"   Thử lại sau {5 * current_attempt_upload} giây...")
                time.sleep(5 * current_attempt_upload)
            except requests.exceptions.RequestException as e:
                print(f"❌ Lỗi kết nối khi upload batch {i + 1}: {e}")
                current_attempt_upload += 1
                if current_attempt_upload >= retries_upload:
                    print(f"❌ Không thể upload batch {i + 1} sau {retries_upload} lần thử.")
                    all_successful = False
                    break
                print(f"   Thử lại sau {5 * current_attempt_upload} giây...")
                time.sleep(5 * current_attempt_upload)
        
        if not all_successful and e.response.status_code == 400: # If a 400 error occurred for the batch, stop all uploads
            print("   Dừng upload do lỗi 400 ở batch này.")
            break
        
        if num_batches > 1 and (i + 1 < num_batches):
             time.sleep(1)
    return all_successful

# === MAIN CHƯƠNG TRÌNH ===
if __name__ == "__main__":
    if  NOTION_API_KEY == "":
        print("🛑 VUI LÒNG CẤU HÌNH NOTION_API_KEY (Internal Integration Token) HỢP LỆ TRONG SCRIPT.")
        print("   API key thường bắt đầu bằng 'secret_...'")
        if NOTION_API_KEY.startswith("ntn_"):
             print("   Lưu ý: 'ntn_...' là Client ID (OAuth), không phải API Key (Internal Integration Token) cần cho script này.")
        # exit() # Allow running for testing even with placeholder key

    raw_source_page_id = input("🔗 Nhập Page ID nguồn (để SAO CHÉP TỪ): ")
    SOURCE_PAGE_ID = normalize_page_id(raw_source_page_id)
    
    raw_target_page_id = input("🔗 Nhập Page ID đích (để DÁN VÀO, phải là trang trống hoặc nơi bạn muốn append): ")
    TARGET_PAGE_ID = normalize_page_id(raw_target_page_id)

    if not SOURCE_PAGE_ID or not TARGET_PAGE_ID :
        print("❌ Page ID nguồn hoặc đích không hợp lệ sau khi chuẩn hóa.")
        exit()
    if SOURCE_PAGE_ID == TARGET_PAGE_ID:
        print("❌ Page ID nguồn và đích không được giống nhau.")
        exit()

    print(f"🎯 Page ID nguồn: {SOURCE_PAGE_ID}")
    print(f"🎯 Page ID đích: {TARGET_PAGE_ID}")

    print(f"\n📥 Đang lấy nội dung từ trang nguồn ({SOURCE_PAGE_ID})...")
    fetched_blocks = get_all_blocks(SOURCE_PAGE_ID)

    if not fetched_blocks:
        print("ℹ️ Không có nội dung nào được lấy từ trang nguồn hoặc có lỗi xảy ra.")
    else:
        print(f"✅ Lấy được {len(fetched_blocks)} block(s) từ trang nguồn (bao gồm cả con của các block có con).")
        
        # --- Optional: Save raw fetched blocks for debugging ---
        # with open("fetched_blocks_raw.json", "w", encoding="utf-8") as f:
        #     json.dump(fetched_blocks, f, indent=2, ensure_ascii=False)
        # print("📝 Raw fetched blocks saved to fetched_blocks_raw.json")

        print("\n🧱 Đang chuyển blocks sang DataFrame...")
        df_blocks = blocks_to_dataframe(fetched_blocks)
        
        print("\n🔄 Đang chuẩn bị cấu trúc blocks để upload (xử lý rich text, equations, annotations)...")
        api_ready_blocks = combine_blocks_for_api(df_blocks)

        # --- Optional: Save API-ready blocks for debugging ---
        # with open("api_ready_blocks_for_upload.json", "w", encoding="utf-8") as f:
        #     json.dump(api_ready_blocks, f, indent=2, ensure_ascii=False)
        # print("📝 API-ready blocks saved to api_ready_blocks_for_upload.json")

        if not api_ready_blocks:
            print("ℹ️ Không có block nào được tạo để upload sau khi xử lý.")
        else:
            print(f"\n📤 Sẵn sàng upload {len(api_ready_blocks)} block đã xử lý lên trang đích ({TARGET_PAGE_ID})...")
            confirm = input("Bạn có chắc muốn tiếp tục upload? (yes/no): ").strip().lower()
            if confirm == "yes":
                if upload_to_notion(TARGET_PAGE_ID, api_ready_blocks):
                    print("\n🎉 Hoàn thành upload!")
                else:
                    print("\n❌ Quá trình upload có thể chưa hoàn thành hoặc gặp lỗi.")
            else:
                print("ℹ️ Upload đã được hủy bởi người dùng.")