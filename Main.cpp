#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
using namespace std;

struct Time {
    string hour, minute, day, month, year;
};

struct Train {
    string tripID, trainID;
    string departure, destination;
    string passenger;
    Time departTime, arrivalTime, departDate, arrivalDate;
};

struct Node {
    Train info;
    Node *next;
};

Node *sp;
Node *sortHead;

void init();
void push(Train x);
int pop(Train &x);
void input_train_info(Train &train);
void input_train_info_from_file(Train &train);
void create_sort_list();
void train_sorting_asc();
void traverse(Node *peak);

int main()
{
    Train train;
    int choose;
    init();
    do {
        system("cls");
        cout << "1. Add train\n"
            << "2. Add train from file\n"
            << "3. Remove train\n"
            << "4. Sort train ascending\n"
            << "5. Quit\n"
            << "Choose: ";
        cin >> choose;
        switch (choose)
        {
            case 1:
            {
                input_train_info(train);
                break;
            }
            case 2:
            {
                input_train_info_from_file(train);
                push(train);
                break;
            }
            case 3:
            {
                if (pop(train))
                    cout << "Trip ID: " << train.tripID << endl
                        << "Train ID: " << train.trainID << endl
                        << "Departure: " << train.departure << endl
                        << "Destination: " << train.destination << endl
                        << "Depart time: " << train.departTime.hour << ":" << train.departTime.minute << endl
                        << "Arrival Time: " << train.arrivalTime.hour << ":" << train.arrivalTime.minute << endl
                        << "Depart Date: " << train.departDate.day << "/" << train.departDate.month << "/" << train.departDate.year << endl
                        << "Arrival Date: " << train.arrivalDate.day << "/" << train.arrivalDate.month << "/" << train.arrivalDate.year << endl
                        << "The number of passengers: " << train.passenger;
                else
                    cout << "There is no train";
                break;
            }
            case 4:
            {
                create_sort_list();
                train_sorting_asc();
                traverse(sortHead);
                break;
            }
            default:
                cout << "You just quitted";
        }
        _getch();
    } while (choose >= 1 && choose <= 4);
    _getch();
    return 0;
}

void init()
{
    sp = NULL;
    sortHead = NULL;
}

void push(Train x)
{
     Node *p;
     p = new Node;
     p->info = x;
     p->next = sp;
     sp = p;
}

int pop(Train &x)
{
    if (sp != NULL)
    {
        Node *p = sp;
        x = p->info;
        sp = p->next;
        delete p;
        return 1;
    }
    return 0;
}

void input_train_info(Train &train)
{
    cout << "Input trip ID: ";
    cin >> train.tripID;
    cout << "Input train ID: ";
    cin >> train.trainID;
    cout << "Input departure: ";
    cin.ignore();
    getline(cin, train.departure); 
    cout << "Input destination: ";
    getline(cin, train.destination);
    cout <<  "Input depart time(HH:MM): ";
    getline(cin, train.departTime.hour, ':');
    getline(cin, train.departTime.minute);
    cout << "Input arrival time(HH:MM): ";
    getline(cin, train.arrivalTime.hour, ':');
    getline(cin, train.arrivalTime.minute);
    cout << "Input depart date(dd/mm/yyyy): ";
    getline(cin, train.departDate.day, '/');
    getline(cin, train.departDate.month, '/');
    getline(cin, train.departDate.year);
    cout << "Input arrival date(dd/mm/yyyy): ";
    getline(cin, train.arrivalDate.day, '/');
    getline(cin, train.arrivalDate.month, '/');
    getline(cin, train.arrivalDate.year);
    cout << "Input the number of passengers: ";
    cin >> train.passenger;
}

void input_train_info_from_file(Train &train)
{
    ifstream inTrain;
    inTrain.open("Train_List.txt");
    if (inTrain.is_open())
    {
        while (!inTrain.eof())
        {
            getline(inTrain, train.tripID, '#');
            getline(inTrain, train.trainID, '#');
            getline(inTrain, train.departure, '#');
            getline(inTrain, train.destination, '#');
            getline(inTrain, train.departTime.hour, ':');
            getline(inTrain, train.departTime.minute, '#');
            getline(inTrain, train.arrivalTime.hour, ':');
            getline(inTrain, train.arrivalTime.minute, '#');
            getline(inTrain, train.departDate.day, '/');
            getline(inTrain, train.departDate.month, '/');
            getline(inTrain, train.departDate.year, '#');
            getline(inTrain, train.arrivalDate.day, '/');
            getline(inTrain, train.arrivalDate.month, '/');
            getline(inTrain, train.arrivalDate.year, '#');
            getline(inTrain, train.passenger);
            if (!inTrain.eof())
                push(train);
        }
        cout << "Read file successfully";
        inTrain.close();
    }
    else
        cout << "Could not read the file";
}

void create_sort_list()
{
    Node *sortList;
    Node *origin = sp;
    while (origin != NULL)
    {
        sortList = new Node;
        sortList->info = origin->info;
        sortList->next = sortHead;
        sortHead = sortList;
        origin = origin->next;
    }
}

void train_sorting_asc()
{
    if (sp == NULL)
        return;
    else
    {
        Node *p, *q;
        p = sortHead;
        while (p != NULL)
        {
            q = p->next;
            while (q != NULL)
            {
                if (p->info.departDate.day > q->info.departDate.day)
                {
                    Train temp = p->info;
                    p->info = q->info;
                    q->info = temp;
                }
                q = q->next;
            }
            p = p->next;
        }
    }
}

void traverse(Node *peak)
{
    Node *p;
    p = peak;
    while(p != NULL)
    {
        cout << p->info.trainID << endl;
        p = p->next;
    }
}