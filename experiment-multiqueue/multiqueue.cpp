#include<iostream>
#include<climits>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

struct task {
   int id, arrival, burst;
};

struct executedtask {
   int id, time, queue;
};

struct cmp_arrival_queue {
   bool operator() (const task &t1, const task &t2) {
       if (t1.arrival == t2.arrival)
           return t1.id > t2.id;
       return t1.arrival > t2.arrival;
   }
};

bool cmp_arrival (const task &t1, const task &t2) {
   if (t1.arrival == t2.arrival)
       return t1.id < t2.id;
   return t1.arrival < t2.arrival;
}

vector<executedtask> orderOfExecution(vector<task> tasks) {
   sort(tasks.begin(), tasks.end(), cmp_arrival);
   int totalcputimeneeded = 0;
   for (auto t : tasks) {
       totalcputimeneeded += t.burst;
   }

   int totalcputime = 0;
   int idx;
   int currTime = tasks[0].arrival;
   vector<executedtask> execOrder;

   priority_queue<task, vector<task>, cmp_arrival_queue> queue0, queue1, queue2;

   int quantum0 = 8, quantum1 = 16;

   for (idx = 0; idx < tasks.size() && tasks[idx].arrival <= currTime; idx++)
           queue0.push(tasks[idx]);

   while (totalcputime < totalcputimeneeded) {
       int timeleft = INT_MAX;
       while (!queue0.empty()) {
           task curr = queue0.top();
           queue0.pop();
           int exectime = min(quantum0, curr.burst);
           currTime += exectime;
           totalcputime += exectime;
           curr.burst -= exectime;
           execOrder.push_back({curr.id, exectime, 0});
           if (curr.burst > 0) {
               curr.arrival = currTime;
               queue1.push(curr);
           }

           for (; idx < tasks.size() && tasks[idx].arrival <= currTime; idx++)
               queue0.push(tasks[idx]);
       }

       if (idx < tasks.size()) {
           timeleft = tasks[idx].arrival - currTime;
           queue0.push(tasks[idx++]);
       }

       while (!queue1.empty() && timeleft > 0) {
           task curr = queue1.top();
           queue1.pop();
           int burst = curr.burst;
           int exectime = min(timeleft, min(quantum1, curr.burst));
           currTime += exectime;
           totalcputime += exectime;
           curr.burst -= exectime;
           timeleft -= exectime;

           executedtask el;
           el.id=curr.id;
           el.time=exectime;
           el.queue=1;

           execOrder.push_back(el);
           
           if (curr.burst > 0) {
               if (exectime < quantum1 && exectime < burst) {
                   queue1.push(curr);
               } else {
                   curr.arrival = currTime;
                   queue2.push(curr);
               }
           }
       }

       while (!queue2.empty() && timeleft > 0) {
           task curr = queue2.top();
           queue2.pop();
           int burst = curr.burst;
           int exectime = min(timeleft, curr.burst);
           currTime += exectime;
           totalcputime += exectime;
           curr.burst -= exectime;
           timeleft -= exectime;
           execOrder.push_back({curr.id, exectime, 2});
           if (curr.burst > 0) {
               curr.arrival = currTime;
               queue2.push(curr);
           }
       }
   }
   return execOrder;
}

void printOrder(vector<executedtask> execOrder) {
   cout << "Order of execution for Multilevel Feedback Queue Scheduling" << endl;
   for (auto t : execOrder) {
       cout << "P" << t.id << "\tBurst time: " << t.time << "\tQueue: " << t.queue << endl;
   }
   cout << endl;
}

int main() {
   int n;
   cout << "Enter number of tasks: ";
   cin >> n;
   cout << endl;
   vector<task> tasks;
   for (int i = 0; i < n; i++) {
       int burst, arrival;
       cout << "TASK ID: " << i + 1 << endl;
       cout << "Enter arrival time: ";
       cin >> arrival;
       cout << "Enter burst time: ";
       cin >> burst;
       task t = {i + 1, arrival, burst};
       tasks.push_back(t);
       cout << endl;
   }
   printOrder(orderOfExecution(tasks));
   return 0;
}