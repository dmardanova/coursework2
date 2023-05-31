#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <queue>

using namespace std;

ofstream f("f.txt");

struct Tree
{

	int key;
	Tree* left;
	Tree* right;
};

Tree* add_el(int value, Tree* root)
{
	if (root == nullptr)
	{
		root = new Tree;
		root->left = root->right = NULL;
		root->key = value;
		return root;

	}
	if (root->key > value)
	{
		if (root->key > value) {
			root->left = add_el(value, root->left);
		}
		else if (root->key < value) {
			root->right = add_el(value, root->right);
		};
		return root;
	}
}
Tree* search_el(Tree* root, int value)
{
	if (root != NULL)
	{
		return NULL;
	}
	else {

		if (value == root->key) {
			return root;
		}
		if (value > root->key) {
			return search_el(root->right, value);
		}
		else {
			return search_el(root->left, value);
		}
	}
}
Tree* printTree(Tree* tree, string prev_str, bool isRight, ostream& f) {
	if (tree == NULL)
		return NULL;
	string new_prev_str = prev_str + "    ";
	printTree(tree->right, new_prev_str, true, f);
	f << prev_str;
	if (isRight) {
		f << ".-->";
		prev_str += "   |";
	}
	else if (prev_str.empty())
		f << "-->";
	else {
		f << "`-->";
		prev_str = prev_str.substr(0, prev_str.length() - 4);
	}
	f << tree->key << endl;
	printTree(tree->left, prev_str, false, f);
}

void preOrderTravers(Tree* root) {
	if (root) {
		cout << root->key << " ";
		preOrderTravers(root->left);
		preOrderTravers(root->right);
	}
}
void postOrderTravers(Tree* root) {
	if (root) {
		postOrderTravers(root->left);
		postOrderTravers(root->right);
		cout << root->key << " ";
	}
}
void breadthFirstTraversal(Tree* root) {
	if (root == NULL)
		return;
	queue<Tree*> q;
	q.push(root);
	while (!q.empty()) {
		Tree* current = q.front();
		cout << current->key << " ";
		if (current->left != NULL)
			q.push(current->left);
		if (current->right != NULL)
			q.push(current->right);
		q.pop();
	}
}
Tree* min_el(Tree* root) {
	while (root->left)
		root = root->left;
	return root;
}

Tree* del_el(Tree* element, int key) {
	if (element == NULL)
		return NULL;

	if (key < element->key)
		element->left = del_el(element->left, key);
	else if (key > element->key)
		element->right = del_el(element->right, key);
	else {
		if (element->left == NULL && element->right == NULL)
			element = NULL;
		else if (element->left == NULL || element->right == NULL)
			element = element->left ? element->left : element->right;
		else {
			Tree* minnode = min_el(element->right);
			element->key = minnode->key;
			element->right = del_el(element->right, minnode->key);
		}
	}

	return element;
}

void del_el_all(Tree* element) {
	if (element != NULL) {
		del_el_all(element->left);
		del_el_all(element->right);
		delete element;
	}
}


int main()
{
	Tree* root = nullptr;
	cout << "Input list: \n";
	int num;
	while (cin >> num)
	{
		root=add_el(num, root);
	}
	printTree(root, "", false, cout);
	ofstream f("output.txt");
	f << "Tree after creation:\n";
	printTree(root, "", false, f);
	cin.clear();
	cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
	bool flag = true;
	while (flag) {
		cout <<
			"\n1)\n"
			"2)\n"
			"3)\n"
			"4)\n"
			"5)\n"
			"6)\n"
			"0)\n";
		int type;
		cin >> type;
		switch (type) {
		case 0:
			flag = false;
			break;
		case 1:
			cout << "Enter an element: ";
			f << "Tree after adding elements:\n";
			std::cin >> num;
			root = add_el(num, root);
			break;
		case 2:
			cout << "Enter an element: ";
			f << "Tree after deleting elements:\n";
			cin >> num;
			if (!search_el(root, num))
				cout << "Element " << num << "Wasnt found!\n";
			else {
				root = del_el(root, num);
			}
			break;
		case 3:
			std::cout << "Enter an element: ";
			std::cin >> num;
			if (search_el(root, num)) {
				cout << "The element " << num << " Was found.";
				f << "The element " << num << " Was found.\n";
			}
			else {
				cout << "Element " << num << "Wasnt found.";
				f << "Element " << num << "Wasnt found\n";
			}
			break;
		case 4:
			cout << "Direct search: ";
			preOrderTravers(root);
			break;
		case 5:
			std::cout << "Reverse search: ";
			postOrderTravers(root);
			break;
		case 6:
			std::cout << "Search in width: ";
			breadthFirstTraversal(root);
			break;
		default:
			std::cout << "Error input!";
		}
		cout << "\n\n";
		f << "\n\n";
		printTree(root, "", false, cout);
		printTree(root, "", false, f);
		cout << std::endl;
		f << std::endl;
	}
	f.close();
	return 0;
}

