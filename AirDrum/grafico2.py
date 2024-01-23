import numpy as np
import matplotlib.pyplot as plt
from matplotlib.lines import Line2D
from itertools import count
from matplotlib.animation import FuncAnimation

# Inicializa os dados
botao1_data = []
botao2_data = []
tempo_data = []
index = count()

# Função para receber os dados dos botões a cada 10 segundos
def recebe_dados():
    # Substitua esta função pela lógica de leitura dos seus botões
    return [np.random.choice([0, 1]), np.random.choice([0, 1])]

# Função de animação para atualizar o gráfico
def update(frame):
    botao1, botao2 = recebe_dados()

    # Adiciona os dados aos vetores
    botao1_data.append(botao1)
    botao2_data.append(botao2)
    tempo_data.append(next(index) * 10)

    # Atualiza o gráfico
    line1.set_data(tempo_data, botao1_data)
    line2.set_data(tempo_data, botao2_data)

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
line1, = ax.plot([], [], 'b-', label='Botão 1 (Azul)')
line2, = ax.plot([], [], 'r-', label='Botão 2 (Vermelho)')

# Adiciona legendas e rótulos
ax.set_xlabel('Tempo (s)')
ax.set_ylabel('Estado do Botão')
ax.set_title('Histórico dos Estados dos Botões')
ax.legend(loc='upper left', bbox_to_anchor=(1, 1))

# Configuração da animação
ani = FuncAnimation(fig, update, frames=range(100), interval=10000, repeat=False)

# Exibe o gráfico
plt.show()
