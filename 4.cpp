#include <iostream>
#include <cstring>
#include <cmath>
#include <ctime>
using namespace std;

void option_list()
{
    cout    <<"------------------------------------------------------------------"<<endl;
    cout    <<"Department      Subjects Code\n"
            <<"                1. English  2. Maths 3. Sociology\n"
            <<"01. CSE         4. Etech    5. Physics     \n"
            <<"02. CHE       \n"
            <<"03. ELE          \n";
    cout    <<"------------------------------------------------------------------"<<endl;
    
}
void print_department(int a)
{
    if (a==1) cout <<" Computer Sc. & Engineering";
    if (a==2) cout <<" Chemical Engineering";
    if (a==3) cout <<" Electrical Engineering";
}
void grade(int g)
{
    if(g==10) cout<<"S"<<endl;
    if(g==9) cout<<"A"<<endl;
    if(g==8) cout<<"B"<<endl;
    if(g==7) cout<<"C"<<endl;
    if(g==6) cout<<"D"<<endl;
    if(g==5) cout<<"E"<<endl;
    if(g==4) cout<<"X"<<endl;
    if(g<4) cout<<"X"<<endl;
}
class student
{
    string roll="XXX000";
    string name;
    int dept;
    int DD,MM,YY;
    int marks[5];
    int sub_grade[5];
    float total=0;
    int check=0;
    int pass=1;
    float sgpa=0;
public:
    void generate_roll(int a, int b)
    {
        if (a==1)
            roll="CSE100";
        if (a==2)
            roll="CHE200";
        if (a==3)
            roll="ELE300";
        roll[4]=(b/10)+48;
        roll[5]=(b%10)+48;
        cout<<"Roll Number assigned ="<<roll<<endl;
        cout<<"Date of admission registered:"<<DD<<"/"<<MM<<"/"<<YY<<endl;
    }
    void get_adm_time()
    {
        time_t now = time(0);
		tm *ltm = localtime(&now);
        DD=ltm->tm_mday;
        MM=ltm->tm_mon+1;
        YY=ltm->tm_year+1900;
        //cout<<DD<<MM<<YY;
        //print time
    }
    void get_marks()
    {
        if(check==1)
        {
            cout<<"Marks already input"<<endl;
            return ;
        }
        int a;
        cout<<"Name : "<<name<<endl;
        cout<<"Enter the marks :-"<<endl;
        cout<<"English   : ";
        //cin>>marks[0];
        cin >>a;
        while(a>100||a<0)
        {
            cout<<"Check input.Try again\n";
            cin>>a;
        
        }
        marks[0]=a;
        cout<<"Maths     : ";
        //cin>>marks[1];
        cin >>a;
        while(a>100||a<0)
        {
            cout<<"Check input.Try again\n";
            cin>>a;
        
        }
        marks[1]=a;
        cout<<"Sociology : ";
        //cin>>marks[2];
        cin >>a;
        while(a>100||a<0)
        {
            cout<<"Check input.Try again\n";
            cin>>a;
        
        }
        marks[2]=a;
        cout<<"E.Tech    : ";
        //cin>>marks[3];
        cin >>a;
        while(a>100||a<0)
        {
            cout<<"Check input.Try again\n";
            cin>>a;
        }
        marks[3]=a;
        cout<<"Physics   : ";
        //cin>>marks[4];
        cin >>a;
        while(a>100||a<0)
        {
            cout<<"Check input.Try again\n";
            cin>>a;
        
        }
        marks[4]=a;
        for(int i=0;i<5;i++)
        {
            total+=marks[i];
            sub_grade[i]=(ceil(float(marks[i])/10));
            sgpa+=sub_grade[i];
            if(sub_grade[i]<5)
                pass=0;
        };
        check=1;
        cout<<"Marks successfully updated"<<endl;        
    
    }
    int get_adm_details()
    {
        cout<<"Enter name student\n";

        getline(cin,name);
        if(name.size() == 0) getline(cin,name);
        cout<<name<<endl;
        cout<<"Enter department code\n ";
        cin>>dept;
        get_adm_time();
        return dept;
    }
    void show_student( int i)
    {
        cout<<i<<"\t"<<"\t"<<roll<<"\t";
        cout<<name<<endl;
    }
    int send_total()
    {
        return total;
    }
    int marksheet()
    {
        if (check!=1)
            return 0;
        
        cout<<"Name : "<<name<<"\nRoll :"<<roll<<endl;
        cout<<"-------------------------------------"<<endl;
        cout<<"Subject           Marks      : Grade"<<endl;
        cout<<"-------------------------------------"<<endl;
        cout<<"English      :   "<<marks[0]<<"\t";
        grade(sub_grade[0]);
        cout<<"Maths        :   "<<marks[1]<<"\t";
        grade(sub_grade[1]);
        cout<<"Sociology    :   "<<marks[2]<<"\t";
        grade(sub_grade[2]);
        cout<<"E.Tech       :   "<<marks[3]<<"\t";
        grade(sub_grade[3]);
        cout<<"Physics      :   "<<marks[4]<<"\t";
        grade(sub_grade[4]);
        cout<<"-------------------------------------"<<endl;
        if(pass==1)
            cout<<"SGPA         :"<<sgpa/5<<endl;
        else
            cout<<"SGPA         :"<<endl;
        cout<<"-------------------------------------"<<endl;
        return 1;
        
    }
};

class university
{
    student sroll[30];
    int dept[4][13];    //column 0 stores count //column 1 to 10 stores student // column 11 stores topper //12 stores topper marks
    int count=0;
    int ch5=0;

public:
  
    void admin_interface()
    {
        dept[0][0]=0;
        dept[1][0]=0;
        dept[2][0]=0;
        dept[3][0]=0;
        dept[0][12]=0;
        dept[1][12]=0;
        dept[2][12]=0;
        dept[3][12]=0; 
        dept[0][11]=0;
        dept[1][11]=0;
        dept[2][11]=0;
        dept[3][11]=0;
        while(1)
        {
            int i;
            cout<<"Press 1 to continue";
            cin>>i;
            system("clear");
            int choice;
            cout<<"Enter\n1. To take new admission\n2. Recieve marks\n3. Generate marksheet\n4. Print department list\n5. Find university topper\n6. To exit session"<<endl;
            cin>>choice;
            switch(choice)
            {
                case 1: admission();break;
                case 2: recieve_mark();break;
                case 3: gen_marksheet();break;
                case 4: print_dept_sheet();break;
                case 5: uni_topper();break;
                case 6: return;
                default:break;
            }
        }
    };
    void admission()
    {
        student s;
        int dcode;
        cout<<"\t\tADMISSION ROLL"<<endl;
        option_list();
        dcode=s.get_adm_details();
        dept[dcode][0]++;
        dept[0][0]=dept[1][0]+dept[2][0]+dept[3][0];
        s.generate_roll(dcode,dept[dcode][0]);
        count++;
        sroll[count]=s;
        dept[dcode][dept[dcode][0]]=count;
        cout<<"Admission Complete\n";

    };
    void recieve_mark()
    {
        int rx;
        cout<<"Enter the last 3 digits of roll number"<<endl;
        cin>>rx;
        int a,b;
    
        a=rx/100;
        b=rx%100;
        sroll[dept[a][b]].get_marks();

        int t;
        t=sroll[dept[a][b]].send_total();
        if(t>dept[a][12])
        {
            dept[a][12]=t;
            dept[a][11]=dept[a][b];
            if(t>dept[0][12])
            {
                dept[0][12]=t;
                dept[0][11]=dept[a][b];
                ch5=1;
            }
        }
    };
    void gen_marksheet()
    {
        int c,rx;
            cout<<"Enter the last 3 digits of roll number"<<endl;
            cin>>rx;
        int a,b;
        a=rx/100;
        b=rx%100;
        c=sroll[dept[a][b]].marksheet();
        if(c==0)
        {
            cout<<"Marks not yet input."<<endl;
            cout<<"Press 1 to enter marks \n Press 0 to return to the previous menu"<<endl;
            int q;
            cin>>q;
            if(q==1)
                recieve_mark();
            if(q==0) return;
        }
    };
    void print_dept_sheet()
    {
        
        int d,i;
        cout    <<"Enter Department Code\n "
                <<"1. CSE 2. CHE 3. ELE\n"<<endl;
        cin>>d;
       // system("clear");
        cout<<"Department: ";
        print_department(d);
        cout<<endl;
       int j=dept[d][0];
        for (i=1;i<=j;i++)
        {
            int k=dept[d][i];
            cout<<k<<endl;
            sroll[k].show_student(i);
        }; 
    };
    void uni_topper()
    {
        if(count==0)
        {
            cout<<"No admission have been taken yet"<<endl;
            return;
        }
        if(ch5==0)
        {
            cout<<"No data regarding marks have been updated"<<endl;
            return;
        }
        cout<<"University topper is"<<endl;
        sroll[dept[0][11]].show_student(1);
        int f;
        f=sroll[dept[0][11]].send_total();
        cout<<"Total marks="<<f<<endl;

    };

};
int main()
{
    university ju;
    ju.admin_interface();
    return 0;
}