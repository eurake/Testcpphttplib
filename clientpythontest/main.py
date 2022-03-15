#coding=utf-8
import requests

fs = {'imgFile': open('../image/GreatWall.jpg', 'rb')}
url = "http://127.0.0.1:12345/api/v1/uploadFile"
r = requests.request('POST', url, files=fs)
print(r.status_code)
print(r.content)

fs = {'imgFile': open('../image/Shanghai.jpg', 'rb')}
url = "http://127.0.0.1:12345/api/v1/uploadFile"
r = requests.request('POST', url, files=fs)
print(r.status_code)
print(r.content)
fs = {'imgFile': open('../image/长城.jpg', 'rb')}
url = "http://127.0.0.1:12345/api/v1/uploadFile"
r = requests.request('POST', url, files=fs)
print(r.status_code)
print(r.content)

fs = {'imgFile': open('../image/上海.jpg', 'rb')}
url = "http://127.0.0.1:12345/api/v1/uploadFile"
r = requests.request('POST', url, files=fs)
print(r.status_code)
print(r.content)
