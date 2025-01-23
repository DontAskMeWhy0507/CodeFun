document.addEventListener('DOMContentLoaded', function () {
  // Kiểm tra xem văn bản có được chọn hay không
  chrome.runtime.onMessage.addListener((message, sender, sendResponse) => {
    if (message.action === 'updatePopup') {
      console.log('Received message in popup:', message.text); // Log the received text
      // Cập nhật nội dung của popup
      document.getElementById('selected-text').textContent = decodeURIComponent(message.text) || "Chưa có văn bản được chọn.";
      sendResponse({ status: 'success' }); // Send response back to background
    }
  });
});
