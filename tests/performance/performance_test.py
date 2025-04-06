import requests
from concurrent.futures import ThreadPoolExecutor
import time

BASE_URL = "http://localhost:8080"
USER_ID = 3
NUM_REQUESTS = 100
MAX_WORKERS = 20

def make_deposit():
    try:
        r = requests.post(f"{BASE_URL}/deposit", json={"userId": USER_ID, "amount": 10})
        return r.status_code
    except Exception:
        return 500

def make_withdraw():
    try:
        r = requests.post(f"{BASE_URL}/withdraw", json={"userId": USER_ID, "amount": 5})
        return r.status_code
    except Exception:
        return 500

if __name__ == "__main__":
    print("🚀 Starting performance test...")

    start = time.time()
    with ThreadPoolExecutor(max_workers=MAX_WORKERS) as executor:
        # Alternate deposits and withdrawals
        futures = []
        for i in range(NUM_REQUESTS):
            if i % 2 == 0:
                futures.append(executor.submit(make_deposit))
            else:
                futures.append(executor.submit(make_withdraw))

        statuses = [f.result() for f in futures]

    end = time.time()
    success = statuses.count(200)
    failed = len(statuses) - success

    print(f"\n✅ Success: {success}")
    print(f"❌ Failed: {failed}")
    print(f"⏱️ Time Taken: {round(end - start, 2)} seconds")
    print("📈 Requests per second:", round(NUM_REQUESTS / (end - start), 2))
