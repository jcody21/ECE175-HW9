#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Author: John Cody
// Date: 04/01/2018
// Program Description: This program takes the number of students in a class, and then takes all the input for each of the students, 
// and finally prompts to see which students the user wants to see the grade on. 

typedef struct { // defining the struct
	char Student_Name[100];
	int Zyante_Assignments[3];
	int Homework_Assingnments[5];
	int In_Class_Participation;
	int Midterm1;
	int Midterm2;
	int Final_Project;
	float Grade_Prcnt;
	char Letter_Grade;
} student_info;

void Print_Student(student_info X); // prints out a student_info struct
void Scan_Student_Info(student_info *S); // prompts the user for info and then scans it into the student_info struct

int main(void) {

	int i = 0, numStudents, display;
	student_info *students; // initializing some variables
	char again = 'y';

	printf("Enter the number of students in the class : "); // Prompting the user for how many students there are
	scanf(" %d", &numStudents); // scanning input into the variable to create the array of appropriate size

	students = (student_info *)malloc(numStudents * sizeof(student_info)); // creating an array using the pointer & dynamic allocation

	for (i = 0; i < numStudents; i++) { // looping through the array
		printf("\nEnter in the name of student number %d: ", i+1); // prompting for the name of the student 
		scanf(" %s", ((students[i]).Student_Name)); // scanning the given name into the struct variable
		Scan_Student_Info(&students[i]); // calling the scan function to get the rest of the info from the user to put in the struct
	}

	while (again == 'y') { // looping the output portion until the user doesn't want to output anymore
		printf("\nWhich student's info would you like to display? (1-%d) ", numStudents); // prompting the user to pick something to output
		scanf(" %d", &display); // taking the users response to determine what to output

		while ((display > numStudents)||(display < 1)) { // This is in case the user is a pos and decides to enter something outside the range
			printf("That input was out of the range. Please try again. \n"); // Warning the user and requesting a new attempt
			printf("\nWhich student's info would you like to display? (1-%d) ", numStudents);  // Prompting the user for some fresh input
			scanf(" %d", &display);   // Scanning for that sweet sweet input
		}

		Print_Student(students[display - 1]); // outputting the information that the user wanted

		printf("\nWould you like to print out the information of another student (y/n)? "); // Prompting the user to see if they want more
		scanf(" %c", &again);  // Scanning for the users input
		
		while ((again != 'y') && (again != 'n')) { // This is in case the user is a pos and decides to not enter one of the provided options
			printf("That input was not one of the options. Please try again. \n");
			printf("\nWould you like to print out the information of another student (y/n)? ");  // Prompting the user for some fresh input
			scanf(" %c", &again);   // Scanning for that sweet sweet input
		}
	}

	free(students); // Freeing up the dynamically allocated data that was accessed through students
	printf("\nGoodbye\n");

	return 0; // fin
}

void Print_Student(student_info X) { // prints out a student_info struct - everything is just print statements and formatting
	printf("\nGrade information for %s\n", X.Student_Name);
	printf("Zybooks Scores = [%d, %d, %d]\n", X.Zyante_Assignments[0], X.Zyante_Assignments[1], X.Zyante_Assignments[2]);
	printf("Homework Scores = [%d, %d, %d, %d, %d]\n", X.Homework_Assingnments[0], X.Homework_Assingnments[1], X.Homework_Assingnments[2], X.Homework_Assingnments[3], X.Homework_Assingnments[4]);
	printf("In-class Participation Score = %d\n", X.In_Class_Participation);
	printf("Midterm Scores = [%d, %d]\n", X.Midterm1, X.Midterm2);
	printf("Final Project Score = %d\n", X.Final_Project);
	printf("Calculated Percentage = %.2f\n", X.Grade_Prcnt);
	printf("The Final Grade for %s is %c\n\n", X.Student_Name, X.Letter_Grade);
}
void Scan_Student_Info(student_info *S) { // prompts the user for a specific piece of input and then scans that input into the proper location
	printf("Enter 3 Zybooks scores(out of 10) : ");
	scanf(" %d %d %d", &S->Zyante_Assignments[0], &S->Zyante_Assignments[1], &S->Zyante_Assignments[2]);

	printf("Enter 5 homework scores(out of 100) : ");
	scanf(" %d %d %d %d %d", &S->Homework_Assingnments[0], &S->Homework_Assingnments[1], &S->Homework_Assingnments[2], &S->Homework_Assingnments[3], &S->Homework_Assingnments[4]);

	printf("Enter the in-class participation score(out of 100) : ");
	scanf(" %d", &S->In_Class_Participation);

	printf("Enter midterm 1 (out of 100) : ");
	scanf(" %d", &S->Midterm1);

	printf("Enter midterm 2 (out of 100) : ");
	scanf(" %d", &S->Midterm2);

	printf("Enter final project(out of 100) : ");
	scanf(" %d", &S->Final_Project);

	S->Grade_Prcnt = .1*((S->Zyante_Assignments[0] + S->Zyante_Assignments[1] + S->Zyante_Assignments[2])/0.3) + 0.3*((S->Homework_Assingnments[0] + S->Homework_Assingnments[1] + S->Homework_Assingnments[2] + S->Homework_Assingnments[3] + S->Homework_Assingnments[4])/5.0) + 0.05*S->In_Class_Participation + 0.15*S->Midterm1 + 0.15*S->Midterm2 + 0.25*S->Final_Project; 
	if (S->Grade_Prcnt > 90) { // Using all the info gathered, it then calculates the grade percent and letter grade accordingly
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
