#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
int main()
{
    //this is the code for round robin schedueling

    cout<<"Enter the number of processes:\n";
    int n;
    cin>>n;

    cout<<"Enter the burst time :\n";
    int b;
    vector<int>burstTime(n,0);
    for(int i=1;i<=n;i++)
    {
        cout<<"For P"<<i<<" : ";
        cin>>b;
        burstTime[i-1]=b;
    }

    vector<int>bt(burstTime.begin(),burstTime.end());
    vector<int>waitingTime(n,0);
    vector<int>turnAroundTime(n,0);
    int quantam=2;
    int totalTime=0;

    while(1)
    {
        bool done=true;

        for(int i=0;i<n;i++)
        {
            if(bt[i]>0)
            {
                done=false;
                if(bt[i]>quantam)
                {
                    bt[i]-=quantam;
                    totalTime+=quantam;
                }
                else
                {
                    bt[i]=0;
                    totalTime+=(bt[i]);
                    turnAroundTime[i]=totalTime;
                    waitingTime[i]=turnAroundTime[i]-burstTime[i];
                }
            }
        }

        if(done==true) break;
    }


    cout<<"Process\t\tArrival Time\t\tBurst Time\t\tWaiting Time\t\tTurnaround Time\n";
    double totalWaitingTime,totalTurnAroundTime,avgW,avgT;
    for(int i=1;i<=n;i++)
    {
        cout<<"P"<<i<<":\t\t "<<"0"<<"\t\t\t"<<burstTime[i-1]<<"\t\t\t"<<waitingTime[i-1]<<"\t\t\t"<<turnAroundTime[i-1]<<endl;
        totalTurnAroundTime+=turnAroundTime[i-1];
        totalWaitingTime+=waitingTime[i-1];
    }

    avgW=totalWaitingTime/(double)n;
    avgT=totalTurnAroundTime/(double)n;

    cout<<"\nAverage waiting time: "<<avgW<<endl;
    cout<<"Average turnaround time: "<<avgT<<endl;

    
    return 0;
}