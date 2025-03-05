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

void BSTTree::Insert(int key)
{
	if (head == nullptr)
	{
		BSTNode* newHead = new BSTNode(key);
		head = newHead;
		cout << "Created new head with key: " + to_string(key) << endl;
	}
	else
	{
		InsertAlgo(key, head);
		cout << "-----Insertion complete-----" << endl;
		
	}

	if (CheckIfRebalanceIsNeeded(head))
		Rebalance();
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
		cout << "Going into child " + currentNode->ToString() + "->" + nextNode->ToString() << endl;
		InsertAlgo(key, nextNode);
	}
}

void BSTTree::Delete(int key)
{
	BSTNode* nodeWithKey = Find(key);

	if (nodeWithKey == nullptr)
	{
		cout << "Key not found" << endl;
		return;
	}

	
	Delete(nodeWithKey);
	cout << "----Delete complete----" << endl;

	if (CheckIfRebalanceIsNeeded(head))
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

		cout << "Removing " + node->ToString() << endl;
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
			cout << "Replacing " + node->ToString() + " with child: " + child->ToString() << endl;
		}
		delete node;
		return;
	}
	// The node being deleted has 2 children
	else
	{
		// Swap value with the smallest node in the right subtree
		BSTNode* smallestInRightSubtree = node->rightChild->GetSmallest();
		cout << "Swapping value with " + smallestInRightSubtree->ToString() << endl;
		node->key = smallestInRightSubtree->key;
		Delete(smallestInRightSubtree);
	}
}

bool BSTTree::CheckIfRebalanceIsNeeded(BSTNode* node)
{
	// If node is a leaf (bottom of the tree)
	if (node->IsLeaf())
	{
		return false;
	}
	// If node has children
	else
	{
		int nodeAmount = node->GetNodeAmount();

		if (node->leftChild != nullptr)
		{
			if (node->leftChild->GetNodeAmount() > c * nodeAmount)
			{
				return true;
			}
			if (CheckIfRebalanceIsNeeded(node->leftChild))
			{
				return true;
			}
		}

		if (node->rightChild != nullptr)
		{

			if (node->rightChild->GetNodeAmount() > c * nodeAmount)
			{
				return true;
			}
			if (CheckIfRebalanceIsNeeded(node->rightChild))
			{
				return true;
			}
		}

		return false;
	}
}

void BSTTree::InOrderTraversal(BSTNode* node, vector<BSTNode*>& nodes)
{
	if (node == nullptr)
		return;

	InOrderTraversal(node->leftChild, nodes);
	nodes.push_back(node);
	InOrderTraversal(node->rightChild, nodes);
}


BSTNode* BSTTree::BuildBalancedTree(vector<BSTNode*>& nodes, int start, int end)
{
	if (start > end)
		return nullptr;

	int mid = start + (end - start) / 2;
	BSTNode* node = nodes[mid];

	node->leftChild = BuildBalancedTree(nodes, start, mid - 1);
	if (node->leftChild != nullptr)
		node->leftChild->parent = node;

	node->rightChild = BuildBalancedTree(nodes, mid + 1, end);
	if (node->rightChild != nullptr)
		node->rightChild->parent = node;

	return node;
}

void BSTTree::Rebalance()
{
	cout << "Rebalancing tree..." << endl;
	vector<BSTNode*> nodes;
	// First make an in order traversal to get all the nodes in order
	InOrderTraversal(head, nodes);

	// Then Make the middle of the vector as the head
	// then keep making the middle between start and current node as the left child and the middle between current node and stop as the right child 
	head = BuildBalancedTree(nodes, 0, nodes.size() - 1);
	head->parent = nullptr;
	cout << "----Rebalance complete----" << endl;

}

void BSTTree::InOrderTraversalWithDepth(BSTNode* node, vector<pair<BSTNode*, int>>& nodesWithDepth, int depth)
{
	if (node == nullptr)
		return;

	InOrderTraversalWithDepth(node->leftChild, nodesWithDepth, depth + 1);
	nodesWithDepth.push_back({ node, depth });
	InOrderTraversalWithDepth(node->rightChild, nodesWithDepth, depth + 1);
}

string BSTTree::ToString()
{
	if (head == nullptr)
		return "Tree is empty";

	int depth = head->GetHeight() + 1;
	vector<string> strVec(depth);
	vector<vector<int>> width(depth);
	int maxWidth = 0;

	vector<pair<BSTNode*, int>> nodesWithDepth;
	InOrderTraversalWithDepth(head, nodesWithDepth, 0);

	for (const auto& nodeWithDepth : nodesWithDepth)
	{
		string s = nodeWithDepth.first->ToString();
		strVec[nodeWithDepth.second] += s + " ";
		width[nodeWithDepth.second].push_back(s.length());
		if (s.length() > maxWidth)
			maxWidth = s.length();
	}

	string str = "";

	for (int i = 0; i < strVec.size(); i++)
	{
		str += "\n";

		str += strVec[i];
	}

	return str;
}

