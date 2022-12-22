#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream fin, mdtin, mntin, kpin;
    fin.open("outputp1.txt");
    mdtin.open("mdtout.txt");
    mntin.open("mntout.txt");
    kpin.open("kpdtout.txt");

    ofstream fout;
    fout.open("machine_code.txt");

    string line, word;

    // KPDT
    vector<pair<string, string>> kpdt(1);

    while (getline(kpin, line))
    {
        stringstream ss(line);
        ss >> word;

        pair<string, string> pr = {"", ""};
        pr.first = word;
        ss >> word;
        pr.second = word;
        kpdt.push_back(pr);
    }

    cout << "\n-----------KPDT------------\n";
    for (int i = 0; i < kpdt.size(); i++)
    {
        cout << kpdt[i].first << "\t" << kpdt[i].second << "\n";
    }

    // MDT
    vector<vector<string>> mdt(1);
    while (getline(mdtin, line))
    {
        stringstream ss(line);
        ss >> word;

        vector<string> a;
        a.push_back(word);

        while (ss >> word)
        {
            if (word[word.size() - 1] == ',')
            {
                word = word.substr(0, word.size() - 1);
            }

            if (word[0] == '(')
            {
                int commaInd = word.size();
                for (int i = 0; i < word.size(); i++)
                {
                    if (word[i] == ',')
                    {
                        commaInd = i;
                        break;
                    }
                }

                word = word.substr(commaInd + 1);
                word = word.substr(0, word.size() - 1);
            }
            a.push_back(word);
        }
        mdt.push_back(a);
    }

    cout << "\n-----------MDT------------\n";

    for (int i = 0; i < mdt.size(); i++)
    {
        for (int j = 0; j < mdt[i].size(); j++)
        {
            cout << mdt[i][j] << "\t";
        }
        cout << "\n";
    }

    // MNT
    vector<array<int, 4>> mnt(1);
    map<string, int> mntMap;

    while (getline(mntin, line))
    {
        stringstream ss(line);
        ss >> word;

        mntMap[word] = mnt.size();
        array<int, 4> a;
        for (int i = 0; i < 4; i++)
        {
            if (ss >> word)
            {
                a[i] = stoi(word);
            }
        }
        mnt.push_back(a);
    }

    cout << "\n-----------MNT------------\n";

    for (int i = 0; i < mnt.size(); i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << mnt[i][j] << "\t";
        }
        cout << "\n";
    }

    // Processing the calls
    while (getline(fin, line))
    {
        // cout << "here2\n";

        stringstream ss(line);
        ss >> word;

        string func = word;
        int mntInd = mntMap[word];
        int totalPara = mnt[mntInd][0] + mnt[mntInd][1];
        vector<string> aptab(totalPara + 1);
        map<string, int> kpInd;

        int indInAp = mnt[mntInd][0] + 1;

        for (int i = 0; i < mnt[mntInd][1]; i++)
        {
            int indInkp = mnt[mntInd][3] + i;
            aptab[indInAp] = kpdt[indInkp].second;
            kpInd[kpdt[indInkp].first] = indInAp;
            indInAp++;
        }

        int ppInd = 1;
        while (ss >> word)
        {
            // cout << "here1\n";
            if (word[0] == '&')
            {
                word = word.substr(1);
            }
            if (word[word.size() - 1] == ',')
            {
                word = word.substr(0, word.size() - 1);
            }

            int equalInd = -1;
            for (int i = 0; i < word.size(); i++)
            {
                if (word[i] == '=')
                {
                    equalInd = i;
                    break;
                }
            }

            if (equalInd != -1)
            {
                string para = word.substr(0, equalInd);
                string val = word.substr(equalInd + 1);
                aptab[kpInd[para]] = val;
            }
            else
            {
                aptab[ppInd] = word;
                ppInd++;
            }
        }

        // 5th
        cout << "\nAPTAB\n";

        for (int i = 0; i < aptab.size(); i++)
        {
            cout << aptab[i] << " ";
        }
        cout << "\nAPTAB\n";
        cout << "\n-------Machine code-------\n";
        for (int i = mnt[mntInd][2]; true; i++)
        {
            if (mdt[i][0] == "MEND")
            {
                break;
            }
            fout << "+ " << mdt[i][0] << " ";
            cout << "+ " << mdt[i][0] << " ";

            for (int j = 1; j < mdt[i].size(); j++)
            {
                // cout << "here3\n";

                if (mdt[i][j][0] == '=')
                {
                    // cout << "here4\n";

                    fout << mdt[i][j];
                }
                else
                {
                    // cout << "here5\n";
                    cout << mdt[i][j];

                    int ind = stoi(mdt[i][j]);
                    // cout << ind << " ind\n";
                    fout << aptab[ind];
                    // cout << aptab[ind] << " aind\n";
                }

                if (j != mdt[i].size() - 1)
                {
                    fout << ", ";
                }
            }
            fout << "\n";
        }
    }
}