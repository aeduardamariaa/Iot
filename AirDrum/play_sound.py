import pygame

class Data:
    def __init__(self, x: float, y: float, z: float) -> None:
        self.x = x
        self.y = y
        self.z = z

class DrumKit:
    def __init__(self):
        self.position = Data(0.0, 0.0, 0.0)
        self.button_chimbal = 0
        self.button_bumbo = 0

    def change_position(self, new_position: list[float]):
        self.position = Data(new_position[0], new_position[1], new_position[2])

    def change_button(self, new_button: list[int]):
        self.button_chimbal = new_button[0]
        self.button_bumbo = new_button[1]

    def play_audio(self, address):
        pygame.mixer.init()
        pygame.mixer.music.load(address)
        pygame.mixer.music.play()

        while pygame.mixer.music.get_busy():
            pygame.time.Clock().tick(10)

        pygame.mixer.quit()

    def play_sound(self, sound_type):
        if sound_type == "HIGH":
            address = "./audio/high_tom.wav"
        elif sound_type == "CAIXA":
            address = "./audio/caixa.wav"
        elif sound_type == "LOW":
            address = "./audio/low_tom.wav"
        elif sound_type == "SURDO":
            address = "./audio/surdo.wav"
        elif sound_type == "ATAQUE":
            address = "./audio/prato_de_ataque.wav"
        elif sound_type == "CONDUÇÃO":
            address = "./audio/prato_de_conducao.wav"
        elif sound_type == "CHIMBAL":
            address = "./audio/chimbal.wav"
        elif sound_type == "BUMBO":
            address = "./audio/bumbo.wav"
        else:
            return

        print(sound_type)
        self.play_audio(address)

    def detect_and_play(self):
        # if 0.2 <= self.position.x <= 0.45 and 0.1 <= self.position.y <= 0.35 and self.position.z <= 0:
        #     self.play_sound("HIGH")
        if self.position.z < 0:
            self.play_sound("CAIXA")
        # if 0.2 <= self.position.x <= 0.45 and -0.1 <= self.position.y <= -0.35 and self.position.z <= 0:
        #     self.play_sound("LOW")
        # if 0.1 <= self.position.x <= 0.35 and -0.4 <= self.position.y <= -0.65 and self.position.z < 0:
        #     self.play_sound("SURDO")
        # if 0.4 < self.position.x <= 0.65 and 0.5 <= self.position.y <= 0.75 and self.position.z < 0:
        #     self.play_sound("ATAQUE")
        # if 0.4 < self.position.x <= 0.65 and -0.5 >= self.position.y >= -0.75 and self.position.z < 0:
        #     self.play_sound("CONDUÇÃO")
        if self.button_chimbal:
            self.play_sound("CHIMBAL")
        if self.button_bumbo:
            self.play_sound("BUMBO")

if __name__ == "__main__":

    drum_kit = DrumKit()
    drum_kit.detect_and_play()