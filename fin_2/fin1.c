/* 
https://contest.yandex.ru/contest/22781/run-report/140358360/ 
 
 
-- ПРИНЦИП РАБОТЫ -- 
Я реализовал задачу на основе интерфейса дек, где элементы можно доабвлять как в начало так и в конец.  
При добавлении в начало указатель на голову смещается против часовой стрелки (влево) 
Хвост смеащется вправо и всегда указывает на пустой элмент для записи. 
Дек реализован на основе массива, так как в данной задаче есть конеченое значение элементов. 
 
-- ВРЕМЕННАЯ СЛОЖНОСТЬ -- 
Добавление в очередь стоит O(1) в отличии от списка с доступом в O(n).  
Извлечение из начала и хвоста также стоит O(1), так как нет необходимости смещений элементов. 
 
-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ -- 
Пространственная сложность 0(n) большую часть которой занимает выделенный массив для данных. 
*/ 
 
 
 
 
#include <stdlib.h> 
#include <stdio.h> 
#include <limits.h> 
#include <string.h> 
 
#define CMD_LINE_LEN 2000 
typedef struct Deque{ 
    int *data; 
    int size; 
    int head; 
    int tail; 
    int max_size; 
}Deque; 
 
Deque *createQueue(int len){ 
    Deque *tmp = (Deque*)malloc(sizeof(Deque)); 
    if(tmp == NULL){ 
        perror("no free mem tmp"); 
        exit(EXIT_FAILURE); 
    } 
 
    int *data = (int*)malloc(sizeof(int) * len); 
    if(data == NULL){ 
        perror("no free mem data"); 
        exit(EXIT_FAILURE); 
    } 
    tmp->data = data; 
    tmp->head = 0; 
    tmp->tail = 0; 
    tmp->max_size = len; 
    tmp->size = 0; 
    return tmp; 
} 
 
 
void pushFront(Deque *q, int x){ 
    if((q->size == q->max_size)){ 
        printf("error\n"); 
        return ; 
    } 
 
    q->head = (q->head - 1 + q->max_size) % q->max_size; 
    *(q->data + q->head) = x; 
    q->size++; 
 
} 
 
 
void pushBack(Deque *q, int x){ 
    if((q->size == q->max_size)){ 
        printf("error\n"); 
        return; 
    } 
 
    *(q->data + q->tail) = x; 
    q->tail = (q->tail + 1 + q->max_size) % q->max_size; 
    q->size++; 
} 
 
int popBack(Deque *q){ 
    if(q->size == 0 || q == NULL){ 
        return INT_MAX; 
    } 
     
    q->tail = (q->tail - 1 + q->max_size) % q->max_size; 
    int x = *(q->data + q->tail); 
    q->size--; 
    return x; 
} 
 
 
int popFront(Deque *q){ 
    if(q->size == 0 || q == NULL){ 
        return INT_MAX; 
    } 
 
    int x = *(q->data + q->head); 
    q->head = (q->head + 1) % q->max_size; 
    q->size--; 
    return x; 
} 
 
void freeQueue(Deque *q){ 
    if (q == NULL) return; 
    free(q->data); 
    free(q); 
} 
 
void printList(Deque *q){ 
    if (q == NULL || q->size == 0) { 
        printf("empty\n"); 
        return; 
    } 
 
    int h = q->head; 
    for(int i = 0; i < q->size; i++){ 
        printf("%d ", *(q->data + h)); 
        h = (h + 1) % q->max_size; 
    } 
    printf("\n"); 
} 
 
 
 
void cmdLine(Deque *q, int num_cmds){ 
    int num_cmds_l = 0; 
 
    while (num_cmds_l < num_cmds){ 
        char line[CMD_LINE_LEN]; 
 
        if(fgets(line, CMD_LINE_LEN, stdin) == NULL) break; 
 
        line[strcspn(line, "\n")] = 0; 
 
        char *cmd = strtok(line, " "); 
        if(cmd == NULL) continue; 
        // printf("%s\n", cmd); 
         
        if(strcmp(cmd, "push_back") == 0){ 
            // printf("!!!\n"); 
            char *arg_str = strtok(NULL, " "); 
            if (arg_str != NULL) { 
                int x = atoi(arg_str); 
                pushBack(q, x); 
            } 
        }else if(strcmp(cmd, "push_front") == 0){ 
            // printf("!!2!\n"); 
            char *arg_str = strtok(NULL, " "); 
            if (arg_str != NULL) { 
                int x = atoi(arg_str); 
                pushFront(q, x); 
            } 
        }else if(strcmp(cmd, "pop_front") == 0){ 
            // printf("!3!!\n"); 
            int v = popFront(q); 
            if(v == INT_MAX){ 
                printf("error\n"); 
            }else{ 
                printf("%d\n", v); 
            } 
        }else if(strcmp(cmd, "pop_back") == 0){ 
            // printf("!!4!\n"); 
            int v = popBack(q); 
            if(v == INT_MAX){ 
                printf("error\n"); 
            }else{ 
                printf("%d\n", v); 
            } 
        } 
        num_cmds_l++; 
    } 
} 
 
 
 
int main(void){ 
    int n, len; 
    scanf("%d%d", &n,  &len); 
 
    int c; 
    while ((c = getchar()) != '\n' && c != EOF);  
 
    Deque *q = createQueue(len); 
    cmdLine(q, n); 
 
    freeQueue(q); 
    exit(EXIT_SUCCESS); 
}