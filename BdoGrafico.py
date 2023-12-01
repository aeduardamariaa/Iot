import datetime 
import json
import requests
import matplotlib.pyplot as plt
import numpy as np
import matplotlib as mpl


def get_request(url, proxy, auth):
    req = requests.get(url, proxies =proxy, auth=auth)

    if req.status_code != 200:
        raise Exception('Erro de autenticação')

    return req.content


url = "https://iiot-dta-default-rtdb.firebaseio.com/iiot-dta.json"

proxy = {
    "http":"http://disrct:ets%40bosch207@rb-proxy-ca1.bosch.com:8080",
    "https":"http://disrct:ets%40bosch207@rb-proxy-ca1.bosch.com:8080"
}

auth = requests.auth.HTTPProxyAuth("disrct", "ets@bosch207")

def update_data():
    dados = json.loads(get_request(url, proxy, auth)) #carrega dados em json
    dados_len = len(dados)
    indices = np.array([int(x[-2:]) for x in dados.keys()])

    luminosity = np.full(dados_len, np.nan, dtype=np.float64)
    temp_sensor_00 = np.full(dados_len, np.nan, dtype=np.float64)
    temp_sensor_01 = np.full(dados_len, np.nan, dtype=np.float64)

    for i, j in zip(range(dados_len),indices): #não poderia ser dois FOR
        try:
            luminosity[i] = dados[f"subsys_{j:02}"]["luminosity"]
            temp_sensor_00[i] = dados[f"subsys_{j:02}"]["temperature"]["temp_sensor_00"]
            temp_sensor_01[i] = dados[f"subsys_{j:02}"]["temperature"]["temp_sensor_01"]
        except KeyError:
            pass

    luminosity_mean = np.mean(luminosity[~np.isnan(luminosity)])
    temp_sensor_00_mean = np.mean(temp_sensor_00[~np.isnan(temp_sensor_00)])
    temp_sensor_01_mean = np.mean(temp_sensor_01[~np.isnan(temp_sensor_01)])

    return luminosity_mean, temp_sensor_00_mean, temp_sensor_01_mean

fig, axs = plt.subplots(3, sharex=True, figsize=(16, 8), gridspec_kw={"hspace":0.4}) #retorna o grafico e os eixos
fig.supxlabel("Tempo")
ax_luminosity, ax_temp_sensor_00, ax_temp_sensor_01 = axs

cmap = mpl.colormaps["coolwarm"]

ax_luminosity.grid(True)
ax_luminosity.set_ylabel("Luminosidade")

ax_temp_sensor_00.grid(True)
ax_temp_sensor_00.set_ylabel("Temp sensor 0")

ax_temp_sensor_01.grid(True)
ax_temp_sensor_01.set_ylabel("Temp sensor 1")

plt.ion()
fig.show()
fig.canvas.draw()

while True:
    luminosity_mean, temp_sensor_00_mean, temp_sensor_01_mean = update_data()
    tempo_atual = datetime.datetime.now()

    #(x - media) / (maximo - minimo)
    temp_color_00 = (temp_sensor_00_mean - 30)/(35-25)
    temp_color_01 = (temp_sensor_01_mean - 30)/(35-25)

    ax_luminosity.plot(tempo_atual, luminosity_mean, linestyle='', marker='o', markersize=5, color='r')
    ax_temp_sensor_00.plot(tempo_atual, temp_sensor_00_mean, linestyle='', marker='o', markersize=5, color=cmap(temp_color_00))
    ax_temp_sensor_01.plot(tempo_atual, temp_sensor_01_mean, linestyle='', marker='o', markersize=5, color=cmap(temp_color_01))

    fig.canvas.draw()
    plt.pause(3)

# #fazendo grafico
# plt.plot(indices, luminosity, linestyle='', maker='o', markersize=5, color='r')
# plt.grid()
# plt.xlabel("Indices")
# plt.ylabel("Luminosidade")
# plt.show()

# plt.plot(indices, temp_sensor_00, linestyle='', maker='o', markersize=5, color='r')
# plt.grid()
# plt.xlabel("Indices")
# plt.ylabel("Temp sensor 0")
# plt.show()

# plt.plot(indices, temp_sensor_01, linestyle='', maker='o', markersize=5, color='r')
# plt.grid()
# plt.xlabel("Indices")
# plt.ylabel("Temp sensor 1")
# plt.show()
