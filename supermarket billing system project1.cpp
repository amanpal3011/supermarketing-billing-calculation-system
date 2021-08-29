#include<iostream>
#include<windows.h>
#include<conio.h>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<iomanip>
using namespace std;

int y=7,z=0,flag=0;
struct date
{
int mm;
int dd;
int yy;
};
 
ofstream fout;
ifstream fin;
 
class item
{
int item_number;
char name[25];
date d;
public:
void add()
{

cout<<"\n\n\tName of the item: ";
cin>>name;	
cout<<"\n\n\t Item Number : ";
cin>>item_number;
cout<<"\n\n\tManufacturing Date(dd-mm-yy): ";
cin>>d.mm>>d.dd>>d.yy;
}
void show()
{
cout<<"\n\tItem No: ";
cout<<item_number;
cout<<"\n\n\tName of the item: ";
cout<<name;
cout<<"\n\n\tDate : ";
cout<<d.mm<<"-"<<d.dd<<"-"<<d.yy;
}
void report()
{
  cout<<" \n ";
  cout<<"  ";
  cout<<item_number;
  cout<<"  ";
  puts(name);
}
int retno()
{
    return(item_number);
 
}
 
};
 
class amount: public item
{
float price,qty,tax,gross,dis,netamt;
public:
void add();
void show();
void report();
void calculate();
void pay();
float retnetamt()
{
    return(netamt);
}
}amt;
  
void amount::pay()
{
show();
cout<<"\n\t\t                 DETAILS                  ";
cout<<"\n\n\t\tPrice                    :"<<price<<endl;
cout<<"\n\n\t\tQuantity                  :"<<qty<<endl;
cout<<"\n\t\tTax Percentage             :"<<tax<<endl;
cout<<"\n\t\tDiscount Percentage         :"<<dis<<endl;
cout<<"\n\n\n\t\tNet Amount             :Rs."<<netamt<<endl;
}
 
void amount::add()
{
item::add();
cout<<"\n\tPrice: ";
cin>>price;
cout<<"\tQuantity: ";
cin>>qty;
cout<<"\tTax percent: ";
cin>>tax;
cout<<"\tDiscount percent: ";
cin>>dis;
calculate();
fout.write((char *)&amt,sizeof(amt));
fout.close();
}
void amount::calculate()
{
gross=price+(price*(tax/100));
netamt=qty*(gross-(gross*(dis/100)));
}
void amount::show()
{
fin.open("itemstore.dat",ios::binary);
fin.read((char*)&amt,sizeof(amt));
item::show();
cout<<"\n\n\tNet amount: ";
cout<<netamt;
fin.close();
}
 
void amount::report()
{
item::report();
cout<<"\n"<<price<<"\t";
cout<<qty<<"\t";
cout<<tax<<"\t";
cout<<dis<<"\t";
cout<<netamt<<"\t";
y=y+1;
if(y==50)
{
cout<<"Press any key ...";
getch();
y=7;
system("cls");

cout<<" Iteims details "<<endl;
cout<<"Number"<<endl;
cout<<"Name"<<endl;
cout<<"Price"<<endl;
cout<<"Quantity"<<endl;
cout<<"Tax"<<endl;
cout<<"Deduction"<<endl;
cout<<"Net amount"<<endl;
}
}
int main()
{
cout.setf(ios::fixed);
cout.setf(ios::showpoint);
cout<<setprecision(2);
fstream tmp("temp.dat",ios::binary|ios::out);
menu:
system("cls");

cout<<"Super Market Billing ";
cout<<"===========================\n\n";
cout<<"\n\t1.Show billing details\n\n";
cout<<"\t2.Add details/Remove details/Edit data Item\n\n";
cout<<"\t3.Show Item Details\n\n";
cout<<"\t4.Exit\n\n";
cout<<"\tPlease Enter your choice: ";
int choose,ff;
float gtotal;
cin>>choose;
switch(choose)
{
case 1:ss:
system("cls");

cout<<"\tBill Details";
cout<<"\n\t1.All Items\n\n";
cout<<"\t2.Back to Main menu\n\n";
cout<<"\tPlease Enter Required Option: ";
int choice;
cin>>choice;
if(choice==1)
{
system("cls");

cout<<" BILL DETAILS \n\n\n\t\t";
cout<<"ITEM number\t";
cout<<"NAME \n\t";
cout<<"PRICE \t";
cout<<"QUANTITY \t";
cout<<"TAX% \t";
cout<<"DISCOUNT% \t";
cout<<"NET AMOUNT";
fin.open("itemstore.dat",ios::binary);
if(!fin)
{
cout<<"\n\nFile Not Found...";
goto menu;
}
fin.seekg(0);
gtotal=0;
while(!fin.eof())
{
fin.read((char*)&amt,sizeof(amt));
if(!fin.eof())
{
amt.report();
gtotal=gtotal+amt.retnetamt();
ff=0;
}
if(ff!=0)
 gtotal=0;
};
cout<<"\n\n\n\t\t\tGrand Total="<<gtotal;
getch();
fin.close();
}
if(choice==2)
{
goto menu;
}
goto ss;
case 2:
db:
system("cls");

cout<<"Billing update  process";
cout<<"\n\t1.Add Item Details\n\n";
cout<<"\t2.Edit Item Details\n\n";
cout<<"\t3.Delete Item Details\n\n";
cout<<"\t4.Back to Main Menu ";
int j;
cin>>j;
switch(j)
{
case 1:
fout.open("itemstore.dat",ios::binary|ios::app);
amt.add();
cout<<"\n\t\tItem Added Successfully!";
getch();
goto db;
 
case 2:
int itno;
flag=0;
cout<<"\n\n\tEnter Item Number to be upgrade :";
cin>>itno;
fin.open("itemstore.dat",ios::binary);
fout.open("itemstore.dat",ios::binary|ios::app);
if(!fin)
{
cout<<"\n\nFile Not Found...";
goto menu;
}
fin.seekg(0);
z=0;
while(!fin.eof())
{
fin.read((char*)&amt,sizeof(amt));
if(!fin.eof())
{
int x=amt.item::retno();
if(x==itno)
{
flag=1; 
fout.seekp(z*sizeof(amt));
system("cls");
cout<<"\n\tCurrent Details are\n";
amt.show();
cout<<"\n\n\tEnter New Details\n";
amt.add();
cout<<"\n\tItem Details upgraded";
}
}z++;
}
if(flag==0)
{
cout<<"\n\tItem No does not exist...Please Retry!";
getch();
goto db;
}
fin.close();
getch();
goto db;
 
case 3:
flag=0;
cout<<"\n\n\tEnter Item Number to be deleted :";
cin>>itno;
fin.open("itemstore.dat",ios::binary);
if(!fin)
{
cout<<"\n\nFile Not Found...";
goto menu;
}
fin.seekg(0);
while(fin.read((char*)&amt, sizeof(amt)))
{
int x=amt.item::retno();
if(x!=itno)
tmp.write((char*)&amt,sizeof(amt));
else
{
flag=1;
}
}
fin.close();
tmp.close();
fout.open("itemstore.dat",ios::trunc|ios::binary);
fout.seekp(0);
tmp.open("temp.dat",ios::binary|ios::in);
if(!tmp)
{
cout<<"Error in File";
goto db;
}
while(tmp.read((char*)&amt,sizeof(amt)))
fout.write((char*)&amt,sizeof(amt));
tmp.close();
fout.close();
if(flag==1)
cout<<"\n\t\tItem Succesfully Deleted";
else if (flag==0)
cout<<"\n\t\tItem does not Exist! Please Retry";
getch();
goto db;
case 4:
goto menu;
default: cout<<"\n\n\t\tWrong Choice!!! Retry";
getch();
goto db;
}
case 3:
system("cls");
flag=0;
int itno;
cout<<"\n\n\t\tEnter Item Number :";
cin>>itno;
fin.open("itemstore.dat",ios::binary);
if(!fin)
{
cout<<"\n\nFile Not Found...\nProgram Terminated!";
goto menu;
}
fin.seekg(0);
while(fin.read((char*)&amt,sizeof(amt)))
{
int x=amt.item::retno();
if(x==itno)
{
amt.pay();
flag=1;
break;
}
}
if(flag==0)
cout<<"\n\t\tItem does not exist....!";
getch();
fin.close();
goto menu;
case 4:
system("cls");

cout<<"ARE YOU SURE, YOU WANT TO EXIT (Y/N)?";
char z;
cin>>z;
if((z=='Y')||(z=='y'))
{
system("cls");
getch();
exit(0);
}
else if((z=='N')||(z=='n'))
goto menu;
else{
goto menu;
}
default:
cout<<"\n\n\t\tWrong Choice....Please Retry!";
getch();
goto menu;
}
return 0;
}
