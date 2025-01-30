document.addEventListener('DOMContentLoaded', function () {
  const spinner = document.getElementById('spinner');
  const selectedTextElement = document.getElementById('selected-text');
  const errorElement = document.getElementById('error');
  const definitionElement = document.getElementById('definition');
  const translationElement = document.getElementById('translation');
  const exampleElement = document.getElementById('example');
  const nextBtn = document.getElementById('next');
  const prevBtn = document.getElementById('prev');
  const readMoreBtn = document.getElementById('read-more');
  const aiTranslateBtn = document.getElementById('ai-translate'); // Nút Dịch bằng AI
  const aiExplainBtn = document.getElementById('ai-explain'); // Nút Giải thích bằng AI

  let wordef = [];
  let index = 0;
  let indlimit = 0;
  let audio;
  let word, phonetic, sourceurl;

  spinner.style.display = 'block';
  selectedTextElement.style.display = 'none';

  chrome.runtime.onMessage.addListener((message, sender, sendResponse) => {
    if (message.action === 'updatePopup') {
      const text = decodeURIComponent(message.text).trim() || "Chưa có văn bản được chọn.";

      selectedTextElement.textContent = text;
      spinner.style.display = 'none';
      selectedTextElement.style.display = 'block';

      if (text.split(' ').length === 1) {
        dictionary(text);
        translateText(text);
      } else {
        translateText(text);
      }
    }
  });

  async function dictionary(query) {
    let url = `https://api.dictionaryapi.dev/api/v2/entries/en/${query}`;
    try {
      let response = await fetch(url);
      wordef = await response.json();

      if (wordef && !wordef.title) {
        indlimit = wordef[0].meanings.length;
        word = wordef[0].word;
        phonetic = wordef[0].phonetic || '';
        sourceurl = `https://www.google.com/search?q=define%20${word}`;
        let audioUrl = wordef[0].phonetics.length > 0 ? wordef[0].phonetics[0].audio : null;

        if (!audioUrl) {
          audioUrl = `https://translate.google.com/translate_tts?ie=UTF-8&client=tw-ob&q=${word}&tl=en`;
        }

        audio = new Audio(audioUrl);
        audio.play();

        setValues();
        if (indlimit > 1) {
          document.getElementById("navigatecontainer").classList.remove("hidden");
        }
      } else {
        errorElement.innerHTML = "⚠ Không tìm thấy định nghĩa.";
        definitionElement.innerHTML = "Không tìm thấy định nghĩa cho từ đã chọn.";
      }
    } catch (error) {
      console.error('Lỗi tải dữ liệu từ từ điển:', error);
      errorElement.innerHTML = "⚠ Lỗi khi lấy định nghĩa.";
      exampleElement.innerHTML = "";
    }
  }

  nextBtn.addEventListener('click', function () {
    if (index < indlimit - 1) {
      index++;
      setValues();
    }
  });

  prevBtn.addEventListener('click', function () {
    if (index > 0) {
      index--;
      setValues();
    }
  });

  document.getElementById("pronounce").addEventListener("click", function () {
     if (audio) {
      audio.play();
    } else {
      const text = selectedTextElement.textContent;
      if (text && text !== "Chưa có văn bản được chọn.") {
        readTextAloud(text);
      }
    }
  });

  function setValues() {
    const pos = wordef[0].meanings[index].partOfSpeech;
    const definition = wordef[0].meanings[index].definitions[0].definition;
    const example = wordef[0].meanings[index].definitions[0].example || '';

    document.getElementById("phonetic").innerHTML = `${phonetic}  (${pos})`;
    document.getElementById("definition").innerHTML = definition;
    document.getElementById("example").innerHTML = example;

    prevBtn.disabled = index === 0;
    nextBtn.disabled = index === indlimit - 1;

    prevBtn.classList.toggle('disabled', index === 0);
    nextBtn.classList.toggle('disabled', index === indlimit - 1);
  }

  readMoreBtn.addEventListener('click', function () {
    window.open(sourceurl, '_blank');
  });

  function readTextAloud(text) {
    if ('speechSynthesis' in window) {
      const utterance = new SpeechSynthesisUtterance(text);
      utterance.lang = 'en-US';
      window.speechSynthesis.speak(utterance);
    } else {
      console.error('Speech synthesis not supported');
    }
  }

  async function translateText(text) {
    try {
      let url = `https://translate.googleapis.com/translate_a/single?client=gtx&sl=auto&tl=vi&dt=t&q=${encodeURIComponent(text)}`;
      let response = await fetch(url);
      let translation = await response.json();
      let translatedText = translation[0].map(item => item[0]).join(' ');
      translationElement.textContent = translatedText;
    } catch (error) {
      console.error('Lỗi khi dịch văn bản:', error);
      errorElement.innerHTML = "⚠ Lỗi khi dịch văn bản.";
    }
  }

  async function translateTextGeminiAI(text) {
    let apiKey = "AIzaSyDuZLRlrXKedQsgHSO41NIU1nVP4L53kvk"; // Thay thế bằng API key hợp lệ
    let url = `https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-flash:generateContent?key=${apiKey}`;
    let requestBody = {
      contents: [{
        parts: [{ text: "dịch chính xác cho tôi sang tiếng việt câu này: " + text }]
      }]
    };

    try {
      let response = await fetch(url, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json'
        },
        body: JSON.stringify(requestBody)
      });

      let result = await response.json();
      if (result && result.candidates) {
        let translatedText = result.candidates[0].content.parts[0].text;
        translationElement.textContent = translatedText;
      } else {
        throw new Error("Phản hồi không hợp lệ từ Gemini AI.");
      }
    } catch (error) {
      console.error('Lỗi khi dịch văn bản với Gemini AI:', error);
      errorElement.innerHTML = "⚠ Lỗi khi dịch bằng AI.";
    }
  }

  async function explainTextByAI (text) {
    let apiKey = "AIzaSyDuZLRlrXKedQsgHSO41NIU1nVP4L53kvk"; // Thay thế bằng API key hợp lệ
    let url = `https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-flash:generateContent?key=${apiKey}`;
    let requestBody = {
      contents: [{
        parts: [{ text: "giải thích câu này trong tiếng việt: " + text }]
      }]
    };
    try {
      let response = await fetch(url, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json'
        },
        body: JSON.stringify(requestBody)
      });

      let result = await response.json();
      if (result && result.candidates) {
        let translatedText = result.candidates[0].content.parts[0].text;
        translationElement.textContent = translatedText;
      } else {
        throw new Error("Phản hồi không hợp lệ từ Gemini AI.");
      }
    } catch (error) {
      console.error('Lỗi khi dịch văn bản với Gemini AI:', error);
      errorElement.innerHTML = "⚠ Lỗi khi dịch bằng AI.";
    }

  }

  aiExplainBtn.addEventListener('click', function () {
    const text = selectedTextElement.textContent;

    if (!text || text === "Chưa có văn bản được chọn.") {
      errorElement.innerHTML = "⚠ Vui lòng chọn văn bản để dịch.";
      return;
    }

    spinner.style.display = 'block';
    translationElement.textContent = '';

    explainTextByAI(text).finally(() => {
      spinner.style.display = 'none';
    });
  });

 
  aiTranslateBtn.addEventListener('click', function () {
    const text = selectedTextElement.textContent;

    if (!text || text === "Chưa có văn bản được chọn.") {
      errorElement.innerHTML = "⚠ Vui lòng chọn văn bản để dịch.";
      return;
    }

    spinner.style.display = 'block';
    translationElement.textContent = '';

    translateTextGeminiAI(text).finally(() => {
      spinner.style.display = 'none';
    });
  });

 

});
