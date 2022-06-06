#include "anna_kawasaki_p1.h"
using namespace std;

//Anna Kawasaki
//client program to test hierarchy
//and data structures
//for application that organizes activities

int main()
{
	char cmd;

	cout << endl << endl << "~~ Welcome to your information organizer! ~~" << endl;
	cout << "Applications to use: mailbox, to do list, weekly planner" << endl << endl;


	//initializing applications
	mailbox my_mailbox;
	todo_list my_todo_list;
	weekly_planner my_week;
	
	do{
	cout << endl << "Here are your menu options: " <<endl;
	cout << "m: enter mailbox application" << endl << "t: enter to do list application" << endl;
	cout << "w: enter weekly planner application" << endl << "q: quit organizer program" << endl << endl;

	cout << "Which application would you like to use: ";
	cin >> cmd; cin.ignore(100, '\n');
	
	switch(cmd)
	{
		case 'm':
			my_mailbox.input();
			break;
		case 't':
			my_todo_list.input();
			break;
		case 'w':
			my_week.input();
			break;
		case 'q':
			cout << "QUITTING PROGRAM." << endl << endl;
			break;
		default:
			cout << "Please enter a valid menu option." << endl;
	}

	}while(cmd != 'q');


	return 0;
}
