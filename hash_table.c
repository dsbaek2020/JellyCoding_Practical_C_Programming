#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct {
    int age;
    char address[100];
} Person;

typedef struct Entry {
    char* key; // 키 값 (문자열)
    Person value; // 값 (Person 구조체)
    struct Entry* next; // 다음 엔트리를 가리키는 포인터 (충돌 처리를 위한 연결 리스트)
} Entry;

typedef struct HashTable {
    Entry* buckets[TABLE_SIZE]; // 해시 테이블 버킷 배열
} HashTable;

unsigned int hash(const char* key) {
    unsigned int hash_val = 0;
    while (*key) {
        hash_val = (hash_val << 5) + *key++; // 문자열을 해싱하기 위한 연산
    }
    return hash_val % TABLE_SIZE; // 해시 값 계산 후 버킷 크기로 나누어 인덱스 계산
}

Entry* createEntry(const char* key, Person value) {
    Entry* new_entry = (Entry*)malloc(sizeof(Entry)); // 새 엔트리 메모리 할당
    new_entry->key = strdup(key); // 키 값을 복제하여 할당
    new_entry->value = value; // 값 복사
    new_entry->next = NULL; // 다음 엔트리 포인터 초기화
    return new_entry;
}

void insertEntry(HashTable* ht, const char* key, Person value) {
    unsigned int index = hash(key); // 해시 값으로 인덱스 계산
    Entry* new_entry = createEntry(key, value); // 새 엔트리 생성

    // 같은 인덱스에 이미 엔트리가 있을 경우 연결 리스트로 추가
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

void deleteEntry(HashTable* ht, const char* key) {
    unsigned int index = hash(key); // 해시 값으로 인덱스 계산
    Entry* current = ht->buckets[index];
    Entry* previous = NULL;

    // 연결 리스트에서 키에 해당하는 엔트리 찾아 삭제
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (previous == NULL) {
                ht->buckets[index] = current->next;
            } else {
                previous->next = current->next;
            }
            free(current->key); // 키 메모리 해제
            free(current); // 엔트리 메모리 해제
            printf("Key %s 삭제됨.\n", key);
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("Key %s를 찾을 수 없음.\n", key);
}

void freeHashTable(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry* entry = ht->buckets[i];
        while (entry != NULL) {
            Entry* temp = entry;
            entry = entry->next;
            free(temp->key); // 키 메모리 해제
            free(temp); // 엔트리 메모리 해제
        }
    }
}

int main() {
    HashTable ht;
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht.buckets[i] = NULL;
    }

    // 예제 데이터 생성
    Person person1 = {25, "123번지"};
    Person person2 = {32, "456번지"};
    Person person3 = {28, "789번지"};

    // 데이터 삽입
    insertEntry(&ht, "John", person1);
    insertEntry(&ht, "Alice", person2);
    insertEntry(&ht, "Bob", person3);

    printf("초기 해시 테이블:\n");
    deleteEntry(&ht, "Alice"); // "Alice" 키의 엔트리 삭제
    deleteEntry(&ht, "Eve"); // 존재하지 않는 키 삭제 시도

    // 해시 테이블 메모리 해제
    freeHashTable(&ht);

    return 0;
}
