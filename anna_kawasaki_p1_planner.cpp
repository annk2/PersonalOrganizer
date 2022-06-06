#include "anna_kawasaki_p1.h"
using namespace std;

//Anna Kawasaki
//implementation of weekly planner
//for application that organizes activities

//DAY NODE IMPLEMENTATION
//day node constructor
day_node::day_node(): weekday(0), time_slots(0), next(0) {}

//day node constructor with weekday arg
day_node::day_node(const char * a_weekday): next(0)
{
	weekday = new char[strlen(a_weekday) +1];
	strcpy(weekday, a_weekday);

	time_slots = new weekly_event * [TIME]; //initializes 48 time slots for every half hour
	for(int i = 0; i<TIME; ++i)
		time_slots[i] = NULL;
}

//day node copy constructor
day_node::day_node(day_node & to_copy)
{
	weekday = new char[strlen(to_copy.weekday) +1];
	strcpy(weekday, to_copy.weekday);

	time_slots = new weekly_event * [TIME];
	for(int i = 0; i<TIME; ++i)
	{
		if(to_copy.time_slots[i])
			time_slots[i] = new weekly_event(*to_copy.time_slots[i]);
		else
			time_slots[i] = NULL;
	}
}

//displays all events for one day
int day_node::display_all()
{
	int exists = 0;
	weekly_event just_displayed; //for events that takes up more than one slot, only want to display once
	cout << "~~" << weekday << "~~" << endl;
	for(int i=0; i<TIME; ++i)
	{
		if(time_slots[i])
		{
			if(time_slots[i]->compare_title_activity(just_displayed) !=0) //check if already displayed
			{
				time_slots[i]->display();
				exists = 1;
				just_displayed.copy(*time_slots[i]);
			}
		}
	}
	return exists;
}

//deletes all events for one day
int day_node::delete_all()
{
	int exists = 0;
	for(int i=0; i<TIME; ++i)
	{
		if(time_slots[i])
		{
			time_slots[i]->remove();
			time_slots[i] = NULL;
			exists = 1;
		}
	}
	return exists;
}

//finds where title in arg is located
//within time slots array
int day_node::find_title_index(const char * to_find)
{
	for(int i=0; i<TIME; ++i)
	{
		if(time_slots[i])
		{
			if(time_slots[i]->compare_title(to_find) == 0)
				return i;
		}
	}
	return -1;
}

//calculates what the time index should be in timeslots
//depending on what the hour and minute are
int day_node::index_time(int an_hour, int a_minute)
{
	int more_than_30 = 0;
	if(a_minute >= 30)
		++more_than_30;
	return (an_hour * 2) + more_than_30;
}

//calculates how many time slots an event takes up
//depending on its length
int day_node::how_many_slots(int a_length)
{
	//one slot is 30 min
	int slots = a_length/30;
	if(slots * 30 < a_length)
		++slots;
	return slots;
}

//finds event by title, removes it from all slots
int day_node::remove(const char * to_remove)
{
	int index = find_title_index(to_remove);
	if(index == -1) //if index invalid, title does not exist
		return 0;
	int slots = how_many_slots(time_slots[index]->get_length());

	for(int i=index; i<index+slots; ++i)  //deletes event from all slots
	{
		time_slots[i]->remove();
		time_slots[i] = NULL;
	}
	return 1;
}

//finds event by title, marks it as going
int day_node::going(const char * to_go)
{
	int index = find_title_index(to_go);
	if(index == -1)
		return 0;
	time_slots[index]->mark_going();
	return 1;
}

//finds event by title, displays it
int day_node::display(const char * to_display)
{
	int index = find_title_index(to_display);
	if(index == -1)
		return 0;
	time_slots[index]->display();
	return 1;
}

//finds event by title, retrieves it
//copies into retrieved arg
int day_node::retrieve(const char * to_retrieve, weekly_event & retrieved)
{
	int index = find_title_index(to_retrieve);
	if(index == -1)
		return 0;
	retrieved.copy(*time_slots[index]);
	return 1;
}

//adds weekly event to day
//calculate what index and how many slots
//doesnt add if space is taken
int day_node::add(weekly_event & to_add)
{
	int index = index_time(to_add.get_hour(),to_add.get_min());
	int length = how_many_slots(to_add.get_length());

	for(int i=index; i<index+length; ++i) 
	{
		if(time_slots[i])
			return 0; //space is taken
	}

	for(int j=index; j<index+length; ++j) 
	{
		time_slots[j] = new weekly_event(to_add);
	}

	return 1;
}

//sets next pointer to connection arg
void day_node::set_next(day_node * connection)
{
	if(!connection)
		next = NULL;
	else
		next = connection;
}

//returns next pointer
day_node * & day_node::go_next()
{
	return next;
}

//gets weekday, copies into argument
void day_node::get_weekday(char * & a_weekday)
{
	a_weekday = new char[strlen(weekday) + 1];
	strcpy(a_weekday, weekday);
}

//day node destructor
day_node::~day_node()
{
	delete_all();
	delete [] weekday;
	delete [] time_slots;
}


//WEEKLY PLANNER IMPLEMENTATION
//CLL of day nodes

//weekly planner constructor
weekly_planner::weekly_planner(): rear(0)
{
	load_week(); //loads week information into CLL
}

//weekly planner copy constructor
weekly_planner::weekly_planner(weekly_planner & to_copy)
{
	rear = new day_node(*to_copy.rear);
	copy_CLL(rear->go_next(), to_copy.rear->go_next(), to_copy.rear);
}

//copies weekly planner CLL from source into destination
void weekly_planner::copy_CLL(day_node * & destination, day_node * source, day_node * hold_rear)
{
	if(source == hold_rear)
		return;

	destination = new day_node(*source);
	copy_CLL(destination->go_next(), source->go_next(), hold_rear);
}

//loads week information into CLL format
void weekly_planner::load_week()
{
	weekdays = new char *[WEEK];
	weekdays[0] = new char[strlen("sunday") + 1];
	strcpy(weekdays[0], "sunday");
	weekdays[1] = new char[strlen("monday") + 1];
	strcpy(weekdays[1], "monday");
	weekdays[2] = new char[strlen("tuesday") + 1];
	strcpy(weekdays[2], "tuesday");
	weekdays[3] = new char[strlen("wednesday") + 1];
	strcpy(weekdays[3], "wednesday");
	weekdays[4] = new char[strlen("thursday") + 1];
	strcpy(weekdays[4], "thursday");
	weekdays[5] = new char[strlen("friday") + 1];
	strcpy(weekdays[5], "friday");
	weekdays[6] = new char[strlen("saturday") + 1];
	strcpy(weekdays[6], "saturday");

	add_node(weekdays[6]);

	for(int i=WEEK-2; i>=0; --i)
		add_node(weekdays[i]);
}

//adds node to CLL using weekday argument
void weekly_planner::add_node(const char * weekday)
{
	if(!rear)
	{
		rear = new day_node(weekday);
		rear->set_next(rear);
		return;
	}

	day_node * to_add = new day_node(weekday);
	to_add->set_next(rear->go_next());
	rear->set_next(to_add);
}

//menu formatted input process for planner application
void weekly_planner::input()
{
	char cmd[SIZE_CMD];
	char read_in[SIZE_MED];
	char * read_in_sized;
	weekly_event hold_event;

	do{
	cout << endl << "Command Options:" << endl << "dpa: display all events" << endl << "rma: remove all events" << endl;
	cout << "rm: remove by title" << endl << "dp: display by title" << endl << "rt: retrieve by title" << endl;
	cout << "ad: add event" << endl << "go: reply to event as going" << endl;
	cout << "ext: exit weekly planner" << endl << endl;
	cout << "What would you like to do with your weekly planner? ";
	cin.get(cmd, SIZE_CMD, '\n'); cin.ignore(100, '\n');
	cout << endl;

	if(strcmp(dpa, cmd) == 0)
	{
		if(!display_all())
			cout << endl << "Weekly planner empty." << endl;
	}

	else if(strcmp(rma, cmd) == 0)
	{
		if(!delete_all())
			cout << endl << "Weekly planner empty. Nothing could be removed." << endl;
	}

	else if(strcmp(rm, cmd) == 0)
	{
		cout << "Title of event to remove: ";
		cin.get(read_in, SIZE_MED, '\n'); cin.ignore(100, '\n');
		read_in_sized = new char[strlen(read_in) + 1];
		strcpy(read_in_sized, read_in);
		if(!remove(read_in_sized))
			cout << endl << "Title not found in weekly planner." << endl;
		delete read_in_sized;
	}

	else if(strcmp(dp, cmd) == 0)
	{
		cout << "Title of event to display: ";
		cin.get(read_in, SIZE_MED, '\n'); cin.ignore(100, '\n');
		read_in_sized = new char[strlen(read_in) + 1];
		strcpy(read_in_sized, read_in);
		if(!display(read_in_sized))
			cout << endl << "Title not found in weekly planner." << endl;
		delete read_in_sized;
	}

	else if(strcmp(rt, cmd) == 0)
	{
		cout << "Title of event to retrieve: ";
		cin.get(read_in, SIZE_MED, '\n'); cin.ignore(100, '\n');
		read_in_sized = new char[strlen(read_in) + 1];
		strcpy(read_in_sized, read_in);
		if(!retrieve(read_in_sized, hold_event))
			cout << endl << "Title not found in weekly planner." << endl;
		else
		{
			cout << endl << "Event retrieved." << endl;
			hold_event.display();
		}
		delete read_in_sized;
	}

	else if(strcmp(go, cmd) == 0)
	{
		cout << "Title of event to reply as going: ";
		cin.get(read_in, SIZE_MED, '\n'); cin.ignore(100, '\n');
		read_in_sized = new char[strlen(read_in) + 1];
		strcpy(read_in_sized, read_in);
		if(!going(read_in_sized))
			cout << endl << "Title not found in weekly planner." << endl;
		else
		{
			cout << endl << "Event marked as going." << endl;
		}
		delete read_in_sized;
	}

	else if(strcmp(ad, cmd) == 0)
	{
		if(!add(hold_event))
			cout << endl << endl << "**THIS TIME SLOT IS ALREADY TAKEN. EVENT COULD NOT BE ADDED.**" << endl;
	}

	else if(strcmp(ext, cmd) == 0)
		cout << "EXITING WEEKLY PLANNER" << endl << endl;

	else
		cout << "Please enter a valid command option." <<endl;

	}while(strcmp(cmd, ext) != 0);
}

//wrapper, displays all events for all days
int weekly_planner::display_all()
{
	int is_empty = 0;
	return display_all(rear->go_next(), is_empty);
}

//wrapper, deletes all events for all days
int weekly_planner::delete_all()
{
	int is_empty = 0;
	return delete_all(rear->go_next(), is_empty);
}

//recursive, displays all events for all days
int weekly_planner::display_all(day_node * & a_rear, int & empty)
{
	if(a_rear == this->rear)
	{
		if(a_rear->display_all())
			empty = 1;
		else
			cout << "No plans scheduled for this day yet." << endl;
		return empty;
	}

	if(a_rear->display_all())
		empty = 1;
	else
		cout << "No plans scheduled for this day yet." << endl;
	return display_all(a_rear->go_next(), empty);
}

//recursive, deletes all events for all days
int weekly_planner::delete_all(day_node * & a_rear, int & empty)
{
	if(a_rear == this->rear)
	{
		if(a_rear->delete_all())
			empty = 1;
		return empty;
	}

	if(a_rear->delete_all())
		empty = 1;
	return delete_all(a_rear->go_next(), empty);
}

//wrapper, searches for title in arg for all days, removes if found
int weekly_planner::remove(const char * to_remove)
{
	int exists = 0;
	return remove(rear->go_next(), to_remove, exists);
}

//recursive, searches for title in arg for all days, removes if found
int weekly_planner::remove(day_node * & a_rear, const char * to_remove, int & exists)
{
	if(a_rear == this->rear)
	{
		if(a_rear->remove(to_remove))
			exists = 1;
		return exists;
	}

	if(a_rear->remove(to_remove))
		exists = 1;

	return remove(a_rear->go_next(), to_remove, exists);
}

//wrapper, searches for title in arg for all days, displays if found
int weekly_planner::display(const char * to_display)
{
	int exists = 0;
	return display(rear->go_next(), to_display, exists);
}

//recursive, searches for title in arg for all days, displays if found
int weekly_planner::display(day_node * & a_rear, const char * to_display, int & exists)
{
	if(a_rear == this->rear)
	{
		if(a_rear->display(to_display))
			exists = 1;
		return exists;
	}

	if(a_rear->display(to_display))
		exists = 1;

	return display(a_rear->go_next(), to_display, exists);
}

//wrapper, searches for title in arg for all days, retrieves if found
//copies into retrieved argument
int weekly_planner::retrieve(const char * to_retrieve, weekly_event & retrieved)
{
	int exists = 0;
	return retrieve(rear->go_next(), to_retrieve, retrieved, exists);
}

//recursive, searches for title in arg for all days, retrieves if found
//copies into retrieved argument
int weekly_planner::retrieve(day_node * & a_rear, const char * to_retrieve, weekly_event & retrieved, int & exists)
{
	if(a_rear == this->rear)
	{
		if(a_rear->retrieve(to_retrieve, retrieved))
			exists = 1;
		return exists;
	}

	if(a_rear->retrieve(to_retrieve, retrieved))
		exists = 1;

	return retrieve(a_rear->go_next(), to_retrieve, retrieved, exists);
}

//wrapper, searches for title in arg for all days, marks as going if found
int weekly_planner::going(const char * to_go)
{
	int exists = 0;
	return going(rear->go_next(), to_go, exists);
}

//recursive, searches for title in arg for all days, marks as going if found
int weekly_planner::going(day_node * & a_rear, const char * to_go, int & exists)
{
	if(a_rear == this->rear)
	{
		if(a_rear->going(to_go))
			exists = 1;
		return exists;
	}

	if(a_rear->going(to_go))
		exists = 1;

	return going(a_rear->go_next(), to_go, exists);
}

//wrapper, adds weekly event
//calls input to add info first
int weekly_planner::add(weekly_event & to_add)
{
	to_add.input();
	return add(rear->go_next(), to_add);
}

//recursive, adds weekly event
//searches for correct weekday first
//adds to correct weekday node
int weekly_planner::add(day_node * & a_rear, weekly_event & to_add)
{
	char * rear_weekday = NULL;  
	a_rear->get_weekday(rear_weekday); //getting weekday from node

	if(a_rear == this->rear)
	{
		if(to_add.compare_weekday(rear_weekday) == 0)
			return a_rear->add(to_add);
	}


	if(to_add.compare_weekday(rear_weekday) == 0)
	{
		return a_rear->add(to_add);
	}

	return add(a_rear->go_next(), to_add);
}

//weekly planner destructor
weekly_planner::~weekly_planner()
{
	delete_all();
	/*
	for(int i=0; i<WEEK; ++i)
	{
		delete [] weekdays[i];
		weekdays = NULL;
	}
	*/
	delete [] weekdays;
}
