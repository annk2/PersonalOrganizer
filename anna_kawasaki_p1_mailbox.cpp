#include "anna_kawasaki_p1.h"
using namespace std;

//Anna Kawasaki
//implementation of mailbox
//for application that organizes activities

//MAIL NODE IMPLEMENTATION

//mail node constructor
mail_node::mail_node(): next(0) {}

//mail node copy constructor for message
mail_node::mail_node(const mail_message & to_copy): mail_message(to_copy), next(0) {}

//mail node copy constructor for node
mail_node::mail_node(const mail_node & to_copy): mail_message(to_copy) {next = to_copy.next;}

//set next pointer to argument value
void mail_node::set_next(mail_node * source)
{
	if(!source)
	{
		next = NULL;
	}
	else
		next = source;
}

//returns next pointer
mail_node * & mail_node::go_next()
{
	return next;
}

//destructor for mail node
mail_node::~mail_node()
{
	if(!mail_message::remove())
		return;
	next = 0;
}

//deep copies all mail node information from source arg
void mail_node::copy(mail_node & source)
{
	mail_message::copy(source);
	next = source.next;
}


//MAILBOX IMPLEMENTATION

//mailbox constructor
mailbox::mailbox() //: message_list(0), category_list(0), num_categories(0)
{
	char read_in[SIZE_MED];

	cout << "How many categories do you want to use to organize your messages? ";
	cin >> num_categories; cin.ignore(100, '\n');
	
	message_list = new mail_node *[num_categories];
	category_list = new char * [num_categories];
	for(int i = 0; i<num_categories; ++i)
	{
		cout << "Category " << i+1 << ": ";
		cin.get(read_in, SIZE_MED, '\n'); cin.ignore(100, '\n');
		category_list[i] = new char[strlen(read_in) + 1];
		strcpy(category_list[i], read_in);
		message_list[i] = NULL;
	}
	cout << endl;
}

//menu input process for mailbox
void mailbox::input()
{
	char cmd[SIZE_CMD];
	char read_in[SIZE_MED];
	char * read_in_sized;
	mail_message hold_message;

	do{
	cout << endl << "Command Options:" << endl << "dpa: display all messages" << endl << "rma: remove all messages" << endl;
	cout << "rm: remove by title" << endl << "dp: display by title" << endl << "rt: retrieve by title" << endl;
	cout << "ad: add message" << endl << "flg: flag message" << endl;
	cout << "ext: exit mailbox" << endl << endl;
	cout << "What would you like to do with your mailbox? ";
	cin.get(cmd, SIZE_CMD, '\n'); cin.ignore(100, '\n');
	cout << endl;

	//display all
	if(strcmp(dpa, cmd) == 0)
	{
		if(!display_all())
			cout << endl << "Mailbox empty. Nothing could be displayed." << endl;
	}

	//remove all
	else if(strcmp(rma, cmd) == 0)
	{
		if(!delete_all())
			cout << endl << "Mailbox empty. Nothing could be removed." << endl;
	}

	//remove by title
	else if(strcmp(rm, cmd) == 0)
	{
		cout << "Title of email to remove: ";
		cin.get(read_in, SIZE_MED, '\n'); cin.ignore(100, '\n');
		read_in_sized = new char[strlen(read_in) + 1];
		strcpy(read_in_sized, read_in);
		if(!remove(read_in_sized))
			cout << endl << "Title not found in mailbox." << endl;
		delete read_in_sized;
	}

	//display by title
	else if(strcmp(dp, cmd) == 0)
	{
		cout << "Title of email to display: ";
		cin.get(read_in, SIZE_MED, '\n'); cin.ignore(100, '\n');
		read_in_sized = new char[strlen(read_in) + 1];
		strcpy(read_in_sized, read_in);
		if(!display(read_in_sized))
			cout << endl << "Title not found in mailbox." << endl;
		delete read_in_sized;
	}

	//retrieve by title (then display to confirm)
	else if(strcmp(rt, cmd) == 0)
	{
		cout << "Title of email to retrieve: ";
		cin.get(read_in, SIZE_MED, '\n'); cin.ignore(100, '\n');
		read_in_sized = new char[strlen(read_in) + 1];
		strcpy(read_in_sized, read_in);
		if(!retrieve(read_in_sized, hold_message))
			cout << endl << "Title not found in mailbox." << endl;
		else
		{
			cout << endl << "Email retrieved." << endl;
			hold_message.display();
		}
		delete read_in_sized;
	}

	//flag by title
	else if(strcmp(flg, cmd) == 0)
	{
		cout << "Title of email to flag: ";
		cin.get(read_in, SIZE_MED, '\n'); cin.ignore(100, '\n');
		read_in_sized = new char[strlen(read_in) + 1];
		strcpy(read_in_sized, read_in);
		if(!flag(read_in_sized))
			cout << endl << "Title not found in mailbox." << endl;
		else
		{
			cout << endl << "Email has been flagged." << endl;
		}
		delete read_in_sized;
	}

	//add message
	else if(strcmp(ad, cmd) == 0)
		add(hold_message);

	//exit mailbox
	else if(strcmp(ext, cmd) == 0)
		cout << "EXITING MAILBOX" << endl << endl;

	//command not valid
	else
		cout << "Please enter a valid command option." <<endl;

	}while(strcmp(cmd, ext) != 0);
}


//mailbox constructor with args
mailbox::mailbox(char ** categories, int num)
{
	num_categories = num;
	category_list = new char *[num_categories];
	for (int i = 0; i<num_categories; ++i)
	{
		category_list[i] = new char[strlen(categories[i]) + 1];
		strcpy(category_list[i], categories[i]);
	}

	message_list = new mail_node *[num_categories];
	for (int j = 0; j<num_categories; ++j)
	{
		message_list[j] = NULL;
	}
}

//mailbox copy constructor
mailbox::mailbox(const mailbox & to_copy)
{
	num_categories = to_copy.num_categories;
	message_list = new mail_node *[num_categories];
	category_list = new char * [num_categories];

	for (int i = 0; i<num_categories; ++i)
	{
		category_list[i] = new char[strlen(to_copy.category_list[i]) + 1];
		strcpy(category_list[i], to_copy.category_list[i]);
	}

	for (int j = 0; j<num_categories; ++j)
	{
		if(to_copy.message_list[j])
			message_list[j]= new mail_node(*to_copy.message_list[j]);
		else
			message_list[j] = NULL;
	}
}

//recursive, displays all messages in a category
void mailbox::display_all(mail_node * & head) const
{
	if(!head)
		return;

	head->display();
	display_all(head->go_next());
}

//wrapper, displays all messages in all categories
int mailbox::display_all() const
{
	int empty = 0;
	for (int i = 0; i<num_categories; ++i)
	{
		if(message_list[i]) //display for one category (if exists)
		{
			cout << "~~Displaying all ";
			message_list[i]->display_category();
			cout << " related messages.~~" << endl;
			display_all(message_list[i]);
			empty = 1;
		}
	}

	return empty;
}

//wrapper, deletes all messages in all categories
int mailbox::delete_all()
{
	int empty = 0;

	for (int i = 0; i<num_categories; ++i)
	{
		if(message_list[i])
		{
			delete_all(message_list[i]);
			message_list[i] = NULL;
			empty = 1;
		}
	}

	return empty;
}

//recursive, deletes all messages in a category
void mailbox::delete_all(mail_node * & head)
{
	if(!head)
		return;

	delete_all(head->go_next());
	delete head;
	head = NULL;
}

//wrapper, searches all categories to remove by title
int mailbox::remove(const char * to_remove)
{
	int exists = 0;

	for (int i = 0; i<num_categories && !exists; ++i)
	{
		if(message_list[i])
		{
			if(remove(message_list[i], to_remove))
				exists = 1;
		}
	}

	return exists;
}

//recursive, searches one category to remove by title
int mailbox::remove(mail_node * & head, const char * to_remove)
{
	if(!head)
		return 0;

	if(head->compare_title(to_remove) == 0)
	{
		head->set_next(head->go_next());
		delete head;
		head = NULL;
		return 1;
	}

	if(head->go_next() && head->go_next()->compare_title(to_remove) == 0)
	{
		head->set_next(head->go_next()->go_next());
		delete head->go_next();
		return 1;
	}

	return remove(head->go_next(), to_remove);
}

//wrapper, searches all categories to display by title
int mailbox::display(const char * to_display)
{
	int exists = 0;

	for (int i = 0; i<num_categories && !exists; ++i)
	{
		if(message_list[i])
		{
			if(display(message_list[i], to_display))
				exists = 1;
		}
	}
	return exists;
}

//recursive, searches one category to display by title
int mailbox::display(mail_node * & head, const char * to_display)
{
	if(!head)
		return 0;

	if(head->compare_title(to_display) == 0)
	{
		head->display();
		return 1;
	}

	return display(head->go_next(), to_display);
}

//wrapper, searches all categories to flag by title
int mailbox::flag(const char * to_flag)
{
	int exists = 0;

	for (int i = 0; i<num_categories && !exists; ++i)
	{
		if(message_list[i])
		{
			if(flag(message_list[i], to_flag))
				exists = 1;
		}
	}
	return exists;
}

//recursive, searches one category to flag by title
int mailbox::flag(mail_node * & head, const char * to_flag)
{
	if(!head)
		return 0;

	if(head->compare_title(to_flag) == 0)
	{
		head->mark_flagged();
		return 1;
	}

	return flag(head->go_next(), to_flag);
}

//wrapper, searches all categories to retrieve by title
//copies retrieved messages into argument
int mailbox::retrieve(const char * to_retrieve, mail_message & retrieved)
{
	int exists = 0;

	for (int i = 0; i<num_categories && !exists; ++i)
	{
		if(message_list[i])
		{
			if(retrieve(message_list[i], to_retrieve, retrieved))
				exists = 1;
		}
	}

	return exists;
}

//recursive, searches one category to retrieve by title
//copies retrieved messages into argument
int mailbox::retrieve(mail_node * & head, const char * to_retrieve, mail_message & retrieved)
{
	if(!head)
		return 0;

	if(head->compare_title(to_retrieve) == 0)
	{
		retrieved.copy(*head);
		return 1;
	}

	return retrieve(head->go_next(), to_retrieve, retrieved);
}

//adds message to mailbox
//searches by category first, adds category slot if not exist already
//calls input to get info first
int mailbox::add(mail_message & to_add)
{
	to_add.input(category_list, num_categories);
	
	int exists = -1; //check if already exists
	int available = -1; //check what category spot is available
	for (int i = 0; i<num_categories; ++i)
	{
		if(!message_list[i])
		{
			available = i;
		}
		else
		{
			if(to_add.compare_category(*message_list[i]) == 0)
			{
				exists = i;
			}
		}
	}

	mail_node * new_mail = new mail_node(to_add);
	mail_node * hold_head;

	if(exists == -1) //does not exist, need to add in available spot
	{
		message_list[available] = new_mail; 
	}

	else
	{
		hold_head = message_list[exists];
		message_list[exists] = new_mail;
		new_mail->set_next(hold_head);
	}

	return 1;
}

//mailbox destructor
mailbox::~mailbox()
{
	delete_all();

	delete [] category_list;
	delete [] message_list;	
}

