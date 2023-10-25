//-------------------
// 파일 설명: 
// 만든 사람: 
// 버전: 1.0
//------------------

#include <stdio.h>

//-------------
//변수선언
int score;

//--------------


//함수 선언

char * greeting(char name[], char *message){

    char * AI_name = "steve";

    printf("message : %s, %s \n", message, name);    

    return AI_name;
}

void main(){


   // 타입 변환 연습 
   char a = -128;
   char b = 14;

   int c = (int )a * -8;

   // 크기가 큰 타입을 크기가 작은 타입에 대입 할때 실험
   unsigned char d = c;

   // 결과는 사이즈가 큰 타입의 일부만 사이즈가 작은 타입에 저장됨, 대입될 변수의 크기 만큼만, 그리고 하위 데이터 기준으로 저장 
   //됨 , 값이 왜곡됨.
    printf("c and d is : %d, %d \n", c, d);
  
  
   char *ptr;

   void *vPtr;
  
  
   ptr = &a;

   *ptr -= 7;
  
   vPtr = (char *) &b;

   *(char *)vPtr =    *(char *)vPtr +  8;
  
  
   char name[20] = "kim yung sam";
   char *ai_name;
  
  ai_name = greeting(name, "Hi I am a student.");

  printf("Hi %s\n", ai_name);
}

