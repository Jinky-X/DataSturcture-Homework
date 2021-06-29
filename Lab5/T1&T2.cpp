#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <queue>

using namespace std;

template<class T>
struct node
{
    T data;
    node<T> *lChild, *rChild;
};

template<class T>
class biTree
{
    node<T> *root;

    void duoOrder(T pre[], T in[], int l, node<T> *&bt)
    {
        if (l == 1)
        {
            bt = new node<T>;
            bt->lChild = bt->rChild = nullptr;
            bt->data = pre[0];
            return;
        }
        if (l < 1) throw invalid_argument("Invalid tree");
        bt = new node<T>;
        bt->data = pre[0];
        int i;
        for (i = 0; i < l && in[i] != pre[0]; ++i)
        {}
        if (in[i] == pre[0])
        {
            duoOrder(pre + 1, in, i, bt->lChild);
            duoOrder(pre + i + 1, in + i + 1, l - i - 1, bt->rChild);
        } else throw invalid_argument("Invalid tree");
    }

    int countNode(node<T> *bt)
    {
        if (!bt) return 0;
        else return countNode(bt->lChild) + countNode(bt->rChild) + 1;
    }

    int countLeave(node<T> *bt)
    {
        if (!bt->lChild && !bt->rChild) return 1;
        return countLeave(bt->lChild) + countLeave(bt->rChild);
    }

    int countLevel(node<T> *bt)
    {
        if (!bt) return 0;
        return max(countLevel(bt->lChild), countLevel(bt->rChild)) + 1;
    }

    node<T> *findNode(T tgt, node<T> *bt)
    {
        if (!bt) return nullptr;
        if (bt->data == tgt) return bt;
        node<T> *t1 = findNode(tgt, bt->lChild), *t2 = findNode(tgt, bt->rChild);
        if (t2) return t2;
        if (t1) return t1;
        return nullptr;
    }

    int findLevel(T tgt, node<T> *bt)
    {
        if (!bt) return 0;
        if (bt->data == tgt) return 1;
        int t1 = findLevel(tgt, bt->lChild), t2 = findLevel(tgt, bt->rChild);
        if (t2) return t2 + 1;
        if (t1) return t1 + 1;
        return 0;
    }

    node<T> *findParent(T tgt, node<T> *bt)
    {
        if (!bt->lChild || !bt->rChild) return nullptr;
        if (bt->lChild->data == tgt || bt->rChild->data == tgt)
            return bt;
        node<T> *t1 = findParent(tgt, bt->lChild), *t2 = findParent(tgt, bt->rChild);
        if (t2) return t2;
        if (t1) return t1;
        return nullptr;
    }

    node<T> *findNode(T tgt)
    {
        return findNode(tgt, root);
    }

    node<T> *findParent(T tgt)
    {
        return findParent(tgt, root);
    }

    void preOrder_expanded(node<T> *bt)
    {
        if (!bt)
        {
            cout << "NULL" << endl;
            return;
        }
        cout << bt->data << endl;
        preOrder_expanded(bt->lChild);
        preOrder_expanded(bt->rChild);
    }

    void copy(node<T> *&bt, node<T> *ori)
    {
        bt = ori;
        if (ori)
        {
            copy(bt->lChild, ori->lChild);
            copy(bt->rChild, ori->rChild);
        }
    }

    void preOrder(node<T> *bt)
    {
        if (!bt) return;
        cout << bt->data << endl;
        preOrder(bt->lChild);
        preOrder(bt->rChild);
    }

    void inOrder(node<T> *bt)
    {
        if (!bt) return;
        inOrder(bt->lChild);
        cout << bt->data << endl;
        inOrder(bt->rChild);
    }

    void postOrder(node<T> *bt)
    {
        if (!bt) return;
        postOrder(bt->lChild);
        postOrder(bt->rChild);
        cout << bt->data << endl;
    }

public:
      biTree(T post[], int l, T signal) //using post-order of an expanded biTree and signal as empty bt
    {
        if (!l)
        {
            root = nullptr;
            return;
        }
        node<T> *stc[l], *curr;
        int top = -1, i = 0;
        while (i < l)
        {
            if (post[i] == signal)
            {
                stc[++top] = nullptr;
            } else
            {
                curr = new node<T>;
                curr->data = post[i];
                if (top < 1)
                    throw invalid_argument("Invalid tree");
                curr->rChild = stc[top--];
                curr->lChild = stc[top--];
                stc[++top] = curr;
            }
            i++;
        }
        if (top != 0)
            throw invalid_argument("Invalid tree");
        root = stc[0];
    }

    biTree()
    {
        root = nullptr;
    }

    biTree(T pre[], T in[], int l)
    {
        duoOrder(pre, in, l, root);
    }

    biTree(const biTree<T> &a)
    {
        copy(root, a.root);
    }

    biTree<T> &operator=(const biTree<T> &a)
    {
        if (&a != this)
            copy(this->root, a.root);
        return *this;
    }

    int countNode()
    {
        return countNode(root);
    }

    int countLeave()
    {
        return countLeave(root);
    }

    int countLevel()
    {
        return countLevel(root);
    }

    int findLevel(T tgt)
    {
        return findLevel(tgt, root);
    }

    void info(T tgt)
    {
        int level = findLevel(tgt);
        if (level)
        {
            cout << "Target info:\nLevel: " << level;
            node<T> *left = findNode(tgt)->lChild, *right = findNode(tgt)->rChild, *parent = findParent(tgt);
            if (parent)
                cout << "\nParent data: " << parent->data;
            else
                cout << "\nParent doesn't exist!";
            if (left)
                cout << "\nLeft Child data: " << left->data;
            else
                cout << "\nLeft Child doesn't exist!";
            if (right)
                cout << "\nRight Child data: " << right->data;
            else
                cout << "\nRight Child doesn't exist!";

        } else cout << "\nTarget doesn't exist!";

        cout << "\nTree info:\nNode: " << countNode() << "\nLevel: " << countLevel() << "\nLeave: " << countLeave()
             << endl;
    }

    void preOrder_expanded()
    {
        preOrder_expanded(root);
    }

    void preOrder()
    {
    	cout << endl;
        preOrder(root);
    }

    void inOrder()
    {
    	cout << endl;
        inOrder(root);
    }

    void postOrder()
    {
    	cout << endl;
        postOrder(root);
    }

    void levelOrder()
    {
    	cout << endl;
        queue<node<T> *> q;
        node<T> *curr;
        q.push(root);
        while (!q.empty())
        {
            curr = q.front();
            q.pop();
            if (!curr) continue;
            cout << curr->data << endl;
            q.push(curr->lChild);
            q.push(curr->rChild);
        }
    }
};


int main()
{
    int way, length;
    cout
            << "Please select a way to way to make tree\n1.Post-Order of expanded tree\n2.Pre-Order and In-Order of the tree"
            << endl;
    cin >> way;
    while (way != 1 && way != 2)
    {
        cout << "Invalid command,please enter again:" << endl;
        cin >> way;
    }
    cout << "Please enter the length:";
    cin >> length;
    string tgt[length], pre[length], in[length];
    biTree<string> treeTest;
    if (way == 1)
    {
        cout << "Please enter the data: (using \"###\" to show empty subtree)";
        for (int i = 0; i < length; ++i)
        {
            cin >> tgt[i];
        }
        string end = "###";
        treeTest = biTree<string>(tgt, length, end);
    } else if (way == 2)
    {
    	cout << "Alert: the tree should not have same nodes\n";
        cout << "Please enter the pre-order data:\n";
        for (int i = 0; i < length; ++i)
            cin >> pre[i];
        cout << "Please enter the in-order data:\n";
        for (int i = 0; i < length; ++i)
            cin >> in[i];
        treeTest = biTree<string>(pre, in, length);
    }
    string x;
    while (true)
    {
    	system("cls");
        cout
                << "Please select a function: \n"
                   "0.use function\"info\" \ngo through the tree:\n1.Pre-order\n2.In-order\n3.Post-order\n4.Level-order\n9.exit\n";
        cin >> way;
        switch (way)
        {
            case 1:
            	cout << "result:\n";
                treeTest.preOrder();
                break;
            case 2:
            	cout << "result:\n";
                treeTest.inOrder();
                break;
            case 3:
            	cout << "result:\n";
                treeTest.postOrder();
                break;
            case 4:
            	cout << "result:\n";
                treeTest.levelOrder();
                break;
            case 0:
                cout << "Please input target \"X\": " << endl;
                cin >> x;
                treeTest.info(x);
                break;
            case 9:
                return 0;
            default:
                cout << "Invalid command!" << endl;
        }
        system("pause");
    }
}
