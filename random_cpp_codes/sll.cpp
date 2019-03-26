/*Program to create a linked list,print a list,finding the length of the list,reverse a list using iteration and recursive methods and insert in a list*/
#include<iostream>
#include<stdlib.h>
using namespace std;
struct node{                              //making of the list
	int data;
	struct node *next;
};
int listLength(struct node *p)           //finding the length of the list
{
	int l=0;
	while(p!=NULL)
	{
		l++;
		p=p->next;
	}
	return l;
}
 void insertList(struct node **head,int pos,int val,int l)    //inserting a node on the list
{
	if(pos>l+1)                                               //checking for improper input
		cout<<"Memory Error!!!\n";
	else
	{
		struct node *temp;
		if(pos==1)                                            //inserting in the beginning
		{
			temp= new node[0];
			temp->data=val;
			temp->next=*head;
			*head=temp;
		}
		else if(pos==l+1)                                    //inserting at the end
		{
			struct node *cur=NULL;
			cur=*head;
			while(cur->next!=NULL)
			{
				cur=cur->next;
			}
			temp= new node[0];
			temp->data=val;
			temp->next=NULL;
			cur->next=temp;
		}
		else                                                //inserting in the middle
		{
			struct node *cur=*head;
			int cnt=1;
			while(cnt<pos-1)
			{
				cur=cur->next;cnt++;
			}
			temp= new node[0];
			struct node *temp2=NULL;
			temp->data=val;
			temp->next=NULL;
			temp2=cur->next;
			cur->next=temp;
			temp->next=temp2;
		}
	}	
}
void printList(struct node *p)				//function to print the list
{
	if(p==NULL)								//checking if list is empty or not
		cout<<"Memory Error!!!"<<endl;
	else									//if list is non-empty, printing begins
		{
			cout<<"The list is:\n";
			while(p!=NULL)
			{
			cout<<p->data<<endl;
			p=p->next;
			}
		}
}

struct node *reverseList2(struct node *after)			//for reversing the list using iteration method
{
	if(after==NULL || after->next==NULL) return after;
	struct node *prev=after,*p=NULL;
	after=after->next;
	prev->next=NULL;
	p=after;
	after=after->next;
	while(after->next!=NULL)
	{
		p->next=prev;
		prev=p;
		p=after;
		after=after->next;
	}
	p->next=prev;
	after->next=p;
	return after;
}
struct node *reverseList(struct node *p,struct node *q,struct node *head)	//reversing the list using recursive method
{
	if(p==NULL) return p;      
	if(p->next==NULL)						
	{
		q->next=NULL;
		p->next=q;
		head=p;
		return head;
	}
	else
	{
		q=p;
		p=p->next;
		head=reverseList(p,q,head);
		if(q!=NULL)
		q->next=NULL;
		p->next=q;
		return head;
	}
}
int main()
{
	struct node *head=NULL,*cur=NULL,*temp=NULL;
	head= (struct node*)malloc(sizeof(struct node));
	int val;
	cout<<"Enter the values of the list(-1 to terminate).\n";
	cin>>val;
	if(val!=-1)
	{
		head->data=val;
		head->next=NULL;
	}
	cur=head;
	if(val!=-1){
	while(1)
	{
	    temp= (struct node*)malloc(sizeof(struct node));
		cin>>val;
		if(val!=-1){
		temp->data=val;
		temp->next=NULL;
		cur->next=temp;
		cur=cur->next;
		}
		else break;
	}
	temp=temp->next;}
	printList(head);
	struct node *rhead=NULL,*rhead2=NULL;
	cout<<"\nAfter reversing:- ";
	rhead=reverseList(head,temp,rhead);       //reversing the list(recursive method)
	printList(rhead);
	rhead2=reverseList2(rhead);				  //reversing the list(iterative method)
	cout<<"\nAfter reversing again:- ";
	printList(rhead2);
	int l=listLength(head);                   //finding the length of the list
	cout<<"\nThe length of the list is:"<<l<<endl;
	cout<<"\nWant to insert new data in the list? (Y/N)\n";
	char ch;
	cin>>ch;
	if(ch=='Y')
	{
		int pos;
		cout<<"Enter the position from the beginning and the data to be inserted.\n";
		cin>>pos>>val;                        //taking input for insertion in the list
		insertList(&rhead2,pos,val,l);        //inserting in the list
	cout<<"\nAfter inserting:- ";}
	printList(rhead2);                        //final list
	return 0;
}
