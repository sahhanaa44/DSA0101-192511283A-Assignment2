#include <iostream>
#include <chrono>
#include <cstdlib>
using namespace std;
class Time{int h,m;public:Time(int hh,int mm):h(hh),m(mm){}friend int minutesBetween(const Time&,const Time&);friend bool earlier(const Time&,const Time&);friend inline int minutesInline(const Time&,const Time&);};
int minutesBetween(const Time& a,const Time& b){return abs((a.h*60+a.m)-(b.h*60+b.m));}
bool earlier(const Time& a,const Time& b){return a.h*60+a.m<b.h*60+b.m;}
inline int minutesInline(const Time& a,const Time& b){return abs((a.h*60+a.m)-(b.h*60+b.m));}
template<typename F>void benchmark(const char* label,F fn){Time a(9,45),b(13,10);volatile long long sink=0;auto start=chrono::steady_clock::now();for(int i=0;i<10000000;i++)sink=sink+fn(a,b);auto end=chrono::steady_clock::now();cout<<label<<" ns="<<chrono::duration_cast<chrono::nanoseconds>(end-start).count()<<" checksum="<<sink<<'\n';}
int main(){Time a(9,45),b(13,10),c(12,0),d(12,0);cout<<minutesBetween(a,b)<<' '<<boolalpha<<earlier(b,a)<<'\n';cout<<"Same: "<<minutesBetween(c,d)<<' '<<earlier(c,d)<<"; noon: "<<minutesBetween(a,c)<<'\n';benchmark("regular",minutesBetween);benchmark("inline",minutesInline);}
