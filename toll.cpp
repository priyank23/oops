#include<bits/stdc++.h>
using namespace std;
template<class T,class U>
class BILL
{
	string carno;
	string date;
	U amount;
	public:
	void randvehicle()
	{
		for(int i=0;i<10;i++)
		{
			if(i<6)
			{
				if(i==2 || i==3)
					cout<<char(rand()%10+'0');
				else
					cout<<char(rand()%26+'A');
			}
			else
				cout<<char(rand()%10+'0');
		}
		time_t tt;
		struct tm * ti;
    		time (&tt); 
    		ti = localtime(&tt);
    		date=asctime(ti);
	}
	void datedisp()
	{
		cout<<date<<endl;
	}
};
template<class T,class U>
class TOLLTAX
{
	protected:
	T nocar;
	T way;
	U totalfare;
	U tax[2][3];
	T twoW;
	T threeW;
	T fourW;
	U prepaid;
	U instant;
	public:
		TOLLTAX()
		{
			nocar=0;
			totalfare=0;
			twoW=0;
			threeW=0;
			fourW=0;
			prepaid=0;
			instant=0;
			tax[0][0]=20;
			tax[0][1]=40;
			tax[0][2]=60;
			tax[1][0]=80;
			tax[1][1]=100;
			tax[1][2]=110;
		}
		void receiveToll();
		void displayCar();
		void displayAmt();
		friend void randvehicle();
};

template<class T,class U>
void TOLLTAX<T,U>::receiveToll()
{
	int c,d,e;
	cout<<"\nENTER CAR TYPE:";
	cout<<"\n1. 2 WHEELER		2. 3 WHEELER		3. 4 WHEELER\n";
	cin>>c;
	cout<<"\n1. ONE-WAY		2. RETURN\n";
	cin>>e;
	if(c>3 || e>2)
	{
		cout<<"\nERROR INPUT!!!\nAborting...";
		return;
	}
	nocar++;
	cout<<"\nENTER PAYMENT METHOD:";
	cout<<"\n1. PREPAID		2. INSTANT\n";
	cin>>d;
	totalfare=totalfare+tax[e-1][c-1];
	if(d==1)
		prepaid=prepaid+tax[e-1][c-1];
	else
		instant=instant+tax[e-1][c-1];
	if(c==1)
		twoW++;
	else if(c==2)
		threeW++;
	else
		fourW++;
	cout<<"\nBILL\n";
	BILL<int,float>B;
	cout<<"\nVEHICLE NO:";
	B.randvehicle();
	cout<<"\nAMOUNT PAID:"<<tax[e-1][c-1];
	if(d==1)
		cout<<"\tPREPAID";
	else
		cout<<"\tINSTANT";	
	if(e==1)
		cout<<"\nONE-WAY";
	else
		cout<<"\nRETURN";
	cout<<"\nTIME:";
	B.datedisp();
	cout<<"\nVALID FOR 24 HRS";
	//cout<<"\n------------------------------\n";
}
template<class T,class U>
void TOLLTAX<T,U>::displayCar()
{
	cout<<"\n2 WHEELER:"<<twoW;
	cout<<"\n3 WHEELER:"<<threeW;
	cout<<"\n4 WHEELER:"<<fourW;
	cout<<"\nTOTAL CARS:"<<nocar;
}
template<class T,class U>
void TOLLTAX<T,U>::displayAmt()
{
	cout<<"\nPREPAID:"<<prepaid;
	cout<<"\nINSTANT:"<<instant;
	cout<<"\nTOTAL AMOUNT:"<<totalfare;
}
int main()
{
	srand(time(NULL));
	TOLLTAX<int,float>T;
	while(1)
	{
		int c;
		cout<<"\n1. RECEIVE TOLL\n2. DISPLAY NO. OF CAR\n3. DISPLAY AMOUNT\n";
		cout<<"ENTER CHOICE:";
		cin>>c;
		if(c==1)
			T.receiveToll();
		else if(c==2)
			T.displayCar();
		else if(c==3)
			T.displayAmt();
		else
			break;
	}
	return 0;
}
