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

	if (key == currentNode->key)
		return currentNode;

	return FindAlgo(key, currentNode->GetNextNode(key));
}

void BSTTree::Insert(int value)
{
	BSTNode* unbalancedNode = nullptr;
	head = InsertAndTrack(head, value, unbalancedNode);
	
	if (unbalancedNode)
	{
		RebalanceAt(unbalancedNode);
	}
}

BSTNode* BSTTree::InsertAndTrack(BSTNode* node, int key, BSTNode*& unbalancedNode)
{
	if (!node) return new BSTNode(key);

	if (key < node->key)
	{
		node->leftChild = InsertAndTrack(node->leftChild, key, unbalancedNode);
		node->leftChild->parent = node;
	}
	else
	{
		node->rightChild = InsertAndTrack(node->rightChild, key, unbalancedNode);
		node->rightChild->parent = node;
	}

	// Update nodeAmount during insertion
	node->nodeAmount = 1 + (node->leftChild ? node->leftChild->nodeAmount : 0)
		+ (node->rightChild ? node->rightChild->nodeAmount : 0);

	// Check balance factor **only once per insert**
	int balanceFactor = GetBalanceFactor(node);
	if (abs(balanceFactor) > 1 && !unbalancedNode)
	{
		unbalancedNode = node;  // Store first unbalanced node
	}

	return node;
}

double BSTTree::GetBalanceFactor(BSTNode* node)
{
	if (!node) return 0.0; // Null nodes are balanced

	int leftSize = node->leftChild ? node->leftChild->nodeAmount : 0;
	int rightSize = node->rightChild ? node->rightChild->nodeAmount : 0;
	int totalSize = node->nodeAmount; // Includes the node itself

	if (totalSize <= 1) return 0.0; // A single node is always balanced

	double leftRatio = static_cast<double>(leftSize) / totalSize;
	double rightRatio = static_cast<double>(rightSize) / totalSize;

	return std::max(leftRatio, rightRatio); // Max ratio determines balance
}

bool BSTTree::CheckIfRebalanceIsNeeded(BSTNode* node)
{
	if (!node) return false;
	return GetBalanceFactor(node) > c;
}

void BSTTree::RebalanceAt(BSTNode* node)
{
	if (!node) return;

	int balanceFactor = GetBalanceFactor(node);

	// LL Case (Right Rotation)
	if (balanceFactor > 1 && GetBalanceFactor(node->leftChild) >= 0)
	{
		node = RotateRight(node);
	}
	// RR Case (Left Rotation)
	else if (balanceFactor < -1 && GetBalanceFactor(node->rightChild) <= 0)
	{
		node = RotateLeft(node);
	}
	// LR Case (Left-Right Rotation)
	else if (balanceFactor > 1 && GetBalanceFactor(node->leftChild) < 0)
	{
		node->leftChild = RotateLeft(node->leftChild);
		node = RotateRight(node);
	}
	// RL Case (Right-Left Rotation)
	else if (balanceFactor < -1 && GetBalanceFactor(node->rightChild) > 0)
	{
		node->rightChild = RotateRight(node->rightChild);
		node = RotateLeft(node);
	}

	// If the node was root, update head
	if (!node->parent)
	{
		head = node;
	}
}

void BSTTree::DeleteTree()
{
	vector<BSTNode*> nodes;

	InOrderTraversal(head, nodes);

	for (int i = 0; i < nodes.size(); i++)
	{
		delete nodes[i];
	}

	head = nullptr;
}

void BSTTree::InOrderTraversal(BSTNode* node, vector<BSTNode*>& nodes)
{
	if (node == nullptr)
		return;

	InOrderTraversal(node->leftChild, nodes);
	nodes.push_back(node);
	InOrderTraversal(node->rightChild, nodes);
}

BSTNode* BSTTree::RotateRight(BSTNode* node)
{
	BSTNode* newRoot = node->leftChild;
	node->leftChild = newRoot->rightChild;

	if (newRoot->rightChild)
	{
		newRoot->rightChild->parent = node;
	}

	newRoot->rightChild = node;
	newRoot->parent = node->parent;
	node->parent = newRoot;

	// Fix parent's child reference
	if (newRoot->parent)
	{
		if (newRoot->parent->leftChild == node)
		{
			newRoot->parent->leftChild = newRoot;
		}
		else
		{
			newRoot->parent->rightChild = newRoot;
		}
	}

	// Update nodeAmount
	UpdateNodeAmount(node);
	UpdateNodeAmount(newRoot);

	return newRoot;
}

BSTNode* BSTTree::RotateLeft(BSTNode* node)
{
	BSTNode* newRoot = node->rightChild;
	node->rightChild = newRoot->leftChild;

	if (newRoot->leftChild)
	{
		newRoot->leftChild->parent = node;
	}

	newRoot->leftChild = node;
	newRoot->parent = node->parent;
	node->parent = newRoot;

	// Fix parent's child reference
	if (newRoot->parent)
	{
		if (newRoot->parent->leftChild == node)
		{
			newRoot->parent->leftChild = newRoot;
		}
		else
		{
			newRoot->parent->rightChild = newRoot;
		}
	}

	// Update nodeAmount
	UpdateNodeAmount(node);
	UpdateNodeAmount(newRoot);

	return newRoot;
}

BSTNode* BSTTree::RotateLeftRight(BSTNode* node)
{
	node->leftChild = RotateLeft(node->leftChild);
	return RotateRight(node);
}

BSTNode* BSTTree::RotateRightLeft(BSTNode* node)
{
	node->rightChild = RotateRight(node->rightChild);
	return RotateLeft(node);
}

void BSTTree::UpdateNodeAmount(BSTNode* node)
{
	if (!node) return;
	node->nodeAmount = 1; // Count itself
	if (node->leftChild)
	{
		node->nodeAmount += node->leftChild->nodeAmount;
	}
	if (node->rightChild)
	{
		node->nodeAmount += node->rightChild->nodeAmount;
	}
}

// NOT IMPORTANT BELOW

BSTNode* BSTTree::FindUnbalancedNode(BSTNode* node)
{
	if (node == nullptr) return nullptr;

	int leftSize = (node->leftChild) ? node->leftChild->nodeAmount : 0;
	int rightSize = (node->rightChild) ? node->rightChild->nodeAmount : 0;

	if (leftSize > c * node->nodeAmount || rightSize > c * node->nodeAmount)
	{
		return node;
	}

	BSTNode* leftUnbalanced = FindUnbalancedNode(node->leftChild);

	if (leftUnbalanced)
		return leftUnbalanced;

	return FindUnbalancedNode(node->rightChild);
}

void BSTTree::Rebalance()
{
	BSTNode* unbalancedNode = FindUnbalancedNode(head);
	if (!unbalancedNode) return; // No need to rebalance

	int leftSize = (unbalancedNode->leftChild) ? unbalancedNode->leftChild->nodeAmount : 0;
	int rightSize = (unbalancedNode->rightChild) ? unbalancedNode->rightChild->nodeAmount : 0;
	int balanceFactor = leftSize - rightSize;

	// LL Case (Left-heavy)
	if (balanceFactor > 1)
	{
		if (unbalancedNode->leftChild && unbalancedNode->leftChild->leftChild)
		{
			unbalancedNode = RotateRight(unbalancedNode);
		}
		else
		{
			unbalancedNode = RotateLeftRight(unbalancedNode);
		}
	}
	// RR Case (Right-heavy)
	else if (balanceFactor < -1)
	{
		if (unbalancedNode->rightChild && unbalancedNode->rightChild->rightChild)
		{
			unbalancedNode = RotateLeft(unbalancedNode);
		}
		else
		{
			unbalancedNode = RotateRightLeft(unbalancedNode);
		}
	}

	// Update root if necessary
	if (!unbalancedNode->parent)
	{
		head = unbalancedNode;
	}
}

void BSTTree::Delete(int key)
{
	BSTNode* nodeWithKey = Find(key);

	if (nodeWithKey == nullptr)
	{
		return;
	}

	Delete(nodeWithKey);


	Rebalance();
}

void BSTTree::Delete(BSTNode* node)
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


