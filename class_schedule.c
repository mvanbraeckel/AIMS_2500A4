/*
 * Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
 * 15/03/2018
 * class_schedule.c
    prints out all the courses a given ID# student is enrolled in (added to)
 */

#include "aim.h"

int main(int argc, char **argv) {
  struct student_struct *student;
  /* checks that the correct #of command line arguments have been entered */
  if(argc != 3) {
    fprintf(stderr, "Usage: %s <input: int ID#> <input: char[] term>\n", argv[0]);
    exit(-1);
  }

  student = get_student_info(atoi(argv[1]));
  if(student != NULL) {
    printf("Name: %s %s %s\n" \
            "ID: %07d\n", student->first_name, student->middle_names, student->last_name, student->id);

    get_student_course_info(atoi(argv[1]), argv[2]);

  } else {
    printf("ID# %d not found\n", atoi(argv[1]));
  }

  /*free(student)?*/

  return 0;
}
