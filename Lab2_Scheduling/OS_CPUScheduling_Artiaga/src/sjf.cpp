#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Process {
    int id, AT, BT, CT, TAT, WT;
};

void displayInput(const vector<Process>& procs) {
    cout << "Input:\nProcesses: ";
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

void displayResults(const vector<int>& ganttProcs, const vector<int>& ganttTimes) {
    cout << "Gantt Chart (SJF):\n\n";
    int cellWidth = 5;
    for (int pid : ganttProcs) cout << "|" << setw(cellWidth - 1) << ("P" + to_string(pid));
    cout << "|\n";
    for (size_t i = 0; i < ganttTimes.size(); i++) cout << setw(cellWidth) << ganttTimes[i];
    cout << "\n\n";
}

void displayTable(const vector<Process>& procs) {
    displayInput(procs);
    cout << "Output Table:\n\n";
    cout << left << setw(10) << "Process" << setw(5) << "AT" << setw(5) << "BT"
         << setw(5) << "CT" << setw(5) << "TAT" << setw(5) << "WT" << "\n";
    cout << string(35, '-') << "\n";

    double totalTAT = 0, totalWT = 0;
    for (auto p : procs) {
        cout << left << setw(10) << ("P" + to_string(p.id))
             << setw(5) << p.AT << setw(5) << p.BT
             << setw(5) << p.CT << setw(5) << p.TAT << setw(5) << p.WT << "\n";
        totalTAT += p.TAT;
        totalWT += p.WT;
    }

    cout << "\nAverage TAT = " << fixed << setprecision(2) << totalTAT / procs.size();
    cout << "\nAverage WT = " << fixed << setprecision(2) << totalWT / procs.size() << "\n\n";
}

// ======== SJF (Non-preemptive) ========
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
    displayResults(ganttProcs, ganttTimes);
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Arrival Time of P" << i + 1 << ": ";
        cin >> processes[i].AT;
        cout << "Burst Time of P" << i + 1 << ": ";
        cin >> processes[i].BT;
    }
    sjf(processes);
    return 0;
}
