#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    //taking input the number of processes
    int numProcesses;
    cout<<"ENTER THE NUMBER OF PROCESSES TO BE SCHEDUELED:\n\n";
    cin>>numProcesses;

    vector<int>arrivalTime;
    vector<int>burstTime;
    vector<int>waitingTime;
    vector<int>turnAroundTime;

    //taking the input for arrival times and the burst times simultaneously 
    // for each and every process in any random order.
    cout<<"\n\nENTER THE ARRIVAL TIMES AND THE BURST TIME FOR THE PROCESSES IN ANY ORDER:\n\n";
    int incomingTime;
    int burstTiming;
    for(int i=1;i<=numProcesses;i++)
    {
        cout<<"Process "<<i<<" Arrival Time: ";
        cin>>incomingTime;
        arrivalTime.push_back(incomingTime);
        cout<<"Process "<<i<<" Burst Time: ";
        cin>>burstTiming;
        burstTime.push_back(burstTiming);
        cout<<endl;
    }
    vector<pair<int,int> >arrivalBurstPair;

    for(int i=0;i<numProcesses;i++) arrivalBurstPair.push_back({arrivalTime[i],burstTime[i]});

    //sorting on the basis of arrival time
    sort(arrivalBurstPair.begin(),arrivalBurstPair.end());

    //the waiting time for the first process is always going to be 0
    waitingTime.push_back(0);

    int endingTime=arrivalBurstPair[0].first+arrivalBurstPair[0].second;
    turnAroundTime.push_back(arrivalBurstPair[0].second);
    for(int j=1;j<numProcesses;j++)
    {
       if(arrivalBurstPair[j].first<endingTime)
       {
           waitingTime.push_back(endingTime-arrivalBurstPair[j].first);
           endingTime=endingTime+arrivalBurstPair[j].second;
           
       }
       else
       {
           waitingTime.push_back(0);
           endingTime=arrivalBurstPair[j].first+arrivalBurstPair[j].second;
       }

         //turnaround time=waiting Time+burstTime
        turnAroundTime.push_back(waitingTime[j]+arrivalBurstPair[j].second);
       
    }

    cout<<"\nProcess\t\tArrival Time\t\tBurst Time\tWaiting Time\tTurnaround Time\n";

    for(int k=0;k<numProcesses;k++)
    {
        cout<<"Process "<<k+1<<" :\t\t"<<arrivalBurstPair[k].first<<"\t\t"<<arrivalBurstPair[k].second<<"\t\t"<<waitingTime[k]<<"\t\t"<<turnAroundTime[k]<<endl;
    }
    cout<<endl;

    double avgWaitingTime=0;
    for(auto x:waitingTime) avgWaitingTime+=x;
    double avgTurnAroundTime=0;
    for(auto y:turnAroundTime) avgTurnAroundTime+=y;

    avgWaitingTime=(avgWaitingTime/(double)numProcesses);
    avgTurnAroundTime=(avgTurnAroundTime/(double)numProcesses);
    cout<<"Average Waiting Time : "<<avgWaitingTime<<endl;
    cout<<"Average Turnaround Time : "<<avgTurnAroundTime<<endl;
    return 0;
    
}