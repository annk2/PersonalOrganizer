#include "anna_kawasaki_p1.h"
using namespace std;

//Anna Kawasaki
//implementation of classes in hierarchy
//for application that organizes activities

//DATE CLASS IMPLEMENTATION:
//SUPER CLASS

//date default constructor
date::date(): month(0), day(0), year(0), weekday(0) 
{
	week = new char *[WEEK];
	week[0] = new char[strlen("sunday") + 1];
	strcpy(week[0], "sunday");
	week[1] = new char[strlen("monday") + 1];
	strcpy(week[1], "monday");
	week[2] = new char[strlen("tuesday") + 1];
	strcpy(week[2], "tuesday");
	week[3] = new char[strlen("wednesday") + 1];
	strcpy(week[3], "wednesday");
	week[4] = new char[strlen("thursday") + 1];
	strcpy(week[4], "thursday");
	week[5] = new char[strlen("friday") + 1];
	strcpy(week[5], "friday");
	week[6] = new char[strlen("saturday") + 1];
	strcpy(week[6], "saturday");
}

//input function to read in info
void date::input()
{
	char read_in[SIZE_SM];

	cout << "~~Date~~" << endl << "Month: ";
	cin.get(read_in, SIZE_SM, '\n'); cin.ignore(100, '\n');
	month = new char[strlen(read_in) + 1];
	strcpy(month, read_in);

	cout << "Day: ";
	cin.get(read_in, SIZE_SM, '\n'); cin.ignore(100, '\n');
	day = new char[strlen(read_in) + 1];
	strcpy(day, read_in);

	cout << "Year: ";
	cin.get(read_in, SIZE_SM, '\n'); cin.ignore(100, '\n');
	year = new char[strlen(read_in) + 1];
	strcpy(year, read_in);

	do{
	cout << "Weekday: ";
	cin.get(read_in, SIZE_SM, '\n'); cin.ignore(100, '\n');

	if(!check_weekday(read_in))
		cout << "Please enter a valid weekday." << endl;
	}while(!check_weekday(read_in));

	weekday = new char[strlen(read_in) + 1];
	strcpy(weekday, read_in);
}

//deep copies date information from arg
void date::copy(date & to_copy)
{
	month = new char[strlen(to_copy.month) + 1];
	strcpy(month, to_copy.month);
	day = new char[strlen(to_copy.day) + 1];
	strcpy(day, to_copy.day);
	year = new char[strlen(to_copy.year) + 1];
	strcpy(year, to_copy.year);
	weekday = new char[strlen(to_copy.weekday) + 1];
	strcpy(weekday, to_copy.weekday);
}

//date copy constructor
date::date(const date & copy_date)
{
	month = new char[strlen(copy_date.month) + 1];
	strcpy(month, copy_date.month);
	day = new char[strlen(copy_date.day) + 1];
	strcpy(day, copy_date.day);
	year = new char[strlen(copy_date.year) + 1];
	strcpy(year, copy_date.year);
	weekday = new char[strlen(copy_date.weekday) + 1];
	strcpy(weekday, copy_date.weekday);
}

//displays full date information
int date::display() const
{
	if(!month || !day || !year || !weekday)
		return 0; //not a valid date

	cout << endl;
	cout << "Date: " << weekday << ", " << month << ' ' << day << ", " << year << endl;
	cout << endl;
	return 1; //successfully displayed
}

//removes all date allocated memory
//sets members to NULL
int date::remove()
{
	if(!month || !day || !year || !weekday)
		return 0; //nothing could be removed

	if(month)
	{
		delete [] month;
		month = NULL;
	}

	if(day)
	{
		delete [] day;
		day = NULL;
	}

	if(year)
	{
		delete [] year;
		year = NULL;
	}

	if(weekday)
	{
		delete [] weekday;
		weekday = NULL;
	}

	if(week)
	{
		for(int i=0; i<WEEK; ++i)
			delete [] week[i];

		delete [] week;
	}

	return 1; //success: removed
}

//compares weekday member to argument
//return value coincides with strcmp values
int date::compare_weekday(const char * to_compare) const
{
	return strcmp(weekday, to_compare);
}

//date destructor
date::~date()
{
	if(remove())
		return;
}

//checks if weekday in arg is valid
//compares to weekdays in week array
bool date::check_weekday(const char * to_check)
{
	for(int i=0; i<WEEK; ++i)
	{
		if(strcmp(week[i], to_check) == 0)
			return 1;
	}
	return 0;
}

//ACTIVITY CLASS IMPLEMENTATION
//SUBCLASS OF DATE CLASS

//activity default constructor
activity::activity(): title(0), description(0) {} 

//input to get information
void activity::input()
{
	date::input();

	char read_in_lg[SIZE_LG];
	char read_in_med[SIZE_MED];

	cout << "Title: ";
	cin.get(read_in_med, SIZE_MED, '\n'); cin.ignore(100, '\n');
	title = new char[strlen(read_in_med) + 1];
	strcpy(title, read_in_med);

	cout << "Description: ";
	cin.get(read_in_lg, SIZE_LG, '\n'); cin.ignore(100, '\n');
	description = new char[strlen(read_in_lg) + 1];
	strcpy(description, read_in_lg);
}

//deep copies activity information from arg
void activity::copy(activity & to_copy)
{
	date::copy(to_copy);

	title = new char[strlen(to_copy.title) + 1];
	strcpy(title, to_copy.title);
	description = new char[strlen(to_copy.description) + 1];
	strcpy(description, to_copy.description);
}

//activity copy constructor
activity::activity(const activity & copy_activity): date(copy_activity)
{
	title = new char[strlen(copy_activity.title) + 1];
	strcpy(title, copy_activity.title);
	description = new char[strlen(copy_activity.description) + 1];
	strcpy(description, copy_activity.description);
}

//display activity information
//display date information as well
int activity::display() const
{
	if(!date::display())
		return 0;

	cout << "Title: " << title << endl;
	cout << "Description: " << description << endl;
	cout << endl;
	return 1;
}

//deallocates memory for activity
int activity::remove()
{
	if(!date::remove())
		return 0;

	if(title)
	{
		delete [] title;
		title = NULL;
	}
	
	if(description)
	{
		delete [] description;
		description = NULL;
	}

	return 1;
}

//compares title with title in argument
//return value coincides with strcmp values
int activity::compare_title(const char * to_compare) const
{
	return strcmp(title, to_compare);
}

//compares title with activity in argument
int activity::compare_title_activity(activity & to_compare) const
{
	if(!to_compare.title)
		return -5;
	return strcmp(title, to_compare.title);
}


//activity destructor
activity::~activity()
{
	if(!remove())
		return;
}


//TO DO CLASS IMPLEMENTATION
//SUBCLASS OF ACTIVITY CLASS

//to do default constructor
to_do::to_do(): priority(0) {} 

//input to get information for to do list item
void to_do::input()
{
	activity::input();

	do{
	cout << "What is the priority of this task (1-5, 1=most important, 5=least): ";
	cin >> priority; cin.ignore(100, '\n');

	if(priority < 1 || priority > 5)
		cout << "Priority must be between 1 and 5. Please enter a priority number within this range." << endl;

	}while(priority < 1 || priority > 5); //make sure priority is valid
}

//copy constructor for to do list
void to_do::copy(to_do & to_copy)
{
	activity::copy(to_copy);

	priority = to_copy.priority;
}

//to do copy constructor
to_do::to_do(const to_do & copy_to_do): activity(copy_to_do)
{
	priority = copy_to_do.priority;
}

//display to do information
//display activity and date information as well
int to_do::display() const
{
	cout << "~TASK~";
	if(!activity::display())
		return 0;

	cout << "Priority: " << priority << endl << endl;
	return 1;
}

//deallocates memory for to do
int to_do::remove()
{
	if(!activity::remove())
		return 0;

	if(priority)
	{
		priority = 0;
	}
	return 1;
}

//compares priority with priority in argument
//negative if priority is less than compare, pos if more than compare
int to_do::compare_priority(const to_do & to_compare) const
{
	if(priority >= to_compare.priority)
		return 1;
	else
		return -1;
}

//to do destructor
to_do::~to_do()
{
	if(!remove())
		return;
}


//MAIL MESSAGE CLASS IMPLEMENTATION
//SUBCLASS OF ACTIVITY CLASS

//mail message constructor
mail_message::mail_message(): category(0), recipient(0), flag(0) {}

//input to get information for mail message
//arguments are for verifying category
void mail_message::input(char ** category_check, int num_cat)
{
	char read_in[SIZE_MED];
	int valid_cat;

	//check if category is valid
	do{

		cout << "Category: ";
		cin.get(read_in, SIZE_MED, '\n'); cin.ignore(100, '\n');

		valid_cat = 0; //check if category is valid
		for (int j = 0; j<num_cat; ++j)
		{
			if(strcmp(read_in, category_check[j]) == 0)
				valid_cat = 1;
		}

		if(!valid_cat)
			cout << "Category is not valid." << endl;

	}while(!valid_cat);

	category = new char[strlen(read_in) + 1];
	strcpy(category, read_in);

	cout << "Recipient E-mail: ";
	cin.get(read_in, SIZE_MED, '\n'); cin.ignore(100, '\n');
	recipient = new char[strlen(read_in) + 1];
	strcpy(recipient, read_in);

	flag = false;

	activity::input();
}

//deep copies mail message information from arg
void mail_message::copy(mail_message & to_copy)
{
	activity::copy(to_copy);

	category = new char[strlen(to_copy.category) + 1];
	strcpy(category, to_copy.category);
	recipient = new char[strlen(to_copy.recipient) + 1];
	strcpy(recipient, to_copy.recipient);
}

//mail message copy constructor
mail_message::mail_message(const mail_message & copy_mail_message): activity(copy_mail_message)
{
	category = new char[strlen(copy_mail_message.category) + 1];
	strcpy(category, copy_mail_message.category);
	recipient = new char[strlen(copy_mail_message.recipient) + 1];
	strcpy(recipient, copy_mail_message.recipient);
}

//display mail message information
//display activity and date information as well
int mail_message::display() const
{
	cout << "~MAIL MESSAGE~" << endl;

	cout << "Category: " << category << endl;
	cout << "Recipient: " << recipient << endl;
	if(flag)
		cout << "Message has been flagged." << endl;

	if(!activity::display())
		return 0;

	cout << endl;
	return 1;
}

//displays the category of the mail message
void mail_message::display_category() const
{
	cout << category;
	return;
}

//deallocates memory for mail message
int mail_message::remove()
{
	if(!activity::remove())
		return 0;

	if(category)
	{
		delete [] category;
		category = NULL;
	}

	if(recipient)
	{
		delete [] recipient;
		recipient = NULL;
	}

	flag = false;

	return 1;
}

//compares category with category in argument
//return value coincides with strcmp values
int mail_message::compare_category(const mail_message & to_compare) const
{
	return strcmp(category, to_compare.category);
}

//compares category with category in argument
//return value coincides with strcmp values
int mail_message::compare_category(const char * to_compare) const
{
	return strcmp(category, to_compare);
}

//marks flag as true
int mail_message::mark_flagged()
{
	flag = true;
	return 1;
}

//mail message destructor
mail_message::~mail_message()
{
	if(!remove())
		return;
}


//WEEKLY EVENT CLASS IMPLEMENTATION
//SUBCLASS OF ACTIVITY CLASS

//weekly event constructor
weekly_event::weekly_event(): location(0), people(0), hour(0), min(0), length(0), going(0) {}

//input to get information for weekly event
void weekly_event::input()
{
	char read_in[SIZE_MED];

	activity::input();

	cout << "Event location: ";
	cin.get(read_in, SIZE_MED, '\n'); cin.ignore(100, '\n');
	location = new char[strlen(read_in) + 1];
	strcpy(location, read_in);

	cout << "People: ";
	cin.get(read_in, SIZE_MED, '\n'); cin.ignore(100, '\n');
	people = new char[strlen(read_in) + 1];
	strcpy(people, read_in);

	cout << "Start time of event (enter in following format in military time,including spaces:16 45): ";
	cin >> hour >> min; cin.ignore(100,'\n');

	cout << "Length of event(in min): ";
	cin >> length; cin.ignore(100, '\n');
}

//deep copies weekly event information from arg
void weekly_event::copy(weekly_event & to_copy)
{
	activity::copy(to_copy);

	location = new char[strlen(to_copy.location) + 1];
	strcpy(location, to_copy.location);
	people = new char[strlen(to_copy.people) + 1];
	strcpy(people, to_copy.people);
	hour = to_copy.hour;
	min = to_copy.min;
	length = to_copy.length;
	going = to_copy.going;
}

//weekly event copy constructor
weekly_event::weekly_event(const weekly_event & copy_weekly_event): activity(copy_weekly_event)
{
	location = new char[strlen(copy_weekly_event.location) + 1];
	strcpy(location, copy_weekly_event.location);
	people = new char[strlen(copy_weekly_event.people) + 1];
	strcpy(people, copy_weekly_event.people);
	hour = copy_weekly_event.hour;
	min = copy_weekly_event.min;
	length = copy_weekly_event.length;
	going = copy_weekly_event.going;
}

//display weekly event information
//display activity and date information as well
int weekly_event::display() const
{
	cout << "~EVENT~";
	if(!activity::display())
		return 0;

	cout << "Location: " << location << endl;
	cout << "People: " << people << endl;
	cout << "Time: ";
	if(hour<10)
		cout << '0' << hour << ' ';
	else
		cout << hour << ' ';

	if(min<10)
		cout << '0' << min << endl;
	else
		cout << min << endl;

	cout << "Length: " << length << endl;
	if(going)
		cout << "Marked as going." << endl;
	else
		cout << "Marked as not going." << endl;

	cout << endl;
	return 1;
}

//deallocates memory for weekly event
int weekly_event::remove()
{
	if(!activity::remove())
		return 0;

	if(location)
	{
		delete [] location;
		location = NULL;
	}

	if(people)
	{
		delete [] people;
		people = NULL;
	}

	hour = min = 0;

	going = false;

	return 1;
}

//sets going to true
int weekly_event::mark_going()
{
	going = true;
	return 1;
}

//return hour to be used to organize
int weekly_event::get_hour()
{
	return hour;
}

//return minute to be used to organize
int weekly_event::get_min()
{
	return min;
}

//return length of event to be used to organize
int weekly_event::get_length()
{
	return length;
}

//weekly event destructor
weekly_event::~weekly_event()
{
	if(!remove())
		return;
}
