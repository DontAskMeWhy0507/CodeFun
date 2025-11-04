import requests
from bs4 import BeautifulSoup
import json
import re

class RoPhimScraper:
    def __init__(self):
        self.base_url = "https://www.rophim.mx"
        self.headers = {
            "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36"
        }
        
    def get_movie_list(self, page_url="/phimhay"):
        """Get list of movies from a page"""
        url = f"{self.base_url}{page_url}"
        print(f"Fetching: {url}")
        
        response = requests.get(url, headers=self.headers)
        soup = BeautifulSoup(response.text, "html.parser")
        
        movies = []
        
        # Look for movie cards/items
        # Common patterns: film-item, movie-item, card, etc.
        movie_cards = soup.find_all(["div", "article"], class_=re.compile(r"film|movie|item|card|post"))
        
        for card in movie_cards:
            movie_info = {}
            
            # Find title
            title_elem = card.find(["h2", "h3", "h4", "a"], class_=re.compile(r"title|name"))
            if not title_elem:
                title_elem = card.find("a", title=True)
            if title_elem:
                movie_info["title"] = title_elem.get("title") or title_elem.get_text(strip=True)
            
            # Find link
            link_elem = card.find("a", href=True)
            if link_elem:
                href = link_elem.get("href")
                movie_info["link"] = href
                movie_info["full_url"] = f"{self.base_url}{href}" if href.startswith("/") else href
            
            # Find image/poster
            img_elem = card.find("img")
            if img_elem:
                movie_info["poster"] = img_elem.get("src") or img_elem.get("data-src") or img_elem.get("data-original")
                movie_info["poster_alt"] = img_elem.get("alt", "")
            
            # Find description
            desc_elem = card.find(["p", "div"], class_=re.compile(r"desc|summary|synopsis"))
            if desc_elem:
                movie_info["description"] = desc_elem.get_text(strip=True)
            
            # Find quality/year/type
            quality_elem = card.find(class_=re.compile(r"quality|badge|label"))
            if quality_elem:
                movie_info["quality"] = quality_elem.get_text(strip=True)
            
            # Find year
            year_elem = card.find(class_=re.compile(r"year|date"))
            if year_elem:
                movie_info["year"] = year_elem.get_text(strip=True)
            
            if movie_info:
                movies.append(movie_info)
        
        return movies
    
    def get_movie_detail(self, movie_url):
        """Get detailed information about a specific movie"""
        if not movie_url.startswith("http"):
            movie_url = f"{self.base_url}{movie_url}"
        
        print(f"Fetching movie detail: {movie_url}")
        
        response = requests.get(movie_url, headers=self.headers)
        soup = BeautifulSoup(response.text, "html.parser")
        
        movie_detail = {
            "url": movie_url
        }
        
        # Title
        title_elem = soup.find(["h1", "h2"], class_=re.compile(r"title|name|heading"))
        if title_elem:
            movie_detail["title"] = title_elem.get_text(strip=True)
        
        # Description
        desc_elem = soup.find(["div", "p"], class_=re.compile(r"description|content|synopsis|plot"))
        if desc_elem:
            movie_detail["description"] = desc_elem.get_text(strip=True)
        
        # Find stream links/iframe
        iframes = soup.find_all("iframe")
        stream_links = []
        for iframe in iframes:
            src = iframe.get("src") or iframe.get("data-src")
            if src:
                stream_links.append(src)
        
        if stream_links:
            movie_detail["stream_links"] = stream_links
        
        # Find video sources
        video_tags = soup.find_all("video")
        video_sources = []
        for video in video_tags:
            sources = video.find_all("source")
            for source in sources:
                src = source.get("src")
                if src:
                    video_sources.append({
                        "url": src,
                        "type": source.get("type", "unknown"),
                        "quality": source.get("label", "unknown")
                    })
        
        if video_sources:
            movie_detail["video_sources"] = video_sources
        
        # Find additional info
        info_elem = soup.find(class_=re.compile(r"info|meta|detail"))
        if info_elem:
            movie_detail["additional_info"] = info_elem.get_text(strip=True)
        
        return movie_detail


# Main execution
if __name__ == "__main__":
    scraper = RoPhimScraper()
    
    # Get movie list
    movies = scraper.get_movie_list("/phimhay")
    
    organized_data = {
        "total_movies": len(movies),
        "movies": movies[:10],  # Get first 10 movies
        "site_info": {
            "name": "RoPhim",
            "base_url": "https://www.rophim.mx"
        }
    }
    
    # If you want to get detailed info for the first movie (uncomment below):
    # if movies:
    #     first_movie_detail = scraper.get_movie_detail(movies[0]["link"])
    #     organized_data["sample_movie_detail"] = first_movie_detail
    
    # Save to JSON
    with open("rophim_movies.json", "w", encoding="utf-8") as f:
        json.dump(organized_data, f, ensure_ascii=False, indent=2)
    
    print(f"\n✅ Scraped {len(movies)} movies")
    print(f"📁 Saved to rophim_movies.json")
    
    # Print sample
    if movies:
        print(f"\n📽️  Sample movie:")
        print(f"   Title: {movies[0].get('title', 'N/A')}")
        print(f"   Link: {movies[0].get('full_url', 'N/A')}")
        print(f"   Poster: {movies[0].get('poster', 'N/A')}")
