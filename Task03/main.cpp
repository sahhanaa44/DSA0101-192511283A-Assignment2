#include <iostream>
#include <string>
using namespace std;
struct Parcel{double kg;bool express=false;bool insured=false;};
double compute(double kg,bool express,bool insured){return 40+kg*20+(express?50:0)+(insured?25:0);}
double charge(int grams){cout<<"grams overload: ";return compute(grams/1000.0,false,false);}
double charge(double kg,bool express=false,bool insured=false){cout<<"kg overload: ";return compute(kg,express,insured);}
double charge(float kg){cout<<"float overload: ";return compute(kg,false,false);}
double charge(const Parcel& p){cout<<"Parcel overload: ";return compute(p.kg,p.express,p.insured);}
int main(){cout<<charge(2)<<'\n'<<charge(2.0f)<<'\n'<<charge(2.0)<<'\n'<<charge(2.0,true)<<'\n'<<charge(2.0,true,true)<<'\n'<<charge(Parcel{2.0,true,true})<<'\n';}
