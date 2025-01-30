document.getElementById("fetchDefinition").addEventListener("click", () => {
    chrome.tabs.query({ active: true, currentWindow: true }, (tabs) => {
      chrome.scripting.executeScript({
        target: { tabId: tabs[0].id },
        func: () => {
          // Gửi yêu cầu đến content script
          return new Promise((resolve) => {
            chrome.runtime.sendMessage({ action: "GET_DEFINITION" }, (response) => {
              resolve(response);
            });
          });
        }
      }, (results) => {
        const response = results[0].result;
        const definitionDiv = document.getElementById("definition");
        
        if (response.success) {
          definitionDiv.innerHTML = response.content;
        } else {
          definitionDiv.innerHTML = `<p class="error">${response.error}</p>`;
        }
      });
    });
  });