#include <iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<map>

#define float double
#define sz 100005
#define all(a) a.begin(), a.end()
#define mod 1000000007
#define vi vector<int>
#define vvi vector<vector<int>>
#define debug cout << "here" << endl;
#define rep(i, n) for (int i = 0; i < n; ++i)
#define pb push_back
#define ff first
#define ss second
#define pi pair<int, int>
using namespace std;

struct req
{
    int id;
    bool modified;
    bool used;
};

void simulate(vector<req> &request, int numRequest, int numFrames)
{
    int id = 0;
    int pageFaultCount = 0;
    map<int, bool> inMemory;
    int filled = 0;
    vector<req> frames(numFrames, {-1, 0, 0});
    for (auto node : request)
    {
        cout << node.id << " ----> ";
        filled++;

        if (inMemory[node.id])
        {
            rep(i, numFrames)
            {
                if (frames[i].id == node.id)
                {
                    frames[i].used = 1;
                    frames[i].modified = (frames[i].modified||node.modified);
                    inMemory[node.id] = true;
                    break;
                }
            }
        }
        else if (filled <= numFrames)
        {
            cout << "(PAGE FAULT) ";
            pageFaultCount++;
            rep(i, numFrames)
            {
                if (frames[i].id == -1)
                {
                    frames[i] = {node.id, node.modified, 1};
                    inMemory[node.id] = true;
                    break;
                }
            }
        }
        else
        {
            cout << "(PAGE FAULT) ";
            pageFaultCount++;
            inMemory[node.id] = true;
            bool done = false;
            rep(p, numFrames)
            {
                if (frames[id].used == false && frames[id].modified == false)
                {
                    inMemory[frames[id].id] = false;
                    frames[id] = {node.id, node.modified, 1};
                    done = true;
                    id = (id + 1) % numFrames;
                    break;
                }
                else
                {
                    id = (id + 1) % numFrames;
                }
            }
            if (!done)
            {
                rep(p, 2 * numFrames)
                {
                    if (frames[id].used == false && frames[id].modified == 1)
                    {
                        inMemory[frames[id].id] = false;
                        frames[id] = {node.id, node.modified, 1};
                        done = true;
                        id = (id + 1) % numFrames;
                        break;
                    }
                    else
                    {
                        frames[id].used = false;
                        id = (id + 1) % numFrames;
                    }
                }
            }
        }
        cout << "[ ";
        for (auto val : frames)
        {
            if (val.id == -1)
                cout << " - ";
            else
                cout << val.id << " ";
        }
        cout << "]";
        cout << endl;
    }
    cout << "Total number of page faults are " << pageFaultCount << endl;
}

int32_t main()
{
    int numFrames;
    cout << "Enter the number of frames" << endl;
    cin >> numFrames;

    cout << "Enter the number memory request " << endl;
    int numRequest;
    cin >> numRequest;

    cout << "Enter the request" << endl;
    vector<req> request(numRequest, {0, 0, 0});
    rep(i, numRequest) cin >> request[i].id;

    cout << "Enter which frames have been modified " << endl;
    rep(i, numRequest) cin >> request[i].modified;

    simulate(request, numRequest, numFrames);
}