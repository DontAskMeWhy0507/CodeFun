import requests

url = "https://www.youtube.com/feeds/videos.xml?channel_id=INVALID_CHANNEL_ID"  # Restricted API

try:
    response = requests.get(url, timeout=5)
    print(f"Status Code: {response.status_code}")
except requests.exceptions.RequestException as e:
    print(f"Error: {e}")
