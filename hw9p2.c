#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Author: John Cody
// Date: 04/01/2018
// Program Description: This program takes input from a file and scans it into an array of students and then sorts that array based on the 
// grade percentages held within each struct, and finally outputs that array so that it goes from highest to lowest. 

typedef struct { // Defining all of the elements of the struct
	char Student_Name[100];
	int Zyante_Assignments[12];
	int Homework_Assingnments[8];
	int In_Class_Participation;
	int Midterm1;
	int Midterm2;
	int Final_Project;
	float Grade_Prcnt;
	char Letter_Grade;
} student_info;

void Print_Student(student_info X);					// Prints out the student struct
void Scan_Student_Info(student_info *S, FILE *fp);  // Scans info from a file into a student_info struct and calculates the grade percent
void selection(student_info *x[], int size);		// Sorts an array based on the highest grade percent
void swap(student_info *x, student_info *y);		// Swaps two student_info elements

int main(void) {

	FILE *input = fopen("ClassData10.txt", "r"); // Creating a FILE pointer and setting it to the ClassData10.txt file
	student_info *list[10];  // Creating an array of student_info pointers
	int i = 0;
	
	if (input == NULL) { // Checking to make sure that the file opens properly
		printf("The file ClassData10.txt could not be opened.\n");
		return -1;
	}

	for (i = 0; i < 10; i++) { // looping through and allocating memory for each pointer and then scanning info from the file into that location
		list[i] = (student_info *)malloc(sizeof(student_info));
		Scan_Student_Info(list[i], input);
	}
	
	selection(list, 10); // using the array of student_info pointers and array size, this orders the array to go from largest to smallest
	
	for (i = 0; i < 10; i++) { // loops through and prints the now sorted array
		Print_Student(*list[i]);
	}

	free(list[0], list[1], list[2], list[3], list[4], list[5], list[6], list[7], list[8], list[9]); // frees all of the memory allocated
	fclose(input); // closes the file that was opened

	printf("Goodbye\n");

	return 0;
}

void Print_Student(student_info X) { // Prints out a student_info struct
	printf("\nGrade information for %s\n", X.Student_Name);
	printf("Zybooks Scores = [%d, %d, %d, %d, ", X.Zyante_Assignments[0], X.Zyante_Assignments[1], X.Zyante_Assignments[2], X.Zyante_Assignments[3]);
	printf("%d, %d, %d, %d, ", X.Zyante_Assignments[4], X.Zyante_Assignments[5], X.Zyante_Assignments[6], X.Zyante_Assignments[7]);
	printf("%d, %d, %d, %d]\n", X.Zyante_Assignments[8], X.Zyante_Assignments[9], X.Zyante_Assignments[10], X.Zyante_Assignments[11]);
	printf("Homework Scores = [%d, %d, %d, %d, ", X.Homework_Assingnments[0], X.Homework_Assingnments[1], X.Homework_Assingnments[2], X.Homework_Assingnments[3]);
	printf("%d, %d, %d, %d]\n", X.Homework_Assingnments[4], X.Homework_Assingnments[5], X.Homework_Assingnments[6], X.Homework_Assingnments[7]);
	printf("In-class Participation Score = %d\n", X.In_Class_Participation);
	printf("Midterm Scores = [%d, %d]\n", X.Midterm1, X.Midterm2);
	printf("Final Project Score = %d\n", X.Final_Project);
	printf("Calculated Percentage = %.2f\n", X.Grade_Prcnt);
	printf("The Final Grade for %s is %c\n\n", X.Student_Name, X.Letter_Grade);
}

void Scan_Student_Info(student_info *S, FILE *fp) { // Scans info from a file and then calculates the grade percent and letter grade
	fscanf(fp, " %s", S->Student_Name);
	fscanf(fp, " %d %d %d %d", &S->Zyante_Assignments[0], &S->Zyante_Assignments[1], &S->Zyante_Assignments[2], &S->Zyante_Assignments[3]);
	fscanf(fp, " %d %d %d %d", &S->Zyante_Assignments[4], &S->Zyante_Assignments[5], &S->Zyante_Assignments[6], &S->Zyante_Assignments[7]);
	fscanf(fp, " %d %d %d %d", &S->Zyante_Assignments[8], &S->Zyante_Assignments[9], &S->Zyante_Assignments[10], &S->Zyante_Assignments[11]);
	fscanf(fp, " %d %d %d %d", &S->Homework_Assingnments[0], &S->Homework_Assingnments[1], &S->Homework_Assingnments[2], &S->Homework_Assingnments[3]);
	fscanf(fp, " %d %d %d %d", &S->Homework_Assingnments[4], &S->Homework_Assingnments[5], &S->Homework_Assingnments[6], &S->Homework_Assingnments[7]);
	fscanf(fp, " %d %d %d %d", &S->In_Class_Participation, &S->Midterm1, &S->Midterm2, &S->Final_Project);

	S->Grade_Prcnt = .1*((S->Zyante_Assignments[0] + S->Zyante_Assignments[1] + S->Zyante_Assignments[2] + S->Zyante_Assignments[3] + S->Zyante_Assignments[4] + S->Zyante_Assignments[5] + S->Zyante_Assignments[6] + S->Zyante_Assignments[7] + S->Zyante_Assignments[8] + S->Zyante_Assignments[9] + S->Zyante_Assignments[10] + S->Zyante_Assignments[11]) / 1.2);
	S->Grade_Prcnt += 0.3*((S->Homework_Assingnments[0] + S->Homework_Assingnments[1] + S->Homework_Assingnments[2] + S->Homework_Assingnments[3] + S->Homework_Assingnments[4] + S->Homework_Assingnments[5] + S->Homework_Assingnments[6] + S->Homework_Assingnments[7]) / 8.0);
	S->Grade_Prcnt += 0.05*S->In_Class_Participation + 0.15*S->Midterm1 + 0.15*S->Midterm2 + 0.25*S->Final_Project;

	if (S->Grade_Prcnt > 90) {
		S->Letter_Grade = 'A';
	}
	else if (S->Grade_Prcnt > 80) {
		S->Letter_Grade = 'B';
	}
	else if (S->Grade_Prcnt > 70) {
		S->Letter_Grade = 'C';
	}
	else if (S->Grade_Prcnt > 60) {
		S->Letter_Grade = 'D';
	}
	else {
		S->Letter_Grade = 'E';
	}
}


void selection(student_info *x[], int size) { // selection sort
	int i, j;
	int max;
	for (i = 0; i < size; i++) {
		max = i; // start searching from currently unsorted
		for (j = i; j < size; j++) {
			if (x[j]->Grade_Prcnt > x[max]->Grade_Prcnt) // if found a bigger element
				max = j; // move it to the front
		}
		swap(x[i], x[max]);
	}
}

void swap(student_info *x, student_info *y) {
	student_info temp = *x;
	*x = *y;
	*y = temp;
}