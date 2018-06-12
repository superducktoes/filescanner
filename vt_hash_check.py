import requests

# add in your api key

def lookup_hash(hash):
    report_url = 'https://www.virustotal.com/vtapi/v2/file/report'
    params = {'apikey': '242b0e436157242a793c643460ab6830abf05411b6f84a718040edb25c57100e', 'resource': hash}
    
    status = requests.get(report_url, params=params).json()
    
    if status["response_code"] == 1:
        return status["positives"]
    else:
        return 0
