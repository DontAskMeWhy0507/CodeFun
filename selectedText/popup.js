document.addEventListener('DOMContentLoaded', function () {
  const spinner = document.getElementById('spinner');
  const selectedTextElement = document.getElementById('selected-text');
  const errorElement = document.getElementById('error');
  const definitionElement = document.getElementById('definition');
  const translationElement = document.getElementById('translation');
  const exampleElement = document.getElementById('example');
  const nextBtn = document.getElementById('next'); // Next button for navigation
  const prevBtn = document.getElementById('prev'); // Previous button for navigation

  let wordef = [];
  let index = 0;
  let indlimit = 0;
  let audio;
  let word, phonetic, sourceurl;

  // Hiển thị spinner ban đầu
  spinner.style.display = 'block';
  selectedTextElement.style.display = 'none';

  // Lắng nghe tin nhắn từ background script
  chrome.runtime.onMessage.addListener((message, sender, sendResponse) => {
    if (message.action === 'updatePopup') {
      const text = decodeURIComponent(message.text).trim() || "Chưa có văn bản được chọn.";

      selectedTextElement.textContent = text;
      spinner.style.display = 'none';
      selectedTextElement.style.display = 'block';

      if (text.split(' ').length === 1) {
        dictionary(text);
      } else {
        readTextAloud(text);
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
        sourceurl = `https://en.wiktionary.org/wiki/${word}`;
        let audioUrl = wordef[0].phonetics.length > 0 ? wordef[0].phonetics[0].audio : null;

        // Fallback to Google Translate if no audio is found
        if (!audioUrl) {
          audioUrl = `https://translate.google.com/translate_tts?ie=UTF-8&client=tw-ob&q=${word}&tl=en`;
        }
        
        audio = new Audio(audioUrl);
        audio.play(); // Automatically play the pronunciation audio

        setValues();
        if (indlimit > 1) {
          document.getElementById("navigatecontainer").classList.remove("hidden");
        }

      } else {
        errorElement.innerHTML = "⚠ No definitions found.";
        definitionElement.innerHTML = "No definitions found for the selected word.";
      }
    } catch (error) {
      console.error('Error fetching dictionary:', error);
      errorElement.innerHTML = "⚠ Error fetching definition.";
      exampleElement.innerHTML = "";
    }
  }

  // Get the selected text from the query parameter (if present)
  const urlParams = new URLSearchParams(window.location.search);
  const selectedText = urlParams.get("text");
  if (selectedText) {
    dictionary(selectedText);
  }

  // Handle Previous button click
  nextBtn.addEventListener('click', function () {
    index = index + 1;
    if (index >= indlimit) index = 0; // Loop back to the first meaning
    setValues();
  });

  // Handle Previous button click
  prevBtn.addEventListener('click', function () {
    index = index - 1;
    if (index < 0) index = indlimit - 1; // Loop back to the last meaning
    setValues();
  });

  // Pronounce the word
  document.getElementById("pronounce").addEventListener("click", function () {
    if (audio) {
      audio.play();
    }
  });

  function setValues() {
    const pos = wordef[0].meanings[index].partOfSpeech;
    const definition = wordef[0].meanings[index].definitions[0].definition;
    const example = wordef[0].meanings[index].definitions[0].example || "No example available.";

    document.getElementById("word").innerHTML = `${word} <a href=${sourceurl} class="searchanchor" target="_blank">Read More</a>`;
    document.getElementById("phonetic").innerHTML = `${phonetic}  (${pos})`;
    document.getElementById("definition").innerHTML = definition;
    document.getElementById("example").innerHTML = example;

    // Enable or disable navigation buttons based on the current index
    prevBtn.disabled = index === 0;
    nextBtn.disabled = index === indlimit - 1;
  }

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
      console.error('Error translating text:', error);
      errorElement.innerHTML = "⚠ Error translating text.";
    }
  }
});
