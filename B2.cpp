#include <bits/stdc++.h>
using namespace std;

class Scheduling
{
    int n, at[100], bt[100], wt[100], tat[100], pr[100];
    int all_avg_wait[4], all_avg_tat[4];
    float awt, atat;

public:
    void input()
    {
        cout << "Enter the number of processes: ";
        cin >> n;

        for (int i = 0; i < n; i++)
        {
            cout << "Enter the arrival time of process no " << i + 1 << ": ";
            cin >> at[i];

            cout << "Enter the burst time of process no " << i + 1 << ": ";
            cin >> bt[i];

            cout << "Enter the priority of process no " << i + 1 << ": ";
            cin >> pr[i];
        }
    }

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

        wt[0] = 0;
        float total_burst = bt[0];

        for (int i = 1; i < n; i++)
        {
            wt[i] = total_burst - at[i];
            // wt[i] = wt[i - 1] + bt[i - 1] + at[i - 1];
            if (wt[i] < 0)
            {
                wt[i] = 0;
            }
            total_burst += bt[i];
        }

        float total_wait = 0;
        for (int i = 0; i < n; i++)
        {
            total_wait += wt[i];
        }

        awt = float(total_wait) / n;
        cout << "\nAverage waiting time is: " << awt << "\n";

        float total_tat = 0;
        for (int i = 0; i < n; i++)
        {
            tat[i] = wt[i] + bt[i];
            total_tat += tat[i];
        }

        atat = float(total_tat) / n;
        cout << "Average turnaround time is: " << atat << "\n";

        all_avg_wait[0] = awt;
        all_avg_tat[0] = atat;
    }

    void sjf()
    {
        int process_comp = 0, min_time = INT_MAX, finish_time = 0, shortest = 0, currtime = 0;
        bool found = false;

        int rembt[n];
        for (int i = 0; i < n; i++)
        {
            rembt[i] = bt[i];
        }

        while (process_comp != n)
        {
            for (int i = 0; i < n; i++)
            {
                if (at[i] <= currtime && rembt[i] < min_time && rembt[i] > 0)
                {
                    min_time = rembt[i];
                    shortest = i;
                    found = true;
                }
            }

            if (!found)
            {
                currtime++;
                continue;
            }

            rembt[shortest]--;
            min_time = rembt[shortest];

            if (min_time == 0)
            {
                min_time = INT_MAX;
            }
            if (rembt[shortest] == 0)
            {
                process_comp++;
                found = false;
                finish_time = currtime + 1;
                wt[shortest] = finish_time - bt[shortest] - at[shortest];

                if (wt[shortest] < 0)
                {
                    wt[shortest] = 0;
                }
            }
            currtime++;
        }

        awt = 0, atat = 0;

        float total_wait = 0, total_turnaround = 0;

        for (int i = 0; i < n; i++)
        {
            total_wait += wt[i];
        }
        awt = float(total_wait) / n;
        cout << "\nAverage waiting time is: " << awt << "\n";

        for (int i = 0; i < n; i++)
        {
            tat[i] = wt[i] + bt[i];
            total_turnaround += tat[i];
        }
        atat = float(total_turnaround) / n;
        cout << "Average turnaround time is: " << atat << "\n";

        all_avg_wait[1] = awt;
        all_avg_tat[1] = atat;
    }

    void priority()
    {

        for (int i = 0; i < n; i++)
        {
            bool flag = false;
            for (int j = 0; j < n - i - 1; j++)
            {
                if (pr[j] > pr[j + 1])
                {
                    flag = true;

                    swap(pr[j], pr[j + 1]);
                    swap(at[j], at[j + 1]);
                    swap(bt[j], bt[j + 1]);
                }
            }
            if (!flag)
            {
                break;
            }
        }

        float total_wait = 0, total_turnaround = 0;
        int time = 0, comp_process = 0;

        int rembt[n];
        for (int i = 0; i < n; i++)
        {
            rembt[i] = bt[i];
        }

        while (comp_process < n)
        {
            int minn = INT_MAX;
            int pos = -1;

            for (int i = 0; i < n; i++)
            {
                if (at[i] <= time && pr[i] < minn && rembt[i] != 0)
                { // finding process with highest priority
                    minn = pr[i];
                    pos = i;
                }
            }

            if (pos != -1)
            {
                time += rembt[pos];
                rembt[pos] = 0;
                comp_process++; 

                tat[pos] = time - at[pos];
                total_turnaround += tat[pos];

                wt[pos] = tat[pos] - bt[pos];
                total_wait += wt[pos];
            }
            else
            {
                time++;
            }
        }

        awt = 0, atat = 0;

        awt = float(total_wait) / n;
        cout << "\nAverage waiting time is: " << awt << "\n";

        for (int i = 0; i < n; i++)
        {
            tat[i] = wt[i] + bt[i];
            total_turnaround += tat[i];
        }

        atat = float(total_turnaround) / n;
        cout << "Average turnaround time is: " << atat << "\n";

        all_avg_wait[2] = awt;
        all_avg_tat[2] = atat;
    }

    void round_robin()
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

        int time_quantum;
        cout << "\nEnter the time quantum for the processes: ";
        cin >> time_quantum;

        int rembt[n];
        for (int i = 0; i < n; i++)
        {
            rembt[i] = bt[i];
        }

        int time = 0;
        bool done = false;

        while (!done)
        {

            done = true;
            for (int i = 0; i < n; i++)
            {
                if (rembt[i] > 0)
                {
                    done = false;

                    if (rembt[i] > time_quantum)
                    {
                        time += time_quantum;
                        rembt[i] -= time_quantum;
                    }
                    else
                    {
                        time += rembt[i];
                        wt[i] = time - bt[i] - at[i];
                        rembt[i] = 0;
                    }
                }
            }
        }

        float total_wait = 0, total_turnaround = 0;
        awt = 0, atat = 0;

        for (int i = 0; i < n; i++)
        {
            total_wait += wt[i];
            tat[i] = wt[i] + bt[i];
            total_turnaround += tat[i];
        }

        awt = float(total_wait) / n;
        atat = float(total_turnaround) / n;

        cout << "\nAverage waiting time is: " << awt << "\n";
        cout << "Average turnaround time is: " << atat << "\n";

        all_avg_wait[3] = awt;
        all_avg_tat[3] = atat;
    }

    void display()
    {
        cout << "\nProcess no\t\t"
             << "AT\t"
             << "BT\t"
             << "WT\t"
             << "TAT\n";

        for (int i = 0; i < n; i++)
        {
            cout << i + 1 << "\t\t\t" << at[i] << "\t" << bt[i] << "\t" << wt[i] << "\t" << tat[i] << "\n";
        }
    }
};

int main()
{
    Scheduling s;

    s.input();

    cout << "\n-------------------------FCFS--------------------------\n";
    s.fcfs();
    s.display();

    cout << "\n-------------------------SJF--------------------------\n";
    s.sjf();
    s.display();

    cout << "\n-------------------------PRIORITY--------------------------\n";
    s.priority();
    s.display();

    cout << "\n-------------------------ROUND ROBIN--------------------------\n";
    s.round_robin();
    s.display();
}