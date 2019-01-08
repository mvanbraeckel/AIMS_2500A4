all: aim init_aim register register2 sort schedule add class_schedule class_list report grade print_students

aim: aim.c aim.h
	gcc -g -Wall -ansi -pedantic -include aim.h -c aim.c -o aim.o

init_aim: init_aim.c aim.c aim.h
	gcc -g -Wall -ansi -pedantic -include aim.h -c init_aim.c -o init_aim.o
	gcc -g -Wall -ansi -pedantic -include aim.h aim.o init_aim.o -o init_aim

register: register.c aim.c aim.h
	gcc -g -Wall -ansi -pedantic -include aim.h -c register.c -o register.o
	gcc -g -Wall -ansi -pedantic -include aim.h aim.o register.o -o register

register2: register2.c aim.c aim.h
	gcc -g -Wall -ansi -pedantic -include aim.h -c register2.c -o register2.o
	gcc -g -Wall -ansi -pedantic -include aim.h aim.o register2.o -o register2

sort: sort.c aim.c aim.h
	gcc -g -Wall -ansi -pedantic -include aim.h -c sort.c -o sort.o
	gcc -g -Wall -ansi -pedantic -include aim.h aim.o sort.o -o sort

schedule: schedule.c aim.c aim.h
	gcc -g -Wall -ansi -pedantic -include aim.h -c schedule.c -o schedule.o
	gcc -g -Wall -ansi -pedantic -include aim.h aim.o schedule.o -o schedule

add: add.c aim.c aim.h
	gcc -g -Wall -ansi -pedantic -include aim.h -c add.c -o add.o
	gcc -g -Wall -ansi -pedantic -include aim.h aim.o add.o -o add

class_schedule: class_schedule.c aim.c aim.h
	gcc -g -Wall -ansi -pedantic -include aim.h -c class_schedule.c -o class_schedule.o
	gcc -g -Wall -ansi -pedantic -include aim.h aim.o class_schedule.o -o class_schedule

class_list: class_list.c aim.c aim.h
	gcc -g -Wall -ansi -pedantic -include aim.h -c class_list.c -o class_list.o
	gcc -g -Wall -ansi -pedantic -include aim.h aim.o class_list.o -o class_list

report: report.c aim.c aim.h
	gcc -g -Wall -ansi -pedantic -include aim.h -c report.c -o report.o
	gcc -g -Wall -ansi -pedantic -include aim.h aim.o report.o -o report

grade: grade.c aim.c aim.h
	gcc -g -Wall -ansi -pedantic -include aim.h -c grade.c -o grade.o
	gcc -g -Wall -ansi -pedantic -include aim.h aim.o grade.o -o grade

print_students: print_students.c aim.c aim.h
	gcc -g -Wall -ansi -pedantic -include aim.h -c print_students.c -o print_students.o
	gcc -g -Wall -ansi -pedantic -include aim.h aim.o print_students.o -o print_students

clean:
	rm -f *.o aim init_aim register register2 sort schedule add class_schedule class_list report grade print_students all

delete:
	rm -i *.bin
