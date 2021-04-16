#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;

void findingBestFit(vector<int>&block,vector<int>&process)
{
    vector<pair<int,int> >b;
    vector<pair<int,int> >p;

    //storing the indicies to create the table later
    for(int i=0;i<process.size();i++) p.push_back({process[i],i});
    for(int i=0;i<block.size();i++) b.push_back({block[i],i});

    sort(b.begin(),b.end());
    sort(p.begin(),p.end());

    int blocksPtr=0;
    int procPtr=0;

    map<int,int>blocksAssigned;
    //intializing with -1
    for(int i=0;i<p.size();i++) blocksAssigned[i]=-1;

    //using two pointer approach to find the best fitting value
    while(blocksPtr<b.size()&&procPtr<p.size())
    {
        if(b[blocksPtr].first<p[procPtr].first)
        {
            blocksPtr++;
        }

        else if(b[blocksPtr].first>=p[procPtr].first)
        {
            blocksAssigned[p[procPtr].second]=b[blocksPtr].second;
            blocksPtr++;
            procPtr++;
        }
    }

    //printing the output table

    cout<<"Process No.\t"<<"Process Size\t"<<"Block Size\t"<<"Block No.\n";

    for(int i=0;i<process.size();i++)
    {
        if(blocksAssigned[i]!=-1)
        {
            cout<<i+1<<"\t\t"<<process[i]<<"\t\t"<<block[blocksAssigned[i]]<<"\t\t"<<blocksAssigned[i]+1<<endl;
        }
        else
        {
             cout<<i+1<<"\t\t"<<process[i]<<"\t\t"<<"Nil"<<"\t\t"<<"Nil"<<endl;
        }
    }

    return;
}

int main()
{
    vector<int>blocks;
    vector<int>processes;

    int b,p;
    cout<<"Enter number of partition blocks:\n";
    cin>>b;
    cout<<"Enter number of processes:\n";
    cin>>p;

    cout<<"Enter the the size of all the partitions:\n";
    
    int blockSize;
    int reqSize;
    for(int i=0;i<b;i++)
    {
        cin>>blockSize;
        blocks.push_back(blockSize);
    }

    cout<<"Enter the the size required by the processes:\n";

    for(int i=0;i<p;i++)
    {
        cin>>reqSize;
        processes.push_back(reqSize);
    }


    findingBestFit(blocks,processes);
    return 0;
}

/*Test case
Enter number of partition blocks:
5
Enter number of processes:
4
Enter the the size of all the partitions:
100 500 200 300 600
Enter the the size required by the processes:
212 417 112 426

*/