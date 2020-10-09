#include <stdio.h>
#include<string.h>

/*
//정수 타입 선언
typedef  char   int8;
typedef  short  int16;
typedef  int    int32;
typedef  long   int64;
//양의 정수 타입 선언(0을 포함한)
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long uint64;
//실수 타입 선언
typedef  float   f32;
typedef  double  f64;
*/

int numberOfUser = 3;

typedef struct { 
  char name[30]; 
  char phone[30];
}ADDRESS;

int displayNumberByArray (ADDRESS info[], int numOfDis)
{
  printf("----연락처----\n");
  printf("이름  |   전화번호\n");
  for(int i=0; i<numOfDis; i++){
    printf("%s: %s\n",info[i].name, info[i].phone);
  }

}

int displayNumberByPointer (ADDRESS *info)
{
  for(int i=0; i<3; i++){
    printf("%s: %s\n",(info+i)->name, (info+i)->phone);
  }

}

int addUser(ADDRESS AddrInfo[], int i){

  int result;
  char cmd[10];

  char name[20];
  char phone[20];

  printf("이름을 입력하세요: ");
  scanf("%s", &name );

  printf("전화번호를 입력하세요: ");
  scanf("%s", &phone);


  printf("등록을 하시겠습니까? (yes/no) ");
  scanf("%s", &cmd);
  
  if(  strcmp(cmd, "yes") == 0){

    strcpy(AddrInfo[i].name, name);
    strcpy(AddrInfo[i].phone, phone);
  
    printf("등록완료되었습니다.\n");
    result = 1;
  }
  else{
    printf("취소 되었습니다. \n");
    result =0;
  }

  return result;
}



int main()
{
  int cmd;



  ADDRESS addr[100]={{"김유림", "01066431234" }, 
                     {"김유빈", "0106643568" },
                     {"김나선", "01056781234" },
                     };


  displayNumberByArray(addr,numberOfUser);

  //displayNumberByPointer(&addr);

  //printf("연락처를 등록하시겠습니까?(yes/no) \n");
  int result;

  while(1){

      
      printf("\n \n ---메뉴를 선택하세요---\n");
      printf("1: 연락처 추가 \n");
      printf("2: 검색 \n");
      printf("3: 삭제 \n");
      printf("4: 연락처 표시 \n");
      printf("0: 프로그램 종료 \n");
      scanf("%d", &cmd );

      if( cmd == 1 ){
        //등록하는 함수를 호출 한다. 
        result = addUser(addr, numberOfUser);
        if( result == 1)
        {
          numberOfUser++;
        }

      }
      else if( cmd == 2 ){
        //검색하는 함수를 호출 한다.  ** strcmp 로 순차적(선형) 검색해서 결과를 알려준다.
        
      }
      else if( cmd == 3 ){
        //삭제하는 함수를 호출 한다. 
      }

      else if (cmd == 4){
        displayNumberByArray(addr,numberOfUser);
      }
    
      else if( cmd == 0 ){
        //프로그램을 종료한다.  
        break;
        
      }
      else{     
          printf("잘못된 명령을 입력하였습니다. 다시 선택해 주세요.\n");
      }
  }

  return 0;

}










//연락처 검색 
void search(){
  int phone=0;

}