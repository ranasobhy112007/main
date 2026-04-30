
#include<iostream>
#include <windows.h>
#include <cstring>
#include <fstream>
#include <string>
#include <cstdlib>
#define maxMoodStorage 100
#define max_users 10
using namespace std;
int userscount = 0, moodCount = 0, logentry;

struct UserAccount
{
    int userid;
    string username;
    string password;
};

struct date
{
    int day;
    int month;
    int year;
};

struct moodEntry
{
    date time;
    int moodLevel;
    string moodtype;
    string note;
};

struct MoodStatistics {
    int TotalEntries;
    int HappyCount;
    int SadCount;
    int AngryCount;
    int StressedCount;
    int CalmCount;
};
UserAccount users[max_users];
UserAccount currentuser;
moodEntry moods[maxMoodStorage];
MoodStatistics statistics[12];
date m[max_users];

// functions declaration
int loadfromfile();
void showLogMenu();
void logmenu();
void signup();
void login();
void closing();
void savetofile();
void addMood(moodEntry moods[], int&);
void saveMoodsToFile();
int loadMoodsFromFile(moodEntry moods[]);
void preStoredMoods();
void updateFuncion(moodEntry moods[], int&);
void Delete(moodEntry moods[], int&);
void display(moodEntry moods[], int&);
void SearchByDate(moodEntry moods[], int&);
void SearchByType(moodEntry moods[], int&);
void SearchMood();
void AnalyzeMoodFrequency(moodEntry moods[], int, int);
void AverageMoodlevel(int&, int, float&, float&, float&, float&, float&);
void DisplayStatistics(int);
void UpdateAllStatistics(moodEntry moods[], int moodCount);



int main() {
    showLogMenu();
    savetofile();
    preStoredMoods();
    moodCount = loadMoodsFromFile(moods);
    addMood(moods, moodCount);
    saveMoodsToFile();
    updateFuncion(moods, moodCount);
    Delete(moods, moodCount);
    display(moods, moodCount);
    SearchByDate(moods, moodCount);
    SearchByType(moods, moodCount);
    SearchMood();

    int targetmonth;
    cout << "\n=============================================" << endl;
    cout << "Enter the month to show statistics:";
    cin >> targetmonth;

    UpdateAllStatistics(moods, moodCount);
    DisplayStatistics(targetmonth);
    return 0;
}

int loadfromfile()
{
    ifstream infile("users.txt");
    int count = 0;
    if (infile.is_open())
    {
        while (count < max_users)
        {
            if (!(infile >> users[count].username >> users[count].password))
                break;
            users[count].userid = count + 1;
            count++;
        }
        infile.close();
    }
    return count;
}

void logmenu()
{
    system("cls");
    cout << "╔════════════════════════════════════════════════════╗\n";
    cout << "║        ♥️ Welcome to Digital Mood Tracker ♥️       ║   \n";
    cout << "╠════════════════════════════════════════════════════╣\n";
    cout << "║                                                    ║\n";
    cout << "║ Are you new user?👋                                ║\n";
    cout << "║ [1] Log in🔑                                       ║\n";
    cout << "║ [2] Sign up📝                                      ║ \n";
    cout << "║ [3] Exit❎                                         ║\n";
    cout << "║                                                    ║\n";
    cout << "╠════════════════════════════════════════════════════╣\n";
    cout << "║ 📊 Total Registered Users: " << userscount << "/" << max_users << "                    ║\n";
    cout << "╚════════════════════════════════════════════════════╝\n";
    cout << " Your entry: ";
}

void closing()
{
    system("cls");
    cout << "Thank you for using Digital Mood Tracker! Goodbye!👋\n";
    system("timeout /t 4 > nul");
    exit(0);
}

void signup()
{
    system("cls");
    int entry3;
    string newname;
    string newpass;
    string confpass;

    if (userscount < max_users)
    {
        cout << "╔═════════════════════════════════════════╗\n";
        cout << "║                Sign up📝                ║\n";
        cout << "╠═════════════════════════════════════════╣\n";
        cout << "║ ┌──────────────────────────────┐        ║\n";
        cout << "║ │ 🪪User name:_                │        ║\n";
        cout << "║ └──────────────────────────────┘        ║\n";
        cout << "║ ┌──────────────────────────────┐        ║\n";
        cout << "║ │🔒Password:_                  │        ║\n";
        cout << "║ └──────────────────────────────┘        ║\n";
        cout << "║ ┌──────────────────────────────┐        ║\n";
        cout << "║ │🔒Confirm password:_          │        ║\n";
        cout << "║ └──────────────────────────────┘        ║\n";
        cout << "║                                         ║\n";
        cout << "║ 📝Notes:                                ║\n";
        cout << "║ - User name must be unique.             ║\n";
        cout << "║ - Passwords must match.                 ║\n";
        cout << "╠═════════════════════════════════════════╣\n";
        cout << "║                                         ║\n";
        cout << "║ [1] Create account📝                    ║\n";
        cout << "║ [2] Already have an account? Log in✔️   ║\n";
        cout << "║ [3] Return to home screen...            ║\n";
        cout << "║                                         ║\n";
        cout << "╚═════════════════════════════════════════╝\n";
        cout << " Your entry: ";
        cin >> entry3;
        if (entry3 == 3)
        {
            return; // Return to main menu loop
        }
        else if (entry3 == 2)
        {
            login();
            return;
        }
        else if (entry3 != 1)
        {
            system("cls");
            cout << "╔════════════════════════════════════╗\n";
            cout << "║           Invalid Entry!           ║\n";
            cout << "╠════════════════════════════════════╣\n";
            cout << "║                                    ║\n";
            cout << "║      Returning to home screen...   ║\n";
            cout << "║                                    ║\n";
            cout << "╚════════════════════════════════════╝\n";
            cin.clear();
            cin.ignore(10000, '\n');
            system("timeout /t 4 > nul");
            return;
        }
        cout << "Enter your user name: ";
        cin >> newname;
        cout << "Enter your password: ";
        cin >> newpass;
        cout << "Confirm your password: ";
        cin >> confpass;

        if (newpass == confpass)
        {
            bool usernameExists = false;
            for (int i = 0; i < userscount; ++i)
            {
                if (users[i].username == newname)
                {
                    usernameExists = true;
                    break;
                }
            }

            if (usernameExists)
            {
                system("cls");
                cout << "╔══════════════════════════════════╗\n";
                cout << "║        ❌Username exists         ║\n";
                cout << "╠══════════════════════════════════╣\n";
                cout << "║ Username already taken!          ║\n";
                cout << "╚══════════════════════════════════╝\n";
                system("timeout /t 4 > nul");
                signup();
                return;
            }

            users[userscount].username = newname;
            users[userscount].password = newpass;
            users[userscount].userid = userscount + 1;
            userscount++;
            savetofile();
            system("cls");
            cout << "╔═════════════════════════════════╗\n";
            cout << "║             Success✅           ║\n";
            cout << "╠═════════════════════════════════╣\n";
            cout << "║                                 ║\n";
            cout << "║   Account created successfully! ║\n";
            cout << "║                                 ║\n";
            cout << "╚═════════════════════════════════╝\n";
            cout << "\nYou are being redirected to the homepage to log in...";
            system("timeout /t 5 > nul");
            return; // Return to main menu loop
        }
        else
        {
            system("cls");
            cout << "╔══════════════════════════════════╗\n";
            cout << "║            ❌Mismatch            ║\n";
            cout << "╠══════════════════════════════════╣\n";
            cout << "║ Passwords do not match!          ║\n";
            cout << "║ Please try again...              ║\n";
            cout << "╚══════════════════════════════════╝\n";
            system("timeout /t 4 > nul");
            signup(); // Recursive call
        }
    }
    else
    {
        system("cls");
        cout << "╔═══════════════════════════════════════════╗\n";
        cout << "║    ❌Sorry! Maximum user limit reached    ║\n";
        cout << "╠═══════════════════════════════════════════╣\n";
        cout << "║                                           ║\n";
        cout << "║ Cannot create more accounts..             ║\n";
        cout << "║                                           ║\n";
        cout << "║ [1] 🗝️Log in                              ║\n";
        cout << "║ [2] ❌Exit                                ║\n";
        cout << "║                                           ║\n";
        cout << "╚═══════════════════════════════════════════╝\n";
        cout << " Your entry: ";
        cin >> entry3;
        if (entry3 == 1)
        {
            login();
        }
        else if (entry3 == 2)
        {
            closing();
        }
        else
        {
            cin.clear();
            cin.ignore(10000, '\n');
            return;
        }
    }
}

void login()
{
    system("cls");
    int entry1;
    int entry2;
    string namecheck;
    string passcheck;
    bool loginSuccess = false;

    cout << "╔════════════════════════════════════════╗\n";
    cout << "║                Log in🔑                ║\n";
    cout << "╠════════════════════════════════════════╣\n";
    cout << "║ ┌──────────────────────────────┐       ║\n";
    cout << "║ │👤User name:_                 │       ║\n";
    cout << "║ └──────────────────────────────┘       ║\n";
    cout << "║ ┌──────────────────────────────┐       ║\n";
    cout << "║ │🔒Password:_                  │       ║\n";
    cout << "║ └──────────────────────────────┘       ║\n";
    cout << "╠════════════════════════════════════════╣\n";
    cout << "║                                        ║\n";
    cout << "║ [1] Log in✔️                           ║\n";
    cout << "║ [2] Don't have an account? Sign up📝   ║\n";
    cout << "║ [3] Return to home screen...           ║\n";
    cout << "║                                        ║\n";
    cout << "╚════════════════════════════════════════╝\n";
    cout << " Your entry: ";
    cin >> entry1;

    if (entry1 == 1)
    {
        cout << "Enter your user name: ";
        cin >> namecheck;
        cout << "Enter your password: ";
        cin >> passcheck;

        for (int i = 0; i < userscount; ++i)
        {
            if (users[i].username == namecheck && users[i].password == passcheck)
            {
                loginSuccess = true;
                break;
            }
        }

        if (loginSuccess)
        {
            return;
        }
        else
        {
            system("cls");
            cout << "╔══════════════════════════════════╗\n";
            cout << "║             ❌Wrong              ║\n";
            cout << "╠══════════════════════════════════╣\n";
            cout << "║                                  ║\n";
            cout << "║   Invalid username or password!  ║\n";
            cout << "║                                  ║\n";
            cout << "║ [1] 🔁Try again                  ║\n";
            cout << "║ [2] 🔙Return to home screen      ║\n";
            cout << "║                                  ║\n";
            cout << "╚══════════════════════════════════╝\n";
            cout << " Your entry: ";
            cin >> entry2;
            if (entry2 == 1)
            {
                login(); // Recursive call for try again
            }
            else if (entry2 == 2)
            {
                return; // Return to main menu loop
            }
            else
            {
                system("cls");
                cout << "╔════════════════════════════════════╗\n";
                cout << "║           Invalid Entry!           ║\n";
                cout << "╠════════════════════════════════════╣\n";
                cout << "║                                    ║\n";
                cout << "║      Returning to home screen...   ║\n";
                cout << "║                                    ║\n";
                cout << "╚════════════════════════════════════╝\n";
                cin.clear();
                cin.ignore(10000, '\n');
                system("timeout /t 4 > nul");
                return;
            }
        }
    }
    else if (entry1 == 2)
    {
        signup();
    }
    else if (entry1 == 3)
    {
        return; // Return to main menu loop
    }
    else
    {
        system("cls");
        cout << "╔════════════════════════════════════╗\n";
        cout << "║           Invalid Entry!           ║\n";
        cout << "╠════════════════════════════════════╣\n";
        cout << "║                                    ║\n";
        cout << "║      Returning to home screen...   ║\n";
        cout << "║                                    ║\n";
        cout << "╚════════════════════════════════════╝\n";
        cin.clear();
        cin.ignore(10000, '\n');
        system("timeout /t 4 > nul");
        return;
    }
}

void showLogMenu()
{
    userscount = loadfromfile(); // Reload users each time
    for (int i = 0; i < userscount; ++i) {
        users[i].userid = i + 1;
        currentuser.userid = users[i].userid;
    }

    while (true) {
        logmenu();
        cin >> logentry;

        switch (logentry)
        {
        case 1:
            login();
            break;
        case 2:
            signup();
            break;
        case 3:
            closing();
            break;
        default:
            system("cls");
            cout << "╔════════════════════════════════════╗\n";
            cout << "║           Invalid Entry!           ║\n";
            cout << "╠════════════════════════════════════╣\n";
            cout << "║                                    ║\n";
            cout << "║         Please try again...        ║\n";
            cout << "║                                    ║\n";
            cout << "╚════════════════════════════════════╝\n";
            cin.clear();
            cin.ignore(10000, '\n');
            system("timeout /t 4 > nul");
            continue;
        }
    }
}

void savetofile()
{
    ofstream outfile("users.txt");
    if (outfile.is_open())
    {
        for (int i = 0; i < userscount; ++i)
        {
            outfile << users[i].username << " " << users[i].password << endl;
        }
        outfile.close();
    }
}

int loadMoodsFromFile(moodEntry moods[])
{
    int count = 0;
    ifstream in("inputData.txt");
    if (in.is_open())
    {
        while (count < maxMoodStorage)
        {
            if (!(in >> moods[count].time.day
                >> moods[count].time.month
                >> moods[count].time.year
                >> moods[count].moodtype
                >> moods[count].moodLevel
                >> moods[count].note))
            {
                break;
            }
            getline(in >> ws, moods[count].note);
            count++;
        }
    }
    in.close();
    return count;
}

void preStoredMoods()
{
    moods[0] = { 1, 4, 2026, 5, "Happy", "Finished my project" };
    moods[1] = { 2, 4, 2026, 3, "Calm", "Normal day" };
    moods[2] = { 3, 4, 2026, 2, "Stressed", "Exam coming up" };
    moods[3] = { 4, 4, 2026, 5, "sad", "did not pass the exam" };
    moods[4] = { 5, 4, 2026, 3, "Calm", "Normal day" };
    moods[5] = { 6, 4, 2026, 2, "Stressed", "Exam coming up" };
    moods[6] = { 7, 4, 2026, 5, "Happy", "passed the exam" };
    moods[7] = { 8, 4, 2026, 5, "Calm", "Normal day" };
    moods[8] = { 9, 4, 2026, 2, "happy", "a new semister comming up" };
}

void addMood(moodEntry moods[], int& moodCount)
{
    cout << "Enter the day\n";
    cin >> moods[moodCount].time.day;
    cout << "Enter the month\n";
    cin >> moods[moodCount].time.month;
    cout << "Enter the year\n";
    cin >> moods[moodCount].time.year;
    cout << "Enter the mood type \n";
    cout << "Happy\tSad\tAngry\tStressed\tcalm\n";
    cin >> moods[moodCount].moodtype;
    cout << "Enter the mood level from (1 - 5)\n";
    cin >> moods[moodCount].moodLevel;
    if (moods[moodCount].moodLevel > 5 || moods[moodCount].moodLevel < 1)
    {
        do
        {
            system("cls");
            cout << "╔════════════════════════════════════╗\n";
            cout << "║           Invalid Entry!           ║\n";
            cout << "╠════════════════════════════════════╣\n";
            cout << "║                                    ║\n";
            cout << "║      Enter Digits from 1 to 5      ║\n";
            cout << "║                                    ║\n";
            cout << "╚════════════════════════════════════╝\n";
            cin.clear();
            cin.ignore(10000, '\n');
            system("timeout /t 4 > nul");
            cin >> moods[moodCount].moodLevel;
        } while (moods[moodCount].moodLevel > 5 || moods[moodCount].moodLevel < 1);
    }
    cout << "Enter the note\n";
    cin >> moods[moodCount].note;
    moodCount++;
}

void saveMoodsToFile()
{
    ofstream out("inputData.txt");
    if (out.is_open())
    {
        for (int i = 0; i < moodCount; i++)
        {
            out << moods[i].time.day << " ";
            out << moods[i].time.month << " ";
            out << moods[i].time.year << " ";
            out << moods[i].moodtype << " ";
            out << moods[i].moodLevel << " ";
            out << moods[i].note << endl;

        }
        out.close();
        cout << "Data saved successfully";
    }
    else
    {
        cout << "Error!!";
    }
}


void updateFuncion(moodEntry moods[], int& moodCount)
{
    int indexDateUserUpdate = -1;
    int searchDay;
    int searchMonth;
    int searchYear;
    string newMoodtype;
    int newMoodLevel;
    string newNote;

    do {
        cout << "Enter day / month / year to update mood entry\n";
        cin >> searchDay >> searchMonth >> searchYear;



        for (int i = 0; i < moodCount; i++)
        {
            if (moods[i].time.day == searchDay
                && moods[i].time.month == searchMonth &&
                moods[i].time.year == searchYear)
            {
                indexDateUserUpdate = i;
                break;
            }
        }



        if (indexDateUserUpdate == -1)
        {
            system("cls");
            cout << "╔════════════════════════════════════╗\n";
            cout << "║           Invalid Entry!           ║\n";
            cout << "╠════════════════════════════════════╣\n";
            cout << "║                                    ║\n";
            cout << "║         Please try again...        ║\n";
            cout << "║                                    ║\n";
            cout << "╚════════════════════════════════════╝\n";
            cin.clear();
            cin.ignore(10000, '\n');
            system("timeout 4 > nul");
        }


        else
        {
            system("cls");
            cout << "╔════════════════════════════════════╗\n";
            cout << "║         Current Mood Entry         ║\n";
            cout << "╠════════════════════════════════════╣\n";
            cout << "║ Date: " << moods[indexDateUserUpdate].time.day << "/"
                << moods[indexDateUserUpdate].time.month << "/"
                << moods[indexDateUserUpdate].time.year << "\n";
            cout << "║ Mood Type:  " << moods[indexDateUserUpdate].moodtype << "\n";
            cout << "║ Mood Level: " << moods[indexDateUserUpdate].moodLevel << "\n";
            cout << "║ Note:       " << moods[indexDateUserUpdate].note << "\n";
            cout << "╚════════════════════════════════════╝\n";

            cout << "\nEnter the new mood type\n";
            cin >> newMoodtype;
            cout << "Enter the new mood level\n";
            cin >> newMoodLevel;
            cout << "Enter the new note\n";
            cin.ignore();
            getline(cin, newNote);



            moods[indexDateUserUpdate].moodtype = newMoodtype;
            moods[indexDateUserUpdate].moodLevel = newMoodLevel;
            moods[indexDateUserUpdate].note = newNote;
        }
    } while (indexDateUserUpdate == -1);

    system("cls");
    cout << "╔════════════════════════════════════╗\n";
    cout << "║       Updated Successfully!        ║\n";
    cout << "╠════════════════════════════════════╣\n";
    cout << "║ Date: " << moods[indexDateUserUpdate].time.day << "/"
        << moods[indexDateUserUpdate].time.month << "/"
        << moods[indexDateUserUpdate].time.year << "\n";
    cout << "║ Mood Type:  " << moods[indexDateUserUpdate].moodtype << "\n";
    cout << "║ Mood Level: " << moods[indexDateUserUpdate].moodLevel << "\n";
    cout << "║ Note:       " << moods[indexDateUserUpdate].note << "\n";
    cout << "╚════════════════════════════════════╝\n";
    system("timeout 4 > nul");
}

void Delete(moodEntry moods[], int& moodCount)
{

    system("timeout /t 4 > nul");
    int day, month, year;
    system("cls");
    cout << "╔════════════════════════════════════╗\n";
    cout << "║  Enter the date to delete          ║\n";
    cout << "╠════════════════════════════════════╣\n";

    cin >> day >> month >> year;

    ifstream in("inputData.txt");
    ofstream temp("temp.txt");

    bool found = false;

    if (in.is_open() && temp.is_open())
    {
        moodEntry m;

        while (in >> m.time.day >> m.time.month >> m.time.year
            >> m.moodtype >> m.moodLevel)
        {
            getline(in >> ws, m.note);

            if (m.time.day == day &&
                m.time.month == month &&
                m.time.year == year)
            {
                found = true;
                continue;
            }
            temp << m.time.day << " "
                << m.time.month << " "
                << m.time.year << " "
                << m.moodtype << " "
                << m.moodLevel << " "
                << m.note << endl;
        }

        in.close();
        temp.close();

        remove("inputData.txt");
        rename("temp.txt", "inputData.txt");


        moodCount = loadMoodsFromFile(moods);

        if (found)
        {
            system("cls");
            cout << "╔════════════════════════════════════╗\n";
            cout << "║      Deleted successfully          ║\n";
            cout << "╠════════════════════════════════════╣\n";
            cout << endl;
        }
        else
        {
            system("cls");
            cout << "╔════════════════════════════════════╗\n";
            cout << "║           Invalid Entry!           ║\n";
            cout << "╠════════════════════════════════════╣\n";
            cout << "║                                    ║\n";
            cout << "║      Date not found...             ║\n";
            cout << "║                                    ║\n";
            cout << "╚════════════════════════════════════╝\n";
        }
    }
    else
    {
        system("cls");
        cout << "╔════════════════════════════════════╗\n";
        cout << "║         *_*    File error!         ║\n";
        cout << "╠════════════════════════════════════╣\n";
        cout << endl;
    }
}

void display(moodEntry moods[], int& moodCount)
{
    int day, month, year;
    bool found = false;

    system("cls");
    cout << "╔════════════════════════════════════╗\n";
    cout << "║     Enter date to display          ║\n";
    cout << "╠════════════════════════════════════╣\n";
    cin >> day >> month >> year;

    for (int i = 0; i < moodCount; i++)
    {
        if (moods[i].time.day == day &&
            moods[i].time.month == month &&
            moods[i].time.year == year)
        {
            cout << "\n* Date: " << moods[i].time.day << "/"
                << moods[i].time.month << "/"
                << moods[i].time.year << endl;

            cout << "* Mood type: " << moods[i].moodtype << endl;
            cout << "* Mood Level: " << moods[i].moodLevel << endl;
            cout << "* Note: " << moods[i].note << endl;

            found = true;
        }
    }
    if (!found)
    {
        system("cls");
        cout << "╔════════════════════════════════════╗\n";
        cout << "║    No data found for this date!    ║\n";
        cout << "╠════════════════════════════════════╣\n";
    }
}







void out(moodEntry moods[], int i) {

    cout << "_________________________________________________________________";
    cout << "Date:" << moods[i].time.day << "/" << moods[i].time.month << "/" << moods[i].time.year << endl << "      ________________"
        << endl
        << "Mood type:" << moods[i].moodtype << endl << "      ________________"
        << endl
        <<"Mood level:" << moods[i].moodLevel << endl << "      ________________"
        << endl
        <<"Notes:" << moods[i].note << endl;
    cout << "_________________________________________________________________";
}

void SearchByDate(moodEntry moods[], int& moodCount) {
    system("cls");
    int day, month, year;
    bool found = false;
    cout << "_________________________________________________________________";
    cout << "Enter the day:";
    cin >> day;
    cout << endl << "      ________________";
    cout << endl << "Enter the month:";
    cin >> month;
    cout << endl << "      ________________";
    cout << endl << "Enter the year:";
    cin >> year;
    cout << endl << "      ________________";
    for (int i = 0; i < moodCount; i++)
        if (moods[i].time.day == day && moods[i].time.month == month && moods[i].time.year == year) {
            out(moods, i);
            found = true;
        }
    if (!found) {

        cout << "╔════════════════════════════════════╗\n";
        cout << "║                                    ║\n";
        cout << "║    No mood found on this date...   ║\n";
        cout << "║                                    ║\n";
        cout << "╚════════════════════════════════════╝\n";
    }
       
}

void SearchByType(moodEntry moods[], int& moodCount) {
    system("cls");
    string type;
    bool found = false;
    cout << "_________________________________________________________________";
    cout << "Enter the type of mood:";
    cin >> type;
    cout << endl << "      ________________";
    for (int i = 0; i < moodCount; i++)
        if (moods[i].moodtype == type) {
            out(moods, i);
            found = true;
        }
    if (!found) {
        cout << "╔════════════════════════════════════╗\n";
        cout << "║                                    ║\n";
        cout << "║ No mood found on with this type... ║\n";
        cout << "║                                    ║\n";
        cout << "╚════════════════════════════════════╝\n";
    }

}

void SearchMood() {
    system("cls");
    int choise;
     cout << "_________________________________________________________________";
    cout << "ENTER 1 to search by date." << endl << "ENTER 2 to search by mood type";
    cin >> choise;
    if (choise == 1)
        SearchByDate(moods, moodCount);
    else if (choise == 2)
        SearchByType(moods, moodCount);
    else {

        cout << "╔════════════════════════════════════╗\n";
        cout << "║           Invalid choise!          ║\n";
        cout << "╚════════════════════════════════════╝\n";
    }
}
''



    

int monthindex;
void AnalyzeMoodFrequency(moodEntry moods[], int size, int month) {
    monthindex = month - 1;
    statistics[monthindex].TotalEntries = 0;
    statistics[monthindex].HappyCount = 0;
    statistics[monthindex].SadCount = 0;
    statistics[monthindex].AngryCount = 0;
    statistics[monthindex].StressedCount = 0;
    statistics[monthindex].CalmCount = 0;

    for (int i = 0; i < size; i++) {
        if (moods[i].time.month == month) {
            statistics[monthindex].TotalEntries++;
        }
    }
}

void AverageMoodlevel(int& moodCount, int month, float& happyavg, float& sadavg, float& calmavg, float& stressavg, float& angryavg) {
    int currentid = currentuser.userid;
    int happy_sum = 0, sad_sum = 0,
        calm_sum = 0, stress_sum = 0,
        angry_sum = 0;
    for (int i = 0; i < moodCount; i++) {
        if (users[i].userid != currentid) {
            continue;//neglect other users
        }
        if (moods[i].time.month != month) {
            continue;//neglect other mounthes
        }
        if (moods[i].moodtype == "happy") {
            happy_sum += moods[i].moodLevel;
            statistics[monthindex].HappyCount++;
        }
        else if (moods[i].moodtype == "sad") {
            sad_sum += moods[i].moodLevel;
            statistics[monthindex].SadCount++;
        }
        else if (moods[i].moodtype == "calm") {
            calm_sum += moods[i].moodLevel;
            statistics[monthindex].CalmCount++;
        }
        else if (moods[i].moodtype == "stress") {
            stress_sum += moods[i].moodLevel;
            statistics[monthindex].StressedCount++;
        }
        else if (moods[i].moodtype == "angry") {
            angry_sum += moods[i].moodLevel;
            statistics[monthindex].AngryCount++;
        }
    }
    if (statistics[monthindex].HappyCount > 0) {
        happyavg = (float)happy_sum / statistics[monthindex].HappyCount;
    }
    if (statistics[monthindex].SadCount > 0) {
        sadavg = (float)sad_sum / statistics[monthindex].SadCount;
    }
    if (statistics[monthindex].CalmCount > 0) {
        calmavg = (float)calm_sum / statistics[monthindex].CalmCount;
    }
    if (statistics[monthindex].StressedCount > 0) {
        stressavg = (float)stress_sum / statistics[monthindex].StressedCount;
    }
    if (statistics[monthindex].AngryCount > 0) {
        angryavg = (float)angry_sum / statistics[monthindex].AngryCount;
    }
}

void DisplayStatistics(int month) {
    float happyavg = 0, sadavg = 0, calmavg = 0, stressavg = 0, angryavg = 0;
    monthindex = month - 1;
    if (statistics[monthindex].TotalEntries == 0) {
        cout << "\nNo data for month " << month << endl;
        system("pause");
        return;
    }
    cout << "\n--- Statistics Report for Month " << month << " ---" << endl;
    cout << "Total Records: " << statistics[monthindex].TotalEntries << endl;
    cout << "Average Mood Level: ";
    AverageMoodlevel(moodCount, month, happyavg, sadavg, calmavg, stressavg, angryavg);
    if (statistics[monthindex].HappyCount > 0) {
        cout << "happy avarege= " << happyavg << endl;
    }
    else {
        cout << " No Happy Avgarage For This Month\n";
    }
    if (statistics[monthindex].SadCount > 0) {
        cout << "sad avarege= " << sadavg << endl;
    }
    else {
        cout << " No Sad Avgarage For This Month\n";
    }
    if (statistics[monthindex].CalmCount > 0) {
        cout << "calm avarege= " << calmavg << endl;
    }
    else {
        cout << " No Calm Avgarage For This Month\n";
    }
    if (statistics[monthindex].StressedCount > 0) {
        cout << "stress avarege= " << stressavg << endl;
    }
    else {
        cout << " No Stress Avgarage For This Month\n";
    }
    if (statistics[monthindex].AngryCount > 0) {
        cout << "angry avarege= " << angryavg << endl;
    }
    else {
        cout << " No Angry Avgarage For This Month\n";
    }
    cout << " / 5" << endl;
    system("pause");
}

void UpdateAllStatistics(moodEntry moods[], int moodCount) {
    for (int m = 1; m <= 12; m++) {
        AnalyzeMoodFrequency(moods, moodCount, m);
    }
}
