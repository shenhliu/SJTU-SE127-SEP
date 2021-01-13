#include <cmath>

class TreeNode
{
    friend class BinaryDimonTree;

private:
    int x;
    int y;
    int layer;
    TreeNode *right;
    TreeNode *left;

public:
    TreeNode(int X = 0, int Y = 0, int layer = 1) : x(X), y(Y), layer(layer), right(NULL), left(NULL){};
    int getX() { return x; };
    int getY() { return y; };
};

class BinaryDimonTree
{
private:
    TreeNode *root;

public:
    TreeNode *guess;
    double bestDist;
    BinaryDimonTree() : root(NULL){};
    ~BinaryDimonTree();
    void insert(int x, int y);
    double distance(TreeNode &a, TreeNode &b);
    void clear(TreeNode *&t);
    TreeNode *find_nearest_node(int x, int y);
    void findnearestnode(TreeNode *goal, TreeNode *curr);
    bool cmp(TreeNode &a, TreeNode &b);
    double VerticalDistance(TreeNode &a, TreeNode &b);
};

BinaryDimonTree::~BinaryDimonTree()
{
    clear(root);
}

void BinaryDimonTree::clear(TreeNode *&t)
{
    if (t == NULL)
        return;
    clear(t->left);
    clear(t->right);
    delete t;
    t == NULL;
}

void BinaryDimonTree::insert(int x, int y)
{
    TreeNode N(x, y);
    TreeNode *tmp = root;
    TreeNode *tmpp = root;
    int n = 1;
    if (root == NULL)
    {
        root = new TreeNode(x, y);
        return;
    }
    while (tmp != NULL)
    {
        tmpp = tmp;
        if (n % 2 == 1)
        {
            if (N.getX() < tmp->x)
                tmp = tmp->left;
            else
                tmp = tmp->right;
        }
        else
        {
            if (N.getY() < tmp->y)
                tmp = tmp->left;
            else
                tmp = tmp->right;
        }
        n++;
    }
    if ((n - 1) % 2)
    {
        if (N.getX() < tmpp->x)
            tmpp->left = new TreeNode(x, y, n);
        else
            tmpp->right = new TreeNode(x, y, n);
    }
    else
    {
        if (N.getY() < tmpp->y)
            tmpp->left = new TreeNode(x, y, n);
        else
            tmpp->right = new TreeNode(x, y, n);
    }
}

//下面是求最短距离的各个函数
double BinaryDimonTree::distance(TreeNode &a, TreeNode &b)
{
    double x = (a.getX() - b.getX()) * (a.getX() - b.getX()) + (a.getY() - b.getY()) * (a.getY() - b.getY());
    return sqrt(x);
}

bool BinaryDimonTree::cmp(TreeNode &a, TreeNode &b)
{
    if (b.layer % 2 == 1)
    {
        if (a.x < b.x)
            return 1;
        else
        {
            return 0;
        }
    }
    else
    {
        if (a.y < b.y)
            return 1;
        else
            return 0;
    }
}

double BinaryDimonTree::VerticalDistance(TreeNode &a, TreeNode &b)
{
    if (b.layer % 2)
        return abs(a.getX() - b.getX());
    else
        return abs(a.getY() - b.getY());
}

TreeNode *BinaryDimonTree::find_nearest_node(int x, int y)
{
    TreeNode *goal = new TreeNode(x, y);
    bestDist = 1.6E308;
    guess = NULL;
    findnearestnode(goal, root);
    return guess;
}

void BinaryDimonTree::findnearestnode(TreeNode *goal, TreeNode *curr)
{
    if (curr == NULL || bestDist == 0)
        return;
    double dis = distance(*goal, *curr);
    if (dis <= bestDist)
    {
        bestDist = dis;
        guess = curr;
    }
    if (cmp(*goal, *curr))
    {
        findnearestnode(goal, curr->left);
    }

    else
        findnearestnode(goal, curr->right);

    if (VerticalDistance(*goal, *curr) < bestDist)
        findnearestnode(goal, curr->right);

    if (VerticalDistance(*goal, *curr) < bestDist)
    {
        if (cmp(*goal, *curr))
            findnearestnode(goal, curr->right);
        else
            findnearestnode(goal, curr->left);
    }
}
