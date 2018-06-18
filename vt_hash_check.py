import requests

# add in your api key

def lookup_hash(hash):
    report_url = 'https://www.virustotal.com/vtapi/v2/file/report'
    params = {'apikey': 'apikey', 'resource': hash}
    
    status = requests.get(report_url, params=params).json()
    
    if status["response_code"] == 1:
        return status["positives"]
    else:
        return 0
