#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELETED "00000000"

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


int hash(char* key){
    int hash;
    int ascii_sum = 0;
    for(int i = 1; i <= strlen(key); i++){
        ascii_sum += ((int)key[i-1])*i;
    }
    hash = (19 * ascii_sum) % 101;
    return hash;
};

int ht_conflict(hash_t *hashtable, char *key, int pos){
    int newpos = pos;
    int k = 0;
    do{
        k++;
        newpos = (pos + k*k + 23*k) % 101; 
    } while(!(!(hashtable->entries[newpos]) || !(strcmp(hashtable->entries[pos]->key, DELETED)) || strcmp(hashtable->entries[newpos]->key, key) == 0 || k >= 19));

    return newpos;
}

int ht_find(hash_t *hashtable, char* key){
    int pos = hash(key);
    int newpos = pos;

    if((hashtable->entries[pos]) && ((strcmp(hashtable->entries[pos]->key, DELETED) != 0))){   
        if(strcmp(hashtable->entries[pos]->key, key) != 0){
            newpos = ht_conflict(hashtable, key, pos);
        }
        pos = newpos;
    } 

    return pos;
};

void ht_insert(hash_t *hashtable, char* key){
    int slot = ht_find(hashtable, key);

    if(!(hashtable->entries[slot]) || !(strcmp(hashtable->entries[slot]->key, DELETED))){
        hashtable->entries[slot] = ht_pair(key);
        hashtable->count += 1;
    }    
}

void ht_delete(hash_t *hashtable, char *key){
    int pos = ht_find(hashtable, key);
    if(hashtable->entries[pos] && !strcmp(hashtable->entries[pos]->key, key)){
        hashtable->entries[pos]->key = (char*)malloc(sizeof(char)*(strlen(DELETED) + 1));
        strcpy(hashtable->entries[pos]->key, DELETED);

        hashtable->count -= 1;
    }

}



int main(){
    int testcases;
    scanf("%d", &testcases);

    for(int i = 0; i < testcases; i++){
        hash_t *dict = ht_create(1500);


        int operations;
        scanf("%d", &operations);

        for(int j = 0; j < operations; j++){
            char input[1004];
            char operation[4];
            char string[1000];
            scanf("%s", input);
            strncpy(operation, input, 3);
            operation[4] = '\0';

            strcpy(string, input + 4);

            if(!strcmp(operation, "ADD")){
                ht_insert(dict, string);
            }
            else if(!strcmp(operation, "DEL")){
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