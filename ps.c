#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

//todo: add the option count in a header thing so that its easier to manage :)
// basically the ps command in linux - but not as good :)
int main(int argc, char *argv[])
{
  int options[6];

  //clear the array
  for(int i = 0; i < 6; i++)
  {
    options[i] = 0;
  }

  

  // todo: make cleaner code for this section

  if(argc > 1)
  {
    for (int i = 0; i < argc; i++)
    {
      printf(1, "argument: %s\n", argv[i]);
      // look for -s
      if( 0 == strcmp(argv[i], "-s"))
        options[0] = 1;
      
      // look for -r
      if( 0 == strcmp(argv[i], "-r"))
        options[1] = 1;
      
      // look for -run
      if( 0 == strcmp(argv[i], "-run"))
        options[2] = 1;
      
      // look for -a
      if( 0 == strcmp(argv[i], "-a"))
        options[3] = 1;
      
      // look for -h
      if( 0 == strcmp(argv[i],"-h"))
      {
        options[4] = 1;
      }
      
      // look for --help
      if( 0 == strcmp(argv[i], "--help"))
        options[5] = 1;
      
    }
    
  }
  else // default
  {
    options[3] = 1;  
  }
  
  // make sure that if all is checked clear out the first 3
  if(options[3] == 1)
  {
    options[0] = 0;
    options[1] = 0;
    options[2] = 0;
  }

  // cps(argint(0, &options[0]), argint(1, &options[1]), argint(2, &options[2]), argint(3, &options[3]), argint(4, &options[4]), argint(5, &options[5]));

  int options_singleline = options[0] + 10 * options[1] + 100 * options[2] + 1000 * options[3] + 10000 * options[4] + 100000 * options[5];

  printf(1, "inside ps this is the inted option: %d\n", options_singleline);

  cps(options_singleline);

  exit();
}