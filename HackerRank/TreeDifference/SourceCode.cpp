// Solution for below link
// https://www.hackerrank.com/challenges/cut-the-tree

#include <iostream>
#include <climits>
#include <cmath>
#include <vector>
#include <utility>
using namespace std;

typedef int WEIGHT;
typedef vector<WEIGHT> WEIGHTLIST;
typedef pair<int, int> EDGE;
typedef pair<int, int> NODESUM;
typedef vector<EDGE> EDGELIST;
typedef vector<NODESUM> NODELIST;
typedef vector<NODELIST> TREE;

int GetSubTreeSum(TREE &tree, WEIGHTLIST &weightlist, int node1, int node2)
{
WEIGHT weightsum = weightlist[node1];

for(NODESUM &nodesum : tree[node1])
	{
	if(nodesum.first == node2)
		continue;

	int sum = 0;
	if(nodesum.second == 0)
		{
		sum = GetSubTreeSum(tree, weightlist, nodesum.first, node1);
		nodesum.second = sum;
		}
	else
		sum = nodesum.second;

	weightsum += sum;
	}

return weightsum;
}

int main(int argc, char* argv[])
{
size_t nbNodes = 0;
cin >> nbNodes;

WEIGHTLIST weightlist(nbNodes);
for(unsigned int i = 0; i < nbNodes; ++i)
	cin >> weightlist[i];

EDGELIST edgelist;
TREE tree(nbNodes);
for(unsigned int i = 0; i < nbNodes - 1; ++i)
	{
	int node1, node2;
	cin >> node1 >> node2;
	EDGE edge(node1 - 1, node2 - 1);
	edgelist.push_back(edge);
	NODESUM nodesum1(node1 - 1, 0);
	NODESUM nodesum2(node2 - 1, 0);
	tree[node1 - 1].push_back(nodesum2);
	tree[node2 - 1].push_back(nodesum1);
	}

WEIGHT weightdiff = INT_MAX;
for(EDGE &edge : edgelist)
	{
	int node1 = edge.first;
	int node2 = edge.second;

	int sum1 = GetSubTreeSum(tree, weightlist, node1, node2);
	int sum2 = GetSubTreeSum(tree, weightlist, node2, node1);

	weightdiff = min(weightdiff, abs(sum1 - sum2));
	}

cout << weightdiff;
return 0;
}