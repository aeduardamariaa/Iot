#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

class Carro{
  private:
    string cor;
    string motor;
    int rodas;
  public:
    Carro(){
      
    }// para criar obj sem nada 
    Carro(string cor, string motor, int rodas){
      this->cor = cor;
      this->motor = motor;
      this->rodas = rodas;
    }
    void barulho(){
      cout<<"Biiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii"<<endl;
    };
    void set_rodas(int r){
      if(r<4){
        cout<<"Não é um carro"<<endl;
        rodas = -1;
      }
      else{
        rodas = r;
      };
    };
    void set_cor(string c){
      cor = c;
    };
    void set_motor(string m){
      motor = m;
    };
    string get_cor(){
      return cor;
    };
    string get_motor(){
      return motor;
    };
    int get_rodas(){
      return rodas;
    };
    void exibir(){
      cout<<"Cor: "<<cor<<endl<<"Motor: "<<motor<<endl<<"Rodas: "<<rodas<<endl;
    };
};

Carro preencher(Carro c1){
  string aux;
  int aux1=0;
  
  cout<<"Digite a cor do carro: "<<endl;
  cin>>aux;
  c1.set_cor(aux);

  cout<<"Digite o motor do carro: "<<endl;
  cin>>aux;
  c1.set_motor(aux);

  cout<<"Digite o rodas do carro: "<<endl;
  cin>>aux1;
  c1.set_rodas(aux1);

  return c1;
};

int main(){
  Carro c1;

  Carro auxc = preencher(c1);

  auxc.exibir();
  auxc.barulho();
  
  return 0;
}
