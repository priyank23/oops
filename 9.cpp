#include<iostream>
#include<fstream>
using namespace std;
 
class BALANCE
{
    int ac,DD,MM,YY;
    float bal;
public:
    BALANCE()
    {
        ac=0;
        DD=0;
        MM=0;
        YY=0;
        bal=0;
    }
    inline int return_ac()
    {
        return ac;
    }
    void get_time()
    {
        time_t now = time(0);
		tm *ltm = localtime(&now);
        DD=ltm->tm_mday;
        MM=ltm->tm_mon+1;
        YY=ltm->tm_year+1900;
    }
    int get_bal();
    void display_bal(int);
    void update_bal(int,float);
    void add_ac();
    int chk_ac(int);
    float ret_bal(int);
    void display();
};
void BALANCE::update_bal(int a,float b)
{
    //cout<<"Enter the account number to be updated.\n";
    //int a;
    //cin>>a;
    ofstream f,n;
    ac=a;
    bal=b;
    get_time();
    //n.open("bal_n.dat",ios::in|ios::binary);
    f.open("bal.dat",ios::out|ios::binary);
    int pos=chk_ac(a);
    if(pos==-2)
    {
        cout<<"The account does not exist.\nWant to create a new one?[y/n]";
        char c;
        cin>>c;
        if(c=='y') add_ac();
        return;
    }
    cout<<"a\n";
    //f.read((char*)(&BALANCE),sizeof(BALANCE));
    //updated values entering
    //bal=b;
    //cout<<"Enter the updated date.\n";
    //cin>>DD>>".">>MM>>".">>YY;
    //make system date here
    f.seekp(pos,ios::beg);
    /*while(f.read((char*)(&b),sizeof(bn
    )))  //copying whole file in n and removing f and renaming n as original
    {
        BALANCE b;
        if(f.tellg()==(pos-sizeof(b)))
        {
            cout<<"b\n";
            
            n.write((char*)(&(*this)),sizeof(BALANCE));
        }
        else
        {
            cout<<"y\n";
          //  f.read((char*)(&b),sizeof(b));
            n.write((char*)(&b),sizeof(b));
        }
    }*/
    f.write((char*)(&(*this)),sizeof(*this));
    cout<<"b\n";
    f.close();
  //  remove("bal.dat");
    //rename("bal_n.dat","bal.dat");
}
void BALANCE::display_bal(int a)
{
    int pos=chk_ac(a);
    if(pos==-2)
    {
        cout<<"Account does not exist!!!\n";
        return;
    }
    ifstream f;
    f.open("bal.dat",ios::in|ios::binary);
    f.seekg(pos,ios::beg);
    f.read((char*)(&(*this)),sizeof(BALANCE));
    cout<<"A/C\t\tBALANCE\tLAST UPDATED\n";
    cout<<ac<<'\t'<<bal<<'\t'<<DD<<"."<<MM<<"."<<YY<<"."<<endl;
    f.close();
}
void BALANCE::display()
{
    ifstream f;
    f.open("bal.dat",ios::in|ios::binary);
    while(!f.eof())
    {
        f.read((char*)(&(*this)),sizeof(BALANCE));
        cout<<"A/C\t\tBALANCE\tLAST UPDATED\n";
        cout<<ac<<'\t'<<bal<<'\t'<<DD<<"."<<MM<<"."<<YY<<"."<<endl;
    }
    f.close();
}
int BALANCE::chk_ac(int a)
{
    ifstream f;
    int pos;
    int flag=0;
    f.open("bal.dat",ios::in|ios::binary);
    while(!f.eof())
    {
        BALANCE b;
        pos=f.tellg();
        f.read((char*)(&b),sizeof(b));
        if(b.return_ac()==a)
        {
            flag=1;
            break;
        }
    }
    if(flag==0) pos=-2;
    f.close();
    return pos;
}
void BALANCE::add_ac()
{
    ofstream f;
    f.open("bal.dat",ios::app|ios::binary);
    int i=get_bal();
    if(i==0)
    f.write((char*)(&(*this)),sizeof(BALANCE));
    f.close();
}
int BALANCE::get_bal()
{
    cout<<"A/C NO:";
    cin>>ac;
    int i=chk_ac(ac);
    if(i!=-2)
    {
        cout<<"Account already available.\n";
        return -1;
    }
    cout<<"Bal:";
    cin>>bal;
    cout<<"DATE:";
    cin>>DD>>MM>>YY;
    return 0;
}
float BALANCE::ret_bal(int ac)
{
    ifstream f;
    f.open("bal.dat",ios::in|ios::binary);
    int pos=chk_ac(ac);
    f.seekg(pos,ios::beg);
    f.read((char*)(&(*this)),sizeof(BALANCE));
    f.close();
    return bal;
}
class TRANSACTION
{
    int ac,DD,MM,YY;
    float amt;
    char tran_type;
public:
    TRANSACTION()
    {
        ac=0;
        DD=0;
        MM=0;
        YY=0;
        amt=0;
        tran_type='X';
    }
    void get_time()
    {
        time_t now = time(0);
		tm *ltm = localtime(&now);
        DD=ltm->tm_mday;
        MM=ltm->tm_mon+1;
        YY=ltm->tm_year+1900;
        //cout<<DD<<MM<<YY;
        //print time
    }
    bool check_ac(int,float=0);
    void withdraw(int,float);
    void credit(int,float);
    void display();
    void interface();
};

bool TRANSACTION::check_ac(int ac,float bal)
{
    BALANCE b;
    int pos=b.chk_ac(ac);
    if(pos==-2)
    {
        //cout<<"Account unavailable!!!\n";
        return false;
    }
    if(bal==0)
    {
        //cout<<"Accoun available.\n";
        return true;
    }
    float x=b.ret_bal(ac);
    if(x>=bal) return true;
    else return false;
}
void TRANSACTION::withdraw(int a,float bal)
{
    BALANCE b;
    bool x=check_ac(a,bal);
    if(x == false)
    {
        cout<<"Cannot Withdraw.\nWrong Account number or insufficient balance.\n";
        return;
    }
    int pos=b.chk_ac(a);
    float y=b.ret_bal(a);
    b.update_bal(a,y-bal);
    fstream f;
    f.open("tran.dat",ios::app|ios::binary);
    ac=a;
    amt=bal;
    tran_type='W';
    get_time();
    f.write((char*)(&(*this)),sizeof(TRANSACTION));
    f.close();
}
void TRANSACTION::credit(int a,float bal)
{
    BALANCE b;
    cout<<1<<endl;
    bool x=check_ac(a);
    if(x==false)
    {
        cout<<"Account not available!!!\n\n";
        return ;
    }
    int pos=b.chk_ac(a);
    float y=b.ret_bal(a);
    cout<<2<<endl;
    b.update_bal(a,y+bal);
    cout<<3<<endl;
    fstream f;
    ac=a;
    amt=bal;
    tran_type='C';
    get_time();
    f.write((char*)(&(*this)),sizeof(TRANSACTION));
    f.close();
}
void TRANSACTION::display()
{
    ifstream f;
    f.open("tran.dat",ios::in|ios::binary);
    while(!f.eof())
    {
        f.read((char*)(&(*this)),sizeof(TRANSACTION));
        cout<<"A/C\t\tDate\tTrans_Type\tAmount\n";
        cout<<ac<<'\t'<<DD<<"."<<MM<<"."<<YY<<'\t'<<tran_type<<amt<<endl;
    }
    f.close();
}
void TRANSACTION::interface()
{
    BALANCE b;
    cout<<"Enter an account.\n";
    b.add_ac();
    while(1)
    {
        system("clear");
        cout<<"1.Admin.\n2.User.\n3.Exit.\n";
        int x;
        cin>>x;
    // system("clear");
        if(x==1)
        {
            while(1)
            {  
                system("clear");
                cout<<"1.Display all accounts.\n2.Display all transactions.\n3.Exit";
                int y;
                cin>>y;
                if(y==1)b.display();
                if(y==2) display();
                if(y==3) break;
                cout<<"\nPress any digit to continue.\n";
                cin>>y;
            }
        }
        if(x==2)
        {
            while(1)
            {
                system("clear");
                cout<<"1.Add an account.\n2.Withdraw an amount.\n3.Add money to an account.\n4.Exit";
                int y;
                cin>>y;
                if(y==1) b.add_ac();
                if(y==2)
                {
                    int a,b;
                    cout<<"A/C:";
                    cin>>a;
                    cout<<"Amount:";
                    cin>>b;
                    withdraw(a,b);
                }
                if(y==3)
                {
                    int a,b;
                    cout<<"A/C:";
                    cin>>a;
                    cout<<"Amount:";
                    cin>>b;
                    credit(a,b);   
                }
                if(y==4) break;
                cout<<"\nPress any digit to continue.\n";
                cin>>y;
            }
        }
        if(x==3) return;
    }
}
int main()
{
    TRANSACTION t;
    t.interface();
    return 0;
}