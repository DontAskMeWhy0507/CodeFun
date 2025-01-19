document.addEventListener("mouseup", () => {
  let selectedText = window.getSelection().toString().trim();

  // Nếu có văn bản được bôi đen
  if (selectedText) {
    let range = window.getSelection().getRangeAt(0);
    let rect = range.getBoundingClientRect();

    // Kiểm tra xem icon đã tồn tại chưa, nếu có thì xóa trước
    let existingIcon = document.getElementById("highlight-icon");
    if (existingIcon) existingIcon.remove();

    // Tạo icon
    let icon = document.createElement("img");
    icon.src = chrome.runtime.getURL("icon.png");
    icon.id = "highlight-icon";
    icon.style.position = "absolute";
    icon.style.left = `${window.scrollX + rect.left}px`;
    icon.style.top = `${window.scrollY + rect.bottom + 5}px`;
    icon.style.width = "20px";
    icon.style.height = "20px";
    icon.style.cursor = "pointer";
    icon.style.zIndex = "9999";

    // Khi nhấn vào icon -> mở popup
    icon.addEventListener("click", () => {
      chrome.storage.local.set({ selectedText }, () => {
        chrome.runtime.sendMessage({ action: "open_popup" });
      });
    });

    document.body.appendChild(icon);
  }
});
