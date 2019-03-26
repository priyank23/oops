#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
using namespace std;

class String
{
    char *ch;
    int *cp;
public:
    String(int l=0)
    {
        ch=new char[l+1];
        cp=NULL;
    }
    String(char *ch2)
    {
        int l=strlen(ch2);
        ch=new char[l+1];
        strcpy(ch,ch2);
        cp=new int;
        *cp=1;
    }
    String(String& S)
    {
        cp=new int;
        cp=S.ret_cp();
        int l=strlen(S.ret_str());
        ch=new char[l+1];
        ch=S.ret_str();
        (*cp)++;
    }
    void operator=(char *ch2)
    {
        (*cp)--;
        cp=new int;
        *cp=1;
        if(strlen(ch)!=0) delete[] ch;
        int l=strlen(ch2);
        ch=new char[l+1];
        strcpy(ch,ch2);
    }
    void operator=(String& S)
    {
        if(cp!=NULL) (*cp)--;
        cp=new int;
        cp=S.ret_cp();
        (*cp)++;
        if(strlen(ch)!=0) delete[] ch;
        int l=strlen(S.ret_str());
        ch=new char[l+1];
        ch=S.ret_str();
    }
    void operator+(String& S)
    {
        strcat(ch,S.ret_str());
    }
    int operator==(String& S)
    {
        int i=strcmp(ch,S.ret_str());
        if(i==0) return 1;
        else return 0;
    }
    int operator>(String& S)
    {
        int i=strcmp(ch,S.ret_str());
        if(i>0) return 1;
        else return 0;
    }
    int operator<(String& S)
    {
        int i=strcmp(ch,S.ret_str());
        if(i<0) return 1;
        else return 0;
    }
    int operator>=(String& S)
    {
        int i=strcmp(ch,S.ret_str());
        if(i>=0) return 1;
        else return 0;
    }
    int operator<=(String& S)
    {
        int i=strcmp(ch,S.ret_str());
        if(i<=0) return 1;
        else return 0;
    }
    char* ret_str()
    {
        return ch;
    }
    int* ret_cp()
    {
        return cp;
    }
    void print()
    {
        cout<<ch<<endl;
    }
    ~String(){
        if(!(--(*cp)))
        {
            delete cp;
            delete[] ch; 
        }
    }
};
int main()
{
    cout<<"Enter the initialising string.\n";
    char ch[20];
    //cin.getline();
    cin.getline(ch,20);
 //   cout<<"1";
    String S(ch),U;
    cout<<"Object S created successfully.\n\n";
    while(1)
    {
        int l;
        cout<<"Enter any digit to continue.\n";
        cin>>l;
        system("clear");
        cout<<"1.Initialize object T with S.\n2.Initialise T with a string.\n3.concatenate T to S.\n4.Compare S with a given String C.\n5.See count\n6.Exit\n\nEnter your choice.\n";
        cin>>l;
        cout<<"S:";
        S.print();
      //  cout<<0;
        switch(l)
        {
            case 1:
            {
                cout<<1;
                String T(S);
                cout<<2;
                U=S;
                cout<<"T:";
                T.print();
                break;
            }
            case 2:
            {
                cout<<"Enter the string.\n";
                cin>>ch;
                String T(ch);
                U=T;
                T.print();
                break;
            }
            case 3:
            {
                S+U;
                cout<<"Contatenated string.\nS:";
                S.print();
                break;
            }
            case 4:
            {
                cout<<"Enter the string to compare with S.\n";
                cin>>ch;
                String C(ch);
                if(C>=S)
                {
                    if(C>S)
                    {
                        cout<<"C is greater than S.\n";
                        break;
                    }
                    if(C==S)
                    {
                        cout<<"C is equal to S.\n";
                        break;
                    }
                }
                else if(C<=S)
                {
                    if(C<S)
                    {
                        cout<<"C is less than S.\n";
                        break;
                    }
                    if(C==S)
                    {
                        cout<<"C is equal to S.\n";
                        break;
                    }
                }
            }
            case 5:{
                cout<<*S.ret_cp()<<endl;
                String A(S);
                cout<<*S.ret_cp()<<'\t'<<*A.ret_cp();
                String B(S);
                cout<<*S.ret_cp()<<'\t'<<*B.ret_cp(); 
                break;
            }
            case 6:
                cout<<*S.ret_cp()<<endl;
                return 0;
        }
    }
    return 0;
}