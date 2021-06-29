#include <iostream>
#include <vector>

using namespace std;

struct child
{
    int id;
    child *next;
};

template<class T>
struct node
{
    int id, parent;
    T data;
    child *next;
};

template<class T>
class realTree
{
    vector<node<T>> tree;

    ostream &print(int index, ostream &out, int depth, bool flag[], bool tag = false)
    {
        if (index)
            for (int i = 1; i < depth; ++i)
            {
                if (flag[i])
                    out << "    ";
                else
                    out << "©¦   ";
            }
        if (index)
        {
            if (!tag)
                out << "©¦©¤©¤";
            else out << "©¸©¤©¤";
        }
        out << " " << tree[index].data << "\n";
        child *p = tree[index].next;
        while (p)
        {
            if (p->next)
                print(p->id, out, depth + 1, flag);
            else
                print(p->id, out, depth + 1, flag, true);
            p = p->next;
        }
        flag[index] = true;
        return out;
    }

public:
    realTree()
    {
        typename vector<node<T>>::iterator i;
        node<T> temp;
        child *curr;
        int count = 0;
        cout << "Please enter node id, parent and its data: \n(end with '-1' in parent)\n";
        while (true)
        {
            cin >> temp.parent >> temp.data;
            temp.parent -= 1;
            temp.id = count++;
            temp.next = nullptr;
            for (i = tree.begin(); i != tree.end(); i++)
                if (i->id == temp.parent)
                {
                    curr = i->next;
                    if (!curr)
                    {
                        i->next = new child;
                        i->next->id = temp.id;
                        i->next->next = nullptr;
                    } else
                    {
                        while (curr->next)
                            curr = curr->next;
                        curr->next = new child;
                        curr->next->id = temp.id;
                        curr->next->next = nullptr;
                    }
                    break;
                }
            if (temp.parent == -2)
                break;
            if (tree.empty() || i != tree.end())
                tree.push_back(temp);
            else
                cerr << "invalid id\n";
        }
        if (!tree.empty())
            tree[0].parent = -1;
    }

    template<class T1>
    friend ostream &operator<<(ostream &out, realTree<T1> &tgt);

};

template<class T>
ostream &operator<<(ostream &out, realTree<T> &tgt)
{
    if (tgt.tree.empty()) return out;
    bool flag[tgt.tree.size()];
    for (int i = 0; i < tgt.tree.size(); ++i)
        flag[i] = false;
    return tgt.print(0, out, 0, flag);
}

int main()
{
    realTree<string> testTree;
    cout << "\nresult:\n";
    cout << testTree;
    system("pause");
    return 0;
}
