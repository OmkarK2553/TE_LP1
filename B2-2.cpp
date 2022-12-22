#include <bits/stdc++.h>
using namespace std;

class Scheduling
{
    int n;
    vector<int> at, bt, pr;

    void fcfs()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (at[j] > at[j + 1])
                {
                    swap(at[j], at[j + 1]);
                    swap(bt[j], bt[j + 1]);
                    swap(pr[j], pr[j + 1]);
                }
            }
        }

        vector<int> wt(n), tat(n), ct(n);

        wt[0] = 0;
        tat[0] = wt[0] + bt[0];
        ct[0] = tat[0] + at[0];

        for (int i = 1; i < n; i++)
        {
            wt[i] = wt[i - 1] + bt[i - 1] + at[i - 1] - at[i];
            tat[i] = at[i] + bt[i];
            ct[i] = tat[i] + at[i];
        }

        int tot_w = 0, tot_t = 0;
        for (int i = 0; i < n; i++)
        {
            tot_w += wt[i];
            tot_t += tat[i];
        }
    }

    void sjf()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (at[j] > at[j + 1])
                {
                    swap(at[j], at[j + 1]);
                    swap(bt[j], bt[j + 1]);
                    swap(pr[j], pr[j + 1]);
                }
            }
        }

        vector<int> wt(n), tat(n), ct(n), rembt(n);

        for (int i = 0; i < n; i++)
        {
            rembt[i] = bt[i];
        }

        int pdone = 0, currtime = 0, selected, minn = INT_MAX;
        bool check = false;

        while (pdone != n)
        {
            for (int i = 0; i < n; i++)
            {
                if (at[i] <= currtime && rembt[i] < minn && rembt[i] > 0)
                {
                    minn = rembt[i];
                    selected = i;
                    check = true;
                }
            }

            if (!check)
            {
                currtime++;
                continue;
            }

            rembt[selected]--;
            minn = rembt[selected];

            if (rembt[selected] == 0)
            {
                pdone++;
                check = false;
                minn = INT_MAX;

                int finishtime = currtime + 1;
                wt[selected] = finishtime - bt[selected] - at[selected];
                if (wt[selected] < 0)
                {
                    wt[selected] = 0;
                }
                tat[selected] = wt[selected] + bt[selected];
                ct[selected] = finishtime;
            }
            currtime++;
        }
    }

    void priority()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (pr[j] > pr[j + 1])
                {
                    swap(at[j], at[j + 1]);
                    swap(bt[j], bt[j + 1]);
                    swap(pr[j], pr[j + 1]);
                }
            }
        }

        vector<int> wt(n), tat(n), ct(n), rembt(n);

        for (int i = 0; i < n; i++)
        {
            rembt[i] = bt[i];
        }

        int pdone = 0, currtime = 0, selected, maxx = INT_MIN;
        bool check = false;

        while (pdone != n)
        {
            for (int i = 0; i < n; i++)
            {
                if (at[i] <= currtime && pr[i] > maxx && rembt[i] > 0)
                {
                    maxx = pr[i];
                    selected = i;
                    check = true;
                }
            }

            if (!check)
            {
                currtime++;
                continue;
            }

            currtime += rembt[selected];
            rembt[selected] = 0;
            pdone++;
            check = false;
            maxx = INT_MIN;

            int finishtime = currtime;
            wt[selected] = finishtime - bt[selected] - at[selected];
            if (wt[selected] < 0)
            {
                wt[selected] = 0;
            }
            tat[selected] = wt[selected] + bt[selected];
            ct[selected] = finishtime;
        }
    }

    void rr()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (at[j] > at[j + 1])
                {
                    swap(at[j], at[j + 1]);
                    swap(bt[j], bt[j + 1]);
                    swap(pr[j], pr[j + 1]);
                }
            }
        }

        vector<int> wt(n), tat(n), ct(n), rembt(n);

        for (int i = 0; i < n; i++)
        {
            rembt[i] = bt[i];
        }

        int tc;
        cin >> tc;

        int currtime = at[0];
        list<int> q;
        q.push_back(0);

        while (!q.empty())
        {
            int ind = q.front();
            q.pop_front();

            if (rembt[ind] <= tc)
            {
                currtime += rembt[ind];
                rembt[ind] = 0;
                wt[ind] = currtime - bt[ind] - at[ind];
                tat[ind] = bt[ind] + wt[ind];
                ct[ind] = currtime;
            }
            else
            {
                currtime += tc;
                rembt[ind] -= tc;
            }

            for (int i = 0; i < n; i++)
            {
                if (i != ind && at[i] <= currtime && rembt[i] > 0)
                {
                    auto itr = find(q.begin(), q.end(), i);

                    if (itr == q.end())
                    {
                        q.push_back(i);
                    }
                }
            }
            if (rembt[ind] > 0)
            {
                q.push_back(ind);
            }
        }
    }
};