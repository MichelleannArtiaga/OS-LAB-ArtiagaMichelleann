1. Install MinGW and extract to your system PATH.
2. Open the src folder in VS Code.
3. Open a terminal in VS Code and run the following commands to build the executables:

    gcc -o output/child_echo.exe child_echo.c
    gcc -o output/create_basic.exe create_basic.c
    gcc -o output/create_two_children.exe create_two_children.c
    gcc -o output/replace_sim.exe replace_sim.c
Task A – Creating a Single Child with a command "\create_basic.exe"
<img width="1224" height="233" alt="image" src="https://github.com/user-attachments/assets/8355cb55-d1fa-49f8-b4cb-16055062c2fc" />

Task B – Creating Two Children with a command ".\'create_two_children.exe'"
<img width="1393" height="313" alt="image" src="https://github.com/user-attachments/assets/89d4f6e2-d8d0-4d9d-b5da-b6306ae6233a" />

Task C – Simulating exec() with a command " .\'replace_sim.exe'"
<img width="1473" height="444" alt="image" src="https://github.com/user-attachments/assets/09c93fa6-37a5-4676-b053-f14bcb54eaca" />

Task D – Managing Processes in PowerShell with a command "Get-Process child_echo
Stop-Process -Id <PID>"
<img width="1266" height="208" alt="image" src="https://github.com/user-attachments/assets/a6ab15d5-7ecc-41b6-9e66-6ee490f43d3b" />

before the termination 
<img width="1479" height="295" alt="image" src="https://github.com/user-attachments/assets/ddfbb63f-8a52-4b66-904d-1b4780e75b58" />


after
<img width="1540" height="134" alt="image" src="https://github.com/user-attachments/assets/c121b32f-8bef-4351-ba99-f5223f5ab33d" />
