#include <stdio.h>
#include <windows.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD exitCode;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Example: run "cmd /c dir"
    if (!CreateProcess(
        NULL, "cmd /c dir", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("CreateProcess failed (%lu).\n", GetLastError());
        return 1;
    }

    // Wait for the process to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Get exit code
    if (!GetExitCodeProcess(pi.hProcess, &exitCode)) {
        printf("Failed to get exit code.\n");
        return 1;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Exit with the same code
    return (int) exitCode;
}