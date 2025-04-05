#include <bits/stdc++.h>
using namespace std;

// Concept - Divide and Qonqure
// Divide array into 2 subarray's recursively until you can no longer divide them
// combine the solution's of sub array's to obtain original array's answer.

//Ex for arr of length 9:

// Segment Tree Visualization:
//                                [0..8]
//                               /      \
//                           [0..4]    [5..8]
//                          /   \       /   \
//                     [0..2] [3..4] [5..6] [7..8]
//                     /  \    /  \   /  \   /  \
//                  [0..1] 2   3   4  5   6  7   8
//                 /   \
//                0     1


int fillTree(int arr[], vector<int> &segmentTree, int node, int size, int index){
	if (node >= size) {
		segmentTree[index] = arr[node];
		return arr[node];
	}
	int left = fillTree(arr, segmentTree, node, node + (size - node) / 2, 2 * index + 1);
	int right = fillTree(arr, segmentTree, node + (size - node) / 2 + 1, size, 2 * index + 2);
	segmentTree[index] = max(left, right);
	return segmentTree[index];
}

void display(vector<int> &segmentTree, int root){
	if (root >= 32 || segmentTree[root] == 0){
	 cout << "None" << " ";
	 return;
	 }
	cout << segmentTree[root] << " ";
	display(segmentTree, root * 2 + 1);
	display(segmentTree, root * 2 + 2);
}

int getMax(pair<int, int> intervel, int start, int end, int root, vector<int> &segmentTree){
	if (start > intervel.second || end < intervel.first) return 0;
	if (start >= intervel.first && end <= intervel.second) return segmentTree[root];
	int mid = start + (end - start) / 2;
	return max(getMax(intervel, start, mid, root * 2 + 1, segmentTree), getMax(intervel, mid + 1, end, root * 2 + 2, segmentTree));
}

//int getMax(int element, int start, int end, int root, vector<int> segmentTree){

//  The function aim's to find number of element's greater than given element

//	This function is incomplete but it is easy to implement. just traverse left and right until 
//  end is reached or a minimum element is reached, this requires a pair<int, int> as element 
//  of segment tree because if the array contain's duplicates we don't wan't the algorithm to 
//	fail so we store value and frequency together.
//}

// There is also a update opetation called lazy propagation also if the lazy propagation is for range updations else just update normally.

int main(){
	int arr[] = {1, 4, 3, 20, 30, 6, 5, 4}, size = 8;
	vector<int> segmentTree(size * 4, 0);
	fillTree(arr, segmentTree, 0, size - 1, 0);
	cout << "Traversal" << endl;
	display(segmentTree, 0);
	cout << endl << "OP: " << endl;
	cout << getMax({5, 7}, 0, 7, 0, segmentTree) << endl;;
}
