#include "v1_parent.h"

void parent1() {

    char buf[BUF_SIZE];
    int a, b, check = 0;
    int status;

    printf("Enter pair of numbers");
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        perror("error on stdin");
        exit(1);
    }
    while (buf[0] != '0') {
        check = checkbuf(buf);
        if (check == 0) {
            printf("Illegal input \n try again !\n ");
            goto input;
        }

        int pid = fork();
        switch (pid) {
            case -1:
                perror("fork failed");
                exit(1);
            case 0:
                extractPairs(&a, &b, buf);
                char arr[5];
                char brr[5];
                sprintf(brr, "%d", b);
                sprintf(arr, "%d", a);
                char *nums[] = {"./child1", arr, brr, NULL};
                execv("child1", nums);
                printf("execv fail");
                exit(-1);
            default:
                wait(&status);
                printf("\n %s gcd: %d \n", buf, WEXITSTATUS(status));
                break;
        }
        input:
        printf("Enter pair of numbers \n Press 0 to exit \n");
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            perror("error on stdin");
            exit(1);
        }
    }
}

int checkbuf(char *buf) {
    int count = 0;
    int i;
    for (i = 0; i < strlen(buf); ++i) {
        if (buf[i] == ' ' && (buf[i - 1] <= '9' && buf[i - 1] >= '0')) {
            count++;
        }
        if (buf[i] != ' ' && !(buf[i] <= '9' && buf[i] >= '0')) {
            break;
        }

    }
    if (count == 1 && ((strlen(buf) - i) == 1)) {
        return 1;
    }
    return 0;
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
