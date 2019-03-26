#include<iostream>
#include<cstring>
#include<bits/stdc++.h>
using namespace std;

class item
{
    string code,name;
    float price;
    int quan;
public:
    void get_item();
    void disp_item();
    void set_price(float pr);
    string get_name()
    {
    	return name;
    }
    string get_code()
    {
    	return code;
    }
    float ret_price()
    {
    	return price;
    }
    int ret_qty()
    {
    	return quan;
    }
    void set_qty(int qty) 
    {
        quan=qty;
    }
};
//
class itemlist
{
    item l1[100];
    int n_items;
public:
    itemlist(int n=0)
    {
        n_items=n;
    }
	int get_num(int n)
	{
		n_items=n;
	}
    int find_code(string temp)
    {
        for(int i=0;i<n_items;i++)
        {
            if(temp.compare(l1[i].get_code())==0)
                return i;
        }
        return -1;
    }
    void prepare_list();
    void update_list();
    void disp_list();
    friend class orderline;
	friend class order;
};
//
class orderline
{
    string code;
    int slno;
    int quan;
public:
    orderline()
    {
        quan=0;
        slno=-1;
    }
    int get_item(itemlist&);
    void ret_code(string,itemlist&);
    int get_qty(itemlist&);
	int ret_qty()
	{
		return quan;
	}
	string get_code()
	{
		return code;
	}
};
//
class order
{
    int n_items;
    orderline list[10];
public:
    order()
    {
        n_items=0;
    }
	void display_bill(itemlist&);
    void collect_order(itemlist &l1)
    {
		l1.disp_list();
		int chk;
        cout<<"Enter the number of items you want to buy.\n";
        cin>>n_items;
        for(int i=0;i<n_items;i++)
        {
        	chk=list[i].get_item(l1);
			if(chk==-1)
			{
				i--;
				cout<<"Enter again.\n";
			}
        }
    }
    void create_bill(itemlist&);
    void update_list(itemlist&);
};

class Sales_interface
{
	string pass="1234";
	itemlist list1;
public:
	void access_panel();
	void Admin();
	void User();
};
//class item member function
void item::get_item()
{
    cout<<"CODE:";
    cin>>code;
    cout<<"NAME:";
    cin>>name;
    cout<<"QUANTITY:";
    cin>>quan;
    cout<<"PRICE:";
    float pr;
    cin>>pr;
    set_price(pr);
}
void item::disp_item()
{
    cout<<"Item code:"<<code<<endl;
    cout<<"Item Name:"<<name<<endl;
    cout<<"Price:"<<price<<endl;
}
void item::set_price(float pr)
{
    price=pr;
}
//class itemlist member functions
void itemlist::prepare_list()
{
    int j=0;
    for(int i=0;i<n_items;i++)
    {
		cout<<endl;
        item temp;
		cout<<"ITEM "<<i+1<<endl;
        temp.get_item();
        int k=find_code(temp.get_code());
        if(k==-1) {l1[j]=temp;j++;}
        else l1[k].set_qty(temp.ret_qty());
    }
}
void itemlist::update_list()
{
	int ch,k,sl;
	string s;
	cout<<"1.Add an Item.\n2.Update existing stock.\n";
	cin>>ch;
	item temp;
	switch(ch)
	{
	case 1:
		//n_items++;
		temp.get_item();
		k=find_code(temp.get_code());
		if(k==-1) l1[n_items++]=temp; 
		else cout<<"Item already exists.\n";
		break;
	case 2:
		cout<<"Enter the item_code to be updated:";
		cin>>s;
		sl=find_code(s);
		if(sl==-1)
		{
			cout<<"Item does not exist\n";
			return;
		}
		cout<<"Item Code:"<<l1[sl].get_code()<<endl;
		cout<<"Item Name:"<<l1[sl].get_name()<<endl;
		cout<<"Quantity:"<<l1[sl].ret_qty()<<endl;
		cout<<"Price:"<<l1[sl].ret_price()<<endl;
		cout<<"\nEnter new stock's quantity.";
		int qn;
		float pr;
		cin>>qn;
		l1[sl].set_qty(qn);
		cout<<"Enter new price:";
		cin>>pr;
		l1[sl].set_price(pr);
		break;
	case 3: cout<<"Wrong choice!!!";
			break;
	}
}
void itemlist::disp_list()
{
	cout<<"Sl.No.\tItem Code\tName\t\tQuan.\tPrice\n\n";
	for(int i=0;i<n_items;i++)
	{
		cout<<i+1<<"\t"<<l1[i].get_code()<<'\t'<<'\t'<<l1[i].get_name()<<'\t'<<'\t'<<l1[i].ret_qty()<<'\t'<<l1[i].ret_price()<<endl;
	}
}
//class orderline member functions
int orderline::get_item(itemlist& l1)
{
    string nm;
    cout<<"Enter the item:";
    cin>>nm;
    ret_code(nm,l1);
    if(code.empty()){ 
		cout<<"Item with that name does not exist!!\n";
		return -1;
	}
	else
	{
		int q;
		q=get_qty(l1);
		if(q==-1){ 
			cout<<"Not in Stock!!";
			return -1;
		}
		else quan=q;
		return 0;
	}
}
void orderline::ret_code(string nm,itemlist& l1)
{
    for(int i=0;i<l1.n_items;i++)
    {
        if(nm.compare(l1.l1[i].get_name())==0) 
        {
            slno=i;
            code= l1.l1[i].get_code();
        }
    }
    return;
}
int orderline::get_qty(itemlist& l1)
{
	int qn;
    if(code.empty()) return 0;
    cout<<"Enter quantity:";
    cin>>qn;
    if(l1.l1[slno].ret_qty() >= qn) return qn;
    else return -1;
}
//class order member functions
void order::create_bill(itemlist &l1)
{
	cout<<"Sl.No.\tItem Code\tName\tQuan.\tPrice\tAmount\n\n";
	float amount[n_items];
	for(int i=0;i<n_items;i++)
	{
		int n=l1.find_code(list[i].get_code());
		amount[i]=l1.l1[n].ret_price()*list[i].ret_qty();
		cout<<i+1<<"\t"<<list[i].get_code()<<'\t'<<'\t'<<l1.l1[n].get_name()<<'\t'<<list[i].ret_qty()<<'\t'<<l1.l1[n].ret_price()<<'\t'<<amount[i]<<endl;
	}
	cout<<"You want to purchase?[y/n]\n";
	char c;
	cin>>c;
	if(c=='y') update_list(l1);
}
void order::display_bill(itemlist &l1)
{
	cout<<"Sl.No.\tItem Code\tName\t\tQuan.\tPrice\tAmount\n\n";
	float amount[n_items];
	float sum=0;
	for(int i=0;i<n_items;i++)
	{
		int n=l1.find_code(list[i].get_code());
		amount[i]=l1.l1[n].ret_price()*list[i].ret_qty();
		sum+=amount[i];
		cout<<i+1<<"\t"<<list[i].get_code()<<'\t'<<'\t'<<l1.l1[n].get_name()<<'\t'<<'\t'<<list[i].ret_qty()<<'\t'<<l1.l1[n].ret_price()<<'\t'<<amount[i]<<endl;
	}
	cout<<endl<<"--------------------------------------------------\n\t\t\t\t\t\t\t\t\t\t\t\t\tTotal:\t\t"<<sum<<endl<<endl;
}
void order::update_list(itemlist &l1)
{
	for(int i=0;i<n_items;i++)
	{
		int n=l1.find_code(list[i].get_code());
		l1.l1[n].set_qty(l1.l1[n].ret_qty()-list[i].ret_qty());
	//	cout<<"\t"<<l1.l1[n].get_code()<<'\t'<<'\t'<<l1.l1[n].get_name()<<'\t'<<l1.l1[n].ret_qty()<<'\t'<<l1.l1[n].ret_price()<<endl;
	//	cout<<"\t"<<list[i].get_code()<<'\t'<<'\t'<<l1.l1[n].get_name()<<'\t'<<list[i].ret_qty()<<'\t'<<l1.l1[n].ret_price()<<endl;
	}
}
//class Sales_interface member functions
void Sales_interface::Admin()
{
	int choice;
	char ch;
	int x=0;
	while(1)
	{
	cout<<"\n1.Prepare the list.\n2.Update the list.\n3.See the list.\n4.Exit.\n";
	cin>>choice;
	switch(choice)
	{
		case 1:
			cout<<"Caution!!Doing this will remove the previously stored list.\nDo you want to continue?[y/n]";
			cin>>ch;
			if(ch=='n') break;
			cout<<"\nEnter the number of items to be in the list:";
			cin>>x;
			list1.get_num(x);
			list1.prepare_list();
			break;
		case 2:
			list1.update_list();
			break;
		case 3:
			list1.disp_list();
			break;
		case 4:
			return;
	}
	}
}
void Sales_interface::User()
{
	char ch='y';
	while(ch=='y')
	{
		order o;
		o.collect_order(list1);
		o.create_bill(list1);
		ch='n';
		o.display_bill(list1);
		cout<<"Want to order again?[y/n]";
		cin>>ch;
	}
}
void Sales_interface::access_panel()
{
	int choice;
	string pswd;
	while(1)
	{
		cout<<"Enter the mode of access.\n\n1.Admin.\n2.User.\n3.Exit\n";
		cin>>choice;
		switch(choice)
		{
			case 1:
				cout<<"Enter the password:";
				cin>>pswd;
				if(pswd.compare(pass)==0)
				Admin();
				else cout<<"Wrong Password!!!\n\n";
				break;
			case 2:
				User();
				break;
			case 3:
				return;
		}
	}
}
int main()
{
	Sales_interface s1;
	s1.access_panel();
	return 0;
}