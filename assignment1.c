//Showad Huda COP3502C-0V05 Spring 2021 Assignment 1

//Directives
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Requirements for the assignment
typedef struct student{
	int id;
	char *lname; //stores last name of student
	float *scores; //stores scores of the student. Size is taken from num_scores array.
	float std_avg; //average score of the student (to be calculated)
}student;

typedef struct course{
	char *course_name; //stores course name
	int num_sections; //number of sections
	student **sections;//stores array of student arrays(2D array). Size is num_sections;
	int *num_students;//stores array of number of students in each section. Size is num_sections;
	int *num_scores; //stores array of number of assignments in each section. Size is num_sections;
} course;

//Given file pointers
student **read_sections(FILE *fp, int num_students[], int num_scores[], int num_sections);

course *read_courses(FILE *fp, int *num_courses);

void display_sections(student **sections, int num_students[], int num_scores[], int num_sections);

void process_courses(course *courses, int num_courses);

void release_sections(student **sections, int num_sections, int *num_students, int *num_scores);

void release_courses(course *courses, int num_courses);

int main(void){
	//File reading
	FILE *fp = fopen("assignment1input.txt", "r");
	int num_test;
	course *courses;
	fscanf(fp, "%d", &num_test);
	
	for(int i = 0; i < num_test; i++){
		int num_courses;
		printf("test case %d\n", i + 1);

		//read, process, and release functions
		courses = read_courses(fp, &num_courses);
		process_courses(courses, num_courses);
		release_courses(courses, num_courses);
		printf("\n"); //new line
	}
	//close File
	fclose(fp);
	return 0;
}

//Read courses
course *read_courses(FILE *fp, int *num_courses){
	fscanf(fp, "%d", num_courses);

	//allocate memory
	course *courses = (course*)malloc(sizeof(course)* *num_courses);
	char cname[50];
	
	//for course c
	for(int c = 0; c < *num_courses; c++){
		fscanf(fp, "%s", cname);
		int len = strlen(cname);
		
		//allocate memory
		courses[c].course_name = malloc(len + 1);
		strcpy(courses[c].course_name, cname);
		
		fscanf(fp, "%d", &courses[c].num_sections);
		courses[c].num_students = (int*)malloc(sizeof(int) * courses[c].num_sections);
		courses[c].num_scores = (int*)malloc(sizeof(int) * courses[c].num_sections);
		courses[c].sections = read_sections(fp, courses[c].num_students, courses[c].num_scores, courses[c].num_sections);
	}

	return courses; //return of courses array

}

//Read sections
student **read_sections(FILE *fp, int num_students[], int num_scores[], int num_sections){
	student **sections = (student**)malloc(sizeof(student*) * num_sections);
	char lname[50];
	
	//for section s
	for(int s = 0; s < num_sections; s++){
		fscanf(fp, "%d %d", &num_students[s], &num_scores[s]);
		sections[s] = (student*)malloc(sizeof(student) * num_students[s]);
		
		//for students st in section s
		for(int st = 0; st < num_students[s]; st++){
			fscanf(fp, "%d %s", &sections[s][st].id, lname);
			//memory allocation
			sections[s][st].lname = malloc(strlen(lname) + 1);
			strcpy(sections[s][st].lname, lname);
			sections[s][st].scores = (float*)malloc(sizeof(float) * num_scores[s]);
			float sum = 0;
			
			//for scores sc 
			for(int sc = 0; sc < num_scores[s]; sc++){
				fscanf(fp, "%f", &sections[s][st].scores[sc]);
				sum +=  sections[s][st].scores[sc];
			}
			
			//average section to student scores equation
			sections[s][st].std_avg = sum/num_scores[s];
		}
	}
	
	return sections;
}

//Process functions
void process_courses(course *courses, int num_courses){
	//for course c
	for(int c = 0; c < num_courses; c++){
		printf("%s ", courses[c].course_name);
		display_sections(courses[c].sections, courses[c].num_students, courses[c].num_scores, courses[c].num_sections);
	}
}

//Display functions
void display_sections(student **sections, int num_students[], int num_scores[], int num_sections){
	//average equation for sections
	float *sec_avg = (float*)malloc(num_sections * sizeof(float));
	
	//max parameters for student section and average
	int max_st = 0;
	int max_sec = 0;
	int pass_count = 0;
	float max_avg = -1;
	
	//for section
	for(int s = 0; s < num_sections; s++){
		float sum_sec = 0;
		
		//for st in s
		for(int st = 0; st < num_students[s]; st++){
			if(sections[s][st].std_avg >= 70){ //parameter set for pass or fail
				pass_count++;
			}
			sum_sec += sections[s][st].std_avg;
			
			if(sections[s][st].std_avg > max_avg){
				max_avg = sections[s][st].std_avg;
				max_st = st;
				max_sec = s;
			}
		}
		
		sec_avg[s] = sum_sec/num_students[s];
	}
	
	printf("%d", pass_count);
	
	for(int i = 0; i < num_sections; i++){
		printf("%.2f ", sec_avg[i]);
		  printf("%d %s %.2f\n",
			sections[max_sec][max_st].id,
			sections[max_sec][max_st].lname,
			sections[max_sec][max_st].std_avg
			);
	
	}
	free(sec_avg);
}

//Free memory functions
void release_courses( course *courses, int num_courses){
	for(int c = 0; c < num_courses; c++){
		free(courses[c].course_name);
		release_sections(courses[c].sections, courses[c].num_sections, courses[c].num_students, courses[c].num_scores);
		free(courses[c].num_students);
		free(courses[c].num_scores);
	}
	free(courses);
}

//Free from allocated memory
void release_sections(student **sections, int num_sections, int *num_students, int *num_scores){
	for(int s = 0; s < num_sections; s++){
		for(int st = 0; st < num_students[s]; st++){
			free(sections[s][st].lname);
			free(sections[s][st].scores);
		}
		free(sections[s]);
	}
	free(sections);
}
			