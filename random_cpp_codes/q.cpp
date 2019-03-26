#include<iostream>
#include<stdlib.h>
using namespace std;
typedef struct node{
	int data;
	struct node *next;
}node;
typedef struct queue{
	node *front,*rear;
}queue;
queue* createQueue(){
	queue *temp=new queue;
	temp->front=new node;
	temp->rear=new node;
	temp->front=NULL;
	temp->rear=NULL;
	return temp;
}
void enqueue(queue *q,int data){
	node *temp = new node;
	temp->data=data;
	temp->next=NULL;
	if(q->rear) q->rear->next=temp;
	q->rear=temp;
	if(q->front==NULL) q->front=q->rear;
	
}
void deque(queue *q){
	if(q->front==NULL) {
		cout<<"queue is empty"<<endl;
		return;
	}
	node *t=q->front;
	q->front=q->front->next;
	cout<<t->data<<endl;
	delete t;
}
int main()
{
	queue *q=createQueue();
	int x;
	while(cin>>x){
		enqueue(q,x);
	}
	while(q->front!=NULL)
	 deque(q);
	return 0;
}
