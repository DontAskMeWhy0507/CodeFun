chrome.runtime.onMessage.addListener((message, sender, sendResponse) => {
  if (message.action === 'openPopup') {
    let selectedText = message.text || "Không có văn bản được chọn.";
    console.log('Received message in background:', selectedText); // Log the received text

    // Định nghĩa kích thước pop-up
    let width = 400;
    let height = 200;

    // Sử dụng chrome.system.display để lấy thông tin về màn hình
    chrome.system.display.getInfo((displays) => {
      if (displays && displays.length > 0) {
        const primaryDisplay = displays[0]; // Lấy màn hình chính
        const left = (primaryDisplay.bounds.width - width) / 2;
        const top = (primaryDisplay.bounds.height - height) / 2;

        // Tạo cửa sổ pop-up bằng chrome.windows.create
        chrome.windows.create({
          url: 'popup.html',  // URL sẽ được mở trong pop-up
          type: 'popup',       // Chế độ cửa sổ pop-up
          width: width,        // Chiều rộng cửa sổ
          height: height,      // Chiều cao cửa sổ
          left: left,          // Căn giữa màn hình
          top: top             // Căn giữa màn hình
        }, function(window) {
          console.log('Popup window created:', window); // Log the created window
          // Add a delay before sending the message to the popup script
          setTimeout(() => {
            // Gửi nội dung văn bản được chọn đến tab của pop-up
            chrome.tabs.sendMessage(window.tabs[0].id, { action: 'updatePopup', text: encodeURIComponent(selectedText) }, function(response) {
              console.log('Response from popup:', response); // Log the response from popup
              sendResponse({ status: 'popup created' }); // Send response back to content script
            });
          }, 500); // Delay of 500ms
        });
      }
    });
    return true; // Keep the message channel open for sendResponse
  }
});
