#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

float media(float n1, float n2, float n3)
{
  return (n1 + n2 + n3) / 3;
}

void recebe_dados(float &n1, float &n2, float &n3)
{
  cout << "Digite três notas, respectivamente: ";
  cin >> n1;
  cin >> n2;
  cin >> n3;
}

int main()
{
  float nota1, nota2, nota3;

  recebe_dados(nota1, nota2, nota3);

  cout << "A média das notas é: " << media(nota1, nota2, nota3) << endl;

  return 0;
}
////////////////////////////////////////////////////////////////////////////

float media(float* n1, float* n2, float* n3)
{
  return (*n1 + *n2 + *n3) / 3;
}

void recebe_dados(float* n1, float* n2, float* n3)
{
  cout << "Digite três notas, respectivamente: ";
  cin >> *n1;
  cin >> *n2;
  cin >> *n3;
}

int main()
{
  float nota1, nota2, nota3;

  float* ptr_nota1 = &nota1;
  float* ptr_nota2 = &nota2;
  float* ptr_nota3 = &nota3;

  recebe_dados(ptr_nota1, ptr_nota2, ptr_nota3);

  float resultado_media = media(ptr_nota1, ptr_nota2, ptr_nota3);

  cout << "A média das notas é: " << resultado_media << endl;

  return 0;
}


// int main()
// {
//   string pause;
//   int variavel=10;
  
//   cout<<"Hello World!"<<variavel; //printa
//   cin>>pause; //recebe dados
//   cout<<pause;
  
//   return 0;
// }
