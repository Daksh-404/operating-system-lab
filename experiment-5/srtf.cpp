#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
class pcb
{
    public:
        int arrivalTime;
        int burstTime;
        int id;
        int startTime;
        int waitingTime;
        int turnAroundTime;
        int rem_bt;
        pcb(int a,int b,int i,int s,int w,int t,int rbt)
        {
            arrivalTime=a;
            burstTime=b;
            id=i;
            startTime=s;
            waitingTime=w;
            turnAroundTime=t;
            rem_bt=rbt;
        }
};
class comparePriorities
{
    public:
        bool operator()(pcb const& p1, pcb const& p2)
        {
            if(p1.rem_bt!=p2.rem_bt) return p1.rem_bt>p2.rem_bt;
            else return p1.id>p2.id;
        }
};
int main()
{
    //this is the code for priority schedueling

    cout<<"Enter the number of processes:\n";
    int n;
    cin>>n;

    cout<<"Enter the arrival time, the burst time in this respective order for each process:\n";
    int a,b;
    int minArrivalTime=(1e9);
    vector<pcb>readyQueue(n,pcb(0,0,0,0,0,0,0));
    map<int,vector<pcb> >checkArrivals;
    for(int i=1;i<=n;i++)
    {
        cout<<"For P"<<i<<" : ";
        cin>>a>>b;
        readyQueue[i-1].arrivalTime=a;
        readyQueue[i-1].burstTime=b;
        readyQueue[i-1].id=i-1;
        readyQueue[i-1].startTime=readyQueue[i-1].waitingTime=readyQueue[i-1].turnAroundTime=0;
        readyQueue[i-1].rem_bt=readyQueue[i-1].burstTime;
        checkArrivals[a].push_back(readyQueue[i-1]);
        minArrivalTime=min(a,minArrivalTime);
    }
    //sorting the pcbs according to their arrivals times
    // using the lambda function
   /*sort(readyQueue.begin(),readyQueue.end(),[](pcb const& lhs, pcb const& rhs) {
      return lhs.arrivalTime < rhs.arrivalTime;
   });*/


    //now ready queue has been intialized with the process
    //control blocks, and is ready to be called by the processor

    //non pre emptive schedueling applied

    /*int endTime=readyQueue[0].arrivalTime;
    int start=0;
    int end=0;*/

    priority_queue<pcb,vector<pcb>,comparePriorities>rq;
    
    int timeStep=minArrivalTime;
    //cout<<timeStep<<endl;
    //int condnForNewProc=0;
    int lastProcId=0;
    bool flag=false;
    while(1)
    {
        //checking if their are process at this time step
        // if there are, I directly push them into the queue
        for(auto proc:checkArrivals[timeStep])
        {
            rq.push(proc);
        }

        //for pre emptive, I need to see if 
        // there is a better priority

        if(!flag)
        {
            flag=true;
            lastProcId=rq.top().id;
            readyQueue[lastProcId].startTime=timeStep;
            rq.pop();
        }
        else if(!rq.empty())
        {
            pcb proc=rq.top();

            if(proc.rem_bt<readyQueue[lastProcId].rem_bt)
            {
                rq.pop();
                if(readyQueue[lastProcId].rem_bt>0)
                {
                    //readyQueue[lastProcId].rem_bt-=(timeStep-readyQueue[lastProcId].startTime);
                    rq.push(readyQueue[lastProcId]);
                }
                else
                {
                    readyQueue[lastProcId].turnAroundTime=timeStep-readyQueue[lastProcId].arrivalTime;
                    readyQueue[lastProcId].waitingTime=readyQueue[lastProcId].turnAroundTime-readyQueue[lastProcId].burstTime;
                }
                readyQueue[proc.id].startTime=timeStep;
                lastProcId=proc.id;
            }
            else
            {
                if(readyQueue[lastProcId].rem_bt<=0)
                {
                    readyQueue[lastProcId].turnAroundTime=timeStep-readyQueue[lastProcId].arrivalTime;
                    readyQueue[lastProcId].waitingTime=readyQueue[lastProcId].turnAroundTime-readyQueue[lastProcId].burstTime;
                    readyQueue[proc.id].startTime=timeStep;
                    lastProcId=proc.id;
                    rq.pop();
                }
            }
        }
        else
        {
            //cout<<timeStep<<endl;
            if(readyQueue[lastProcId].rem_bt<=0)
            {
                readyQueue[lastProcId].turnAroundTime=timeStep-readyQueue[lastProcId].arrivalTime;
                readyQueue[lastProcId].waitingTime=readyQueue[lastProcId].turnAroundTime-readyQueue[lastProcId].burstTime;
                break;
            }
        }

        readyQueue[lastProcId].rem_bt-=1;
        timeStep+=1;
    }
    
    //reaaranging it in terms of ids
    sort(readyQueue.begin(),readyQueue.end(),[](const pcb&lhs,const pcb& rhs)
    {   
        return lhs.id<rhs.id;
    });

    double totalWaitingTime,totalTurnAroundTime,avgW,avgT;
    cout<<"Process\t\tArrival Time\t\tBurst Time\t\tWaiting Time\t\tTurnaround Time\n";
    for(int i=1;i<=n;i++)
    {
        cout<<"P"<<i<<":\t\t "<<readyQueue[i-1].arrivalTime<<"\t\t\t"<<readyQueue[i-1].burstTime<<"\t\t\t"<<readyQueue[i-1].waitingTime<<"\t\t\t"<<readyQueue[i-1].turnAroundTime<<endl;
        totalTurnAroundTime+=readyQueue[i-1].turnAroundTime;
        totalWaitingTime+=readyQueue[i-1].waitingTime;
    }

    avgW=totalWaitingTime/(double)n;
    avgT=totalTurnAroundTime/(double)n;

    cout<<"Average waiting time: "<<avgW<<endl;
    cout<<"Average turnaround time: "<<avgT<<endl;

    
    return 0;
}