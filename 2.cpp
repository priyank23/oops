#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;

class complex{
    int real,im;
public:
    friend istream& operator >>(istream&,complex&);
    friend ostream& operator <<(ostream&,complex);
    complex(int r=0,int i=0)
    {
        real=r;
        im=i;
    }
    complex operator +(complex c)
    {
        complex temp;
        temp.real=real+c.real;
        temp.im=im+c.im;
        return temp;
    }
    complex operator -(complex c)
    {
        complex temp;
        temp.real=real-c.real;
        temp.im=im-c.im;
        return temp;
    }
};

istream& operator >>(istream& i,complex& c)
{
    string s;
    i>>s;
    c.real=0;
    c.im=0;
    int flag=0,neg=0,negi=0,num=0,tag=0;
    if(s[0]=='-')
    {
        s=s.substr(1,s.length());
        neg=1;
    }
    for(int i=0;i<s.length();i++)
    {
        if(s[i]=='+' || s[i]=='-')
        {
            flag=1;
            tag=i;
            if(s[i]=='-') negi=1;
            num=0;
        }
        else if(s[i]=='i')
        {
            if(flag==0)
            {
                negi=neg;
                c.im=c.real;
                c.real=0;
            }
            break;
        }
        else
        {
            if(flag == 0)
            {
                num=num*pow(10,i)+(s[i]-48);
                c.real=num;
            }
            if(flag == 1)
            {
                num=num*pow(10,i-tag-1)+(s[i]-48);
                c.im=num;
            }
        }
        if(neg==1) c.real=-1*c.real;
        if(negi==1) c.im=-1*c.im;
    }
    return i;
}

ostream& operator <<(ostream& o,complex c)
{
    cout<<c.real;
    if(c.im<0) cout<<"-";
    else cout<<"+";
    cout<<fabs(c.im)<<"i";
    return o;
}

int main()
{
    complex c1,c2,c3;
    int ch;
    cout<<"Enter any complex number in (a+bi) format.\n";
    cin>>c1;
    while(1)
    {
        cout<<"Choose any one of the following options.\n";
        cout<<"1. Enter new complex number.\n2. Display the presently stored number.\n3. Add another complex number.\n4. Subtract two complex numbers.\n5. Exit.\n";
        cin>>ch;
        switch(ch)
        {
            case 1:
                cin>>c1;
                break;
            case 2:
                cout<<c1;
                break;
            case 3:
                cout<<"Enter the number to be added with the currently stored number.\n";
                cin>>c2;
                c3=c1+c2;
                cout<<"The resultant sum is "<<c3<<endl;
                break;
            case 4:
                cout<<"Enter the number to be subtracted from the currently stored nummber.\n";
                cin>>c2;
                c3=c1-c2;
                cout<<"The resultant difference is "<<c3<<endl;
                break;
            case 5:
                return 0;
            default:
                cout<<"Error input!!!.\n";
                break;
        }
    }
    return 0;
}