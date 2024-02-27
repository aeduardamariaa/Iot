#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class Binario {
private:
    string bi;

public:
    Binario(string bi) {
        this->bi = bi;
    }

    void print() {
        int result = 0;
        for (int i = bi.size() - 1; i >= 0; i--) {
            if (bi[i] == '1') {
                result += pow(2, (bi.size() - 1 - i));
            }
        }
        cout << "Valor decimal: " << result << endl;
    }
};

int main() {
    string bi;

    cout << "Insira um número binário: " << endl;
    cin >> bi;
    Binario b1(bi);

    b1.print();

    return 0;
}
