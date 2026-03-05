#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct Node{
    int value;
    struct Node *next;
}node;

typedef struct NodePair{
    struct Node *stack;
    struct Node *stack_m;
}nodePair;

int getMax(nodePair *pair){
    if(pair == NULL || pair->stack_m == NULL){
        return INT_MIN;
    }
    return pair->stack_m->value;
}

void freeStack(nodePair *pair){

    if(pair == NULL){
        return;
    }


    node *stack = pair->stack;
    node *stack_m = pair->stack_m;

    while(stack != NULL){
        if(stack_m != NULL){
            node * stack_m_n = stack_m->next;
            free(stack_m);
            stack_m = stack_m_n;
        }
        node *stack_n = stack->next;
        free(stack);
        stack = stack_n;
    }

    free(pair);
}

nodePair* push(nodePair *pair, int num){
    node *stack_el = (node*)malloc(sizeof(node));
    stack_el->value = num;
    if(pair->stack != NULL){
        stack_el->next = pair->stack;
    }
    pair->stack = stack_el;

    if(pair->stack_m == NULL || num >= pair->stack_m->value){
        node *stack_el_m = (node*)malloc(sizeof(node));
        stack_el_m->value = num;
        stack_el_m->next = pair->stack_m;
        pair->stack_m = stack_el_m;
    }
    return pair;
}

nodePair* pop(nodePair *pair){
    if(pair == NULL){
        printf("error\n");
        return pair;
    }

    if(pair->stack_m != NULL && pair->stack_m->value == pair->stack->value){
        node *stack_el_prev_m = pair->stack_m->next;
        free(pair->stack_m);
        pair->stack_m = stack_el_prev_m;
    }

    if(pair->stack != NULL){
        node *stack_el_prev = pair->stack->next;
        free(pair->stack);
        pair->stack = stack_el_prev;
    }else{
        printf("error\n");
        return pair;
    }

    

    return pair;
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

void top(nodePair *pair){
    if(pair == NULL || pair->stack == NULL){
        printf("error\n");
        return;
    }
    printf("%d\n", pair->stack->value);
    return;
}



int main(void){

    nodePair *node_p = (nodePair*)malloc(sizeof(nodePair));
    int n;
    scanf("%d", &n);
    char command_line[100];


    while (getchar() != '\n' && getchar() != EOF); 

    
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
                node_p = push(node_p, x);
            }
        }else if (strcmp(command, "pop") == 0) {
            node_p = pop(node_p);
        }else if (strcmp(command, "get_max") == 0) {
            int max = getMax(node_p);
            if(max == INT_MIN){
                printf("None\n");
            }else{
                printf("%d\n", max);
            }
        }else if (strcmp(command, "top") == 0) {
            top(node_p);
        }
    
        coms++;
    }
        


    // node_p = push(node_p, 1);
    // node_p = push(node_p, 2);
    // node_p = push(node_p, 5);
    // node_p = push(node_p, 4);
    // node_p = push(node_p, 14);
    // node_p = push(node_p, 4);
    // node_p = push(node_p, 4);
    // node_p = push(node_p, 4);
    // node_p = push(node_p, 114);

    // printStack(node_p->stack_m);
    // printStack(node_p->stack);

    // printf("%d MAX \n", getMax(node_p));
    
    // node_p = pop(node_p);
    // node_p = pop(node_p);
    // node_p = pop(node_p);
    // top(node_p);
    // node_p = push(node_p, 4);
    // node_p = push(node_p, -5);
    // top(node_p);
    // node_p = push(node_p, 7);



    // printStack(node_p->stack);


    // node_p = pop(node_p);
    // node_p = pop(node_p);

    // int max = getMax(node_p);
    // if(max == INT_MIN){
    //     printf("None\n");
    // }else{
    //     printf("%d\n", max);
    // }
    // top(node_p);
    // printStack(node_p->stack);
    // node_p = pop(node_p);
    // printStack(node_p->stack);
    // max = getMax(node_p);
    // if(max == INT_MIN){
    //     printf("None\n");
    // }else{
    //     printf("%d\n", max);
    // }

    // printStack(node_p->stack_m);
    // printStack(node_p->stack);
    // printf("%d MAX \n", getMax(node_p));

    freeStack(node_p);
    exit(EXIT_SUCCESS);
}
