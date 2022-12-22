#include <bits/stdc++.h>
using namespace std;

#define MAX 50

class Election
{
    int n, coordinator, pStatus[MAX];

public:
    void input()
    {
        cout << "Enter the number of processes: ";
        cin >> n;

        for (int i = 1; i <= n; i++)
        {
            cout << "\nEnter if the process no " << i << " is active or not (0/1): ";
            cin >> pStatus[i];
            if (pStatus[i])
            {
                coordinator = i;
            }
        }
    }

    void display()
    {
        cout << "Processes: \t";
        for (int i = 1; i <= n; i++)
        {
            cout << i << "\t";
        }
        cout << "\n";
        cout << "Active: \t";
        for (int i = 1; i <= n; i++)
        {
            cout << pStatus[i] << "\t";
        }
        cout << "\n";
        cout << "--------------------------------------------\n";
        cout << "Coordinator is: " << coordinator << "\n";
    }

    void bully()
    {
        int crash, activate, gen_id, subcoordinator, ch, flag;

        do
        {
            /* code */

            cout << "\nWhat to do: \n1) Crash\n2) Activate\n3) Display\n4) Exit\n";
            cin >> ch;

            switch (ch)
            {
            case 1:
                cout << "Enter the process id to crash: ";
                cin >> crash;

                if (pStatus[crash])
                {
                    pStatus[crash] = 0;
                }
                else
                {
                    cout << "Process no " << crash << " is already inactive!\n";
                }

                do
                {
                    cout << "Enter the generator id: ";
                    cin >> gen_id;

                    if (gen_id == coordinator)
                    {
                        cout << "Coordinator cannot be the generator!";
                    }
                    if (pStatus[gen_id] == 0)
                    {
                        cout << "The process is inactive, so can't be the generator!";
                    }
                } while (gen_id == coordinator || pStatus[gen_id] == 0);

                flag = 0;
                if (crash == coordinator)
                {
                    for (int i = gen_id + 1; i <= n; i++)
                    {
                        cout << "Message sent from " << gen_id << " to " << i << "\n";

                        if (pStatus[i])
                        {
                            subcoordinator = i;
                            cout << "Reply sent from " << i << " to " << gen_id << "\n";
                            flag = 1;
                        }
                    }

                    if (flag == 1)
                    {
                        coordinator = subcoordinator;
                    }
                    else
                    {
                        coordinator = gen_id;
                    }
                }
                display();
                break;

            case 2:
                cout << "Enter the process to activate: ";
                cin >> activate;

                if (!pStatus[activate])
                {
                    pStatus[activate] = 1;
                }
                else
                {
                    cout << "Process no " << activate << " is already active!\n";
                }

                if (activate == n)
                {
                    coordinator = activate;
                    break;
                }

                flag = 0;
                for (int i = activate + 1; i <= n; i++)
                {
                    cout << "Message send from " << activate << " to " << i << "\n";

                    if (pStatus[i])
                    {
                        subcoordinator = i;
                        cout << "Reply send from " << i << " to " << activate << "\n";
                        flag = 1;
                    }
                }

                if (flag)
                {
                    coordinator = subcoordinator;
                }
                else
                {
                    coordinator = activate;
                }
                display();
                break;

            case 3:
                display();

            case 4:
                break;
            }
        } while (ch != 4);
    }

    void ring()
    {
        int crash, activate, gen_id, subcoordinator, ch;

        do
        {
            cout << "What to do: \n1) Crash\n2) Activate\n3) Display\n4) Exit\n";
            cin >> ch;

            switch (ch)
            {
            case 1:
                cout << "Enter the process id to crash: ";
                cin >> crash;

                if (pStatus[crash])
                {
                    pStatus[crash] = 0;
                }
                else
                {
                    cout << "Process no " << crash << " is already inactive!\n";
                }

                do
                {
                    cout << "Enter the generator id: ";
                    cin >> gen_id;
                    if (gen_id == coordinator)
                    {
                        cout << "The coordinator can't be the generator!\n";
                    }
                } while (gen_id == coordinator);

                if (crash == coordinator)
                {
                    subcoordinator = 1;
                    for (int i = 0; i < n + 1; i++)
                    {
                        int pid = (i + gen_id) % (n + 1);
                        if (pid != 0)
                        {
                            if (pStatus[pid] && subcoordinator < pid)
                            {
                                subcoordinator = pid;
                            }
                            cout << "Election message send from " << pid << ": #Msg" << subcoordinator << "\n";
                        }
                    }
                    coordinator = subcoordinator;
                }
                display();
                break;

            case 2:
                cout << "Enter the process to activate: ";
                cin >> activate;

                if (!pStatus[activate])
                {
                    pStatus[activate] = 1;
                }
                else
                {
                    cout << "Process no " << activate << " is aready active!";
                }

                subcoordinator = activate;
                for (int i = 0; i < n + 1; i++)
                {
                    int pid = (i + activate) % (n + 1);
                    if (pid != 0)
                    {
                        if (pStatus[pid] && subcoordinator < pid)
                        {
                            subcoordinator = pid;
                        }
                        cout << "Election message sent from " << pid << ": #Msg" << subcoordinator << "\n";
                    }
                }
                coordinator = subcoordinator;
                display();
                break;

            case 3:
                display();
                break;

            case 4:
                break;
            }
        } while (ch != 4);
    }

    void mainFunc()
    {
        int choice;
        do
        {
            cout << "\nWhich operation to perform: \n1) Bully\n2) Ring\n3) Display\n4) Exit\n";
            cin >> choice;

            switch (choice)
            {
            case 1:
                bully();
                break;
            case 2:
                ring();
            case 3:
                display();
            }
        } while (choice != 4);
    }
};

int main()
{
    Election e;

    e.input();
    e.display();
    e.mainFunc();
}