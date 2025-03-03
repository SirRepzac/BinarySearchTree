#include "Tree.h"

Tree::Tree()
{
	head = nullptr;
}

void Tree::Insert(Node* newNode)
{
	int key = 0;

	for (int i = 0; i < newNode->maxKeyAmount; i++)
	{
		if (newNode->keys[i] != 0)
		{
			key = newNode->keys[i];
			break;
		}
	}

	if (key == 0)
	{
		cout << "Err: No value in node" << endl;
		return;
	}

	InsertMethod(key, head);
}

void Tree::Insert(int key)
{
	if (key == 0)
	{
		cout << "Err: Key cannot be zero" << endl;
		return;
	}

	if (head == nullptr)
	{
		head = new Node();
		head->keys[0] = key;
		head->keyAmount = 1;
		return;
	}

	InsertMethod(key, head);

	cout << "Tree now looks like: \n" + ToString() << endl;
}

void Tree::InsertMethod(int key, Node* from)
{
	cout << "Inserting " + to_string(key) + " against " + from->ToString() << endl;
	if (from->IsKeyInNode(key))
	{
		cout << "Err: Key " + to_string(key) + " already in tree" << endl;
		return;
	}



	// If the node has children
	if (!from->IsLeaf())
	{
		Node* nextNode = from->NextNode(key);
		if (nextNode != nullptr)
		{
			cout << "Going into childnode..." << endl;
			InsertMethod(key, nextNode);
			return;
		}
	}
	// If the node is a leaf
	else
	{
		from->AddKey(key);
		while(head->parent != nullptr)
		{
			head = head->parent;
		}
	} 

}

Node* Tree::Find(int key)
{
	return FindMethod(key, head);
}

Node* Tree::FindMethod(int key, Node* from)
{
	if (from == nullptr)
		return nullptr;

	if (from->IsKeyInNode(key))
		return from;

	Node* nextNode = from->NextNode(key);

	FindMethod(key, nextNode);
}

string Tree::ToString()
{
	std::ostringstream oss;
	if (head == nullptr)
		return oss.str();

	std::queue<Node*> currentLevel;
	currentLevel.push(head);

	while (!currentLevel.empty())
	{
		std::queue<Node*> nextLevel;

		while (!currentLevel.empty())
		{
			Node* node = currentLevel.front();
			currentLevel.pop();

			if (node != nullptr)
			{

				oss << node->ToString() << " ";
				for (int i = 0; i <= node->keyAmount; ++i)
				{
					nextLevel.push(node->children[i]);
				}
			}
		}
		oss << "\n";
		currentLevel = nextLevel;
	}

	return oss.str();
}




