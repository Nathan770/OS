
#include "v2_parent.h"
#include "v1_parent.h"
#pragma once

int main(int argc, char *argv[]) {
    int pfd1[2] ,pfd2[2],pfd3[2],pfd4[2];                                     /* Pipe file descriptors */
    char buf[BUF_SIZE];
    ssize_t numRead;
    int a ,b ,counter=1 ,switcher = 0;

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        perror("usage error");

    if (pipe(pfd1) == -1)                            /* Create pipe 1*/
        perror("pipe1");
    if (pipe(pfd2) == -1)                            /* Create pipe 2*/
        perror("pipe2");
    if (pipe(pfd3) == -1)                            /* Create pipe 3*/
        perror("pipe3");
    if (pipe(pfd4) == -1)                            /* Create pipe 4*/
        perror("pipe4");

    FILE *f = fopen(argv[1],"r");
    if(f == NULL){
        perror("Cannot open file");
        exit(-1);
    }
        buf_exit :
    fscanf(f, "%[^\n]", buf);
    if(checkbuf(buf) == 0){
        printf("Probleme in line %d",counter);
        goto buf_exit ;
    }
    counter++;
    extractPairs(&a,&b,buf);


    switch (fork()) {
        case -1:
            perror("fork");

        case 0:
            if (close(pfd1[1]) == -1)
                perror("close 1");
            if(close(pfd2[0]) == -1)
                perror("close 2");


            if (pfd1[0] != STDIN_FILENO) {              /* Defensive check */
                if (dup2(pfd1[0], STDIN_FILENO) == -1)
                    perror("dup2 1");
            }

            execlp("v2_child1", "ls", (char *) NULL);          /* Writes to pipe */
            perror("execlp ls");

        default:          /* Parent falls through to create next child */
        if(switcher == 0){

        }
            break;
    }

    switch (fork()) {
        case -1:
            errExit("fork");

        case 0:             /* Second child: exec 'wc' to read from pipe */
            if (close(pfd[1]) == -1)                    /* Write end is unused */
                errExit("close 3");

            /* Duplicate stdin on read end of pipe; close duplicated descriptor */

            if (pfd[0] != STDIN_FILENO) {               /* Defensive check */
                if (dup2(pfd[0], STDIN_FILENO) == -1)
                    errExit("dup2 2");
                if (close(pfd[0]) == -1)
                    errExit("close 4");
            }

            execlp("wc", "wc", "-l", (char *) NULL);
            errExit("execlp wc");

        default: /* Parent falls through */
            break;
    }

    /* Parent closes unused file descriptors for pipe, and waits for children */

    if (close(pfd[0]) == -1)
        errExit("close 5");
    if (close(pfd[1]) == -1)
        errExit("close 6");
    if (wait(NULL) == -1)
        errExit("wait 1");
    if (wait(NULL) == -1)
        errExit("wait 2");

    exit(EXIT_SUCCESS);
}
