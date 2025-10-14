import fitz  # PyMuPDF
import sys  # For progress logging

# --- Helper Function ---

def get_page_text_lines(page):
    """
    Extracts all text line bounding boxes as a sorted list of (y0, y1) tuples.
    These coordinates are in the page's original coordinate system.
    """
    text_lines = []
    # Get all text in a structured dictionary
    page_dict = page.get_text("dict", flags=fitz.TEXTFLAGS_DICT)
    for block in page_dict["blocks"]:
        if block["type"] == 0:  # This is a text block
            for line in block["lines"]:
                bbox = line["bbox"]
                # Store the vertical coordinates of the line
                text_lines.append((bbox[1], bbox[3])) # (y0, y1)
                
    # Sort lines by their top coordinate (y0) to ensure they are in order
    text_lines.sort()
    return text_lines

# --- Main Script ---

# Open the original PDF
try:
    doc = fitz.open(r"Python/1234.pdf")
except Exception as e:
    print(f"Error opening file: {e}")
    sys.exit(1)

# A4 size in points (portrait)
A4_WIDTH, A4_HEIGHT = 595, 842  

new_doc = fitz.open()

print(f"Processing {len(doc)} pages...")

for page_num in range(len(doc)):
    page = doc[page_num]
    rect = page.rect
    
    print(f"  Processing Page {page_num + 1}/{len(doc)}...")

    # Get a sorted list of all text line coordinates on this page
    safe_text_lines = get_page_text_lines(page)
    if not safe_text_lines:
        print("    Warning: No text found on this page. Slicing mathematically.")
    
    # Scale factor to fit width into A4
    zoom = A4_WIDTH / rect.width
    scaled_page_height_per_a4 = A4_HEIGHT / zoom
    
    current_clip_top = 0.0
    slice_count = 0

    # Loop slicing down the page until we've covered the whole height
    while current_clip_top < rect.height:
        slice_count += 1
        
        # Calculate the ideal bottom of the clip based on A4 height
        ideal_clip_bottom = current_clip_top + scaled_page_height_per_a4
        
        actual_clip_bottom = ideal_clip_bottom
        
        # Check if we've gone past the page height
        if ideal_clip_bottom >= rect.height - 1.0: # Use a small tolerance
            actual_clip_bottom = rect.height
        elif safe_text_lines:
            # We are not at the end. We must find a safe split point.
            intersecting_line_top = None
            for y0, y1 in safe_text_lines:
                # Does our ideal split fall INSIDE a line of text?
                # (i.e., is it between the top and bottom of a single line?)
                if y0 < ideal_clip_bottom < y1:
                    intersecting_line_top = y0  # Store the top of the line we hit
                    break
            
            if intersecting_line_top is not None:
                # YES, we hit a line. We must adjust the split.
                # We will split right BEFORE this line starts.
                
                # This check prevents an infinite loop:
                # If the top of the line we hit is ABOVE our current slice top,
                # it means the *entire A4 slice* is filled by this one giant line.
                # We have no choice but to cut it (by reverting to the ideal_clip_bottom).
                if intersecting_line_top > current_clip_top:
                    # This is a good split. Set the bottom to the top of the line we hit.
                    actual_clip_bottom = intersecting_line_top
                    print(f"    - Page {page_num+1}, Slice {slice_count}: Safe split found. Adjusted cut from {ideal_clip_bottom:.2f} to {actual_clip_bottom:.2f}")
                else:
                    # This is a "giant line" case. We must force-cut.
                    print(f"    - Page {page_num+1}, Slice {slice_count}: Unavoidable cut in giant line.")
                    actual_clip_bottom = ideal_clip_bottom # Revert to unsafe cut
        
        # Define the clip rectangle for the ORIGINAL page
        clip = fitz.Rect(0, current_clip_top, rect.width, actual_clip_bottom)
        
        # Ensure we don't create tiny or zero-height pages (can happen from adjustments)
        if clip.height < 1.0:
             if actual_clip_bottom >= rect.height:
                 break # We are truly at the end
             else:
                 # This should ideally not happen, but if it does, force the ideal cut to prevent loop
                 actual_clip_bottom = ideal_clip_bottom
                 clip = fitz.Rect(0, current_clip_top, rect.width, actual_clip_bottom)
                 if clip.height < 1.0:
                     break # Truly stuck or finished.


        # Create a new blank A4 page
        new_page = new_doc.new_page(width=A4_WIDTH, height=A4_HEIGHT)

        # Insert the clipped portion of the original page, scaled to fit A4 width
        # The show_pdf_page function handles the scaling automatically
        # when the destination rect (new_page.rect) and the clip rect are given.
        new_page.show_pdf_page(
            new_page.rect,  # Destination rect: the entire new A4 page
            doc,
            page_num,
            clip=clip        # Source rect: the calculated slice
        )
        
        # Set the top of the NEXT slice to be the bottom of THIS slice
        current_clip_top = actual_clip_bottom

# Save the output
output_filename = "split_long_to_A4_safe.pdf"
new_doc.save(output_filename)
new_doc.close()
doc.close()

print(f"\nDone. Output saved to: {output_filename}")