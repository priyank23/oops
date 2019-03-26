#include <bits/stdc++.h>
using namespace std;

class Person
{
	string holder_name;
	long int acc_number;
	//long int ifsc_code;
	string date_update;
	string time_update;
	public:
		void setname(string name){
			holder_name=name;
		}
		
		void setAccountNumber(long int n)
		{
			acc_number=n;
		}
		
		string getname()
		{
			return holder_name;
		}
		
		long int getAccNo()
		{
			return acc_number;
		}
		
		void set_date_update(string s1)
		{
			date_update = s1;
		}
		
		void set_time_update(string s2)
		{
			time_update = s2;
		}
		
		string d_update()
		{
			return date_update;
		}
		
		string t_update()
		{
			return time_update;
		}
};

class Balance:public Person
{
	float amt;
	public:
		Balance()
		{
			amt=0;
		}
		
		void initialize(float amt_todeposit)
		{
			amt=amt_todeposit;
		}
		
		void deposit(float amt)
		{
			if(amt<0)
				cout<<"Wrong Input"<<endl<<endl;
			else
			{
				this->amt+=amt;
				cout<<"Deposit : "<<amt<<" to bank account SUCCESSFULL!!"<<endl;
				cout<<"BALANCE : "<<this->amt<<endl<<endl;
			}
		}
		
		void withdrawal(float amt)
		{
			if(amt<0)
				cout<<"Wrong Input"<<endl<<endl;
			else
			{
				float chk=this->amt-amt;
				if(chk < 0)
				{
					cout<<"BALANCE : "<<this->amt<<endl;
					cout<<"Transaction NOT POSSIBLE\nInsufficient balance"<<endl<<endl;
				}
				else if(chk >= 500)
				{
					this->amt=chk;
					cout<<"Withdrawal : "<<amt<<" from bank account SUCCESSFULL!!"<<endl;
					cout<<"BALANCE : "<<this->amt<<endl<<endl;
				}
			}
		}
		
		float getamt()
		{
			return amt;
		}
};

class AllTransaction
{
	unordered_set<long int> acc_no;
	vector<Balance> save;
	
	private:
	
		string date_update()
		{
			string str;
			time_t now = time(0);
   			tm *ltm = localtime(&now);
		   	str = to_string(ltm->tm_mday)+"/"+to_string(1 + ltm->tm_mon)+"/"+to_string(1900 + ltm->tm_year);
		   	return str;
		}
		
		string time_update()
		{
			string str;
			time_t now = time(0);
   			tm *ltm = localtime(&now);
   			str = to_string(ltm->tm_hour)+":"+to_string(ltm->tm_min)+":"+to_string(ltm->tm_sec);
   			return str;
		}
			
		long int generate()
		{
		    long int myRand;
			srand(unsigned(time(0)));
			const long int MAX = 99999999999;
			const long int MIN = 10000000000;
			for(int i = 0; i < 12; i++)
			{
				myRand = rand()/(float)RAND_MAX * (MAX-MIN) + MIN ;
			}
			if(acc_no.empty())
				acc_no.insert(myRand);
			
			else
			{
				if(acc_no.find(myRand)==acc_no.end())
					acc_no.insert(myRand);
				else
					generate();
			}
			return myRand;
		}
	
	public:
		void add_member()
		{
			string sname;
			long int new_acc_no;
			cout<<"NAME : ";
			cin>>sname;
			new_acc_no = generate();
	
			Balance p;
			p.setname(sname);
			p.setAccountNumber(new_acc_no);
			
			p.set_date_update(date_update());
			p.set_time_update(time_update());
			
			save.push_back(p);
			cout<<"A/C: "<<p.getAccNo()<<endl;
			
			cout<<"ACCOUNT ADDED SUCCESSFULLY."<<endl<<endl;
			cout<<"Want to add more?[y/n] : ";
			char chk;
			cin>>chk;
			if(chk=='y' || chk=='Y')
				add_member();
		}
		
		void transaction()
		{			
		    long int input_acc;
		    cout<<"Enter A/C: ";
		    cin>>input_acc;
		    if(acc_no.find(input_acc)==acc_no.end())
		    {
		        cout<<"Invalid A/C no!!!"<<endl;
		        cout<<"Try Again."<<endl<<endl;
		        transaction();
		    }
		    else
		    {
		        string s;
		       //cout<<"ACCOUNT FOUND"<<endl<<endl;		        
		        cout<<"Confirm with ACCOUNT HOLDER'S name : ";
		        cin>>s;
		        int flag=0;
		        int index;
		            for(int i=0; i<save.size(); i++)
		            {
		                if(s==save[i].getname())
		                {
		                    flag=1;
		                    index=i;
		                    break;
		                }
		            }
		            if(flag==1)
		            {
		                cout<<"WELCOME "<<s<<endl<<endl;
		                cout<<"Is it your first time in the bank?[y/n]"<<endl;
		                char ans;
		                cin>>ans;
		                save[index].set_date_update(date_update());
				save[index].set_time_update(time_update());
		                if(ans=='y' || ans=='Y')
		                {
		                	cout<<"Enter Amount:"<<endl;
		                	float amt;
		                	cin>>amt;
		                	save[index].initialize(amt);
		                }
		                else
		                {
		                	cout<<"Enter your choice.\n";
		                	cout<<"1.DEPOSIT\n2.WITHDRAWAL\n3.BALANCE"<<endl;
		                	int x;
		                	cin>>x;
		                	if(x==1)
		                	{
		                		cout<<"Amount:"<<endl;
		                		float amount;
		                		cin>>amount;
		                		save[index].deposit(amount);
		                	}
		                	else if(x==2)
		                	{
		                		cout<<"Amount:"<<endl;
		                		float amount;
		                		cin>>amount;
		                		save[index].withdrawal(amount);
		                	}
		                	else if(x==3)
		                	{
		                		cout<<"BALANCE: "<<save[index].getamt()<<endl;
		                		cout<<"Last Activity : "<<save[index].d_update()<<"  "<<save[index].t_update()<<endl<<endl;
		                	}
		                }
		            }
		            else
		        		cout<<"ACCOUNT HOLDER'S name NOT matching"<<endl;
		    	}
			}
			
			void display()
			{
				cout<<"NAME\t\tACCOUNT NO.\t\tLast Update(Date)\tLast Activity\t\tBALANCE\n";
				for(int i=0; i<save.size(); i++)
		        {
		        	cout<<save[i].getname()<<"\t\t"<<save[i].getAccNo()<<"\t\t"<<save[i].d_update()<<"\t\t"<<save[i].t_update()<<"\t\t\t"<<save[i].getamt()<<endl;
		        }
			}
};

int main()
{
	AllTransaction at;
	int k1,k2;	
	do
	{
		system("clear");
		cout<<"1.ADD MEMBER"<<endl;
		cout<<"2.TO DO BALANCE QUERIES"<<endl;
		cout<<"3.TO Display"<<endl<<endl;
		cin>>k1;
		if(k1==1)
			at.add_member();
		else if(k1==2)
			at.transaction();
		else if(k1==3)
			at.display();
		
		cout<<"1. To Continue\n2. Break out"<<endl;
		cin>>k2;
		if(k2==2)
			break;
	}while(k2==1);
	return 0;
}


