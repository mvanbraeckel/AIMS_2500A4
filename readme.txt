# AIMS_2500A4
"Academic Information Management System" - create, manipulate, sort, and save academic courses and students (Intermediate Programming course A4)

*Do not use code from this or copy any aspects without explicit permission from creator*

Use the makefile to compile and view the executable file names to actually run the programs

NOTE: I have added some extra .bin and text files to help run the system

# aim.c
    Contains all the functions required for the system
    
# init_aim.c
    Initializes the system by creating 3 files: "students.bin", "courses.bin" and "student_course.bin"
    
# register.c
    Registers a student by prompting user to provide the information for a student:
      Records the provided information in a student_struct and then appends it to the end of the "students.bin" file.
    Reads all the entries in the "students.bin" file and finds the one with the largest "student_id".
      The new student should be assigned a student_id number that is one larger than the maximum number found previously in the file.
      If the "students.bin" file is empty, then the new student gets assigned the student_id number 1.
      
# register2.c
    Registers a student by prompting user to provide the information for a student, including an ID# as input
      Records the provided information in a student_struct and then appends it to the end of the "students.bin" file.
      
# print_students.c
    Prints out all students' information

# sort.c
    Sorts all the students in "student.bin"in order of student_id, then save the sorted contents back to the file.
    
# schedule.c
    Schedules a course offering by prompting the user for the information about a course:
      Record the information provided in a course_struct, and then append it to the end of the "courses.bin" file.
      
# add.c
    Adds a student (based on ID#) to a scheduled (existing) course by prompting the user to provide the necessary information.
      If the user enters and invalid value for Registration, it should re-prompt until a valid value is provided
        (either "CRD" or "AUD" are valid)
    Initialize the grade value to -1.
    After recording the information in a student_course_struct, append it to the end of the "student_course.bin" file.
    
# class_schedule.c
    Prints out all the courses a student is enrolled in based on a provided ID#

# class_list.c
    writes a txt file with a given filename that contains a header of the course code and title, then all the students enrolled in (part of) that course
    Takes three command line arguments: First is a course code, Second is a term, and Third is a filename.
    Goes through the "student_course.bin" file and picks out all the entries for the given course and term.
      As it adds these entries to a linked list, it retrieves the appropriate student information from the "students.bin" file by performing a binary search.
        Each item should be added to the list in alphabetical order of the student's last name.
    Once the list is created, your program should write to the text file that is given by the third argument:
      "%s %s\n" - course code and course name
    Then, for each student it should print:
      "%s, %s %s (%s)\n" - last name, first name, middle names, program

# report.c
    prints out all the courses a student is enrolled in based on a provided ID#, including their grade in that course
    Takes two command line arguments: First is a student ID number, Second is a term.
    The program should go through the "student_course.bin" file and pick out all the entries for the given student ID and term.
      As it adds these entries to a linked list, each item is added in alphabetical order of the course code.
    Once the linked list is complete, it prints the student information using the following two format strings:
      "Name: %s %s %s\n" - print the student's first, middle and last names (in that order)
      "ID: %07d\n" - print the student's student ID number
    Then the program prints out the courses in alphabetical order by course code (not name) using the following two format strings:
      "%s %s %d\n" - print the course code, the course name, and the student's grade
      "%s\n" - print the instructor
      
# grade.c
    Takes a single command line argument that is the name of a text file.
    Writes a text file will be identical to one of the files created by the "class_list" program,
      except that each student line will have an addition consisting of a space, followed by an integer in the range 0 to 100.
    The program will then go through the student_course file and update the grades.
