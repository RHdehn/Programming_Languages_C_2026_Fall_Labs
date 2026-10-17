// week5_task4_struct_binary_io.c   (BONUS)
// Name: Fabian Malte  Surname: Dehnbostel  Student ID: 260AIM015
//
// Task 4: Save and load a struct in binary format with fwrite()/fread()
// Week 5 – Files & Modular Programming
//
// Build: make lab5   Run: ./bin/week5_task4_struct_binary_io

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct Student {
    char name[MAX_NAME_LEN];
    int age;
    float gpa;
} Student;

// Function prototypes (do not change these signatures – the autograder calls them directly)
int  save_student_binary(const Student *s, const char *filename);  // 0 on success, -1 on error
int  load_student_binary(const char *filename, Student *out);      // 0 on success, -1 on error
long file_size(const char *filename);                              // bytes, -1 on error

int main(void) {
    Student s1 = {0};          // zero-initialised so unused name bytes are not garbage on disk
    strcpy(s1.name, "Alice");
    s1.age = 21;
    s1.gpa = 3.75f;

    Student loaded = {0};
    const char *bin_file = "student.bin";
    const char *txt_file = "student.txt";

    printf("Saving student in binary format...\n");
    // TODO: save_student_binary(&s1, bin_file); handle failure

    if(save_student_binary(&s1, bin_file) != 0) {
        fprintf(stderr, "Error saving binary file.\n");
        return EXIT_FAILURE;
    }

    // TODO: Save the same record as text ("name age gpa") to txt_file for comparison
     FILE *txt = fopen(txt_file, "w");
    if(txt == NULL){
        fprintf(stderr, "Error opening text file.\n");
        return EXIT_FAILURE;
    }
    if(fprintf(txt, "%s %d %.2f\n", s1.name, s1.age, s1.gpa) < 0){
        fprintf(stderr, "Error writing text file.\n");
        fclose(txt);
        return EXIT_FAILURE;
    }
    if (fclose(txt) != 0){
        fprintf(stderr, "Error closing text file.\n");
        return EXIT_FAILURE;
    }

    printf("Loading student from binary file...\n");
    // TODO: load_student_binary(bin_file, &loaded); handle failure
    if(load_student_binary(bin_file, &loaded) != 0){
        fprintf(stderr, "Error loading binary file.\n");
        return EXIT_FAILURE;
    }

    // TODO: printf("Loaded student: %s, %d, GPA %.2f\n", ...);
    printf("Loaded student: %s, %d, GPA %.2f\n",
           loaded.name, loaded.age, loaded.gpa);
    // TODO: printf("Text file size: %ld bytes\n", file_size(txt_file));
    long text_size = file_size(txt_file);
    if(text_size < 0){
        fprintf(stderr, "Error getting text file size.\n");
        return EXIT_FAILURE;
    }
    printf("Text file size: %ld bytes\n", text_size);
    // TODO: printf("Binary file size: %ld bytes\n", file_size(bin_file));

    long binary_size = file_size(bin_file);
    if(binary_size < 0){
        fprintf(stderr, "Error getting binary file size.\n");
        return EXIT_FAILURE;
    }
    printf("Binary file size: %ld bytes\n", binary_size);

    
    return EXIT_SUCCESS;
}

 

// TODO: open with "wb", fwrite(s, sizeof(Student), 1, fp) must return 1, close, return 0/-1
int save_student_binary(const Student *s, const char *filename) {
    FILE *fp = fopen(filename, "wb");

    if (fp == NULL) {
        return -1;
    }

    int result = fwrite(s, sizeof(Student), 1, fp) == 1 ? 0 : -1;

    if (fclose(fp) != 0) {
        result = -1;
    }

    return result;
}
    

// TODO: open with "rb", fread(out, sizeof(Student), 1, fp) must return 1, close, return 0/-1
int load_student_binary(const char *filename, Student *out) {
    FILE *fp = fopen(filename, "rb");

    if (fp == NULL) {
        return -1;
    }

    int result = fread(out, sizeof(Student), 1, fp) == 1 ? 0 : -1;

    if (fclose(fp) != 0) {
        result = -1;
    }

    return result;
}

// TODO: open with "rb", fseek(fp, 0, SEEK_END), size = ftell(fp), close, return size (-1 on error)
long file_size(const char *filename) {
    FILE *fp = fopen(filename, "rb");

    if (fp == NULL) {
        return -1;
    }

    if (fseek(fp, 0, SEEK_END) != 0) {
        fclose(fp);
        return -1;
    }

    long size = ftell(fp);

    if (size < 0) {
        fclose(fp);
        return -1;
    }

    if (fclose(fp) != 0) {
        return -1;
    }

    return size;
}

