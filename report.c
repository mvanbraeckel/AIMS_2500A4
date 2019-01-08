/*
 * Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
 * 15/03/2018
 * report.c
    prints out all the courses a given ID# student is enrolled in (added to)
      also prints out the grade in that course
 */

#include "aim.h"

int main(int argc, char **argv) {
  /* checks that the correct #of command line arguments have been entered */
  if(argc != 3) {
    fprintf(stderr, "Usage: %s <input: int ID#> <input: char[] term>\n", argv[0]);
    exit(-1);
  }

  report(atoi(argv[1]), argv[2]);

  return 0;
}
