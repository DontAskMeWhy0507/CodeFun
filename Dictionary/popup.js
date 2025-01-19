document.addEventListener("DOMContentLoaded", () => {
    chrome.storage.local.get("selectedText", (data) => {
      document.getElementById("selected-text").innerText = data.selectedText || "Không có văn bản nào.";
    });
  });
  