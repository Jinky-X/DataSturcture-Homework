#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <fstream>

using namespace std;

const int MAXSIZE = 100;

struct node
{
    char ch;
    int weight, parent, lChild, rChild;
    string id;
};

class huffmanTree
{
    node tree[MAXSIZE * 3];
    int length, charLen;

    void select(int &i1, int &i2)
    {
        int min = tree[0].weight, subMin = tree[1].weight;
        i1 = 0;
        i2 = 1;
        for (int i = 0; i < length; ++i)
            if (tree[i].parent == -1 && (tree[i1].parent != -1 || min > tree[i].weight))
            {
                i1 = i;
                min = tree[i].weight;
            }
        for (int i = 0; i < length; ++i)
            if (tree[i].parent == -1 && (tree[i2].parent != -1 || subMin > tree[i].weight) && i != i1)
            {
                i2 = i;
                subMin = tree[i].weight;
            }
    }

    string getID(char tgt)
    {
        for (int i = 0; i < charLen; ++i)
            if (tree[i].ch == tgt)
                return tree[i].id;
        return "#";
    }

    void idMaker(int tgt, string tempID)
    {
        tree[tgt].id = tempID;
        if (tree[tgt].lChild == -1 && tree[tgt].rChild == -1) return;
        tempID.push_back('0');
        idMaker(tree[tgt].lChild, tempID);
        tempID[tempID.length() - 1] = '1';
        idMaker(tree[tgt].rChild, tempID);
    }

public:
    huffmanTree(const char in[], const int fre[], int len)
    {
        int i1, i2;
        length = charLen = len;
        for (int i = 0; i < len; ++i)
        {
            tree[i].parent = tree[i].rChild = tree[i].lChild = -1;
            tree[i].ch = in[i];
            tree[i].weight = fre[i];
        }
        while (len != 0)
        {
            len--;
            select(i1, i2);
            tree[length].weight = tree[i1].weight + tree[i2].weight;
            tree[length].lChild = i1;
            tree[length].rChild = i2;
            tree[length].parent = -1;
            tree[i1].parent = tree[i2].parent = length;
            length++;
        }
        idMaker(tree[length - 1].lChild, "0");
        idMaker(tree[length - 1].rChild, "1");
    }

    string decode(string str)
    {
        int len = str.length(), i, iTree = length - 1;
        string out;
        for (i = 2; i < len; i++)
        {
            if (str[i] == '0')
                iTree = tree[iTree].lChild;
            else
                iTree = tree[iTree].rChild;
            if (tree[iTree].lChild == -1 && tree[iTree].rChild == -1)
            {
                out.push_back(tree[iTree].ch);
                iTree = length - 1;
            }
        }
        return out;
    }

    string encode(string str)
    {
        string out, fastIndex[55];
        for (int i = 0; i < charLen; ++i)
        {
            if (tree[i].ch >= 'A' && tree[i].ch <= 'Z')
                fastIndex[tree[i].ch - 65] = tree[i].id;
            if (tree[i].ch >= 'a' && tree[i].ch <= 'z')
                fastIndex[tree[i].ch - 71] = tree[i].id;
            if (tree[i].ch == ' ')
                fastIndex[52] = tree[i].id;
            if (tree[i].ch == '\n')
                fastIndex[53] = tree[i].id;
            if (tree[i].ch == '.')
                fastIndex[54] = tree[i].id;
        }
        for (int i = 0; i < str.length(); ++i)
        {
            if (str[i] >= 'A' && str[i] <= 'Z')
                out += fastIndex[str[i] - 65];
            else if (str[i] >= 'a' && str[i] <= 'z')
                out += fastIndex[str[i] - 71];
            else if (str[i] == ' ')
                out += fastIndex[52];
            else if (str[i] == '\n')
                out += fastIndex[53];
            else if (str[i] == '.')
                out += fastIndex[54];
            else
            {
                int j = 0;
                for (; j < charLen; ++j)
                    if (tree[j].ch == str[i])
                    {
                        out += tree[j].id;
                        break;
                    }
                if (j == charLen)
                    throw invalid_argument("character can not be found");
            }
        }
        return out;
    }
};

void counter(string str, char charData[], int fre[], int len, int &lChar)
{
    int iStr, j;
    lChar = 0;
    for (iStr = 0; iStr < len; ++iStr)
    {
        for (j = 0; j < lChar; j++)
            if (charData[j] == str[iStr])
            {
                fre[j]++;
                break;
            }
        if (j == lChar)
        {
            if (lChar == MAXSIZE)
                throw invalid_argument("Overflow");
            charData[lChar++] = str[iStr];
            fre[lChar - 1] = 1;
        }
    }
}


int main()
{
    int fun, input, lChar, output, temp;
    string strIn, filename, strOut;
    char charData[MAXSIZE];
    int fre[MAXSIZE];
    cout << "Please select a function\n1.encode\n2.decode\n";
    cin >> fun;
    if (fun != 1 && fun != 2)
    {
        cout << "Invalid command" << endl;
        system("pause");
    }
    cout << "Please select a way to input\n1.console\n2.file\n";
    cin >> input;
    if (input == 1)
    {
        if (fun == 1)
        {
            cout << "Please input data,end by #\n";
            getline(cin, strIn, '#');
            counter(strIn, charData, fre, strIn.length(), lChar);
        } else
        {
            cout << "Please enter huffmanTree-ID: ";
            cin >> lChar;
            for (int i = 0; i < lChar; ++i)
            {
                cin >> temp >> fre[i];
                charData[i] = char(temp);
            }
            cout << "Please enter code:\n";
            getline(cin, strIn, '#');
        }
    } else if (input == 2)
    {
        cout << "Please input filename:\n";
        cin >> filename;
        ifstream in(filename);
        if (!in.is_open())
        {
            cout << "Invalid filename" << endl;
            system("pause");
            return 0;
        }
        if (fun == 1)
        {
            getline(in, strIn, '#');
            counter(strIn, charData, fre, strIn.length(), lChar);
        } else
        {
            in >> lChar;
            for (int i = 0; i < lChar; ++i)
            {
                in >> temp >> fre[i];
                charData[i] = char(temp);
            }
            getline(in, strIn, '#');
        }
        in.close();
    }

    huffmanTree huff(charData, fre, lChar);
    if (fun == 1)
    {
        strOut = huff.encode(strIn);
        cout << "\nEncode success, compression ratio: " << double(strOut.length()) / 8.0 / double(strIn.length()) * 100
             << "%\n";
    } else
    {
        strOut = huff.decode(strIn);
        cout << "\nDecode success\n";
    }
    cout << "\nPlease select a way to output\n1.console\n2.file\n";
    cin >> output;
    if (output == 1)
    {
        if (fun == 1)
        {

            cout << "\nhuffmanTree-ID:\n" << lChar << " ";
            for (int i = 0; i < lChar; ++i)
                cout << int(charData[i]) << " " << fre[i] << " ";
        }    
		cout << "\n\nThe result is:\n" << strOut;
    } else
    {
        cout << "Please enter filename for output:\n";
        cin >> filename;
        ofstream out(filename);
        if (fun == 1)
        {
            out << lChar << " ";
            for (int i = 0; i < lChar; ++i)
                out << int(charData[i]) << " " << fre[i] << " ";
        }
        out << "\n" << strOut << "#";
        out.close();
    }
    cout << "\n\nDone" << endl;
    system("pause");
    return 0;
}
