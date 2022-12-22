#include <bits/stdc++.h>
using namespace std;

class Schedular
{
    int n;
    int arrivalTime[100], burstTime[100], priority[100];

public:
    Schedular()
    {
        n = 0;
    }
    void input()
    {
        cout << "Enter number of processes:" << endl;
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cout << "Enter the arrival time:" << endl;
            cin >> arrivalTime[i];
            cout << "Enter burst time:" << endl;
            cin >> burstTime[i];
            cout << "Enter priority:" << endl;
            cin >> priority[i];
        }
    }
    void fcfs()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (arrivalTime[j] > arrivalTime[j + 1])
                {
                    swap(arrivalTime[j], arrivalTime[j + 1]);
                    swap(burstTime[j], burstTime[j + 1]);
                    swap(priority[j], priority[j + 1]);
                }
            }
        }
        vector<int> waitingTime(n + 1);

        int totalWaitingTime = 0;
        waitingTime[0] = 0;
        int totalTurnAroundTime = 0;
        vector<int> turnAroundTime(n + 1);
        turnAroundTime[0] = waitingTime[0] + burstTime[0];
        int previous = arrivalTime[0] + burstTime[0];
        totalTurnAroundTime += turnAroundTime[0];
        for (int i = 1; i < n; i++)
        {
            waitingTime[i] = max(0, previous - arrivalTime[i]); // if the waiting time goes negative , then the process is already started before entering in a ready queue
            if (previous - arrivalTime[i] < 0)
            {
                previous = arrivalTime[i];
            }
            previous += burstTime[i];
            totalWaitingTime += waitingTime[i];
            turnAroundTime[i] = waitingTime[i] + burstTime[i]; // turn around time
            totalTurnAroundTime += turnAroundTime[i];
        }
        float averageWaitingTime = float(totalWaitingTime) / (float)n;
        float averageTurnAroundTime = float(totalTurnAroundTime) / (float)n;
        cout << "Process No"
             << " "
             << "Arrival Time"
             << " "
             << "Burst Time"
             << " "
             << "Waiting Time"
             << " "
             << "TurnAround Time" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << i + 1 << "\t\t" << arrivalTime[i] << "\t\t" << burstTime[i] << "\t\t" << waitingTime[i] << "\t\t" << turnAroundTime[i] << endl;
        }
        cout << "Average Waiting Time:" << averageWaitingTime << endl;
        cout << "Average Turn Around Time:" << averageTurnAroundTime << endl;
    }
    void sjf()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (arrivalTime[j] > arrivalTime[j + 1])
                {
                    swap(arrivalTime[j], arrivalTime[j + 1]);
                    swap(burstTime[j], burstTime[j + 1]);
                    swap(priority[j], priority[j + 1]);
                }
            }
        }
        int process_completed = 0; // to check how many processes are completed
        int minTime = INT_MAX;
        int finishTime = 0;
        int shortest = 0;
        int currentTime = 0;
        vector<int> remainingBurstTime(n + 1);
        for (int i = 0; i < n; i++)
        {
            remainingBurstTime[i] = burstTime[i];
        }
        vector<int> waitingTime(n + 1), turnAroundTime(n + 1);
        bool check = false; // to check if we found a process with a less burst time than current running process's remaining burst time
        while (process_completed != n)
        {
            for (int i = 0; i < n; i++)
            {
                if (arrivalTime[i] <= currentTime && remainingBurstTime[i] < minTime && remainingBurstTime[i] > 0)
                {
                    minTime = remainingBurstTime[i];
                    shortest = i;
                    check = true;
                }
            }
            // if there is no process whose remaining burst time is less than current process's remaining time then go to next time
            if (!check)
            {
                currentTime++;
                continue;
            }
            remainingBurstTime[shortest]--; // decrement the burst time of the process
            minTime = remainingBurstTime[shortest];
            if (minTime == 0)
            {
                minTime = INT_MAX;
            }
            if (remainingBurstTime[shortest] == 0)
            {
                process_completed++;
                check = false;
                finishTime = currentTime + 1;
                waitingTime[shortest] = finishTime - burstTime[shortest] - arrivalTime[shortest];
                waitingTime[shortest] = max(0, waitingTime[shortest]);
            }
            currentTime++;
        }

        int totalTurnAroundTime = 0, totalWaitingTime = 0;
        for (int i = 0; i < n; i++)
        {
            turnAroundTime[i] = waitingTime[i] + burstTime[i];
            totalWaitingTime += waitingTime[i];
            totalTurnAroundTime += turnAroundTime[i];
        }
        float averageWaitingTime = float(totalWaitingTime) / (float)n;
        float averageTurnAroundTime = float(totalTurnAroundTime) / (float)n;
        cout << "Process No"
             << " "
             << "Arrival Time"
             << " "
             << "Burst Time"
             << " "
             << "Waiting Time"
             << " "
             << "TurnAround Time" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << i + 1 << "\t\t" << arrivalTime[i] << "\t\t" << burstTime[i] << "\t\t" << waitingTime[i] << "\t\t" << turnAroundTime[i] << endl;
        }
        cout << "Average Waiting Time:" << averageWaitingTime << endl;
        cout << "Average Turn Around Time:" << averageTurnAroundTime << endl;
    }
    void priorityNonPreemptive()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (priority[j] > priority[j + 1])
                {
                    swap(arrivalTime[j], arrivalTime[j + 1]);
                    swap(burstTime[j], burstTime[j + 1]);
                    swap(priority[j], priority[j + 1]);
                }
            }
        }
        vector<int> waitingTime(n + 1), turnAroundTime(n + 1);
        int completedProcess = 0;
        int currentTime = 0;
        vector<int> remainingBurstTime(n + 1);
        for (int i = 0; i < n; i++)
        {
            remainingBurstTime[i] = burstTime[i];
        }
        int totalWaitingTime = 0, totalTurnAroundTime = 0;
        int totalBurstTime = burstTime[0];
        while (completedProcess < n)
        {
            int mn = INT_MAX;
            int pos = -1;
            for (int i = 0; i < n; i++)
            {
                if (arrivalTime[i] <= currentTime && priority[i] < mn && remainingBurstTime[i] > 0)
                {
                    mn = priority[i];
                    pos = i;
                }
            }
            if (pos != -1)
            {
                currentTime += remainingBurstTime[pos];
                remainingBurstTime[pos] = 0;
                completedProcess++;
                turnAroundTime[pos] = currentTime - arrivalTime[pos];
                totalTurnAroundTime += turnAroundTime[pos];
                waitingTime[pos] = turnAroundTime[pos] - burstTime[pos];
                totalWaitingTime += waitingTime[pos];
            }
            else
            {
                currentTime++;
            }
        }
        float averageWaitingTime = float(totalWaitingTime) / (float)n;
        float averageTurnAroundTime = float(totalTurnAroundTime) / (float)n;
        cout << "Process No"
             << " "
             << "Arrival Time"
             << " "
             << "Burst Time"
             << " "
             << "Waiting Time"
             << " "
             << "TurnAround Time" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << i + 1 << "\t\t" << arrivalTime[i] << "\t\t" << burstTime[i] << "\t\t" << waitingTime[i] << "\t\t" << turnAroundTime[i] << endl;
        }
        cout << "Average Waiting Time:" << averageWaitingTime << endl;
        cout << "Average Turn Around Time:" << averageTurnAroundTime << endl;
    }
    void RoundRobbins()
    {
        cout << "Enter a quantum:" << endl;
        int q;
        cin >> q;
        queue<int> ready_queue; // to store process in ready state
        vector<int> remainingBurstTime(n + 1);
        for (int i = 0; i < n; i++)
        {
            remainingBurstTime[i] = burstTime[i];
        }
        vector<int> waitingTime(n + 1);
        vector<bool> isPresent(n + 1, false);
        // to check if a process is already in a ready queue or not
        int currentTime = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            currentTime = min(currentTime, arrivalTime[i]);
        }
        vector<pair<int, int>> temp;
        for (int i = 0; i < n; i++)
        {
            if (arrivalTime[i] <= currentTime)
            {
                isPresent[i] = true;
                temp.push_back({arrivalTime[i], i});
            }
        }
        int completedProcesses = 0;
        // sorting the processes according to arrivalTime and adding all processes to queue
        sort(temp.begin(), temp.end());
        for (auto &x : temp)
        {
            ready_queue.push(x.second);
        }
        while (completedProcesses != n)
        {
            int first = -1; // to point to the first process in queue
            if (!ready_queue.empty())
            {
                first = ready_queue.front();
                ready_queue.pop();
                if (remainingBurstTime[first] <= q)
                {
                    currentTime += remainingBurstTime[first];
                    remainingBurstTime[first] = 0;
                    completedProcesses++;
                    waitingTime[first] = currentTime - burstTime[first] - arrivalTime[first];
                }
                else
                {
                    currentTime += q;
                    remainingBurstTime[first] -= q;
                }
            }
            temp.clear();
            for (int i = 0; i < n; i++)
            {
                // not present in ready queue already
                // arrival time is less than current time
                // must have burst time remaining
                if (arrivalTime[i] <= currentTime && !isPresent[i] && remainingBurstTime[i] > 0)
                {
                    temp.push_back({arrivalTime[i], i});
                    isPresent[i] = true;
                }
            }
            sort(temp.begin(), temp.end());
            for (auto &x : temp)
            {
                ready_queue.push(x.second);
            }
            if (first != -1)
            {
                isPresent[first] = false;
                if (remainingBurstTime[first] > 0)
                {
                    ready_queue.push(first);
                    isPresent[first] = true;
                }
            }
        }
        vector<int> turnAroundTime(n + 1);
        int totalTurnAroundTime = 0, totalWaitingTime = 0;
        for (int i = 0; i < n; i++)
        {
            turnAroundTime[i] = waitingTime[i] + burstTime[i];
            totalWaitingTime += waitingTime[i];
            totalTurnAroundTime += turnAroundTime[i];
        }
        float averageWaitingTime = float(totalWaitingTime) / (float)n;
        float averageTurnAroundTime = float(totalTurnAroundTime) / (float)n;
        cout << "Process No"
             << " "
             << "Arrival Time"
             << " "
             << "Burst Time"
             << " "
             << "Waiting Time"
             << " "
             << "TurnAround Time" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << i + 1 << "\t\t" << arrivalTime[i] << "\t\t" << burstTime[i] << "\t\t" << waitingTime[i] << "\t\t" << turnAroundTime[i] << endl;
        }
        cout << "Average Waiting Time:" << averageWaitingTime << endl;
        cout << "Average Turn Around Time:" << averageTurnAroundTime << endl;
    }
};

int main()
{
    Schedular s;
    s.input();
    s.fcfs();
    s.sjf();
    s.priorityNonPreemptive();
    s.RoundRobbins();
    return 0;
}