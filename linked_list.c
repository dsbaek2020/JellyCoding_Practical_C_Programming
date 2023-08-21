#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 예제용 구조체 정의
typedef struct {
    int studentID;
    char name[50];
    int age;
} Student;

// 연결 리스트의 노드 구조체
typedef struct ListNode {
    Student data;
    struct ListNode* next;
} ListNode;

// 연결 리스트의 헤드 노드를 가리키는 포인터
ListNode* head = NULL;

// 새로운 노드 생성
ListNode* createNode(Student student) {
    ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
    new_node->data = student;
    new_node->next = NULL;
    return new_node;
}

// 연결 리스트에 노드 추가
void insertNode(Student student) {
    ListNode* new_node = createNode(student);
    new_node->next = head;
    head = new_node;
}

// 연결 리스트에서 노드 삭제
void deleteNode(int studentID) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    ListNode* current = head;
    ListNode* previous = NULL;

    while (current != NULL) {
        if (current->data.studentID == studentID) {
            if (previous == NULL) {
                head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            printf("Node with Student ID %d deleted.\n", studentID);
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("Node with Student ID %d not found.\n", studentID);
}

// 연결 리스트 중간에 노드 추가
void insertAfter(int studentID, Student newStudent) {
    ListNode* current = head;

    while (current != NULL) {
        if (current->data.studentID == studentID) {
            ListNode* new_node = createNode(newStudent);
            new_node->next = current->next;
            current->next = new_node;
            printf("Node inserted after Student ID %d.\n", studentID);
            return;
        }
        current = current->next;
    }

    printf("Node with Student ID %d not found.\n", studentID);
}

// 연결 리스트 출력
void printList() {
    ListNode* current = head;
    while (current != NULL) {
        printf("Student ID: %d, Name: %s, Age: %d\n", current->data.studentID, current->data.name, current->data.age);
        current = current->next;
    }
}

// 연결 리스트 해제
void freeList() {
    ListNode* current = head;
    while (current != NULL) {
        ListNode* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    // 학생 정보를 추가하여 연결 리스트 생성
    Student student1 = {101, "Alice", 20};
    Student student2 = {102, "Bob", 22};
    Student student3 = {103, "John", 21};

    insertNode(student1);
    insertNode(student2);
    insertNode(student3);

    // 연결 리스트 출력
    printf("Original Student List:\n");
    printList();

    // 노드 삭제
    deleteNode(102);

    // 연결 리스트 출력
    printf("\nStudent List after Deletion:\n");
    printList();

    // 노드 추가
    Student newStudent = {104, "Eve", 23};
    insertAfter(101, newStudent);

    // 연결 리스트 출력
    printf("\nStudent List after Insertion:\n");
    printList();

    // 연결 리스트 해제
    freeList();

    return 0;
}
