# 🧠 CPU Scheduling Algorithms — OS Project

This project demonstrates three classic **CPU Scheduling Algorithms** implemented in **C++**:

- **FCFS (First Come First Serve)**
- **SJF (Shortest Job First — Non-preemptive)**
- **RR (Round Robin)**

Each algorithm calculates:
- **Completion Time (CT)**
- **Turnaround Time (TAT)**
- **Waiting Time (WT)**

And displays:
- Input and output tables  
- Average TAT & WT  
- A clean, text-based **Gantt Chart**

---

## ⚙️ How to Compile and Run

### 1️⃣ Compile
From your terminal (inside the project root):

```bash
g++ src/fcfs.cpp -o output/fcfs.exe
g++ src/sjf.cpp -o output/sjf.exe
g++ src/rr.cpp -o output/rr.exe
