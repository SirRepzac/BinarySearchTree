#include "BTreeTree.h"

BTreeTree::BTreeTree()
{
	head = nullptr;
}

void BTreeTree::Insert(BTreeNode* newNode)
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

void BTreeTree::Insert(int key)
{
	if (key == 0)
	{
		cout << "Err: Key cannot be zero" << endl;
		return;
	}

	if (head == nullptr)
	{
		head = new BTreeNode();
		head->keys[0] = key;
		head->keyAmount = 1;
		return;
	}

	InsertMethod(key, head);

	cout << "Tree now looks like: \n" + ToString() << endl;
}

void BTreeTree::InsertMethod(int key, BTreeNode* from)
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
		BTreeNode* nextNode = from->NextNode(key);
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

BTreeNode* BTreeTree::Find(int key)
{
	return FindMethod(key, head);
}

BTreeNode* BTreeTree::FindMethod(int key, BTreeNode* from)
{
	if (from == nullptr)
		return nullptr;

	if (from->IsKeyInNode(key))
		return from;

	BTreeNode* nextNode = from->NextNode(key);

	FindMethod(key, nextNode);
}

string BTreeTree::ToString()
{
	std::ostringstream oss;
	if (head == nullptr)
		return oss.str();

	std::queue<BTreeNode*> currentLevel;
	currentLevel.push(head);

	while (!currentLevel.empty())
	{
		std::queue<BTreeNode*> nextLevel;

		while (!currentLevel.empty())
		{
			BTreeNode* node = currentLevel.front();
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




