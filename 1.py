import requests
from bs4 import BeautifulSoup
import json

class LinkedInJobsCrawler:
    def __init__(self, url):
        self.url = url
        self.headers = {
            "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3"
        }
        self.job_data = []
        self.base_url = "https://www.linkedin.com"

    def get_page(self, url, retries = 3):
        # Get page content with retry logic
        for attempt in range(retries):
            try:
                response = self.session.get(url, timeout = 15)
                if response.status_code == 200:
                    return response
                elif response.status_code == 429:
                    logger.warning(f"Rate limited, đợi lâu hơn... (attempt {attempt + 1})")
                    time.sleep(30)
                else:
                    logger.warning(f"Status code: {response.status_code} for {url}")
                    
            except requests.RequestException as e:
                logger.error(f"Lỗi request (attempt {attempt + 1}): {e}")
                if attempt < retries - 1:
                    time.sleep(10)
        
        return None
    
    def search_jobs(self, keywords = "", location = "", start = 0):
        search_url  = f"{self.base_url}/jobs/search/?"

        params = []
        if keywords:
            params.append(f"keywords={quote(keywords)}")
        if location:
            params.append(f"location={quote(location)}")
        params.append(f"start={start}")
        params.append("f_TPR=r604800")  # Jobs posted in last week
        
        search_url += "&".join(params)
        
        logger.info(f"Tìm kiếm: {search_url}")
        return self.get_page(search_url)
    
    def crawl_job(self, keywords = "", location = "", max_jobs = 50):
        start = 0
        while len(self.job_data) < max_jobs:
            page = self.search_jobs(keywords, location, start)
            if not page:
                break
            
            soup = BeautifulSoup(page.content, "html.parser")
            job_cards = soup.find_all("div", class_="result-card__contents job-result-card__contents")
            if not job_cards:
                logger.info("Không tìm thấy thêm công việc.")
                break
            
            for card in job_cards:
                if len(self.job_data) >= max_jobs:
                    break
                
                job_info = self.parse_job_card(card)
                if job_info:
                    self.job_data.append(job_info)
            
            start += len(job_cards)
        
        return self.job_data


if __name__ == "__main__":
    search_queries = [
        ("Data Engineer", "Vietnam")
    ]

    crawler = LinkedInJobsCrawler(url)
    page = crawler.get_page(url)
    if page:
        soup = BeautifulSoup(page.content, "html.parser")
        print(soup.prettify())
