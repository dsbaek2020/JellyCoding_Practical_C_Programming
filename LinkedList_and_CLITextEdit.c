///////////////////////////////////////
//  단일 연결 리스트(Linked List) 개념도
//
//   [head] -> [data|next] -> [data|next] -> [data|next] -> NULL
//             노드1        노드2           노드3
//
//   각 노드는 data(데이터)와 next(다음 노드 주소)를 가짐
//   head는 첫 번째 노드를 가리킴
///////////////////////////////////////

//
//  main.c
//  heapTest
//
//  Created by 젤리코딩학원(백대성) + 박솔 on 2/2/26.
//

#include <stdlib.h>   // 동적 메모리 할당(malloc, free) 함수 사용을 위한 헤더
#include <stdio.h>    // 입출력 함수(printf 등) 사용을 위한 헤더
#include <ctype.h>
#ifdef _WIN32
#include <windows.h>
#endif

int getch(void);

unsigned int a;     // 0 ~ (2^32)-1 까지 저장하는 4바이트 정수
unsigned int b;     // 예시용 전역 변수
unsigned int c;     // 예시용 전역 변수


typedef unsigned int uint32;      // 32비트 부호 없는 정수의 별칭
typedef unsigned char uint8;      // 8비트 부호 없는 정수의 별칭

uint32 d;            // uint32 타입 예시 변수
uint8 sensor_temp1;  // 센서 데이터 저장 예시 변수


/*
  ┌─────────────┐      next      ┌─────────────┐      next      ┌─────────────┐
  │  ListNode   │──────────────→│  ListNode   │──────────────→│  ListNode   │→ NULL
  │  data, next │               │  data, next │               │  data, next │
  └─────────────┘               └─────────────┘               └─────────────┘
    (단일 연결리스트의 노드)
*/
// 단일 연결 리스트의 노드 구조체 정의
typedef struct ListNode {
    char data;                // 노드에 저장될 데이터(문자형)
    struct ListNode* next;    // 다음 노드를 가리키는 포인터
} ListNode;


// 함수 포인터 타입 정의: 리스트 메서드용
struct List;
typedef void (*AppendFunc)(struct List*, char);            // 요소 추가 함수 포인터 타입
typedef void (*PrintFunc)(struct List*);                   // 리스트 출력 함수 포인터 타입
typedef char (*ReadByIndexFunc)(struct List*, int);        // 인덱스로 값 읽기 함수 포인터 타입
typedef void (*FreeFunc)(struct List*);                    // 리스트 메모리 해제 함수 포인터 타입
typedef void (*InsertFunc)(struct List*, int, char);       // 요소 삽입 함수 포인터 타입
typedef void (*DeleteByIndexFunc)(struct List*, int);      // 인덱스 삭제 함수 포인터 타입


/*
  ┌─────────────┐
  │ List       │
  │ ┌─────────┐│
  │ │ head    ││ ──────┐
  │ └─────────┘│       │
  │ ┌─────────┐│       │ next
  │ │ size    ││       ▼
  │ └─────────┘│  ┌─────────────┐      ┌─────────────┐
  │ ┌─────────┐│  │ ListNode    │─────>│ ListNode    │─...
  │ │ append  ││  │  data, next │      └─────────────┘
  │ └─────────┘│
  │ ┌─────────┐│  (함수 포인터: 리스트 메서드 역할 수행)
  │ │ print   ││
  │ └─────────┘│
  │ ┌─────────┐│
  │ │ readByIdx││
  │ └─────────┘│
  │ ┌─────────┐│
  │ │ free    ││
  │ └─────────┘│
  │ ┌─────────┐│
  │ │ insert  ││
  │ └─────────┘│
  │ ┌─────────┐│
  │ │ deleteByIndex│
  │ └─────────┘│
  └─────────────┘
  (단일 연결 리스트 구조체: 노드 연결 + 함수 포인터 포함)
*/
// 단일 연결 리스트 구조체 정의 (메서드처럼 함수 포인터를 포함)
typedef struct List {
    ListNode* head;         // 리스트의 첫 번째 노드를 가리키는 포인터
    int size;               // 리스트에 저장된 노드 개수
    AppendFunc append;      // append 메서드 함수 포인터
    PrintFunc print;        // print 메서드 함수 포인터
    ReadByIndexFunc readByIndex; // readByIndex 메서드 함수 포인터
    FreeFunc free;          // free 메서드 함수 포인터
    InsertFunc insert;      // insert 메서드 함수 포인터
    DeleteByIndexFunc deleteByIndex; // deleteByIndex 메서드 함수 포인터
} List;


/*
  ┌─────────────────────────────────────────────┐
  │                 TextBox                      │
  │ ┌─────────────┐   ┌───────────────────────┐ │
  │ │ text        │→  │ List (문자열 저장용)  │ │
  │ └─────────────┘   └───────────────────────┘ │
  │ ┌─────────────┐                               │
  │ │ cursor_index│                               │
  │ └─────────────┘                               │
  │ ┌─────────────┐ ┌─────────────────────────┐ │
  │ │ insert      │ │ 문자 삽입 메서드         │ │
  │ │ deleteAfter │ │ 커서 뒤 삭제 메서드      │ │
  │ │ deleteBefore│ │ 커서 앞 삭제 메서드      │ │
  │ │ moveLeft    │ │ 커서 왼쪽 이동 메서드    │ │
  │ │ moveRight   │ │ 커서 오른쪽 이동 메서드  │ │
  │ │ printBubble │ │ 말풍선 출력 메서드       │ │
  │ │ editLoop    │ │ 편집 루프 메서드         │ │
  │ └─────────────┘ └─────────────────────────┘ │
  └─────────────────────────────────────────────┘
*/
// 텍스트 박스 구조체: 내부에 List와 커서 위치 보유, 편집 메서드 함수포인터 포함
typedef struct TextBox TextBox;
struct TextBox {
    List text;              // 텍스트 내용 저장용 리스트
    int cursor_index;       // 커서 위치 (0~size)
    // 메서드용 함수 포인터
    void (*insert)(TextBox*, char);
    void (*deleteAfter)(TextBox*);
    void (*deleteBefore)(TextBox*);
    void (*moveLeft)(TextBox*);
    void (*moveRight)(TextBox*);
    void (*printBubble)(TextBox*);
    void (*editLoop)(TextBox*);
};


/*
  [입력]   [리스트], [데이터]
  └───────────────┐
                  ▼
          [새 노드 생성]
                  │
        [리스트가 비었는가?]
          ├─ 예: [head로 지정]
          └─ 아니오: [마지막 노드까지 이동하여 next에 연결]
                  │
            [size 증가]
                  ▼
                [함수 종료]
 */
// 리스트에 새로운 데이터를 추가하는 함수
void List_append(List* list, char data) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode)); // 새로운 노드 동적 할당
    node->data = data;         // 데이터 저장
    node->next = NULL;         // 마지막 노드이므로 next는 NULL

    if (list->head == NULL){   // 리스트가 비어 있는 경우(첫 노드 추가 상황)
        list->head = node;     // 방금 만든 노드를 head로 지정
    } else {                   // 이미 노드가 하나 이상 존재할 때
        ListNode* lastNode = list->head; // head부터 시작
        while (lastNode->next)             // 마지막 노드까지 탐색
            lastNode = lastNode->next;
        lastNode->next = node;             // 마지막 노드의 next에 새 노드 연결
    }
    list->size++;              // 리스트 크기 1 증가
}


/*
  [입력]   [리스트], [인덱스], [데이터]
  └───────────────┐
                  ▼
          [인덱스 범위 검사]
                  │
         (범위 초과 시 에러 출력 후 종료)
                  │
        [index==0?]
          ├─ 예: [head 앞 삽입]
          └─ 아니오: [index-1 노드까지 이동하여 연결 조정]
                  │
            [size 증가]
                  ▼
                [함수 종료]
 */
// 원하는 위치에 데이터를 삽입하는 함수
void List_insert(List* list, int index, char data) {
    if (index < 0 || index > list->size) {
        printf("Index out of range!\n");
        return;
    }
    ListNode* node = (ListNode*)malloc(sizeof(ListNode)); // 새로운 노드 동적 할당
    node->data = data;      // 데이터 저장

    if (index == 0) {
        // 인덱스가 0이면 head 앞에 삽입
        node->next = list->head; // 기존 head를 다음 노드로 연결
        list->head = node;       // 새 노드를 head로 지정
    } else {
        // 그 외에는 인덱스 바로 앞 노드를 찾아 연결 변경
        ListNode* prev = list->head;
        for (int i = 0; i < index - 1; ++i)
            prev = prev->next;
        node->next = prev->next;
        prev->next = node;
    }
    list->size++;  // 리스트 크기 증가
}


/*
  [입력]   [리스트], [인덱스]
  └───────────────┐
                  ▼
          [인덱스 범위 검사]
                  │
         (범위 초과 시 에러 출력 후 종료)
                  │
        [index==0?]
          ├─ 예: [head 삭제 후 head를 다음 노드로]
          └─ 아니오: [index-1 노드까지 이동 후 다음 노드 삭제]
                  │
            [size 감소]
                  ▼
                [함수 종료]
 */
// 리스트에서 인덱스 위치 노드를 삭제하는 함수
void List_deleteByIndex(List* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Index out of range!\n");
        return;
    }

    if (index == 0) {
        ListNode* toDelete = list->head;
        list->head = toDelete->next;
        free(toDelete);
    } else {
        ListNode* prev = list->head;
        for (int i = 0; i < index - 1; ++i) {
            prev = prev->next;
        }
        ListNode* toDelete = prev->next;
        prev->next = toDelete->next;
        free(toDelete);
    }
    list->size--;
}


/*
  [입력]   [리스트]
  └───────────────┐
                  ▼
        [현재 노드 = head]
                  │
        [NULL이 될 때까지 data 출력]
                  │
              [줄바꿈]
                  ▼
                [함수 종료]
 */
// 리스트 전체 내용을 출력하는 함수 (숫자형 기반 출력)
// 내부적으로 쓰이고, CLI용은 별도로 처리
void List_print(List* list) {
    ListNode* node = list->head;  // head에서부터 시작
    printf("[ ");
    while (node) {                // 노드가 NULL이면 끝
        printf("%d ", node->data); // 각 노드의 데이터 출력
        node = node->next;         // 다음 노드로 이동
    }
    printf("]\n");
}


/*
  [입력]   [리스트], [인덱스]
  └───────────────┐
                  ▼
          [인덱스 범위 검사]
                  │
         (범위 초과 시 에러 출력 및 0 반환)
                  │
        [head 노드부터 인덱스까지 노드 이동]
                  │
          [해당 노드의 데이터 반환]
                  ▼
                [함수 종료]
 */
char List_readByIndex(List* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Index out of range!\n"); // 범위 초과시 오류 출력
        return 0;
    }
    ListNode* node = list->head;
    for (int i = 0; i < index; ++i) // 원하는 인덱스까지 이동
        node = node->next;
    return node->data;              // 해당 노드의 데이터 반환
}


/*
  [입력]   [리스트]
  └───────────────┐
                  ▼
        [현재 노드 = head]
                  │
        [다음 노드 보관 후 현재 free]
                  │
        [현재 = 다음으로 이동하며 반복]
                  │
      [head = NULL, size = 0 설정]
                  ▼
                [함수 종료]
 */
// 리스트 전체 노드 메모리를 해제하는 함수
void List_free(List* list) {
    ListNode* node = list->head;
    while (node) {
        ListNode* next = node->next; // 다음 노드 미리 저장
        free(node);                  // 현재 노드 메모리 해제
        node = next;                 // 다음 노드로 이동
    }
    list->head = NULL;               // head 초기화
    list->size = 0;                  // 크기 0으로 초기화
}

/*
  [입력]   [리스트]
  └───────────────┐
                  ▼
        [head=NULL, size=0 초기화]
                  │
     [함수 포인터 바인딩(append/print/...)]
                  ▼
                [함수 종료]
 */
// 리스트 구조체를 초기화하고 함수 포인터를 연결하는 함수
void List_init(List* list) {
    list->head = NULL;                   // head 포인터 초기화
    list->size = 0;                      // 크기 0으로 초기화
    list->append = List_append;          // append 메서드 지정
    list->print = List_print;            // print 메서드 지정
    list->readByIndex = List_readByIndex;// readByIndex 메서드 지정
    list->free = List_free;              // free 메서드 지정
    list->insert = List_insert;          // insert 메서드 지정
    list->deleteByIndex = List_deleteByIndex; // deleteByIndex 메서드 지정
}


/* 
 * TextBox용 멤버 함수 구현
 * 리스트와 커서 위치를 내부에서 관리하며 동작
 */

// 터미널 화면을 지우고 커서를 홈으로 이동 (플랫폼별 처리)
static void clearScreen(void) {
#ifdef _WIN32
    // Windows 콘솔: 화면 지우고 커서를 (0,0)으로 이동
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD cellCount;
    DWORD count;
    COORD home = {0, 0};

    if (!GetConsoleScreenBufferInfo(hOut, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    // 화면을 공백으로 채움
    FillConsoleOutputCharacter(hOut, (TCHAR)' ', cellCount, home, &count);
    // 속성도 초기화
    FillConsoleOutputAttribute(hOut, csbi.wAttributes, cellCount, home, &count);
    // 커서 홈으로 이동
    SetConsoleCursorPosition(hOut, home);
#else
    // 유닉스 계열: ESC[2J 화면 지우기, ESC[H 커서 홈 이동
    printf("\033[2J\033[H");
    fflush(stdout);
#endif
}

// 말풍선 형태로 텍스트와 커서 출력
void TextBox_printBubble(TextBox* tb) {
    clearScreen();
    int len = tb->text.size;

    // 위쪽 말풍선 선 (╭───╮)
    printf("╭");
    for (int i = 0; i < len + 1; i++) { // +1은 커서 공간 포함
        printf("─");
    }
    printf("╮\n");

    // 내용 출력
    // '│ ' 문자들 ' |' 형태
    printf("│");
    for (int i = 0; i <= len; i++) {
        if (i == tb->cursor_index) {
            // 커서 위치 - '|' 출력
            printf("|");
        }
        if (i < len) {
            // 문자 출력
            char ch = tb->text.readByIndex(&tb->text, i);
            printf("%c", ch);
        }
    }
    printf("│\n");

    // 아래쪽 말풍선 선 (╰───╯)
    printf("╰");
    for (int i = 0; i < len + 1; i++) {
        printf("─");
    }
    printf("╯");
    fflush(stdout);
}

// 커서 왼쪽 이동
void TextBox_moveLeft(TextBox* tb) {
    if (tb->cursor_index > 0) {
        tb->cursor_index--;
    }
}

// 커서 오른쪽 이동
void TextBox_moveRight(TextBox* tb) {
    if (tb->cursor_index < tb->text.size) {
        tb->cursor_index++;
    }
}

// 커서 뒤에 문자 삽입 (커서가 가리키는 위치 바로 뒤)
void TextBox_insert(TextBox* tb, char ch) {
    tb->text.insert(&tb->text, tb->cursor_index, ch);
    tb->cursor_index++;
}

// 커서 뒤 노드 삭제 (커서가 가리키는 위치 뒤 노드 삭제)
void TextBox_deleteAfter(TextBox* tb) {
    if (tb->cursor_index < tb->text.size) {
        tb->text.deleteByIndex(&tb->text, tb->cursor_index);
        if (tb->cursor_index > tb->text.size) {
            tb->cursor_index = tb->text.size;
        }
    }
}

// 커서 앞 노드 삭제 (커서 바로 앞 노드 삭제)
void TextBox_deleteBefore(TextBox* tb) {
    if (tb->cursor_index > 0 && tb->text.size > 0) {
        tb->text.deleteByIndex(&tb->text, tb->cursor_index - 1);
        tb->cursor_index--;
    }
}

// 편집 루프: 키 입력에 따라 편집 수행
void TextBox_editLoop(TextBox* tb) {
    printf("입력 박스에서는 ←/→/Backspace/Delete/Enter/영문자 사용 가능!\n");
    while (1) {
        tb->printBubble(tb);
        int ch = getch();
        if (ch == '\r' || ch == '\n') break;
        else if (ch == 27) { // ESC 처리 (화살표 키)
            int next1 = getch();
            if (next1 == 91) { // '['
                int arrow = getch();
                if (arrow == 'D') tb->moveLeft(tb);  // ←
                else if (arrow == 'C') tb->moveRight(tb); // →
            }
        } else if (ch == 127 || ch == 8) { // Backspace
            tb->deleteBefore(tb);
        } else if (ch == 4) { // Ctrl-D(Delete 대체)
            tb->deleteAfter(tb);
        } else if (isprint(ch)) {
            tb->insert(tb, (char)ch);
        }
    }
    printf("\n입력 완료!\n");
    tb->printBubble(tb);
    printf("\n");
}

// TextBox 초기화 및 메서드 바인딩
void TextBox_init(TextBox* tb) {
    List_init(&tb->text);
    tb->cursor_index = 0;
    tb->insert = TextBox_insert;
    tb->deleteAfter = TextBox_deleteAfter;
    tb->deleteBefore = TextBox_deleteBefore;
    tb->moveLeft = TextBox_moveLeft;
    tb->moveRight = TextBox_moveRight;
    tb->printBubble = TextBox_printBubble;
    tb->editLoop = TextBox_editLoop;
}


// 간단한 콘솔 입력 처리를 위한 (리눅스: termios, 윈도우: _getch 등 안내 주석)
#ifdef _WIN32
#include <conio.h> // Windows 전용 키 입력 함수
#else
// macOS, Linux 등 유닉스 계열에서 한 글자씩 입력받기 위한 termios 기반 getch 함수
#include <termios.h>
#include <unistd.h>
int getch(void) {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt); // 현재 터미널 속성 저장
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // 표준 입력 버퍼링·에코 끄기
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // 새로운 속성 적용
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // 원복
    return ch;
}
#endif


/*
 ┌───────────────┐    ┌──────────────┐    ┌─────────────────────┐    ┌────────┐    ┌─────────────┐    ┌─────────────┐    ┌────────┐    ┌────────┐
 │  [TextBox ]   │ →  │ [초기화]       │ → │ [키 입력에 따른 편집] │ → │ [출력] │ → │ [메모리 해제]│
 └───────────────┘    └──────────────┘    └─────────────────────┘    └────────┘    └─────────────┘
  🧱                  🛠️                  ⌨️                       🖨️           🗑️
*/

// 데모 1: 텍스트 편집기 실행
void runTextEditorDemo(void) {
    printf("\n--- 메시지 입력 박스 시작! ---\n");
    TextBox textbox;
    TextBox_init(&textbox);
    textbox.editLoop(&textbox);
    textbox.text.free(&textbox.text);
}

// 데모 2: 링크드 리스트 동작 시연
void runLinkedListDemo(void) {
    printf("\n--- 링크드 리스트 데모 ---\n");
    List list;
    List_init(&list);
    // append로 ABC 추가
    list.append(&list, 'A');
    list.append(&list, 'B');
    list.append(&list, 'C');
    printf("append A, B, C => ");
    list.print(&list);

    // 인덱스 1에 X 삽입: A X B C
    list.insert(&list, 1, 'X');
    printf("insert 'X' at index 1 => ");
    list.print(&list);

    // 인덱스 2 삭제: A X C
    list.deleteByIndex(&list, 2);
    printf("delete index 2 => ");
    list.print(&list);

    // 인덱스별 읽기
    for (int i = 0; i < list.size; ++i) {
        char ch = list.readByIndex(&list, i);
        printf("index %d: %c\n", i, ch);
    }

    list.free(&list);
}

// 전처리 매크로로 데모 선택
#ifndef LINKED_LIST_DEMO
#define TEXT_EDITOR_DEMO 1
#endif

int main(void) {
#if defined(LINKED_LIST_DEMO)
    runLinkedListDemo();
#elif defined(TEXT_EDITOR_DEMO)
    runTextEditorDemo();
#else
    // 기본값: 텍스트 편집기 데모
    runTextEditorDemo();
#endif
    return 0;
}

