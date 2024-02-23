#include <iostream>
#include <string>

using namespace std;

class ContaBancaria{
  private:
    int agencia;
    string nome;
    float saldo;
  public:
    void set_agencia(int a){
      agencia = a;
    };
    int get_agencia(){
      return agencia;
    };
    void set_nome(string n){
      nome = n;
    };
    string get_nome(){
      return nome;
    };
    float get_saldo(){
      return saldo;
    };
    void set_saldo(float n){
      saldo = n;
    };
    void depositar(float valor){
      saldo += valor;
    };
    void sacar(float valor){
      if(valor <= saldo){
        cout<< "Saque realizado com sucesso!"<<endl;
        saldo-=valor;
      }else{
        cout<< "Saldo insuficiente!"<<endl;
        return;
      };
    };
};

void preencher(ContaBancaria* conta) {
    int aux;
    string aux1;

    cout << "Digite a agencia: " << endl;
    cin >> aux;
    conta->set_agencia(aux);

    cout << "Digite o nome: " << endl;
    cin >> aux1;
    conta->set_nome(aux1);
}

void menu(){
  cout<<"1 - Depositar"<<endl;
  cout<<"2 - Sacar"<<endl;
  cout<<"3 - Saldo"<<endl;
  cout<<"4 - Sair"<<endl;
}

int main(){
  ContaBancaria conta;
  preencher(&conta);

  int escolha;

  do {
    menu();
    cout << "Escolha uma opção: ";
    cin >> escolha;

    switch (escolha) {
      case 1:
        // Depositar
        float valor;
        cout << "Digite o valor a ser depositado: ";
        cin >> valor;
        conta.depositar(valor);
        break;
      case 2:
        // Sacar
        cout << "Digite o valor a ser sacado: ";
        cin >> valor;
        conta.sacar(valor);
        break;
      case 3:
        // Saldo
        cout << "Saldo atual: " << conta.get_saldo() << endl;
        break;
      case 4:
        // Sair
        cout << "Saindo do programa." << endl;
        break;
      default:
        cout << "Opção inválida. Tente novamente." << endl;
    }
  } while (escolha != 4);

  return 0;
}
