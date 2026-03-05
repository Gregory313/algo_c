/*
https://contest.yandex.ru/contest/24414/run-report/141536244/


-- ПРИНЦИП РАБОТЫ --
вдохновением в реализации хеш таблицы с закрытой адресацией послужил туториал:
https://learnc.info/adt/hashmap.html

Я реализавал хещ табилцу на основе односвязного списка (закрытая адресация)
Основная структура хранит в себе указатель на массив указателей  данных data, где каждый его элемент является началом списка конкретной корзины
size  - текущее количество элементов в таблице 
arr_size - размер таблицы
loadFactor - процент при достижении которого необходимо рехешировать табилцу
limit - порог для исключения разрастания таблицы
multiplier - миинимальный шаг с которым таблица будет расти

вставка - перед вставкой элемента в табилцу происходит проверка на заполненность таиблцы
если таблица занята на определенный процент, то происходит рехеширования для исключения частых коллизий
хеширование текущего ключа и поиск в какое ведро по какому индексу необходимо положить узел
Так как коллизии неисключены, происходит проход по односвязному списку до конца
для нахождения элемента с таким же ключом. 
При наличии в ведре такого же ключа, значение узла обновляется.
Иначе происходит вставка нового элемента.

рехеширование - создание новой таблицы на основе новых данных,
хеширование существующих элементов и запись в новую табилцу.
Так как рехеширование возможно при вставке новых данных, в ней же вызвается функция вставки после успещного рехеширования

получение элемента - расчет местоположения обьекта в таблице, поиск в корзине по списку до совпадения ключа

удаление элемента - расчет местоположения обьекта в таблице, поиск в корзине, удаление узла из односвязного списка



-- ВРЕМЕННАЯ СЛОЖНОСТЬ --

вставка (без учета рехеширования) - 
    хеширование ключа o1
    поиск корзины o1
    вставка в односвязный список o(n)(в худшем случае) (так как необзодима проверка на наличие существующего элемента с подобным ключом)
    о(1) (в лучше случае) если корзина путса

рехеширование O(n) так как необходимо перехешивароть и раскидать все элементы

получение элемента - о(1) (в лучше случае) - доступ по индексу
    o(n)(в худшем случае)  доступ по инедксу проход по односвязному списку

удаление элемента - о(1) (в лучше случае) - доступ по индексу
    o(n)(в худшем случае)  доступ по инедксу проход по односвязному списку



-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
удаление элемента - о(1)
получение элемента - о(1)
вставка (без учета рехеширования)- о(1)
рехеширование O(n)
создание таблицы O(n)

*/


#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <limits.h>

#define CMD_LINE_LEN 2000

unsigned long long hashcode(int key) {
    unsigned long long hash = (unsigned long long)key;
    hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
    hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
    hash = ((hash >> 16) ^ hash);
    return hash;
}


static const float LOAD_FACTOR = 0.72f;
static const size_t INITIAL_SIZE = 99;
static const float MULTIPLIER = 2.0f; 

typedef int K;
typedef int V;

typedef struct Entry{
	K key;
	V value;
}Entry;

typedef struct Node{
	Entry *value;
	struct Node *next;
}Node;

void freeEntry(Entry **e){
	free((*e));
	*e = NULL;
}

#define CMP_EQ(a, b) ((a) == (b))
#define HASHCODE(a)(hashcode(a))
#define FREE_ENTRY(a) (freeEntry(&a))

typedef struct  Hashmap{
	Node **data;
	size_t size;
	size_t arr_size;
	size_t limit;

	float loadFactor;
	float multiplier;
}Hashmap;

Hashmap* rehashT(Hashmap **h_map, Entry *e);

Hashmap* createHashmap(size_t limit, float loadFactor, float mul){
	Hashmap *tmp = (Hashmap*)malloc(sizeof(Hashmap));
	if (tmp == NULL) return NULL;	
	tmp->arr_size = (limit > 0) ? limit : INITIAL_SIZE;
 	tmp->loadFactor = (loadFactor >= LOAD_FACTOR && loadFactor <= 1.0f) ? loadFactor : LOAD_FACTOR;
	tmp->limit = (int)(tmp->loadFactor * tmp->arr_size);
	tmp->size = 0;
	tmp->multiplier = (mul >= MULTIPLIER) ? mul : MULTIPLIER;
	tmp->data = (Node**) calloc(tmp->arr_size, sizeof(Node*));
	if (tmp->data == NULL){ free(tmp); return NULL;}
	return tmp;
}

void rawPut(Hashmap **h_map, Entry *e){
	Hashmap *map = *h_map;

	if(map->size >= map->limit){
		*h_map = rehashT(h_map, e);
		return;
	}

	unsigned long long hash = HASHCODE(e->key);
	size_t index = (hash % map->arr_size);
	
	Node *curr_node = map->data[index];
	while(curr_node){
		if(CMP_EQ(curr_node->value->key, e->key)){
			V val = e -> value;
			free(e); 
			curr_node->value->value = val;
			return;
		}
		curr_node = curr_node->next;
	}

	Node *new_node = (Node*)malloc(sizeof(Node));
	if (new_node == NULL) return NULL;
	new_node->next = map->data[index];
	new_node->value = e;
	map->data[index] = new_node;
	(map)->size++;
}


void put(Hashmap ** h_map, K key, V value){
	Entry *e = (Entry*)malloc(sizeof(Entry));
	if (e == NULL) return NULL;
	e->key = key;
	e->value = value;
	rawPut(h_map, e);
}

Hashmap* rehashT(Hashmap **h_map, Entry *e){
	Hashmap *tmp_h = createHashmap((size_t)(*h_map)->arr_size * (*h_map)->multiplier,	(*h_map)->loadFactor, (*h_map)->multiplier);
	Hashmap *map = *h_map;
	Node *curr = NULL;
        Node *tmp = NULL;
	for(size_t i = 0; i < (*h_map)->arr_size; i++){
		curr = (map)->data[i];
		while(curr){
			tmp = curr->next;
			unsigned long long hash = HASHCODE(curr->value->key);
			size_t new_place = (hash % tmp_h->arr_size);
			curr->next = tmp_h->data[new_place];
			tmp_h->data[new_place] = curr;
			tmp_h->size++;
			curr = tmp;
		}
	}
	free(map->data);
	free(map);
	rawPut(&tmp_h, e);
	return tmp_h;
}

V get(Hashmap *map, K key){
	unsigned long long hash = HASHCODE(key);
	size_t index = (hash % map->arr_size);

	Node *curr = map->data[index];

	while(curr != NULL){
		if(CMP_EQ(curr->value->key, key)){
			return curr->value->value;
		}
		curr = curr->next;
	}
	return -1;
}

Entry* removeEl(Hashmap *map, K key){
	unsigned long long hash = HASHCODE(key);
	size_t index = (hash % map->arr_size);

	Node *curr = map->data[index];
	Node *prev = NULL;

	while(curr != NULL){
		if(CMP_EQ(key, curr->value->key)){
			Entry *e_node_del = curr->value;
			if(prev == NULL){
				map->data[index] = curr->next;
			}else{
				prev->next = curr->next;
			}
			free(curr);
			map->size--;
			return e_node_del;
		}
		prev = curr;
		curr = curr->next;
	}
	return NULL;
}

void deleteHashMap(Hashmap **h_map){
	Hashmap *map = *h_map;
	size_t size = map->arr_size;
	for (size_t i = 0; i < size; i++){
		Node *curr = map->data[i];
		while(curr){
			Node* tmp = curr->next;
			FREE_ENTRY(curr->value);
			free(curr);
			curr = tmp;
		}		
	}
	free(map->data);
	free(map);
	*h_map = NULL;
}

void cmdLine(Hashmap **q, int num_cmds){
    int num_cmds_l = 0;

    while (num_cmds_l < num_cmds){
        char line[CMD_LINE_LEN];

        if(fgets(line, CMD_LINE_LEN, stdin) == NULL) break;

        line[strcspn(line, "\n")] = 0;

        char *cmd = strtok(line, " ");
        if(cmd == NULL) continue;
        
        if(strcmp(cmd, "get") == 0){
            char *arg_str = strtok(NULL, " ");
            if (arg_str != NULL) {
                int x = atoi(arg_str);
                V value = get(*q, x);
				if(value != -1){
					printf("%d\n", value);
				}else{
                	printf("None\n");	
				}
            }
        }else if(strcmp(cmd, "put") == 0){
            char *arg_str = strtok(NULL, " ");
			char *arg_str2 = strtok(NULL, " ");
            if (arg_str != NULL) {
                int x = atoi(arg_str);
                int y = atoi(arg_str2);
                put(q, x, y);
            }
        }else if(strcmp(cmd, "delete") == 0){
            char *arg_str = strtok(NULL, " ");
            Entry *e = removeEl(*q, atoi(arg_str));
            if(e == NULL){
                printf("None\n");
            }else{
                printf("%d\n", e->value);
				FREE_ENTRY(e);
            }
        }
        num_cmds_l++;
    }
}


int main(void){
	Hashmap *my_map = createHashmap(INITIAL_SIZE, LOAD_FACTOR, MULTIPLIER);
	int len;
    scanf("%d",&len);

    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
	cmdLine(&my_map, len); 

	deleteHashMap(&my_map);
	exit(EXIT_SUCCESS);
}
