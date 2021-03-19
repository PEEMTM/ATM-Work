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

int m;
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
	while(true){
    cout <<"How much will you deposit? ";
        	cin>>deposit;
        	if(deposit > 0){
        	balances[m]+=deposit;
            cout << sname << "'s balance = " << fixed << setprecision(2) << balances[m] << endl;
            status = "add";
            write(sname,spass[m],deposit,status,balances[m]);
    if(status != "add") cout << "Cannot found." << endl;
    cout << "\n\n---------------------------------";
    
   	system("cls");
	receipt();
	cout << "\n\t\t\t|Balance:\t\t   " << balances[m] <<"\t        |";
	break;
	}else cout << "Not permit this amount. Plase input again." << endl;
}
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
	if(balances[m] >= 100){
    while(true){
    		cout <<"How much will you withdraw? ";
        	cin>>withdraw;
        	if(balances[m] >= withdraw && withdraw % 100 == 0 && withdraw >= 100){
			balances[m]-=withdraw;
            cout << sname << "'s balance = " << fixed << setprecision(2) << balances[m] << endl;
            status = "withdraw";
            write(sname,spass[m],withdraw,status,balances[m]);
			break;
			}
			else if(balances[m] >= withdraw && withdraw % 100 != 0 ) cout << "Not permit this amount. Plase withdraw hundreds of money only" << endl;
			else cout << "Not enough money " << endl;
	}
	if(status == "withdraw"){
		    cout << "\n\n---------------------------------";
			system("cls");
			receipt();
			cout << "\n\t\t\t|Balance:\t\t   " << balances[m] <<"\t        |";
		}
	}else cout << "Money in the account now not enough! (money < 100) can't withdraw ";
}

void Transfer(vector<string> &names,vector<int> &spass,vector<float> &balances,string key){
	int N = names.size(),t=0;
    float transfer;
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
    	}else cout<<"Cannot found. Plase input again: ";
	}while(true);
	while(true){
    cout <<"How much will you transfer? ";
        	cin>>transfer;
        	if(balances[m] >= transfer && transfer > 0){
			balances[m] -= transfer;
            cout << sname << "'s balance = " << fixed << setprecision(2) << balances[m] << endl;
            status = "withdraw";
            write(sname,spass[m],transfer,status,balances[m]);
            balances[t] += transfer;
            status = "add";
            write(tname,spass[t],transfer,status,balances[t]);
    cout << "\n\n---------------------------------";
    
	system("cls");
	receipt();
	cout << "\n\t\t\t|Balance:\t\t   " << balances[m] <<"\t        |";
	break;
	}
	else if(transfer <= 0) cout << "Not permit this amount. Plase input again." << endl;
	else cout << "Not enough money " << endl;
	
	}
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
    string key,stat,nstat,y;
    int pass;
    importDataFromFile(filename, names, spass , moneys , stats, balances);
    int N=names.size(),count=0,m;
    
    cout<<"Please input your name : ";
    while(true){
		getline(cin,key);
		key = toUpperStr(key);
		for(int i = 0 ; i < N ; i++){
        	if(key == toUpperStr(names[i])){
        		nstat = "true";
        		break;
			}
		}
		if(nstat != "true")cout<<"Please input your name again : ";
		else break;
	}
	cout<<"Please input your password : ";
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
	while(true){
	double x = -1;
	system("cls");
	cout<<"\n\nPlease select your order"<<endl;
	cout<<"1 : Deposit"<<"     "<<"2 : Withdraw"<<"     "<<"3 : Transfer"<<endl;
	cout<<"4 : View transaction history"<<"     "<<"5 : Check Balance"<<"     "<<"6 : EXIT"<<endl;
	cout<<"Please select number(1-6) : ";
	do{
		getline(cin,y);
		x = atof(y.c_str());
		if(x>0&&x<7) break;
		if(x<=0.0&&x>7.0) cout<<"Please select again"<<endl;
	}while(true);
	
        if(x == 1) Deposit(names, spass , balances, key);
		if(x == 2) Withdraw(names, spass , balances, key);
		if(x == 3) Transfer(names, spass ,balances, key);
        if(x == 4) searchName(names, moneys, stats, balances, key);
        if(x == 5) Balance(names, balances, key);
        if(x == 6){
		system("cls");
		cout << "THANK YOU FOR CHOOSING US";
		break;
	}
	waiting(4000);
}
    return 0;
}
