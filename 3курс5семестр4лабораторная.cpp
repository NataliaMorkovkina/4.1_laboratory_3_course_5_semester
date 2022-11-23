#include <iostream>
#include <vector>

class TreeNode
{
public:
    double data = 0;
    TreeNode* left = NULL;
    TreeNode* right = NULL;
};

TreeNode* add(double _data, TreeNode* tree)
{
    if (tree == NULL)
    {
        tree = new TreeNode;
        tree->data = _data;
        return tree;
    }

    if (_data < tree->data)
        tree->left = add(_data, tree->left);
    else
        tree->right = add(_data, tree->right);
    return tree;
}

void remove(double _data, TreeNode* tree)
{
    if (tree == NULL)
        return;

    if (_data == tree->data)
        delete tree;
    else if (_data < tree->data)
        remove(_data, tree->left);
    else
        remove(_data, tree->right);
}

void print(std::vector<TreeNode*> last)
{
    std::vector<TreeNode*> next;
    for (TreeNode* tree : last)
    {
        if (tree != NULL)
        {
            std::cout << tree->data << ' ';
            next.push_back(tree->left);
            next.push_back(tree->right);
        }
    }
    std::cout << '\n';
    if (next.size())
        print(next);
}

void print(TreeNode* tree)
{
    if (tree == NULL)
        return;

    std::vector<TreeNode*> trees;
    trees.push_back(tree);
    print(trees);
}

bool searchData(double _data, TreeNode* tree)
{
    if (tree == NULL)
        return false;

    if (_data == tree->data)
        return true;

    if (_data < tree->data)
        return searchData(_data, tree->left);

    return searchData(_data, tree->right);
}

std::pair<bool, double> searchBigger(double _data, TreeNode* tree)
{
    if (tree == NULL)
        return std::pair<bool, double>(false, 0);

    if (_data <= tree->data)
        if (tree->right != NULL)
            return searchBigger(_data, tree->right);
        else
            return std::pair<bool, double>(false, 0);
    if (tree->left != NULL)
        return searchBigger(_data, tree->left);
    return std::pair<bool, double>(true, tree->data);
}

std::pair<bool, double> searchLesser(double _data, TreeNode* tree)
{
    if (tree == NULL)
        return std::pair<bool, double>(false, 0);

    if (_data <= tree->data)
        if (tree->left != NULL)
            return searchLesser(_data, tree->left);
        else
            return std::pair<bool, double>(false, 0);
    if (tree->right != NULL)
        return searchLesser(_data, tree->right);
    return std::pair<bool, double>(true, tree->data);
}

std::pair<bool, double> min(TreeNode* tree)
{
    if (tree == NULL)
        return std::pair<bool, double>(false, 0);
    while (tree->left != NULL)
        tree = tree->left;

    return std::pair<bool, double>(true, tree->data);
}

std::pair<bool, double> max(TreeNode* tree)
{
    if (tree == NULL)
        return std::pair<bool, double>(false, 0);
    while (tree->left != NULL)
        tree = tree->right;

    return std::pair<bool, double>(true, tree->data);
}

int main()
{
    TreeNode* root = NULL;
    root = add(4, root);
    root = add(6, root);
    root = add(7, root);
    root = add(2, root);
    root = add(3, root);
    root = add(1, root);
    root = add(5, root);
    print(root);

    if (searchData(-1, root))
        std::cout << "false\n";
    else
        std::cout << "true\n";

    if (searchData(5, root))
        std::cout << "true\n";
    else
        std::cout << "false\n";

    std::pair<bool, double> res;
    res = searchLesser(6, root);
    if (res.first)
        std::cout << "true " << res.second << '\n';
    else
        std::cout << "false\n";

    res = searchLesser(-1, root);
    if (res.first)
        std::cout << "false\n";
    else
        std::cout << "true\n";

    res = searchBigger(-1, root);


    res = searchLesser(11, root);
    if (res.first)
        std::cout << "true " << res.second << '\n';
    else
        std::cout << "false\n";

    res = min(root);
    if (res.first)
        std::cout << "true " << res.second << "\n";
    else
        std::cout << "false\n";
    print(root);

    res = max(root);
    if (res.first)
        std::cout << "true " << res.second << "\n";
    else
        std::cout << "false\n";
    print(root);

    return 0;
}