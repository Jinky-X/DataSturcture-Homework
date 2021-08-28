#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <stdexcept>

using namespace std;

static double normal_cdf(double avg, double sig, double x)
{
    return 0.5 * erfc((avg - x) / (pow(2, 0.5) * sig));
}

template<typename T>
void distinct(vector<T> &vec)
{
    auto it = vec.begin(), it1 = it;
    for (it = vec.begin(); it != vec.end();)
    {
        it1 = find(vec.begin(), vec.end(), *it);
        if (it1 != it)
            vec.erase(it1);
        else
            it++;
    }
}

struct majorInfo
{
    string name, school;
    int minScore[3], avgScore[3];
    int minRank[3], avgRank[3], plan[3] = {}, countEmpty = 0;
    double avgMinRank = 0, avgAvgRank = 0, varMinRank = 0, pop;

    majorInfo()
    {}

    static bool popularity_comp(const majorInfo &x, const majorInfo &y)
    {
        return x.pop < y.pop;
    }
};

bool operator==(const majorInfo &in, const string &str)
{
    return (in.name.find(str) != -1 || str.find(in.name) != -1);
}

bool operator==(const majorInfo &a, const majorInfo &b)
{
    return a.name == b.name;
}

struct score
{
    int num, amount, total;

    bool operator==(int i) const
    {
        return i == num;
    }
};

struct major21
{
    string name;
    vector<majorInfo> major;
    double rankPresume = 0, varPresume = 0;

    bool operator==(string &str) const
    {
        return name.find(str) != -1;
    }

    void make_presume()
    {
        double totalPop = 0;
        for (auto &it : major)
        {
            totalPop += it.pop;
        }
        for (auto &it : major)
        {
            rankPresume += it.avgMinRank * it.pop / totalPop;
            varPresume += pow(it.varMinRank * pow(it.pop / totalPop, 2), 0.5);
        }
    }

    double prob(const int score) const
    {
        return 1 - normal_cdf(rankPresume, varPresume, score);
    }
};

void input_score(istream &in, vector<score> &scoData)
{
    string temp;
    score sco;
    getline(in, temp);
    while (!in.eof())
    {
        in >> sco.num >> sco.amount >> sco.total;
        scoData.push_back(sco);
    }
}

void input_admission(vector<majorInfo> &data, vector<score> scoData[])
{
    ifstream fAdm("admission2018-2020.txt");
    if (!fAdm.is_open())
        throw invalid_argument("admission file is not found!");
    majorInfo temp;
    string pass;
    vector<score>::iterator it;
    int countEffective = 0;
    while (!fAdm.eof())
    {
        temp.countEmpty = 0;
        temp.varMinRank = temp.avgMinRank = temp.avgAvgRank = 0;
        fAdm >> temp.name >> temp.school >> pass;
        for (int i = 2; i >= 0; --i)
        {
            fAdm >> temp.minScore[i] >> temp.avgScore[i];
            if (temp.minScore[i] == -1)
            {
                temp.countEmpty++;
                temp.minRank[i] = -1;
                temp.avgRank[i] = -1;
                continue;
            }
            it = find(scoData[i].begin(), scoData[i].end(), temp.minScore[i]);
            temp.minRank[i] = it->total;
            it = find(scoData[i].begin(), scoData[i].end(), temp.avgScore[i]);
            temp.avgRank[i] = it->total;
            temp.avgMinRank += double(temp.minRank[i]) / 3;
            temp.avgAvgRank += double(temp.avgRank[i]) / 3;
        }
        temp.avgMinRank *= 3.0 / (3 - temp.countEmpty);
        temp.avgAvgRank *= 3.0 / (3 - temp.countEmpty);
        if (temp.countEmpty == 0)
        {
            for (int i : temp.minRank)
            {
                temp.varMinRank += pow(double(i - temp.avgMinRank), 2) / 2;
            }
            countEffective++;
        } else if (temp.countEmpty == 1)
        {
            for (int i : temp.minRank)
                if (temp.avgMinRank != -1)
                    temp.varMinRank += pow(double(i - temp.avgMinRank), 2);
            countEffective++;
        } else temp.varMinRank = -1;
        data.push_back(temp);
    }
    double avgVar = 0;
    for (auto &i : data)
    {
        if (i.countEmpty != 2)
            avgVar += i.varMinRank / countEffective;
    }
    for (auto &i : data)
    {
        if (i.countEmpty == 2)
            i.varMinRank = avgVar;
    }
    fAdm.close();
}

void input_plan(vector<majorInfo> &data, vector<major21> &result)
{
    string planName[] = {"plan2018.txt", "plan2019.txt", "plan2020.txt", "plan2021.txt"};
    int enroll;
    string majorName, temp;
    vector<majorInfo>::iterator it;
    for (int i = 0; i < 3; i++)
    {
        ifstream plan(planName[i]);
        if (!plan.is_open())
            throw invalid_argument("plan file not found!");
        getline(plan, temp);
        while (!plan.eof())
        {
            plan >> majorName;
            for (int j = 0; j < 3; ++j)
                plan >> temp;
            plan >> enroll;
            getline(plan, temp);
            it = find(data.begin(), data.end(), majorName);
            it->plan[i] = enroll;
        }
        plan.close();
    }
}

void plan21(vector<majorInfo> &data, vector<major21> &result)
{
    string planName[] = {"plan2018.txt", "plan2019.txt", "plan2020.txt", "plan2021.txt"};
    int enroll;
    string majorName, temp;
    vector<majorInfo>::iterator it;
    major21 mTemp;
    ifstream plan(planName[3]);
    while (!plan.eof())
    {
        plan >> mTemp.name;
        plan >> temp;
        plan >> temp;
        mTemp.major.clear();
        for (plan >> majorName; majorName != "#"; plan >> majorName)
        {
            it = data.begin();
            while (true)
            {
                it = find(it, data.end(), majorName);
                if (it != data.end())
                    mTemp.major.push_back(*it);
                else break;
                it++;
            }
        }
        distinct(mTemp.major);
        result.push_back(mTemp);
    }
    result.erase(result.end() - 1);
    plan.close();

}

void popularity(vector<majorInfo> &data)
{
    double quota1, quota2;
    int enroll;
    for (auto &it : data)
    {
        for (int i = 0, enroll = 0; i < 3; ++i)
        {
            enroll += it.plan[i] / 3;
        }
        quota1 = 1.0 / log((it.avgMinRank - it.avgAvgRank) / enroll);
        quota2 = 500 / (it.avgAvgRank - 500);
        it.pop = quota1 + quota2;
    }
}

int main()
{
    vector<majorInfo> majorData;
    majorInfo temp;
    vector<score> scoData[4];
    vector<major21> result;
    int fun;
    string ScoreName[] = {"score2018.txt", "score2019.txt", "score2020.txt", "score2021.txt"};
    for (int i = 0; i < 4; ++i)
    {
        ifstream fScore(ScoreName[i]);
        if (!fScore.is_open())
            throw invalid_argument("score file is not opened!");
        input_score(fScore, scoData[i]);
        fScore.close();
    }
    input_admission(majorData, scoData);
    input_plan(majorData, result);
    popularity(majorData);
    plan21(majorData, result);
    sort(majorData.begin(), majorData.end(), majorInfo::popularity_comp);
    for (auto &it : result)
        it.make_presume();
    while (true)
    {
        system("cls");
        cout << "----------------------------------\n"
                "   _______     _______ _    _ \n"
                "  / ____\\ \\   / / ____| |  | |\n"
                " | (___  \\ \\_/ / (___ | |  | |\n"
                "  \\___ \\  \\   / \\___ \\| |  | |\n"
                "  ____) |  | |  ____) | |__| |\n"
                " |_____/   |_| |_____/ \\____/ \n"
                "\n----------------------------------\n";
        cout << "请选择一个功能：\n1. 显示十大热门、冷门专业\n2. 输出带排名的前三年录取情况\n3. 志愿推荐\n0. 退出\n";
        cin >> fun;
        if (fun == 0)
            return 0;
        else if (fun == 1)
        {
            cout << "\n十大冷门专业：\n";
            for (auto it = majorData.begin(); it < majorData.begin() + 10 && it != majorData.end(); ++it)
                cout << it->name << "\n";
            cout << "\n十大热门专业：\n";
            for (auto it = majorData.end() - 1; it > majorData.end() - 11 && it != majorData.begin(); --it)
                cout << it->name << "\n";
        } else if (fun == 2)
        {
            ofstream out("2018-2020录取情况修改版.csv");
            out
                    << "专业名称,所属学院,2018最低分,2018最低排位,2018平均分,2018平均排位,2019最低分,2019最低排位,"
                       "2019平均分,2019平均排位,2020最低分,2020最低排位,2020平均分,2020平均排位\n";
            for (auto &it : majorData)
            {
                out << it.name << "," << it.school << ",";
                for (int i = 0; i < 3; ++i)
                {
                    out << it.minScore[i] << "," << it.minRank[i] << "," << it.avgScore[i] << "," << it.avgRank[i]
                        << ",";
                }
                out << "\n";
            }
            out.close();
            cout << "\n输出成功！\n请查看文件“2018-2020录取情况修改版.csv”\n";
        } else if (fun == 3)
        {
            struct majorProb
            {
                major21 info;
                double prob;

                bool operator<(majorProb &b) const
                {
                    return prob < b.prob;
                }

                majorProb(major21 &i, double b)
                {
                    info = i;
                    prob = b;
                }
            };
            int rank;
            cout << "\n请输入您的排名\n";
            cin >> rank;
            if (rank <= 800)
                cout << "恭喜，因为您的分数太高了，中山大学所有的专业您都可以随意选择\n";
            else if (rank >= 10000)
                cout << "真可惜，您的分数无法达到中山大学的投档线\n";
            else
            {
                vector<majorProb> majors;
                for (auto &it : result)
                    majors.emplace_back(it, it.major21::prob(rank));
                sort(majors.begin(), majors.end());
                vector<majorProb>::iterator it;
                for (it = majors.begin(); it->prob < 0.2 && it < majors.end(); it++)
                {}
                cout << "\n可冲刺的专业组：\n"
                     << "--------------------------------------------------------\n"
                        "              专业名称           |     录取概率\n"
                        "--------------------------------------------------------\n";
                for (; it->prob < 0.5 && it < majors.end(); it++)
                {
                    cout << setw(32) << it->info.name << " | " << setprecision(3) << it->prob * 100 << "%\n";
                }
                cout << "--------------------------------------------------------\n"
                     << "\n较稳的专业组：\n"
                     << "--------------------------------------------------------\n"
                        "              专业名称           |     录取概率\n"
                        "--------------------------------------------------------\n";
                for (; it->prob < 0.8 && it < majors.end(); it++)
                {
                    cout << setw(32) << it->info.name << " | " << setprecision(3) << it->prob * 100 << "%\n";
                }
                cout << "--------------------------------------------------------\n"
                     << "\n可保底的专业组：\n"
                     << "--------------------------------------------------------\n"
                        "              专业名称           |     录取概率\n"
                        "--------------------------------------------------------\n";
                for (; it < majors.end(); it++)
                {
                    cout << setw(32) << it->info.name << " | " << setprecision(3) << it->prob * 100 << "%\n";
                }
                cout << "--------------------------------------------------------\n"
                     << "以上结果的参考依据是近三年的录取分数，具体内容请参考选项2中生成的文件\n";

            }
        } else cout << "命令输入错误，请重新输入\n";
        cout << "\n";
        system("pause");
    }
}
