#include <stdio.h>


#define BOARD_WIDTH       3
#define BOARD_HEIGHT      3



/*
    int i =3;
    while(i>=1)
    {
      /// my code 
      i--;
    }

    for(int k=1; k<=3; k++){
      // my code
    }


*/

/*
char GameBoard[BOARD_HEIGHT][BOARD_WIDTH] = {{'1', '2', '3'}, 
                                             {'4', '5', '6'},
                                             {'7', '8', '9'} };
*/
char GameBoard[BOARD_HEIGHT][BOARD_WIDTH] = {{'e', 'e', 'e'}, 
                                             {'e', 'e', 'e'},
                                             {'e', 'e', 'e'} };


int indexTable[9][2] = {
  {0,0}, 
  {0,1},
  {0,2}, 
  {1,0}, 
  {1,1},
  {1,2},
  {2,0}, 
  {2,1},
  {2,2},
};

#define PLAYER_A    1
#define PLAYER_B    2

int currentPlayer = PLAYER_A;

void displayBoard(void){

  printf("---Display Game Board--- \n");
  //printf("%c", GameBoard[1][2]);
  for(int j=0; j<3; j++){
    for(int k=0; k<3; k++){
          printf("%c ", GameBoard[j][k]);
    }
    printf("\n");
  }
}

int main(void) {

  displayBoard();

  int BoardPositionX, BoardPositionY;
  int position;
  
  

  while(1){

    printf("어디에 표시 할 것 인가요? (1~9)칸 중에서 고르시오");
    scanf("%d", &position);
    printf("position = %d \n", position);

    if((position >=1) && (position <=9 ))
    {
        BoardPositionX = indexTable[position-1][1];
        BoardPositionY = indexTable[position-1][0];

       

        printf("x = %d y = %d \n", BoardPositionX, BoardPositionY);

        if(GameBoard[BoardPositionY][BoardPositionX] == 'e')
        {
            if(currentPlayer == PLAYER_A)
            {
              
              GameBoard[BoardPositionY][BoardPositionX] = 'O';
              displayBoard();
              currentPlayer = PLAYER_B;

            }
            else 
            {
              GameBoard[BoardPositionY][BoardPositionX] = 'X';
              displayBoard();
              currentPlayer = PLAYER_A;
            }
        }else{
          printf("이곳은 이미 선택되어져있어요. ");
        }
      }
              
    }
                                               

  return 0;
}