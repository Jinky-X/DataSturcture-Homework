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
        cout << "���������������:\n";
        cin >> root->data;
        root->child = root->bro = nullptr;
        queue[rear++] = root;
        cout << "����###�����������룬��####����ȫ�����룩" << endl;
        while (rear != front)
        {
            curr = queue[front++];
            cout << "\n������" << curr->data << "�ĺ��ӽڵ㣺\n";
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
        cout << root->data << "����" << count << "��У��" << endl;
        for (node *p = root->child; p != nullptr; p = p->bro)
        {
            count = 0;
            for (node *q = p->child; q != nullptr; q = q->bro)
                count++;
            cout << p->data << "��" << count << "��ѧԺ\n";
        }
        cout << "\n����ѧԺ�����к��С����̡�:" << endl;
        for (node *p = root->child; p != nullptr; p = p->bro)
        {
            for (node *q = p->child; q != nullptr; q = q->bro)
                if (q->data.find("����") != string::npos)
                    cout << setw(15) << p->data << " -> " << q->data << endl;
        }
        cout << "\n����ѧԺ�����к��С�������:" << endl;
        for (node *p = root->child; p != nullptr; p = p->bro)
        {
            for (node *q = p->child; q != nullptr; q = q->bro)
                if (q->data.find("����") != string::npos)
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
            out << "������ " << p->data << "\n";
        else
            out << "������ " << p->data << "\n";
        for (node *q = p->child; q != nullptr; q = q->bro)
        {
            if (p->bro)
                out << "��  ";
            else
                out << "   ";
            if (q->bro)
                out << " ������ " << q->data << "\n";
            else
                out << " ������ " << q->data << "\n";
        }
    }
}

int main()
{
    tree sysu;
    cout << "\n���������" << endl;
    int i;
    while (true)
    {
        system("pause");
        system("cls");
        cout << "��ѡ���ܣ�\n1.ѧУ��Ϣ\n2.�������ѧԺ��Ϣ\n0.�˳�" << endl;
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
                cout << "�����ָ�" << endl;
        }
    }
}
