import requests
from bs4 import BeautifulSoup
import time
import csv
import os
from datetime import datetime

class Linkedin:
    def __init__(self):
        self.session = requests.Session()
        # Add headers to properly handle Vietnamese content
        self.session.headers.update({
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36',
            'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
            'Accept-Language': 'en-US,en;q=0.5,vi;q=0.3',
            'Accept-Encoding': 'gzip, deflate',
            'Accept-Charset': 'UTF-8'
        })
        self.job_data = []
        self.base_url = "https://www.linkedin.com"
    
    def get_page(self, url):
        try:
            response = self.session.get(url)
            # Ensure proper encoding for Vietnamese content
            response.encoding = 'utf-8'
            if response.status_code == 200:
                return response.text
            else:
                print(f"Failed to retrieve page: {url}, Status: {response.status_code}")
                return None
        except Exception as e:
            print(f"Error fetching page {url}: {e}")
            return None

    def get_job_description(self, job_url):
        """Fetch full job description from individual job page with proper Vietnamese encoding"""
        html = self.get_page(job_url)

        if not html:
            return "N/A"
        
        # Parse with proper encoding
        soup = BeautifulSoup(html, 'html.parser', from_encoding='utf-8')
        
        # Try multiple selectors for job description - updated for current LinkedIn structure
        description_selectors = [
            'div.show-more-less-html__markup',
            'div.description__text--rich',
            'section.description .core-section-container__content',
            'div.jobs-description-content__text',
            '.jobs-box__html-content',
            'div.description__text',
            'section.description',
            'div[data-test-id="job-description"]'
        ]
        
        description_text = ""
        
        for selector in description_selectors:
            description_elem = soup.select_one(selector)
            if description_elem:
                # Get all text content, preserving some structure and Vietnamese characters
                description_text = description_elem.get_text(separator='\n', strip=True)
                break
        
        # If no description found with primary selectors, try broader search
        if not description_text:
            # Look for any section that might contain job details
            possible_containers = [
                soup.find('section', class_='description'),
                soup.find('div', class_='decorated-job-posting__details'),
                soup.find('main', id='main-content')
            ]
            
            for container in possible_containers:
                if container:
                    # Look for large text blocks that might be the description
                    text_elements = container.find_all(['div', 'section', 'p'], 
                                                     string=lambda text: text and len(text.strip()) > 100)
                    if text_elements:
                        description_text = text_elements[0].get_text(separator='\n', strip=True)
                        break
        
        # Clean up the extracted text while preserving Vietnamese characters
        if description_text:
            # Remove excessive whitespace and normalize line breaks
            lines = [line.strip() for line in description_text.split('\n') if line.strip()]
            description_text = '\n'.join(lines)
            
            # Look for common job description sections and extract the main content
            # Remove navigation elements, headers, footers that might be included
            exclude_patterns = [
                'Skip to main content',
                'LinkedIn',
                'Sign in',
                'Join now',
                'Apply',
                'Save',
                'Show more',
                'Show less',
                'Similar jobs',
                'People also viewed',
                '© 2025',
                'Đăng nhập',  # Vietnamese "Sign in"
                'Tham gia ngay',  # Vietnamese "Join now"
                'Ứng tuyển',  # Vietnamese "Apply"
                'Lưu',  # Vietnamese "Save"
            ]
            
            filtered_lines = []
            for line in lines:
                # Skip lines that are likely navigation or UI elements
                if not any(pattern.lower() in line.lower() for pattern in exclude_patterns):
                    # Skip very short lines that are likely UI elements
                    if len(line) > 10 or any(keyword in line.lower() for keyword in [
                        'responsibilities', 'requirements', 'qualifications', 'benefits', 
                        'experience', 'skills', 'education', 'contact',
                        'trách nhiệm', 'yêu cầu', 'kinh nghiệm', 'kỹ năng', 'quyền lợi'  # Vietnamese keywords
                    ]):
                        filtered_lines.append(line)
            
            if filtered_lines:
                description_text = '\n'.join(filtered_lines)
            
            return description_text
        
        return "N/A"

    def fetch_job_data(self, keywords=None, location=None, limit=10, get_full_description=False):
        """Fetch job data with pagination support"""
        self.job_data = []  # Reset job data
        jobs_fetched = 0
        page = 0
        
        while jobs_fetched < limit:
            job_search_url = f"{self.base_url}/jobs/search/"
            
            # Add search parameters
            params = {}
            if keywords:
                params['keywords'] = keywords
            if location:
                params['location'] = location
            
            # Add pagination parameter
            params['start'] = page * 25  # LinkedIn typically shows 25 jobs per page
            
            param_string = '&'.join([f"{key}={value}" for key, value in params.items()])
            job_search_url += f"?{param_string}"
            
            print(f"Fetching page {page + 1}...")
            html = self.get_page(job_search_url)
            
            if not html:
                print("Failed to fetch page, stopping.")
                break
            
            # Parse jobs from current page
            jobs_on_page = self.parse_job_data_page(html, limit - jobs_fetched, get_full_description, jobs_fetched)
            
            if jobs_on_page == 0:
                print("No more jobs found, stopping pagination.")
                break
            
            jobs_fetched += jobs_on_page
            page += 1
            
            # Add delay between pages to avoid being blocked
            if jobs_fetched < limit:
                time.sleep(2)

    def parse_job_data_page(self, html, remaining_limit, get_full_description=False, jobs_processed=0):
        """Parse jobs from a single page with proper Vietnamese text handling"""
        # Parse with proper encoding
        soup = BeautifulSoup(html, 'html.parser', from_encoding='utf-8')
        job_elements = soup.find_all('div', class_='job-search-card')
        
        if not job_elements:
            return 0
        
        # Limit jobs to process from this page
        jobs_to_process = min(len(job_elements), remaining_limit)
        job_elements = job_elements[:jobs_to_process]
        
        for i, job in enumerate(job_elements):
            try:
                title_elem = job.find('h3')
                company_elem = job.find('h4')
                location_elem = job.find('span', class_='job-search-card__location')
                link_elem = job.find('a', href=True)
                
                # Extract text with proper encoding
                title = title_elem.get_text(strip=True) if title_elem else "N/A"
                company = company_elem.get_text(strip=True) if company_elem else "N/A"
                location = location_elem.get_text(strip=True) if location_elem else "N/A"
                
                # Process the job link
                link = "N/A"
                if link_elem:
                    href = link_elem['href']
                    if href.startswith('/'):
                        link = self.base_url + href
                    elif href.startswith('http'):
                        link = href
                    else:
                        link = f"{self.base_url}/{href}"
                
                # Get description
                description = "N/A"
                if get_full_description and link != "N/A":
                    print(f"Fetching description for job {jobs_processed + i + 1}...")
                    description = self.get_job_description(link)
                    time.sleep(1)  # Add delay to avoid being blocked
                else:
                    description_elem = job.find('p', class_='job-search-card__snippet') or \
                                     job.find('div', class_='job-search-card__snippet') or \
                                     job.find('span', class_='job-search-card__snippet')
                    if description_elem:
                        description = description_elem.get_text(strip=True)
                
                self.job_data.append({
                    'title': title,
                    'company': company,
                    'location': location,
                    'link': link,
                    'description': description
                })
                
            except (AttributeError, UnicodeDecodeError) as e:
                print(f"Error parsing job: {e}")
                continue
        
        return len(job_elements)

    def search_jobs(self, title_keyword=None, location_keyword=None, limit=None):
        """Search through fetched job data by title and/or location"""
        filtered_jobs = []
        
        for job in self.job_data:
            title_match = True
            location_match = True
            
            if title_keyword:
                title_match = title_keyword.lower() in job['title'].lower()
            
            if location_keyword:
                location_match = location_keyword.lower() in job['location'].lower()
            
            if title_match and location_match:
                filtered_jobs.append(job)
                
        # Apply limit to filtered results if specified
        if limit:
            filtered_jobs = filtered_jobs[:limit]
                
        return filtered_jobs

    def display_jobs(self, jobs=None, show_description=True, display_limit=None):
        jobs_to_display = jobs if jobs is not None else self.job_data
        
        # Apply display limit if specified
        if display_limit:
            jobs_to_display = jobs_to_display[:display_limit]
        
        if not jobs_to_display:
            print("No jobs found matching your criteria.")
            return
            
        print(f"Displaying {len(jobs_to_display)} job(s):")
        for i, job in enumerate(jobs_to_display, 1):
            print(f"\n--- Job {i} ---")
            print(f"Title: {job['title']}")
            print(f"Company: {job['company']}")
            print(f"Location: {job['location']}")
            print(f"Link: {job['link']}")
            if show_description and job['description'] != "N/A":
                print(f"Description: {job['description']}")
    
    def export_to_csv(self, filename=None, jobs=None):
        """Export job data to CSV file with proper Vietnamese encoding"""
        jobs_to_export = jobs if jobs is not None else self.job_data
        
        if not jobs_to_export:
            print("No job data to export.")
            return
        
        # Generate filename if not provided
        if not filename:
            timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
            filename = f"linkedin_jobs_{timestamp}.csv"
        
        # Ensure .csv extension
        if not filename.endswith('.csv'):
            filename += '.csv'
        
        try:
            # Use UTF-8 BOM to ensure proper display in Excel
            with open(filename, 'w', newline='', encoding='utf-8-sig') as csvfile:
                fieldnames = ['title', 'company', 'location', 'link', 'description']
                writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
                
                # Write header
                writer.writeheader()
                
                # Write job data - ensure all text is properly encoded
                for job in jobs_to_export:
                    # Clean and ensure proper encoding for each field
                    clean_job = {}
                    for key, value in job.items():
                        if isinstance(value, str):
                            # Normalize Vietnamese text
                            clean_job[key] = value.encode('utf-8').decode('utf-8')
                        else:
                            clean_job[key] = value
                    writer.writerow(clean_job)
            
            print(f"Successfully exported {len(jobs_to_export)} jobs to '{filename}'")
            print(f"File saved at: {os.path.abspath(filename)}")
            print("Note: File uses UTF-8 encoding to preserve Vietnamese characters")
            
        except Exception as e:
            print(f"Error exporting to CSV: {e}")

    def export_filtered_jobs_to_csv(self, title_keyword=None, location_keyword=None, limit=None, filename=None):
        """Search and export filtered jobs to CSV"""
        filtered_jobs = self.search_jobs(title_keyword, location_keyword, limit)
        
        if not filename and (title_keyword or location_keyword):
            # Create descriptive filename based on search criteria
            timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
            name_parts = ["linkedin_jobs"]
            
            if title_keyword:
                name_parts.append(title_keyword.replace(" ", "_"))
            if location_keyword:
                name_parts.append(location_keyword.replace(" ", "_"))
            
            name_parts.append(timestamp)
            filename = "_".join(name_parts) + ".csv"
        
        self.export_to_csv(filename, filtered_jobs)
        return filtered_jobs

if __name__ == "__main__":
    linkedin = Linkedin()
    
    # Fetch jobs with full descriptions (slower but more detailed)
    print("Fetching jobs with full descriptions...")
    linkedin.fetch_job_data(keywords="data engineer", location="Vietnam", limit=100, get_full_description=True)
    linkedin.display_jobs(display_limit=100)
    
    # Export all jobs to CSV
    linkedin.export_to_csv()
    
    # Or export with custom filename
    # linkedin.export_to_csv("my_jobs.csv")
    
    # Or export filtered jobs
    # linkedin.export_filtered_jobs_to_csv(title_keyword="senior", filename="senior_jobs.csv")