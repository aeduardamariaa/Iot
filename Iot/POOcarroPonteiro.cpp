#include <iostream>
#include <string>

using namespace std;

class Carro {
private:
    string cor;
    string motor;
    int rodas;

public:
    void barulho() {
        cout << "Biiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii" << endl;
    }

    void set_rodas(int r) {
        if (r < 4) {
            cout << "Não é um carro" << endl;
            rodas = -1;
        } else {
            rodas = r;
        }
    }

    void set_cor(const string& c) {
        cor = c;
    }

    void set_motor(const string& m) {
        motor = m;
    }

    string get_cor() const {
        return cor;
    }

    string get_motor() const {
        return motor;
    }

    int get_rodas() const {
        return rodas;
    }

    void exibir() const {
        cout << "Cor: " << cor << endl << "Motor: " << motor << endl << "Rodas: " << rodas << endl;
    }
};

void preencher(Carro* c1) {
    string aux;
    int aux1 = 0;

    cout << "Digite a cor do carro: " << endl;
    cin >> aux;
    c1->set_cor(aux);

    cout << "Digite o motor do carro: " << endl;
    cin >> aux;
    c1->set_motor(aux);

    cout << "Digite o número de rodas do carro: " << endl;
    cin >> aux1;
    c1->set_rodas(aux1);
}

int main() {
    Carro c1;  // Criando um objeto Carro
    preencher(&c1);

    c1.exibir();
    c1.barulho();

    return 0;
}
