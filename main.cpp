#include <iostream>
#include <fstream>
#include <cstring>
#include <conio.h>
#include <limits>

using namespace std;

class Lib{
public:
    char bookname[100];
    char auname[50];
    char id[20];
    char pub[20];
    int q,p,B;//q-quantity,p-price

    Lib()
    {
        strcpy(bookname,"No Book Name");
        strcpy(auname,"No Author Name");
        strcpy(id,"No book Id");
        strcpy(pub,"No book Publication");
        q=0;
        p=0;
        B=0;
    }
    void get();
    void student();
    void pass();
    void librarian();
    void password();
    void getdata();//to get information of book
    void show(int);//to show information of book
    void booklist(int);//to read the books from a file
    void modify();
    void see(int);
    int branch(int);
    void issue();
    void der(char[],int,int);
    void fine(int,int,int,int,int,int);

};

void Lib::getdata()
{
    int i;
    fflush(stdin);//to remove input buffer
    cout<<"\n\tEnter the book details :- \n";
    cout<<"\n\tEnter the Book's name:- ";
    cin.getline(bookname,100);//used to store with spaces
    for(i=0;bookname[i]!='\0';i++)
    {
        if(bookname[i]>'a'&&bookname[i]<'z')
        {
            bookname[i]-=32;//converting all lowercase to uppercase
        }
    }
    cout<<"\n\tEnter the Book's Author :-";
    cin.getline(auname,50);
    cout<<"\n\tEnter the Book's ID :-";
    cin.getline(id,20);
    cout<<"\n\tEnter the Book's Publication :-";
    cin.getline(pub,20);
    cout<<"\n\tEnter the Book's Price :-";
    cin>>p;
    cout<<"\n\tEnter the Books Quantity :-";
    cin>>q;
}
void Lib::show(int i)
{
    cout<<"\n\tBook name :"<<bookname<<endl;
    cout<<"\n\tBook's Author name :"<<auname<<endl;
    cout<<"\n\tBook's ID :"<<id<<endl;
    cout<<"\n\tBook's Publication :"<<pub<<endl;
    if(i==2)//only for librarian
    {
        cout<<"\n\tBook's Price :"<<p<<endl;
        cout<<"\n\tBook's Quantity :"<<q<<endl;
    }}
void Lib::booklist(int i)
{
    int b,r=0;
    system("cls");//to clear console screen
    //used library stdlib.h;
    b=branch(i);
    system("cls");
    ifstream intf("Booksdata.txt",ios::binary);//This is a C++ standard library class used for reading from files.
    //intf is an object created
    if(!intf)
    {
        cout<<"\n\tFile not found.";
        //if  if the file cannot be opened for any reason (such as if it does not exist or if there are permission issues), the stream object will be in a "fail" state.
    }
    else
    {
        cout<<"\n\t    ************ Book List ************ \n\n";
        intf.read((char*)this,sizeof(*this));
        while(!intf.eof())//to read till end of book
        {
         if(b==B)
         {
             if(q==0&&i==1){}//quantity of book is not zero
             else
             {
                 r++;
                 cout<<"\n\t\t********** "<<r<<". ********** \n";
                 show(i);
             }
         }
         intf.read((char*)this,sizeof(*this));
        }
    }
    cout<<"\n\tPress any key to continue...";
    getch();
    system("cls");
    if(i==1)
        student();
    else
        librarian();
}
void Lib::modify()
{
    char ch,title[100];
    int i=0,b,cont=0;
    system("cls");
    cout<<"\n\tPlease chose one option :-\n\n\t1.Modification In Current Book\n\n\t2.Add New Books\n\n\t3.Delete a Book\n\n\t4.Go back\n";
    cout<<"\n\tEnter your choice :";
    cin>>i;
    if(i==1)
    {
        system("cls");
        b=branch(2);
        ifstream intf1("Booksdata.txt",ios::binary);//opening in binary
        if(!intf1)
        {
            cout<<"\n\tFile Not found\n";
            cout<<"\n\tPress any key to continue....";
            getch();
            system("cls");
            librarian();//shows options of librarian cause only librarian can modify books
        }
        intf1.close();//close text file
        system("cls");
        cout<<"\n\tPlease Choose One Option :-\n";
        cout<<"\n\t1.Search by Book name\n\n\t2.Search by Book ID\n";
        cout<<"\n\tEnter your choice :";
        cin>>i;
        cin.ignore();
        if(i==1)//to search by book name
        {
            system("cls");
            cout<<"\n\tEnter Book Name :";
            cin.getline(title,100);
            system("cls");
            fstream intf("Booksdata.txt",ios::in|ios::out|ios::ate|ios::binary);//opens the file and the seeker is set to end
            intf.seekg(0);//seeker set to start of file
            intf.read((char*)this,sizeof(*this));
            while(!intf.eof())
            {
                for(i=0;b==B&&bookname[i]!='\0'&&title[i]!='\0'&&(title[i]==bookname[i]||title[i]==bookname[i]+32);i++);
                if(bookname[i]=='\0'&&title[i]=='\0')
                {
                    cont++;
                    getdata();
                    intf.seekg(intf.tellg() - sizeof(*this));
                    intf.write((char*)this,sizeof(*this));
                    break;
                }
                intf.read((char*)this,sizeof(*this));

            }
            intf.close();}
        else if(i==2)//to search by id
        {
            cout<<"\n\tEnter the books ID :";
            cin.getline(title,100);
            system("cls");
            fstream intf("Booksdata.txt",ios::in|ios::out|ios::ate|ios::binary);
            intf.seekg(0);
            intf.read((char*)this,sizeof(*this));
            while(!intf.eof())
            {
                for(i=0;b==B&&title[i]!='\0'&&id[i]!='\0'&&id[i]==title[i];i++);
                if(title[i]=='\0'&&id[i]=='\0')
                {
                    cont++;
                    getdata();
                    intf.seekp(intf.tellp()-sizeof(*this));
                    intf.write((char*)this,sizeof(*this));
                    break;

                }
                intf.read((char*)this,sizeof(*this));
            }
            intf.close();
        }
        else
        {
            cout<<"\n\tIncorrect Input...\n";
            cout<<"\n\tPress any key to continue\n";
            getch();
            system("cls");
            modify();
        }
        if(cont==0)
        {
            cout<<"\n\tBook not found.\n";
            cout<<"\n\tPress any key to continue....";
            getch();
            system("cls");
            modify();
        }
        else
            cout<<"\n\tUpdate Successful\n";

    }//end of option one i.e Adding a book
    else if(i==2)
    {
        system("cls");
        B=branch(2);
        system("cls");
        getdata();
        ofstream outf("Booksdata.txt",ios::app|ios::binary);//appends to end of file
        outf.write((char*)this,sizeof(*this));
        outf.close();
        cout<<"\n\tBook added successfully\n";

    }//end of book add function
    else if(i==3)
    {
      system("cls");;
      b=branch(2);//only librarian can add
      ifstream intf1("Booksdata.txt",ios::binary);
      if (!intf1.is_open()){
          cout<<"\n\tFile not Found\n";
          cout<<"\n\tPress any key to continue....";
          getch();
          intf1.close();
          system("cls");
          librarian();
      }//checking if file exists
      intf1.close();//closing anyway
      system("cls");
      cout<<"\n\tPlease Choose one option for deletion:-\n";
      cout<<"\n\t1.By Book name\n\n\t2.By Book's ID\n";
      cout<<"\n\tEnter your choice :";
      cin>>i;
      fflush(stdin);
      if(i==1)
      {
          system("cls");
          cout<<"\n\tEnter Book Name:";
          cin.getline(title,100);
          ofstream outf("temp.txt",ios::app|ios::binary);//to duplicate the orignal file
          ifstream intf("Booksdata.txt",ios::binary);
          intf.read((char*)this,sizeof(*this));
          while(!intf.eof())
          {
              for(i=0;b==B&&bookname[i]!='\0'&&title[i]!='\0'&&(title[i]==bookname[i]||bookname[i]+32);i++)
                if(bookname[i]=='\0'&&title[i]=='\0')
              {
                  cont++;
                  intf.read((char*)this,sizeof(*this));
              }
              else
              {
                  outf.write((char*)this,sizeof(*this));
                  intf.read((char*)this,sizeof(*this));
              }
          }
          remove("Booksdata.txt");//deleting orignal file
        rename("temp.txt","Booksdata.txt");//changing duplicate into orignal
        }
        else if(i==2)
        {
            cout<<"\n\tEnter Book's ID :";
            cin.getline(title,100);
            ofstream outf("temp.txt",ios::app|ios::binary);
            ifstream intf("Booksdata.txt",ios::binary);
            intf.read((char*)this,sizeof(*this));
            while(!intf.eof())
            {
                for(i=0;b==B&&title[i]!='\0'&&id[i]!='\0'&&(id[i]==title[i]);i++);
                if(title[i]=='\0'&&id[i]=='\0')
                {
                    cont++;
                    intf.read((char*)this,sizeof(*this));
                }
                else
                {
                    outf.write((char*)this,sizeof(*this));
                    intf.read((char*)this,sizeof(*this));
                }
            }
            outf.close();
            intf.close();//closing both files
            remove("Booksdata.txt");
            rename("temp.txt","Booksdata.txt");
            }
            else
            {
                cout<<"\n\tIncorrect Input...\n";
                cout<<"\n\tPress any key to continue...";
                getch();
                system("cls");
                modify();
            }
            if(cont==0)
            {
                cout<<"\n\tBook not found.\n";
                cout<<"\\n\tPress any key to continue...";
                getch();
                system("cls");
                modify();
            }
            else
            {
                cout<<"\n\tDeletion Successful.\n";

            }}
            else if(i==4)//go back to main menu
            {
              system("cls");
              librarian();
            }
            else
            {
                cout<<"\n\tWrong Input.\n";
                cout<<"\n\tPress any key to continue...";
                getch();
                system("cls");
                modify();
            }
            cout<<"\n\tPress any key to continue...";
            getch();
            system("cls");
            librarian();//going back to librarian page
            }
            //end of modify funciton
int Lib::branch(int x)
{
    int i;
    cout<<"\n\tPlease chose one Branch :-\n";
    cout<<"\n\t1.Class 12th\n\n\t2.CS\n\n\t3.ECE\n\n\t4.CIVIL\n\n\t5.MECHANICAL\n\n\t6.1ST YEAR\n\n\t7.Go to menu\n";
    cout<<"\n\tEnter your choice :";
    cin>>i;
    switch(i)
    {
        case 1:return 1;
        break;
        case 2:return 2;
        break;
        case 3:return 3;
        break;
        case 4:return 4;
        break;
        case 5:return 5;
        break;
        case 6:return 6;
        break;
        case 7:system("cls");
        if(x==1)
            student();
        else
            librarian();
        default:cout<<"\n\tPlease Enter correct option :";
        getch();
        system("cls");
        branch(x);
    }
}//branch function completed
void Lib::see(int x)
{
    int i,b,cont=0;
    char ch[100];
    system("cls");
    b=branch(x);
    ifstream intf("Booksdata.txt",ios::binary);
    if(!intf)
    {
        cout<<"\n\tFile not found.\n";
        cout<<"\n\tPress any key to continue...";
        getch();
        system("cls");
        if(x==1)
            student();
        else
            librarian();
    }
    system("cls");

        cout<<"\n\tPlease Choose one option :\n";
        cout<<"\n\tEnter Your Choice :";
        cin>>i;
        fflush(stdin);
        intf.read((char*)this,sizeof(*this));
        if(i==1)//to search with book name
        {
            cout<<"\n\tEnter Book's Name :";
            cin.getline(ch,100);
            system("cls");
            while(!intf.eof())
            {
                for(i=0;b==B&&q!=0&&bookname[i]!='\0'&&ch[i]!='\0'&&(ch[i]==bookname[i]||ch[i]==bookname[i]+32);i++);
                if(bookname[i]=='\0'&&ch[i]=='\0')
                {
                  cout<<"\n\tBook found :\n";
                  show(x);
                  cont++;
                  break;
                }
                intf.read((char*)this,sizeof(*this));
            }
        }
        else if(i==2)//to search with book id
        {
          cout<<"\n\tEnter the books id: ";
          cin.getline(ch,100);//to get book id
          system("cls");
          while(!intf.eof())
          {
              for(i=0;b==B&&q!=0&&id[i]!='\0'&&ch[i]!='\0'&&ch[i]==id[i];i++);
              if(id[i]=='\0'&&ch[i]=='\0')
              {
                  cout<<"\n\tBook found :-\n";
                  show(x);
                  cont++;
                  break;
              }
              intf.read((char*)this,sizeof(*this));

          }

        }
        else
        {
            cont++;
            cout<<"\n\tPlease enter correct option :";
            getch();
            system("cls");
            show(x);
        }
        intf.close();
        if(cont==0)
        cout<<"\n\tThis book is not Avalilable!\n";
        cout<<"\n\tPress any key to continue....";
        getch();
        system("cls");
        if(x==1)
            student();
        else
            librarian();
}//this function was just to check whether the book existed or not
void Lib::issue()
{
    char st[50],st1[20];//student name and student id
    int b,i,j,d,m,y,dd,mm,yy,cont=0;
    system("cls");
    cout<<"\n\tPlease Choose one option :-\n";
    cout<<"\n\t1.Issue Book\n\n\t2.View Issued Book\n\n\t3.Search student who issued books.\n\n\t4.Return Book.\n\n\t5.Go back to menu\n";
    cin>>i;
    fflush(stdin);
    if(i==1)//to issue a book
    {
        system("cls");
        b=branch(2);
        system("cls");
        fflush(stdin);
        cout<<"\n\tPlease enter book details :-\n";
        cout<<"\n\tEnter Bookname :";
        cin.getline(bookname,100);
        cout<<"\n\tEnter Book's ID : ";
        cin.getline(id,20);
        der(id,b,1);
        cout<<"\n\tEnter the Students Name :";
        cin.getline(auname,50);
        cout<<"\n\tEnter Student's ID :";
        cin.getline(pub,20);
        cout<<"\n\tEnter date :";
        cin>>q>>B>>p;//date is stored in this variables in this context
        ofstream outf("student.txt",ios::binary|ios::app);//create a file to store issued books
        outf.write((char*)this,sizeof(*this));
        outf.close();
        cout<<"\n\tIssue Successfully.\n";
    }
    else if(i==2)//to view issued books
    {
      ifstream intf("student.txt",ios::binary);
      system("cls");
      cout<<"\n\tThe Details are :-\n";
      intf.read((char*)this,sizeof(*this));
      i=0;
      while(!intf.eof())
      {
          i++;
          cout<<"\n\t*"<<i<<"*\n";
          cout<<"\n\tStudent's Name : "<<auname<<"\n\tStudent's ID: "<<pub<<"Book Name :"<<bookname<<"\n\tBooks ID :"<<id<<"\n\tDate : "<<q<<"/"<<B<<"/"<<p<<endl;
          intf.read((char*)this,sizeof(*this));}
      intf.close();
    }
    else if(i==3)
    {
        system("cls");
        fflush(stdin);
        cout<<"\n\tPlease Enter Details :-\n";
        cout<<"\n\tEnter Student Name :";
        cin.getline(st,50);
        cout<<"Enter Student's ID :";
        cin.getline(st1,20);
        system("cls");
        ifstream intf("Student.txt",ios::binary);
        intf.read((char*)this,sizeof(*this));
        cont=0;
        while(!intf.eof())
        {
            for(i=0;id[i]!='\0'&&st1[i]!='\0'&&st1[i]==id[i];i++);
            if(id[i]=='\0'&&id[i]=='\0')
            {
                cont++;
                if(cont==1)
                {
                    cout<<"\n\tThe Details are :\n";
                    cout<<"\n\tStudents Name: "<<auname;
                    cout<<"\n\tStudent's ID :"<<id;
                    //only first time this will be printed

                }
                cout<<"\n\t******* "<<cont<<". Book details *******\n";
                cout<<"\n\tBook name :"<<bookname;
                cout<<"\n\tBooks id :"<<id;
                cout<<"\n\tDate : "<<q<<"/"<<B<<"/"<<p<<endl;
            }
            intf.read((char*)this,sizeof(*this));}
            intf.close();//close file
            if(cont==0)
            {
                cout<<"\n\tNo record found";
            }

    }//end of conditional
    if(i==4)//return book
    {
        system("cls");
        b=branch(2);
        system("cls");
        fflush(stdin);
        cout<<"\n\tPlease enter details :-\n";
        cout<<"\n\tEnter Books ID :";
        cin.getline(st1,20);
        der(st1,b,2);
        cout<<"\n\tEnter Student's ID :";
        cin.getline(st,20);
        cout<<"\n\tEnter Present date :";
        cin>>d>>m>>y;
        ofstream outf("temp.txt",ios::app|ios::binary);
        ifstream intf("student.txt",ios::binary);
        intf.read((char*)this,sizeof(*this));
        while(!intf.eof())
        {
            for(i=0;id[i]!='\0'&&st1[i]!='\0'&&st1[i]==id[i];i++);
            for(j=0;pub[j]!='\0'&&st[j]!='\0'&&st[j]==pub[j];j++);
            if(id[i]=='\0'&&pub[j]=='\0'&&st[j]=='\0'&&st1[i]=='\0'&&cont==0)
            {
                cont++;
                intf.read((char*)this,sizeof(*this));
                fine(q,B,p,d,m,y);
                cout<<"\n\tReturned successfully.";
            }
            else
            {
                outf.write((char*)this,sizeof(*this));
                intf.read((char*)this,sizeof(*this));
                }
                }
            intf.close();
            outf.close();
            getch();
            remove("student.txt");
            rename("temp.txt","student.txt");
    }
    else if(i==6)
    {
        system("cls");
        librarian();
    }
    else
    cout<<"\n\tWrong Input.\n";
    cout<<"\n\tPress any key to continue...";
    getch();
    system("cls");
    librarian();//goes back to menu
}
//qwert
void Lib::fine(int d,int m,int y,int dd,int mm,int yy){
    long int n1,n2;
    int years,l,i;
    const int monthdays[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    n1=365*y+d;
    for(i=0;i<m-1;i++){
        n1+=monthdays[i];
    }
    years=y;
    if(m<=2){
        years--;
        l=years/4-years/100+years/400;
        n1+=l;
        n2=yy*365+dd;
    }
    for(i=0; i<mm-1;i++){
        n2+=monthdays[i];
    }
    years=yy;
    if(m<=2){
        years--;
        l=years/4-years/100+years/400;
        n2+=l;
        n1=n2-n1;
        n2=n1-15;
    }
    if(n2>0){
        cout<<"\n\t\tThe Total Fine is : "<<n2;
    }
}

void Lib::der(char st[],int b,int x){
    int i,cont=0;
    fstream intf("Bookdata.txt",ios::in|ios::out|ios::ate|ios::binary);
    intf.seekg(0);
    intf.read((char*)this,sizeof(*this));
    while(!intf.eof()){
        for(i=0;b==B && id[i]!='\0'&& st[i]!='\0'&&st[i]==id[i];i++);
        if(id[i]=='\0' && st[i]=='\0'){
            cont++;
            if(x==1){
                q--;
            }
            else{
                q++;
            }
            intf.seekp(intf.tellp()-sizeof(*this));
            intf.write((char*)this,sizeof(*this));
            break;
        }
        intf.read((char*)this,sizeof(*this));
    }
    if(cont==0){
        cout<<"\n\t\tBook not found.\n";
        cout<<"\n\n\t\tPress any key to continue....";
        getch();
        system("cls");
        issue();
    }
    intf.close();
}

void Lib::get(){
    int i;
    cout<<"\n\t*********** LIBRARY MANAGEMENT SYSTEM ***********\n";
    cout<<"\n\t\t>>Please Choose Any Option To login \n";
    cout<<"\n\t\t1.Student\n\n\t\t2.Librarian\n\n\t\t3.Close Application\n";
    cout<<"\n\t\tEnter your choice : ";
    cin>>i;
    if(i==1){
        system("cls");
        student();
    }
    else if(i==2){
        pass();
    }
    else if(i==3){
        exit(0);
    }
    else{
        cout<<"\n\t\tPlease enter correct option :(";
        getch();
        system("CLS");
        get();
    }
}

void Lib::student()
{
    int i;
    cout<<"\n\t************ WELCOME STUDENT ************\n";
    cout<<"\n\t\t>>Please Choose One Option:\n";
    cout<<"\n\t\t1.View BookList\n\n\t\t2.Search for a Book\n\n\t\t3.Go to main menu\n\n\t\t4.Close Application\n";
    cout<<"\n\t\tEnter your choice : ";
    cin>>i;
    if(i==1){
        booklist(1);
    }
    else if(i==2){
        see(1);
    }
    else if(i==3){
        system("cls");
        get();
    }
    else if(i==4){
        exit(0);
    }
    else{
        cout<<"\n\t\tPlease enter correct option :(";
        getch();
        system("cls");
        student();
    }
}

void Lib::pass()
{
    int i=0;
    char ch,st[21],ch1[21]={"123"};
    cout<<"\n\t\tEnter Password : ";
    while(1){
        ch=getch();
        if(ch==13){
            st[i]='\0';
        break;
        }
        else if(ch==8&&i>0){
            i--;
            cout<<"\b \b";
        }
        else{
            cout<<"*";
            st[i]=ch;
            i++;
        }
    }
    ifstream inf("password.txt");
    inf>>ch1;
    inf.close();
    for(i=0;st[i]==ch1[i]&&st[i]!='\0'&&ch1[i]!='\0';i++);
    if(st[i]=='\0'&&ch1[i]=='\0'){
        system("cls");
        librarian();
    }
    else{
        cout<<"\n\n\t\tWrong Password.\n\n\t\ttry again.....\n";
        getch();
        system("cls");
        get();
    }
}

void Lib::librarian() {
    while (true) {
        cout << "\n\t************ WELCOME LIBRARIAN ************\n";
        cout << "\n\t\t>>Please Choose One Option:\n";
        cout << "\n\t\t1.View BookList\n\n"
             << "\t\t2.Search for a Book\n\n"
             << "\t\t3.Modify/Add Book\n\n"
             << "\t\t4.Issue Book\n\n"
             << "\t\t5.Go to main menu\n\n"
             << "\t\t6.Change Password\n\n"
             << "\t\t7.Close Application\n\n";
        cout << "\n\t\tEnter your choice : ";

        int choice;
        if (!(cin >> choice)) {
            cout << "\n\t\tPlease enter a valid number.";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            continue;
        }

        switch (choice) {
            case 1:
                booklist(2);
                break;
            case 2:
                see(2);
                break;
            case 3:
                modify();
                break;
            case 4:
                issue();
                break;
            case 5:
                system("cls");
                get();
                break;
            case 6:
                password();
                break;
            case 7:
                cout << "\n\t\tClosing application...\n";
                exit(0);
            default:
                cout << "\n\t\tPlease enter a correct option.\n";
                system("cls");
        }
    }
}

void Lib::password(){
    int i=0,j=0;
    char ch,st[21],ch1[21]={"123"};
    system("cls");
    cout<<"\n\n\t\tEnter Old Password : ";
    while(1){
        ch=getch();
        if(ch==13){
            st[i]='\0';
            break;
        }
        else if(ch==8&&i>0){
            i--;
            cout<<"\b \b";
        }
        else{
            cout<<"*";
            st[i]=ch;
            i++;
        }
    }
    ifstream intf("password.txt");
    intf>>ch1;
    intf.close();
    for(i=0;st[i]==ch1[i]&&st[i]!='\0'&&ch1[i]!='\0';i++);
    if(st[i]=='\0'&&ch1[i]=='\0'){
        system("cls");
        cout<<"\n\t**The Password Should be less than 20 characters & don't use spaces**\n\n";
        cout<<"\n\t\tEnter New Password : ";
        fflush(stdin);
        i=0;
        while(1){
            j++;
            ch=getch();
            if(ch==13){
                for(i=0;st[i]!=' '&&st[i]!='\0';i++);
                if(j>20 || st[i]==' '){
                    cout<<"\n\n\t\tYou did't follow the instruction \n\n\t\tPress any key for try again.....";
                    getch();
                    system("cls");
                    password();
                    librarian();
                }
                st[i]='\0';
                break;
            }
            else if(ch==8&&i>0){
                i--;
                cout<<"\b \b";
            }
            else{
                cout<<"*";
                st[i]=ch;
                i++;
            }
        }
        ofstream outf("password.txt");
        outf<<st;
        outf.close();
        cout<<"\n\n\t\tYour Password has been changed Successfully.";
        cout<<"\n\t\tPress any key to continue......";
        getch();
        system("cls");
        librarian();
    }
    else{
        cout<<"\n\n\t\tPassword is incorrect.....\n";
        cout<<"\n\t\tEnter 1 for retry or 2 for menu";
        cin>>i;
        if(i==1){
            system("cls");
            password();
        }
        else{
            system("cls");
            librarian();
        }
    }
}

int main(){
    Lib obj;
    obj.get();
    getch();
    return 0;
}
