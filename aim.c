/*
 * Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
 * 15/03/2018
 * aim.c
    Contains all the functions required for the assignment
 */

#include "aim.h"

/* Initialize the academic information management system by creating 3 files "students.bin", "courses.bin" and "student_course.bin".
   Each file should be of size zero bytes (you can do this by issuing fopen and fclose functions). */
void init_aim() {
  FILE *fp;

  fp = fopen("students.bin", "wb");
  if(fp == NULL) {
      fprintf(stderr, "ERROR: File could not be opened\n"); /* checks if fopen messed up */
  }
  fclose(fp);

  fp = fopen("courses.bin", "wb");
  if(fp == NULL) {
      fprintf(stderr, "ERROR: File could not be opened\n"); /* checks if fopen messed up */
  }
  fclose(fp);

  fp = fopen("student_course.bin", "wb");
  if(fp == NULL) {
      fprintf(stderr, "ERROR: File could not be opened\n"); /* checks if fopen messed up */
  }
  fclose(fp);
}

/* Registers a student by prompting user to provide the information for a student:
   Records the provided information in a student_struct and then appends it to the end of the "students.bin" file.
   Reads all the entries in the "students.bin" file and finds the one with the largest "student_id".
   The new student should be assigned a student_id number that is one larger than the maximum number found previously in the file.
      If the "students.bin" file is empty, then the new student gets assigned the student_id number 1. */
void register_student() {
  FILE *fp;
  struct student_struct *student = malloc(sizeof(struct student_struct));
  int max_ID = 0; /* init to 0 as default, for later step where student gets +1 as their ID */

  fp = fopen("students.bin", "rb+");
  if(fp == NULL) {
      fprintf(stderr, "ERROR: File could not be opened\n"); /* checks if fopen messed up */

  } else {
    /* read until the end of the file -- if something is read, will return non-zero */
    while(fread(student, sizeof(struct student_struct), 1, fp)) {
        /* check highscore */
        if(student->id > max_ID) {
          max_ID = student->id;
        }
    } /* note that file ptr will be at the very end of the file */

    /* prompt user and collect input */
    printf("Last name: ");
    fgets(student->last_name, 64, stdin);
    flush_input(student->last_name);
    printf("First name: ");
    fgets(student->first_name, 64, stdin);
    flush_input(student->first_name);
    printf("Middle names: ");
    fgets(student->middle_names, 64, stdin);
    flush_input(student->middle_names);
    printf("Major: ");
    fgets(student->major, 64, stdin);
    flush_input(student->major);

    student->id++; /* was prev at the max, so now it's one higher */

    fwrite(student, sizeof(struct student_struct), 1, fp); /* writes the new registered student to the file */
  }
  fclose(fp);
  free(student);
}

/* Same as register_student(), except also intakes ID# as input */
void register_student2() {
  char id[64];
  FILE *fp;
  struct student_struct *student = malloc(sizeof(struct student_struct));

  fp = fopen("students.bin", "ab");
  if(fp == NULL) {
      fprintf(stderr, "ERROR: File could not be opened\n"); /* checks if fopen messed up */

  } else {
    /* prompt user and collect input */
    printf("Last name: ");
    fgets(student->last_name, 64, stdin);
    flush_input(student->last_name);
    printf("First name: ");
    fgets(student->first_name, 64, stdin);
    flush_input(student->first_name);
    printf("Middle names: ");
    fgets(student->middle_names, 64, stdin);
    flush_input(student->middle_names);
    printf("Major: ");
    fgets(student->major, 64, stdin);
    flush_input(student->major);

    printf("ID: ");
    fgets(id, 64, stdin);
    flush_input(id);
    student->id = atoi(id);

    fwrite(student, sizeof(struct student_struct), 1, fp); /* writes the new registered student to the file */
  }
  fclose(fp);
  free(student);
}

/* Print out all students' information */
void print_students() {
  FILE *fp;
  struct student_struct *student = malloc(sizeof(struct student_struct));

  fp = fopen("students.bin", "rb");
  if(fp == NULL) {
      fprintf(stderr, "ERROR: File could not be opened\n"); /* checks if fopen messed up */

  } else {
    /* read until the end of the file -- if something is read, will return non-zero */
    while(fread(student, sizeof(struct student_struct), 1, fp)) {
      /* print the student's info */
      printf("Last name: %s\n" \
              "First name: %s\n" \
              "Middle names: %s\n" \
              "Major: %s\n" \
              "ID: %d\n", student->last_name, student->first_name, student->middle_names, student->major, student->id);
    }
  }
  fclose(fp);
  free(student);
}

/* Sorts the contents of the "students.bin" file by allocating memory to store
   the entire contents of the file in an array of student_struct, and then sort that array in order of student_id.
    Finally, (over-)write the contents of the file out to the "students.bin" file. */
void sort() {
  FILE *fp;
  int num_students = 0;
  struct student_struct *student_array;

  fp = fopen("students.bin", "rb+");
  if(fp == NULL) {
      fprintf(stderr, "ERROR: File could not be opened\n"); /* checks if fopen messed up */

  } else {
    fseek(fp, 0, SEEK_END); /* moves to end of file */
    num_students = ftell(fp) / sizeof(struct student_struct); /* calculates number of students using total bytes divided by #in a student_struct */

    student_array = calloc(num_students, sizeof(struct student_struct)); /* init the array */
    fseek(fp, 0, SEEK_SET); /* move it back to the beginning */
    fread(student_array, sizeof(struct student_struct), num_students, fp); /* reads entire file into the array at once */

    qsort(student_array, num_students, sizeof(struct student_struct), compar_id);

    fseek(fp, 0, SEEK_SET); /* go back to beginning again */
    fwrite(student_array, sizeof(struct student_struct), num_students, fp); /* over-write the file with the sorted array version */
  }
  fclose(fp);
  free(student_array);
}
/* for qsort-ing the students based on ID# */
int compar_id( const void *a, const void *b ) {
    const struct student_struct *struct_a, *struct_b;
    struct_a = a;
    struct_b = b;
    return ((struct_a->id)-(struct_b->id));
}

/* Schedules a course offering by prompting the user for the information for a course:
   Record the information provided in a course_struct, and then append it to the end of the "courses.bin" file. */
void schedule() {
  FILE *fp;
  struct course_struct *course = malloc(sizeof(struct course_struct));

  fp = fopen("courses.bin", "ab");
  if(fp == NULL) {
      fprintf(stderr, "ERROR: File could not be opened\n"); /* checks if fopen messed up */

  } else {
    /* prompt user and collect input */
    printf("Code: ");
    fgets(course->code, 10, stdin);
    flush_input(course->code);
    printf("Term: ");
    fgets(course->term, 6, stdin);
    flush_input(course->term);
    printf("Title: ");
    fgets(course->title, 128, stdin);
    flush_input(course->title);
    printf("Instructor: ");
    fgets(course->instructor, 64, stdin);
    flush_input(course->instructor);

    fwrite(course, sizeof(struct course_struct), 1, fp); /* writes the new registered course to the file */
  }
  fclose(fp);
  free(course);
}

/* Adds a student to a course by prompting the user to provide the necessary information.
   If the user enters and invalid value for Registration, it should re-prompt until a valid value is provided. (either "CRD" or "AUD")
   Initialize the grade value to -1.
   After recording the information in a student_course_struct, append it to the end of the "student_course.bin" file. */
void add() {
  char id[64];
  FILE *fp;
  int valid = 0; /* init false */
  struct student_course_struct *student_course = malloc(sizeof(struct student_course_struct));
  student_course->grade = -1; /* init grade value to -1 */

  fp = fopen("student_course.bin", "ab");
  if(fp == NULL) {
      fprintf(stderr, "ERROR: File could not be opened\n"); /* checks if fopen messed up */

  } else {
    /* prompt user and collect input */
    printf("Student ID: ");
    fgets(id, 64, stdin);
    flush_input(id);
    student_course->student_id = atoi(id);

    printf("Course Code: ");
    fgets(student_course->course_code, 10, stdin);
    flush_input(student_course->course_code);
    printf("Term: ");
    fgets(student_course->term, 6, stdin);
    flush_input(student_course->term);

    /* only valid if input was "CRD" or "AUD" */
    while(valid == 0) {
      printf("Registration [CRD or AUD]: ");
      fgets(student_course->registration, 5, stdin);
      flush_input(student_course->registration);
      if(strcmp(student_course->registration, "CRD") == 0 || strcmp(student_course->registration, "AUD") == 0) {
        valid = 1;
      }
    }
    fwrite(student_course, sizeof(struct student_course_struct), 1, fp); /* writes the new registered student_course to the file */
  }
  fclose(fp);
  free(student_course);
}

/* gets the desired student's info (based in ID#) from students.bin */
struct student_struct* get_student_info(int id) {
  FILE *fp;
  int mid, left, right;
  struct student_struct *student = malloc(sizeof(struct student_struct));

  fp = fopen("students.bin", "rb");
  if(fp == NULL) {
      fprintf(stderr, "ERROR: File could not be opened\n"); /* checks if fopen messed up */
  } else {
    /* init variables */
    mid = 0;
    left = 0;
    fseek(fp, 0, SEEK_END);
    right = ftell(fp) / sizeof(struct student_struct); /* gets #of students in file */

    /* binary search for matching ID# */
    while(left <= right) {
      /* gets student in the middle */
      mid = (left + right) / 2;
      fseek(fp, mid * sizeof(struct student_struct), SEEK_SET);
      fread(student, sizeof(struct student_struct), 1, fp);

      if(id == student->id) {       /* it's a match */
        fclose(fp);
        return student;
      } else if(id < student->id) { /* search the left half */
        right = mid-1;
      } else {                      /* search the right hald */
        left = mid+1;
      }
    } /* end while loop */
  }
  fclose(fp);
  free(student);
  return NULL;
}

/* gets info about a student_course */
void get_student_course_info(int id, char term[]) {
  FILE *fp;
  List *linked_list = NULL;
  struct student_course_struct *student_course = malloc(sizeof(struct student_course_struct));

  fp = fopen("student_course.bin", "rb");
  if(fp == NULL) {
      fprintf(stderr, "ERROR: File could not be opened\n"); /* checks if fopen messed up */

  } else {
    /* read until the end of the file -- if something is read, will return non-zero */
    while(fread(student_course, sizeof(struct student_course_struct), 1, fp)) {
      if(student_course->student_id == id && strcmp(student_course->term, term) == 0) {
        push(&linked_list, new_item(student_course));
      }
    } /* end while loop */
    print_list(linked_list);
  }
  fclose(fp);
  free(student_course);
}

/* Return a pointer to a newly allocated linked list item by setting the student_course attribute and pointing next to NULL. */
List *new_item( struct student_course_struct *student_course ) {
  List *new = malloc( sizeof(List) );
  memcpy(&(new->student_course), student_course, sizeof(struct student_course_struct));
  /*new->student_course->student_id = student_course->student_id;
  strcpy(new->student_course->course_code, student_course->course_code);
  strcpy(new->student_course->term, student_course->term);
  strcpy(new->student_course->registration, student_course->registration);
  new->student_course->grade = student_course->grade;*/

  new->next = NULL;
  return new;
}

/* Add an item to the linked list.
   Advances the list_ptr pointer to the right position to insert the new course in alphabetical order by course code */
void push( List **list_ptr, List *to_add ) {
  List *prev, *curr;
  curr = *list_ptr;
  prev = NULL;

  /* loop through linked list, as long as the current course_code is alphabetically before the one desired to add */
  while(curr != NULL && strcmp(curr->student_course.course_code, to_add->student_course.course_code) < 0) {
    prev = curr;
    curr = curr->next;
  }

  if(prev == NULL) {          /* start case */
    to_add->next = *list_ptr;
    *list_ptr = to_add;
  } else {                    /* middle and end case */
    to_add->next = prev->next;
    prev->next = to_add;
  }
}

/* prints the entire linked list */
void print_list(List *linked_list) {
  struct course_struct *course;
  while(linked_list) {
    course = get_course_info(linked_list->student_course.course_code);
    printf("%s %s\n" \
            "%s\n", course->code, course->title, course->instructor);
    linked_list = linked_list->next;
  }
}

/* gets info about a course */
struct course_struct* get_course_info(char course_code[]) {
  FILE *fp;
  struct course_struct *course = malloc(sizeof(struct course_struct));

  fp = fopen("courses.bin", "rb");
  if(fp == NULL) {
      fprintf(stderr, "ERROR: File could not be opened\n"); /* checks if fopen messed up */

  } else {
    /* read until the end of the file -- if something is read, will return non-zero */
    while(fread(course, sizeof(struct course_struct), 1, fp)) {
      if(strcmp(course_code, course->code) == 0) {
        fclose(fp);
        return course;
      }
    }
  }
  fclose(fp);
  free(course);
  return NULL;
}

/* Takes three command line arguments: First is a course code, Second is a term, and Third is a filename.
   Goes through the "student_course.bin" file and picks out all the entries for the given course and term.
   It should add these entries to a linked list.
   As it does so, it should retrieve the appropriate student information from the "students.bin" file by performing a binary search.
   Each item should be added to the list in alphabetical order of the student's last name.
   Once the list is created, your program should write to the text file that is given by the third argument:
      "%s %s\n" - course code and course name
   Then, for each student it should print:
      "%s, %s %s (%s)\n" - last name, first name, middle names, program */
void class_list(char course_code[], char term[], char filename[]) {
  FILE *fp;
  List *linked_list;
  struct course_struct *course;
  struct student_struct *student;
  struct student_course_struct *student_course = malloc(sizeof(struct student_course_struct));

  linked_list = NULL;
  student = NULL;
  course = get_course_info(course_code);

  fp = fopen("student_course.bin", "rb");
  if(fp == NULL) {
      fprintf(stderr, "ERROR: File could not be opened\n"); /* checks if fopen messed up */

  } else {
    /* read until the end of the file -- if something is read, will return non-zero */
    while(fread(student_course, sizeof(struct student_course_struct), 1, fp)) {
      if(strcmp(student_course->course_code, course_code) == 0 && strcmp(student_course->term, term) == 0) {
        student = get_student_info(student_course->student_id);
        push3(&linked_list, new_item(student_course), student->last_name);
      }
    }
    write_text(linked_list, filename, course);
  }
  fclose(fp);
  /*free(student);? --*/
  free(student_course);
}

/* Add an item to the linked list.
   Advances the list_ptr pointer to the right position to insert the new course in alphabetical order by last_name */
void push3(List **list_ptr, List *to_add, char last_name[]) {
  List *prev, *curr;
  struct student_struct *student_curr;

  curr = *list_ptr;
  prev = NULL;

  /* loop through the linked list */
  while(curr != NULL) {
    student_curr = get_student_info(curr->student_course.student_id);

    /* stop once the desire last_name is alphabetically before or equal to the current one */
    if( strcmp(last_name, student_curr->last_name) <= 0) {
      break;
    }
    prev = curr;
    curr = curr->next;
  }

  if(prev == NULL) {          /* start case */
    to_add->next = *list_ptr;
    *list_ptr = to_add;
  } else {                    /* middle and end case */
    to_add->next = prev->next;
    prev->next = to_add;
  }
}

/* writes the linked list to the file */
void write_text(List *linked_list, char filename[], struct course_struct *course) {
  FILE *fp;
  struct student_struct *student;

  fp = fopen(filename, "w");
  if(fp == NULL) {
      fprintf(stderr, "ERROR: File could not be opened\n");

  } else {
    fprintf(fp, "%s %s\n", course->code, course->title);

    while(linked_list) {
      student = get_student_info(linked_list->student_course.student_id);
      fprintf(fp, "%s, %s %s (%s)\n", student->last_name, student->first_name, student->middle_names, student->major);
      linked_list = linked_list->next;
    }
  }
  /*free(student);?*/
  fclose(fp);
}

/* Takes a single command line argument that is the name of a text file.
   The text file will be identical to one of the files created by the previous program ("class_list") except that each student line will have an addition consisting of a space,
      followed by an integer in the range 0 to 100.
   The program will then go through the student_course file and update the grades. */
void grade(char filename[]) {
  FILE *fout, *fin;
  struct student_struct *student;
  struct student_course_struct *student_course = malloc(sizeof(struct student_struct));

  char buffer[300] = "";
  char string[300] = "";
  int i = 0;
  int grade = 0;
  int place_holder = 0;

  fout = fopen("student_course.bin", "rb+");
  if(fout == NULL) {
      fprintf(stderr, "ERROR: File could not be opened\n");

  } else {
    while(fread(student_course, sizeof(struct student_course_struct), 1, fout)) {
      student = get_student_info(student_course->student_id);
      sprintf(string, "%s, %s %s (%s)", student->last_name, student->first_name, student->middle_names, student->major);

      fin = fopen(filename, "r");
      if(fin == NULL) {
          fprintf(stderr, "ERROR: File could not be opened\n");
      } else {

        fgets(buffer, 300, fin); /* gets the header of course_code and title */

        if(strncmp(buffer, student_course->course_code, strlen(student_course->course_code)) == 0) {
          while(fgets(buffer, 300, fin)) {
            if(strncmp(buffer, string, strlen(string)) == 0) {
              /* reset variables */
              place_holder = 100;
              grade = 0;
              /* get the last 3 chars (the grade) from the file */
              for(i = strlen(buffer)-4; i < strlen(buffer)-1; i++) {
                if(isdigit(buffer[i])) {
                  grade += (buffer[i] - '0') * place_holder;
                }
                place_holder /= 10; /* update column of number */
              }
              /* set the grade, then move back 1 in the file, then fwrite */
              student_course->grade = grade;
              fseek(fout, -(sizeof(struct student_course_struct)), SEEK_CUR);
              fwrite(student_course, sizeof(struct student_course_struct), 1, fout);
            }
          }
        }

      }
      fclose(fin);
    }
  }
  fclose(fout);
}

/* Takes two command line arguments: First is a student ID number, Second is a term.
   The program should go through the "student_course.bin" file and pick out all the entries for the given student ID and term.
   It should add these entries to a linked list. Each item should be added in alphabetical order of the course code.
   Once the linked list is complete your program should print the student information using the following two format strings:
      "Name: %s %s %s\n" - print the student's first, middle and last names (in that order)
      "ID: %07d\n" - print the student's student ID number
   Then the program should print out the courses in alphabetical order by course code (not name) using the following two format strings:
      "%s %s %d\n" - print the course code, the course name, and the student's grade
      "%s\n" - print the instructor */
void report(int id, char term[]) {
  struct student_struct *student = get_student_info(id);

  if(student != NULL) {
    printf("Name: %s %s %s\n" \
            "ID: %07d\n", student->first_name, student->middle_names, student->last_name, student->id);

    get_student_course_info2(id, term);

  } else {
    printf("ID# %d not found\n", id);
  }
}

/* gets info about a student_course */
void get_student_course_info2(int id, char term[]) {
  FILE *fp;
  List *linked_list;
  struct student_course_struct *student_course = malloc(sizeof(struct student_course_struct));

  linked_list = NULL;

  fp = fopen("student_course.bin", "rb");
  if(fp == NULL) {
      fprintf(stderr, "ERROR: File could not be opened\n"); /* checks if fopen messed up */

  } else {
    /* read until the end of the file -- if something is read, will return non-zero */
    while(fread(student_course, sizeof(struct student_course_struct), 1, fp)) {
      if(student_course->student_id == id && strcmp(student_course->term, term) == 0) {
        push(&linked_list, new_item(student_course));
      }
    }
    print_list2(linked_list);
  }
  fclose(fp);
  free(student_course);
}

/* prints the entire linked list */
void print_list2(List *linked_list) {
  struct course_struct *course;
  while(linked_list) {
    course = get_course_info(linked_list->student_course.course_code);
    if(course != NULL) {
      printf("%s %s %d\n" \
              "%s\n", course->code, course->title, linked_list->student_course.grade, course->instructor);
    }
    linked_list = linked_list->next;
  }
}

/* ============================== MY FUNCTIONS ============================== */

/* flushes all leftover data in the stream -- return 0 if stream was flushed
   @param char *input - the string that was just read from stdin */
void flush_input(char *input) {
  /* if the '\n' is NOT found in the word itself, flush the stream */
  if(strchr(input, '\n') == NULL) {
    while ((getchar()) != '\n');
    input[strlen(input)] = '\0';
  } else {
    input[strlen(input)-1] = '\0';
  }
}
