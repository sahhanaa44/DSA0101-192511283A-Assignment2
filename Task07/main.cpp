#include <iostream>
#include <chrono>
#include <vector>
using namespace std;
class ShiftHistory{vector<int> a;size_t cap;public:explicit ShiftHistory(size_t k):cap(k){}void add(int x){if(a.size()==cap)a.erase(a.begin());a.push_back(x);}vector<int> snapshot()const{return a;}};
class RingHistory{vector<int> a;size_t cap,start=0,count=0;public:explicit RingHistory(size_t k):a(k),cap(k){}void add(int x){if(count<cap){a[(start+count)%cap]=x;++count;}else{a[start]=x;start=(start+1)%cap;}}vector<int> snapshot()const{vector<int> out;for(size_t i=0;i<count;i++)out.push_back(a[(start+i)%cap]);return out;}};
template<class T>long long run(size_t k,int n){T t(k);auto begin=chrono::steady_clock::now();for(int i=0;i<n;i++)t.add(i);auto end=chrono::steady_clock::now();auto v=t.snapshot();cout<<"capacity="<<k<<" size="<<v.size()<<" first="<<v.front()<<" last="<<v.back()<<'\n';return chrono::duration_cast<chrono::microseconds>(end-begin).count();}
int main(){for(size_t k:{size_t(10),size_t(50),size_t(1000),size_t(10000)}){cout<<"shift us="<<run<ShiftHistory>(k,100000)<<'\n';cout<<"ring us="<<run<RingHistory>(k,100000)<<'\n';}}
