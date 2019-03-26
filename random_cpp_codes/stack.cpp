#include<iostream>
#include<stdlib.h>
using namespace std;
typedef struct listNode{
	int data;
	struct listNode *next;
} stack;
stack* createStack(){
	return NULL;
}
void display(stack *top){
	stack* temp=top;
	while(temp)
	{
		cout<<temp->data<<endl;
		temp=temp->next;
	}
}
void push(stack **top,int data){
	stack* temp;
	temp=new stack;
	temp->data=data;
	temp->next=*top;
	*top=temp;
}
void pop(stack **top)
{
	if(top==NULL) {
	cout<<"Stack is empty"<<endl;
	return;
	}
	cout<<(*top)->data<<endl;
	stack *temp = *top;
	*top=(*top)->next;
	delete temp;
}
int main()
{
	stack *s=createStack();
	int x;
	while(cin>>x){
		push(&s,x);
	}
	display(s);
	pop(&s);
	display(s);
	return 0;
}
