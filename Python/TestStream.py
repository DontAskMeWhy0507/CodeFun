import requests

url = "https://vebo.thethaoiptv.com/stream/zhV60ee/wpael0y"
headers = {
    "Ping": "https://go.eztool.xyz/ping"
}

res = requests.get(url, headers=headers)
print(res.text)  # nếu thành công, sẽ ra file .m3u8
