import json
import requests

url = "https://random.dog/woof.json"

proxy = {
    "http":"http://disrct:ets%40bosch207@rb-proxy-ca1.bosch.com:8080",
    "https":"http://disrct:ets%40bosch207@rb-proxy-ca1.bosch.com:8080"
}

auth = requests.auth.HTTPProxyAuth("disrct", "ets@bosch207")

#autentificação do proxy
req = requests.get(url, proxies = proxy, auth=auth)

# 200 = requisição bem sucedida
if req.status_code != 200:
    raise Exception("Erro na requisição")

dados = json.loads(req.content)

url_image = dados["url"]

with open("cachorro.jpg", "wb") as image:
    req_image = requests.get(url_image, proxies = proxy, auth=auth)

    if req_image.status_code != 200:
        raise Exception("Erro na requisição")

    image.write(req_image.content)
