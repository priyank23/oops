#include<iostream>
using namespace std;
typedef struct AVL{
	int data;
	int h;
	struct AVL *left,*right;
}avl;
avl *createavl(){
	return NULL;
}
avl* rotate_right(avl *t){    //right rotation
	avl* temp;
	temp=t->left;
	t->left=temp->right;
	temp->right=t;
	return temp;
}
avl* rotate_left(avl *t){     //left rotation
	avl* temp;
	temp=t->right;
	t->right=temp->left;
	temp->left=t;
	return temp;
}
avl* insertion(avl *root,int data){
	if(root==NULL){
		root=new avl;
		root->data=data;
		root->left=NULL;
		root->right=NULL;
		root->h=0;
		return root;
	}
	if(root->data<data){        
		root->h--;
		root->right=insertion(root->right,data);
//		root->h=((root->left)->h)-((root->right)->h);
		if(root->h>1) root=rotate_right(root);
		else if(root->h<-1) root=rotate_left(root);
		else if(root->data<-1) root=rotate_left(root);
		if(root->h>1 && (root->left->h<-1 || root->right->h<-1)){   //LR double rotation
			if(root->left->h<-1)	root->left=rotate_left(root->left);
			if(root->right->h<-1)	root->right=rotate_left(root->right);
			root=rotate_right(root);
		} 
		if(root->h<-1 && (root->left->h>1 || root->right->h>1)){    //RL double rotation
		if(root->left->h>1)	root->left=rotate_right(root->left);
		if(root->right->h>1)	root->right=rotate_right(root->right);
			root=rotate_left(root);
		}
		return root;
	}
	else{
		root->h++;
		root->left=insertion(root->left,data);
	//	root->h=((root->left)->h)-((root->right)->h);
		if(root->h>1) root=rotate_right(root);
		else if(root->h<-1) root=rotate_left(root);
		else if(root->data<-1) root=rotate_left(root);
		if(root->h>1 && (root->left->h<-1 || root->right->h<-1)){
			if(root->left->h<-1)	root->left=rotate_left(root->left);
			if(root->right->h<-1)	root->right=rotate_left(root->right);
			root=rotate_right(root);
		}
		if(root->h<-1 && (root->left->h>1 || root->right->h>1)){
		if(root->left->h>1)	root->left=rotate_right(root->left);
		if(root->right->h>1)	root->right=rotate_left(root->right);
			root=rotate_left(root);
		}
		return root;
	}
	return root;
}
int main(){
	avl *root=createavl();
	int x;
	while(cin>>x){
		root=insertion(root,x);
	}
	return 0;
}


