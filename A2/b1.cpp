#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> arr;
    arr.push_back(1);
    arr.push_back(3);
    arr.push_back(8);
    int m = 3;
    int k = 10;

    // map<int, int> m;

    // for (int i = 0; i < arr.size(); i++)
    // {
    //     m[arr[i]]++;
    // }

    int q = 1;
    int items = m;
    while (k > 0 && q<=k)
    {
        bool f = false;
        for (int i = 0; i < m; i++)
        {
            if (arr[i] == q)
            {
                f = true;
                break;
            }
        }
        if (f)
        {
            q++;
            continue;
        }

        items++;
        k -= q;
        q++;
    }

    cout << items << "\n";

    return 0;
}