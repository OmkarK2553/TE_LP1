#include <bits/stdc++.h>
using namespace std;

class Scheduling
{
    int n;
    vector<int> at, bt, pr;
    vector<float> avg_wait_time, avg_tat_time;

public:
    Scheduling()
    {
        n = 0;
        at.resize(n);
        bt.resize(n);
        pr.resize(n);
        avg_wait_time.resize(4);
        avg_tat_time.resize(4);
    }

    void input()
    {
        cout << "Enter number of processes :- ";
        cin >> n;

        at.resize(n);
        bt.resize(n);
        pr.resize(n);

        for (int i = 0; i < n; i++)
        {
            cout << "Enter the arrival time for " << i + 1 << " process :- ";
            cin >> at[i];
        }

        for (int i = 0; i < n; i++)
        {
            cout << "Enter the burst time for " << i + 1 << " process :- ";
            cin >> bt[i];
        }

        for (int i = 0; i < n; i++)
        {
            cout << "Enter the priority for " << i + 1 << " process :- ";
            cin >> pr[i];
        }
    }

    void display()
    {

        for (int i = 0; i < n; i++)
        {
            cout << "Arival time for " << i + 1 << " process :- ";
            cout << at[i] << "\n";
        }

        for (int i = 0; i < n; i++)
        {
            cout << "Burst time for " << i + 1 << " process :- ";
            cout << bt[i] << "\n";
        }

        for (int i = 0; i < n; i++)
        {
            cout << "Priority for " << i + 1 << " process :- ";
            cout << pr[i] << "\n";
        }
    }

    void fcfs()
    {
        cout << "--- FCFS ---"
             << "\n";

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

        vector<int> ct(n), tat(n), wt(n);

        wt[0] = 0;
        tat[0] = wt[0] + bt[0];
        ct[0] = tat[0] + at[0];

        for (int i = 1; i < n; i++)
        {
            wt[i] = (wt[i - 1] + bt[i - 1] + at[i - 1]) - at[i];
            if (wt[i] < 0)
                wt[i] = 0;
            tat[i] = wt[i] + bt[i];
            ct[i] = tat[i] + at[i];
        }

        int total_wait = 0, total_tat = 0;
        for (int i = 0; i < n; i++)
        {
            total_wait += wt[i];
            total_tat += tat[i];
        }

        float avg_wait, avg_tat;
        avg_wait = (float)total_wait / n;
        avg_tat = (float)total_tat / n;

        cout << "\tPN\t\tAT\t\tBT\t\tPR\t\tCT\t\tWT\t\tTAT\n";
        for (int i = 0; i < n; i++)
        {
            cout << "\t" << i + 1 << "\t\t" << at[i] << "\t\t" << bt[i] << "\t\t" << pr[i] << "\t\t" << ct[i] << "\t\t"
                 << wt[i] << "\t\t" << tat[i] << "\n";
        }

        cout << "Average waiting time = " << avg_wait << "\n";
        cout << "Average turn around time = " << avg_tat << "\n";

        avg_wait_time[0] = avg_wait;
        avg_tat_time[0] = avg_tat;
    }

    void sjf()
    {
        cout << "--- SJF ---"
             << "\n";

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

        vector<int> ct(n), tat(n), wt(n), rbt(n, 0);
        for (int i = 0; i < n; i++)
            rbt[i] = bt[i];

        int pdone = 0, currentTime = 0, maxx = INT_MAX, selected;
        bool check = false;

        while (pdone != n)
        {
            for (int i = 0; i < n; i++)
            {
                if (at[i] <= currentTime && rbt[i] < maxx && rbt[i] > 0)
                {
                    selected = i;
                    check = true;
                    maxx = rbt[i];
                }
            }

            if (!check)
            {
                currentTime++;
                continue;
            }

            rbt[selected]--;
            maxx = rbt[selected];

            if (rbt[selected] == 0)
            {
                pdone++;
                maxx = INT_MAX;
                check = false;

                int finishTime = currentTime + 1;
                wt[selected] = finishTime - bt[selected] - at[selected];
                if (wt[selected] < 0)
                    wt[selected] = 0;
                tat[selected] = wt[selected] + bt[selected];
                ct[selected] = finishTime;
            }
            currentTime++;
        }

        int total_wait = 0, total_tat = 0;
        for (int i = 0; i < n; i++)
        {
            total_wait += wt[i];
            total_tat += tat[i];
        }

        float avg_wait, avg_tat;
        avg_wait = (float)total_wait / n;
        avg_tat = (float)total_tat / n;

        cout << "\tPN\t\tAT\t\tBT\t\tPR\t\tCT\t\tWT\t\tTAT\n";
        for (int i = 0; i < n; i++)
        {
            cout << "\t" << i + 1 << "\t\t" << at[i] << "\t\t" << bt[i] << "\t\t" << pr[i] << "\t\t" << ct[i] << "\t\t"
                 << wt[i] << "\t\t" << tat[i] << "\n";
        }

        cout << "Average waiting time = " << avg_wait << "\n";
        cout << "Average turn around time = " << avg_tat << "\n";

        avg_wait_time[1] = avg_wait;
        avg_tat_time[1] = avg_tat;
    }

    void priority()
    {
        cout << "--- Priority ---"
             << "\n";

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (pr[j] < pr[j + 1])
                {
                    swap(at[j], at[j + 1]);
                    swap(bt[j], bt[j + 1]);
                    swap(pr[j], pr[j + 1]);
                }
            }
        }

        vector<int> ct(n), wt(n), tat(n), rbt(n, 0);
        for (int i = 0; i < n; i++)
            rbt[i] = bt[i];
        for (int i = 0; i < n; i++)
            cout << rbt[i] << " ";
        cout << "\n";
        int currentTime = 0, pdone = 0, maxx = 0, selected;
        bool check = false;

        while (pdone != n)
        {
            for (int i = 0; i < n; i++)
            {
                if (at[i] <= currentTime && pr[i] > maxx && rbt[i] > 0)
                {
                    maxx = pr[i];
                    selected = i;
                    check = true;
                }
            }

            if (!check)
            {
                currentTime++;
                continue;
            }

            currentTime += rbt[selected];
            rbt[selected] = 0;
            pdone++;
            maxx = 0;
            check = false;

            int finishTime = currentTime;
            wt[selected] = finishTime - bt[selected] - at[selected];
            if (wt[selected] < 0)
                wt[selected] = 0;
            tat[selected] = wt[selected] + bt[selected];
            ct[selected] = finishTime;
        }

        int total_wait = 0, total_tat = 0;
        for (int i = 0; i < n; i++)
        {
            total_wait += wt[i];
            total_tat += tat[i];
        }

        float avg_wait, avg_tat;
        avg_wait = (float)total_wait / n;
        avg_tat = (float)total_tat / n;

        cout << "\tPN\t\tAT\t\tBT\t\tPR\t\tCT\t\tWT\t\tTAT\n";
        for (int i = 0; i < n; i++)
        {
            cout << "\t" << i + 1 << "\t\t" << at[i] << "\t\t" << bt[i] << "\t\t" << pr[i] << "\t\t" << ct[i] << "\t\t"
                 << wt[i] << "\t\t" << tat[i] << "\n";
        }

        cout << "Average waiting time = " << avg_wait << "\n";
        cout << "Average turn around time = " << avg_tat << "\n";

        avg_wait_time[2] = avg_wait;
        avg_tat_time[2] = avg_tat;
    }

    void roundRobin()
    {
        cout << "--- Round Robin ---"
             << "\n";

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

        map<int, array<int, 3>> process;

        for (int i = 0; i < n; i++)
        {
            array<int, 3> a = {at[i], bt[i], pr[i]};
            process[i] = a;
        }

        vector<int> ct(n), wt(n), tat(n), rbt(n);
        for (int i = 0; i < n; i++)
        {
            rbt[i] = bt[i];
        }

        int quantum;
        cout << "Enter time quantum :- ";
        cin >> quantum;

        int currentTime = 0;
        currentTime = at[0];

        list<int> q;
        q.push_back(0);

        while (!q.empty())
        {

            int ind = q.front();
            q.pop_front();
            if (rbt[ind] <= quantum)
            {
                currentTime += rbt[ind];
                rbt[ind] = 0;

                wt[ind] = currentTime - bt[ind] - at[ind];
                tat[ind] = wt[ind] + bt[ind];
                ct[ind] = currentTime;
            }
            else
            {
                currentTime += quantum;
                rbt[ind] -= quantum;
            }

            for (int i = 0; i < n; i++)
            {
                if (i != ind && at[i] <= currentTime && rbt[i] > 0)
                {
                    auto itr = find(q.begin(), q.end(), i);

                    if (itr == q.end())
                    {
                        q.push_back(i);
                                        }
                }
            }

            if (rbt[ind] > 0)
                q.push_back(ind);
        }

        int total_wait = 0, total_tat = 0;
        for (int i = 0; i < n; i++)
        {
            total_wait += wt[i];
            total_tat += tat[i];
        }

        float avg_wait, avg_tat;
        avg_wait = (float)total_wait / n;
        avg_tat = (float)total_tat / n;

        cout << "\tPN\t\tAT\t\tBT\t\tPR\t\tCT\t\tWT\t\tTAT\n";
        for (int i = 0; i < n; i++)
        {
            cout << "\t" << i + 1 << "\t\t" << at[i] << "\t\t" << bt[i] << "\t\t" << pr[i] << "\t\t" << ct[i] << "\t\t"
                 << wt[i] << "\t\t" << tat[i] << "\n";
        }

        cout << "Average waiting time = " << avg_wait << "\n";
        cout << "Average turn around time = " << avg_tat << "\n";

        avg_wait_time[3] = avg_wait;
        avg_tat_time[3] = avg_tat;
    }
};

int main()
{

    Scheduling s;
    s.input();
    s.fcfs();
    s.sjf();
    s.priority();
    s.roundRobin();
    s.display();

    return 0;
}