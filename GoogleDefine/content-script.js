// Lắng nghe yêu cầu từ popup
chrome.runtime.onMessage.addListener((request, sender, sendResponse) => {
    if (request.action === "GET_DEFINITION") {
      // Tìm thẻ div chứa định nghĩa
      const definitionDiv = document.querySelector('div[jsname="x3Eknd"].VpH2eb.vmod');
      
      if (definitionDiv) {
        sendResponse({
          success: true,
          content: definitionDiv.innerHTML
        });
      } else {
        sendResponse({
          success: false,
          error: "Không tìm thấy định nghĩa."
        });
      }
    }
    return true; // Giữ kết nối mở để gửi phản hồi không đồng bộ
  });