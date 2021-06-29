#include <iostream>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <queue>

using namespace std;
template<class T>
struct node
{
    T data;
    bool lTag, rTag; //Tag==true => lChild is real
    node<T> *lChild, *rChild, *parent, *next;
};

template<class T>
class biTree
{
    node<T> *root;

    void copy(node<T> *&bt, node<T> *ori)
    {
        bt = ori;
        if (ori)
        {
            bt->lTag = ori->lTag;
            bt->rTag = ori->rTag;
            if (bt->lTag)
                copy(bt->lChild, ori->lChild);
            else bt->lChild = ori->lChild;
            if (bt->rTag)
                copy(bt->rChild, ori->rChild);
            else bt->rChild = ori->rChild;
        }
    }

    void preOrderLink(node<T> *bt, node<T> *&prev)
    {
        if (!bt) return;
        if (prev->rChild)
        {
            prev->rTag = true;
        } else
        {
            prev->rTag = false;
            prev->rChild = bt;
        }
        if (bt->lChild)
            bt->lTag = true;
        else
        {
            bt->lTag = false;
            bt->lChild = prev;
        }
        prev = bt;
        if (bt->lTag)
            preOrderLink(bt->lChild, prev);
        if (bt->rChild)
            preOrderLink(bt->rChild, prev);
    }

    void inOrderLink(node<T> *bt, node<T> *&prev)
    {
        if (bt->lChild)
            inOrderLink(bt->lChild, prev);
        if (prev)
        {
            if (prev->rChild)
            {
                prev->rTag = true;
            } else
            {
                prev->rTag = false;
                prev->rChild = bt;
            }
        }
        if (bt->lChild)
            bt->lTag = true;
        else
        {
            bt->lTag = false;
            bt->lChild = prev;
        }
        prev = bt;
        if (prev->rChild)
            inOrderLink(bt->rChild, prev);
    }

    void postOrderLink(node<T> *bt, node<T> *&prev)
    {
        if (bt->lChild)
            postOrderLink(bt->lChild, prev);
        if (bt->rChild)
            postOrderLink(bt->rChild, prev);
        if (prev)
        {
            if (prev->rChild)
            {
                prev->rTag = true;
            } else
            {
                prev->rTag = false;
                prev->rChild = bt;
            }
        }
        if (bt->lChild)
            bt->lTag = true;
        else
        {
            bt->lTag = false;
            bt->lChild = prev;
        }
        prev = bt;
    }

    void linkParent(node<T> *bt)
    {
        if (!bt) return;
        bt->parent = findParent(bt, root);
        linkParent(bt->lChild);
        linkParent(bt->rChild);
    }

    node<T> *findParent(node<T> *tgt, node<T> *bt)
    {
        if (!bt->lChild || !bt->rChild) return nullptr;
        if (bt->lChild == tgt || bt->rChild == tgt)
            return bt;
        node<T> *t1 = findParent(tgt, bt->lChild), *t2 = findParent(tgt, bt->rChild);
        if (t2) return t2;
        if (t1) return t1;
        return nullptr;
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

    void preOrderLink()
    {
        if (!root) return;
        node<T> *prev = root;
        if (root->rChild)
        {
            preOrderLink(root->lChild, prev);
            root->lTag = true;
        } else
        {
            root->lTag = false;
            root->lChild = nullptr;
        }
        if (root->rChild)
        {
            preOrderLink(root->rChild, prev);
            root->rTag = true;
        } else
            root->rTag = false;
        if (!prev->rChild)
            prev->rTag = false;
        else prev->rTag = true;
    }

    void inOrderLink()
    {
        if (!root) return;
        node<T> *prev = nullptr;
        inOrderLink(root, prev);
        if (!prev->rChild)
            prev->rTag = false;
        else prev->rTag = true;
    }

    void postOrderLink()
    {
        if (!root) return;
        node<T> *prev = nullptr;
        linkParent(root);
        postOrderLink(root, prev);
        if (!prev->rChild)
            prev->rTag = false;
        else prev->rTag = true;
    }

    void preOrder()
    {
        node<T> *curr = root;
        if (!root) return;
        while (curr->lChild)
        {
            cout << curr->data << endl;
            if (curr->lTag)
                curr = curr->lChild;
            else
                curr = curr->rChild;
            if (!curr)
                break;
        }
    }

    void inOrder()
    {
        node<T> *curr = root;
        if (!root) return;
        while (curr->lTag)
            curr = curr->lChild;
        cout << curr->data << "\n";
        while (curr->rChild)
        {
            if (!curr->rTag)
                curr = curr->rChild;
            else
            {
                curr = curr->rChild;
                while (curr->lTag)
                    curr = curr->lChild;
            }
            cout << curr->data << endl;
        }
    }

    void postOrder()
    {
        node<T> *curr = root;
        if (!root) return;
        bool rootFlag = false;
        while (curr->lTag)
            curr = curr->lChild;
        cout << curr->data << "\n";
        while (true)
        {
            if (curr->lTag && curr->rTag && curr != root)
            {
                curr = curr->parent;
                if (curr == root)
                {
                    if (rootFlag || !root->rChild)
                    {
                        cout << root->data << endl;
                        return;
                    }
                    rootFlag = true;
                    curr = curr->rChild;
                    while (curr->lTag)
                        curr = curr->lChild;
                }
            } else
            {
                if (!curr->rTag)
                    curr = curr->rChild;
                else
                {
                    curr = curr->rChild;
                    while (curr->lTag)
                        curr = curr->lChild;
                }
            }
            cout << curr->data << "\n";
            if (curr == root)
                rootFlag = false;
        }
    }

    biTree()
    {
        root = nullptr;
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

    void levelOrderLink()
    {
        queue<node<T> *> q;
        node<T> *curr, *prev = root;
        q.push(root);
        while (!q.empty())
        {
            curr = q.front();
            q.pop();
            if (!curr) continue;
            if (curr != root)
                prev->next = curr;
            prev = curr;
            q.push(curr->lChild);
            q.push(curr->rChild);
        }
        prev->next = nullptr;
    }

    void levelOrder()
    {
        node<T> *p = root;
        while (p)
        {
            cout << p->data << endl;
            p = p->next;
        }
    }
};

int main()
{
    int length, way;
    cout << "Please enter the length:";
    cin >> length;
    if (length < 0)
    {
        cerr << "invalid length\n";
        return -1;
    }
    string tgt[length];
    cout
            << "Using expanded Bi-tree to initialize the tree\nPlease input the data: (using \"###\" to show empty subtree)\n";
    for (int i = 0; i < length; ++i)
        cin >> tgt[i];
    string end = "###";
    biTree<string> treeTest(tgt, length, end);
    system("cls");
    cout
            << "Please select a way to link and go through the tree\n(the tree can only be linked and went through only for once)\n"
            << "1.pre-order \n2.in-order\n3.post-order\n4.level-order\n0.exit\n";
    cin >> way;
    cout << "result:\n";
    switch (way)
    {
        case 1:
            treeTest.preOrderLink();
            treeTest.preOrder();
            break;
        case 2:
            treeTest.inOrderLink();
            treeTest.inOrder();
            break;
        case 3:
            treeTest.postOrderLink();
            treeTest.postOrder();
            break;
        case 4:
            treeTest.levelOrderLink();
            treeTest.levelOrder();
            break;
        case 0:
            return 0;
        default:
            cout << "Invalid command!" << endl;
    }
    system("pause");
    return 0;
}
