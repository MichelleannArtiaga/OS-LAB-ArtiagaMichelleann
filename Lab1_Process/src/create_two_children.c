#include <stdio.h>
#include <windows.h>

int main() {
    STARTUPINFO si[2];
    PROCESS_INFORMATION pi[2];
    char cmdLine[2][256];
    DWORD parent_pid = GetCurrentProcessId();
    DWORD exitCode[2];

    for (int i = 0; i < 2; i++) {
        ZeroMemory(&si[i], sizeof(si[i]));
        si[i].cb = sizeof(si[i]);
        ZeroMemory(&pi[i], sizeof(pi[i]));
        sprintf(cmdLine[i], "child_echo.exe %lu", parent_pid);

        if (!CreateProcess(
            NULL, cmdLine[i], NULL, NULL, FALSE, 0, NULL, NULL, &si[i], &pi[i]
        )) {
            printf("CreateProcess for child %d failed (%lu).\n", i + 1, GetLastError());
            return 1;
        }
    }

    // Wait for both children to terminate
    HANDLE handles[2] = {pi[0].hProcess, pi[1].hProcess};
    WaitForMultipleObjects(2, handles, TRUE, INFINITE);

    for (int i = 0; i < 2; i++) {
        if (GetExitCodeProcess(pi[i].hProcess, &exitCode[i])) {
            printf("Child %d exit code: %lu\n", i + 1, exitCode[i]);
        }
        CloseHandle(pi[i].hProcess);
        CloseHandle(pi[i].hThread);
    }

    return 0;
}