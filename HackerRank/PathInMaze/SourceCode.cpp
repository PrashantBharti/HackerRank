// Solution for below link
// https://www.hackerrank.com/challenges/count-luck

#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>
#include <utility>
using namespace std;

typedef vector<string> MATRIX;
typedef pair<size_t, size_t> POSITION;
typedef stack<POSITION> STACKPOSITION;
typedef map<POSITION, bool> HASHMAP;
typedef vector<POSITION> PATH;

PATH CopyPath(PATH path, PATH pathToCopy)
{
for(POSITION pos : pathToCopy)
	path.push_back(pos);

return path;
}

bool TestTheMatrix(MATRIX matrix, size_t matRows, size_t matCols, POSITION &posStart, POSITION &posEnd, PATH &path, size_t &nbSplitPaths, HASHMAP &hashmap)
{
if(posStart == posEnd)
	{
	path.push_back(posEnd);
	return true;
	}

size_t nbChecks = 0;

bool bIsPathUp = false;
size_t nbSplitPathsUp = 0;
PATH pathUp;

bool bIsPathDown = false;
size_t nbSplitPathsDown = 0;
PATH pathDown;

bool bIsPathRight = false;
size_t nbSplitPathsRight = 0;
PATH pathRight;

bool bIsPathLeft = false;
size_t nbSplitPathsLeft = 0;
PATH pathLeft;

hashmap[posStart] = true;

// Check Up
if(posStart.first - 1 < matRows && matrix[posStart.first-1][posStart.second] != 'X' && !hashmap[POSITION(posStart.first-1, posStart.second)])
	{
	nbChecks++;
	POSITION posUp = POSITION(posStart.first - 1, posStart.second);
	bIsPathUp = TestTheMatrix(matrix, matRows, matCols, posUp, posEnd, pathUp, nbSplitPathsUp, hashmap);
	}

// Check Down
if(posStart.first + 1 < matRows && matrix[posStart.first + 1][posStart.second] != 'X' && !hashmap[POSITION(posStart.first + 1, posStart.second)])
	{
	nbChecks++;
	POSITION posDown = POSITION(posStart.first + 1, posStart.second);
	bIsPathDown = TestTheMatrix(matrix, matRows, matCols, posDown, posEnd, pathDown, nbSplitPathsDown, hashmap);
	}

// Check Left
if(posStart.second - 1 < matCols && matrix[posStart.first][posStart.second - 1] != 'X' && !hashmap[POSITION(posStart.first, posStart.second - 1)])
	{
	nbChecks++;
	POSITION posLeft = POSITION(posStart.first, posStart.second - 1);
	bIsPathLeft = TestTheMatrix(matrix, matRows, matCols, posLeft, posEnd, pathLeft, nbSplitPathsLeft, hashmap);
	}

// Check Right
if(posStart.second + 1 < matCols && matrix[posStart.first][posStart.second + 1] != 'X' && !hashmap[POSITION(posStart.first, posStart.second + 1)])
	{
	nbChecks++;
	POSITION posRight = POSITION(posStart.first, posStart.second + 1);
	bIsPathRight = TestTheMatrix(matrix, matRows, matCols, posRight, posEnd, pathRight, nbSplitPathsRight, hashmap);
	}

if(bIsPathUp)
	{
	nbSplitPaths += (nbChecks > 1 ? 1 : 0);
	nbSplitPaths += nbSplitPathsUp;
	path.push_back(posStart);
	path = CopyPath(path, pathUp);
	return true;
	}

if(bIsPathDown)
	{
	nbSplitPaths += (nbChecks > 1 ? 1 : 0);
	nbSplitPaths += nbSplitPathsDown;
	path.push_back(posStart);
	path = CopyPath(path, pathDown);
	return true;
	}

if(bIsPathLeft)
	{
	nbSplitPaths += (nbChecks > 1 ? 1 : 0);
	nbSplitPaths += nbSplitPathsLeft;
	path.push_back(posStart);
	path = CopyPath(path, pathLeft);
	return true;
	}

if(bIsPathRight)
	{
	nbSplitPaths += (nbChecks > 1 ? 1 : 0);
	nbSplitPaths += nbSplitPathsRight;
	path.push_back(posStart);
	path = CopyPath(path, pathRight);
	return true;
	}

return false;
}

int main(int argc, char* argv[])
{
size_t nbTest = 0;
cin >> nbTest;

for(size_t i = 0; i < nbTest; ++i)
	{
	size_t matRows = 0, matCols = 0;
	cin >> matRows >> matCols;
	cin.ignore();

	MATRIX matrix;
	POSITION posStart;
	POSITION posEnd;

	for(size_t row = 0; row < matRows; ++row)
		{
		string strInput;
		for(size_t col = 0; col < matCols; ++col)
			{
			char val = cin.get();
			if(val == 'M')
				posStart.first = row, posStart.second = col;

			if(val == '*')
				posEnd.first = row, posEnd.second = col;

			strInput += val;
			}

		matrix.push_back(strInput);
		cin.ignore();
		}

	size_t testNbSplitPaths = 0;
	cin >> testNbSplitPaths;

	PATH pathToEnd;
	size_t nbSplitPaths = 0;
	HASHMAP hashmap;
	bool bHasPath = TestTheMatrix(matrix, matRows, matCols, posStart, posEnd, pathToEnd, nbSplitPaths, hashmap);

	if(bHasPath && nbSplitPaths == testNbSplitPaths)
		cout << "Impressed" << endl;
	else
		cout << "Oops!" << endl;
	}

return 0;
}