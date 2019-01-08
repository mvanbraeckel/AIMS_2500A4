/*
 * Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
 * 15/03/2018
 * aim.h
    Header file for aim.c
 */

#ifndef AIM_H
#define AIM_H

/* =========================== INCLUDED LIBRARIES =========================== */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* =========================== STRUCT DECLARATIONS ========================== */
struct student_struct {
     char last_name[64];
     char first_name[64];
     char middle_names[64];
     int id;
     char major[64];
};
struct course_struct {
     char code[10];
     char term[6];
     char title[128];
     char instructor[64];
};
struct student_course_struct {
     int student_id;
     char course_code[10];
     char term[6];
     char registration[4];
     int grade;
};

typedef struct linked_list_struct {
    struct student_course_struct student_course;
    struct linked_list_struct *next;
} List;

/* =========================== FUNCTION PROTOTYPES ========================== */
void init_aim();
void register_student();
void register_student2();
void print_students();
void sort();
int compar_id( const void *a, const void *b );
void schedule();
void add();

struct student_struct *get_student_info(int id);
void get_student_course_info(int id, char term[]);
List *new_item( struct student_course_struct *student_course );
void push( List **list_ptr, List *item_ptr );
void print_list(List *linked_list);
struct course_struct* get_course_info(char course_code[]);

void class_list(char course_code[], char term[], char filename[]);
void write_text(List *linked_list, char filename[], struct course_struct *course);
void push3( List **list_ptr, List *to_add, char last_name[] );

void grade(char filename[]);
void report(int id, char term[]);
void get_student_course_info2(int id, char term[]);
void print_list2(List *linked_list);

void flush_input(char *input);

#endif
