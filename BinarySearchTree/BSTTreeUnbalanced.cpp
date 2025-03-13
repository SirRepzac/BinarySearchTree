#include "BSTTreeUnbalanced.h"

BSTTreeUnbalanced::BSTTreeUnbalanced()
{
	head = nullptr;
}

BSTNode* BSTTreeUnbalanced::Find(int key)
{
	return FindAlgo(key, head);
}

BSTNode* BSTTreeUnbalanced::FindAlgo(int key, BSTNode* currentNode)
{
	if (currentNode == nullptr)
		return nullptr;

	if (key == currentNode->key)
		return currentNode;

	return FindAlgo(key, currentNode->GetNextNode(key));
}

void BSTTreeUnbalanced::Insert(int key)
{
	if (head == nullptr)
	{
		BSTNode* newHead = new BSTNode(key);
		head = newHead;
	}
	else
	{
		InsertAlgo(key, head);
	}
}

void BSTTreeUnbalanced::InsertAlgo(int key, BSTNode* currentNode)
{
	if (key == currentNode->key)
	{
		return;
	}

	BSTNode* nextNode = currentNode->GetNextNode(key);

	if (nextNode == nullptr)
	{
		currentNode->SetNewChild(key);

		// Update nodeAmount
		BSTNode* parentNode = currentNode;

		while (parentNode->parent != nullptr)
		{
			parentNode->nodeAmount++;
			parentNode = parentNode->parent;
		}
		// Add to nodeAmount for head
		parentNode->nodeAmount++;
	}
	else
	{
		InsertAlgo(key, nextNode);
	}
}

void BSTTreeUnbalanced::DeleteTree()
{
	vector<BSTNode*> nodes;

	InOrderTraversal(head, nodes);

	for (int i = 0; i < nodes.size(); i++)
	{
		delete nodes[i];
	}

	head = nullptr;
}

void BSTTreeUnbalanced::InOrderTraversal(BSTNode* node, vector<BSTNode*>& nodes)
{
	if (node == nullptr)
		return;

	InOrderTraversal(node->leftChild, nodes);
	nodes.push_back(node);
	InOrderTraversal(node->rightChild, nodes);
}


// NOT IMPORTANT BELOW

void BSTTreeUnbalanced::Delete(int key)
{
	BSTNode* nodeWithKey = Find(key);

	if (nodeWithKey == nullptr)
	{
		return;
	}

	Delete(nodeWithKey);
}

void BSTTreeUnbalanced::Delete(BSTNode* node)
{
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

		BSTNode* parentNode = node->parent;
		while (parentNode->parent != nullptr)
		{
			parentNode->nodeAmount--;
			parentNode = parentNode->parent;
		}
		// Remove from nodeAmount for head
		parentNode->nodeAmount--;

		delete node;
		return;
	}

	// The node being deleted has 1 child, relocate the child to the deleted values position
	else if (node->ChildAmount() == 1)
	{
		BSTNode* child = (node->leftChild != nullptr) ? node->leftChild : node->rightChild;

		if (node == head)
		{
			head = child;
			child->parent = nullptr;
		}
		else
		{
			child->parent = node->parent;
			if (node->parent->leftChild == node)
				node->parent->leftChild = child;
			else
				node->parent->rightChild = child;
		}

		BSTNode* parentNode = node->parent;
		while (parentNode->parent != nullptr)
		{
			parentNode->nodeAmount--;
			parentNode = parentNode->parent;
		}
		// Remove from nodeAmount for head
		parentNode->nodeAmount--;

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