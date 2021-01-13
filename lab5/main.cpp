#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "Tree.h"

using namespace std;

void run_testcase(string testcasename)
{
    ifstream testcase;
    testcase.open(testcasename);
    int treeNodeNum;
    testcase >> treeNodeNum;

    BinaryDimonTree tree;
    for (int i = 0; i < treeNodeNum; i++)
    {
        int x, y;
        testcase >> x;
        testcase >> y;
        tree.insert(x, y);
    }

    int testNum;
    testcase >> testNum;
    for (int i = 0; i < testNum; i++)
    {
        int x, y, z, w;
        testcase >> x;
        testcase >> y;
        testcase >> z;
        testcase >> w;
        TreeNode *node = tree.find_nearest_node(x, y);

        if (z == node->getX() && w == node->getY())
        {
            cout << "The " << i << " test case Success." << endl;
        }
        else
        {
            //cout << node->getX() << node->getY();
            cout << "The " << i << " test case Wrong." << endl;
        }
    }

    testcase.close();
}

int main()
{
    cout << "The first group of test cases' results." << endl;
    run_testcase("1.txt");

    cout << endl;
    cout << "The second group of test cases' results." << endl;
    run_testcase("2.txt");

    return 0;
}