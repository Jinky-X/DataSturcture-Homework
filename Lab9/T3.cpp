#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <stdexcept>
#pragma GCC optimize(2)
using namespace std;

const int MAXSIZE = 10000;

struct node
{
    int data, degree = 0;
    node *left = nullptr, *right = nullptr;
};

class BSTree
{
    node *root;

    void change_LL(node *&bt)
    {
        node *B = bt->left;
        bt->left = B->right;
        B->right = bt;
        bt = B;
        refresh_degree(bt);
    }

    void change_LR(node *&bt)
    {
        node *C = bt->left->right, *B = bt->left;
        if (!C) //turn to LL
        {
            B->right = bt;
            bt->left = nullptr;
            bt = B;
            return;
        }
        B->right = C->left;
        bt->left = C->right;
        C->left = B;
        C->right = bt;
        refresh_degree(C);
        if (bt->degree <= -2)
            change_RL(C->right);
        if (C->degree <= -2)
            change_RL(C);
        bt = C;
        refresh_degree(C);
    }

    void change_RR(node *&bt)
    {
        node *B = bt->right;
        bt->right = B->left;
        B->left = bt;
        bt = B;
        refresh_degree(B);
    }

    void change_RL(node *&bt)
    {
        node *C = bt->right->left, *B = bt->right;
        if (!C) //turn to RR
        {
            B->left = bt;
            bt->right = nullptr;
            bt = B;
            return;
        }
        B->left = C->right;
        bt->right = C->left;
        C->left = bt;
        C->right = B;
        refresh_degree(C);
        if (bt->degree >= 2)
            change_LR(C->left);
        bt = C;
        refresh_degree(C);
    }

    int refresh_degree(node *bt) //return depth
    {
        if (!bt)
            return 0;
        int l = refresh_degree(bt->left), r = refresh_degree(bt->right);
        bt->degree = l - r;
        return max(l, r) + 1;
    }

    node *push(int in, node *&bt)
    {
        node *temp;
        if (!bt)
        {
            bt = new node;
            bt->data = in;
        } else
        {
            if (in <= bt->data)
            {
                bt->degree++;
                if (bt->degree <= 1)
                {
                    bt->left = push(in, bt->left);
                    return bt;
                }
                if (in <= bt->left->data)
                {
                    temp = bt->left;
                    temp->left = push(in, temp->left);
                    change_LL(bt);
                    return temp;
                }
                if (in > bt->left->data)
                {
                    bt->left->right = push(in, bt->left->right);
                    change_LR(bt);
                    return bt;
                }
            } else
            {
                bt->degree--;
                if (bt->degree >= -1)
                {
                    bt->right = push(in, bt->right);
                    return bt;
                }
                if (in > bt->right->data)
                {
                    temp = bt->right;
                    bt->right->right = push(in, bt->right->right);
                    change_RR(bt);
                    return temp;
                }
                if (in <= bt->right->data)
                {
                    bt->right->left = push(in, bt->right->left);
                    change_RL(bt);
                    return bt;
                }
            }
        }
    }

    int get_depth(node *bt)
    {
        if (!bt)
            return 0;
        return max(get_depth(bt->left), get_depth(bt->right)) + 1;
    }

    void inOrder(node *bt, ostream &out)
    {
        if (!bt) return;
        inOrder(bt->left, out);
        out << bt->data << endl;
        inOrder(bt->right, out);
    }

public:
    BSTree()
    {
        root = nullptr;
    }

    void push(int in)
    {
        push(in, root);
        refresh_degree(root);
    }

    int get_depth()
    {
        return get_depth(root);
    }

    void inOrder(ostream &out)
    {
        inOrder(root, out);
    }
};

int main()
{
    BSTree t;
    int temp;
    default_random_engine random(time(nullptr));
    uniform_int_distribution<int> dist(int(pow(10, 5)), int(pow(10, 6) - 1));
    for (int i = 0; i < MAXSIZE; ++i)
    {
        temp = dist(random);
        t.push(temp);
    }
    ofstream out("T3_result.txt");
    cout << "depth:\n" << t.get_depth() << "\n";
    t.inOrder(out);
    out.close();
    cout << "File has successfully wrote\n";
    system("pause");
    return 0;
}
