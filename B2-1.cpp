#include <bits/stdc++.h>
using namespace std;

class Scheduling
{
    int n;
    vector<int> at,bt,pr;

    public:

    Scheduling()
    {
        n = 0;
        at.resize(n);
        bt.resize(n);
        pr.resize(n);
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
        for(int i=0;i<n;i++){
            for(int j=0;j<n-i-1;j++){
                if(at[j]>at[j+1]){
                    swap(at[j],at[j+1]);
                    swap(bt[j], bt[j + 1]);
                    swap(pr[j], pr[j + 1]);
                }
            }
        }

        vector<int> wt(n),tat(n),ct(n);

        wt[0] = 0;
        tat[0] = wt[0]+bt[0];
        ct[0] = tat[0]+at[0];

        for(int i=1;i<n;i++){
            wt[i] = (wt[i-1]+bt[i-1]+at[i-1])-at[i];
            if(wt[i]<0)
                wt[i]=0;
            tat[i] = wt[i]+bt[i];
            ct[i] = tat[i]+at[i];
        }

        float total_wait=0,total_turn=0,avg_wait,avg_turn;
        for(int i=0;i<n;i++){
            total_wait+=wt[i];
            total_turn+=tat[i];
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

        vector<int> wt(n),tat(n),ct(n),rembt(n);

        for(int i=0;i<n;i++){
            rembt[i] = bt[i];
        }

        int pdone=0,minn=INT_MAX,selected,currTime=0;
        bool check=false;

        while(pdone!=n){
            for(int i=0;i<n;i++){
                if(at[i]<=currTime && rembt[i]<minn && rembt[i]>0){
                    check=true;
                    selected=i;
                    minn=rembt[i];
                }
            }

            if(!check){
                currTime++;
                continue;
            }

            rembt[selected]--;
            minn = rembt[selected];

            if(rembt[selected]==0){
                check=false;
                minn=INT_MAX;
                pdone++;

                int finishtime = currTime+1;
                wt[selected] = finishtime-bt[selected]-at[selected];
                if(wt[selected]<0)
                    wt[selected] = 0;
                tat[selected] = bt[selected]+wt[selected];
                ct[selected] = finishtime;
            }
            currTime++;
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

        int pdone=0,currtime=0,selected,maxx=INT_MIN;
        bool check=false;

        while(pdone!=n){
            for(int i=0;i<n;i++){
                if(at[i]<=currtime && pr[i]>maxx&&rembt[i]>0){
                    selected=i;
                    check=true;
                    maxx=pr[i];
                }
            }

            if(!check){
                currtime++;
                continue;
            }

            currtime += rembt[selected];
            rembt[selected] = 0;
            pdone++;
            check = false;
            maxx=INT_MIN;

            int finishtime = currtime;
            wt[selected] = finishtime-at[selected]-bt[selected];
            if(wt[selected]<0)
                wt[selected] = 0;
            tat[selected] = bt[selected]+wt[selected];
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
        cin>>tc;

        int currtime = at[0];

        list<int> q;
        q.push_back(0);

        while(!q.empty()){
            int ind = q.front();
            q.pop_front();

            if(rembt[ind]<=tc){
                currtime += rembt[ind];
                rembt[ind] = 0;

                wt[ind] = currtime-at[ind]-bt[ind];
                tat[ind] = wt[ind]+bt[ind];
                ct[ind] = currtime;
            }
            else{
                currtime+=tc;
                rembt[ind]-=tc;
            }

            for(int i=0;i<n;i++){
                if(i!=ind && at[i]<=currtime && rembt[i]>0){
                    // q.push_back(i);
                    auto itr = find(q.begin(), q.end(), i);
                    if (itr == q.end())
                    {
                        q.push_back(i);
                    }
                }
            }

            if(rembt[ind]>0){
                q.push_back(ind);
            }
        }
    }
};