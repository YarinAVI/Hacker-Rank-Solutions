#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

/*
 * Complete the function below.
 */
struct node {
    int data;
    struct node *next;
};
int stack_size=0;

void push (struct node **top, int value) {
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    if(new_node==NULL) printf("Problem Allocating Memory For new Node.\n");
    else {
        new_node->data=value;
        new_node->next = (*top); // if list is empty *top is null
        (*top)=new_node;
        stack_size++;
    }

}
void print_top (struct node *top) {
    if(stack_size) printf("%d\n",top->data);
    else {
        printf("EMPTY\n");
    }
}
void inc_elements(struct node *top, int index_from_bottom,int inc_val) {
// we have the size of the stack and the index from the bottom, we can use these value to know from where to ADD V to value
if(index_from_bottom==stack_size) { // in this case traverse the whole stack and add V
while(top) {
    top->data += inc_val;
    top=top->next;
}
}
else {
    int x = stack_size-index_from_bottom;
    while(x) top=top->next,x--;
    while(top) {
        top->data += inc_val;
        top=top->next;
    }

}

}
void pop (struct node **top) {
    if((*top)==NULL) return;
    struct node *t=*top;
    (*top) = (*top)->next;
    free(t);
    stack_size--;
}
// since maximum stack size is unknown or very big we will use linked list to implement it
// we also gonna use ATOI - this function will help us to convert strings into int and also deal with spaces.
// So my code can handle garabe commands (commands that are not pop push or inc) it will just print the current top and continue.
// the code seem to break at the last 4 cases (run time limitation).
void superStack(int operations_size, char** operations) {
struct node *top = NULL;

char cmp1[5] = "push", cmp2[4] = "pop", cmp3[4] = "inc";
char cmp[6] =""; // extra null just in case, this variable will hold the operation without args.
unsigned int i,j;
int arg1,arg2; // only inc will use them both
// reading operations where operation_size is rows size.
for(i=0;i<operations_size;i++) {
    for(j=0;operations[i][j]!='\0';j++) { // we read operation until space occours and null.
    //printf("%c",operations[i][j]);
    // here we copy only necessary letters for 'push' , 'pop , 'inc' into cmp string.

    if(operations[i][j]!=' ' && operations[i][j] >= 'c' && operations[i][j]<= 'u') cmp[j] = operations[i][j];
    //if the first arg is minus it cannot be 'inc' operation, and cannot be 'pop', it can only be 'push'.
    else if(operations[i][j]=='-') {
        if(strcmp(cmp,cmp1)) {
            print_top(top);
            break;
        }
        else {
    arg1 = atoi(&operations[i][j]);
    //printf("%d",arg1);
    // we break here because we finished reading push and we have the argument.
    push(&top,arg1);
    print_top(top);
    break;
        }
    }
    // if the first arg is not minus it can be either 'push' or 'inc'.
    else if (operations[i][j]>='0' && operations[i][j]<='9') {
        // in case cmp is 'inc X' index is 4, 5 letters.
        if(j==4) {
            cmp[3] = '\0';
            if(strcmp(cmp,cmp3)) {
             print_top(top);
             break;
            }
            else {
            arg1 = atoi(&operations[i][j]);
            // we now have the first argument which is index from bottom of the stack.
            while(operations[i][j]!=' ' && operations[i][j]!='\0') j++; // going to the next argument.
            arg2 = atoi(&operations[i][j]);
            inc_elements(top,arg1,arg2);
            print_top(top);
            break;
            // now we have operation in cmp, and the required arguments.
           // printf("%d %d\n",arg1,arg2);
            }
        }
        // in case cmp is 'push X' index is 5, 6 letters.
        else if(j==5) {
            cmp[4] = '\0';
            if(strcmp(cmp,cmp1)) {
                print_top(top);
                break;
            }
            else {
            arg1=atoi(&operations[i][j]);
            push(&top,arg1);
            print_top(top);
            break;
            }
        }
    }

}
    // here goes the case of 'pop' which has no arguments at all.
    if(j==3) {
        cmp[3] = '\0'; // nulling in case before we read push which is 4 letters
        if(strcmp(cmp,cmp2)) {
            print_top(top);
        }

        else {
        pop(&top);
        print_top(top);
        }
    }
    // now cmp holds the actual operation without arguments.
    //for(j=0;cmp[j]!='\0';j++) printf("%c",cmp[j]);
    //printf("\n");
}
}
int main () {
    char *operations[6] = {
    {"push -4"},
    {"pop"},
    {"push 3"},
    {"push 5"},
    {"push 2"},
    {"inc 3 1"},
    };
    superStack(6,&operations);
}