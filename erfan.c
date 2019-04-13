#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

int main(int argc, char *argv[])
{
  printf(1,"hello world its erfan\nexit with ctrl a then x after release\n");
  // now lets add the first program mentioned in the book
  int pid = fork();
  if(pid > 0){
    printf(1,"parent: child=%d\n", pid);
    pid = wait();
    printf(1,"child with number %d is done\n");
  }
  else if (pid == 0)
  {
    printf(1,"hello this is a child\n");
    exit();
  }
  else
  {
    printf(1,"error in fork\n");
    exit();
  }
  exit();
}