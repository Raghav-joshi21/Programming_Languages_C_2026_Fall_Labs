// week5_task3_student_management_system.c
// Name: Raghav  Surname: Joshi  Student ID: 251ADB004
//
// Task 3: Mini-project – Student management system with file persistence
// Week 5 – Files & Modular Programming
// TODO: Implement the functions to load, save, add, and list students.
//
// Build: make lab5   Run: ./bin/week5_task3_student_management_system

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define LINE_LEN 256
#define DATA_FILE "students.txt"

typedef struct Student {
  char name[NAME_LEN];
  int id;
  float gpa;
} Student;

/* Required function prototypes */
int load_students(Student arr[], int max);
int save_students(const Student arr[], int count);
void add_student(Student arr[], int* count);
void list_students(const Student arr[], int count);
int read_line(const char* prompt, char* buf, size_t size);

int main(void) {
  Student students[MAX_STUDENTS];
  int count = 0;
  char input[LINE_LEN];
  int running = 1;

  count = load_students(students, MAX_STUDENTS);
  printf("Loaded %d student(s) from %s\n", count, DATA_FILE);

  while (running) {
    printf("\n=== Student Management System ===\n");
    printf("1. List students\n");
    printf("2. Add student\n");
    printf("3. Save and Exit\n");

    int choice;

    if (read_line("Select an option: ", input, sizeof input) != 0) {
      choice = 3;
    } else {
      char* end;
      long value = strtol(input, &end, 10);

      while (isspace((unsigned char)*end)) {
        end++;
      }

      if (end == input || *end != '\0' || value < INT_MIN || value > INT_MAX) {
        choice = 0;
      } else {
        choice = (int)value;
      }
    }

    switch (choice) {
      case 1:
        list_students(students, count);
        break;

      case 2:
        add_student(students, &count);
        break;

      case 3:
        if (save_students(students, count) != 0) {
          fprintf(stderr, "Error saving students to %s.\n", DATA_FILE);
          return EXIT_FAILURE;
        }

        printf("Data saved. Goodbye!\n");
        running = 0;
        break;

      default:
        printf("Invalid option. Try again.\n");
    }
  }

  return EXIT_SUCCESS;
}

/* Read a line and remove its trailing newline. */
int read_line(const char* prompt, char* buf, size_t size) {
  if (size == 0 || size > INT_MAX) {
    return -1;
  }

  printf("%s", prompt);
  fflush(stdout);

  if (fgets(buf, (int)size, stdin) == NULL) {
    return -1;
  }

  size_t len = strcspn(buf, "\r\n");

  if (buf[len] == '\0' && len == size - 1) {
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
    }
  }

  buf[len] = '\0';
  return 0;
}

/* Load student records from students.txt. */
int load_students(Student arr[], int max) {
  FILE* fp = fopen(DATA_FILE, "r");

  if (fp == NULL || max <= 0) {
    if (fp != NULL) {
      fclose(fp);
    }
    return 0;
  }

  char line[LINE_LEN];
  int count = 0;

  while (count < max && fgets(line, sizeof line, fp) != NULL) {
    Student student = {0};
    char extra;

    int fields = sscanf(line, "%49[^,],%d,%f %c", student.name, &student.id,
                        &student.gpa, &extra);

    if (fields == 3 && student.name[0] != '\0' && student.id >= 0 &&
        student.gpa >= 0.0f && student.gpa <= 4.0f) {
      arr[count] = student;
      count++;
    }
  }

  fclose(fp);
  return count;
}

/* Save all student records to students.txt. */
int save_students(const Student arr[], int count) {
  FILE* fp = fopen(DATA_FILE, "w");

  if (fp == NULL) {
    return -1;
  }

  for (int i = 0; i < count; i++) {
    if (fprintf(fp, "%s,%d,%.2f\n", arr[i].name, arr[i].id, arr[i].gpa) < 0) {
      fclose(fp);
      return -1;
    }
  }

  if (fclose(fp) == EOF) {
    return -1;
  }

  return 0;
}

/* Add a student after validating the input. */
void add_student(Student arr[], int* count) {
  if (*count >= MAX_STUDENTS) {
    printf("Cannot add more students (limit reached).\n");
    return;
  }

  Student student = {0};
  char input[LINE_LEN];
  char* end;

  if (read_line("Enter name: ", student.name, sizeof student.name) != 0) {
    return;
  }

  if (student.name[0] == '\0' || strchr(student.name, ',') != NULL) {
    printf("Invalid input. Student not added.\n");
    return;
  }

  if (read_line("Enter ID: ", input, sizeof input) != 0) {
    return;
  }

  errno = 0;
  long id = strtol(input, &end, 10);

  while (isspace((unsigned char)*end)) {
    end++;
  }

  if (input[0] == '\0' || end == input || *end != '\0' || errno == ERANGE ||
      id < 0 || id > INT_MAX) {
    printf("Invalid input. Student not added.\n");
    return;
  }

  student.id = (int)id;

  if (read_line("Enter GPA: ", input, sizeof input) != 0) {
    return;
  }

  errno = 0;
  float gpa = strtof(input, &end);

  while (isspace((unsigned char)*end)) {
    end++;
  }

  if (input[0] == '\0' || end == input || *end != '\0' || errno == ERANGE ||
      gpa < 0.0f || gpa > 4.0f) {
    printf("Invalid input. Student not added.\n");
    return;
  }

  student.gpa = gpa;
  arr[*count] = student;
  (*count)++;

  printf("Student added successfully!\n");
}

/* Display all students. */
void list_students(const Student arr[], int count) {
  if (count == 0) {
    printf("No students found.\n");
    return;
  }

  printf("%-5s %-20s %s\n", "ID", "Name", "GPA");

  for (int i = 0; i < count; i++) {
    printf("%-5d %-20s %.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
  }
}