#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct Node{
    int value;
    struct Node *next;
}Node;

typedef struct Queue{
    int size;
    Node *head;
    Node *tail;
}Queue;

void freeQueue(Queue *q){
    Node *n = q->head;
    while(n != NULL){
        Node *n_old = n;
        n = n->next;
        free(n_old);
    }
    free(q);
}


Queue* createQueue(){
    Queue *tmp = (Queue*)malloc(sizeof(Queue));
    tmp->size = 0;
    tmp->head = NULL;
    tmp->tail = NULL;
    return tmp;
}

void pushQueue(Queue *q, int value){
    if (q == NULL) {
        return;
    }
    Node *tmp = (Node*)malloc(sizeof(Node));
    tmp->value = value;

    if(q->head == NULL){
        (q)->head = tmp;
    }else{
        (q)->tail->next = tmp;
    }
    tmp->next = NULL;
    q->tail = tmp;
    q->size++;
}

int popQueue(Queue *q){
    if(q == NULL || q->head == NULL){
        return INT_MAX;
    }   

    Node *tmp = (q)->head->next;
    int v = q->head->value;

    free(q->head);
    q->head = tmp;

    if (q->head == NULL) {
        q->tail = NULL;
    }

    q->size--;
    return v;
}

int peek(Queue *q){
    if(q == NULL || q->size == 0 || q->head == NULL){
        return INT_MAX;
    }
    int v = q->head->value;
    return v;
}


void printQueue(Queue *q){
    Node *n = q->head;
    while(n != NULL){
        printf("%d ", n->value);
        n = n->next;
    }
}


int main(void){
    Queue *q = createQueue();

    int n, len;
    scanf("%d%d", &n, &len);
    char command_line[100];

    int c;
    while ((c = getchar()) != '\n' && c != EOF); 

    
    int coms = 0;

    while(coms < n){
        char command_line[100];
        if (fgets(command_line, sizeof(command_line), stdin) == NULL) {
            break;
        }

        command_line[strcspn(command_line, "\n")] = 0;
        
        
        char *command = strtok(command_line, " ");
        
        if (command == NULL) {
            continue;
        }
        
        
        if (strcmp(command, "push") == 0) {
            char *arg_str = strtok(NULL, " ");
            if (arg_str != NULL) {
                int x = atoi(arg_str);
                if(q->size < len){
                    pushQueue(q, x);
                }else{
                    printf("error\n");
                }
            }
        }else if (strcmp(command, "pop") == 0) {
            int maxx = popQueue(q);
            if(maxx == INT_MAX){
                printf("None\n");
            }else{
                printf("%d\n", maxx);
            }
        }else if (strcmp(command, "peek") == 0) {
            int max = peek(q);
            if(max == INT_MAX){
                printf("None\n");
            }else{
                printf("%d\n", max);
            }
        }else if (strcmp(command, "size") == 0) {
            int ss = q->size;
            printf("%d\n", ss);
        }
    
        coms++;
    }

    freeQueue(q);
    exit(EXIT_SUCCESS);
}
