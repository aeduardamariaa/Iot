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


url = "https://iiot-dta-default-rtdb.firebaseio.com/challenge02.json"

proxy = {
    "http":"http://disrct:ets%40bosch207@rb-proxy-ca1.bosch.com:8080",
    "https":"http://disrct:ets%40bosch207@rb-proxy-ca1.bosch.com:8080"
}

auth = requests.auth.HTTPProxyAuth("disrct", "ets@bosch207")

def update_data():
    dados = json.loads(get_request(url, proxy, auth)) #carrega dados em json
    dados_len = len(dados)
    indices = np.array([int(x[-2:]) for x in dados.keys()])

    temperature = np.full(dados_len, np.nan, dtype=np.float64)
    humidity = np.full(dados_len, np.nan, dtype=np.float64)
    #temp_sensor_01 = np.full(dados_len, np.nan, dtype=np.float64)

    for i, j in zip(range(dados_len),indices): #não poderia ser dois FOR
        try:
            temperature[i] = dados[f"subsys_{j:02}"]["temperature"]
            humidity[i] = dados[f"subsys_{j:02}"]["humidity"]
            # temp_sensor_01[i] = dados[f"subsys_{j:02}"]["temperature"]["temp_sensor_01"]
        except KeyError:
            pass

    temperature_mean = np.mean(temperature[~np.isnan(temperature)])
    humidity_mean = np.mean(humidity[~np.isnan(humidity)])
    # temp_sensor_01_mean = np.mean(temp_sensor_01[~np.isnan(temp_sensor_01)])

    return temperature_mean, humidity_mean

fig, axs = plt.subplots(2, sharex=True, figsize=(16, 8), gridspec_kw={"hspace":0.4}) #retorna o grafico e os eixos
fig.supxlabel("Tempo")
ax_temperature, ax_humidity = axs

cmap = mpl.colormaps["coolwarm"]

ax_temperature.grid(True)
ax_temperature.set_ylabel("TEMPERATURAAAAAAAAAA")

ax_humidity.grid(True)
ax_humidity.set_ylabel("HUMIDADEEEEEEEEEEEEE")

# ax_temp_sensor_01.grid(True)
# ax_temp_sensor_01.set_ylabel("Temp sensor 1")

plt.ion()
fig.show()
fig.canvas.draw()

while True:
    temperature_mean, humidity_mean = update_data()
    tempo_atual = datetime.datetime.now()

    #(x - media) / (maximo - minimo)
    temp_color_00 = (temperature_mean - 30)/(35-25)
    # temp_color_01 = (temp_sensor_01_mean - 30)/(35-25)

    ax_temperature.plot(tempo_atual, temperature_mean, linestyle='', marker='o', markersize=5, color='r')
    ax_humidity.plot(tempo_atual, humidity_mean, linestyle='', marker='o', markersize=5, color=cmap(temp_color_00))
    # ax_temp_sensor_01.plot(tempo_atual, temp_sensor_01_mean, linestyle='', marker='o', markersize=5, color=cmap(temp_color_01))

    fig.canvas.draw()
    plt.pause(3)
