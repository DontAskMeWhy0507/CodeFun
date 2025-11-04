import requests
from bs4 import BeautifulSoup
import json
import re

## Scrape movie data from Rophim.mx

# Get the movie listing page
response = requests.get("https://www.rophim.mx/phimhay")
soup = BeautifulSoup(response.text, "html.parser")

# Save HTML for inspection
with open("phimhay_page.html", "w", encoding="utf-8") as f:
    f.write(response.text)

## Export to html file
with open("rophim.html", "w", encoding="utf-8") as f:
    f.write(response.text)


# Initialize organized data structure
organized_data = {
    "movies": [],
    "site_info": {
        "name": "RoPhim",
        "url": "https://www.rophim.mx",
        "description": "Phim hay cả rổ - Xem phim HD online miễn phí"
    }
}

# Find all movie thumbnails with class "v-thumbnail" or any anchor with /phim/ in href
movie_links = soup.find_all("a", class_="v-thumbnail")

# If no v-thumbnail found, try alternative patterns
if not movie_links:
    print("No v-thumbnail found, trying alternative patterns...")
    movie_links = soup.find_all("a", href=re.compile(r"/phim/"))
    
print(f"Found {len(movie_links)} movie links")

for movie_link in movie_links:
    movie_data = {}
    
    # Get movie link and ID
    href = movie_link.get("href", "")
    movie_data["link"] = href
    movie_data["full_url"] = f"https://www.rophim.mx{href}" if href.startswith("/") else href
    
    # Extract movie slug from URL (e.g., "thu-thach-than-tuong.4FmPc8om")
    if href:
        slug = href.split("/")[-1]
        movie_data["slug"] = slug
    
    # Get image (poster)
    img = movie_link.find("img")
    if img:
        movie_data["poster"] = img.get("src", "")
        movie_data["title"] = img.get("alt", "").replace("Xem Phim ", "").replace(" Vietsub HD Online - Rophim", "")
    
    # Get episode count (pin-new)
    pin_new = movie_link.find("div", class_="pin-new")
    if pin_new:
        episode_count = pin_new.find("strong")
        if episode_count:
            movie_data["episodes"] = episode_count.get_text(strip=True)
    
    # Add to list if we have at least a title
    if movie_data.get("title"):
        organized_data["movies"].append(movie_data)

organized_data["total_movies"] = len(organized_data["movies"])

# Extract meta information
meta_description = soup.find("meta", {"name": "description"})
if meta_description:
    organized_data["site_info"]["description"] = meta_description.get("content", "")

# Try to find movie/content data in script tags
scripts = soup.find_all("script")
for script in scripts:
    script_content = script.string
    if script_content:
        # Look for movie data patterns in __next_f.push or other JSON structures
        if "self.__next_f.push" in script_content:
            matches = re.findall(r'self\.__next_f\.push\((\[.*?\])\)', script_content, re.DOTALL)
            for match in matches:
                try:
                    data = json.loads(match)
                    # Check if this contains movie information
                    if isinstance(data, list) and len(data) > 1:
                        # Try to extract useful information
                        content = str(data)
                        # Look for potential movie titles, links, etc.
                        if any(keyword in content for keyword in ["phim", "movie", "title", "href"]):
                            organized_data["movies"].append({
                                "raw_data": data,
                                "type": "next_data"
                            })
                except json.JSONDecodeError:
                    pass

# Look for links to movies
movie_links = []
for link in soup.find_all("a", href=True):
    href = link.get("href", "")
    title = link.get_text(strip=True)
    
    # Filter for movie-like links
    if href and title and not href.startswith("#"):
        # Avoid common navigation links
        if href.startswith("/") and title not in ["Hỏi-Đáp", "Chính sách bảo mật", "Điều khoản sử dụng", "Giới thiệu", "Liên hệ"]:
            movie_links.append({
                "title": title,
                "link": href,
                "full_url": f"https://www.rophim.mx{href}" if href.startswith("/") else href
            })

if movie_links:
    organized_data["discovered_links"] = movie_links

# Extract structured content from the page
# Look for movie cards, sections, etc.
movie_sections = soup.find_all("div", class_=re.compile(r"movie|film|card|item"))
for section in movie_sections:
    movie_info = {}
    
    # Try to find title
    title_elem = section.find(["h1", "h2", "h3", "h4", "a"])
    if title_elem:
        movie_info["title"] = title_elem.get_text(strip=True)
    
    # Try to find link
    link_elem = section.find("a", href=True)
    if link_elem:
        movie_info["link"] = link_elem.get("href")
    
    # Try to find image
    img_elem = section.find("img")
    if img_elem:
        movie_info["image"] = img_elem.get("src") or img_elem.get("data-src")
    
    # Try to find description
    desc_elem = section.find("p")
    if desc_elem:
        movie_info["description"] = desc_elem.get_text(strip=True)
    
    if movie_info:
        organized_data["movies"].append(movie_info)

# Save organized data
with open("extracted_data.json", "w", encoding="utf-8") as f:
    json.dump(organized_data, f, ensure_ascii=False, indent=2)

print(f"\n✅ Extracted {organized_data['total_movies']} movies from RoPhim")
print(f"📁 Saved to extracted_data.json")

# Print first 3 movies as sample
if organized_data["movies"]:
    print(f"\n📽️  Sample movies:")
    for i, movie in enumerate(organized_data["movies"][:3], 1):
        print(f"\n{i}. {movie.get('title', 'N/A')}")
        print(f"   URL: {movie.get('full_url', 'N/A')}")
        print(f"   Episodes: {movie.get('episodes', 'N/A')}")
        print(f"   Poster: {movie.get('poster', 'N/A')[:60]}...")
         
