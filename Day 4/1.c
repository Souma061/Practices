
#include<stdio.h>
#include<stdlib.h>

struct address {
    char city[30];
    char state[30];
    int pincode;
};

struct student {
    char name[50];
    int roll;
    float marks;
    struct address addr;
};


//add,sisplay,search by student name, search by roll number, search by pincode


