// #include "unistd.h"
#include "fcntl.h"
#include "error.h"
#include "stdio.h"
#include "stdlib.h"

#define IFLAGS O_RDONLY
#define OFLAGS O_WRONLY|O_CREAT
#define BUFFER_SIZE 4096

int main(){
  int fdr, fdw;
  ssize_t rd, wr;
  char buffer[BUFFER_SIZE];
  if((fdr=open("in.txt",IFLAGS))<0){perror("open in:"); exit(1);}
  if((fdw=open("out",OFLAGS,0600))<0){perror("open out:"); exit(1);}
  printf("%d\n%d\n", fdr,fdw);
  while((rd=read(0,buffer,5))>0){
    printf("%s ", buffer);
    // printf("%d",rd);
    wr=write(fdw,buffer,rd);
    if(wr!=rd){fprintf(stderr, "Write error\n" );exit(1);}
    /*hàm open trả về số nguyên là bản ghi, -1 nếu lỗi, bản ghi 1-hiện lên màn hình
    tham số đầu là địa chỉ file, 2 là flags,
    hàm read trả về kích thước của chuổi, tham số đầu là vị trí đọc, thứ 2 là đọc vào đâu, thứ 3 là kích thướcs
    hàm write tương tự
    */

  }
  if(rd<0){perror("read:"),exit(1);}
  close(fdr);
  close(fdw);
  return 0;

}
