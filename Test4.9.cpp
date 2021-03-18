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

void write(string name,int pass,float money,string status,float amount){
	fstream list("List.txt",ios::app);
	list<<name<<","<<pass<<","<<money<<","<<status<<","<<amount<<endl;
	list.close();
}

void importDataFromFile(string fn,vector<string> &names,vector<int> &spass,vector<float> &moneys,vector<string> &stats,vector<float> &balances){
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
		int pass;
    	float money;
        char ctext[100];
        char format[] = "%[^,],%d,%f";
        strcpy(ctext,text.c_str());
        sscanf(ctext,format,name,&pass,&money);
        write(name,pass,money,"add",money);
    }
}
    source.close();
    fstream list("List.txt",ios::in);
    while(getline(list,text)){
    	int pass;
    	float money;
        char ctext[100];
        char format[] = "%[^,],%d,%f,%[^,],%f";
        strcpy(ctext,text.c_str());
        sscanf(ctext,format,name,&pass,&money,stat,&balance);
        names.push_back(name);
        spass.push_back(pass);
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
	time_t rawtime;
    struct tm * local;
    time(&rawtime);
    local = localtime(&rawtime);

			cout << "\n\n\t\t\t\t\t PRINTING RECEIPT . . .\n";
			waiting(2500);
			system("cls");
			cout << endl <<"\n\n\t\t\t|\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2           \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\t\t\t\t\t|";
			cout << "\n\t\t\t|\t\t\t\t\t        |"
				 << "\n\t\t\t|\t      ATM TRANSACTION RECORD  \t        |"
				 << "\n\t\t\t|\t\t\t\t\t        |"
				 << "\n\t\t\t|DATE:\t\t\t   "<<local->tm_mday<<":"<<local->tm_mon<<":"<< local->tm_year <<"\t        |"
				 << "\n\t\t\t|TIME:\t\t\t   "<<local->tm_hour<<":"<<local->tm_min<<":"<< local->tm_sec <<"\t        |";
}

void searchName(vector<string> &names,vector<float> &moneys,vector<string> &stats,vector<float> &balances,string key){
    int N = names.size();
    int stat = 0;
    cout << "---------------------------------------------------------------------------------------------------\n\n";
    cout << "NAME" << "\t\t" << "amount" << "\t\t" << "Add" << "\t\t" << "WITHDRAW" << "\t\t" << "BALANCE"<<endl;
    for(int i = 0 ; i < N ; i++){
        if(key == toUpperStr(names[i])){
            cout << names[i] << "\t\t" << moneys[i] << "\t\t";
			if(stats[i] == "withdraw")  cout<< "\t\t";
			cout << stats[i] << "\t\t";
			if(stats[i] != "withdraw") cout<< "\t\t\t";
			cout << balances[i] << endl;
            stat = 1;
        }
    }
    if(stat != 1) cout << "Cannot found." << endl;
    cout << "\n\n---------------------------------------------------------------------------------------------------";
}

void Deposit(vector<string> &names,vector<int> &spass,vector<float> &balances,string key){
    int N = names.size();
    int deposit;
    cout << "---------------------------------\n\n";
    for(int i = 0 ; i < N ; i++){
        if(key == toUpperStr(names[i])){
        	sname=names[i];
        	m=i;
        }
    }
	cout << sname << "'s Money in the account now = " << fixed << setprecision(2) << balances[m] << endl;
    cout <<"How much will you deposit? ";
        	cin>>deposit;
        	balances[m]+=deposit;
            cout << sname << "'s balance = " << fixed << setprecision(2) << balances[m] << endl;
            status = "add";
            write(sname,spass[m],deposit,status,balances[m]);
    if(status != "add") cout << "Cannot found." << endl;
    cout << "\n\n---------------------------------";
    
   	system("cls");
	receipt();
	cout << "\n\t\t\t|Balance:\t\t   " << balances[m] <<"\t        |";
}
void Withdraw(vector<string> &names,vector<int> &spass,vector<float> &balances,string key){
    int N = names.size();
    int withdraw;
    cout << "---------------------------------\n\n";
    for(int i = 0 ; i < N ; i++){
        if(key == toUpperStr(names[i])){
        	sname=names[i];
        	m=i;
        }
    }
	cout << sname << "'s Money in the account now = " << fixed << setprecision(2) << balances[m] << endl;
    cout <<"How much will you withdraw? ";
        	cin>>withdraw;
        	if(balances[m] >= withdraw){
			balances[m]-=withdraw;
            cout << sname << "'s balance = " << fixed << setprecision(2) << balances[m] << endl;
            status = "withdraw";}
            write(sname,spass[m],withdraw,status,balances[m]);
    if(status != "withdraw") cout << "Cannot found." << endl;
    cout << "\n\n---------------------------------";
    
	system("cls");
	receipt();
	cout << "\n\t\t\t|Balance:\t\t\t   " << balances[m] <<"\t        |";
}

void Transfer(vector<string> &names,vector<int> &spass,vector<float> &balances,string key){
	int N = names.size();
    int transfer,t=0;
    string target,stat="false",tname;
    cout << "---------------------------------\n\n";
    for(int i = 0 ; i < N ; i++){
        if(key == toUpperStr(names[i])){
        	sname=names[i];
        	m=i;
        }
    }
	cout << sname << "'s Money in the account now = " << fixed << setprecision(2) << balances[m] << endl;
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
    	}else cout<<"Cannot found. Plase input agian: ";
	}while(true);
    cout <<"How much will you transfer? ";
        	cin>>transfer;
        	if(balances[m] >= transfer){
			balances[m] -= transfer;
            cout << sname << "'s balance = " << fixed << setprecision(2) << balances[m] << endl;
            status = "withdraw";}
            write(sname,spass[m],transfer,status,balances[m]);
            balances[t] += transfer;
            status = "add";
            write(tname,spass[t],transfer,status,balances[t]);
    cout << "\n\n---------------------------------";
    
	system("cls");
	receipt();
	cout << "\n\t\t\t|Balance:\t\t   " << balances[m] <<"\t        |";
}

void Balance(vector<string> &names,vector<float> &balances,string key){
	int N = names.size();
    cout << "-------------------------------------------------\n\n";
    for(int i = 0 ; i < N ; i++){
        if(key == toUpperStr(names[i])){
        	sname=names[i];
        	m=i;
        }
    }
	cout << sname << "'s Balance in the account now = " << fixed << setprecision(2) << balances[m] << endl;
    cout << "\n\n-------------------------------------------------";
	
}

int main(){
    string filename = "Bank.txt";
    vector<string> names;
    vector<int> spass;
    vector<float> moneys;
    vector<string> stats;
	vector<float> balances;
    string key,stat;
    int pass;
    importDataFromFile(filename, names, spass , moneys , stats, balances);
    cout<<"Please input your name : ";
	getline(cin,key);
	key = toUpperStr(key);
	cout<<"Please input your password : ";
	int N=names.size(),count=0;
	while(true){
		cin>>pass;
		cin.ignore();
		for(int i = 0 ; i < N ; i++){
        	if(pass == spass[i]){
        		stat = "true";
        		break;
			}
		}
		if(stat == "true") break;
		else {
		count++;
		cout<<"Please input your password again : ";
		}
		if(count == 5) break;
	}
	if(count == 5){
		system("cls");
		cout << "too much unusual access. Exit";
		return 0;
	}
	cout<<"Please select your order"<<endl;
	cout<<"1 : Deposit"<<"     "<<"2 : Withdraw"<<"     "<<"3 : Transfer"<<endl;
	cout<<"4 : View transaction history"<<"     "<<"5 : Check Balance"<<"     "<<"6 : EXIT"<<endl;
	while(true){
		cout<<"Please select number(1-6) : ";
		cin>>x;
		if(x>0&&x<7) break;
		else cout<<"Please select again"<<endl;
	}
        if(x == 1) Deposit(names, spass , balances, key);
		if(x == 2) Withdraw(names, spass , balances, key);
		if(x == 3) Transfer(names, spass ,balances, key);
        if(x == 4) searchName(names, moneys, stats, balances, key);
        if(x == 5) Balance(names, balances, key);
        if(x == 6){
		system("cls");
		cout << "THANK YOU FOR CHOOSING US";
}
    return 0;
}
