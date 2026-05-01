#include<iostream>
#include <windows.h>
#include <cstring>
#include <fstream>
#include <string>
#include <cstdlib>
#include<sstream>
#include <algorithm>
#include <cctype>
#define maxMoodStorage 100
using namespace std;

//Global variables declarations
int userscount = 0;
int logentry;
int moodCount = 0;
int monthindex;
const int max_users = 10;

//Structs declarations
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

//Array declarations
UserAccount users[max_users];
UserAccount currentuser;
moodEntry moods[maxMoodStorage];
MoodStatistics statistics[12];
//chares
string toLowerCase(string str) {

    for (char& c : str) {

        c = tolower(c);

    }

    return str;

}

//function declarations
void logmenu();
void login();
void preStoredMoods();
void signup();
void closing();
void showLogMenu();
int loadingusers();
void saveusers();
int loadingMoods(moodEntry moods[]);
void saveMoods();
void addMood(moodEntry moods[], int& moodCount);
void mood_output(moodEntry moods[], int i);
void display(moodEntry moods[], int);
void SearchMood(moodEntry moods[], int& moodCount);
void SearchByDate(moodEntry moods[], int& moodcount);
void SearchByType(moodEntry moods[], int& moodcount);
void SearchByLevel(moodEntry moods[], int& moodcount);
void SearchByWord(moodEntry moods[], int& moodcount);
void updateFuncion(moodEntry moods[], int& moodCount);
void Delete(moodEntry moods[], int& moodCount);
void DisplayStatistics(int);
void UpdateAllStatistics(moodEntry moods[], int);
void AnalyzeMoodFrequency(moodEntry moods[], int, int);
void AverageMoodlevel(moodEntry moods[], int, int, float&, float&, float&, float&, float&);


//main function
int main()
{
    //لدعم الرموز والإطارات
    system("chcp 65001 > nul");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hConsole, false, &fontInfo);
    wcscpy_s(fontInfo.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(hConsole, false, &fontInfo);

    // Load users and assign user IDs
    userscount = loadingusers();
    for (int i = 0; i < userscount; ++i) {
        users[i].userid = i + 1;
    }

    // Initialize statistics
    for (int i = 0; i < 12; i++)
    {
        statistics[i] = { 0,0,0,0,0,0 };
    }

    // Show login menu until a user successfully logs in
    while (currentuser.userid == 0)
    {
        showLogMenu();
    }

    while (currentuser.userid != 0)
    {
        int choice;
        system("cls");
        cout << "╔═══════════════════════════════════════════════════════╗\n";
        cout << "║              🎉 Welcome " << currentuser.username << "! 🎉                    ║\n";
        cout << "╠═══════════════════════════════════════════════════════╣\n";
        cout << "║                                                       ║\n";
        cout << "║              📊 Digital Mood Tracker                  ║\n";
        cout << "║                                                       ║\n";
        cout << "╠═══════════════════════════════════════════════════════╣\n";
        cout << "║  [1] ➕ Add New Mood Entry                             ║\n";
        cout << "║  [2] 📅 Display Mood by Date                         ║\n";
        cout << "║  [3] 🔍 Search Mood                                   ║\n";
        cout << "║  [4] ✏️  Update Mood Entry                            ║\n";
        cout << "║  [5] 🗑️  Delete Mood Entry                            ║\n";
        cout << "║  [6] 📈 View Monthly Statistics                       ║\n";
        cout << "║  [7] 🚪 Logout                                        ║\n";
        cout << "║                                                       ║\n";
        cout << "╚═══════════════════════════════════════════════════════╝\n";
        cout << " Your choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input.\n";
            system("timeout /t 1 > nul");
            continue;
        }

        // handle user choices
        switch (choice)
        {
        case 1:
            addMood(moods, moodCount);
            saveMoods();
            UpdateAllStatistics(moods, moodCount);
            cout << "╔═════════════════════════════════╗\n";
            cout << "║             Success✅           ║\n";
            cout << "╠═════════════════════════════════╣\n";
            cout << "║                                 ║\n";
            cout << "║    Mood added successfully! ✅  ║\n";
            cout << "║                                 ║\n";
            cout << "╚═════════════════════════════════╝\n";
            system("timeout /t 3 > nul");
            break;

        case 2:
            display(moods, moodCount);
            system("pause");
            break;

        case 3:
            SearchMood(moods, moodCount);
            system("pause");
            break;

        case 4:
            updateFuncion(moods, moodCount);
            saveMoods();
            UpdateAllStatistics(moods, moodCount);
            break;

        case 5:
            Delete(moods, moodCount);
            saveMoods();
            UpdateAllStatistics(moods, moodCount);
            break;

        case 6:
        {
            int month;
            cout << "Enter month (1-12): ";
            cin >> month;
            if (month >= 1 && month <= 12)
            {
                UpdateAllStatistics(moods, moodCount);
                DisplayStatistics(month);
            }
            else
            {
                cout << "Invalid month!\n";
                system("pause");
            }
        }
        break;

        case 7:
            cout << "Logging out...\n";
            system("timeout /t 3 > nul");
            currentuser = { 0, "", "" }; // إعادة تعيين المستخدم الحالي
            moodCount = 0; // إعادة تعيين عدد المودات
            // العودة لشاشة تسجيل الدخول
            showLogMenu();
            break;

        default:
            cout << "Invalid choice! Please try again.\n";
            system("timeout /t 1 > nul");
            break;
        }
    }

    return 0;
}
//Ending main function

//Loading data from file functions
int loadingusers()
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
int loadingMoods(moodEntry moods[])
{
    ifstream infile("inputData.txt");
    int count = 0;

    if (!infile.is_open() || currentuser.userid == 0) {
        moodCount = 0;
        return 0;
    }

    string line;
    while (getline(infile, line) && count < maxMoodStorage) {
        istringstream iss(line);
        int userid, day, month, year, moodLevel;
        string moodtype, note;

        if (iss >> userid >> day >> month >> year >> moodtype >> moodLevel) {
            if (userid == currentuser.userid) {
                moods[count].time.day = day;
                moods[count].time.month = month;
                moods[count].time.year = year;
                moods[count].moodtype = moodtype;
                moods[count].moodLevel = moodLevel;
                getline(iss, note);
                moods[count].note = note;
                count++;
            }
        }
    }
    infile.close();
    moodCount = count;
    return count;
}

//Saving data to file function
void saveusers()
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
void saveMoods()
{
    ofstream out("inputData.txt");
    if (out.is_open()) {
        for (int i = 0; i < moodCount; i++) {
            out << currentuser.userid << " "
                << moods[i].time.day << " "
                << moods[i].time.month << " "
                << moods[i].time.year << " "
                << moods[i].moodtype << " "
                << moods[i].moodLevel << " "
                << moods[i].note << endl;
        }
        out.close();
    }
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
    cout << " Your entry (1-3): ";
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
    cout << " Your entry (1-3): ";
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
            for (int i = 0; i < userscount; i++)
            {
                if (users[i].username == namecheck && users[i].password == passcheck)
                {
                    currentuser = users[i];
                    moodCount = loadingMoods(moods);
                    return;
                }
            }
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
            cout << " Your entry (1-2): ";
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

    currentuser = { 0, "", "" };
    return;
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
        cout << " Your entry (1-3): ";
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
            saveusers();
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
        cout << " Your entry (1-2): ";
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

//Exit function
void closing()
{
    system("cls");
    cout << "Thank you for using Digital Mood Tracker! Goodbye!👋\n";
    system("timeout /t 4 > nul");
    exit(0);
}

// Log menu loop function
void showLogMenu()
{
    userscount = loadingusers();
    for (int i = 0; i < userscount; ++i)
    {
        users[i].userid = i + 1;
    }

    while (true) {
        logmenu();
        if (!(cin >> logentry))
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
            system("timeout /t 4 > nul");
            continue;
        }

        switch (logentry)
        {
        case 1:
            login();
             preStoredMoods();
            if (currentuser.userid != 0)
                return;
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

void validationDate(int& validDay, int& validMonth, int& validYear)
{
    bool validDate = false;
    do {
        cout << "╔════════════════════════════════════╗\n";
        cout << "║       Enter Date                   ║\n";
        cout << "╠════════════════════════════════════╣\n";
        cout << "║  Day / Month / Year: ";

        if (!(cin >> validDay >> validMonth >> validYear))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            system("clear");
            cout << "╔════════════════════════════════════╗\n";
            cout << "║           Invalid Input!           ║\n";
            cout << "╠════════════════════════════════════╣\n";
            cout << "║  Please enter numbers only...      ║\n";
            cout << "╚════════════════════════════════════╝\n";
            system("sleep 2");
            system("clear");
            continue;
        }

        if (validDay < 1 || validDay > 31) {
            system("clear");
            cout << "╔════════════════════════════════════╗\n";
            cout << "║           Invalid Day!             ║\n";
            cout << "╠════════════════════════════════════╣\n";
            cout << "║  Day must be between 1 and 31...   ║\n";
            cout << "╚════════════════════════════════════╝\n";
            system("sleep 2");
            system("clear");
        }
        else if (validMonth < 1 || validMonth > 12) {
            system("clear");
            cout << "╔════════════════════════════════════╗\n";
            cout << "║           Invalid Month!           ║\n";
            cout << "╠════════════════════════════════════╣\n";
            cout << "║  Month must be between 1 and 12... ║\n";
            cout << "╚════════════════════════════════════╝\n";
            system("sleep 2");
            system("clear");
        }
        else if (validYear < 2000 || validYear > 2100) {
            system("clear");
            cout << "╔════════════════════════════════════╗\n";
            cout << "║           Invalid Year!            ║\n";
            cout << "╠════════════════════════════════════╣\n";
            cout << "║  Year must be between 2000 & 2100  ║\n";
            cout << "╚════════════════════════════════════╝\n";
            system("sleep 2");
            system("clear");
        }
        else
            validDate = true;

    } while (!validDate);
}

//Add new mood entry function
void addMood(moodEntry moods[], int& moodCount)
{
    int validDay, validMonth, validYear;
    validationDate(validDay, validMonth, validYear);
    moods[moodCount].time.day = validDay;
    moods[moodCount].time.month = validMonth;
    moods[moodCount].time.year = validYear;
    system("cls");
    cout << "╔═════════════════════════════════════════════════════════╗\n";
    cout << "║                    ➕Add New Mood                       ║\n";
    cout << "╠═════════════════════════════════════════════════════════╣\n";
    cout << "║                      Mood Types:                        ║\n";
    cout << "╠═════════════════════════════════════════════════════════╣\n";
    cout << "║  😃 Happy / 🥲 Sad / 😡 Angry / 😫 Stressed / 😌 Calm   ║\n";
    cout << "╚═════════════════════════════════════════════════════════╝\n";
    cout << "Enter Mood Type: ";
    cin >> moods[moodCount].moodtype;
    cout << "Enter the mood level from (1 - 5): ";
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
            system("sleep 4");
            cin >> moods[moodCount].moodLevel;
        } while (moods[moodCount].moodLevel > 5 || moods[moodCount].moodLevel < 1);
    }
    cout << "Enter the note: ";
    cin.ignore();
    getline(cin, moods[moodCount].note);
    moodCount++;
    saveMoods();
}

//Display mood entry function
void mood_output(moodEntry moods[], int i)
{

    cout << "╔════════════════════════════════════╗\n";
    cout << "║ Date:" << moods[i].time.day << "/" << moods[i].time.month << "/" << moods[i].time.year << "           ║\n";
    cout << "╠════════════════════════════════════╣\n";
    cout << "║ Mood type:" << moods[i].moodtype << "                     ║\n";
    cout << "║ Mood level:" << moods[i].moodLevel << "                     ║\n";
    cout << "║ Notes:" << moods[i].note << "                     ║\n";
    cout << "╚════════════════════════════════════╝\n";
}
void display(moodEntry moods[], int moodCount)
{
    int day, month, year;
    bool found = false;

    cout << "Enter date to display (day/month/year): \n";
    cin >> day >> month >> year;

    for (int i = 0; i < moodCount; i++)
    {
        if (moods[i].time.day == day &&
            moods[i].time.month == month &&
            moods[i].time.year == year)
        {
            mood_output(moods, i);

            found = true;
        }
    }

    if (!found)
        cout << "No data found for this date\n";
}

//Search moods function
void SearchByDate(moodEntry moods[], int& moodCount) {
    system("cls");
    int day, month, year;
    bool found = false;
    cout << "_________________________________________________________________\n";
    cout << "Enter the day:\n";
    cin >> day;
    cout << endl << "      ________________\n";
    cout << endl << "Enter the month:\n";
    cin >> month;
    cout << endl << "      ________________\n";
    cout << endl << "Enter the year:\n";
    cin >> year;
    cout << endl << "      ________________\n";
    if (day < 1 || day>31 || month < 1 || month>12) {
        cout << "╔════════════════════════════════════╗\n";
        cout << "║                                    ║\n";
        cout << "║        Inva4lid date entered!      ║\n";
        cout << "║    Day must be in betweem (1:31)   ║\n";
        cout << "║   month must be in betweem (1:12)  ║\n";
        cout << "║                                    ║\n";
        cout << "╚════════════════════════════════════╝\n";
    }
    else {
        for (int i = 0; i < moodCount; i++) {
            if (moods[i].time.day == day && moods[i].time.month == month && moods[i].time.year == year) {
                mood_output(moods, i);
                found = true;
            }
        }
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

    int indexes[100];
    int idxCount = 0;

    char choice;
    int level;
    bool levelFound = false;

    cout << "_________________________________________________________________\n";
    cout << "Enter the type of mood:\n";
    cin >> type;
    cout << endl << "      ________________\n";
    for (int i = 0; i < moodCount; i++)
        if (moods[i].moodtype == type) {
            mood_output(moods, i);
            indexes[idxCount++] = i;
            found = true;
        }
    if (!found) {
        cout << "╔════════════════════════════════════╗\n";
        cout << "║                                    ║\n";
        cout << "║ No mood found on with this type... ║\n";
        cout << "║                                    ║\n";
        cout << "╚════════════════════════════════════╝\n";
        return;
    }

    cout << "Do you want to filter these results by mood level ?  (y/n)\n";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        system("cls");
        cout << "_________________________________________________________________\n";
        cout << "\nEnter the mood level:\n";
        cin >> level;
        for (int j = 0; j < idxCount; j++)
            if (moods[indexes[j]].moodLevel == level) {
                mood_output(moods, indexes[j]);
                levelFound = true;
            }
        if (!levelFound) {
            cout << endl;
            cout << "╔═══════════════════════════════════════╗\n";
            cout << "║                                       ║\n";
            cout << "║No moods with this level in this type..║\n";
            cout << "║                                       ║\n";
            cout << "╚═══════════════════════════════════════╝\n";
        }
    }
    else if (choice == 'N' || choice == 'n') {
        cout << endl;
        cout << "╔════════════════════════════════════╗\n";
        cout << "║                                    ║\n";
        cout << "║          Okay, returning...        ║\n";
        cout << "║                                    ║\n";
        cout << "╚════════════════════════════════════╝\n";
    }
    else {
        cout << endl;
        cout << "╔════════════════════════════════════╗\n";
        cout << "║           Invalid choise!          ║\n";
        cout << "╚════════════════════════════════════╝\n";
    }
}
void SearchByLevel(moodEntry moods[], int& moodCount) {
    system("cls");
    int level;
    bool found = false;
    cout << "_______________________\n";
    cout << "Enter the level of mood:\n";
    cin >> level;
    cout << endl << "      ______\n";
    for (int i = 0; i < moodCount; i++)
        if (moods[i].moodLevel == level) {
            mood_output(moods, i);
            found = true;
        }
    if (!found) {
        cout << "╔════════════════════════════════════╗\n";
        cout << "║                                    ║\n";
        cout << "║   No mood found at this level...   ║\n";
        cout << "║                                    ║\n";
        cout << "╚════════════════════════════════════╝\n";
    }
}


void SearchByWord(moodEntry moods[], int& moodCount) {
    system("cls");
    string word;
    bool found = false;
    cout << "_________________________________________________________________\n";
    cout << "Enter a word to search in notes:\n";
    cin >> word;
    cout << endl << "      ________________\n";
    for (int i = 0; i < moodCount; i++)
        if (moods[i].note.find(word)!=string::npos) {
            mood_output(moods, i);
            found = true;
        }
    if (!found) {
        cout << "╔════════════════════════════════════════╗\n";
        cout << "║                                        ║\n";
        cout << "║ No moods contain this word in notes... ║\n";
        cout << "║                                        ║\n";
        cout << "╚════════════════════════════════════════╝\n";
    }
}

void SearchMood(moodEntry moods[], int& moodCount)
{
    system("cls");
    int choise;
    cout << "_________________________________________________________________\n";
    cout << "ENTER 1 to search by date." << endl << "ENTER 2 to search by mood type."
        << endl << "ENTER 3 to search by mood level." << endl << "ENTER 4 to search by word in notes.\n";
    cin >> choise;
    switch (choise) {
    case 1:
        SearchByDate(moods, moodCount);
        break;

    case 2:
        SearchByType(moods, moodCount);
        break;

    case 3:
        SearchByLevel(moods, moodCount);
        break;

    case 4:
        SearchByword(moods, moodCount);
        break;

    default:
        cout << endl;
        cout << "╔════════════════════════════════════╗\n";
        cout << "║           Invalid choise!          ║\n";
        cout << "╚════════════════════════════════════╝\n";
    }

}

//Update moods function
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
        cout << "Enter day / month / year to update mood entry " << endl;
        validationDate(searchDay, searchMonth, searchYear);

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
            system("clear");
            cout << "╔════════════════════════════════════╗\n";
            cout << "║           Invalid Entry!           ║\n";
            cout << "╠════════════════════════════════════╣\n";
            cout << "║                                    ║\n";
            cout << "║         Please try again...        ║\n";
            cout << "║                                    ║\n";
            cout << "╚════════════════════════════════════╝\n";
            cin.clear();
            cin.ignore(10000, '\n');
            system("sleep 4");
        }
        else
        {
            system("clear");
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
            break;
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
    system("sleep 4");
    saveMoods();
}

//Delete moods function
void Delete(moodEntry moods[], int& moodCount)
{
    int day, month, year;
    bool found = false;

    system("cls");
    cout << "╔══════════════════════════════════════════════╗\n";
    cout << "║        🗑️ Delete Mood Entry by Date         ║\n";
    cout << "╠══════════════════════════════════════════════╣\n";
    cout << "║  📅 Enter Day   : "; cin >> day;
    cout << "║  📅 Enter Month : "; cin >> month;
    cout << "║  📅 Enter Year  : "; cin >> year;
    cout << "╠══════════════════════════════════════════════╣\n";

    for (int i = 0; i < moodCount; i++)
    {
        if (moods[i].time.day == day &&
            moods[i].time.month == month &&
            moods[i].time.year == year)
        {
            for (int j = i; j < moodCount - 1; j++)
            {
                moods[j] = moods[j + 1];
            }

            moodCount--;
            found = true;
            break;
        }
    }

    if (found)
    {
        cout << "║      ✅ Mood deleted successfully!          ║\n";
        cout << "║      💡 Stay positive & keep tracking!     ║\n";
    }
    else
    {
        cout << "║      ❌ Date not found! Try again...        ║\n";
        cout << "║      🔍 Make sure the date is correct      ║\n";
    }

    cout << "╚══════════════════════════════════════════════╝\n";

    system("pause");
    saveMoods();
}

//Statistics functions

void DisplayStatistics(int month) {
    system("cls");
    float happyavg = 0, sadavg = 0, calmavg = 0, stressavg = 0, angryavg = 0;

    monthindex = month - 1;

    cout << "\n--- Statistics for Month " << month << " ---\n";
    cout << "Total Entries: " << statistics[monthindex].TotalEntries << endl;

    
    AverageMoodlevel(moods, moodCount, month, happyavg, sadavg, calmavg, stressavg, angryavg);

    
    cout << "\nMood       | Count | Average Mood Level\n";
    cout << "----------------------------------------\n";

    cout << "Happy      | " << statistics[monthindex].HappyCount << "     | " << happyavg << "/5\n";
    cout << "Sad        | " << statistics[monthindex].SadCount << "     | " << sadavg << "/5\n";
    cout << "Calm       | " << statistics[monthindex].CalmCount << "     | " << calmavg << "/5\n";
    cout << "Stressed   | " << statistics[monthindex].StressedCount << "     | " << stressavg << "/5\n";
    cout << "Angry      | " << statistics[monthindex].AngryCount << "     | " << angryavg << "/5\n";

    cout << "----------------------------------------\n";

    system("pause");
}
void UpdateAllStatistics(moodEntry moods[], int size)
{
    for (int m = 1; m <= 12; m++) {
        AnalyzeMoodFrequency(moods, size, m);
    }
}

void AnalyzeMoodFrequency(moodEntry moods[], int size, int month) {
    monthindex = month - 1;
    statistics[monthindex] = { 0,0,0,0,0,0 }; // reset all

    for (int i = 0; i < size; i++) {
        if (moods[i].time.month == month) {
            statistics[monthindex].TotalEntries++;

            string type = moods[i].moodtype;
            transform(type.begin(), type.end(), type.begin(), [](unsigned char c) {
                return tolower(c);
                });
        }
    }
}

//Calculate average mood level for a given month
void AverageMoodlevel(moodEntry moods[], int moodCount, int month, float& happyavg, float
    & sadavg, float& calmavg, float& stressavg, float& angryavg)
{
    int happy_sum = 0, sad_sum = 0,
        calm_sum = 0, stress_sum = 0,
        angry_sum = 0;
    for (int i = 0; i < moodCount; i++) {
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
        else if (moods[i].moodtype == "stressed") {
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

void preStoredMoods()
{
    moods[0] = { {1, 4, 2026}, 5, "Happy", "Finished my project" };
    moods[1] = { {2, 4, 2026}, 3, "Calm", "Normal day" };
    moods[2] = { {3, 4, 2026}, 2, "Stressed", "Exam coming up" };
    moods[3] = { {4, 4, 2026}, 5, "sad", "did not pass the exam" };
    moods[4] = { {5, 4, 2026}, 3, "Calm", "Normal day" };
    moods[5] = { {6, 4, 2026}, 2, "Stressed", "Exam coming up" };
    moods[6] = { {7, 4, 2026}, 5, "Happy", "passed the exam" };
    moods[7] = { {8, 4, 2026}, 5, "Calm", "Normal day" };
    moods[8] = { {9, 4, 2026}, 2, "happy", "a new semister comming up" };
    moodCount = 9;
}

