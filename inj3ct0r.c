#include <sys/ptrace.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <string.h>
#include <errno.h>
#include <string.h>
      
int main (int argc, char **argv) {
  
    pid_t pid = 0;
    unsigned long addr = 0;
    long value = 0, old_value = 0;                  
    
    if (4 != argc) { 
        if (argc == 2) {
            if (strncmp(argv[1], "--help", 16) == 0 || strncmp(argv[1], "-h", 16) == 0) {
                printf("%s by ykb39\n", basename(argv[0]));
                printf("+--------------------------------------------------+\n");
                printf("| Change value at given address in target process. |\n");
                printf("| Usage: %s {pid} {addr} {value}             |\n", basename(argv[0]));
                printf("+--------------------------------------------------+\n");
                printf("\nhttps://github.com/Volvo2v1\n");
                exit(EXIT_SUCCESS);
            }
        }

        fprintf(stderr, "[-] Not enough arguments!\n |_ Usage: %s {pid} {addr} {value}\n", basename(argv[0]));
        return -1;
    }

    pid = strtol (argv[1], NULL, 10);
    addr = strtol (argv[2], NULL, 16);
    value = strtol (argv[3], NULL, 10);

    if (ptrace (PTRACE_ATTACH, pid, 0, 0)) {
        fprintf (stderr, "[-] Unable to attach to PID: %d (%s)\n", 
                pid, strerror (errno));
        return 1;
    }

    old_value = ptrace (PTRACE_PEEKDATA, pid, addr, 0);
    fprintf (stderr, "[+] Original value: %d\n", old_value);
    if (ptrace (PTRACE_POKEDATA, pid, addr, value)) {
        fprintf (stderr, "[-] Unable to overwrite data @ 0x%lx (%s)\n",
                addr, strerror (errno));
        ptrace (PTRACE_DETACH, pid, 0, 0);
        return 1;
    }
    printf("[+] Written value: %d\n", value);

    ptrace (PTRACE_DETACH, pid, 0, 0);
    return 0;
}
