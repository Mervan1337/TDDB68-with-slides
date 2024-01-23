#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
	char *name;
	struct list_elem elem;
};


void insert (struct list *student_list) {
	char *name = (char*) malloc(sizeof(char) * 30);
	printf("Enter name of student: ");
	scanf("%29s", name);

	struct student * student = (struct student*) malloc(sizeof(struct student));
	student->name = name;
	list_push_back(student_list, &student->elem);
}

void delete (struct list *student_list) {
	printf("Which student do you want to delete?: ");
	char name[30];
	scanf("%29s", name);
	for(struct list_elem *e = list_begin(student_list); e != list_end(student_list); e = list_next(e)) {
		struct student *student = list_entry(e, struct student, elem);
		if (!strcmp(student->name, name)) {
			list_remove(e);
			free(student->name);
			free(student);
			return;
		}
	}
}

void list (struct list *student_list) {
	for(struct list_elem *e = list_begin(student_list); e != list_end(student_list); e = list_next(e)) {
		struct student *student = list_entry(e, struct student, elem);
		printf("%s\n",student->name);
	}
}

void quit (struct list *student_list) {
	while(!list_empty(student_list)) {
		struct list_elem *e = list_pop_front(student_list);
		struct student *student = list_entry(e, struct student, elem);
		free(student->name);
		free(student);
	}
	exit(0);
}

int main() {
	struct list student_list;
	list_init (&student_list);
	int opt;

	do {
		printf("Menu:\n");
		printf("1 - Insert student\n");
		printf("2 - Delete student\n");
		printf("3 - List students\n");
		printf("4 - Exit\n");
		scanf("%d", &opt);
		switch (opt) {
			case 1:
				{
					insert(&student_list);
					break;
				}
			case 2:
				{
					delete(&student_list);
					break;
				}
			case 3:
				{
					list(&student_list);
					break;
				}

			case 4:
				{
					quit(&student_list);
					break;
				}
			default:
				{
					printf("Quit? (1/0):\n");
					scanf("%d", &opt);
					if (opt)
						quit(&student_list);
					break;
				}
		}
	} while(1);
		
	return 0;
}
