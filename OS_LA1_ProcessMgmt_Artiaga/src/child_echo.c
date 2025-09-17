#include <stdio.h>
#include <windows.h>

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: child_echo <parent_pid>\n");
        return 1;
    }
    DWORD parent_pid = atoi(argv[1]);
    printf("Child PID: %lu\n", GetCurrentProcessId());
    printf("Parent PID (from argument): %lu\n", parent_pid);

    Sleep(40000); // <--- Add this line here

    return 0;
}