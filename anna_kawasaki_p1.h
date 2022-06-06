#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>

//Anna Kawasaki
//Header file outlining classes
//for application that organizes activities

//input size constants
const int SIZE_SM = 15;
const int SIZE_MED = 30;
const int SIZE_LG = 200;
const int SIZE_CMD = 4;

//constants for week and day
const int WEEK = 7;
const int TIME = 48; //each hour split into 2 30 min sections

//command constants for menus
const char dpa[SIZE_CMD] = "dpa";
const char rma[SIZE_CMD] = "rma";
const char ext[SIZE_CMD] = "ext";
const char rm[SIZE_CMD] = "rm";
const char dp[SIZE_CMD] = "dp";
const char rt[SIZE_CMD] = "rt";
const char ad[SIZE_CMD] = "ad";

const char flg[SIZE_CMD] = "flg";
const char go[SIZE_CMD] = "go";

//superclass
//holds date information
class date
{
	public:
		date(); //default
		void input(); 
		void copy(date & to_copy);
		date(const date & copy_date); //copy
		int display() const; 
		int remove();
		int compare_weekday(const char * to_compare) const;
		~date();
	protected:
		bool check_weekday(const char * to_check); //check to make sure weekday is valid
		char * month;
		char * day;
		char * year;
		char * weekday;
		char ** week;
};

//subclass of date
//holds shared activity information
class activity: public date
{
	public:
		activity(); //default
		void input();
		void copy(activity & to_copy);
		activity(const activity & copy_activity); //copy
		int display() const;
		int remove();
		int compare_title(const char * to_compare) const; //with strcmp
		int compare_title_activity(activity & to_compare) const;
		~activity();
	protected:
		char * title;
		char * description;
};

//subclass of activity
//holds information about to do list item
//will be organized by priority in a BST
class to_do: public activity
{
	public:
		to_do(); //default
		to_do(const to_do & copy_to_do); //copy
		void input();
		void copy(to_do & to_copy);
		int display() const;
		int remove();
		int compare_priority(const to_do & to_compare) const; //with strcmp
		~to_do();
	protected:
		int priority;
};

//subclass of activity
//holds information about outgoing mail message
//will be organized by category in an array of LLLs 
class mail_message: public activity
{
	public:
		mail_message(); //default
		void input(char ** category_check, int num_cat);
		void copy(mail_message & to_copy);
		mail_message(const mail_message & copy_mail_message); //copy
		int display() const;
		void display_category() const;
		int remove();
		int compare_category(const mail_message & to_compare) const;
		int compare_category(const char * to_compare) const;
		int mark_flagged(); //marks flag as true
		~mail_message();
	protected:
		char * category;
		char * recipient;
		bool flag;
};

//subclass of activity
//holds information about events repeated every week
//will be organized by weekday in a CLL of arrays, with timeslots
class weekly_event: public activity
{
	public:
		weekly_event(); //default
		void input();
		void copy(weekly_event & to_copy);
		weekly_event(const weekly_event & copy_weekly_event); //copy
		int display() const;
		int remove();
		int mark_going(); //marks going as true
		int get_hour();
		int get_min();
		int get_length();
		~weekly_event();
	protected:
		char * location;
		char * people;
		int length;
		int hour;
		int min;
		bool going;
};

//subclass of message
//packages message information
//to store in array of LLL
class mail_node: public mail_message
{
	public:
		mail_node();
		mail_node(const mail_message & to_copy); 
		mail_node(const mail_node & to_copy);
		void set_next(mail_node * source);
		void copy(mail_node & source);
		mail_node * & go_next();
		~mail_node();

	protected:
		mail_node * next;
};

//mailbox
//sorted by category 
class mailbox
{
	public:
		mailbox();
		void input();
		mailbox(const mailbox & to_copy);
		mailbox(char ** categories, int num);
		int display_all() const;
		int delete_all();
		int remove(const char * to_remove); //search by title (same below as well)
		int display(const char * to_display);
		int flag(const char * to_flag); 
		int retrieve(const char * to_retrieve, mail_message & retrieved);
		int add(mail_message & to_add);
		~mailbox();
	protected:
		int remove(mail_node * & head, const char * to_remove);
		int display(mail_node * & head, const char * to_display);
		int retrieve(mail_node * & head, const char * to_retrieve, mail_message & retrieved);
		int flag(mail_node * & head, const char * to_flag); 
		void delete_all(mail_node * & head);
		void display_all(mail_node * & head) const;

		mail_node ** message_list;
		char ** category_list;
		int num_categories;
};

//packages daily events
//to store in CLL of arrays
class day_node
{
	public:
		day_node();
		day_node(const char * a_weekday);
		day_node(day_node & to_copy);
		int display_all();
		int delete_all();
		int remove(const char * to_remove);//search by title (same below as well)
		int display(const char * to_display);
		int going(const char * to_go);
		int retrieve(const char * to_retrieve, weekly_event & retrieved);
		int add(weekly_event & to_add);
		void get_weekday(char * & a_weekday);
		void set_next(day_node * connection);
		day_node * & go_next();
		//int compare_weekday(char * to_compare);
		~day_node();
	protected:
		int find_title_index(const char * to_find); //finds index for title, -1 if doesnt exist
		int index_time(int an_hour, int a_minute); //calculates index by time
		int how_many_slots(int a_length); //calculates slots needed by length

		char * weekday;
		weekly_event ** time_slots;
		day_node * next;
};

//CLL of arrays to store weekly events
//has nodes
//sorted into days of the week
class weekly_planner
{
	public:
		weekly_planner();
		weekly_planner(weekly_planner & to_copy);
		void load_week();
		void input();
		int display_all();
		int delete_all();
		int remove(const char * to_remove);//search by title (same below as well)
		int display(const char * to_display);
		int retrieve(const char * to_retrieve, weekly_event & retrieved);
		int going(const char * to_go);
		int add(weekly_event & to_add);
		void add_node(const char * weekday); 
		~weekly_planner();
	protected:
		int add(day_node * & a_rear, weekly_event & to_add);
		int display_all(day_node * & a_rear, int & empty);
		int delete_all(day_node * & a_rear, int & empty);
		int remove(day_node * & a_rear, const char * to_remove, int & exists);
		int retrieve(day_node * & a_rear, const char * to_retrieve, weekly_event & retrieved, int & exists);
		int display(day_node * & a_rear, const char * to_display, int & exists);
		int going(day_node * & a_rear, const char * to_go, int & exists);
		void copy_CLL(day_node * & destination, day_node * source, day_node * hold_rear);

		day_node * rear;
		char ** weekdays;
};

//subclass of to do item
//packages to do list information
//to store in BST
class BST_node: public to_do
{
	public:
		BST_node();
		BST_node(const to_do & to_copy); 
		BST_node(const BST_node & to_copy);
		BST_node * & go_left();
		BST_node * & go_right();
		void set_left(BST_node * connection);
		void set_right(BST_node * connection);
		bool if_left() const;
		bool if_right() const;
	protected:
		BST_node * left;
		BST_node * right;
};

//binary search tree to store to do items
//has nodes
//sorted by priority
class todo_list
{
	public:
		todo_list();
		void input();
		todo_list(const todo_list & to_copy);
		int display_all();
		int delete_all();
		int remove(const char * to_remove);//search by title (same below as well)
		int display(const char * to_display);
		int retrieve(const char * to_retrieve, to_do & retrieved);
		int add(to_do & to_add);
		~todo_list();
	protected:
		int add(BST_node * & a_root, const to_do & to_add);
		int remove(BST_node * & a_root, const char * to_remove);
		int display(BST_node * & a_root, const char * to_display);
		int retrieve(BST_node * & a_root, const char * to_retrieve, to_do & retrieved);
		void copy_tree(BST_node * & destination, BST_node * source);
		void delete_all(BST_node * & a_root);
		void display_all(BST_node * & a_root);

		BST_node * root;
};


