#include "BSTTree.h"
#include <queue>
#include <sstream>

using namespace std;

BSTTree::BSTTree()
{
	head = nullptr;
	c = 0.75f;
}

BSTNode* BSTTree::Find(int key)
{
	return FindAlgo(key, head);
}

BSTNode* BSTTree::FindAlgo(int key, BSTNode* currentNode)
{
	if (currentNode == nullptr)
		return nullptr;

	else if (key == currentNode->key)
		return currentNode;

	else
		return FindAlgo(key, currentNode->GetNextNode(key));
}

void BSTTree::Insert(int key)
{
	if (head == nullptr)
	{
		BSTNode* newHead = new BSTNode(key);
		head = newHead;
		cout << "Created new head with key" + to_string(key) << endl;
	}
	else
	{
		InsertAlgo(key, head);
		cout << "-----Insertion complete-----" << endl;
		
	}
}

void BSTTree::InsertAlgo(int key, BSTNode* currentNode)
{
	if (key == currentNode->key)
	{
		cout << "Key already in tree" << endl;
		return;
	}

	BSTNode* nextNode = currentNode->GetNextNode(key);

	if (nextNode == nullptr)
	{
		currentNode->SetNewChild(key);
		cout << "Set new child of " + currentNode->ToString() + " to " + to_string(key) << endl;
	}
	else
	{
		cout << "Going into child of " + currentNode->ToString() + "..." << endl;
		InsertAlgo(key, nextNode);
	}
}

void BSTTree::Delete(int key)
{
	BSTNode* nodeWithKey = Find(key);
	Delete(nodeWithKey);
}

void BSTTree::Delete(BSTNode* node)
{
	if (node == nullptr)
	{
		cout << "Key not found" << endl;
		return;
	}
	else
	{
		cout << "Deleting " + node->ToString() << endl;

		// The node being deleted has no children
		if (node->IsLeaf())
		{
			if (node == head)
			{
				head = nullptr;
			}
			else
			{
				node->parent->DeleteChild(node);

			}

			delete node;
			return;
		}
		// The node being deleted has 1 child
		else if (node->ChildAmount() == 1)
		{
			if (node->leftChild == nullptr)
			{
				if (node == head)
				{
					head = node->rightChild;
					node->rightChild->parent = nullptr;
				}
				else
				{
					node->rightChild->parent = node->parent;
					int nodeWithKeyId = node->parent->GetChildId(node);
					node->parent->children[nodeWithKeyId] = node->rightChild;
				}
			}
			else
			{
				if (node == head)
				{
					head = node->leftChild;
					node->leftChild->parent = nullptr;
				}
				else
				{
					node->leftChild->parent = node->parent;
					int nodeWithKeyId = node->parent->GetChildId(node);
					node->parent->children[nodeWithKeyId] = node->leftChild;
				}
			}

			delete node;
			return;
		}
		// The node being deleted has 2 children
		else
		{
			// Swap value with the smallest node in the right subtree

			BSTNode* smallestInRightSubtree = node->rightChild->GetSmallest();
			node->key = smallestInRightSubtree->key;
			Delete(smallestInRightSubtree);
		}
	}
}

bool BSTTree::CheckIfRebalanceIsNeeded(BSTNode* node)
{
	if (node->IsLeaf())
	{
		return false;
	}
	else if (node->ChildAmount() == 1)
	{
		if (node->rightChild == nullptr)
			return CheckIfRebalanceIsNeeded(node->leftChild);
		else
			return CheckIfRebalanceIsNeeded(node->rightChild);
	}
	else
	{
		int nodeAmount = node->GetNodeAmount();

		if (node->leftChild != nullptr && node->leftChild->GetNodeAmount() > c * nodeAmount)
			return true;
		if (node->rightChild != nullptr && node->rightChild->GetNodeAmount() > c * nodeAmount)
			return true;

		if (CheckIfRebalanceIsNeeded(node->leftChild) == true || CheckIfRebalanceIsNeeded(node->rightChild) == true)
			return true;
		else
			return false;
	}
}





string BSTTree::ToString()
{
	std::ostringstream oss;
	if (head == nullptr)
		return oss.str();

	std::queue<BSTNode*> currentLevel;
	currentLevel.push(head);

	while (!currentLevel.empty())
	{
		std::queue<BSTNode*> nextLevel;

		while (!currentLevel.empty())
		{
			BSTNode* node = currentLevel.front();
			currentLevel.pop();

			if (node != nullptr)
			{
				oss << node->ToString() << " ";
				nextLevel.push(node->leftChild);
				nextLevel.push(node->rightChild);
			}
		}
		oss << "\n";
		currentLevel = nextLevel;
	}

	return oss.str();
}

