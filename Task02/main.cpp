#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int& highest(int a[],int n){return *max_element(a,a+n);}
const int& highestReadOnly(const int a[],int n){return *max_element(a,a+n);}
int highestCopy(const int a[],int n){return *max_element(a,a+n);}
int highestIndex(const int a[],int n){return max_element(a,a+n)-a;}
int* highestPointer(int a[],int n){return max_element(a,a+n);}
int main(){int marks[]={70,86,91,80};highest(marks,4)+=2;
 cout<<"Moderated: "<<marks[2]<<"; const ref: "<<highestReadOnly(marks,4)
 <<"; copy: "<<highestCopy(marks,4)<<'\n';
 cout<<"Index: "<<highestIndex(marks,4)<<"; pointer: "<<*highestPointer(marks,4)<<'\n';
 vector<int> v={70,86,91};size_t index=max_element(v.begin(),v.end())-v.begin();
 v.reserve(100);v.push_back(95);cout<<"Vector max after growth: "<<v[index]<<'\n';
}
