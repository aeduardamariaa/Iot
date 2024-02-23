#include <iostream>
#include <vector>

using namespace std;

class Binario {
  private:
      int num;
      vector<unsigned char> bi;
  
  public:
      Binario(int num) {
          this->num = num;
          bi = decimalParaBinario(num);
      }
  
      void set_num(int num) {
          this->num = num;
          bi = decimalParaBinario(num);
      }
  
      void print() {
          cout << "Binario: ";
  
          for (int i = 0; i < bi.size(); i++) {
              cout << static_cast<int>(bi[i]);
          }
          cout << endl;
      }

      vector<unsigned char> decimalParaBinario(int decimal) {
          vector<unsigned char> binario;

          while (decimal > 0) {
              binario.push_back(static_cast<unsigned char>(decimal % 2));
              decimal /= 2;
          }

          for (int i = 0, j = binario.size() - 1; i < j; i++, j--) {
              int temp = binario[i];
              binario[i] = binario[j];
              binario[j] = temp;
          }

          return binario;
      }
};

int main() {
    int num;

    cout << "Insira um número decimal: " << endl;
    cin >> num;
    Binario b1(num);

    b1.print();

    return 0;
}
