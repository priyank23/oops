#include<iostream>
using namespace std;

class Array
{
    int *ar;
    int len;
public:
    Array(int l=0,int val=0)
    {
        len=l;
        ar=new int[l];
        for(int i=0;i<l;i++) ar[i]=val;
    }
    Array(const Array &a)
    {
        len=a.len;
        ar=new int[len];
        for(int i=0;i<len;i++)
        {
            ar[i]=a.ar[i];
        }
    }
    Array(const int a[])
    {
        int s;
        s=a[0];
       // if(len!=0) delete[] ar;
        ar=new int[s];
        len=s;
        for(int i=0;i<s;i++)
        {
            ar[i]=a[i+1];
        }
    }
    void print()
    {
        for(int i=0;i<len;i++)
            cout<<ar[i]<<'\t';
        cout<<endl;
    }
    void operator=(Array &a)
    {
        delete[] ar;
        len=a.len;
        ar=new int[len];
        for(int i=0;i<len;i++)
        {
            ar[i]=a.ar[i];
        }
    }
    void operator=(int *a)
    {
        int s;
        s=a[0];
        if(len!=0) delete[] ar;
        len=s;
        ar=new int[s];
        for(int i=0;i<s;i++)
        {
            ar[i]=a[i+1];
        }
    }
    void operator+(Array &a)
    {
        Array temp;
        temp.len=len>a.len?len:a.len;
        if(len>=a.len)
        {
            int i;
            for(i=0;i<a.len;i++)
            {
                temp.ar[i]=ar[i]+a.ar[i];
            }
            for(;i<len;i++) temp.ar[i]=ar[i];            
        }
        else 
        {
            int i;
            for(i=0;i<len;i++)
            {
                temp.ar[i]=ar[i]+a.ar[i];
            }
            for(;i<a.len;i++) temp.ar[i]=a.ar[i];
        }
        *this=temp;
    }
    int operator[](int i)
    {
        return ar[i];
    }
    void operator*(int i)
    {
        if(len==0) return ;
        for(int j=0;j<len;j++)
        {
            ar[j]=ar[j]*i;
        }
    }
    friend void operator*(int i,Array& a);
    ~Array()
    {
        delete[] ar;
    }
};
void operator*(int i,Array& a)
{
     a*i;
}
int main()
{
    cout<<"Enter the length and initialising value for the array respectively.\n";
    int l,v;
    cin>>l>>v;
    Array A(l,v),C;
    cout<<"Object A created successfully.\n\n";
    while(1)
    {
        cout<<"Enter any digit to continue.\n";
        cin>>l;
        system("clear");
        cout<<"1.Initialize object B with A.\n2.Initialise B with an array.\n3.Read i-th element of array of A.\n4.Add B to A.\n5.Multiply an integer with A as A*i\n6.Multiply an integer with A as i*A\n7.Exit\n\nEnter your choice.\n";
        cin>>l;
        cout<<"A:";
        A.print();
        switch(l)
        {
            case 1:
            {
                Array B=A;
                C=B;
                cout<<"B:";
                B.print();
                break;
            }
            case 2:
            {
                cout<<"Enter the length of the array.\n";
                int x;
                cin>>x;
                cout<<"Enter the elements of the array.\n";
                int arr[x+1];
                arr[0]=x;
                for(int i=1;i<=x;i++) cin>>arr[i];
                Array B=arr;
                C=B;
                B.print();
                break;
            }
            case 3:
            {
                cout<<"Enter the index to be read of A.\n";
                int i;
                cin>>i;
                cout<<A[i]<<endl;
                break;
            }
            case 4:
            {
                A+C;
                cout<<"C:";
                C.print();
                cout<<"A:";
                A.print();
                break;
            }
            case 5:
            {
                cout<<"Enter the number you want to multiply the array with.\n";
                int i;
                cin>>i;
                A*i;
                cout<<"A:";
                A.print();
                break;
            }
            case 6:
            {
                cout<<"Enter the number you want to multiply the array with.\n";
                int i;
                cin>>i;
                i*A;
                cout<<"A:";
                A.print();
                break;
            }
            case 7: return 0;
        }
    }
}