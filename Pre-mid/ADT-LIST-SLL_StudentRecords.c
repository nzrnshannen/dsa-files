/*=====================================================================================================
Created by: Shannen T. Nazareno
Date: 12/27/2023

Notes:
1. Will add yr and dept for studRec /
2. + functions: filterByYrLvl / , filterByDept /, sortByYrLvl /
3. + : enum for departments (DCISM = 1, etc) /
4. + : before adding a student, check if course is present or valid /
5. Menu [add, delete(w/ clearStudRec option), search(w/ filter), sort, checkAvailability(isPresent())]


Functions to be implemented:
sort by id /, fname /, lname /
clearStudRec == clear a section (probably or given year lvl)
clearAllRec /
======================================================================================================*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define SIZE 40
#define NULL_VAL -9999999

typedef enum{
    DCISM = 1,
    DCLL,
    DEEE
}Department;

typedef struct{
    int id;
    char fName[SIZE], lName[SIZE];
    char mid_init;
    char course[SIZE];
    Department dept;
    int yrLvl;
}studRec;

typedef struct node{
    studRec Stud;
    struct node *next_rec;
}studType, *LIST;

void initList(LIST* L);
void insertUnique(LIST *L, studRec S);
void printRecords(LIST L);

bool isEmpty(LIST L);
bool isPresent(LIST L, int id);
bool authenticateCourse(Department dept, char *course);

void emptyListMsg();
void noExistingRecMsg();

studRec searchStud(LIST L, int id);

void filterByFname(LIST L, char *f_name);
void filterByLname(LIST L, char *l_name);
void filterByCourse(LIST L, char *course);
void filterByYrLvl(LIST L, int yrLvl);
void filterByDept(LIST L, char *dept);

char* printDeptName(Department dept);

void sortByYrLvl(LIST *L);
void sortByID(LIST *L);
void sortByFName(LIST *L);
void sortByLName(LIST *L);

void clearAllRec(LIST *L);

bool authenticateCourse(Department dept, char *course)
{
    switch(dept)
    {
        case DCISM: 
            return ((strcmp(course, "Information Systems")==0) 
            || (strcmp(course, "Information Technology") == 0)
            || (strcmp(course, "Computer Science")==0)) 
            ? true : false;
        break;
        case DCLL:
            return ((strcmp(course, "Applied Linguistics")==0) 
            || (strcmp(course, "Literature") == 0) 
            || (strcmp(course, "English Language Studies")==0)) 
            ? true : false;
        break;
        case DEEE: 
            return ((strcmp(course, "Electrical Engineering")==0)
            || (strcmp(course, "Electronics Engineering")==0)) 
            ? true : false; 
        break;

        default: return false; break;
    }
}   


char* printDeptName(Department dept)
{
    switch(dept)
    {
        case DCISM: return ("DCISM"); break;
        case DCLL: return ("DCLL"); break;
        case DEEE: return ("DEEE"); break;

        default: return ("\n\t> Unknown Department < \n\n"); break;
    }
}

//sortByID
//sortByFName
//sortByLName

//clearStudRec

bool isEmpty(LIST L)
{
    return (L==NULL);
}

bool isPresent(LIST L, int id)
{
    LIST trav;
    for(trav=L; trav!=NULL && trav->Stud.id!=id; trav=trav->next_rec){}

    return (trav!=NULL && trav->Stud.id==id) ? true : false;
}

studRec searchStud(LIST L, int id)
{
    studRec null_stud = {NULL_VAL, "XXXXX", "XXXXX", 'X', "XXXXX", NULL_VAL, NULL_VAL};
    LIST check;
    for(check=L; check!=NULL && check->Stud.id!=id; check=check->next_rec){}

    return (check!=NULL && check->Stud.id==id) ? check->Stud : null_stud;
}

void emptyListMsg()
{
    printf("\n\nNo student records yet!\n\n");
}

void noExistingRecMsg()
{
    printf("\n\n\tStudent doesn't exists!\n\n");
}

void initList(LIST *L)
{
    *L = NULL;
}

void insertUnique(LIST *L, studRec S)
{
    if(authenticateCourse(S.dept, S.course))
    {
        LIST check = *L;
        for(check = *L; check!=NULL&&check->Stud.id!=S.id; check=check->next_rec){}
        
        if(check==NULL)
        {
            LIST newStud = (LIST)malloc(sizeof(studType));
            if(newStud==NULL)
            {
                printf("\nMemory allocation failure!");
                exit(1);
            }

            newStud->Stud = S;
            newStud->next_rec = *L;
            *L = newStud;

            printf("\n\tSuccessfully added student [%d]\n\n", S.id);
        }
        else
        {
            printf("\n\tStudent record already exists!\n\n");
        }
    }
    else
    {
        printf("\n\tInvalid Course!\n");
    }
    
    
}

void printRecords(LIST L)
{
    if(isEmpty(L))
    {
        emptyListMsg();
    }
    else
    {
        LIST trav;
        int ctr = 1;

        printf("\n****************************\n");
        for(trav=L; trav!=NULL; trav=trav->next_rec)
        {
            printf("\tSTUDENT %d\n\n", ctr++);
            printf("ID: %d\n", trav->Stud.id);
            printf("Name: %s %c. %s\n", trav->Stud.fName, trav->Stud.mid_init, trav->Stud.lName);
            printf("Course: %s\n", trav->Stud.course);
            printf("Department: %s\n", printDeptName(trav->Stud.dept));
            printf("Year: %d\n\n", trav->Stud.yrLvl);
        }
    }
}

void deleteStudent(LIST *L, int id)
{
    if(isEmpty(*L))
    {
        emptyListMsg();
    }
    else
    {
        LIST *trav;
        for(trav=L; *trav!=NULL && (*trav)->Stud.id!=id; trav=&(*trav)->next_rec){}

        if(*trav!=NULL && (*trav)->Stud.id==id )
        {   
            LIST temp;

            if(trav==L)
            {
                temp = *L;
                *L = (*L)->next_rec;
                
            }
            else
            {
                temp = *trav;
                *trav = temp->next_rec;
            }

            free(temp);

            printf("\n\tSuccessfully removed Student [%d]\n\n", id);
        }
        else
        {
            noExistingRecMsg();
        }
    }
}

void filterByFname(LIST L, char *f_name)
{
    if(isEmpty(L))
    {
        emptyListMsg();
    }
    else
    {
        LIST check;

        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nFilter by first name: %s\n\n--------------------------------------------------------------------------------------------------------------------------\n", f_name);
        for(check=L; check!=NULL && (strcmp(f_name, check->Stud.fName)!=0); check=check->next_rec){}

        if(check==NULL || strcmp(f_name, check->Stud.fName)!=0)
        {
            noExistingRecMsg();
        }
        else
        {
            LIST trav;
            printf("%-12s | %-12s | %-15s | %-15s | %-15s | %-15s | %-5s \n", "ID", "FIRST NAME", "LAST NAME", "M.I", "COURSE", "DEPARTMENT", "YEAR");
            for(trav=L; trav!=NULL; trav=trav->next_rec)
            {
                if(strcmp(trav->Stud.fName, f_name)==0)
                {
                    printf("%-15d %-15s %-15s %-17c %-15s %-15s %d\n", trav->Stud.id, trav->Stud.fName, trav->Stud.lName, trav->Stud.mid_init, trav->Stud.course, printDeptName(trav->Stud.dept), trav->Stud.yrLvl);
                }
            }
            printf("\n=================\n\n");
        }
    }
}

void filterByLname(LIST L, char *l_name)
{
    if(isEmpty(L))
    {
        emptyListMsg();
    }
    else
    {
        LIST check;
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nFilter by last name: %s\n\n--------------------------------------------------------------------------------------------------------------------------\n", l_name);
        for(check=L; check!=NULL && (strcmp(l_name, check->Stud.lName)!=0); check=check->next_rec){}

        if(check==NULL || strcmp(l_name, check->Stud.lName)!=0)
        {
            noExistingRecMsg();
        }
        else
        {
            LIST trav;
            printf("%-12s | %-12s | %-15s | %-15s | %-15s | %-15s | %-15s\n", "ID", "FIRST NAME", "LAST NAME", "M.I", "COURSE", "DEPARTMENT", "YEAR");
            for(trav=L; trav!=NULL; trav=trav->next_rec)
            {
                if(strcmp(trav->Stud.lName, l_name)==0)
                {
                    printf("%-15d %-15s %-15s %-17c %-15s %-15s %d\n", trav->Stud.id, trav->Stud.fName, trav->Stud.lName, trav->Stud.mid_init, trav->Stud.course, printDeptName(trav->Stud.dept), trav->Stud.yrLvl);
                }
            }
            printf("\n=================\n\n");
        }
    }
}

void filterByCourse(LIST L, char *course)
{
    if(isEmpty(L))
    {
        emptyListMsg();
    }
    else
    {
        LIST check;
        
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nFilter by course: %s\n\n--------------------------------------------------------------------------------------------------------------------------\n", course);
        for(check=L; check!=NULL && (strcmp(course, check->Stud.course)!=0); check=check->next_rec){}

        if(check==NULL || strcmp(check->Stud.course, course)!=0)
        {
            noExistingRecMsg();
        }
        else
        {
            LIST trav;
            printf("%-12s | %-12s | %-15s | %-15s | %-15s | %-5s | %-15s  \n", "ID", "FIRST NAME", "LAST NAME", "M.I", "COURSE", "DEPARTMENT", "YEAR");
            for(trav=L; trav!=NULL; trav=trav->next_rec)
            {
                if(strcmp(trav->Stud.course, course)==0)
                {
                    printf("%-15d %-15s %-15s %-17c %-15s %-15s %-5d\n", trav->Stud.id, trav->Stud.fName, trav->Stud.lName, trav->Stud.mid_init, trav->Stud.course, printDeptName(trav->Stud.dept), trav->Stud.yrLvl);
                }
            }
            printf("\n=================\n\n");
        }
    }
}

void filterByYrLvl(LIST L, int yrLvl)
{
    if(isEmpty(L))
    {
        emptyListMsg();
    }
    else
    {
        LIST check;
         printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nFilter by year level: %d\n\n--------------------------------------------------------------------------------------------------------------------------\n", yrLvl);
         for(check=L; check!=NULL && yrLvl!=check->Stud.yrLvl; check=check->next_rec){}

         if(check==NULL || yrLvl!=check->Stud.yrLvl)
         {
            noExistingRecMsg();
         }
         else
         {
            LIST trav;
            printf("%-12s | %-12s | %-15s | %-15s | %-15s | %-15s | %-5s \n", "ID", "FIRST NAME", "LAST NAME", "M.I", "COURSE", "DEPARTMENT", "YEAR");
            for(trav=L; trav!=NULL; trav=trav->next_rec)
            {
                if(yrLvl==trav->Stud.yrLvl)
                {
                    printf("%-15d %-15s %-15s %-17c %-15s %-15s %d\n", trav->Stud.id, trav->Stud.fName, trav->Stud.lName, trav->Stud.mid_init, trav->Stud.course, printDeptName(trav->Stud.dept), trav->Stud.yrLvl);
                }
            }
            printf("\n=================\n\n");
         }
        
    }
}

void filterByDept(LIST L, char *dept)
{
    if(isEmpty(L))
    {
        emptyListMsg();
    }
    else
    {
        LIST check;
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nFilter by departement: %s\n\n--------------------------------------------------------------------------------------------------------------------------\n", dept);
        for(check=L; check!=NULL && (strcmp(dept, printDeptName(check->Stud.dept))!=0); check=check->next_rec){}

        if(check==NULL || strcmp(dept, printDeptName(check->Stud.dept))!=0)
        {
            printf("%d",strcmp(dept, printDeptName(check->Stud.dept)));
            noExistingRecMsg();
        }
        else
        {
            LIST trav;
            printf("%-12s | %-12s | %-15s | %-15s | %-15s | %-15s | %-15s\n", "ID", "FIRST NAME", "LAST NAME", "M.I", "COURSE", "DEPARTMENT", "YEAR");
            for(trav=L; trav!=NULL; trav=trav->next_rec)
            {
                if(strcmp(printDeptName(trav->Stud.dept), dept)==0)
                {
                    printf("%-15d %-15s %-15s %-17c %-15s %-15s %d\n", trav->Stud.id, trav->Stud.fName, trav->Stud.lName, trav->Stud.mid_init, trav->Stud.course, printDeptName(trav->Stud.dept), trav->Stud.yrLvl);
                }
            }
            printf("\n=================\n\n");
        }
    }
}

void sortByYrLvl(LIST *L)
{
    if(isEmpty(*L))
    {
        emptyListMsg();
    }
    else
    {
        printf("\n\n\t** SORTING BY YEAR LEVEL**\n\n");
        LIST *tmp1, *tmp2;

        for(tmp1=L; (*tmp1)->next_rec!=NULL; tmp1=&(*tmp1)->next_rec)
        {
            for(tmp2=tmp1; (*tmp2)->next_rec!=NULL; tmp2=&(*tmp2)->next_rec)
            {
                if((*tmp2)->Stud.yrLvl > (*tmp2)->next_rec->Stud.yrLvl)
                {
                    studRec swapRec;
                    swapRec = (*tmp2)->Stud;
                    (*tmp2)->Stud = (*tmp2)->next_rec->Stud;
                    (*tmp2)->next_rec->Stud = swapRec;
                }
            }
        }
    }
}

void sortByID(LIST *L)
{
    if(isEmpty(*L))
    {
        emptyListMsg();
    }
    else
    {
        printf("\n\n\t** SORTING BY ID **\n\n");
        LIST *tmp1, *tmp2;

        for(tmp1=L; (*tmp1)->next_rec!=NULL; tmp1=&(*tmp1)->next_rec)
        {
            for(tmp2=tmp1; (*tmp2)->next_rec!=NULL; tmp2=&(*tmp2)->next_rec)
            {
                if((*tmp2)->Stud.id > (*tmp2)->next_rec->Stud.id)
                {
                    studRec swapRec;
                    swapRec = (*tmp2)->Stud;
                    (*tmp2)->Stud = (*tmp2)->next_rec->Stud;
                    (*tmp2)->next_rec->Stud = swapRec;
                }
            }
        }
    }
}

void sortByFName(LIST *L)
{
    if(isEmpty(*L))
    {
        emptyListMsg();
    }
    else
    {
        printf("\n\n\t** SORTING BY FIRST NAME **\n\n");
        LIST *tmp1, *tmp2;

        for(tmp1=L; (*tmp1)->next_rec!=NULL; tmp1=&(*tmp1)->next_rec)
        {
            for(tmp2=tmp1; (*tmp2)->next_rec!=NULL; tmp2=&(*tmp2)->next_rec)
            {
                if(strcmp((*tmp2)->Stud.fName, (*tmp2)->next_rec->Stud.fName) == 1)
                {
                    studRec swapRec;
                    swapRec = (*tmp2)->Stud;
                    (*tmp2)->Stud = (*tmp2)->next_rec->Stud;
                    (*tmp2)->next_rec->Stud = swapRec;
                }

            }
        }
    }
}

void sortByLName(LIST *L)
{
    if(isEmpty(*L))
    {
        emptyListMsg();
    }
    else
    {
        printf("\n\n\t** SORTING BY LAST NAME **\n\n");
        LIST *tmp1, *tmp2;

        for(tmp1=L; (*tmp1)->next_rec!=NULL; tmp1=&(*tmp1)->next_rec)
        {
            for(tmp2=tmp1; (*tmp2)->next_rec!=NULL; tmp2=&(*tmp2)->next_rec)
            {
                if(strcmp((*tmp2)->Stud.lName, (*tmp2)->next_rec->Stud.lName)==1)
                {
                    studRec swapRec;
                    swapRec = (*tmp2)->Stud;
                    (*tmp2)->Stud = (*tmp2)->next_rec->Stud;
                    (*tmp2)->next_rec->Stud = swapRec;
                }
            }
        }
    }
}

void clearAllRec(LIST *L)
{
    if(isEmpty(*L))
    {
        emptyListMsg();
    }
    else
    {
        while((*L)!=NULL)
        {
            LIST clr;
            clr = *L;
            *L = (*L)->next_rec;
            free(clr);
        }

        printf("\n==========================================================\nLIST CLEARED\n\n");
    }
}
int main()
{
    LIST section_A;
    studRec stud1 = {19103991, "Shannen", "Nazareno", 'T', "Information Systems", DCISM, 3}; 
    studRec stud2 = {9999, "Butter", "Cups", 'C', "Information Systems", DCISM, 3};
    studRec stud3 = {9234, "Shannen", "Nazars", 'C', "Information Systems", DCISM, 2};
    studRec stud4 = {1351, "test1", "test1", 'A', "Electrical Engineering", DEEE, 1};
    initList(&section_A);

    insertUnique(&section_A, stud3);
    insertUnique(&section_A, stud1);
    insertUnique(&section_A, stud2);
    insertUnique(&section_A, stud4);

    printRecords(section_A);

    deleteStudent(&section_A, 1910399);
    printRecords(section_A);

    //printf("Is present? %d", isPresent(section_A, 19103991));
    // studRec testRetrieve = searchStud(section_A, 1910399);

    // filterByCourse(section_A, "Information Systems");
    // filterByCourse(section_A, "Electrical Engineering");
    // filterByLname(section_A, "test1");


    // filterByYrLvl(section_A, 3);
    // filterByDept(section_A, "DCISM");


    sortByFName(&section_A);
    printRecords(section_A);
    sortByLName(&section_A);
    printRecords(section_A);
    clearAllRec(&section_A);
    printRecords(section_A);
    return 0;
}