let icon = document.createElement('div');
icon.id = 'highlight-icon';
icon.textContent = '💬';
document.body.appendChild(icon);

// Lắng nghe sự kiện khi người dùng bôi đen văn bản
document.addEventListener('mouseup', function() {
  let selectedText = window.getSelection().toString();
  console.log('Selected text:', selectedText); // Log the selected text

  if (selectedText) {
    icon.style.display = 'block';
    icon.setAttribute('data-selected-text', selectedText);
  } else {
    icon.style.display = 'none';
  }
});

// Khi nhấn vào biểu tượng, gửi thông báo đến background để mở pop-up
icon.addEventListener('click', function() {
  let text = icon.getAttribute('data-selected-text');
  console.log('Sending message to background:', text); // Log the text being sent
  chrome.runtime.sendMessage({ action: 'openPopup', text: text }, function(response) {
    console.log('Response from background:', response); // Log the response from background
  });
});
