#include<iostream>
using namespace std;
int count = 0;
struct moodEntry
{
	int day;
	int month;
	int year;
	int moodLevel;
	string moodtype;
	string note;
};
moodEntry moods[100];
void addMood(moodEntry moods[])
{
	cout << "Enter the day\n";
	cin >> moods->day;
	cout << "Enter the month\n";
	cin >> moods->month;
	cout << "Enter the year\n";
	cin >> moods->year;
	cout << "Enter the mood level\n";
	cin >> moods->moodLevel;
	do
	{
		cout << "wrong input please enter a number between 1 and 5\n";
	} while (moods->moodLevel > 5 || moods->moodLevel < 1) ;
	cout << "Enter the mood type \n";
	cin >> moods->moodtype;
	cout << "Enter the note\n";
	cin >> moods->note;
}
int main()
{

	int moodCount = 0;
	 
	return 0;
}





void SearchByDate(MoodEntry moods[], int moodcount) {
	int day, month, year;
	bool found = false;

	cout << "Enter the day:";
	cin >> day;
	cout << endl << "Enter the month:";
	cin >> month;
	cout << endl << "Enter the year:";
	cin >> year;
	for (int i = 0; i < moodcount; i++)
		if (moods[i].day == day && moods[i].month == month && moods[i].year == year) {
			cout << "Date:" << moods[i].day << "/" << moods[i].month << "/" << moods[i].year << endl
				<< moods[i].moodtype << endl << moods[i].moodlevel << endl << moods[i].note << endl 
				<< "____________________________________________________________";
			found = true;
		}
	if (!found)
		cout << "No mood found on this date." << endl;
}


void SearchByType(MoodEntry moods[], int moodcount) {
	string type;
	bool found = false;

	cout << "Enter the type of mood:";
	cin >> type;

	  for (int i = 0; i < moodcount; i++)
		  if (moods[i].type == type) {
			cout << "Date:" << moods[i].day << "/" << moods[i].month << "/" << moods[i].year << endl
				<< moods[i].moodtype << endl << moods[i].moodlevel << endl << moods[i].note  << endl 
				<< "____________________________________________________________";
			found = true;
		  }
	if (!found)
		cout << "No mood found on with this type." << endl;
}


void SearchMood() {
	int choise;
	cout << "ENTER 1 to search by date." << endl << "ENTER 2 to search by mood type";
	cin >> choise;
	if (choise == 1)
		SearchByDate( moods , moodcount);
	else if (choise == 2)
		SearchByType( moods , moodcount);
	else
		cout << "invalid choise!" << endl;
}



