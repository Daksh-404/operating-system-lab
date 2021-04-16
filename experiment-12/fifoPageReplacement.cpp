#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<queue>
using namespace std;

int pageFaults(vector<int>pages,int capacity)
{
    //maximum capacity= capacity
    queue<int>fifoQueue;
    map<int,bool>isPresent;
    int numPagefaults=0;

    for(int i=0;i<pages.size();i++)
    {
        if(fifoQueue.size()>=capacity)
        {
            //just see if it's a hit
            if(!isPresent[pages[i]])
            {
                int id=fifoQueue.front();
                fifoQueue.pop();
                isPresent[id]=false;
                fifoQueue.push(pages[i]);
                isPresent[pages[i]]=true;
                numPagefaults++;
            }
        }
        else
        {
            if(!isPresent[pages[i]])
            {
                fifoQueue.push(pages[i]);
                isPresent[pages[i]]=true;
                numPagefaults++;
            }
        }
    }

    return numPagefaults;
}

int main()
{
    int capacity,total;
    vector<int>pages;

    cout<<"Enter the capacity of the FIFO queue:\n";
    cin>>capacity;
    cout<<"Enter the size of page replacement reference string:\n";
    cin>>total;
    cout<<"Enter the page replacement reference string:\n";

    int ref;
    for(int i=0;i<total;i++)
    {
        cin>>ref;
        pages.push_back(ref);
    }
    
    cout<<endl;
    cout<<"The number of page faults occuring in FIFO Replacement Algorithm are: "<<pageFaults(pages,capacity)<<endl;
    return 0;
}

/*Enter the capacity of the FIFO queue:
4
Enter the size of page replacement reference string:
13
Enter the page replacement reference string:
7 0 1 2 0 3 0 4 2 3 0 3 2*/