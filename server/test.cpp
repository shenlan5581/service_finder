

#include <iostream>
#include <string>
using namespace std;
class a
{ 
    public: 
  a(){s=5;};  
  int s;
}; 
class b
{
public:
  b(int x){z=x;};
  b(const b &x) { z = (x.z+1); }; 
  int z;      
};             
void  fun(b bs)
{
 cout<<bs.z<<endl; 
}
  
int main()
{
    b  b1(10);
    cout<<b1.z;
    fun(b1); 
}


 