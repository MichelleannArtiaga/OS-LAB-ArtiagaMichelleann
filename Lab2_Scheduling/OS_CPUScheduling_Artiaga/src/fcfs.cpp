#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Process {
    int id, AT, BT, CT, TAT, WT;
};

void displayTable(const vector<Process>& procs) {
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

void fcfs(vector<Process> procs) {
    sort(procs.begin(), procs.end(), [](Process a, Process b) {
        return a.AT < b.AT;
    });

    int time = 0;
    for (auto &p : procs) {
        if (time < p.AT) time = p.AT;
        time += p.BT;
        p.CT = time;
        p.TAT = p.CT - p.AT;
        p.WT = p.TAT - p.BT;
    }
    displayTable(procs);
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].id = i+1;
        cout << "AT of P" << i+1 << ": ";
        cin >> p[i].AT;
        cout << "BT of P" << i+1 << ": ";
        cin >> p[i].BT;
    }
    fcfs(p);
}