from bluetoothConnection import BluetoothConnection
from play_sound import DrumKit

BLUETOOTH_ADDRESS = 'E0:5A:1B:C7:FF:56'
btconn = BluetoothConnection(BLUETOOTH_ADDRESS, 1, 1)
btconn.connect()
print(btconn.connection())

listaa = []

new_drum = DrumKit()

while(1):

    noteESP = list(btconn.getPressedFromBT())[0]

    new_drum.button_chimbal = noteESP[0]
    new_drum.button_bumbo = noteESP[1]

    new_drum.detect_and_play()