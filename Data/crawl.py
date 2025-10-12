import requests
from bs4 import BeautifulSoup
import time
import csv
import json
import random
from urllib.parse import urljoin, quote
import logging

# Cấu hình logging
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')
logger = logging.getLogger(__name__)

class LinkedInJobsCrawler:
    def __init__(self, delay_range=(2, 5)):
        self.delay_range = delay_range
        self.session = requests.Session()
        
        # Headers để giả lập browser thật
        self.session.headers.update({
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36',
            'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8',
            'Accept-Language': 'en-US,en;q=0.5',
            'Accept-Encoding': 'gzip, deflate, br',
            'Connection': 'keep-alive',
            'Upgrade-Insecure-Requests': '1',
            'Sec-Fetch-Dest': 'document',
            'Sec-Fetch-Mode': 'navigate',
            'Sec-Fetch-Site': 'none',
        })
        
        self.jobs_data = []
        self.base_url = "https://www.linkedin.com"
    
    def random_delay(self):
        """Tạo delay ngẫu nhiên để tránh bị phát hiện"""
        delay = random.uniform(self.delay_range[0], self.delay_range[1])
        time.sleep(delay)
    
    def get_page(self, url, retries=3):
        """Lấy nội dung trang với retry logic"""
        for attempt in range(retries):
            try:
                self.random_delay()
                response = self.session.get(url, timeout=15)
                
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
    
    def search_jobs(self, keywords="", location="", start=0):
        """Tìm kiếm việc làm với từ khóa và địa điểm"""
        # Tạo URL tìm kiếm
        search_url = f"{self.base_url}/jobs/search?"
        
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
    
    def extract_job_links_from_search(self, soup):
        """Trích xuất các link công việc từ trang tìm kiếm"""
        job_links = []
        
        # Tìm các thẻ chứa link công việc
        job_cards = soup.find_all(['div', 'li'], class_=lambda x: x and 'job' in x.lower())
        
        for card in job_cards:
            # Tìm link trong card
            link_element = card.find('a', href=True)
            if link_element:
                href = link_element.get('href')
                if '/jobs/view/' in href:
                    full_url = urljoin(self.base_url, href)
                    job_links.append(full_url)
        
        # Fallback: tìm tất cả link có chứa /jobs/view/
        if not job_links:
            all_links = soup.find_all('a', href=True)
            for link in all_links:
                href = link.get('href')
                if href and '/jobs/view/' in href:
                    full_url = urljoin(self.base_url, href)
                    job_links.append(full_url)
        
        return list(set(job_links))  # Loại bỏ duplicate
    
    def extract_job_details(self, job_url):
        """Trích xuất chi tiết công việc từ URL"""
        response = self.get_page(job_url)
        if not response:
            return None
        
        soup = BeautifulSoup(response.content, 'html.parser')
        
        job_data = {
            'url': job_url,
            'title': self.extract_job_title(soup),
            'company': self.extract_company_name(soup),
            'location': self.extract_location(soup),
            'description': self.extract_description(soup),
            'employment_type': self.extract_employment_type(soup),
            'experience_level': self.extract_experience_level(soup),
            'posted_date': self.extract_posted_date(soup),
            'salary': self.extract_salary(soup),
            'applicants_count': self.extract_applicants_count(soup)
        }
        
        return job_data
    
    def extract_job_title(self, soup):
        """Trích xuất tiêu đề công việc"""
        selectors = [
            'h1.top-card-layout__title',
            'h1[class*="job-title"]',
            'h1[class*="title"]',
            '.job-details-jobs-unified-top-card__job-title h1',
            'h1'
        ]
        
        for selector in selectors:
            element = soup.select_one(selector)
            if element:
                title = element.get_text().strip()
                if title and len(title) > 3:
                    return title
        
        return "Unknown Title"
    
    def extract_company_name(self, soup):
        """Trích xuất tên công ty"""
        selectors = [
            '.job-details-jobs-unified-top-card__company-name a',
            '.job-details-jobs-unified-top-card__company-name',
            '[class*="company-name"]',
            'a[class*="company"]'
        ]
        
        for selector in selectors:
            element = soup.select_one(selector)
            if element:
                company = element.get_text().strip()
                if company:
                    return company
        
        return "Unknown Company"
    
    def extract_location(self, soup):
        """Trích xuất địa điểm"""
        selectors = [
            '.job-details-jobs-unified-top-card__bullet',
            '[class*="location"]',
            '.job-details-jobs-unified-top-card__primary-description'
        ]
        
        for selector in selectors:
            element = soup.select_one(selector)
            if element:
                location = element.get_text().strip()
                if location and (',' in location or any(word in location.lower() for word in ['city', 'remote', 'hybrid'])):
                    return location
        
        return "Unknown Location"
    
    def extract_description(self, soup):
        """Trích xuất mô tả công việc"""
        selectors = [
            '.job-details-jobs-unified-top-card__job-description',
            '.jobs-description__content',
            '[class*="description"]',
            '.job-details-module'
        ]
        
        for selector in selectors:
            element = soup.select_one(selector)
            if element:
                # Loại bỏ các thẻ không cần thiết
                for tag in element(['script', 'style']):
                    tag.decompose()
                
                description = element.get_text().strip()
                if description and len(description) > 50:
                    return description[:500]  # Giới hạn 500 ký tự
        
        return "No description available"
    
    def extract_employment_type(self, soup):
        """Trích xuất loại hình công việc"""
        text = soup.get_text().lower()
        
        employment_types = ['full-time', 'part-time', 'contract', 'temporary', 'internship', 'freelance']
        for emp_type in employment_types:
            if emp_type in text:
                return emp_type.title()
        
        return "Unknown"
    
    def extract_experience_level(self, soup):
        """Trích xuất mức độ kinh nghiệm"""
        text = soup.get_text().lower()
        
        levels = ['entry level', 'associate', 'mid-senior level', 'director', 'executive']
        for level in levels:
            if level in text:
                return level.title()
        
        return "Unknown"
    
    def extract_posted_date(self, soup):
        """Trích xuất ngày đăng"""
        selectors = [
            'time',
            '[class*="posted"]',
            '[class*="date"]'
        ]
        
        for selector in selectors:
            element = soup.select_one(selector)
            if element:
                date_text = element.get('datetime') or element.get_text().strip()
                if date_text:
                    return date_text
        
        return "Unknown"
    
    def extract_salary(self, soup):
        """Trích xuất mức lương"""
        text = soup.get_text()
        
        # Tìm các pattern lương
        import re
        salary_patterns = [
            r'\$[\d,]+\s*-\s*\$[\d,]+',
            r'\$[\d,]+',
            r'[\d,]+\s*USD',
            r'[\d,]+\s*VND'
        ]
        
        for pattern in salary_patterns:
            match = re.search(pattern, text)
            if match:
                return match.group()
        
        return "Not specified"
    
    def extract_applicants_count(self, soup):
        """Trích xuất số lượng ứng viên"""
        text = soup.get_text()
        
        import re
        applicant_pattern = r'(\d+)\s+applicants?'
        match = re.search(applicant_pattern, text, re.IGNORECASE)
        
        if match:
            return match.group(1)
        
        return "Unknown"
    
    def crawl_jobs(self, keywords="python developer", location="Vietnam", target_count=100):
        """Crawl các công việc từ LinkedIn"""
        logger.info(f"Bắt đầu crawl {target_count} công việc với từ khóa: '{keywords}', địa điểm: '{location}'")
        
        collected_jobs = 0
        start_index = 0
        page_size = 25  # LinkedIn thường hiển thị 25 jobs/trang
        
        while collected_jobs < target_count:
            logger.info(f"Đang crawl trang {start_index // page_size + 1} (jobs {start_index + 1}-{start_index + page_size})")
            
            # Tìm kiếm jobs
            response = self.search_jobs(keywords, location, start_index)
            if not response:
                logger.error("Không thể tải trang tìm kiếm")
                break
            
            soup = BeautifulSoup(response.content, 'html.parser')
            
            # Trích xuất các link công việc
            job_links = self.extract_job_links_from_search(soup)
            
            if not job_links:
                logger.warning("Không tìm thấy link công việc nào trên trang này")
                break
            
            logger.info(f"Tìm thấy {len(job_links)} link công việc")
            
            # Crawl chi tiết từng công việc
            for i, job_url in enumerate(job_links):
                if collected_jobs >= target_count:
                    break
                
                logger.info(f"Đang crawl job {collected_jobs + 1}/{target_count}: {job_url}")
                
                job_data = self.extract_job_details(job_url)
                if job_data and job_data['title'] != "Unknown Title":
                    self.jobs_data.append(job_data)
                    collected_jobs += 1
                    
                    logger.info(f"✓ Thu thập: {job_data['title']} tại {job_data['company']}")
                else:
                    logger.warning("Không thể trích xuất dữ liệu job")
            
            start_index += page_size
            
            # Nghỉ giữa các trang
            logger.info("Đang nghỉ giữa các trang...")
            time.sleep(random.uniform(5, 10))
        
        logger.info(f"Hoàn thành crawl {len(self.jobs_data)} công việc")
    
    def save_to_csv(self, filename='linkedin_jobs.csv'):
        """Lưu dữ liệu ra file CSV"""
        if not self.jobs_data:
            logger.warning("Không có dữ liệu để lưu")
            return
        
        filepath = f"c:\\Work\\CodeFun\\Data\\{filename}"
        
        with open(filepath, 'w', newline='', encoding='utf-8') as csvfile:
            fieldnames = self.jobs_data[0].keys()
            writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
            
            writer.writeheader()
            for job in self.jobs_data:
                writer.writerow(job)
        
        logger.info(f"Đã lưu {len(self.jobs_data)} công việc vào {filepath}")
    
    def save_to_json(self, filename='linkedin_jobs.json'):
        """Lưu dữ liệu ra file JSON"""
        if not self.jobs_data:
            logger.warning("Không có dữ liệu để lưu")
            return
        
        filepath = f"c:\\Work\\CodeFun\\Data\\{filename}"
        
        with open(filepath, 'w', encoding='utf-8') as jsonfile:
            json.dump(self.jobs_data, jsonfile, ensure_ascii=False, indent=2)
        
        logger.info(f"Đã lưu {len(self.jobs_data)} công việc vào {filepath}")
    
    def display_summary(self):
        """Hiển thị tóm tắt dữ liệu đã crawl"""
        if not self.jobs_data:
            print("Không có dữ liệu để hiển thị")
            return
        
        print(f"\n=== TÓNG KẾT CRAWL LINKEDIN JOBS ===")
        print(f"Tổng số công việc: {len(self.jobs_data)}")
        
        # Thống kê theo công ty
        companies = {}
        locations = {}
        
        for job in self.jobs_data:
            company = job['company']
            location = job['location']
            
            companies[company] = companies.get(company, 0) + 1
            locations[location] = locations.get(location, 0) + 1
        
        print(f"\nTop 5 công ty có nhiều việc làm nhất:")
        for company, count in sorted(companies.items(), key=lambda x: x[1], reverse=True)[:5]:
            print(f"  {company}: {count} jobs")
        
        print(f"\nTop 5 địa điểm có nhiều việc làm nhất:")
        for location, count in sorted(locations.items(), key=lambda x: x[1], reverse=True)[:5]:
            print(f"  {location}: {count} jobs")
        
        # Hiển thị một số ví dụ
        print(f"\n=== VÍ DỤ 3 CÔNG VIỆC ĐẦU TIÊN ===")
        for i, job in enumerate(self.jobs_data[:3]):
            print(f"\n{i+1}. {job['title']}")
            print(f"   Công ty: {job['company']}")
            print(f"   Địa điểm: {job['location']}")
            print(f"   Lương: {job['salary']}")
            print(f"   URL: {job['url']}")

# Sử dụng crawler
if __name__ == "__main__":
    # Tạo crawler
    crawler = LinkedInJobsCrawler(delay_range=(2, 4))
    
    # Các từ khóa tìm kiếm khác nhau
    search_queries = [
        ("python developer", "Vietnam"),
        ("software engineer", "Ho Chi Minh City"),
        ("data analyst", "Hanoi"),
        ("project manager", "Vietnam"),
        ("marketing manager", "Vietnam")
    ]
    
    # Crawl với từ khóa đầu tiên
    keywords, location = search_queries[0]
    crawler.crawl_jobs(keywords=keywords, location=location, target_count=100)
    
    # Lưu dữ liệu
    crawler.save_to_csv()
    crawler.save_to_json()
    
    # Hiển thị tóm tắt
    crawler.display_summary()
    
    print(f"\n=== HOÀN THÀNH ===")
    print("Files đã được lưu tại:")
    print("- c:\\Work\\CodeFun\\Data\\linkedin_jobs.csv")
    print("- c:\\Work\\CodeFun\\Data\\linkedin_jobs.json")