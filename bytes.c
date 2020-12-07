#include <stdlib.h>
#include <stdio.h>
#include "bytes.h"
#include <string.h>
#include <malloc.h>
//student name : allen bronshtein
// student username : bronsha
//student id : 206228751
static int count = 0;

byte_t *create_bytes(char *file_name) {
    FILE *fileP = fopen(file_name, "r");
    if (fileP == NULL) {
        printf("Error: file pointer is null.");
        exit(1);
    }
    int numOfLines = 0;
    char studentAnswer[10];
    //count how much students answered
    while (fgets(studentAnswer, 10, fileP)) {
        ++numOfLines;
    }
    count = numOfLines;
    FILE *fileP2 = fopen(file_name, "r");
    if (fileP2 == NULL) {
        printf("Error: file pointer is null.");
        exit(1);
    }
    byte_t *bytes = malloc(sizeof(bytes) * count);
    int it = 0;
    while (fgets(studentAnswer, 10, fileP2)) {
        byte_t t = 0;
        for (int i = 0; i < 4; i++) {
            char c = studentAnswer[2 * i];
            unsigned int x = c - '0';
            t += x << 2 * i;
        }
        bytes[it] = t;
        it++;
    }
    fclose(fileP);
    fclose(fileP2);
    return bytes;
}

void print_bytes(byte_t *byte_array, FILE *out) {
    if (out == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }
    for (int i = 0; i < count; i++) {
        fprintf(out, "%02x", byte_array[i]);
    }
    fprintf(out, "\n");
}

void set_stud(byte_t *byte_array, int i, int j, int k) {
    byte_t t = byte_array[i - 1];
    byte_t newT;
    if (j == 1) {
        newT = t & 252;
        newT = newT | k;
    } else if (j == 2) {
        newT = t & 242;
        k *= 4;
        newT = newT | k;
    } else if (j == 3) {
        newT = t & 207;
        k *= 16;
        newT = newT | k;
    } else if (j == 4) {
        newT = t & 63;
        k *= 32;
        newT = newT | k;
    }
    byte_array[i - 1] = newT;
}

float average_stud(byte_t *byte_array, int i) {
    float sum = 0;
    float a ;
    byte_t studentAnswers = byte_array[i-1];
    int ans1 , ans2 , ans3 , ans4 ;
    ans1 = studentAnswers%4;
    ans2 = (studentAnswers>>2)%4;
    ans3 = (studentAnswers>>4)%4;
    ans4 = (studentAnswers>>6)%4;
    sum = (ans1+ans2+ans3+ans4)/4;
    sum = ans1 + ans2 + ans3 + ans4 ;
    return sum/4;
}

float average_ans(byte_t *byte_array, int j) {
    float sum = 0;
    for(int i=0;i<count;i++){
        if(j==1){
            sum+=byte_array[i]%4;
        }
        else if(j==2){
            sum+=(byte_array[i]>>2)%4;
        }
        else if(j==3){
            sum+=(byte_array[i]>>4)%4;
        }
        else if(j==4){
            sum+=(byte_array[i]>>8)%4;
        }
    }
    return sum/count;
}
