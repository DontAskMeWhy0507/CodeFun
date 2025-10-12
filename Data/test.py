import requests
from bs4 import BeautifulSoup

url = "https://docs.google.com/spreadsheets/d/1DTtmHpSD6f2iIDVJNTdAn1xnUtcLyCD8Iy3O9sW5s54/edit?fbclid=IwY2xjawNA921leHRuA2FlbQIxMABicmlkETFVbVV3eEdSUjBCTTA0NlhQAR60PbkpAEGLReeGAcJdHUyJ8mmBUCb4oCeU33Maed5Bidx39CLgdDsYzVbq2A_aem_C9GlrS5KvK8er-YghiPEkQ&gid=1608374136#gid=1608374136"
response = requests.get(url)

## export file 
if response.status_code == 200:
    soup = BeautifulSoup(response.text, "html.parser")
    titles = soup.find_all("h3", class_="title-news")
    for idx, t in enumerate(titles, start=1):
        print(f"{idx}. {t.get_text(strip=True)}")

    print ("Download file")
else:
    print("Không thể truy cập trang web")   
