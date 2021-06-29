#include<iostream>

using namespace std;

void enCode(char *c, int l)
{
    for (int i = 0; c[i] != '\0'; i++)
    {
        if (c[i] >= 'a' && c[i] <= 'z')
            c[i] = (int(c[i]) - 97 + l) % 26 + 97;
        if (c[i] >= 'A' && c[i] <= 'Z')
            c[i] = (int(c[i]) - 65 + l) % 26 + 65;
    }
}

void deCode(char *c, int l)
{
    for (int i = 0; c[i] != '\0'; i++)
    {
        if (c[i] >= 'a' && c[i] <= 'z')
            c[i] = (int(c[i]) - 97 - l + 26) % 26 + 97;
        if (c[i] >= 'A' && c[i] <= 'Z')
            c[i] = (int(c[i]) - 65 - l + 26) % 26 + 65;
    }
}

void deCode_violence(char *c, int l)
{
    for (int j = 0; j < 25; j++)
    {
        deCode(c, 1);
        cout << c << endl;
    }
}

int main()
{
    int fun, l;
    char c[100];
    cout << "please enter a sentence:";
    cin.getline(c, 100);
    while (1)
    {
        system("cls");
        cout << "please select a function:\n1.encoding\n2.decoding\n3.violently decoding\n0.exit" << endl;
        cin >> fun;
        switch (fun)
        {
            case 0:
                return 0;
            case 1:
                cout << "please enter a number: " << endl;
                cin >> l;
                enCode(c, l);
                cout << c << endl;
                break;
            case 2:
                cout << "please enter a number: " << endl;
                cin >> l;
                deCode(c, l);
                cout << c << endl;
                break;
            case 3:
                deCode_violence(c, l);
                break;
            default:
                cout << "Invalid command!";
        }
        system("pause");
    }
}
