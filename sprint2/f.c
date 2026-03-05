#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct Node{
    int value;
    struct Node *next;
}node;


int getMax(node *stack_h){
    if(stack_h == NULL){
        return INT_MIN;
    }
    int max = INT_MIN;
    node *pointer = stack_h;
    while(pointer != NULL){
        if(pointer->value > max){
            max = pointer->value;
        }
        pointer = pointer->next;
    }
    return max;
}

node* push(node *stack_h, int num){
    node *stack_el = (node*)malloc(sizeof(node));
    if(stack_el == NULL){
        perror("no mem");
        exit(EXIT_FAILURE);
    }
    stack_el->value = num;
    stack_el->next = stack_h;
    return stack_el;
}

node* pop(node *stack_h){
    if(stack_h == NULL){
        printf("error\n");
        return NULL;
    }
    node *stack_el_prev = stack_h->next;
    free(stack_h);
    stack_h = stack_el_prev;
    return stack_h;
}

void printStack(node *stack_h){
    printf("-----\n");
    node *pointer = stack_h;
    while(pointer != NULL){

        printf("%d\n", pointer->value);
        pointer = pointer->next;
    }
    printf("-----\n");
}



int main(void){

    int n;
    scanf("%d", &n);
    char command_line[100];


    while (getchar() != '\n' && getchar() != EOF); 

    node *stack_h = NULL;
    int coms = 0;

    while(coms < n){
        char command_line[100];
        if (fgets(command_line, sizeof(command_line), stdin) == NULL) {
            break;
        }

        command_line[strcspn(command_line, "\n")] = 0;
        
        char *command = strtok(command_line, " ");
        if (strcmp(command, "push") == 0) {
            char *arg_str = strtok(NULL, " ");
            if (arg_str != NULL) {
                int x = atoi(arg_str);
                stack_h = push(stack_h, x);
            }
        }else if (strcmp(command, "pop") == 0) {
            char *arg_str = strtok(NULL, " ");
            stack_h = pop(stack_h);
        }else if (strcmp(command, "get_max") == 0) {
            char *arg_str = strtok(NULL, " ");
            int max = getMax(stack_h);
            if(max == INT_MIN){
                printf("None\n");
            }else{
                printf("%d\n", max);
            }
        }
    
        coms++;
    }
        


    // stack_h = push(stack_h, 1);
    // stack_h = push(stack_h, 2);
    // stack_h = push(stack_h, 3);
    // stack_h = push(stack_h, 4);

    // printStack(stack_h);

    // stack_h = pop(stack_h);
    // stack_h = pop(stack_h);


    // printStack(stack_h);


    exit(EXIT_SUCCESS);
}