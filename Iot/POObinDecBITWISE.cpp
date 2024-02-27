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
          for(int i=7;i>-1;i--){
            cout<<((num>>i)&1);
          }
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
