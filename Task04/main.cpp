#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
class SavingsAccount{
 long long account;double balance;double tx[10]{};int count=0;
 void record(double amount){if(count<10)tx[count++]=amount;else{for(int i=1;i<10;i++)tx[i-1]=tx[i];tx[9]=amount;}}
public:
 SavingsAccount(long long id,double initial):account(id),balance(initial){}
 void deposit(double amount){if(amount>0){balance+=amount;record(amount);}}
 bool withdraw(double amount);
 void miniStatement()const;
};
bool SavingsAccount::withdraw(double amount){if(amount<=0||amount>balance)return false;balance-=amount;record(-amount);return true;}
void SavingsAccount::miniStatement()const{cout<<fixed<<setprecision(2)<<"Account "<<account<<" balance "<<balance<<'\n';for(int i=0;i<count;i++)cout<<i+1<<": "<<tx[i]<<'\n';}
int main(){SavingsAccount a(12345,1000);for(int i=0;i<12;i++)a.deposit(10+i);a.withdraw(20);a.miniStatement();}
