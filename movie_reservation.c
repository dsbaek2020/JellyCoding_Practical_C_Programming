#include <stdio.h>
#include <string.h>

typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;


typedef union{
  char seatXY[4][4];//16BYTE
  char seat[16];    //16BYTE
}SEAT;

typedef struct{
  char UserID[20];  //20BYTE
  SEAT seat;        //16BYTE
}SEAT_AND_ID;

typedef struct {
  char movieTitle[20];//20BYTE
  char ActorName[20]; //20BYTE
  SEAT_AND_ID seat;   //36BYTE

}MOVIE_INFO;  //76BYTE



void movieDataLoad(MOVIE_INFO *ptr, char *Title, char *Actor)
{
  strcpy(ptr->movieTitle, Title);
  strcpy(ptr->ActorName, Actor);
}

void resetSeats(MOVIE_INFO *ptr){
  int i;

  for(i=0; i<16; i++){
    ptr->seat.seat.seat[i]='O';
  }
}

void diplayTitle(MOVIE_INFO *ptr, int number){
  printf("%d:  %s \n", number, ptr->movieTitle);
}

int diplayMainPanel(MOVIE_INFO *ptr)
{
  int select;

  printf("영화 예약 프로그램\n");
  diplayTitle(ptr, 1);
  diplayTitle(ptr+1, 2);
  diplayTitle(ptr+2, 3);

  printf("영화를 선택해 주세요.  0번을 누르시면 종료합니다.");
  scanf("%d", &select);  //blocking 함수 
  return select-1;
}

int movieReservation(MOVIE_INFO *ptr){
   int selectSeat;
   int returnValue;

   printf("제목:");  printf("%s \n",  ptr->movieTitle);
   printf("배우:");  printf("%s \n",  ptr->ActorName);

  //-----------좌석상태 표시----


  //----------------------------
  int reservation =0;
  do{

    printf("좌석을 선택해 주세요(1~16번). 0번을 누르시면 취소 입니다. \n");
    scanf("%d", &selectSeat);  //blocking 함수 
    if(selectSeat == 0){
      printf("취소 되었습니다. 메인 매뉴로 돌아갑니다.\n");
      returnValue = -1;
      break;
    }

    //----------------------------
    if( ptr->seat.seat.seat[selectSeat-1] == 'O')
    {
      ptr->seat.seat.seat[selectSeat-1] = 'V';
      printf("%d번으로 예약되었습니다. \n", selectSeat);
      reservation =1;
      returnValue = selectSeat;
    }
    else{
      printf("%d번 좌석은 이미 예약된 자리입니다. 다른자리를 선택해주세요.\n", selectSeat);
    }
  }while(reservation != 1);

  

  //-----------좌석상태 표시----


  //----------------------------

  return returnValue;


}

#define LOGIN           0
#define MAIN            1
#define RESERVATION     2
#define EXIT            3

char ProgramStatus = MAIN;

int main(void) {
  int selectedMovie;

  // 영화정보가 모두 포함된 구조체 변수 선언
  MOVIE_INFO movies[3];  //76BYTE * 3
  movieDataLoad(&movies[0], "타이타닉", "디카프리오");
  movieDataLoad(&movies[1], "태양의 눈물", "브루스윌리스");
  movieDataLoad(&movies[2], "마션", "맷데이먼");

  resetSeats(&movies[0]);
  resetSeats(&movies[1]);
  resetSeats(&movies[2]);

  do
  {
     if(ProgramStatus == MAIN){
        selectedMovie = diplayMainPanel(&movies[0]);

        if(selectedMovie > 0)
        {
          ProgramStatus = RESERVATION;
        }
        else{
          ProgramStatus = EXIT;
        }
     }else if(ProgramStatus == RESERVATION){

        if(movieReservation(&movies[selectedMovie]) == -1)
        {
          ProgramStatus = MAIN;
        }

     }

  }while( ProgramStatus != EXIT);

  printf("감사합니다");

  return 0;
}
