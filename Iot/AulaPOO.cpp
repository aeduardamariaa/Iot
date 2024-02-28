#include <iostream>

using namespace std;

int main(){
  cout<<(0b100 & 0b101)<<endl;
  cout<<(0b100 | 0b101)<<endl;
  cout<<(4<<2)<<endl;  // 100(4) << 2 = 10000(16)
  cout<<(4>>2)<<endl;  // 100(4) >> 2 = 1 (1)
  cout<<~4<<endl;  // ~4 = -(5) = -5
  cout<<(12^10)<<endl;
  return 0;
}
