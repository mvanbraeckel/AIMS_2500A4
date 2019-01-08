/*
 * Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
 * 15/03/2018
 * grade.c
    Writes a text file for a course with each of the student's grades
 */

#include "aim.h"

int main(int argc, char **argv) {
  /* checks that the correct #of command line arguments have been entered */
  if(argc != 2) {
    fprintf(stderr, "Usage: %s <input: char[] filename>\n", argv[0]);
    exit(-1);
  }

  grade(argv[1]);

  return 0;
}
