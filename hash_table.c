#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

// 예제용 구조체 정의
typedef struct {
    int age;
    char address[100];
} Person;

// 해시 테이블의 버킷 구조체
typedef struct Entry {
    char* key;
    Person value;
    struct Entry* next;
} Entry;

// 해시 테이블 구조체
typedef struct HashTable {
    Entry* buckets[TABLE_SIZE];
} HashTable;

// 해시 함수
unsigned int hash(const char* key) {
    unsigned int hash_val = 0;
    while (*key) {
        hash_val = (hash_val << 5) + *key++;
    }
    return hash_val % TABLE_SIZE;
}

// 해시 테이블 초기화
void initHashTable(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->buckets[i] = NULL;
    }
}

// 새로운 엔트리 생성
Entry* createEntry(const char* key, Person value) {
    Entry* new_entry = (Entry*)malloc(sizeof(Entry));
    new_entry->key = strdup(key);
    new_entry->value = value;
    new_entry->next = NULL;
    return new_entry;
}

// 해시 테이블에 엔트리 추가
void insertEntry(HashTable* ht, const char* key, Person value) {
    unsigned int index = hash(key);
    Entry* new_entry = createEntry(key, value);

    // 연결 리스트의 가장 앞에 새 엔트리를 추가
    new_entry->next = ht->buckets[index];
    ht->buckets[index] = new_entry;
}

// 키를 이용하여 해시 테이블에서 값을 찾음
Person findValue(HashTable* ht, const char* key) {
    unsigned int index = hash(key);
    Entry* entry = ht->buckets[index];

    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }

    // 존재하지 않는 경우, 초기화된 값을 반환
    Person empty_person = {0, ""};
    return empty_person;
}

// 해시 테이블 해제
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
    initHashTable(&ht);

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
