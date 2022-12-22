#include <bits/stdc++.h>
using namespace std;

#define MAX 100

class Memory
{
    int n, m, process[MAX], memory[MAX];

public:
    void input()
    {
        cout << "Enter the no of memory blocks: ";
        cin >> m;
        for (int i = 0; i < m; i++)
        {
            cout << "Enter the size of memory block no " << i + 1 << ": ";
            cin >> memory[i];
        }

        cout << "Enter the no of processes: ";
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cout << "Enter the size of process no " << i + 1 << ": ";
            cin >> process[i];
        }
    }

    void display(int b[])
    {
        cout << "Process No\t\tProcess Size\t\tBlock no\n";
        for (int i = 0; i < n; i++)
        {
            cout << i + 1 << "\t\t" << process[i] << "\t\t";
            if (b[i] == -1)
            {
                cout << "Not allocated\n";
            }
            else
            {
                cout << b[i] << "\n";
            }
        }
    }

    void firstFit()
    {
        int dupmem[m];
        int allocated[m];
        int b[n];

        for (int i = 0; i < m; i++)
        {
            dupmem[i] = memory[i];
            allocated[i] = -1;
        }
        for (int i = 0; i < n; i++)
        {
            b[i] = -1;
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (process[i] <= dupmem[j] && allocated[j] == -1)
                {
                    dupmem[j] -= process[i];
                    allocated[j] = 1;
                    b[i] = j + 1;
                    break;
                }
            }
        }
        display(b);
    }

    void bestFit()
    {
        int dupmem[m];
        int allocated[m];
        int b[n];

        for (int i = 0; i < m; i++)
        {
            dupmem[i] = memory[i];
            allocated[i] = -1;
        }
        for (int i = 0; i < n; i++)
        {
            b[i] = -1;
        }

        for (int i = 0; i < n; i++)
        {
            int pos = -1, minn = INT_MAX;
            for (int j = 0; j < m; j++)
            {
                if (process[i] <= dupmem[j] && allocated[j] == -1)
                {
                    int diff = dupmem[j] - process[i];
                    if (diff < minn)
                    {
                        minn = diff;
                        pos = j;
                    }
                }
            }
            if (pos != -1)
            {
                b[i] = pos + 1;
                dupmem[pos] -= process[i];
                allocated[pos] = 1;
            }
        }
        display(b);
    }

    void worstFit()
    {
        int dupmem[m];
        int allocated[m];
        int b[n];

        for (int i = 0; i < m; i++)
        {
            dupmem[i] = memory[i];
            allocated[i] = -1;
        }
        for (int i = 0; i < n; i++)
        {
            b[i] = -1;
        }

        for (int i = 0; i < n; i++)
        {
            int pos = -1, maxx = INT_MIN;
            for (int j = 0; j < m; j++)
            {
                if (process[i] <= dupmem[j] && allocated[j] == -1)
                {
                    int diff = dupmem[j] - process[i];
                    if (diff > maxx)
                    {
                        maxx = diff;
                        pos = j;
                    }
                }
            }
            if (pos != -1)
            {
                b[i] = pos + 1;
                dupmem[pos] -= process[i];
                allocated[pos] = 1;
            }
        }
        display(b);
    }

    void nextFit()
    {
        int dupmem[m];
        int allocated[m];
        int b[n];

        for (int i = 0; i < m; i++)
        {
            dupmem[i] = memory[i];
            allocated[i] = -1;
        }
        for (int i = 0; i < n; i++)
        {
            b[i] = -1;
        }

        int z = 0;
        // int start;
        for (int i = 0; i < n; i++)
        {
            // start = z;
            int c = 0;
            for (int j = z; j < m; j++)
            {
                if (process[i] <= dupmem[j] && allocated[j] == -1)
                {
                    dupmem[j] -= process[i];
                    b[i] = j + 1;
                    allocated[j] = 1;
                    z = j + 1;
                    if (z == m)
                    {
                        z = 0;
                    }
                    break;
                }
                c++;
                if (j == m - 1)
                {
                    j = 0;
                }
                if (c == n - 1)
                {
                    break;
                }
            }
        }
        display(b);
    }
};

int main()
{
    Memory m;

    m.input();

    cout << "\n------First fit-----\n";
    m.firstFit();
    cout << "\n------Best fit-----\n";
    m.bestFit();
    cout << "\n------Worst fit-----\n";
    m.worstFit();
    cout << "\n------Next fit-----\n";
    m.nextFit();
}
