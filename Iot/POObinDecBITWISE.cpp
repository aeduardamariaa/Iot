#include <iostream>
#include <vector>

using namespace std;

class Binario {
private:
    int num;

public:
    Binario(int num) {
        this->num = num;
    }

    void print() {
        for (int i = 7; i >= 0; i--) {
            cout << ((num >> i) & 1);
        }
        cout << endl;
    }

    void imparPar() {
        string result = ((num>>0 & 1) == 0) ? "Par" : "Impar";
        cout << "O número é: " << result << endl;
    }
};

int main() {
    int num;

    cout << "Insira um número decimal: " << endl;
    cin >> num;
    Binario b1(num);

    b1.print();
    b1.imparPar();

    return 0;
}
