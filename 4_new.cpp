#include<iostream>
#include<fstream>
#include<cstring>
#include<cmath>
#include<ctime>
#include<map>
#include<utility>
using namespace std;

class options
{
    ifstream f;
public:
    options()
    {
        f.open("4.txt",ios::in);
    }
    void show_options()
    {
        char ch;
        while(!f.eof())
        {
            f.get(ch);
            cout<<ch;
        }
    }
    ~options()
    {
        f.close();
    }
};

class student  //storing student details
{
    string roll,name;
    int dept,DD,MM,YY;
    int marks[5],grade[5],chk,pass;
    float total,sgpa;
public:
    student()
    {
        roll="XXX000";
        dept=0;
        chk=0;
        pass=1;
        total=0;
        sgpa=0;
    }
    int ret_pass() 
    {
        return pass;
    }
    void grade_s(int g)
    {
    if(g==10) cout<<"S"<<endl;
    if(g==9) cout<<"A"<<endl;
    if(g==8) cout<<"B"<<endl;
    if(g==7) cout<<"C"<<endl;
    if(g==6) cout<<"D"<<endl;
    if(g==5) cout<<"E"<<endl;
    if(g==4) cout<<"X"<<endl;
    if(g<4) {cout<<"X"<<endl;pass=0;}
    }
    void assign_roll(int dep_code,int std_no)
    {
        if(dep_code==1) roll="CSE100";
        else if(dep_code==2) roll="CHE200";
        else if(dep_code==3) roll="ELE300";
        else{
            cout<<"Error code!!\n";
            return;
        }
        roll[4]=(std_no/10)+48;
        roll[5]=(std_no%10)+48;
        cout<<"ROLL: "<<roll<<endl;
        cout<<"Date of registration: "<<DD<<"/"<<MM<<"/"<<YY<<endl;
    }
    void get_adm_date()
    {
        time_t prst=time(0);
        struct tm *ltm=localtime(&prst);
        DD=ltm->tm_mday;
        MM=ltm->tm_mon +1;
        YY=ltm->tm_year + 1900;
    }
    void set_marks()
    {
        if(chk==1)
        {
            cout<<"Input already taken!!"<<endl;
            return;
        }
        string sub[5]={"English","Maths","Socio","E.Tech","Physics"};
        cout<<"Name: "<<name<<endl<<"Enter the marks:-\n";
        for(int i=0;i<5;i++)
        {
            int a;
            cout<<sub[i]<<" :";
            cin>>a;
            while(a>100||a<0)
            {
                cout<<"Wrong Input!! Try again.\n";
                cin>>a;
            }
            marks[i]=a;
            total+=marks[i];
            grade[i]=(ceil(float(marks[i])/10));
            sgpa+=grade[i];
            if(grade[i]<4) pass=0;
        }
        chk=1;
        cout<<"Marks entered successfully.\n";
    }
    int get_student_details()
    {
        cout<<"Name:\n";
        getline(cin,name);
        if(name.size()==0) getline(cin,name);
        cout<<"Department Code:\n";
        cin>>dept;
        get_adm_date();
        return dept;
    }
    void show_stud(int i)
    {
        cout<<i<<'\t'<<'\t'<<roll<<'\t'<<name<<endl;
    }
    int ret_total()
    {
        return total;
    }
    int print_marksheet()
    {
        if(chk==0)
        {
            cout<<"Marks not entered for the student yet.\n";
            return 0;
        }
        cout<<"Name: "<<name<<"\nRoll: "<<roll<<endl;
        cout<<"------------------------------------\n";
        cout<<"Subject         Marks          Grade\n";
        string sub[5]={"English","Maths","Socio","E.Tech","Physics"};
        for(int i=0;i<5;i++)
        {
            cout<<sub[i]<<"\t   "<<marks[i]<<'\t';grade_s(grade[i]);
        }
        cout<<"------------------------------------\n";
        if(pass==1) cout<<"                    SGPA: "<<sgpa/5<<endl;
        else cout<<"                      SGPA:\n";
        cout<<"------------------------------------\n";
        return 1;
    }
};

class university
{
    map<int,student>s[3];
    student stu;
    map<int,student>p;
    int count[3]={0},chm=0;
public:
    void admin_interface();
    void admission();
    void rcv_marks();
    void marksheet();
    void stu_list();
    void uni_topper();
};
void university::admin_interface()
{
    while(1)
    {
        string s;
        int i;
        cout<<"Press any key to continue";
        cin>>i;
        system("clear");
        cout<<"Enter your choice\n1. New admission\n2. Receive marks\n3. Generate marksheet\n4. Print department list\n5.Find university topper\n6.Exit"<<endl;
        fflush(stdin);
        int ch;
        cin>>ch;
        switch(ch)
        {
            case 1:admission(); break;
            case 2:rcv_marks(); break;
            case 3:marksheet(); break;
            case 4:stu_list();break;
            case 5:uni_topper(); break;
            case 6:return;
            default: break;
        }
    }
}
void university::admission()
{
    int dep_code;
    cout<<"\t\tADMISSION ROLL\n";
    options o;
    o.show_options();
    dep_code=stu.get_student_details();
    ++count[dep_code-1];
    stu.assign_roll(dep_code,count[dep_code-1]);
    pair<map<int,student>::iterator,bool>r;
    r=s[dep_code-1].insert({count[dep_code-1],stu});
    if(r.second==false) {cout<<"Error!!";return;}
    cout<<"Admission Complete.\n";
}
void university::rcv_marks()
{
    int rl;
    cout<<"Enter last 3 digits of roll number\n";
    cin>>rl;
    int dp_code=rl/100;
    if(dp_code==0){
        cout<<"Invalid Input!!\n";
        return;
    }
    int cnt=rl%100;
    map<int,student>::iterator ptr;  //finding the student using roll number
    ptr=s[dp_code-1].find(cnt);
    ptr->second.set_marks();     //receiving marks
    int t=ptr->second.ret_total();  //calculating total
    pair<map<int,student>::iterator,bool>r; //for storing the topper of the resp. dept
    r=p.insert({dp_code-1,ptr->second});
    if(r.second==false) {    //if already exists with that dept_code
        map<int,student>::iterator ptr2;   //for finding the total of the prev. topper 
        ptr2=p.find(dp_code-1);
        if(t>ptr2->second.ret_total() && ptr2->second.ret_pass()!=0) ptr->second=ptr2->second;  //updating the topper
    }
    chm=1;
}
void university::marksheet()
{
    int rl;
    int dp_code=0;
    while(dp_code==0)
    {
    cout<<"Enter last 3 digits of roll number\n";
    cin>>rl;
    dp_code=rl/100;
    cout<<"Error Input.Try again.\n";
    }
    int cnt=rl%100;
    map<int,student>::iterator ptr;  //finding the student using roll number
    ptr=s[dp_code-1].find(cnt);
    int ch=ptr->second.print_marksheet();
    if(ch==0)
    {
        cout<<"Marks not yet entered.\nPress 1 to enter marks.\nPress any other button to return to prev menu.\n";
        int a;
        cin>>a;
        if(a==1) rcv_marks();
        else return;
    }
}
void university::stu_list()
{
    int dpt;
    cout<<"Enter Department Code\n1.CSE  2.CHE  3.ELE\n";
    cin>>dpt;
    system("clear");
    if(dpt==1) cout<<"COMPUTER SCIENCE & ENGINEERING\n";
    if(dpt==2) cout<<"CHEMICAL ENGINEERING\n";
    if(dpt==3) cout<<"ELECTRICAL ENGINEERING\n";
    map<int,student>::iterator itr;
    for(itr=s[dpt-1].begin();itr!=s[dpt-1].end();itr++)
    {
        itr->second.show_stud(itr->first);
    }
}
void university::uni_topper()
{
    int c=0;
    c=count[0]+count[1]+count[2];
    if(c==0)
    {
        cout<<"No student is admitted yet.\n";
        return;
    }
    if(chm==0)
    {
        cout<<"No student's marks is entered yet.\n";
        return;
    }
    cout<<"Enter the department code:";
    int k;
    cin>>k;
    map<int,student>::iterator ptr;
    ptr=p.find(k-1);
    ptr->second.show_stud(0);
    cout<<"Total marks= "<<ptr->second.ret_total()<<endl;
}
int main()
{
    university u;
    u.admin_interface();
    return 0;
}