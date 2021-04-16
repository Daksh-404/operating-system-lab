#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
class pcb
{
    public:
        int arrivalTime;
        int burstTime;
        int priority; //remember lower the number, higher is the priority
        int id;
        int startTime;
        int waitingTime;
        int turnAroundTime;
        pcb(int a,int b,int p,int i,int s,int w,int t)
        {
            arrivalTime=a;
            burstTime=b;
            priority=p;
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
            if(p1.arrivalTime!=p2.arrivalTime) return p1.arrivalTime>p2.arrivalTime;
            else return p1.priority>p2.priority;
        }
};
int main()
{
    //this is the code for priority schedueling

    cout<<"Enter the number of processes:\n";
    int n;
    cin>>n;

    cout<<"Enter the arrival time, the burst time and the priority in this respective order for each process:\n";
    int a,b,p;
    vector<pcb>readyQueueMain(n,pcb(0,0,0,0,0,0,0));
    for(int i=1;i<=n;i++)
    {
        cout<<"For P"<<i<<" : ";
        cin>>a>>b>>p;
        readyQueueMain[i-1].arrivalTime=a;
        readyQueueMain[i-1].burstTime=b;
        readyQueueMain[i-1].priority=p;
        readyQueueMain[i-1].id=i;
        readyQueueMain[i-1].startTime=readyQueueMain[i-1].waitingTime=readyQueueMain[i-1].turnAroundTime=0;
    }

    vector<pcb>readyQueue(readyQueueMain.begin(),readyQueueMain.end());
    //sorting the pcbs according to their arrivals times
    // using the lambda function
    sort(readyQueue.begin(),readyQueue.end(),[](pcb const& lhs, pcb const& rhs) {
      return lhs.arrivalTime < rhs.arrivalTime;
   });


    //now ready queue has been intialized with the process
    //control blocks, and is ready to be called by the processor

    //non pre emptive schedueling applied

    int endTime=readyQueue[0].arrivalTime;
    int start=0;
    int end=0;

    priority_queue<pcb,vector<pcb>,comparePriorities>rq;

    rq.push(readyQueue[0]);
    while(!rq.empty())
    {
        end=start+1;
        //adding elements with the same arrival times
        while(end<n&&readyQueue[end].arrivalTime==readyQueue[start].arrivalTime)
        {
            rq.push(readyQueue[end]);
            end++;
        }

        //taking the process with highest priority and
        // calculating end time using it's parameters

        pcb proc=rq.top();
        rq.pop();

        int idx=proc.id;
        idx--;
        readyQueueMain[idx].startTime=endTime;
        readyQueueMain[idx].waitingTime=readyQueueMain[idx].startTime-readyQueueMain[idx].arrivalTime;
        readyQueueMain[idx].turnAroundTime=readyQueueMain[idx].waitingTime+readyQueueMain[idx].burstTime;
        //cout<<readyQueueMain[idx].turnAroundTime<<endl;
        endTime=readyQueueMain[idx].startTime+readyQueueMain[idx].burstTime;
        //cout<<endTime<<endl;
        //moving forward
        start=end;
        if(start<n) rq.push(readyQueue[start]);
    }
    
    //reaaranging it in terms of ids
    sort(readyQueueMain.begin(),readyQueueMain.end(),[](const pcb&lhs,const pcb& rhs)
    {   
        return lhs.id<rhs.id;
    });

    double totalWaitingTime,totalTurnAroundTime,avgW,avgT;
    cout<<"Process\t\tArrival Time\t\tBurst Time\t\tPriority\t\tWaiting Time\t\tTurnaround Time\n";
    for(int i=1;i<=n;i++)
    {
        cout<<"P"<<i<<":\t\t "<<readyQueueMain[i-1].arrivalTime<<"\t\t\t"<<readyQueueMain[i-1].burstTime<<"\t\t\t"<<readyQueueMain[i-1].priority<<"\t\t\t"<<readyQueueMain[i-1].waitingTime<<"\t\t\t"<<readyQueueMain[i-1].turnAroundTime<<endl;
        totalTurnAroundTime+=readyQueueMain[i-1].turnAroundTime;
        totalWaitingTime+=readyQueueMain[i-1].waitingTime;
    }

    avgW=totalWaitingTime/(double)n;
    avgT=totalTurnAroundTime/(double)n;

    cout<<"Average waiting time: "<<avgW<<endl;
    cout<<"Average turnaround time: "<<avgT<<endl;

    
    return 0;
}