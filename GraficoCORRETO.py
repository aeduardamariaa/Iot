from bluetoothConnection import BluetoothConnection
from play_sound import DrumKit
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.lines import Line2D
from itertools import count
from matplotlib.animation import FuncAnimation

BLUETOOTH_ADDRESS = 'E0:5A:1B:C7:FF:56'
btconn = BluetoothConnection(BLUETOOTH_ADDRESS, 1, 1)
btconn.connect()
print(btconn.connection())

listaa = []

new_drum = DrumKit()

# Inicializa os dados
botao1_data = []
botao2_data = []
tempo_data = []
index = count()

# Função de animação para atualizar o gráfico
def update(frame):
    # Obtém os dados do Bluetooth
    noteESP = list(btconn.getPressedFromBT())[0]
    noteESP2 = list(btconn.getPressedFromBT())[0]

    # Adiciona os dados aos vetores
    botao1_data.append(noteESP)
    botao2_data.append(noteESP2)
    tempo_data.append(next(index) * 10)

    # Configuração inicial do gráfico se ainda não estiver configurado
    if not hasattr(update, "line1"):
        update.line1, = ax.plot([], [], 'b-', label='Botão 1 (Azul)')
        update.line2, = ax.plot([], [], 'r-', label='Botão 2 (Vermelho)')

    # Atualiza o gráfico
    update.line1.set_data(tempo_data, botao1_data)
    update.line2.set_data(tempo_data, botao2_data)

    # Ajusta os limites do gráfico
    ax.relim()
    ax.autoscale_view()

    # Atualiza as legendas
    legend = ax.legend(loc='upper left', bbox_to_anchor=(1, 1))
    legend.get_lines()[0].set_linestyle('-')
    legend.get_lines()[1].set_linestyle('-')
    legend.get_lines()[0].set_marker('')
    legend.get_lines()[1].set_marker('')

# Configuração inicial do gráfico
fig, ax = plt.subplots()

# Adiciona legendas e rótulos
ax.set_xlabel('Tempo (s)')
ax.set_ylabel('Estado do Botão')
ax.set_title('Histórico dos Estados dos Botões')
ax.legend(loc='upper left', bbox_to_anchor=(1, 1))

# Configuração da animação
ani = FuncAnimation(fig, update, frames=range(100), interval=10000, repeat=False)

# Exibe o gráfico
plt.show()
