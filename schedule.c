/*
 * Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
 * 15/03/2018
 * schedule.c
    creates a course and writes it to courses.bin

       Takes two command line arguments: first is a student ID number, second is a term.
       Binary search on the "students.bin" file to look up the student's information.
       Then, goes through the "student_course.bin" file and picks out all the entries for the given student ID and term.
       It should add these entries to a linked list. (Each item should be added in alphabetical order of the course code)
       Once the linked list is complete, prints the student information using the following two format strings:
          "Name: %s %s %s\n" - print the student's first, middle and last names (in that order)
          "ID: %07d\n" - print the student's student ID number
       Then, prints out the courses in alphabetical order by course code (not name) using the following two format strings:
          "%s %s\n" - print the course code and the course name
          "%s\n" - print the instructor
 */

#include "aim.h"

int main() {
  schedule();

  return 0;
}
