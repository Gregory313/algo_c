/*https://contest.yandex.ru/contest/23815/run-report/140638313/



-- ПРИНЦИП РАБОТЫ --
Я релизовал быструю сортировку на основе функции корпаратора, которая опредлеяет последовательность 
выбора критериев для оценки места в массиве. Сортировка реализована полурекурсивным методом

вдохновенеим послужил комментарий на форуме от Pavel Mayorov: https://ru.stackoverflow.com/questions/1510818/%D0%98%D1%81%D0%BF%D0%BE%D0%BB%D1%8C%D0%B7%D1%83%D0%B5%D1%82%D1%81%D1%8F-%D0%BB%D0%B8-%D0%BD%D0%B5%D1%80%D0%B5%D0%BA%D1%83%D1%80%D1%81%D0%B8%D0%B2%D0%BD%D0%B0%D1%8F-%D1%80%D0%B5%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D1%8F-%D0%B1%D1%8B%D1%81%D1%82%D1%80%D0%BE%D0%B9-%D1%81%D0%BE%D1%80%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%BA%D0%B8-%D0%BD%D0%B0-%D1%80%D0%B5%D0%B0%D0%BB%D1%8C%D0%BD%D1%8B%D1%85-%D0%BF%D1%80%D0%BE%D0%B5%D0%BA%D1%82%D0%B0%D1%85

данный подход позволяет сократить использваоние рекурсии для ислюкчения переполенения стека

-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
весь массив группируется на основе опорного элемента, на основе уловия была составлена послдеователньость проверок
на их основе элементы распределяются как при обычной сортивке.
                                    
-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
поиск обьекта как и в бин поиске в худшем случае может занять  
O(n2) елси опорный элемент будет неудачно расположен в лучшем O(nlogn)

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ -
O(logn) так как дополнительной памяти не выделяется для проверок или хранения информации 
благодаря реалзации  in-place quick sort, но используется рекурсия


*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define CHUNK_SIZE 2
#define INITIAL_LINES_CAPACITY 2


typedef struct Person{
    char* name;
    int len;
    int ex_count;
    int mis_count;
}Person;

void swapPerson(Person **p1, Person **p2) {
    Person *temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

Person* readPerson(){
    size_t curr_capacity = CHUNK_SIZE;
    size_t len = 0;
    
    int ex_count = 0;
    int mis_count = 0;
    char name[256];

    char *bffr = (char*)malloc(sizeof(char) * curr_capacity + 1);
    if(bffr == NULL){
        perror("no mem alloc");
        return NULL;
    }

    while(fgets(bffr + len, curr_capacity - len - 1, stdin) != NULL){
    
        len = strlen(bffr);
        if(len > 0 &&  *(bffr + len - 1) == '\n'){
            len--;
            break;
        }

        curr_capacity *= 2;
        char *tmp = (char*)realloc(bffr, curr_capacity + 1);
        if(tmp == NULL){
            perror("no mem alloc");
            free(bffr);
            return NULL;
        }
        bffr = tmp;
    }

    if(len == 0 && feof(stdin)){
        free(bffr);
        return NULL;
    }

    sscanf(bffr, "%s %d %d", name, &ex_count, &mis_count);
    // printf("-------------- |%s| %d %d %d ------------\n", name, ex_count, mis_count, strlen(name));

    int w_len = strlen(name);
    strncpy(name, bffr, w_len);
    *(bffr + w_len) = '\0';

    char* sized_buff = (char*)realloc(bffr, len + 1);
    if(sized_buff == NULL){
        sized_buff = bffr;
    }

    Person *n_line = (Person*)malloc(sizeof(Person));
    if(n_line == NULL){
        perror("no mem alloc");
        free(bffr);
        return NULL;
    }

    n_line->len = w_len;
    n_line->name = sized_buff;
    n_line->ex_count = ex_count;
    n_line->mis_count = mis_count;

    return n_line;
}

Person** readStrings(int *lines_num){
    int capacity = INITIAL_LINES_CAPACITY;
    Person **lines = (Person**)malloc(sizeof(Person*) * capacity);
    if(lines == NULL){
        perror("no mem alloc");
        return NULL;
    }
   
    *lines_num = 0;

    for(;;){
        Person *curr_line = readPerson();
        if (curr_line == NULL) { break; }
        // printf("%d %d printf\n", curr_line, curr_line->len);     
        
        // if(curr_line->len == 0){
        //     break;
        // }

        if (*lines_num == capacity) {
            capacity *= 2;
            Person **tmp = (Person**)realloc(lines, sizeof(Person*) * capacity);
            if(tmp == NULL){
                for (size_t i = 0; i < *lines_num; i++){
                    free((*(lines + i))->name);
                    free(*(lines + i));
                }
                free(lines);
                *lines_num = 0;
                return NULL;
                
            }
            lines = tmp;
        }

        *(lines + *lines_num) = curr_line;
        (*lines_num)++;
    }

    if(*lines_num < capacity){
        Person **sized_lines = (Person**)realloc(lines, sizeof(Person*) * *lines_num);
        if(sized_lines != NULL){
            lines = sized_lines;
        }
    }
    return lines;
}

void freeLines(Person **lines, int num_lines){
    for(int i = 0; i < num_lines; i++){
        if(*(lines + i) != NULL){
            free((*(lines + i))->name);
            free(*(lines + i));
        }
    }
    free(lines);
}

int cmpCreteria(Person *pivot_p, Person *p){
    if(pivot_p->ex_count != p->ex_count){
        return pivot_p->ex_count- p->ex_count;
    }

    if(pivot_p->mis_count != p->mis_count){
        return p->mis_count - pivot_p->mis_count;
    }

    return strcmp(p->name, pivot_p->name);
}

int partition(Person **list, int low, int high){
    Person* pivot = *(list + high);
    int left = low;
    int right = high - 1;

    for(;;){
        while(left <= right && (cmpCreteria(pivot, *(list + left)) <= 0)){
            left++;
        }

        while(left <= right && (cmpCreteria(pivot, *(list + right)) > 0)){
            right--;
        }

        if(left > right){
            break;
        }else{
            swapPerson(((list + right)), ((list + left)));
        }
    }

    swapPerson(((list + left)), ((list + high)));
    return left;
}

void quickSort(Person **list, int low, int high){
    while(low < high){
        int pivot = partition(list, low, high);
        if(abs(pivot - low) < abs(pivot - high)){
            quickSort(list, low, pivot - 1);
            low = pivot + 1;
        }else{
            quickSort(list, pivot + 1, high);
            high = pivot - 1;
        }
    }
}


int main(void){

    int len = 0;
    scanf("%d\n", &len);

    Person **lines = readStrings(&len);

    quickSort(lines, 0, len - 1);

    for (int i = 0; i < len; i++){
        printf("%s\n",(*(lines + i))->name);               
    }


    freeLines(lines, len);
    exit(EXIT_SUCCESS);
}   