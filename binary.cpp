/* INCLUDE ********************************************************************/

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<cassert>

/* CLASSES ********************************************************************/

class Node
{
    public:
 	 std::string s;
	 int n;
	 Node *lname, *rname, *lmark, *rmark;
};

/* FUNCTIONS ******************************************************************/

void add_name(Node*& root, Node*& usernode)
/*	PURPOSE: 	Adds node to the binary search tree based on the user name.
	RECEIVES:	root - the root of the binary tree.
				usernode - the node to insert.
*/
{
	if (root == NULL)
		root = usernode;
	else if (usernode->s < root->s)
		add_name(root->lname, usernode);
	else add_name(root->rname, usernode);
}

void add_mark(Node*& root, Node*& usernode)
/*	PURPOSE: 	Adds node to the binary search tree based on the user mark.
	RECEIVES:	root - the root of the binary tree.
				usernode - the node to insert.
*/
{
	if (root == NULL)
		root = usernode;
	else if (usernode->n < root->n)
		add_mark(root->lmark, usernode);
	else add_mark(root->rmark, usernode);

}

void display_name(Node* root)
/*	PURPOSE: 	Displays all the binary search tree nodes, order by the user
				names.
	RECEIVES:	root - the root of the binary tree.
*/
{
	if (root != NULL)
	{	display_name(root->lname);
		std::cout << root->s << " " << root->n << std::endl;
		display_name(root->rname);
	}
}

void display_mark(Node* root)
/*	PURPOSE: 	Displays all the binary search tree nodes, order by the user
				marks.
	RECEIVES:	root - the root of the binary tree.
*/
{
	if (root != NULL)
	{	display_mark(root->rmark);
		std::cout << root->s << " " << root->n << std::endl;
		display_mark(root->lmark);
	}
}

void search_mark(Node* root, int x, bool& there)
/*	PURPOSE: 	Searches the binary tree for a specific user mark and
				displays user names that have that mark together with the
				mark.
	RECEIVES:	root - the root of the binary tree.
				x - the mark.
				there - a boolean to make true if the mark exists.
*/
{
	if (root->n == x)
	{	std::cout << root->s << " " << root->n << "  ";
		there = true;
	}
	if (root->lmark != NULL)
		search_mark(root->lmark, x, there);
	if (root->rmark != NULL)
		search_mark(root->rmark, x, there);
}

void search_name(Node* root, std::string st, bool& there)
/*	PURPOSE: 	Searches the binary tree for a specific user name and
				displays user marks that have that name together with the
				name.
	RECEIVES:	root - the root of the binary tree.
				st - the name.
				there - a boolean to make true if the name exists.
*/
{
	if (root->s == st)
	{	std::cout << root->s << " " << root->n << "  ";
		there = true;
	}
	if (root->lname != NULL)
		search_name(root->lname, st, there);
	if (root->rname != NULL)
		search_name(root->rname, st, there);
}

void construct_display(Node* root)
/*	PURPOSE: 	Calls the display and search procedures.
	RECEIVES:	root - the root of the binary tree.
*/
{
	std::cout << "Name order:" << std::endl;
	display_name(root);
	std::cout << std::endl << "Mark order:" << std::endl;
	display_mark(root);
	std::cout << std::endl;
	std::string response = "";
	std::cout << "Type in a name or a mark or ! to Quit: ";
	std::cin >> response;
	while(response != "!")
	{	bool there = false;
		int num;
		std::istringstream is(response);
		is >> num;
		if(is.fail())
		{	search_name(root, response, there);
			if(!there)
				std::cout << response << " not there" << std::endl;
		}
		else
		{
			search_mark(root, num, there);
			if(!there)
				std::cout << num << " not there" << std::endl;
		}
		std::cout << std::endl << std::endl << "Type in a name or a mark or ! to Quit: ";
		std::cin >> response;
	}
}

int main()
{
	std::cout << "Please enter the path to the file" << std::endl;
	std::string filepath = "";
	std::cin >> filepath;
    std::ifstream infile(filepath.c_str());
	if(infile.fail())
	{	std::cout << "File Open Failure " << std::endl;
		return EXIT_FAILURE;
	}
	std::string full_line;
	std::string name;
	int mark;

	Node* root = NULL;
	while (getline(infile, full_line))
	{	std::istringstream is(full_line);
		is >> name >> mark;
		Node* usernode = new Node;
		usernode->lname = usernode->rname = usernode->lmark = usernode->rmark = 
            NULL;
		usernode->s = name;
		usernode->n = mark;
		if (root == NULL)
			add_name(root, usernode);
		else
		{	add_name(root, usernode);
			add_mark(root, usernode);
		}
	}
	construct_display(root);
}
