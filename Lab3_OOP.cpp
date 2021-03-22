#pragma warning(disable : 4996)
#include <iostream>
#include <ctime>

#define KST 30

using namespace std;

time_t t = time(0);   // отримуЇмо поточну дату та час
    tm* now = localtime(&t);

class Date {            //оголошенн€ класу дати
private:
    int day;
    int month;
    int year;

public:
    Date() { day = month = year = 0; }          //конструктор без параметр≥в
    Date(int d, int m, int y) { day = d; month = m; year = y; }         //конструктор ≥з трьома параметрами
    ~Date() {}          //деструктор

    // методи класу
    int SetDate(int d, int m, int y)        //встановити нову дату
    {
        if ((d < 1 || d > 31) || (m < 1 || m > 12))
        {
            cout << "Incorrectly entered date!!!" << endl;
            system("pause");
            return 0;
        }
        else
            day = d; month = m; year = y;
    }

    int Bissextile(int y)                   //перев≥рка чи Ї заданий р≥к високосним
    {
        return ((y % 100 != 0) && (y % 4 == 0)) || (y % 400 == 0);
    }
    int DaysInMonth(int m, int y)          //к≥льк≥сть дн≥в у введеному м≥с€ц≥
    {
        int arr[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        if (Bissextile(y))
            arr[1] = 29;
        return arr[m - 1];
    }

    //дружнЇ перевантаженн€ операц≥й вводу та виводу
    friend istream& operator>> (istream& in, Date& date);
    friend ostream& operator<< (ostream& out, const Date& date);

    Date operator--(int)
    {
        if (day-- < 1)
        {
            day = DaysInMonth(month - 1, year);
            if (month - 1 == 0)
                day = DaysInMonth(12, year);
            month--;
        }
        if (month < 1)
        {
            month = 12;
            year--;
        }
        return *this;
    }

    bool operator>=(Date &d)
    {
        for (int i = 0; i < KST; i++)
        {
            if (now->tm_mday - this->day + i >= now->tm_mday - d.day + i)
                return true;
        }
        return false;
    }
};

istream& operator>> (istream& in, Date& d)
{
    cout << "\n" << "Enter the day: ";
    in >> d.day;
    cout << "Enter the month: ";
    in >> d.month;
    cout << "Enter the year: ";
    in >> d.year;
    d.SetDate(d.day, d.month, d.year);
    return in;
}

ostream& operator<< (ostream& out, const Date& d)
{
    out << "Date in format d/m/y: " << d.day << "/" << d.month << "/" << d.year << " р." << endl;
    out << "Date in format y-m-d: " << d.year << "-" << d.month << "-" << d.day << endl;
    return out;
}

void sort(Date* d, int k);
void print(Date* d, int k);
bool check(Date* d, int k);

int main()
{
    setlocale(LC_ALL, "Ukrainian");
    Date date[KST];
    int kst = 0;
    int days = 0;

    cout << "Enter the number of dates: ";
    cin >> kst;
    for (int i = 0; i < kst; i++)
        cin >> date[i];

    cout << endl << "Sorted: " << endl;
    sort(date, kst);
    print(date, kst);

    cout << endl << "Number of days to reduce each date: ";
    cin >> days;
    for (int i = 0; i < kst; i++)
    {
        for (int j = 0; j < days; ++j)
            date[i]--;
    }
    print(date, kst);

    if (check(date, kst))
        cout << endl << "Dates are sorted." << endl;
    else
        cout << endl << "Dates aren't sorted." << endl;
    system("pause");
    return 0;
}

void sort(Date* d, int k)
{
    for (int i = 1; i < k; i++)
    {
        for (int j = i; j > 0 && d[j] >= d[j - 1]; j--)
        {
            Date tmp = d[j - 1];
            d[j - 1] = d[j];
            d[j] = tmp;
        }
    }
}

void print(Date* d, int k)
{
    for (int i = 0; i < k; i++)
        cout << i + 1 << ". " << d[i];
}

bool check(Date* d, int k)
{
    for (int i = 1; i < k; i++)
    {
        for (int j = i; j > 0; j--)
        {
            while (d[j] >= d[j - 1])
                return false;
                
        }
    }
    return true;
}