#include <stdio.h>
#include "SimpleCPXParser.c"

int main(int argc, char **argv){
  parse_GPX(argv[1]);
  return 0;
}
