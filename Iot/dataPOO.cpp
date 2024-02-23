#include <iostream>
#include <string>

using namespace std;

int bi = 0;

class Data {
private:
    int dia=0;
    int mes=0;
    int ano=0;

public:
    void get_data() {
        cout << dia << "/" << mes << "/" << ano << endl;
    }

    int get_dia() {
        return dia;
    }

    int get_mes() {
        return mes;
    }

    int get_ano() {
        return ano;
    }

    void set_dia(int d) {
        if ((bi == 1 && d > 0 && d <= 29) || (bi == 0 && d > 0 && d <= 31)) {
            dia = d;
        } else {
            cout << "Dia inválido" << endl;
        }
    }

    void set_mes(int m) {
        if (m > 0 && m <= 12) {
            mes = m;
        } else {
            cout << "Mês inválido" << endl;
        }
    }

    void set_ano(int a) {
        ano = a;
    }
};

bool ehBissexto(int ano) {
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
        bi = 1;
        return true;
    } else {
        bi = 0;
        return false;
    }
}

void preencher(Data* data) {
    int aux;

    cout << "Digite o ano: " << endl;
    cin >> aux;
    bi = ehBissexto(aux);
    data->set_ano(aux);

    cout << "Digite o mes: " << endl;
    cin >> aux;
    data->set_mes(aux);

    cout << "Digite o dia: " << endl;
    cin >> aux;
    data->set_dia(aux);
}

int main() {
    Data data;

    preencher(&data);

    data.get_data();

    return 0;
}
