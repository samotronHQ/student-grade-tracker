#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void saveToFile();
void loadFromFile();


#define MAX_STUDENTS 100

struct Student{
char name[50];
int roll;
float marks[3];
};

struct Student students[MAX_STUDENTS];
int count=0;

void addStudent(){
    if(count>=MAX_STUDENTS){ 
        printf("Maximum Limit reached\n");
    }
    printf("Enter name: ");
    scanf(" %[^\n]",students[count].name);

    printf("Enter roll number:\n");
    scanf("%d",&students[count].roll);

    for(int i=0;i<3;i++)
    {
        printf("Enter marks for subject %d: \n",i+1);
        scanf("%f",&students[count].marks[i]);
    }
    count ++;
    printf("Student added!");
    saveToFile();
   
}

void displayStudents()
{
    for(int i=0;i<count;i++)
    {
        printf("Data for Student %d\n",i+1);
        printf("Name of student: %s\n",students[i].name);
        printf("Roll number of Student : %d",students[i].roll);
        printf("Marks scored in subject 1 : %.2f\n",students[i].marks[0]);
        printf("Marks scored in subject 2 : %.2f\n",students[i].marks[1]);
        printf("Marks scored in subject 3 : %.2f\n",students[i].marks[2]);

    }
}

void averageMarks()
{
    for(int i=0;i<count;i++)
    {
        float sum=0;
        for(int j=0;j<3;j++){
            sum+=students[i].marks[j];
        }
        printf("Student %s : Average : %.2f\n",students[i].name, sum/3);
    }
}


void searchStudent()
{
    int roll;
    printf("Enter roll number of student you want to search:\n");
    scanf("%d",&roll);
    for(int i=0;i<count;i++)
    {
        if(roll==students[i].roll)
        {
            printf("Student found!\n");
            printf("Details:\n");
            printf("\nName of student: %s\n", students[i].name);
            printf("Roll number of student: %d\n",students[i].roll);
            printf("Marks in subject 1: %.2f\n",students[i].marks[0]);
            printf("Marks in subject 2: %.2f\n",students[i].marks[1]);
            printf("Marks in subject 3: %.2f\n",students[i].marks[2]);
            return;
                }
               
    }
    printf("Student not found!");
}

void deleteStudent()
{
    int n;
    printf("Enter roll number of student you want to delete");
    scanf("%d",&n);
    for(int i=0;i<count;i++)
    {
        if(n==students[i].roll)
        {
            for (int j = i; j < count - 1; j++) {
                students[j] = students[j + 1];
        }printf("Student has been deleted!");
        count--;
        saveToFile();
        return;
    }
}
printf("Student not found!");
}


void saveToFile() {
    FILE *f = fopen("students.txt", "w");

    if (f == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(f, "%s %d %.2f %.2f %.2f\n",
                students[i].name,
                students[i].roll,
                students[i].marks[0],
                students[i].marks[1],
                students[i].marks[2]);
    }

    fclose(f);
}

void loadFromFile() {
    FILE *f = fopen("students.txt", "r");

    if (f == NULL) {
        // File doesn't exist yet
        return;
    }

    while (fscanf(f, "%s %d %f %f %f",
                  students[count].name,
                  &students[count].roll,
                  &students[count].marks[0],
                  &students[count].marks[1],
                  &students[count].marks[2]) == 5) {
        count++;
    }

    fclose(f);
}
char getGrade(float avg) {
    if (avg >= 90) return 'A';
    else if (avg >= 75) return 'B';
    else if (avg >= 60) return 'C';
    else if (avg >= 50) return 'D';
    else return 'F';
}


void generatereport(){
    printf("Enter roll number");
    int rn;
    scanf("%d",&rn);
    for(int i=0;i<count;i++)
    {
        if(rn==students[i].roll){
            float avg= ((students[i].marks[0]+students[i].marks[1]+students[i].marks[2])/3);
            char grade=getGrade(avg);

            char filename[50];
            sprintf(filename,"Report_%d.txt",rn);
            FILE *f = fopen(filename, "w");
            if (f == NULL) {
                printf("Error creating report card file.\n");
                return;
            }
            fprintf(f, "-------- Report Card --------\n");
            fprintf(f, "Name       : %s\n", students[i].name);
            fprintf(f, "Roll Number: %d\n", students[i].roll);
            fprintf(f, "Marks      : %.2f, %.2f, %.2f\n",
                    students[i].marks[0],
                    students[i].marks[1],
                    students[i].marks[2]);
                    fprintf(f, "Average    : %.2f\n", avg);
            fprintf(f, "Grade      : %c\n", grade);
            fprintf(f, "------------------------------\n");
            fclose(f);
            printf("Report card generated: %s\n", filename);
            return;
        }
    }
    printf("Student with roll number %d not found.\n", rn);
}

int main(){
    loadFromFile();
    int ch;
    while(1){
        printf("\n1. Add Student\n2. Display Students\n3. Average Marks\n4. Search Student\n5.Delete Student\n6. Get grade\n7. Generate report card\n8. Exit\nChoice: ");
        scanf("%d", &ch);

        switch(ch) {
        case 1:
        addStudent();
        break;

        case 2:
        displayStudents();
        break;

        case 3:
        averageMarks();
        break;

        case 4:
        searchStudent();
        break;

        case 5:
        deleteStudent();
        break;
        
        case 6:
        printf("Enter average marks: ");
        float n;
        scanf("%f",&n);
        char gr;
        gr=getGrade(n);
        printf("Grade obtained: %c",gr);
        break;

        case 7:
        generatereport();
        break;

        case 8:
        return 0;


        default:
        printf("Invalid choice");
    }
}
}

