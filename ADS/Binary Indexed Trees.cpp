#include <bits/stdc++.h>
using namespace std;

// Binary Indexed Tree is a tree that is used instead of segment tree
// we use binary index's to update, compute, build the tree.

// BUILD - General

// while filling the tree if we are at index 4 --> 0100
// we need to filp the last set bit [filped] 4 --> 0000
// now we add 1 to the obtained index till we reach 4 - at the same time update the current value
// with the element present in the fliped index of array.
//// we asume index start's from one here we minus here
// tree[3] += arr[1] i.e. tree[index - 1] += tree[fliped - 1] --> fliped = fliped + 1
// tree[3] += tree[2]
// tree[3] += tree[3] end here

// Time complexity O(nlogn)

void fillTree(const int arr[], const int &size, vector<int> &tree)
{
	int index, flip;
	for (int i = 0; i < size; i++)
	{
		index = i + 1;
		flip = index - (index & -index);
		while (flip++ != index)
		{
			tree[i] += arr[flip - 1];
		}
	}
}

// BUILD - Optimal

// If you observed closely while building tree from 1 --> n
// we can use this formula for construction in O(n)

// tree[index - 1] += arr[index - 1]
// add right most set bit of index to index
// prev = index
// index += index & -index why? just see previous computation you will understand why.
// tree[index] += tree[prev]

void fillTreeOptimal(const int arr[], const int &size, vector<int> &tree)
{
	int index;
	for (int i = 0; i < size; i++)
	{
		index = i + 1;
		tree[i] += arr[i];
		if (index + (index & -index) - 1 < size)
			tree[index + (index & -index) - 1] += tree[i];
	}
}

// UPDATE

// This is same as insert just add the value to all the effected nodes
// how do you compute the effected nodes?
// just add the left set bit to index. that's it.

void updateTree(int index, int add, vector<int> &tree)
{
	int treeIndex = index + 1;
	while (treeIndex <= tree.size())
	{
		tree[treeIndex - 1] += add;
		treeIndex += treeIndex & -treeIndex;
	}
}

// SUM Of N
// for Nth node you have sum of distance between right most set bit to the end elements
// what you lack is the sum of n - n & -n nodes.

int sumOfN(const vector<int> &tree, int n)
{
	int s = 0;
	while (n)
	{
		s += tree[n - 1];
		n -= n & -n;
	}
	return s;
}

ostream &operator<<(ostream &stream, const vector<int> &tree)
{
	stream << "{ ";
	for (int i : tree)
	{
		stream << i << " ";
	}
	stream << "}";
	return stream;
}

int main()
{
	int arr[] = {2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9}, size = sizeof(arr) / sizeof(int);
	vector<int> binaryIndexedTree(size, 0);
	//	fillTree(arr, size, binaryIndexedTree);
	fillTreeOptimal(arr, size, binaryIndexedTree);
	cout << binaryIndexedTree << endl;
	cout << "After adding 3 for '2' at index 0: ";
	updateTree(0, 3, binaryIndexedTree);
	cout << binaryIndexedTree << endl;
	cout << "Sum of first 5 Nodes: " << sumOfN(binaryIndexedTree, 5) << endl;
}
