#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>

using namespace std;
const int MaxSize = 300;


struct node
{
    string data;
    node *child, *bro;
};

void clean(string &tgt)
{
    for (int i = 0; i < tgt.size(); ++i)
        if (tgt[i] == '\n' || tgt[i] == ' ')
            tgt.erase(i, 1);
}

class tree
{
    node *root;
public:
    tree()
    {
        root = new node();
        int rear = 0, front = 0;
        string str;
        node *curr, *temp, *queue[MaxSize];
        cout << "请输入根结点的数据:\n";
        cin >> root->data;
        root->child = root->bro = nullptr;
        queue[rear++] = root;
        cout << "（以###结束单次输入，以####结束全部输入）" << endl;
        while (rear != front)
        {
            curr = queue[front++];
            cout << "\n请输入" << curr->data << "的孩子节点：\n";
            while (true)
            {
                getline(cin, str, ',');
                clean(str);
                if (str == "###" || str == "####") break;
                if (str.empty()) continue;
                temp = new node;
                temp->data = str;
                temp->child = nullptr;
                temp->bro = curr->child;
                curr->child = temp;
                queue[rear++] = temp;
            }
            if (str == "####") break;
        }
    }

    void Info()
    {

        int count = 0;
        for (node *p = root->child; p != nullptr; p = p->bro)
            ++count;
        cout << root->data << "共有" << count << "个校区" << endl;
        for (node *p = root->child; p != nullptr; p = p->bro)
        {
            count = 0;
            for (node *q = p->child; q != nullptr; q = q->bro)
                count++;
            cout << p->data << "有" << count << "个学院\n";
        }
        cout << "\n以下学院名称中含有“工程”:" << endl;
        for (node *p = root->child; p != nullptr; p = p->bro)
        {
            for (node *q = p->child; q != nullptr; q = q->bro)
                if (q->data.find("工程") != string::npos)
                    cout << setw(15) << p->data << " -> " << q->data << endl;
        }
        cout << "\n以下学院名称中含有“技术”:" << endl;
        for (node *p = root->child; p != nullptr; p = p->bro)
        {
            for (node *q = p->child; q != nullptr; q = q->bro)
                if (q->data.find("技术") != string::npos)
                    cout << setw(15) << p->data << " -> " << q->data << endl;
        }
    }

    friend ostream &operator<<(ostream &, const tree &);
};

ostream &operator<<(ostream &out, const tree &in)
{
    out << in.root->data << "\n";
    for (node *p = in.root->child; p != nullptr; p = p->bro)
    {
        if (p->bro)
            out << "│── " << p->data << "\n";
        else
            out << "└── " << p->data << "\n";
        for (node *q = p->child; q != nullptr; q = q->bro)
        {
            if (p->bro)
                out << "│  ";
            else
                out << "   ";
            if (q->bro)
                out << " │── " << q->data << "\n";
            else
                out << " └── " << q->data << "\n";
        }
    }
}

int main()
{
    tree sysu;
    cout << "\n输入结束！" << endl;
    int i;
    while (true)
    {
        system("pause");
        system("cls");
        cout << "请选择功能：\n1.学校信息\n2.输出所有学院信息\n0.退出" << endl;
        cin >>  i;
        switch (i)
        {
            case 0:
                return 1;
            case 1:
                sysu.Info();
                break;
            case 2:
                cout << "\n" << sysu;
                break;
            default:
                cout << "错误的指令！" << endl;
        }
    }
}
