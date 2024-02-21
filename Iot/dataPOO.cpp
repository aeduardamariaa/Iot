#include <iostream>
#include <string>

using namespace std;

class Data{
  private:
    int dia;
    int mes;
    int ano;
  public:
    void get_data(int d, int m, int a){
      cout<<d<<"/"<<m<<"/"<<a<<endl;
    };
    int get_dia(){
      return dia;
    };
    int get_mes(){
      return mes;
    };
    int get_ano(){
      return ano;
    };
    void set_dia(int d){
      if(d>0 && d<=31){
        dia = d;
      }else{
        cout<<"Dia inválido"<<endl;
      };
    };
    void set_mes(int m){
      if(m>0 && m<=12){
        mes = m;
      }else{
        cout<<"Mês inválido"<<endl;
      };
    };
    void set_ano(int a){
      ano = a;
    };
};

void preencher(Data* data) {
    int aux;

    cout << "Digite o dia: " << endl;
    cin >> aux;
    data->set_dia(aux);

    cout << "Digite o mes: " << endl;
    cin >> aux;
    data->set_mes(aux);


    cout << "Digite o ano: " << endl;
    cin >> aux;
    data->set_ano(aux);
}

int main(){
  Data data;

  preencher(&data);

  data.get_data(data.get_dia(), data.get_mes(), data.get_ano());

  return 0;
}
