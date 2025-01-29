chrome.runtime.onInstalled.addListener(() => {
  console.log("Dictionary extension installed.");
});

chrome.runtime.onMessage.addListener((message, sender, sendResponse) => {
  if (message.type === "log") {
    console.log(message.data);
  } else if (message.type === "openPopup") {
    chrome.windows.create({
      url: `popup/popup.html?text=${message.text}`,
      type: "popup",
      width: 400,
      height: 400,
    });
  }
  sendResponse({ status: "received" });
});
