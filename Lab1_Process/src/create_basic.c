#include <stdio.h>
#include <windows.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    char cmdLine[256];
    DWORD exitCode;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    DWORD parent_pid = GetCurrentProcessId();
    printf("Parent PID: %lu\n", parent_pid);

    // Prepare command line with parent PID as an argument
    sprintf(cmdLine, "child_echo.exe %lu", parent_pid);

    // Start the child process
    if (!CreateProcess(
        NULL,       // Application name
        cmdLine,    // Command line
        NULL,       // Process handle not inheritable
        NULL,       // Thread handle not inheritable
        FALSE,      // Set handle inheritance to FALSE
        0,          // No creation flags
        NULL,       // Use parent's environment block
        NULL,       // Use parent's starting directory 
        &si,        // Pointer to STARTUPINFO structure
        &pi)        // Pointer to PROCESS_INFORMATION structure
    ) {
        printf("CreateProcess failed (%lu).\n", GetLastError());
        return 1;
    }

    // Wait until child process exits
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Get exit code
    if (GetExitCodeProcess(pi.hProcess, &exitCode)) {
        printf("Child's exit code: %lu\n", exitCode);
    } else {
        printf("Failed to get child exit code.\n");
    }

    // Close process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}