#include <iostream>
#include <conio.h>
#include <string.h>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
using namespace std;

/*==========================================================================CLASSES=================================================================*/

class user;
class admin
{
protected:
    char name[20];
    int id;
    char date[10];
    // int bill;

public:
    void get();
    void put();
    int get_id()
    {
        return id;
    }
    /* void update_bill(int num)

      {
          bill = num;
      }*/

    void update_id(int new_id)

    {
        id = new_id;
    }
    void update_name(char arr[])

    {
        strcpy(name, arr);
    }
    void update_date(char str[])

    {
        strcpy(date, str);
    }

    void add_customer();
    void display_all();
    void display_particular();
    void edit_customer();
    void delete_customer();
};

/*=====================================================================CLASSES======================================================================*/

class food_operation
{
protected:
    int num;
    char name_dish[10];
    int price;
    char veg_nonveg[7];
    int discount;
    char cuisine[15];
    char course[15];

public:
    void get_dish();
    void put_dish();
    int get_num()
    {
        return num;
    }

    void update_dishname(char arr[])

    {
        strcpy(name_dish, arr);
    }

    void update_price(int new_price)

    {
        price = new_price;
    }
    void update_discount(int disc)

    {
        discount = disc;
    }

    void update_type(char arr[])
    {
        strcpy(veg_nonveg, arr);
    }

    void update_cuisine(char arr[])
    {
        strcpy(cuisine, arr);
    }

    void update_course(char arr[])
    {
        strcpy(course, arr);
    }

    void add_dish();
    void show_all();
    void show_particular();
    void edit_dish();
    void delete_dish();
};

/*====================================================================CLASSES========================================================================*/

class restaurant_info : public admin
{
    char designation[15];

public:
    friend class user;
    void menu();
    void timings();
    void get_employee();
    void put_employee();
    void add_employee();
    void display_employee();
    void delete_employee();
    void search_employee();
    int get_idemp()
    {
        return id;
    }
};

/*===================================================================CLASSES=========================================================================*/

class user : public food_operation
{
protected:
    char user_name[15];
    long int phone;
    char dish_order[10];
    int quantity;
    int bill;
    int password;
    char address[15];

public:
    void get_user();
    void put_user();
    void signup();
    void login();
    void order_food();
};

/*=====================================================================CLASSES=======================================================================*/

class special_offers : public user
{
public:
    void offer()
    {
        if (bill > 1000)
        {
            bill = bill - 100;
            cout << "CONGRATULATIONS !!!  YOU GOT 100 RUPEE OFF ON YOUR FOOD ......" << endl;
        }
        else if (bill > 2000)
        {
            bill = bill - 300;
            cout << "CONGRATULATIONS !!!  YOU GOT 300 RUPEE OFF ON YOUR FOOD ......" << endl;
        }

        else if (bill == 350)
        {

            cout << "CONGRATULATIONS !!!  YOU GOT FREE FOOD (LUCKY NUMBER )......" << endl;
        }
    }
};

/****************************************************************************************************************************************************/

// global scope
admin a;
fstream file;
void admin ::get()
{

    cout << "ENTER NAME OF THE CUSTOMER :";
    cin >> name;
    fflush(stdin);
    cout << "ENTER ID OF THE CUSTOMER :";
    cin >> id;
    fflush(stdin);
    cout << "ENTER DATE :";
    cin >> date;
    fflush(stdin);
    /*cout << "ENTER BILL :";
     cin >> bill;
     fflush(stdin);*/
}

void admin ::put()
{
    cout << setw(3) << id
         << setw(15) << name
         << setw(10) << date
         << endl;
}

void admin ::add_customer()
{
    char ch = 'y';

    file.open("customers.txt", ios ::app | ios ::binary);
    while (ch == 'y' || ch == 'Y')
    {
        a.get();
        file.write((char *)&a, sizeof(a));

        cout << "ADD MORE RECORDS.....(Y/N)?";
        cin >> ch;
        fflush(stdin);
    }
    file.close();
}
void admin ::display_all()
{
    ifstream file("customers.txt", ios ::in | ios::binary);
    if (!file)
    {
        cout << "FILE NOT FOUND" << endl;
        exit(0);
    }
    else
    {

        file.read((char *)&a, sizeof(a));
        while (!file.eof())
        {
            a.put();
            file.read((char *)&a, sizeof(a));
        }
    }
    file.close();
}
void admin ::display_particular()
{
    int no, flag = 0;
    file.open("customers.txt", ios ::in | ios ::binary);
    if (!file)
    {
        cout << "FILE NOT FOUND" << endl;
        exit(0);
    }

    else
    {
        cout << "ENTER ID OF THE CUSTOMER :";
        cin >> no;
        fflush(stdin);

        file.read((char *)&a, sizeof(a));
        while (!file.eof())
        {
            if (no == a.get_id())
            {
                flag = 1;
                cout << "----------------------------------------------------------------" << endl;
                cout << setw(3) << id
                     << setw(15) << name
                     << setw(10) << date
                     << endl;
                cout << "-----------------------------------------------------------------" << endl;
                break;
            }
            file.read((char *)&a, sizeof(a));
        }
        if (flag == 0)
        {
            cout << "RECORD OF THAT CUSTOMER NOT FOUND....";
        }
    }
    file.close();
}
void admin ::delete_customer()
{
    int no;
    cout << "ENTER CUSTOMER ID :";
    cin >> no;
    fflush(stdin);

    ofstream file2;
    file2.open("temp.txt", ios ::out | ios ::binary);
    file.open("customers.txt", ios::in | ios ::binary);
    if (!file)
    {
        cout << "FILE NOT FOUND....";
    }
    else
    {
        file.read((char *)&a, sizeof(a));
        while (!file.eof())
        {
            if (no != a.get_id())
            {
                file2.write((char *)&a, sizeof(a));
            }
            file.read((char *)&a, sizeof(a));
        }
    }
    file2.close();
    file.close();
    remove("customers.txt");
    rename("temp.txt", "customers.txt");
}
void admin ::edit_customer()
{
    int no, num, new_id;
    char arr1[15], arr2[10];
    cout << "ENTER ID OF CUSTOMER TO BE EDITED :";
    cin >> no;
    fflush(stdin);

    cout << "ENTER NEW ID :";
    cin >> new_id;
    fflush(stdin);

    cout << "ENTER NEW NAME OF THE CUSTOMER :";
    cin >> arr1;
    fflush(stdin);

    cout << "ENTER NEW DATE :";
    cin >> arr2;
    fflush(stdin);

    file.open("customers.txt", ios ::in | ios ::out | ios ::binary);
    if (!file)
    {
        cout << "FILE NOT FOUND";
        exit(0);
    }
    while (file.read((char *)&a, sizeof(a)))
    { /// just another method to check the end of file which even consist of reading operation
        if (a.get_id() == no)
        {
            a.update_id(new_id);
            a.update_name(arr1);
            a.update_date(arr2);

            // move the ponter to current position -1
            int pos = sizeof(a);
            file.seekp(-pos, ios ::cur);
            // write object to customer.txt file
            file.write((char *)&a, sizeof(a));
        }
    }
    file.close();
}

/******************************************************************************************************************************************************/

void food_operation::get_dish()
{

    cout << "ENTER ID OF DISH :";
    cin >> num;
    fflush(stdin);
    cout << "ENTER NAME OF DISH :";
    cin >> name_dish;
    fflush(stdin);
    cout << "ENTER PRICE OF DISH :";
    cin >> price;
    fflush(stdin);
    cout << "ENTER TYPE OF DISH VEG OR NONVEG :";
    cin >> veg_nonveg;
    fflush(stdin);
    cout << "ENTER ANY OFFER IF AVAILABLE ON THE DISH :";
    cin >> discount;
    fflush(stdin);
    cout << "ENTER TYPE OF CUISINES :";
    cin >> cuisine;
    fflush(stdin);
    cout << "ENTER COURSE :";
    cin >> course;
    fflush(stdin);
}

void food_operation::put_dish()
{
    cout << setw(5) << num
         << setw(15) << name_dish
         << setw(5) << price
         << setw(10) << veg_nonveg
         << setw(10) << discount
         << setw(15) << cuisine
         << setw(15) << course << endl;
}

food_operation d;
fstream file1;
void food_operation ::add_dish()
{
    char ch = 'y';

    file1.open("dishes.txt", ios ::app | ios ::binary);
    while (ch == 'y' || ch == 'Y')
    {
        d.get_dish();
        file1.write((char *)&d, sizeof(d));

        cout << "ADD MORE RECORDS.....(Y/N)?";
        cin >> ch;
        fflush(stdin);
    }
    file1.close();
}

void food_operation ::show_all()
{

    ifstream file1("dishes.txt", ios ::in | ios ::app | ios::binary);
    if (!file1)
    {
        cout << "FILE NOT FOUND" << endl;
        // exit(0);
    }
    else
    {

        file1.read((char *)&d, sizeof(d));
        while (!file1.eof())
        {
            d.put_dish();
            file1.read((char *)&d, sizeof(d));
        }
    }
    file1.close();
}

void food_operation ::show_particular()
{
    int no, flag = 0;
    file1.open("dishes.txt", ios ::in | ios ::binary);
    if (!file1)
    {
        cout << "FILE NOT FOUND" << endl;
    }

    else
    {
        cout << "ENTER ID OF THE DISH:";
        cin >> num;
        fflush(stdin);

        file1.read((char *)&d, sizeof(d));
        while (!file1.eof())
        {
            if (no == d.get_num())
            {
                flag = 1;
                cout << "----------------------------------------------------------------" << endl;
                cout << setw(5) << num
                     << setw(15) << name_dish
                     << setw(5) << price
                     << setw(10) << veg_nonveg
                     << setw(10) << discount
                     << setw(15) << cuisine
                     << setw(15) << course << endl;
                cout << "-----------------------------------------------------------------" << endl;
                break;
            }
            file1.read((char *)&d, sizeof(d));
        }
        if (flag == 0)
        {
            cout << "RECORD OF THE DISH IS NOT AVAILABLE....";
        }
    }
    file1.close();
}

void food_operation ::edit_dish()
{
    int NO, num, dis;
    char str1[15], str2[7], str3[15], str4[15];
    cout << "ENTER ID OF DISH TO BE EDITED :";
    cin >> NO;
    fflush(stdin);

    cout << "ENTER NEW NAME OF THE DISH :";
    cin >> str1;
    fflush(stdin);

    cout << "ENTER PRICE AGAIN :";
    cin >> num;
    fflush(stdin);

    cout << "ENTER NEW TYPE VEG OR NON VEG :";
    cin >> str2;
    fflush(stdin);

    cout << "ENTER NEW DISCOUNT :";
    cin >> dis;
    fflush(stdin);

    cout << "ENTER NEW CUISINE :";
    cin >> str3;
    fflush(stdin);

    cout << "ENTER  NEW COURSE :";
    cin >> str4;
    fflush(stdin);

    file1.open("dishes.txt", ios ::in | ios ::out | ios ::binary);
    if (!file1)
    {
        cout << "FILE NOT FOUND";
        exit(0);
    }
    while (file1.read((char *)&d, sizeof(d)))
    { /// just another method to check the end of file which even consist of reading operation
        if (d.get_num() == NO)
        {
            d.update_dishname(str1);
            d.update_price(num);
            d.update_type(str2);
            d.update_discount(dis);
            d.update_cuisine(str3);
            d.update_course(str4);
            // move the ponter to current position -1
            int pos = sizeof(d);
            file1.seekp(-pos, ios ::cur);
            // write object to customer.txt file
            file1.write((char *)&d, sizeof(d));
        }
    }
    file1.close();
}

void food_operation ::delete_dish()
{
    int no;
    cout << "ENTER ID OF DISH :";
    cin >> no;
    fflush(stdin);

    ofstream file2;
    file2.open("buffer.txt", ios ::out | ios ::binary);
    file.open("dishes.txt", ios::in | ios ::binary);
    if (!file1)
    {
        cout << "FILE NOT FOUND....";
    }
    else
    {
        file1.read((char *)&d, sizeof(d));
        while (!file1.eof())
        {
            if (no != d.get_num())
            {
                file2.write((char *)&d, sizeof(d));
            }
            file1.read((char *)&d, sizeof(d));
        }
    }
    file2.close();
    file1.close();
    remove("dishes.txt");
    rename("buffer.txt", "dish.txt");
}

/****************************************************************************************************************************************************/
restaurant_info r;
special_offers o;
fstream file3;
void restaurant_info ::menu()
{
    d.show_all();
}

void restaurant_info ::timings()
{
    cout << "-----------------------------------------------------------" << endl;
    cout << "ON NORMAL DAYS------------------->FROM 9:00 AM TO 11:00 PM " << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "ON WEEKENDS --------------------->FROM 10:00 AM TO 10:00 PM" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "ON FESTIVE OCCCASSIONS ---------->FROM 12:00 PM TO 5:00 PM " << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "SPECIAL OFFERS AT --------------->FROM 1:00 PM TO 3:00 PM " << endl;
    cout << "-----------------------------------------------------------" << endl;
}

void restaurant_info ::get_employee()
{
    fflush(stdin);
    cout << "ENTER NAME OF THE EMPLOYEE :";
    cin >> name;
    fflush(stdin);
    cout << "ENTER ID OF THE EMPLOYEE :";
    cin >> id;
    fflush(stdin);
    cout << "ENTER DESIGNATION :";
    cin >> designation;
    fflush(stdin);
}

void restaurant_info ::put_employee()
{
    cout << setw(3) << id
         << setw(15) << name
         << setw(10) << designation << endl;
}

void restaurant_info ::add_employee()
{
    char ch = 'y';

    file3.open("employee.txt", ios ::app | ios ::binary);
    while (ch == 'y' || ch == 'Y')
    {
        r.get_employee();
        file3.write((char *)&r, sizeof(r));

        cout << "ADD MORE RECORDS.....(Y/N)?";
        cin >> ch;
        fflush(stdin);
    }
    file3.close();
}
void restaurant_info ::display_employee()
{
    ifstream file3("employee.txt", ios ::in | ios::binary);
    if (!file3)
    {
        cout << "FILE NOT FOUND" << endl;
    }
    else
    {

        file3.read((char *)&r, sizeof(r));
        while (!file3.eof())
        {
            r.put_employee();
            file3.read((char *)&r, sizeof(r));
        }
    }
    file3.close();
}

void restaurant_info ::delete_employee()
{
    int no;
    cout << "ENTER EMPLOYEE ID :";
    cin >> no;
    fflush(stdin);

    ofstream file4;
    file4.open("tempp.txt", ios ::out | ios ::binary);
    file3.open("employee.txt", ios::in | ios ::binary);
    if (!file3)
    {
        cout << "FILE NOT FOUND....";
    }
    else
    {
        file3.read((char *)&r, sizeof(r));
        while (!file3.eof())
        {
            if (no != r.get_idemp())
            {
                file4.write((char *)&r, sizeof(r));
            }
            file3.read((char *)&r, sizeof(r));
        }
    }
    file4.close();
    file3.close();
    remove("employee.txt");
    rename("tempp.txt", "employee.txt");
}

/**************************************************************************************************************************************/
user u;
fstream fil;
void user ::get_user()
{
    fflush(stdin);
    cout << "ENTER NAME :";
    cin >> user_name;
    fflush(stdin);

    cout << "ENTER PHONE NUMBER :";
    cin >> phone;
    fflush(stdin);

    cout << "ENTER PASSWORD IN NUMERICAL DIGITS :";
    cin >> password;
    fflush(stdin);

    cout << "ENTER YOUR ADDRESS :";
    cin >> address;
    fflush(stdin);
}

void user ::put_user()
{
    cout << setw(15) << user_name
         << setw(12) << phone
         << setw(10) << password
         << setw(20) << endl;
}
void user ::signup()
{

    fil.open("user.txt", ios ::app | ios ::binary);
    u.get_user();
    fil.write((char *)&u, sizeof(u));
    fil.close();
}

void user ::login()
{

    int pass;
    char use_name[15];

    cout << "ENTER USERNAME :";
    cin >> use_name;
    fflush(stdin);

    cout << "ENTER PASSWORD  :";
    cin >> pass;
    fflush(stdin);

    fil.read((char *)&u, sizeof(u));
    while (!fil.eof())
    {
        if (pass == password && strcmp(use_name, user_name) == 0)
        {
            cout << "YOU HAVE SUCCESSFULLY LOGGED IN TO THE PAGE !!!" << endl;
            cout << "YOU CAN NOW ORDER ANY OF THE FOLLOWING DISHES!!" << endl;

            break;
        }
        fil.read((char *)&u, sizeof(u));
    }
    cout << "PLEASE FIRST REGISTER TO THE PAGE FIRST..." << endl;
    signup();
    fil.close();
}

void user ::order_food()
{
    cout << setw(5) << "num"
         << setw(15) << "dishname"
         << setw(5) << "price"
         << setw(10) << "veg_nonveg"
         << setw(10) << "discount"
         << setw(15) << "cuisine"
         << setw(15) << "course" << endl;
    d.show_all();
    char ch = 'y';
    bill = 0;
    ifstream file1("dishes.txt", ios ::in | ios::binary);
    while (ch == 'y' || ch == 'Y')
    {

        cout << "ENTER THE DISH YOU WANT TO ORDER :";
        cin >> dish_order;
        fflush(stdin);

        cout << "ENTER QUANTITY :";
        cin >> quantity;
        fflush(stdin);

        cout << "ENTER PRICE ";
        cin >> price;
        fflush(stdin);

        bill = ((quantity * price) - discount) + bill;
        cout << "ADD MORE DISHES.....(Y/N) :";
        cin >> ch;
    }
    o.offer();
    cout << "TOTAL BILL IS :" << bill << endl;
    cout << "HOPE YOU LIKED OUR FOOD AND SERVICES !!!!!" << endl;
    cout << "PLEASE VISIT US AGAIN !!" << endl;
    cout << "HAVE A GOOD DAY !!!" << endl;
}

/////////////////////////////////////////////////////////////////MENU DRIVEN PROGRAM//////////////////////////////////////////////////////////////////
int main()
{

    string un;
    string pass;
    int flag = 0;
    /////////////////////////////////////////////////// RESTRAUNT MANAGEMENT SYSTEM ////////////////////////////////////////////////////////////////////
    cout << "------------------------------------------RESTAURAUNT MANAGEMENT SYSTEM-----------------------------------------------" << endl;
    cout << "********************************************************************************************************************" << endl;
    cout << "|                                                                                                                   |" << endl;
    cout << "|                                                                                                                   |" << endl;
    cout << " ------------------------------------------WELCOME TO CAPE DESERT HOTEL----------------------------------------------" << endl;
    cout << "|                                                                                                                   |" << endl;
    cout << "|                                                                                                                   |" << endl;
    cout << "*********************************************************************************************************************" << endl;
    cout << "ENTER ANY KEY ";
    getch();
    system("cls");
    int option;
    int option1;
    int option2;
    int option3;
    int option4;
    int option5;
    int option6;
    int lag = 0;
label1:
    while (1)
    {
        system("cls");
        cout << "1. USER " << endl;
        cout << "2. ADMIN " << endl;
        cout << "3. INFO " << endl;
        cout << "4. EXIT " << endl;
        cout << "ENTER YOUR CHOICE  :";
        cin >> option;
        switch (option)
        {
        case 1: //// from first loop
        {
            while (1)
            {
                system("cls");
                cout << "YOU CAN PERFORM THE FOLLOWING OPERATIONS THAT MUST BE PERFORMED FOR ORDERING FOOD ONLINE :" << endl;
                cout << "1. SIGNUP TO THE PAGE " << endl;
                cout << "2. LOGIN TO THE PAGE " << endl;
                cout << "3. ORDER FOOD (IF LOGGED IN ON THE PAGE) " << endl;
                cout << "4. EXIT " << endl;
                cout << "ENTER ANY OPTION FROM ABOVE ";
                cin >> option2;
                switch (option2)
                {
                case 1:

                {
                    u.signup();
                    cout << "ENTER ANY KEY TO VIEW MAIN USER PAGE :";
                    getch();
                    break;
                }
                case 2:
                {
                    u.login();
                    cout << "ENTER ANY KEY TO VIEW MAIN USER PAGE :";
                    getch();
                    break;
                }
                case 3:
                {
                    u.order_food();
                    cout << "ENTER ANY KEY TO VIEW MAIN USER PAGE :";
                    getch();
                    break;
                }
                case 4:
                {

                    cout << "ENTER ANY KEY TO VIEW MAIN USER PAGE :";
                    getch();
                    goto label1;
                    break;
                }
                default:
                {
                    cout << "WRONG KEY ENTER :" << endl;
                    cout << "ENTER ANY KEY TO VIEW MAIN USER PAGE :";
                    getch();
                    break;
                }
                }
            }
            cout << "PRESS ANT KEY RO EXIT ";
            getch();
            break;
        }
        case 2: // from first loop
        {
            cout << "ENTER THE LOGIN CREDENTIAL" << endl;
            cout << "ENTER USER NAME :";
            cin >> un;
            fflush(stdin);
            cout << "ENTER PASSWORD :";
            cin >> pass;
            fflush(stdin);

            if (un == "admin" && pass == "password")
            {
                cout << "SUCESSFULLY LOGGED IN" << endl;
                lag = 1;
            }
            else
            {
                cout << "PLEASE TRY AGAIN" << endl;
                cout << "ENTER THE LOGIN CREDENTIAL AGAIN :" << endl;
                cout << "ENTER USER NAME :";
                cin >> un;
                fflush(stdin);
                cout << "ENTER PASSWORD :";
                cin >> pass;
                fflush(stdin);
                if (un == "admin" && pass == "password")
                {
                    cout << "SUCESSFULLY LOGGED IN" << endl;
                    lag = 1;
                }
                else
                {
                    cout << "CAN'T TRY ANY MORE" << endl;
                }
            }
            if (lag == 1)
            {
            label2:
                while (1)
                {
                    system("cls");
                    cout << " NOW YOU CAN PERFORM THE FOLLOWINF FUNCTION :" << endl;
                    cout << "1. USER RELATED INFO :" << endl;
                    cout << "2. EMPLOYEE RELATED INFO " << endl;
                    cout << "3. RESTAURANT RELATED CHANGES :" << endl;
                    cout << "4. EXIT FROM HERE " << endl;
                    cout << "ENTER ANY OPTION FROM ABOVE :";
                    cin >> option3;
                    switch (option3)
                    {
                    case 1:
                    {
                        while (1)
                        {
                            system("cls");
                            cout << "**************MENU****************" << endl;
                            cout << "1. ADD NEW CUSTOMER " << endl;
                            cout << "2. DISPLAY ALL CUSTOMERS " << endl;
                            cout << "3. DISPLAY PARTICULAR CUSTOMER " << endl;
                            cout << "4. DELETE PARTICULAR CUSTOMER " << endl;
                            cout << "5. EDIT CUSTOMER RECORD " << endl;
                            cout << "6. EXIT " << endl;
                            cout << "ENTER ANY OPTION :";
                            cin >> option4;
                            switch (option4)
                            {
                            case 1:
                            {
                                a.add_customer();
                                cout << "ENTER ANY KEY FOR ADMIN MAIN MENU.......";
                                getch();
                                break;
                            }
                            case 2:
                            {
                                cout << "----------------------------------------------------------------------\n";
                                cout << setw(3) << "id" << setw(15) << "name" << setw(10) << "date" << endl;
                                cout << "-----------------------------------------------------------------------\n";
                                a.display_all();
                                cout << "-----------------------------------------------------------------------\n";
                                cout << "PRESS ANY KEY FOR ADMIN MAIN MENU.......";
                                getch();
                                break;
                            }

                            case 3:
                            {
                                a.display_particular();
                                cout << "PRESS ANY KEY FOR ADMIN MAIN MENU.....";
                                getch();
                                break;
                            }
                            case 4:
                            {
                                a.delete_customer();
                                cout << "PRESS ANY KEY FOR ADMIN MAIN MENU.....";
                                getch();
                                break;
                            }
                            case 5:
                            {
                                a.edit_customer();
                                cout << "PRESS ANY KEY FOR ADMIN MAIN MENU.....";
                                getch();
                                break;
                            }
                            case 6:
                            {
                                cout << "YOU HAVE PRESSED A WRONG KEY " << endl;
                                cout << "PRESS ANY KEY FOR ADMIN MAIN MENU.....";
                                getch();
                                goto label2;
                                break;
                            }

                            default:
                            {
                                cout << "INCORRECT OPTION , PRESS ANY KEY FOR ADMIN MAIN MENU :";
                                getch();
                                break;
                            }
                            }
                        }
                        cout << "press any key to exit ";
                        getch();
                        break;
                    }

                    case 2:
                    {
                        while (1)
                        {
                            system("cls");
                            cout << "**************MENU****************" << endl;
                            cout << "1. ADD NEW EMPLOYEE " << endl;
                            cout << "2. DISPLAY ALL EMPLOYEE" << endl;
                            cout << "3. DELETE PARTICULAR  EMPLOYEE " << endl;
                            cout << "4. EXIT " << endl;
                            cout << "ENTER ANY OPTION :";
                            cin >> option1;
                            fflush(stdin);

                            switch (option1)
                            {

                            case 1:
                            {
                                r.add_employee();
                                cout << "ENTER ANY KEY FOR ADMIN MAIN MENU.......";
                                getch();
                                break;
                            }
                            case 2:
                            {
                                cout << "----------------------------------------------------------------------\n";
                                cout << setw(3) << "id" << setw(15) << "name" << setw(15) << "desigantion" << endl;
                                cout << "-----------------------------------------------------------------------\n";
                                r.display_employee();
                                cout << "-----------------------------------------------------------------------\n";
                                cout << "PRESS ANY KEY FOR ADMIN MAIN MENU.......";
                                getch();
                                break;
                            }

                            case 3:
                            {
                                r.delete_employee();
                                cout << "PRESS ANY KEY FOR ADMIN MAIN MENU.....";
                                getch();
                                break;
                            }

                            case 4:
                            {
                                cout << "ENTER ANY KEY TO EXIT ";
                                getch();
                                goto label2;
                                break;
                            }

                            default:
                            {
                                cout << "INCORRECT OPTION , PRESS ANY KEY FOR ADMIN MAIN MENU :";
                                getch();
                                break;
                            }
                            }
                        }
                        cout << "press any key to exit ";
                        getch();
                        break;
                    }

                    case 3:
                    {
                        while (1)
                        {
                            system("cls");
                            cout << "**************MENU****************" << endl;
                            cout << "1. ADD NEW DISH" << endl;
                            cout << "2. DISPLAY ALL DISH" << endl;
                            cout << "3. DISPLAY PARTICULAR DISH" << endl;
                            cout << "4. DELETE INFORMATION OF PARTICULAR DISH" << endl;
                            cout << "5. MODIFY INFORMATION RELATED TO ANY DISH" << endl;
                            cout << "6. EXIT " << endl;
                            cout << "ENTER ANY OPTION :";
                            cin >> option5;
                            fflush(stdin);

                            switch (option5)
                            {

                            case 1:
                            {
                                d.add_dish();
                                cout << "ENTER ANY KEY FOR ADMIN MAIN MENU.......";
                                getch();
                                break;
                            }
                            case 2:
                            {
                                cout << "----------------------------------------------------------------------\n";
                                cout << setw(5) << "id"
                                     << setw(15) << "dishname"
                                     << setw(5) << "price"
                                     << setw(10) << "type"
                                     << setw(10) << "discount"
                                     << setw(15) << "cuisine"
                                     << setw(15) << "course" << endl;
                                cout << "-----------------------------------------------------------------------\n";
                                d.show_all();
                                cout << "-----------------------------------------------------------------------\n";
                                cout << "PRESS ANY KEY FOR ADMIN MAIN MENU.......";
                                getch();
                                break;
                            }
                            case 3:
                            {
                                d.show_particular();
                                cout << "ENTER ANY KEY TO EXIT ";
                                getch();
                                break;
                            }

                            case 4:
                            {
                                d.delete_dish();
                                cout << "PRESS ANY KEY FOR ADMIN MAIN MENU.....";
                                getch();
                                break;
                            }

                            case 5:
                            {
                                d.edit_dish();
                                getch();
                                break;
                            }
                            case 6:
                            {
                                cout << "ENTER ANY KEY TO EXIT ";
                                getch();
                                goto label2;
                                break;
                            }

                            default:
                            {
                                cout << "INCORRECT OPTION , PRESS ANY KEY FOR ADMIN MAIN MENU :";
                                getch();
                                break;
                            }
                            }
                        }
                    }
                    case 4:
                    {

                        cout << "press any key to exit ";
                        getch();
                        goto label1;
                        break;
                    }

                    default:
                    {

                        cout << "press any key to exit ";
                        getch();
                        break;
                    }
                        cout << "press any key to exit ";
                        getch();
                        break;
                    }
                }
            }

            cout << "press any key to exit ";
            getch();
            break;
        }
        case 3: // from first loop
        {
            while (1)
            {
                system("cls");
                cout << "YOU CAN PERFORM FOLLOWING OPERATIONS :" << endl;
                cout << "1. SHOW MENU " << endl;
                cout << "2. SHOW TIMINGS " << endl;
                cout << "3. EXIT " << endl;
                cout << "ENTER OPTION :";
                cin >> option6;
                switch (option6)
                {
                case 1:
                {
                    cout << "-----------------------------------------------------------------------------------------------" << endl;
                    cout << setw(5) << "id"
                         << setw(15) << "dishname"
                         << setw(5) << "price"
                         << setw(10) << "type"
                         << setw(10) << "discount"
                         << setw(15) << "cuisine"
                         << setw(15) << "course" << endl;
                    r.menu();
                    cout << "-----------------------------------------------------------------------------------------------" << endl;
                    getch();
                    break;
                }
                case 2:
                {
                    r.timings();
                    getch();
                    break;
                }
                case 3:
                {
                    cout << "ENTER ANY KEY TO EXIT" << endl;
                    getch();
                    goto label1;
                    break;
                }
                default:
                {
                    cout << "PRESS ANY CORRECT KEY ";
                    getch();
                    break;
                }
                }
            }
            cout << "PRESS ANY KEY TO EXIT ";
            getch();
            break;
        }

        case 4: // from first loop
        {
            cout << "press any key to exit ";
            getch();
            exit(0);
            break;
        }

        default: // from first loop
        {
            cout << "SORRY YOU HAVE ENTERD A WRONG KEY " << endl;
            cout << "press any key to exit ";
            getch();
            break;
        }
        }
    }
}
