#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Process {
    int id, AT, BT, CT, TAT, WT;
};

// ======== Display Input ========
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

// ======== Gantt Chart (aligned neatly) ========
void displayResults(const vector<int>& ganttProcs, const vector<int>& ganttTimes, const string& algoName) {
    cout << "Gantt Chart (" << algoName << "):\n\n";

    // Each bar has a consistent width for neat alignment
    const int cellWidth = 7;

    // Print process bars
    for (int pid : ganttProcs) {
        cout << "|" << setw(cellWidth - 2) << ("P" + to_string(pid)) << " ";
    }
    cout << "|\n";

    // Print the timeline numbers below the bars
    for (size_t i = 0; i < ganttTimes.size(); i++) {
        cout << left << setw(cellWidth) << ganttTimes[i];
    }
    cout << "\n\n";
}

// ======== Output Table ========
void displayTable(const vector<Process>& procs) {
    displayInput(procs);

    cout << "Output Table:\n\n";
    cout << left << setw(10) << "Process"
         << setw(5) << "AT"
         << setw(5) << "BT"
         << setw(5) << "CT"
         << setw(5) << "TAT"
         << setw(5) << "WT" << "\n";
    cout << string(35, '-') << "\n";

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

    cout << "\nAverage TAT = " << fixed << setprecision(2) << totalTAT / procs.size() << "\n";
    cout << "Average WT = " << fixed << setprecision(2) << totalWT / procs.size() << "\n\n";
}

// ======== FCFS Algorithm ========
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

    displayTable(procs);
    displayResults(ganttProcs, ganttTimes, "FCFS");
}

// ======== Main ========
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

    cout << "\n";
    fcfs(processes);
    return 0;
}
