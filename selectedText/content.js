let icon = document.createElement('div');
icon.id = 'highlight-icon';
icon.textContent = '⭐'; // Biểu tượng ngôi sao
icon.style.display = 'none'; // Ban đầu ẩn biểu tượng
icon.style.width = '20px'; // Chiều rộng của phần tử
icon.style.height = '20px'; // Chiều cao của phần tử
icon.style.position = 'absolute'; // Đặt vị trí tuyệt đối cho biểu tượng
icon.style.textAlign = 'center'; // Căn giữa theo chiều ngang
icon.style.lineHeight = '16px'; // Căn giữa theo chiều dọc
icon.style.fontSize = '20px'; // Điều chỉnh kích thước font chữ
icon.style.padding = '0'; // Loại bỏ padding
icon.style.margin = '0'; // Loại bỏ margin

document.body.appendChild(icon);


// Lắng nghe sự kiện khi người dùng bôi đen văn bản
document.addEventListener('mouseup', function() {
  let selectedText = window.getSelection().toString();
  console.log('Selected text:', selectedText); // Log the selected text

  if (selectedText) {
    icon.style.display = 'block';
    icon.setAttribute('data-selected-text', selectedText);
    
    // Get the position of the selected text
    let range = window.getSelection().getRangeAt(0);
    let rect = range.getBoundingClientRect();
    
    // Position the icon just below the selected text
    icon.style.top = `${rect.bottom + window.scrollY + 5}px`; // Add a little space below
    icon.style.left = `${rect.right + window.scrollX}px`;  // Align with the left of the selected text
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
