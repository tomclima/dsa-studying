#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int NULLPOS = 1500;

const char *DELETED = "00000000";


typedef struct entry_t{
    char *key;
    struct entry_t *next;
} entry_t;

entry_t *ht_pair(char* key){
    entry_t *entry = (entry_t *)malloc(sizeof(entry_t));
    entry->key = (char *)malloc(sizeof(char) * (strlen(key) +1));
    entry->next = NULL;

    strcpy(entry->key, key);

    return entry;
}

typedef struct hash_t {
    int size;
    int count;
    entry_t **entries;
} hash_t;

hash_t *ht_create(int size){
    hash_t *hashtable = (hash_t *)malloc(sizeof(hash_t)*1);
    hashtable->entries = (entry_t**)malloc(sizeof(entry_t*)*size);
    hashtable->count = 0;
    hashtable->size = size;

    for(int i = 0; i < size; i++){
        hashtable->entries[i] = NULL;
    }

    return hashtable;
};


int ht_hash(char* key){
    int hash;
    int ascii_sum = 0;
    for(int i = 1; i <= strlen(key); i++){
        ascii_sum += ((int)key[i-1])*i;
    }
    hash = (19 * ascii_sum) % 101;
    return hash;
};

int ht_probing(int pos, int j){
    return (pos + j*j + 23*j) % 101; 
}

int ht_find(hash_t *hashtable, char* key){
    int pos = ht_hash(key);
    int hash = pos;
    for(int j = 0; j < 20; j++){
        pos = ht_probing(hash, j);
        if(hashtable->entries[pos] && (!strcmp(hashtable->entries[pos]->key, key))){return pos;} // Se encontra a key exata, retorna a sua posição
        if(!hashtable->entries[pos]){return NULLPOS;}
    } 

    return NULLPOS; //em todos os outros casos, retorna a NULLPOS, que indica erro
}
      

void ht_insert(hash_t *hashtable, char* key){

    int find = ht_find(hashtable, key);


    if(find == NULLPOS){ // Apenas realiza a inserção caso a key não tenha sido encontrada
        int slot = ht_hash(key);
        int hash = slot;
        for(int i = 0; i < 20; i++){
            slot = ht_probing(hash, i);
            if(!hashtable->entries[slot] || !strcmp(hashtable->entries[slot]->key, DELETED)){ //insere ao primeiro espaço vazio ou deletado
                hashtable->entries[slot] = ht_pair(key);
                hashtable->count += 1;
                return;
            }
        }
    }
    
}

void ht_delete(hash_t *hashtable, char *key){
    int pos = ht_find(hashtable, key);
    if(pos != NULLPOS){ //apenas deleta caso a key exata tenha sido encontrada
        hashtable->entries[pos]->key = (char*)malloc(sizeof(char)*(strlen(DELETED) + 1));
        strcpy(hashtable->entries[pos]->key, DELETED);
        hashtable->count -= 1;
    }

}



int main(){
    int testcases;
    scanf("%d", &testcases);

    for(int i = 0; i < testcases; i++){
        
        int commands;
        scanf("%d", &commands);

        hash_t *dict = ht_create(1500);



        for(int j = 0; j < commands; j++){
            char input[1004];
            char operation[4];
            char string[1000];
            scanf("%s", input);
            strncpy(operation, input, 3);
            operation[4] = '\0';

            strcpy(string, input + 4);

            if(!strcmp(operation, "ADD") && (strcmp(string, "") != 0)){
                ht_insert(dict, string);
            }
            else if(!strcmp(operation, "DEL") && (strcmp(string, "") != 0)){
                ht_delete(dict, string);
            }
        }

        printf("%d\n", dict->count);
        for(int k = 0; k < dict->size; k++){
            if(dict->entries[k] && strcmp(dict->entries[k]->key, DELETED) != 0){
                printf("%d:%s\n", k, dict->entries[k]->key);
            }
        }

        free((void*)dict);
    }
}