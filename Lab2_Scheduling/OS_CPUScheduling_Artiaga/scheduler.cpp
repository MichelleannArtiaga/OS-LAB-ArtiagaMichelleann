#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Process {
    int id, AT, BT, CT, TAT, WT;
};

// ======== Display Input Section (clean like sample) ========
void displayInput(const vector<Process>& procs) {
    cout << "Input:\n";
    cout << "Processes: ";
    for (size_t i = 0; i < procs.size(); i++) {
        if (i > 0) cout << ", ";
        cout << "P" << procs[i].id;
    }
    cout << "\nAT: [";
    for (size_t i = 0; i < procs.size(); i++) {
        cout << procs[i].AT;
        if (i < procs.size() - 1) cout << ", ";
    }
    cout << "]\nBT: [";
    for (size_t i = 0; i < procs.size(); i++) {
        cout << procs[i].BT;
        if (i < procs.size() - 1) cout << ", ";
    }
    cout << "]\n\n";
}

// ======== Gantt Chart (clean style, fixed time alignment) ========
void displayResults(const vector<int>& ganttProcs, const vector<int>& ganttTimes, const string& algoName) {
    cout << "Gantt Chart (" << algoName << "):\n\n";

    int cellWidth = 5; // width of each cell

    // Process row
    for (int pid : ganttProcs) {
        cout << "|" << setw(cellWidth-1) << ("P" + to_string(pid));
    }
    cout << "|\n";

    // Time row (print each time under its bar)
    for (size_t i = 0; i < ganttTimes.size(); i++) {
        cout << setw(cellWidth) << ganttTimes[i];
    }
    cout << "\n\n";
}


// ======== Output Table (styled like sample) ========
void displayTable(const vector<Process>& procs) {
    displayInput(procs); // Show input first

    cout << "Output Table:\n\n";
    cout << left << setw(10) << "Process"
         << setw(5) << "AT"
         << setw(5) << "BT"
         << setw(5) << "CT"
         << setw(5) << "TAT"
         << setw(5) << "WT" << "\n";

    cout << string(35, '-') << "\n";  // separator line

    double totalTAT = 0, totalWT = 0;
    for (auto p : procs) {
        cout << left << setw(10) << ("P" + to_string(p.id))
             << setw(5) << p.AT
             << setw(5) << p.BT
             << setw(5) << p.CT
             << setw(5) << p.TAT
             << setw(5) << p.WT << "\n";
        totalTAT += p.TAT;
        totalWT += p.WT;
    }

    double avgTAT = totalTAT / procs.size();
    double avgWT = totalWT / procs.size();

    cout << "\nAverage TAT = " << fixed << setprecision(2) << avgTAT << "\n";
    cout << "Average WT = " << fixed << setprecision(2) << avgWT << "\n\n";
}

// ================= FCFS =================
void fcfs(vector<Process> procs) {
    sort(procs.begin(), procs.end(), [](Process a, Process b) {
        return a.AT < b.AT;
    });

    int time = 0;
    vector<int> ganttProcs, ganttTimes;
    ganttTimes.push_back(0);

    for (auto &p : procs) {
        if (time < p.AT) time = p.AT;
        time += p.BT;
        p.CT = time;
        p.TAT = p.CT - p.AT;
        p.WT = p.TAT - p.BT;
        ganttProcs.push_back(p.id);
        ganttTimes.push_back(time);
    }

    // Table first, then Gantt (as you requested)
    displayTable(procs);
    displayResults(ganttProcs, ganttTimes, "FCFS");
}

// ================= SJF (non-preemptive) =================
void sjf(vector<Process> procs) {
    int n = procs.size();
    vector<bool> done(n, false);
    int completed = 0, time = 0;
    vector<int> ganttProcs, ganttTimes;
    ganttTimes.push_back(0);

    while (completed < n) {
        int idx = -1, minBT = 1e9;
        for (int i = 0; i < n; i++) {
            if (procs[i].AT <= time && !done[i]) {
                if (procs[i].BT < minBT) {
                    minBT = procs[i].BT;
                    idx = i;
                }
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }
        time += procs[idx].BT;
        procs[idx].CT = time;
        procs[idx].TAT = procs[idx].CT - procs[idx].AT;
        procs[idx].WT = procs[idx].TAT - procs[idx].BT;
        done[idx] = true;
        completed++;
        ganttProcs.push_back(procs[idx].id);
        ganttTimes.push_back(time);
    }
    displayTable(procs);
    displayResults(ganttProcs, ganttTimes, "SJF");
}

// ================= Round Robin =================
void roundRobin(vector<Process> procs, int quantum) {
    int n = procs.size();
    vector<int> remBT(n);
    for (int i = 0; i < n; i++) remBT[i] = procs[i].BT;

    queue<int> q;
    vector<bool> added(n, false);
    int time = 0, done = 0;
    vector<int> ganttProcs, ganttTimes;
    ganttTimes.push_back(0);

    while (done < n) {
        for (int i = 0; i < n; i++) {
            if (procs[i].AT <= time && !added[i]) {
                q.push(i);
                added[i] = true;
            }
        }
        if (q.empty()) {
            time++;
            continue;
        }
        int idx = q.front(); q.pop();
        int exec = min(quantum, remBT[idx]);
        ganttProcs.push_back(procs[idx].id);
        time += exec;
        ganttTimes.push_back(time);
        remBT[idx] -= exec;

        // Re-check for newly arrived processes
        for (int i = 0; i < n; i++) {
            if (procs[i].AT <= time && !added[i]) {
                q.push(i);
                added[i] = true;
            }
        }

        if (remBT[idx] > 0) {
            q.push(idx);
        } else {
            procs[idx].CT = time;
            procs[idx].TAT = procs[idx].CT - procs[idx].AT;
            procs[idx].WT = procs[idx].TAT - procs[idx].BT;
            done++;
        }
    }
    displayTable(procs);
    displayResults(ganttProcs, ganttTimes, "RR");
}

// ================= Main =================
int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        processes[i].id = i+1;
        cout << "Arrival Time of P" << i+1 << ": ";
        cin >> processes[i].AT;
        cout << "Burst Time of P" << i+1 << ": ";
        cin >> processes[i].BT;
    }

    cout << "\nChoose Algorithm:\n1. FCFS\n2. SJF (Non-preemptive)\n3. Round Robin\n";
    int choice; cin >> choice;

    if (choice == 1) {
        fcfs(processes);
    } else if (choice == 2) {
        sjf(processes);
    } else if (choice == 3) {
        int q;
        cout << "Enter Quantum (e.g., 2 or 3): ";
        cin >> q;
        roundRobin(processes, q);
    } else {
        cout << "Invalid choice.\n";
    }
    return 0;
}
