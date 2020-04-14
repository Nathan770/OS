//
// Created by me on 12/04/2020.
//

#include "v1_parent.h"
#include <unistd.h>

void parent1() {
    int inputFd, outputFd, openFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buf[BUF_SIZE];
    int a, b;
    int gcd = 0;
    int status;
    char *number =

        printf("start");
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            perror("error on stdin");
            exit(1);
        }
        int pid = fork();
        switch (pid) {
            case -1:
                perror("fork failed");
                exit(1);
            case 0:
                printf("child");
                extractPairs(&a, &b, buf);
                char * nums = {(char) a, (char) b};
                execv("v1_child.c" ,nums);
                gcd = execlp("./v1_child.c" , "v1_child.c",a,b, (char *)NULL);
                exit(gcd);
            default:
                wait(&status);
                printf("parent");
                gcd = WEXITSTATUS(status);
                printf("%s gcd: %d",buf, status);

                    break;
        }

    }


void extractPairs(int *a, int *b, char *buf) {
    char *a1 = (char *) malloc(4 * sizeof(char));
    char *b1 = (char *) malloc(20 * sizeof(char));
    int i = 0;
    for (i = 0; i < BUF_SIZE; ++i) {
        if (buf[i] == ' ') {
            break;
        }
    }
    memcpy(a1, buf, i * sizeof(char));
    memcpy(b1, &buf[i], 20 * sizeof(char));
    *a = atoi(a1);
    *b = atoi(b1);
}
