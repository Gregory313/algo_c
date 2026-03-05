/* 
https://contest.yandex.ru/contest/22781/run-report/140379553/ 
 
-- ПРИНЦИП РАБОТЫ -- 
Я реализовал хранение данных на стеке. 
Есди на вход пришло число, оно заносится в стек 
КОгда встречается оператор, происходит выделелния из стека двух чисел 
В конце вычислений результат вычислений будет в стеке один 
 
 
-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ -- 
 
Стек -- это порядок LIFO. Который обеспечивает приавльный порядок рассчетов.  
Так как при встрече с числом он ожидает нужный оператор для выполнения действия, 
так как действия могу быть вложенными, результат операции будет использван далее. 
 
 
-- ВРЕМЕННАЯ СЛОЖНОСТЬ -- 
Добавление в стек стоит O(1). 
Извлечение из стека стоит O(1). 
Обарботака строки выражиния O(n).  
 
 
-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ -- 
Выражение содержит n элементов.  
Каждый элемент стека занимает константное количество памяти. 
Стек, содержащий k элементов, занимает O(k) памяти. 
*/ 
 
 
#include <stdlib.h> 
#include <stdio.h> 
#include <limits.h> 
#include <string.h> 
 
#define CMD_LINE_LEN 1256 
 
typedef struct Node{ 
    int value; 
    struct Node *next; 
}Node; 
 
 
 
void push(Node **h, int v){ 
    Node *tmp = (Node*)malloc(sizeof(Node)); 
    if(tmp == NULL){ 
        printf("no free mem node\n");       
    } 
 
    tmp->value = v; 
 
    if((*h) != NULL){ 
        tmp->next = *h; 
    } 
    (*h) = tmp; 
} 
 
int pop(Node **h){ 
    if(h == NULL  || *h == NULL){ 
        printf("error\n");  
        return INT_MAX; 
    } 
 
    Node *tmp = (*h)->next; 
    int v = (*h)->value; 
    free(*h); 
    *h = tmp; 
    return v; 
} 
 
void freeStack(Node **h){ 
    Node *tmp = *h; 
    while(tmp != NULL){ 
        Node *t = tmp->next; 
        free(tmp); 
        tmp = t; 
    } 
    *h = NULL; 
} 
 
void printStack(Node *h){ 
    if(h == NULL){ 
        printf("error\n");  
        return; 
    } 
 
    Node *tmp = h; 
    while(tmp != NULL){ 
        printf("%d ", tmp->value); 
        tmp = tmp->next; 
    } 
    printf("\n"); 
} 
 
int checkSymbol(char symb, Node **h){ 
    int b = 0; 
    int a = 0; 
 
    switch (symb){ 
    case '+': 
        return pop(h) + pop(h); 
    case '-': 
        b = pop(h); 
        a = pop(h); 
        return (a - b); 
    case '/': 
        b = pop(h); 
        a = pop(h); 
 
        if (b == 0) { 
            return INT_MAX; 
        } 
         
        int res = a / b; 
        int rem = a % b; 
 
        if (rem != 0 && a < 0) { 
            return res - 1; 
        } else { 
            return res; 
        } 
 
    case '*': 
        return pop(h) * pop(h); 
    default: 
        return symb - '0'; 
    } 
} 
 
void readLine(Node **h){    
    char line[CMD_LINE_LEN]; 
    fgets(line, CMD_LINE_LEN, stdin); 
     
    int i = 0, j = 0; 
    char num[6]; 
    memset(num, 0, sizeof(num)); 
    int res = INT_MAX; 
    size_t len = strlen(line); 
 
    if (len > 0 && *(line + len - 1) == '\n') { 
        *(line + len - 1) = ' '; 
        len--;  
    } 
     
    if (len < CMD_LINE_LEN - 1) {  
        *(line + len) = ' '; 
        *(line + len + 1) = '\0'; 
    } else { 
        *(line + CMD_LINE_LEN - 1) = '\0'; 
    } 
 
    while (*(line + i) != '\0') { 
        if(*(line + i) == ' '){ 
            *(num + j) = '\0'; 
 
            if((*(num) > 48 && *(num) < 58) || (*num == '-' && j > 1)){ 
                push(h, atoi(num)); 
                // printf(" | %s %d | \n", num, atoi(num)); 
            }else{ 
                res = checkSymbol(*num, h); 
                // printf(" | %d RR| \n", res); 
                push(h, res); 
            } 
 
            memset(num, 0, sizeof(num)); 
            j = 0; 
        }else{ 
            *(num + j) = *(line + i); 
            j++; 
        } 
        i++; 
    } 
} 
 
 
 
int main(void){ 
    Node *base = NULL; 
    readLine(&base); 
 
    printf("%d ", pop(&base)); 
 
 
    freeStack(&base); 
    exit(EXIT_SUCCESS); 
} 
