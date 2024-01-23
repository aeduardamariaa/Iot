import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# Inicializando os vetores de dados
historico_botao1 = []
historico_botao2 = []

# Função para atualizar o gráfico em cada frame
def update(frame):
    # Simulando dados de entrada [botao1, botao2]
    botao1 = np.random.randint(0, 2)
    botao2 = np.random.randint(0, 2)

    # Adicionando dados aos históricos
    historico_botao1.append(botao1)
    historico_botao2.append(botao2)

    # Plotando o gráfico
    plt.cla()  # Limpa o eixo para não sobrepor dados antigos
    plt.plot(historico_botao1, label='Botão 1 (Azul)', color='blue')
    plt.plot(historico_botao2, label='Botão 2 (Vermelho)', color='red')

    # Adicionando rótulos e legenda
    plt.title('Histórico dos Botões')
    plt.xlabel('Tempo (s)')
    plt.ylabel('Estado do Botão')
    plt.legend()

# Configurando o gráfico
fig, ax = plt.subplots()
ani = FuncAnimation(fig, update, interval=10000)  # Atualiza a cada 1 segundo

# Exibindo o gráfico
plt.show()
