#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void basicPointers(int i);
int testAndReduce(int*ip);
void basicMemoryAllocation();
void basicArrayMemoryAllocation();
void intermediateArrayMemoryAllocation();
void checkIfNull(void* p);
void basicStructureMemoryAllocation();
void intermediateStructureMemoryAllocation();
int times2(int x);
void basicFunctionPointers();
void arrayApplyFunction(int *a, int aLen, int (*fp)(int));
void printIntArrayValues(int *a,int aLen);
void intermediateFunctionPointers();

//Basic structure

struct point {
    int x;
    int y;
};

//Getters and setters equivalents
int point_get_x(struct point*p) {
    return p->x;
}void point_set_x(struct point*p, int x) {
    p->x = x;
}
int point_get_y(struct point*p) {
    return p->y;
}void point_set_y(struct point*p, int y) {
    p->y = y;
}


struct line {
    struct point *start;
    struct point *end;
};

struct node {
    int value;
    struct node*next;
};

int main(int argc, char** argv) {
    int i = 123;
    int* ip = &i;
    printf("Calling the 'basicPointers' function \n");
    basicPointers(i);
    printf("Calling the 'basicMemoryAllocation' function \n");
    basicMemoryAllocation();
    printf("Calling the 'basicArrayMemoryAllocation' function \n");
    basicArrayMemoryAllocation();
    printf("Calling the 'intermediateArrayMemoryAllocation' function \n");
    intermediateArrayMemoryAllocation();
    printf("Calling the 'basicStructureMemoryAllocation' function \n");
    basicStructureMemoryAllocation();
    printf("Calling the 'intermediateStructureMemoryAllocation' function \n");
    intermediateStructureMemoryAllocation();
    printf("Calling the 'basicFunctionPointers' function \n");
    basicFunctionPointers();
    printf("Calling the 'intermediateFunctionPointers' function \n");
    intermediateFunctionPointers();
    return 0;

}

//Pointers

void basicPointers(int i) {
    int*ip = &i;
    printf("variable i: %i \n"
           "dereferenced pointer of variable i: %i \n"
           "pointer of variable i: %p\n\n", i,*ip,ip);
    *ip=321;
    printf("After changing the value of i through the dereferenced pointer:\n"
           "variable i: %i \n"
           "dereferenced pointer of variable i: %i \n"
           "pointer of variable i: %p\n\n ", i,*ip,ip);

    printf("Calling the 'testAndReduce' function \n");
    printf("Prior to calling the function the value of *ip is %i\n",*ip);
    if (testAndReduce(&i)) {
        printf("i is now one less than before, possibly 0 \n"
               "Variable i: %i\n\n",i);
        printf("\n");
    }else {
        printf("i was already <= 0\n"
               "Variable i: %i\n\n",i);
    }
}

//Pass by reference

int testAndReduce(int* ip) {
    if (*ip > 0) {
        *ip -= 1;
        printf("*ip was bigger to 0 so the function will return true\n");
        return 1;
    } else {
        printf("*ip was equal to 0 or negative so the function will return false\n");
        return 0;
    }
}

void basicMemoryAllocation(){
    printf("Allocating 100 bytes of memory\n");
    void* p = malloc(100); //Allocating custom amount of memory
    checkIfNull(p);
    printf("Correcting the amount of bytes by using sizeof(int) to allocate memory\n");
    p=malloc(sizeof(int)); //Allocating the proper amount of memory for integers
    checkIfNull(p);
    int* ip = (int*)p;
    *ip = 98765;
    printf("%d\n\n",*ip);
    free(ip);
    ip = NULL;
}

void basicArrayMemoryAllocation(){
    int num_numbers, num_letters;
    num_numbers=2;
    num_letters=3;
    printf("Allocating the amount of memory required for the numbers and letters arrays\n");
    int* numbers = (int*)calloc(num_numbers, sizeof(int));
    char* letters = (char*)calloc(num_letters, sizeof(char));
    printf("Giving initial values to the first elements of each array\n");
    numbers[0] = 214;
    letters[0] = 'x';
    printf("numbers[0]: %d\n", numbers[0]);
    printf("letters[0]: %c\n\n", letters[0]);

}

void intermediateArrayMemoryAllocation(){
    int arrayOfStringLength=5;
    int stringLength=100;
    char** s_array = (char**)calloc(arrayOfStringLength, sizeof(char*));
    for (int i=0; i < arrayOfStringLength; i++) {
        s_array[i] = (char*)calloc(stringLength, sizeof(char));
    }
    //Random code using the array of strings here

    for (int i=0; i < arrayOfStringLength; i++) {
        free(s_array[i]);
        s_array[i]=NULL;
    }
    free(s_array);
    s_array=NULL;
}

void checkIfNull(void* p){
    if (p==NULL){
        printf("malloc failed, the program will be terminated");
        exit(0);
    }
}

void basicStructureMemoryAllocation(){
    struct point* p = (struct point*)malloc(sizeof(struct point));
    p->x = 1;
    p->y = 99;
    struct line*line1 = (struct line*)malloc(sizeof(struct line));
    line1->start = (struct point*)malloc(sizeof(struct point));
    line1->end = (struct point*)malloc(sizeof(struct point));
    line1->start->x = 667;
    line1->start->y = 668;
    line1->end->x = -123;
    line1->end->y = 0;
    printf("line1.start.x= %i \n"
           "line1.start.y= %i \n"
           "line1.end.x= %i\n"
           "line1.end.y= %i \n\n",line1->start->x,line1->start->y,line1->end->x,line1->end->y);
    free(line1->start);
    line1->start=NULL;
    free(line1->end);
    line1->end=NULL;
    free(line1);
    line1=NULL;
}

void intermediateStructureMemoryAllocation(){
    struct node*head = (struct node*)malloc(sizeof(struct node));
    head->value = 0;
    head->next = (struct node*)malloc(sizeof(struct node));
    head->next->value = 99;
    head->next->next = (struct node*)malloc(sizeof(struct node));
    head->next->next->value = -13;
    head->next->next->next = NULL;
    for (struct node*p=head; p != NULL; p=p->next) {
        printf("node value:%d\n", p->value);
    }
    free(head->next->next);
    head->next->next=NULL;
    free(head->next);
    head->next=NULL;
    free(head);
    head=NULL;
    printf("\n");
}

int times2(int x) {
    return x*2;
}
int square(int x) {
    return pow(x,2);
}

void printIntArrayValues(int *a, int aLen){
    for (int i=0;i<aLen;i++){
        printf("array[%i]=%i\n",i,a[i]);
    }
}
void arrayApplyFunction(int *a, int aLen, int (*fp)(int)) {
    for (int i=0; i < aLen; i++) {
        a[i] = (*fp)(a[i]);
    }
}

void basicFunctionPointers(){
    //int (*fp)(int) = &times2; //in case i want to create a reference to the function
    int i = 999;
    int jLen=5;
    int *j = (int*)calloc(jLen, sizeof(int));
    for (int z=0;z<jLen;z++){
        j[z]=i++;
    }
    printf("Created an array with the following numbers:\n");
    printIntArrayValues(j,jLen);
    printf("\n");
    //Passing the times2 function as parameter to the arrayApplyFunction function
    arrayApplyFunction(j, jLen, times2);
    printf("Doubled the array's values:\n");
    printIntArrayValues(j,jLen);
    printf("\n");
    arrayApplyFunction(j, jLen, square);
    printf("Multiplied each value of the array with itself:\n");
    printIntArrayValues(j,jLen);
    printf("\n");
}

struct dog {
    char*name;
    void (*bark)();
};
void arf() {
    printf("arf\n\n");
}void woof() {
    printf("woof\n\n");
}// ...

void intermediateFunctionPointers(){
    struct dog*fido = (struct dog*)malloc(sizeof(struct dog));
    fido->name = "fido";
    fido->bark = arf;
    fido->bark();      // prints "arf"
}

//Typedef

typedef struct node2 {
    int value;
    struct node*next;
} Node;

typedef struct node*Node2;
struct node3 {
    int value;
    Node next;
};

void typedefExamples(){
    typedef int Distance;
    Distance d;
    Distance*dp;
    Distance distances[100];

    typedef char*String;

    Node*head = (Node*)malloc(sizeof(Node));

    Node2*head2 = (Node*)malloc(sizeof(Node));

    typedef int (*PFII)(int); //Pointer Function that takes an Integer and returns an Integer
    PFII times2Func = times2;
};

