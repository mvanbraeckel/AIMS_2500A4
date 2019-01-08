/*
 * Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
 * 15/03/2018
 * class_list.c
    writes a txt file with a given filename that contains a header of the course code and title, then all the students enrolled in (part of) that course
 */

#include "aim.h"

int main(int argc, char **argv) {
  /* checks that the correct #of command line arguments have been entered */
  if(argc != 4) {
    fprintf(stderr, "Usage: %s <input: char[] course code> <input: char[] term> <input: char[] filename>\n", argv[0]);
    exit(-1);
  }

  class_list(argv[1], argv[2], argv[3]);

  return 0;
}
