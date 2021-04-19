#include <rlib/stdio.hpp>
using namespace rlib::literals;

using std::cout;
using rlib::endl;
using rlib::println;

constexpr int n = 5;
#define rootFlag 0
#define leftFlag 1
#define rightFlag 2

int root[n+1][n+1] = 
{ 
	0, 0, 0, 0, 0, 0,
	0, 1, 1, 2, 2, 2,
	0, 0, 2, 2, 2, 4,
	0, 0, 0, 3, 4, 5,
	0, 0, 0, 0, 4, 5,
	0, 0, 0, 0, 0, 5,
};

void BST(int root[n+1][n+1],int i, int j, int flag){

	if (i <= j){
		if (flag == rootFlag)
			println("k{} is root."_format(root[i][j]));
		else if (flag == leftFlag)
			println("k{} is k{}'s left child."_format(root[i][j], j+1));
		else
			println("k{} is k{}'s right child."_format(root[i][j], i-1));
		BST(root,i, root[i][j] - 1, leftFlag);
		BST(root,root[i][j] + 1, j, rightFlag);
	}
	else if (j == (i-1))
	{
		if (flag == leftFlag)
			println("d{} is k{}'s left child."_format(j, j+1));
		else if (flag == rightFlag)
			println("d{} is k{}'s right child."_format(j, i-1));
	}
}

int main()
{
	BST(root,1, 5, rootFlag);
}
