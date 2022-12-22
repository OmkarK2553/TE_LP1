#include <bits/stdc++.h>
using namespace std;

class memPlace
{
    int n_mem, n_proc;
    int memory[100], process[100];

public:
    void input()
    {
        cout << "Enter the number of memory blocks: ";
        cin >> n_mem;

        for (int i = 0; i < n_mem; i++)
        {
            cout << "Enter the size of memory block no " << i + 1 << ": ";
            cin >> memory[i];
        }

        cout << "Enter the number of processes: ";
        cin >> n_proc;

        for (int i = 0; i < n_proc; i++)
        {
            cout << "Enter the size of process no " << i + 1 << ": ";
            cin >> process[i];
        }
    }

    void firstFit()
    {
        int dup_memory[n_mem];
        int dup_memory2[n_mem];
        int b[n_mem];

        for (int i = 0; i < n_mem; i++)
        {
            dup_memory[i] = memory[i];
            dup_memory2[i] = -2;
            b[i] = -1;
        }

        for (int i = 0; i < n_proc; i++)
        {
            for (int j = 0; j < n_mem; j++)
            {
                if (process[i] <= dup_memory[j] && dup_memory2[j] == -2)
                {
                    dup_memory[j] -= process[i];
                    dup_memory2[j] = -1;
                    b[i] = j + 1; // size of b doubtful
                    break;
                }
            }
        }
        cout << "Available memory on each block: ";
        for (int i = 0; i < n_mem; i++)
        {
            cout << dup_memory[i] << " ";
        }
        cout << "\n";

        cout << "Process no\tProcess size\tBlock no\n";
        for (int i = 0; i < n_proc; i++)
        {
            if (b[i] == -1)
            {
                cout << i + 1 << "\t" << process[i] << "\t  "
                     << "Not allocated"
                     << "\n";
            }
            else
            {
                cout << i + 1 << "\t" << process[i] << "\t\t  "
                     << b[i] << "\n";
                ;
            }
        }
        cout << "\n";
    }

    void bestFit()
    {
        int dup_memory[n_mem];
        int dup_memory2[n_mem];
        int b[n_mem];

        for (int i = 0; i < n_mem; i++)
        {
            dup_memory[i] = memory[i];
            dup_memory2[i] = -2;
            b[i] = -1;
        }

        for (int i = 0; i < n_proc; i++)
        {
            int pos = -1;
            int minn = INT_MAX;

            for (int j = 0; j < n_mem; j++)
            {
                if (process[i] <= dup_memory[j] && dup_memory2[j] == -2)
                {
                    int diff = dup_memory[j] - process[i];

                    if (diff < minn)
                    {
                        minn = diff;
                        pos = j;
                    }
                }
            }
            if (pos != -1)
            {
                dup_memory[pos] -= process[i];
                dup_memory2[pos] = -1;
                b[i] = pos + 1;
            }
        }

        cout << "Available memory on each block: ";
        for (int i = 0; i < n_mem; i++)
        {
            cout << dup_memory[i] << " ";
        }
        cout << "\n";

        cout << "Process no\tProcess size\tBlock no\n";
        for (int i = 0; i < n_proc; i++)
        {
            if (b[i] == -1)
            {
                cout << i + 1 << "\t" << process[i] << "\t  "
                     << "Not allocated"
                     << "\n";
            }
            else
            {
                cout << i + 1 << "\t" << process[i] << "\t\t  "
                     << b[i] << "\n";
                ;
            }
        }
        cout << "\n";
    }

    void worstFit()
    {
        int dup_memory[n_mem];
        int dup_memory2[n_mem];
        int b[n_mem];

        for (int i = 0; i < n_mem; i++)
        {
            dup_memory[i] = memory[i];
            dup_memory2[i] = -2;
            b[i] = -1;
        }

        for (int i = 0; i < n_proc; i++)
        {
            int pos = -1;
            int maxx = INT_MIN;

            for (int j = 0; j < n_mem; j++)
            {
                if (process[i] <= dup_memory[j] && dup_memory2[j] == -2)
                {
                    int diff = dup_memory[j] - process[i];
                    if (maxx < diff)
                    {
                        maxx = diff;
                        pos = j;
                    }
                }
            }
            if (pos != -1)
            {
                dup_memory[pos] -= process[i];
                dup_memory2[pos] = -1;
                b[i] = pos + 1;
            }
        }

        cout << "Available memory on each block: ";
        for (int i = 0; i < n_mem; i++)
        {
            cout << dup_memory[i] << " ";
        }
        cout << "\n";

        cout << "Process no\tProcess size\tBlock no\n";
        for (int i = 0; i < n_proc; i++)
        {
            if (b[i] == -1)
            {
                cout << i + 1 << "\t" << process[i] << "\t  "
                     << "Not allocated"
                     << "\n";
            }
            else
            {
                cout << i + 1 << "\t" << process[i] << "\t\t  "
                     << b[i] << "\n";
                ;
            }
        }
        cout << "\n";
    }

    void nextFit()
    {
        int dup_memory[n_mem];
        int dup_memory2[n_mem];
        int b[n_mem];

        for (int i = 0; i < n_mem; i++)
        {
            dup_memory[i] = memory[i];
            dup_memory2[i] = -2;
            b[i] = -1;
        }

        int z = -1; // to keep the track of alloted memory..so z+1 will be the starting point of next
        for (int i = 0; i < n_proc; i++)
        {
            int j; // starting point of next;
            if (z == (n_mem - 1))
            {
                j = 0; // to last, next will start from first
            }
            else
            {
                j = z + 1;
            }

            int count = 0;         // to maintain count of processes (not to go in infinite loop)
            while (count != n_mem) // count doubtful
            {
                if (process[i] <= dup_memory[j] && dup_memory2[j] == -2)
                {
                    dup_memory[j] -= process[i];
                    dup_memory2[j] = -1;
                    z = j;
                    break;
                }
                count++;
                j++;
            }
            if (count != n_mem)
            {
                b[i] = z + 1;
            }
        }

        cout << "Available memory on each block: ";
        for (int i = 0; i < n_mem; i++)
        {
            cout << dup_memory[i] << " ";
        }
        cout << "\n";

        cout << "Process no\tProcess size\tBlock no\n";
        for (int i = 0; i < n_proc; i++)
        {
            if (b[i] == -1)
            {
                cout << i + 1 << "\t" << process[i] << "\t  "
                     << "Not allocated"
                     << "\n";
            }
            else
            {
                cout << i + 1 << "\t" << process[i] << "\t\t  "
                     << b[i] << "\n";
                ;
            }
        }
        cout << "\n";
    }
};

int main()
{
    memPlace m;

    m.input();

    cout << "\n--------------------FIRST FIT------------------------\n";
    m.firstFit();

    cout << "\n--------------------BEST FIT------------------------\n";
    m.bestFit();

    cout << "\n--------------------WORST FIT------------------------\n";
    m.worstFit();

    cout << "\n--------------------NEXT FIT------------------------\n";
    m.nextFit();

    return 0;
}