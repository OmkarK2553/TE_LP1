#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s, t;
    cin >> s >> t;

    int ones = 0, zeros = 0;
    for (int i = 0; i < t.length(); i++)
    {
        if (t[i] == '0')
        {
            zeros++;
        }
        else
        {
            ones++;
        }
    }
    string t1 = "";
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '0')
        {
            if (ones != 0)
            {
                t1 += '1';
                ones--;
            }
            else
            {
                t1 += '0';
                zeros--;
            }
        }
        else if (s[i] == '1')
        {
            if (zeros != 0)
            {
                t1 += '0';
                zeros--;
            }
            else
            {
                t1 += '1';
                ones--;
            }
        }
    }

    string ans = "";
    for (int i = 0; i < s.length(); i++)
    {
        if ((s[i] == '0' && t1[i] == '0') || (s[i] == '1' && t1[i] == '1'))
        {
            ans += '0';
        }
        else
        {
            ans += '1';
        }
    }
    cout << t1 << "\n";
    cout << ans << "\n";
}