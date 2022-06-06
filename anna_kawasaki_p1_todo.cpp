#include "anna_kawasaki_p1.h"
using namespace std;

//Anna Kawasaki
//implementation of to do list
//for application that organizes activities

//BST NODE IMPLEMENTATION

//BST node constructor
BST_node::BST_node(): left(0), right(0) {}

//BST node copy constructor for to do list item
BST_node::BST_node(const to_do & to_copy): to_do(to_copy), left(0), right(0) {}

//BST node copy constructor for BST node
BST_node::BST_node(const BST_node & to_copy): to_do(to_copy), left(to_copy.left), right(to_copy.right) {}

//returns left pointer
BST_node * & BST_node::go_left()
{
	return left;
}

//returns right pointer
BST_node * & BST_node::go_right()
{
	return right;
}

//sets left pointer to arg connection
void BST_node::set_left(BST_node * connection)
{
	if(!connection)
		left = NULL;
	else
		left = connection;
}

//sets right pointer to arg connection
void BST_node::set_right(BST_node * connection)
{
	if(!connection)
		right = NULL;
	else
		right = connection;
}

//checks if left exists, returns true if does, false if doesnt
bool BST_node::if_left() const
{
	if(left)
		return true;
	else
		return false;
}

//checks if right exists, returns true if does, false if doesnt
bool BST_node::if_right() const
{
	if(right)
		return true;
	else
		return false;
}

//TO DO LIST IMPLEMENTATION
//BST of BST nodes, organized by priority 1-5

//to do list constructor
todo_list::todo_list(): root(0) {}

//input menu process for to do list application
void todo_list::input()
{
	char cmd[SIZE_CMD];
	char read_in[SIZE_MED];
	char * read_in_sized;
	to_do hold_task;

	do{
	cout << endl << "Command Options:" << endl << "dpa: display all tasks" << endl << "rma: remove all tasks" << endl;
	cout << "rm: remove by title" << endl << "dp: display by title" << endl << "rt: retrieve by title" << endl;
	cout << "ad: add task" << endl << "ext: exit to do list" << endl << endl;
	cout << "What would you like to do with your to do list? ";
	cin.get(cmd, SIZE_CMD, '\n'); cin.ignore(100, '\n');
	cout << endl;

	//displays all tasks
	if(strcmp(dpa, cmd) == 0)
	{
		if(!display_all())
			cout << endl << "To do list empty. Nothing could be displayed." << endl;
	}

	//removes all tasks
	else if(strcmp(rma, cmd) == 0)
	{
		if(!delete_all())
			cout << endl << "To do list empty. Nothing could be removed." << endl;
	}

	//removes task by title
	else if(strcmp(rm, cmd) == 0)
	{
		cout << "Title of task to remove: ";
		cin.get(read_in, SIZE_MED, '\n'); cin.ignore(100, '\n');
		read_in_sized = new char[strlen(read_in) + 1];
		strcpy(read_in_sized, read_in);
		if(!remove(read_in_sized))
			cout << endl << "Title not found in to do list." << endl;
		delete read_in_sized;
	}

	//displays task by title
	else if(strcmp(dp, cmd) == 0)
	{
		cout << "Title of task to display: ";
		cin.get(read_in, SIZE_MED, '\n'); cin.ignore(100, '\n');
		read_in_sized = new char[strlen(read_in) + 1];
		strcpy(read_in_sized, read_in);
		if(!display(read_in_sized))
			cout << endl << "Title not found in to do list." << endl;
		delete read_in_sized;
	}

	//retrieves task by title, displays to confirm
	else if(strcmp(rt, cmd) == 0)
	{
		cout << "Title of task to retrieve: ";
		cin.get(read_in, SIZE_MED, '\n'); cin.ignore(100, '\n');
		read_in_sized = new char[strlen(read_in) + 1];
		strcpy(read_in_sized, read_in);
		if(!retrieve(read_in_sized, hold_task))
			cout << endl << "Title not found in to do list." << endl;
		else
		{
			cout << endl << "Task retrieved." << endl;
			hold_task.display();
		}
		delete read_in_sized;
	}

	//adds task to to do list
	else if(strcmp(ad, cmd) == 0)
		add(hold_task);

	//exits to do list application, function
	else if(strcmp(ext, cmd) == 0)
		cout << "EXITING TO DO LIST" << endl << endl;

	//not a valid command
	else
		cout << "Please enter a valid command option." <<endl;

	}while(strcmp(cmd, ext) != 0);
}

//to do list copy constructor
todo_list::todo_list(const todo_list & to_copy)
{
	copy_tree(root, to_copy.root);
}

//wrapper, displays all tasks in to do list, sorted by priority
int todo_list::display_all()
{
	if(!root)
		return 0;
	display_all(root);
	return 1;
}

//recursive, displays all tasks in to do list, sorted by priority
void todo_list::display_all(BST_node * & a_root)
{
	if(!a_root)
		return;

	display_all(a_root->go_left());
	a_root->display();
	display_all(a_root->go_right());
}

//wrapper, deletes all tasks in to do list
int todo_list::delete_all()
{
	if(!root)
		return 0;
	delete_all(root);
	return 1;
}

//recursive, deletes all tasks in to do list
void todo_list::delete_all(BST_node * & a_root)
{
	if(!a_root)
		return;
	delete_all(a_root->go_left());
	delete_all(a_root->go_right());
	delete a_root;
	a_root = NULL;
}

//wrapper, searches for title, removes if found
int todo_list::remove(const char * to_remove)
{
	if(!root)
		return 0;
	return remove(root, to_remove);
}

//recursive, searches for title, removes if found
int todo_list::remove(BST_node * & a_root, const char * to_remove)
{
	if(!a_root)
		return 0;

	if(a_root->compare_title(to_remove) == 0)
	{
		if(!a_root->if_left() && !a_root->if_right()) //no children
		{
			delete a_root;
			a_root = NULL;
		}

		else if(!a_root->if_right() && a_root->if_left()) //1 child
		{
			BST_node * hold = a_root->go_left();
			delete a_root;
			a_root = hold;
		}

		else if(!a_root->if_left() && a_root->if_right()) //1 child
		{
			BST_node * hold = a_root->go_right();
			delete a_root;
			a_root = hold;
		}

		else //2 children
		{
			BST_node * current = a_root->go_right();

			if(!current->if_left()) //IOS found
			{
				a_root->remove();
				a_root->copy(*current);
				BST_node * hold = current->go_right();
				delete current;
				a_root->set_right(hold);
			}

			else //need to find IOS
			{
				BST_node * parent;
				while(current->if_left())
				{
					parent = current;
					current = current->go_left();
				}
				//current is at IOS
				a_root->remove();
				a_root->copy(*current);
				BST_node * hold = current->go_right();
				parent->set_left(hold);
				delete current;
			}
		}
		return 1;
	}
		return remove(a_root->go_left(), to_remove) || remove(a_root->go_right(), to_remove);  
}


//wrapper, searches for title, displays if found
int todo_list::display(const char * to_display)
{
	if(!root)
		return 0;
	return display(root, to_display);
}

//recursive, searches for title, displays if found
int todo_list::display(BST_node * & a_root, const char * to_display)
{
	if(!a_root)
	{
		return 0;
	}
	
	if(a_root->compare_title(to_display) == 0)
	{
		a_root->display();
		return 1;
	}

	return display(a_root->go_left(), to_display) || display(a_root->go_right(), to_display);
}

//wrapper, searches for title, retrieves if found
//copies into retrieved argument
int todo_list::retrieve(const char * to_retrieve, to_do & retrieved)
{
	if(!root)
		return 0;
	return retrieve(root, to_retrieve, retrieved);
}

//recursive, searches for title, retrieves if found
//copies into retrieved argument
int todo_list::retrieve(BST_node * & a_root, const char * to_retrieve, to_do & retrieved)
{
	if(!a_root)
	{
		return 0;
	}
	
	if(a_root->compare_title(to_retrieve) == 0)
	{
		retrieved.copy(*a_root);
		return 1;
	}

	return retrieve(a_root->go_left(), to_retrieve, retrieved) || retrieve(a_root->go_right(), to_retrieve, retrieved);
}

//adds to do list item into BST
//calls input to load info first
int todo_list::add(to_do & to_add)
{
	to_add.input();
	return add(root, to_add);
}

//adds to do list item into BST
//places it in order by priority
int todo_list::add(BST_node * & a_root, const to_do & to_add)
{
	if(!a_root) //root or leaf
	{
		a_root = new BST_node(to_add);
		return 1;
	}

	if(to_add.compare_priority(*a_root) < 0) //priority to add is less than node pointer
		return add(a_root->go_left(), to_add);
	else
		return add(a_root->go_right(), to_add); //priority to add is more
}

//copies tree from source arg into tree destination arg
void todo_list::copy_tree(BST_node * & destination, BST_node * source)
{
	if(!source)
		root = NULL;

	destination = new BST_node(*source);

	copy_tree(destination->go_left(), source->go_left());
	copy_tree(destination->go_right(), source->go_right());
}


	
//to do list destructor
todo_list::~todo_list()
{
	delete_all();
}
