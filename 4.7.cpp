#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include <stdio.h>
#include <time.h>

using namespace std;

int x,m;
string sname,status;

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void write(string name,float money,string status,float amount){
	fstream list("List.txt",ios::app);
	list<<name<<","<<money<<","<<status<<","<<amount<<endl;
	list.close();
}

void importDataFromFile(string fn,vector<string> &names,vector<float> &moneys,vector<string> &stats,vector<float> &balances){
	fstream source(fn.c_str());
    string text,c;
    char name[100],stat[10];
    float balance = 0;
    fstream check("List.txt",ios::in);
    if(getline(check,text)){
    	c = "T";
	}else c = "F";
	check.close();
    if(c == "F"){
	while(getline(source,text)){
    	float money;
        char ctext[100];
        char format[] = "%[^,],%f";
        strcpy(ctext,text.c_str());
        sscanf(ctext,format,name,&money);
        write(name,money,"add",money);
    }
}
    source.close();
    fstream list("List.txt",ios::in);
    while(getline(list,text)){
    	float money;
        char ctext[100];
        char format[] = "%[^,],%f,%[^,],%f";
        strcpy(ctext,text.c_str());
        sscanf(ctext,format,name,&money,stat,&balance);
        names.push_back(name);
        moneys.push_back(money);
        stats.push_back(stat);
        balances.push_back(balance);
    }
    list.close();
}

void waiting(unsigned int mseconds){
		clock_t goal = mseconds + clock();
		while (goal > clock());
	}

void receipt(){
		system("cls");
			char date[9];
			char time[9];
			_strdate(date);
			_strtime(time);

			cout << "\n\n\t\t\t\t\t PRINTING RECEIPT . . .\n";
			waiting(2500);
			system("cls");
			cout << endl <<"\n\n\t\t\t|\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2              \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2|";
			cout << "\n\t\t\t|\t\t\t\t\t      |"
				 << "\n\t\t\t|\t     ATM TRANSACTION RECORD\t      |"
				 << "\n\t\t\t|\t\t\t\t\t      |"
				 << "\n\t\t\t|DATE:\t\t\t       "<<date<<"\t      |"
				 << "\n\t\t\t|TIME:\t\t\t       "<<time<<"\t      |";
				
}

void searchName(vector<string> &names,vector<float> &moneys,vector<string> &stats,vector<float> &balances,string key){
    int N = names.size();
    int stat = 0;
    cout << "---------------------------------\n";
    cout << "NAME" << "\t\t" << "amount" << "\t\t" << "Add" << "\t\t" << "DEDUCT" << "\t\t" << "BALANCE"<<endl;
    for(int i = 0 ; i < N ; i++){
        if(key == toUpperStr(names[i])){
            cout << names[i] << "\t\t" << moneys[i] << "\t\t"<< stats[i] << "\t\t";
			if(stats[i] != "withdraw") cout<< "\t\t";
			cout << balances[i] << endl;
            stat = 1;
        }
    }
    if(stat != 1) cout << "Cannot found." << endl;
    cout << "---------------------------------\n";
}

void Deposit(vector<string> &names,vector<float> &moneys,string key){
    int N = names.size();
    int deposit;
    cout << "---------------------------------\n";
    for(int i = 0 ; i < N ; i++){
        if(key == toUpperStr(names[i])){
        	sname=names[i];
        	m=i;
        }
    }
	cout << sname << "'s Money in the account now = " << fixed << setprecision(2) << moneys[m] << endl;
    cout <<"How much will you deposit? ";
        	cin>>deposit;
        	moneys[m]+=deposit;
            cout << sname << "'s balance = " << fixed << setprecision(2) << moneys[m] << endl;
            status = "add";
            write(sname,deposit,status,moneys[m]);
    if(status != "add") cout << "Cannot found." << endl;
    cout << "---------------------------------\n";
    
   	system("cls");
	receipt();
	cout << "\n\t\t\t|Balance:\t\t       " << moneys[m] <<"\t      |";
}
void Withdraw(vector<string> &names,vector<float> &moneys,string key){
    int N = names.size();
    int withdraw;
    cout << "---------------------------------\n";
    for(int i = 0 ; i < N ; i++){
        if(key == toUpperStr(names[i])){
        	sname=names[i];
        	m=i;
        }
    }
	cout << sname << "'s Money in the account now = " << fixed << setprecision(2) << moneys[m] << endl;
    cout <<"How much will you withdraw?";
        	cin>>withdraw;
        	if(moneys[m] >= withdraw){
			moneys[m]-=withdraw;
            cout << sname << "'s balance = " << fixed << setprecision(2) << moneys[m] << endl;
            status = "withdraw";}
            write(sname,withdraw,status,moneys[m]);
    if(status != "withdraw") cout << "Cannot found." << endl;
    cout << "---------------------------------\n";
    
	system("cls");
	receipt();
	cout << "\n\t\t\t|Balance:\t\t  " << moneys[m] <<"\t      |";
}

void Transfer(vector<string> &names,vector<float> &moneys,string key){
	int N = names.size();
    int transfer,t=0;
    string target,stat="false",tname;
    cout << "---------------------------------\n";
    for(int i = 0 ; i < N ; i++){
        if(key == toUpperStr(names[i])){
        	sname=names[i];
        	m=i;
        }
    }
	cout << sname << "'s Money in the account now = " << fixed << setprecision(2) << moneys[m] << endl;
	cout <<"Transfer money to which account: ";
	do{
	cin>>target;
	cin.ignore();
	target=toUpperStr(target);
		for(int j = 0 ; j < N ; j++){
        	if(target == toUpperStr(names[j])){
        		tname=names[j];
        		t=j;
        	}
    	}
    	if(t!=0){
			stat="true";
			break;
    	}else cout<<"Cannot found. Plase input agian: "<<endl;
	}while(true);
    cout <<"How much will you transfer? ";
        	cin>>transfer;
        	if(moneys[m] >= transfer){
			moneys[m] -= transfer;
            cout << sname << "'s balance = " << fixed << setprecision(2) << moneys[m] << endl;
            status = "withdraw";}
            write(sname,transfer,status,moneys[m]);
            moneys[t] += transfer;
            status = "deposit";
            write(sname,transfer,status,moneys[m]);
    cout << "---------------------------------\n";
    
	system("cls");
	receipt();
	cout << "\n\t\t\t|Balance:\t\t  " << moneys[m] <<"\t      |";
}

void Balance(vector<string> &names,vector<float> &balances,string key){
	int N = names.size();
    cout << "---------------------------------\n";
    for(int i = 0 ; i < N ; i++){
        if(key == toUpperStr(names[i])){
        	sname=names[i];
        	m=i;
        }
    }
	cout << sname << "'s Balance in the account now = " << fixed << setprecision(2) << balances[m] << endl;
    cout << "---------------------------------\n";
	
}

int main(){
    string filename = "Bank.txt";
    vector<string> names;
    vector<float> moneys;
    vector<string> stats;
	vector<float> balances;
    string key;
    importDataFromFile(filename, names, moneys , stats, balances);
    cout<<"Please input your name : ";
	getline(cin,key);
	key = toUpperStr(key);
	cout<<"Please select your order"<<endl;
	cout<<"1 : Deposit"<<"     "<<"2 : Withdraw"<<"     "<<"3 : Transfer"<<endl;
	cout<<"4 : View transaction history"<<"     "<<"5 : Check Balance"<<"     "<<"6 : EXIT"<<endl;
	while(true){
		cout<<"Please select number(1-6) : ";
		cin>>x;
		if(x>0&&x<7) break;
		else cout<<"Please select again"<<endl;
	}
        if(x == 1) Deposit(names, moneys, key);
		if(x == 2) Withdraw(names, moneys, key);
		if(x == 3) Transfer(names, moneys, key);
        if(x == 4) searchName(names, moneys, stats, balances, key);
        if(x == 5) Balance(names, balances, key);
        if(x == 6){
		system("cls");
		cout << "THANK YOU FOR CHOOSING US";
}
    return 0;
}
