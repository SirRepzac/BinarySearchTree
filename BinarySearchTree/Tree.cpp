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
}

void Tree::InsertMethod(int key, Node* from)
{
	cout << "Inserting " + to_string(key) + " against " + from->ToString() << endl;
	if (from->IsKeyInNode(key))
	{
		cout << "Err: Key " + to_string(key) + " already in tree" << endl;
		return;
	}



		// If the has children
	if (!from->IsLeaf())
	{
		Node* nextNode = from->NextNode(key);
		InsertMethod(key, nextNode);
	}
	// If the node is full and does not have children
	else if (from->keyAmount >= Node::maxKeyAmount)
	{
		int newKey = InsertAndSplitNode(from, key);
		Node* parentToNewsplitChildren = from->parent;
		Node* nextNode = parentToNewsplitChildren->NextNode(key);
		//InsertMethod(newKey, nextNode);
	} 
	// If the node is not full and does not have children
	else
	{
		from->AddNewKey(key, from->keyAmount);
		from->keyAmount++;
		from->SortKeys();
	}

	ToString();
}

int Tree::InsertAndSplitNode(Node* from, int key)
{
	if (from->keyAmount < Node::maxKeyAmount)
		return -1;


	const int maxKeys = Node::maxKeyAmount + 1;

	int keys[Node::maxKeyAmount + 1];

	for (int i = 0; i < from->keyAmount; i++)
	{
		keys[i] = from->keys[i];
	}

	keys[Node::maxKeyAmount] = key;

	std::sort(keys, keys + maxKeys);

	int midIndex = (maxKeys) / 2;  // Find the middle key
	int midKey = keys[midIndex];

	Node* leftNode = new Node();
	Node* rightNode = new Node();

	// Populate leftNode keys
	for (int i = 0; i < midIndex; i++)
	{
		leftNode->keys[i] = keys[i];
		leftNode->keyAmount++;
	}

	// Populate rightNode keys
	for (int i = midIndex + 1; i < maxKeys; i++)
	{
		rightNode->keys[i - (midIndex + 1)] = keys[i];
		rightNode->keyAmount++;
	}

	cout << to_string(key) + from->ToString() + "->" + leftNode->ToString() + to_string(midKey) + rightNode->ToString() << endl;

	if (!from->IsLeaf())
	{
		for (int i = 0; i <= midIndex; i++)
		{
			leftNode->children[i] = from->children[i];

			if (leftNode->children[i] != nullptr)
			{
				leftNode->children[i]->parent = leftNode;
			}
		}

		for (int i = midIndex + 1; i < maxKeys; i++)
		{
			rightNode->children[i - (midIndex + 1)] = from->children[i];

			if (rightNode->children[i - (midIndex + 1)] != nullptr)
			{
				rightNode->children[i - (midIndex + 1)]->parent = rightNode;
			}
		}
	}

	if (from->parent == nullptr)
	{
		Node* newRoot = new Node();
		newRoot->keys[0] = midKey;
		newRoot->keyAmount = 1;
		newRoot->children[0] = leftNode;
		newRoot->children[1] = rightNode;
		head = newRoot;
		leftNode->parent = newRoot;
		rightNode->parent = newRoot;
		from->parent = newRoot;
	}
	else
	{
		Node* parent = from->parent;

		if (parent->keyAmount < Node::maxKeyAmount)
		{
			int pos = parent->NodeNeedsKey();
			parent->AddNewKey(midKey, pos);
			parent->keyAmount++;
			parent->SortKeys();
		}
		else
		{
			InsertAndSplitNode(parent, midKey);
		}

		for (int i = 0; i < parent->keyAmount + 1; i++)
		{
			if (parent->children[i] == from)
			{
				parent->children[i] = leftNode;
				for (int j = parent->keyAmount; j > i + 1; j--)
				{
					parent->children[j] = parent->children[j - 1];
				}
				parent->children[i + 1] = rightNode;
				break;
			}
		}

		leftNode->parent = parent;
		rightNode->parent = parent;
	}

	// Debugging: Print the state of the nodes after splitting
	std::cout << "Split to: " + leftNode->ToString() + rightNode->ToString() + " with parent " + leftNode->parent->ToString() << endl;
	return midKey;
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




