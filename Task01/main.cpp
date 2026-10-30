#include <iostream>
using namespace std;
void byValue(long long fee,int percent){fee-=fee*percent/100;cout<<"Inside value: "<<fee<<'\n';}
void byReference(long long& fee,int percent){fee-=fee*percent/100;}
void byPointer(long long* fee,int percent){if(fee)*fee-=*fee*percent/100;}
void change(int a,int& b,int* c){a+=10;b+=10;*c+=10;}
int& bigger(int& p,int& q){return p>q?p:q;}
void show(int x,int y=5,int z=10){cout<<x+y+z<<' ';}
int main(){
 int a=1,b=2,c=3;change(a,b,&c);cout<<a<<' '<<b<<' '<<c<<'\n';
 bigger(a,c)=100;cout<<a<<' '<<c<<'\n';show(1);show(1,2);show(1,2,3);cout<<'\n';
 long long fee=45000;byValue(fee,10);cout<<"after call by value   : "<<fee<<'\n';
 byReference(fee,10);cout<<"after call by reference: "<<fee<<'\n';
 byPointer(&fee,15);cout<<"after call by pointer  : "<<fee<<'\n';
}
