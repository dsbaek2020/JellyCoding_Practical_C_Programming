#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct {
    int age;
    char address[100];
} Person;

typedef struct Entry {
    char* key;
    Person value;
    struct Entry* next;
} Entry;

typedef struct HashTable {
    Entry* buckets[TABLE_SIZE];
} HashTable;

unsigned int hash(const char* key) {
    unsigned int hash_val = 0;
    while (*key) {
        hash_val = (hash_val << 5) + *key++;
    }
    return hash_val % TABLE_SIZE;
}

Entry* createEntry(const char* key, Person value) {
    Entry* new_entry = (Entry*)malloc(sizeof(Entry));
    new_entry->key = strdup(key);
    new_entry->value = value;
    new_entry->next = NULL;
    return new_entry;
}

void insertEntry(HashTable* ht, const char* key, Person value) {
    unsigned int index = hash(key);
    Entry* new_entry = createEntry(key, value);

    // 충돌 처리: 같은 인덱스에 이미 다른 엔트리가 있으면 연결 리스트로 연결
    if (ht->buckets[index] == NULL) {
        ht->buckets[index] = new_entry;
    } else {
        Entry* current = ht->buckets[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_entry;
    }
}

Person findValue(HashTable* ht, const char* key) {
    unsigned int index = hash(key);
    Entry* entry = ht->buckets[index];

    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }

    Person empty_person = {0, ""};
    return empty_person;
}

void freeHashTable(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry* entry = ht->buckets[i];
        while (entry != NULL) {
            Entry* temp = entry;
            entry = entry->next;
            free(temp->key);
            free(temp);
        }
    }
}

int main() {
    HashTable ht;
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht.buckets[i] = NULL;
    }

    Person person1 = {25, "123 Main St"};
    Person person2 = {32, "456 Elm St"};
    Person person3 = {28, "789 Oak St"};

    insertEntry(&ht, "John", person1);
    insertEntry(&ht, "Alice", person2);
    insertEntry(&ht, "Bob", person3);

    Person johnInfo = findValue(&ht, "John");
    Person aliceInfo = findValue(&ht, "Alice");
    Person bobInfo = findValue(&ht, "Bob");

    printf("John's Age: %d, Address: %s\n", johnInfo.age, johnInfo.address);
    printf("Alice's Age: %d, Address: %s\n", aliceInfo.age, aliceInfo.address);
    printf("Bob's Age: %d, Address: %s\n", bobInfo.age, bobInfo.address);

    freeHashTable(&ht);

    return 0;
}
