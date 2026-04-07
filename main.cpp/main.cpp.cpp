#include<iostream>
using namespace std;
int moodCount = 0;
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
	cout << "Enter the mood type \n";
	cout << "Happy\tSad\tAngry\tStressed\tcalm\n";
	cin >> moods->moodtype;
	cout << "Enter the mood level\n";
	cin >> moods->moodLevel;
	do
	{
		cout << "wrong input please enter a number between 1 and 5\n";
	} while (moods->moodLevel > 5 || moods->moodLevel < 1) ;
	cout << "Enter the note\n";
	cin >> moods->note;
}
float averagepermood(int entires, float& happyavg, float& sadavg, float& calmavg, float& stressavg, float& angryavg) {
	int happycount, happy_sum = 0,
		sadcount, sad_sum = 0,
		calmcount, calm_sum = 0,
		stresscount, stress_sum=0,
		angrycount, angry_sum = 0;
	for (int i = 0;i < entires;i++) {
		if (moods[i].moodtype == "happy") {
			happy_sum += moods[i].moodlevel;
			happycount++;
		}
		else if (moods[i].moodtype == "sad") {
			sad_sum += moods[i].moodllevel;
			sadcount++;
		}
		else if (moods[i].moodtype == "calm") {
			calm_sum += moods[i].moodlevel;
			calmcount++;
		}
		else if (moods[i].moodtype == "stress") {
			stress_sum += moods[i].moodlevel;
			stresscount++;
		}
		else if (moods[i].moodtype == "angry") {
			angry_sum += moods[i].moodlevel;
			angrycount++;
		}
	}
	if (happycount > 0)
		happyavg = (float)happy_sum / happycount;
	if (sadcount > 0)
		sadavg = (float)sad_sum / sadcount;
	if (calmcount > 0)
		calmavg = (float)calm_sum / calmcount;
	if (stresscount > 0)
		stressavg = (float)stress_sum / stresscount;
	if (angrycount > 0)
		angryavg = angry_sum / angrycount;
}

int main()
{
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
