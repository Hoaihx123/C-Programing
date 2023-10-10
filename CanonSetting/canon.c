#include "stdio.h"
#include "stdlib.h"
#include "termios.h"
#include "unistd.h"
#include "time.h"

struct termios orig_termios;

void OffCannon(){
  struct termios raw;
  tcgetattr(STDIN_FILENO,&orig_termios);
  raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
void  OnCanon() {
  struct termios raw;
  tcgetattr(STDIN_FILENO, &orig_termios);
  raw = orig_termios;
  raw.c_lflag |= (ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
int main(int argc, char const *argv[]) {
  OffCannon();
  char c;
  while((c=getc(stdin))!=EOF){
    switch (c) {
      case 'Q' :OnCanon(); return 2;
      default: printf("%x\n",c ); break;
    }
  }
  return 0;
}
