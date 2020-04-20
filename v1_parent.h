//
// Created by me on 12/04/2020.
//
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "nums.txt"
#ifndef BUF_SIZE        /* Allow "cc -D" to override definition */
#define BUF_SIZE 20
#endif

void parent1();

void extractPairs(int *a, int *b, char *buf);

int checkbuf(char *buf);