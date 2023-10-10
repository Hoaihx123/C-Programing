#include "stdio.h"
#include "stdlib.h"
#include "termios.h"
#include "fcntl.h"
#include "unistd.h"
#include "time.h"
#include "stacks.h"
#define consoleWidth 80
#define consoleHeight 25
node *last;

struct termios orig_termios;

void start_Game();

void OffCanon(){
  struct termios raw;
  tcgetattr(STDIN_FILENO, &orig_termios);
  raw = orig_termios;
  raw.c_lflag &= ~(ECHO|ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
  fcntl(0,F_SETFL,fcntl(0,F_GETFL,0)|O_NONBLOCK);
}
void OnCanon(){
  struct termios raw;
  tcgetattr(STDIN_FILENO, &orig_termios);
  raw = orig_termios;
  raw.c_lflag |= (ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void create_food(int foodXY[], node *head){
  do
  {
      srand (time(NULL) );
      foodXY[0] = rand() % (consoleWidth-4) + 3;
      srand (time(NULL) );
      foodXY[1] = rand() % (consoleHeight-5) + 4;
  } while (collisionSnake(foodXY[0], foodXY[1], head));
  gotoxy(foodXY[0] ,foodXY[1]);
  printf("$");
}
int check_gameover(node *head){
  if(last->x==1||last->x==consoleWidth||last->y==3||last->y==consoleHeight) return 1;
  while (head->next!=NULL) {
    if((head->x==last->x)&&(head->y==last->y)) return 1;
    head=head->next;
  }
  return 0;
}
void checkXY(node **head, int foodXY[], int *score, char direction){
  move(*head,direction);
  if((last->x==foodXY[0])&&(last->y==foodXY[1])){
    (*score)++;
    printf("\7");
    add_head(head);
    create_food(foodXY,*head);
    gotoxy(65,1);
    printf("Score: %d\n", *score);
  }
}
void gameOverScreen(int score){
  gotoxy(35,10);
  printf("YOUR SCORE: %d", score);
  gotoxy(15,12);
  printf("THANKS FOR PLAYING <3<3 DO YOU WANT TO RESTART GAME?");
  gotoxy(36,14);
  printf("RESTART");
  gotoxy(36,15);
  printf("EXIT NOW");
  gotoxy(34,14);
  printf(">");
  gotoxy(0,0);
  char c;
  int k =1;
  fcntl(0,F_SETFL,O_RDWR);
  while ((c=getc(stdin))!=EOF) {
    switch (c) {
             case '\n':break;
             case 'q': OnCanon();
             case 0x1b: break;
             case 0x5b: break;
             case 0x41: if(k==0){gotoxy(34,15); printf(" ");gotoxy(34,14);printf(">");k=1;};printf("\7");break;
             case 0x42: if(k==1){gotoxy(34,14); printf(" ");gotoxy(34,15);printf(">");k=0;};printf("\7");break;
             default: break;
         }
         if(c=='\n') break;
  }
  if(k==1) start_Game();
  if(k==0) {
    system("clear");
    gotoxy(0,0);
    OnCanon();
    exit(1);
  }

}
void start_Game(){
  OffCanon();
  system("clear");

  for(int i=1; i<=consoleWidth; i++){
    gotoxy(i,3);
    printf("/");
  }
  for(int i=4;i<consoleHeight; i++){
    gotoxy(1,i);
    printf("||");
    gotoxy(consoleWidth,i);
    printf("||");
  }
  for(int i=1; i<=consoleWidth; i++){
    gotoxy(i,consoleHeight);
    printf("/");
  }
  int score=0;
  char c;
  int foodXY[2];
  char direction = 0x43;
  node *head = NULL;
  if((head=(node*)malloc(sizeof(node)))==NULL){
    perror("malloc");
    exit(1);
  };
  last=head;
  head->x=20;
  head->y=14;
  add_head(&head);
  head->x=19; head->y=14;
  gotoxy(65,1);
  printf("Score: %d\n", score);
  loadSnake(head);
  create_food(foodXY,head);
  while(1){
    usleep(200000);
    while ((c=getc(stdin))!=EOF) {
        switch (c) {
            case 'q': OnCanon();
            case 0x1b: break;
            case 0x5b: break;
            case 0x41: direction==0x42?(0):(direction=0x41);break;
            case 0x42: direction==0x41?(0):(direction=0x42);break;
            case 0x43: direction==0x44?(0):(direction=0x43);break;
            case 0x44: direction==0x43?(0):(direction=0x44);break;
            default: break;
        }
    }
    checkXY(&head,foodXY, &score, direction);
    if(check_gameover(head)) break;
  }
  gameOverScreen(score);
}

int main(int argc, char const *argv[]) {


  start_Game();
  return 0;
}
