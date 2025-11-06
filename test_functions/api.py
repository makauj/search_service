# code that pulls data from an API and processes it
# use python3 api.py to run the program

import requests
import json
import logging
from typing import List, Dict, Any
import time

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)
API_URL = "https://serpapi.com/search.json?engine=google_jobs&q=barista+new+york&hl=en"

def fetch_job_data(api_url: str) -> Dict[str, Any]:
    """Fetch job data from the given API URL."""
    try:
        response = requests.get(api_url)
        response.raise_for_status()
        logger.info("Data fetched successfully from API.")
        return response.json()
    except requests.RequestException as e:
        logger.error(f"Error fetching data from API: {e}")
        return {}


def process_job_data(data: Dict[str, Any]) -> List[Dict[str, Any]]:
    """Process the job data and extract relevant fields."""
    jobs = []
    for job in data.get("jobs_results", []):
        processed_job = {
            "title": job.get("title"),
            "company": job.get("company_name"),
            "location": job.get("location"),
            "date_posted": job.get("date"),
            "description": job.get("description"),
            "url": job.get("link"),
        }
        jobs.append(processed_job)
    logger.info(f"Processed {len(jobs)} job listings.")
    return jobs


def save_jobs_to_file(jobs: List[Dict[str, Any]], filename: str) -> None:
    """Save the processed job data to a JSON file."""
    try:
        with open(filename, 'w') as f:
            json.dump(jobs, f, indent=4)
        logger.info(f"Job data saved to {filename}.")
    except IOError as e:
        logger.error(f"Error saving data to file: {e}")


def main():
    """Main function to fetch, process, and save job data."""
    data = fetch_job_data(API_URL)
    if data:
        jobs = process_job_data(data)
        save_jobs_to_file(jobs, "job_listings.json")


if __name__ == "__main__":
    main()
