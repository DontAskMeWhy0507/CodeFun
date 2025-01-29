// get the currently active tab in the current window
// and then invoke the callback function gotTabs.
let query = { active: true, currentWindow: true };
chrome.tabs.query(query, gotTabs);

// function to check current url and eliminate offline urls.
function safeUrl(url) {
  return url.startsWith("https://") || url.startsWith("http://");
}

// callback function
function gotTabs(tabs) {
  // prevent offline urls to run the extension by throwing error.
  if (!safeUrl(tabs[0].url)) {
    document.getElementById("error").innerHTML = "Oh no!";
    document.getElementById("definition").innerHTML = "Unsupported Page.";
    return;
  }

  let msg = {
    txt: "hello from popup",
  };

  // send message to the content script
  chrome.tabs.sendMessage(tabs[0].id, msg, function (response) {
    if (!response) {
      document.getElementById("phonetic").innerHTML =
        "Refresh the page and try again.";
    } else if (response.swor === "_TextNotSelected_") {
      document.getElementById("phonetic").innerHTML = "Welcome!";
      document.getElementById("example").innerHTML =
        "Please select a word to find its definition.";
    } else {
      let swo = response.swor;
      swo = swo.replace(/[^a-zA-Z ]/g, "");
      dictionary(swo);
    }
  });
}

// Get the selected text from the query parameter
const urlParams = new URLSearchParams(window.location.search);
const selectedText = urlParams.get("text");
if (selectedText) {
  dictionary(selectedText);
}

let wordef,
  word,
  phonetic,
  pos,
  defin,
  example,
  sourceurl,
  index = 0,
  indlimit,
  audio;

// function to fetch and show definition on the popup
async function dictionary(query) {
  let url = `https://api.dictionaryapi.dev/api/v2/entries/en/${query}`;
  let response = await fetch(url);
  wordef = await response.json();
  if (wordef && !wordef.title) {
    indlimit = wordef[0].meanings.length;
    word = wordef[0].word;
    phonetic = wordef[0].phonetic ? wordef[0].phonetic : "";
    sourceurl = `https://en.wiktionary.org/wiki/${word}`;
    index = 0;
    let audioUrl = wordef[0].phonetics.length > 0 ? wordef[0].phonetics[0].audio : null;
    if (!audioUrl) {
      audioUrl = `https://translate.google.com/translate_tts?ie=UTF-8&client=tw-ob&q=${word}&tl=en`;
    }
    audio = new Audio(audioUrl);
    audio.play(); // Automatically play the pronunciation audio

    setValues();

    if (indlimit > 1) {
      document
        .getElementById("navigatecontainer")
        .classList.remove("hidenavigator");
    }
  } else if (wordef.title) {
    document.getElementById("error").innerHTML = "⚠ No definitions found.";
    document.getElementById("definition").innerHTML = "No definitions found for the selected word.";
  }
}

document.getElementById("prev").addEventListener("click", handlePrevious);
document.getElementById("next").addEventListener("click", handleNext);
document.getElementById("pronounce").addEventListener("click", () => {
  if (audio) {
    audio.play();
  }
});

function handlePrevious() {
  index = index - 1;
  if (index < 0) index = indlimit - 1;
  setValues();
}

function handleNext() {
  index = index + 1;
  if (index >= indlimit) index = 0;
  setValues();
}

function setValues() {
  pos = wordef[0].meanings[index].partOfSpeech;
  defin = wordef[0].meanings[index].definitions[0].definition;
  example = wordef[0].meanings[index].definitions[0].example
    ? wordef[0].meanings[index].definitions[0].example
    : null;

  document.getElementById(
    "word"
  ).innerHTML = `${word} <a href=${sourceurl} class="searchanchor" target="_blank"><img class="searchsvg" title="read more" src = "../assets/searchonweb.svg" alt="read more"/><a>`;
  document.getElementById("phonetic").innerHTML = `${phonetic}  (${pos})`;
  document.getElementById("definition").innerHTML = defin;
  if (example) {
    document.getElementById("example").innerHTML = `Example: ${example}`;
  } else {
    document.getElementById("example").innerHTML = "";
  }
}
