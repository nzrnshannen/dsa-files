#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define MAX 50

typedef enum {M=1, F} Sex;

typedef enum{
    BSCS = 1,
    BSIT, 
    BSIS
} Course;

typedef struct{
    char FN[20], LN[20], MI;
}nameType;

typedef struct{
    char ID[10];
    nameType Name;
    Sex S;
    Course course;
    float gpa;
}studType, *Studlist;

typedef struct node{
    Studlist Stud;
    int noOfStudents;
    struct node *LC;
    struct node *RC;
}Cell, *CLASS;


void initClassList(CLASS *Class);
void populateClass(CLASS *Class, studType listOfStudents[], int noOfStudents);
bool isStudent(CLASS *Class, char ID[]);

void addStudent(CLASS *Class, Studlist Stud);

void removeStudent(CLASS *Class, char ID[]);
Studlist deleteFirstStud(CLASS *Class); //for removeStudent; acting as deleteMin
Studlist deleteLastStud(CLASS *Class); //for removeStudent; acting as deleteMax

void displayStudentRecord(Studlist studType); //prints student record of one student
void displayStudents(CLASS Class);
void StudentLevelOrder(CLASS Class);
void preorder(CLASS Class);
void postorder(CLASS Class);
void inorder(CLASS Class);

char* studentCourse(Course course);
char* studentSex(Sex s);

//filter functions ==> get____()
void groupBySex(CLASS Class, CLASS* maleStuds, CLASS *femaleStuds);
CLASS groupByCourse(CLASS Class, CLASS *grp, Course course);

char* studentCourse(Course course)
{
    char* returnStr;

    switch(course)
    {
        case BSCS: returnStr = "BSCS"; break;
        case BSIT: returnStr = "BSIT"; break;
        case BSIS: returnStr = "BSIS"; break; 
    }

    return returnStr;
}

char* studentSex(Sex s)
{
    char* returnStr;

    switch(s)
    {
        case M: returnStr = "Male"; break;
        case F: returnStr = "Female"; break;
    }

    return returnStr;
}

void initClassList(CLASS *Class)
{
    *Class = NULL;
}

bool isStudent(CLASS *Class, char ID[])
{
    CLASS *trav;
    for(trav=Class; *trav!=NULL && (strcmp((*trav)->Stud->ID, ID))!=0; )
    {
        trav =((strcmp(ID, (*trav)->Stud->ID))<0) ? &(*trav)->LC : &(*trav)->RC;
    }

    return (*trav!=NULL) ? true : false;
}

void addStudent(CLASS *Class, Studlist Stud)
{
    CLASS *trav;
    for(trav=Class; *trav!=NULL && (strcmp(Stud->ID, (*Class)->Stud->ID))!=0; )
    {
        trav = ((strcmp(Stud->ID, (*trav)->Stud->ID))<0) ? &(*trav)->LC : &(*trav)->RC;
    }

    if(*trav==NULL)
    {
        *trav = (CLASS)calloc(1, sizeof(Cell));
        (*trav)->Stud = Stud;
    }
}

void removeStudent(CLASS *Class, char ID[])
{
    CLASS *trav;
    for(trav = Class; *trav!=NULL && (strcmp(ID, (*Class)->Stud->ID))!=0; )
    {
        trav = ((strcmp(ID, (*trav)->Stud->ID))<0)? &(*trav)->LC : &(*trav)->RC;
    }

    if(*trav!=NULL)
    {
        CLASS temp;
        temp = *trav;

        if(temp->LC==NULL || temp->RC==NULL)
        {
            *trav = (temp->LC!=NULL) ? temp->LC : temp->RC;
            free(temp);
        }
        else
        {
            //using the successor
            temp->Stud = deleteFirstStud(&temp->RC);
        }
    }
}

Studlist deleteFirstStud(CLASS *Class)
{
    CLASS *trav, temp;
    Studlist returnedStudRec;

    for(trav=Class; *trav!=NULL && (*trav)->LC!=NULL; trav=&(*trav)->LC){}

    if(*trav!=NULL)
    {
        temp = *trav;
        returnedStudRec = temp->Stud;
        *trav = temp->RC;
        free(temp);
    }

    return returnedStudRec;
}

Studlist deleteLastStud(CLASS *Class)
{
    CLASS *trav, temp;
    Studlist returnedStudRec;

    for(trav=Class; *trav!=NULL && (*trav)->RC!=NULL; trav=&(*trav)->RC){}

    if(*trav!=NULL)
    {
        temp = *trav;
        returnedStudRec = temp->Stud;
        *trav = temp->LC;
        free(temp);
    }

    return returnedStudRec;
}

void displayStudentRecord(Studlist studType)
{
    printf("%-15s %-15s %-15s %-15c %-15s %-15s %.2f\n", studType->ID, studType->Name.FN, studType->Name.LN, studType->Name.MI, studentSex(studType->S), studentCourse(studType->course), studType->gpa);
}

void StudentLevelOrder(CLASS Class)
{
    CLASS tempQueue[MAX], currentStud;
    int front=1, rear=0;

    if(Class!=NULL)
    {
        for(tempQueue[++rear] = Class; front!=(rear+1)%MAX; )
        {
            currentStud = tempQueue[front];
            front = (front+1)%MAX;

            if(currentStud!=NULL)
            {
                displayStudentRecord(currentStud->Stud);

                rear = (rear+1)%MAX;
                tempQueue[rear] = currentStud->LC;
                rear = (rear+1)%MAX;
                tempQueue[rear] = currentStud->RC;
            }
        }
    }
}

void populateClass(CLASS *Class, studType listOfStudents[], int noOfStudents)
{
    int x;

    for(x=0; x<noOfStudents; x++)
    {
        addStudent(Class, &listOfStudents[x]);
    }

    (*Class)->noOfStudents = noOfStudents;
}

void preorder(CLASS Class)
{
    if(Class!=NULL)
    {
        displayStudentRecord(Class->Stud);
        preorder(Class->LC);
        preorder(Class->RC);
    }
}

void postorder(CLASS Class)
{
    if(Class!=NULL)
    {
        postorder(Class->LC);
        postorder(Class->RC);
        displayStudentRecord(Class->Stud);
    }
}

void inorder(CLASS Class)
{
    if(Class!=NULL)
    {
        inorder(Class->LC);
        displayStudentRecord(Class->Stud);
        inorder(Class->RC);
    }
}

void displayStudents(CLASS Class)
{
    if(Class==NULL)
    {
        printf("\n\n\tEmpty class list!\n\n");
    }
    else
    {
        printf("\n***************************************************************************************************************************\n");
        printf("%-15s %-15s %-15s %-15s %-15s %-15s %-15s\n", "ID", "FIRST NAME", "LAST NAME", "M.I", "SEX", "COURSE", "GPA");
        printf("-------------------------------------------------------------------------------------------------------------------------------\n");

        StudentLevelOrder(Class);
        printf("\n\n");
    }
}

void groupBySex(CLASS Class, CLASS *maleStuds, CLASS *femaleStuds)
{
    CLASS tempQueue[MAX], currentStud;
    int front=1, rear=0;

    if(Class!=NULL)
    {
        for(tempQueue[++rear]=Class; front!=(rear+1)%MAX; )
        {
            currentStud = tempQueue[front];
            front = (front+1)%MAX;

            if(currentStud!=NULL)
            {
                if(currentStud->Stud->S==M)
                {
                    addStudent(maleStuds, currentStud->Stud);
                    (*maleStuds)->noOfStudents+=1;
                }
                else
                {
                    addStudent(femaleStuds, currentStud->Stud);
                    (*femaleStuds)->noOfStudents+=1;
                }

                rear=(rear+1)%MAX;
                tempQueue[rear]=currentStud->LC;
                rear=(rear+1)%MAX;
                tempQueue[rear]=currentStud->RC;
            }
        }
    }
}

CLASS groupByCourse(CLASS Class, CLASS *grp, Course course)
{
    CLASS tempQueue[MAX], currentStud;
    int front=1, rear=0;

    if(Class!=NULL)
    {
        for(tempQueue[++rear]=Class; front!=(rear+1)%MAX; )
        {
            currentStud = tempQueue[front];
            front = (front+1)%MAX;

            if(currentStud!=NULL)
            {
                if(currentStud->Stud->course==course)
                {
                    addStudent(grp, currentStud->Stud);
                    (*grp)->noOfStudents+=1;
                }

                rear=(rear+1)%MAX;
                tempQueue[rear]=currentStud->LC;
                rear=(rear+1)%MAX;
                tempQueue[rear]=currentStud->RC;
            }
        }
    }

    return *grp;
}

int main()
{
    studType students1[MAX] = {
        {"19103991", {"Shannen", "Nazareno", 'T'}, F, BSIS, 1.7},
        {"20103337", {"Jasper", "Marbella", 'S'}, M, BSIT, 2.4},
        {"19106000", {"Butter", "Cup", 'N'}, F, BSCS, 3.1}
    };

    
    CLASS DSA;

    CLASS maleStuds, femaleStuds;
    CLASS BSISstud;

    initClassList(&DSA);
    initClassList(&maleStuds);
    initClassList(&femaleStuds);
    initClassList(&BSISstud);

    displayStudents(DSA);
    populateClass(&DSA, students1, 3);
    displayStudents(DSA);

    groupBySex(DSA, &maleStuds, &femaleStuds);
    removeStudent(&DSA, "19103991");
    printf("FEMALE STUDENTS: ");
    displayStudents(femaleStuds);

    BSISstud = groupByCourse(DSA, &BSISstud, BSIS);
    printf("\nBSIS STUDENTS: ");
    displayStudents(BSISstud);

    displayStudents(DSA);


    return 0;
}