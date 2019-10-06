#include<iostream>
#include<fstream>
#include<string.h>
#include<iomanip>
#include<ctime>
using namespace std;

class customer
{
    protected:
    int customer_ID;
    float cash;
    string customer_name,customer_address;


    public:
        void set_cus_data();
};

void customer::set_cus_data()
{   cout<<"_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n";
    cout<<"Enter customer Name";cout<<"\t";
    cin>>customer_name;cout<<"\n";
    cout<<"_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n";

    cout<<"Enter customer ID";cout<<"\t";
    cin>>customer_ID;cout<<"\n";
    cout<<"_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n";

    cout<<"Enter customer address";cout<<"\t";
    cin>>customer_address;cout<<"\n";
    cout<<"_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n";

    cout<<"Enter cash given by customer(RS.) ";cout<<"\t";
    cin>>cash;
    cout<<"_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n";

}

class loyalty_customer:public customer
{

   protected:
         int discount_RT=0;

    public:
        void set_discount(int);

};

void loyalty_customer::set_discount(int discount_RT)
{
    this->discount_RT=discount_RT;

}
class Normal_customer:public customer
{

};

class paint
{
    protected:
    int Code;
    string paint_Name;

    public:
        void set_paint_data(string,int);
};

void paint::set_paint_data(string paint_Name,int Code)
{
    this->paint_Name=paint_Name;
    this->Code=Code;
}

class Premium_colours:public paint
{  protected:
    static float Tax_Rate,price;
    float Tax_Amount;

public:
    void cal_Tax();


};

float Premium_colours::Tax_Rate=10;
float Premium_colours::price=2500;



void Premium_colours::cal_Tax()
{
    Tax_Amount=price*Tax_Rate/100;
    price=price+Tax_Amount;
}


class Normal_colours:public paint
{

};

class customer_data:public loyalty_customer,public Premium_colours
{  protected:
    int Amount=0,Tot_Amount=0,Bill_Code,QTY,discounted_price,change;
    time_t x = time(0);//returns value which is the elapsed time from the date the system has been created
    char* dt = ctime(&x);//This returns a pointer to a string of the form day month year hours:minutes:seconds,
    //this converts the above returned value into an understandable time format

     public:
      void calculation();
      void set_QTY();
      void File_creating();
};

void customer_data::calculation()
{
    Amount=price*QTY;
    discounted_price=Amount*discount_RT/100;
    Tot_Amount=Amount-discounted_price;
    change=cash-Tot_Amount;

}

void customer_data::set_QTY()
{   cout<<"_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n";
    cout<<"Enter quantity:";cin>>QTY;cout<<"\n";
}

void customer_data::File_creating()
{
   fstream x;
   x.open("Data_log.txt",ios::app);
   x<<"\n ___________________________________________"
   <<"\n Date and Time   :"
   <<setw(20)<<dt//this sets the character limit
   <<" customer Name   :"
   <<setw(10)<<customer_name<<"\n Customer ID     :"
   <<setw(10)<<customer_ID<<"\n Customer address:"
   <<setw(10)<<customer_address<<"\n Total amount    :"
   <<setw(10)<<Tot_Amount;

}

class Bill:public customer_data
{
public:
   void Display();
};

void Bill::Display()
{
     cout<<"\n\n\n\t\t    New Rainbow Colors(PVT)LTD.\n"
    <<"\t\t\t    COLOMBO 07\n"
    <<"\t\t   Tel-0112 2699563   Fax7565566\n"
    <<"\t\t"
    <<"DATE:"<<dt
    <<"\t \t \t \t \t   \tCashier : Sampath "
    <<"\n\n\n\t  DESCRIPION\tITEM CODE\tQTY\tGROSS\t   AMOUNT"


      <<"\n\t_______________________________________________________________\n"
      <<"\t"<<paint_Name<<"\t"
      <<"   "<<Code
      <<"\t \t"<<QTY
      <<"\t"<<price
      <<"\t"
      <<Amount
      <<"\n";

      cout<<"\n\t*****************************************************************\n"
      <<"\t\tTotal Amount\t"
      <<Amount
      <<"\n\t        Discounted\t"
      <<discounted_price
      <<"\n\t\tNet Amount\t"
      <<Tot_Amount<<"\n"
      <<"\t \tcash\t"
      <<cash<<"\n"
      <<"\t \tBalance\t"
      <<change<<"\n"

      <<"\t\t********************************************\n\t";

       cout<<"\t             THE ITEMS YOU BROUGHT IS NON RETURNABLE\n"
       <<"\t                      *Thank you come again :)*\n\n";

};


main()
{

   Bill B1;
   B1.set_cus_data();
   int PRM,LYL;

   cout<<"If customer is Loyalty customer press 1 \n * customer don't have press 2:";
     cin>>LYL;
     cout<<"_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n";
   cout<<"If customer brought Premium colors press 1 \n If customer brought Noraml colors press 2:";
     cin>>PRM;
     if(PRM==1)
     {
     B1.set_paint_data("Premium Paint",112);
     B1.cal_Tax();
     B1.set_QTY();
     }
     else
     {
     B1.set_paint_data("Normal Paint",133);
     B1.set_QTY();
     }

     if(LYL==1)
      {
          B1.set_discount(15);
          B1.calculation();
      }
      else
      {
          B1.calculation();
      }


     B1.File_creating();
    B1.Display();

   return 0;
}
