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
        pcb(int a,int b,int i,int s,int w,int t)
        {
            arrivalTime=a;
            burstTime=b;
            id=i;
            startTime=s;
            waitingTime=w;
            turnAroundTime=t;
        }
};
class comparePriorities
{
    public:
        bool operator()(pcb const& p1, pcb const& p2)
        {
            return p1.burstTime>p2.burstTime;
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
    vector<pcb>readyQueue(n,pcb(0,0,0,0,0,0));
    map<int,vector<pcb> >checkArrivals;
    for(int i=1;i<=n;i++)
    {
        cout<<"For P"<<i<<" : ";
        cin>>a>>b;
        readyQueue[i-1].arrivalTime=a;
        readyQueue[i-1].burstTime=b;
        readyQueue[i-1].id=i;
        readyQueue[i-1].startTime=readyQueue[i-1].waitingTime=readyQueue[i-1].turnAroundTime=0;
        checkArrivals[a].push_back(readyQueue[i-1]);
        minArrivalTime=min(a,minArrivalTime);
    }


    //now ready queue has been intialized with the process
    //control blocks, and is ready to be called by the processor

    //non pre emptive schedueling applied

    priority_queue<pcb,vector<pcb>,comparePriorities>rq;
    
    int timeStep=minArrivalTime;

    int condnForNewProc=0;
    while(1)
    {
        //checking if their are process at this time step
        // if there are, I directly push them into the queue
        for(auto proc:checkArrivals[timeStep])
        {
            rq.push(proc);
        }

        //checking if I can pop a process from the queue
        if(timeStep>=condnForNewProc)
        {
            if(!rq.empty())
            {
                pcb proc=rq.top();
                int id=proc.id;
               
                if(timeStep>=readyQueue[id-1].arrivalTime)
                {
                    rq.pop();
                    readyQueue[id-1].waitingTime=timeStep-readyQueue[id-1].arrivalTime;
                    readyQueue[id-1].turnAroundTime=readyQueue[id-1].waitingTime+readyQueue[id-1].burstTime;  
                    condnForNewProc=timeStep+readyQueue[id-1].burstTime;   
                }      
            }
            else break;
        }

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