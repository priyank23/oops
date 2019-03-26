#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
void swap(int *x,int *y)
{
	int temp=*x;
	*x=*y;
	*y=temp;
}
void cut(int pos[][4],int pla,int p)
{
	pos[pla][p]=-1;
	for(int i=p;i<3;i++)
	{
		if(pos[pla][i]!=-1)
			swap(&pos[pla][i],&pos[pla][p]);
	}
}
int search(int a[],int l,int u,int val)
{
	if(l<=u)
	{
		int m=(l+u)/2;
		if(a[m]==val) return 1;
		if(a[m]<val) search(a,m+1,u,val);
		else search(a,l,m-1,val);
	}
	return 0;
}
int roll(int n)
{
	srand(time(0));
	n+=1+rand()%6;
	cout<<n;
	if(n%6==0)
	{
		if(n%18==0)
			n=0;
		roll(n);
	}
	else return n;
}
int chance(int pos[][4],int p)
{
	int safe[]={0,8,13,21,26,34,39,47,51,52,53,54,55,56};
	int turn = roll(0);
	cout<<endl<<turn/6<<"sixes and "<<turn%6;
	char a='F';
	int n_six=turn/6,sum=0;
	for(int i=0;i<=3;i++)
	{
		sum+=pos[p-1][i];
	}
	if(sum==-4 && n_six==0) return 0;  //if no 6 comes until you start
	else if(sum==-4 &&n_six>0)
	{
		pos[p-1][0]=0;
		n_six--;
		turn-=6;
	}
	if(n_six>1)                //if more than 1 six comes and some pawn is locked,one six will be used to unlock the pawn
	for(int i=0;i<=3;i++)  
		if(pos[p-1][i]==-1){
			n_six--;
			turn-=6;
			pos[p-1][i]=0;
		}
	for(int i=0;i<=3;i++)  //1st priority:locking other opponent's pawn
	{
		for(int j=0;j<=3|| pos[p-1][j]==-1;j++)
		{
			int n=pos[p%2][i]-pos[p-1][j]-26;
			if(n>0&&n==turn && !search(safe,0,13,pos[p%2][i])){
				pos[p-1][j]+=turn;
				turn=0;
				cut(pos,p%2,i);
				a='T';
			}
			else if(n<turn && n_six!=0 && !search(safe,0,13,pos[p%2][i])){
				if(n==6){
				pos[p-1][j]+=6;
				turn-=6;
				n_six--;
				cut(pos,p%2,i);
				a='T';
				}
				else if(n==6 && n_six==2){
				pos[p-1][j]+=12;
				turn-=12;
				n_six=0;
				cut(pos,p%2,i);
				a='T';
				}
				else if(n==(turn%6)){
				pos[p-1][j]+=turn%6;
				turn-=(turn%6);
				cut(pos,p%2,i);
				a='T';
				}
			}
		}
	}
	for(int i=0;i<=3;i++)   //2nd priority:to safeguard our own pawns
	{
		if(pos[p-1][i]!=-1&&search(safe,0,13,pos[p-1][i]+(turn%6))){
			pos[p-1][i]+=(turn%6);
			turn-=(turn%6);
		}
		if(n_six!=0&&pos[p-1][i]!=-1&&search(safe,0,13,pos[p-1][i]+6))
		{
			pos[p-1][i]+=6;
			turn-=6;
			n_six--;
		}
	}
	for(int i=0;i<=3;i++)  //3rd priority:home
	{
		int diff=56-pos[p-1][i];
		if(diff ==turn){
			pos[p-1][i]+=turn;
			turn=0;
			a='T';
		}
		else if(diff<turn && n_six!=0){
			if(diff==6){
				pos[p-1][i]+=6;
				turn-=6;;
				a='T';
				}
				else if(diff==6 && n_six==2){
				pos[p-1][i]+=12;
				turn-=12;
				a='T';
				}
				else if(diff==(turn%6)){
				pos[p-1][i]+=turn%6;
				turn-=(turn%6);
				a='T';
		}
	}
	for(int i=0;i<=3;i++)
	{
		if(pos[p-1][i]!=56 ){
			pos[p-1][i]+=turn;
			turn=0;
		}
	}
	if(a=='T'){
		cout<<"\nOpponent got a bonus chance.\n";
		chance(pos,p);
	}
}
return 0;
}

int main()
{
	int pos[2][4],flag=0,player=0;
	char buff;
	for(int i=0;i<2;i++)
		for (int j=0;j<4;j++)	pos[i][j]=-1;
	cout<<"-------------------------LUDO(2-player)-------------------------\n\n";
	cout<<"Yours is red and opponent's is blue.\n";
	while(flag!=1)
	{
		int sl,move;
		cout<<"\nYour turn.\nEnter any character to roll the dice.\n";
		cin>>buff;
		int t=roll(0);
		cout<<"\nYou got "<<t/6<<"sixes and "<<t%6;
		cout<<"\nyour pawns are at positions ";
		for(int i=0;i<=3;i++)
		{
			cout<<pos[0][i]<<" ";
		}
		cout<<"\nYour opponent's pawns are at positions ";
		for(int i=0;i<=3;i++)
		{
			cout<<pos[1][i]<<" ";
		}
		int s=0;
		for(int i=0;i<=3;i++)
		{
			s+=pos[0][i];
		}
		if(s==-4 && t/6==0) cout<<"\nYou can not move until you get a six.\n";
		else{
		int x=0;
		while(!x){
		cout<<"Enter the serial number of the pawn you want to move and the number by which you want it to move.\n";
		cin>>sl>>move;
		if(sl<1 || sl>4 || move>t || (t/6==0)?move!=t%6:(move==6?0:move!=t%6)) {
		cout<<"INVALID MOVE!!!\n";
		}
		else{
			if(pos[0][sl-1]==-1 && move!=6) cout<<"\nYou can not move ths pawn until you use a six.\n";
			else if(pos[0][sl-1]==-1 && move==6){
				pos[0][sl-1]=0;
				t-=6;
			}
			else{
			pos[0][sl-1]+=move;
			t-=move;
			}
			if(t==0) x=1 ;
		} s=0;
		for(int i=0;i<=3;i++)
		{
			s+=pos[0][i];
		}
		if(s==56*4){
			flag=1;
			cout<<"YOU WIN.\n\n\n";
			break;
		}
		}
		cout<<"\nyour pawns are now at positions ";
		for(int i=0;i<=3;i++)
		{
			cout<<pos[0][i]<<" ";
		}
		}
		cout<<"\nOpponent's chance.\n";
		chance(pos,2);
		s=0;
		for(int i=0;i<=3;i++)
		{
			s+=pos[0][i];
		}
		if(s==56*4){
			flag=1;
			cout<<"YOU LOSE.\n\n\n";
			break;
		}
		cout<<"\nYour opponent's pawns are now at positions ";
		for(int i=0;i<=3;i++)
		{
			cout<<pos[1][i]<<" ";
		}
	}
	return 0;
}
