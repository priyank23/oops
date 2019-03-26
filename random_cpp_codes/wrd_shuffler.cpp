#include<iostream>
#include<string>
using namespace std;
void swap(char *a,char *b)
{
	char temp=*a;
	*a=*b;
	*b=temp;
}
void shuffle(string s,int l,int *cnt)
{
	if(l==1)
		{
		cout<<s<<endl;*cnt=*cnt+1;}
	else
	{
		for(int i=0;i<l;i++)
		{
			shuffle(s,l-1,cnt);
			swap(&s[l-1],&s[i]);
		}
	}
}
int main()
{
	int t;
	cin>>t;
	string s;
	while(t--)
	{
		int count=0;
		cin>>s;
		cout<<endl;
		int l=s.length();
		shuffle(s,l,&count);
		cout<<count<<"\n\n";
	}
	return 0;
}
