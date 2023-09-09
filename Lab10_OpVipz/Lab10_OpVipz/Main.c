#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#define MAX_SIZE 20 // Determination of the maximum size of strings and arrays
#define MAX_LENTH 11
#define MAX_STUDENTS 20 // 
#define MARKS_NUM 5 // Determination of the number of marks

//------------------------------------------------------------------------------
// Structure for creating a singly linked list.
// The first field of the structure is a pointer to combine the objects of 
// the structure into a list.
// The rest of the fields are a description of the students.
typedef struct Sstudent {
    char m_sSurname[MAX_SIZE];
    char m_sName[MAX_SIZE];
    int m_nDate, m_nMonth, m_nYear;
    int m_aMarks[MARKS_NUM];
    float m_fRatingScore;
    long m_lAge;
    struct Sstudent* m_pNext;
}Sstudent;

//------------------------------------------------------------------------------
// Reads student data from a file or command line and adds them to the linked
// list. Takes the address of a pointer to the first element of the list.
void ReadingDataOfStudents(Sstudent **pssHead) {
    printf("\nREADING:\n");
    char cReadType[MAX_SIZE];
    do {
        printf("Enter type of reading (1 from file, 2 from comand line): ");
        gets(cReadType);
        rewind(stdin);
        if ((cReadType[0] != '1' && cReadType[0] != '2') ||
            cReadType[1] != '\0') {
            printf("Value is incorrect!\n");
            continue;
        }
    } while ((cReadType[0]!='1' && cReadType[0] != '2') || cReadType[1] != '\0');

    char cStudentsCnt[MAX_SIZE];
    int nStudentsCnt;
    int nCheck1;
    int nCheck2;
    do {
        printf("How many students want you add? ");
        gets(cStudentsCnt);
        rewind(stdin);
        int temp = 0;
        nCheck1 = 0;
        nCheck2 = strlen(cStudentsCnt);
        for (int i = 0; i < nCheck2; i++) {
            if (isdigit(cStudentsCnt[i])) {
                nCheck1++;
            }
        }
        if (nCheck1 == nCheck2) {
            temp = atoi(cStudentsCnt);
            if (temp > MAX_STUDENTS) {
                printf("The set value is greater than the maximum: %s > %i\n", cStudentsCnt, MAX_STUDENTS);
                nCheck1--;
                continue;
            }
            else {
                nStudentsCnt = temp;
            }
        }
        else {
            printf("Set value incorrect!\n");
            continue;
        }
    } while (nCheck1 != nCheck2);

    if (cReadType[0] == '1' && cReadType[1] == '\0') {
        char sFileName[MAX_SIZE] = "students.txt";
        /*char sFileName[MAX_SIZE];
        do {
            printf("Specify the name of the reading file (name.txt): ");
            gets(sFileName);
            rewind(stdin);
            if (strcmp(sFileName, "students.txt") != 0) {
                printf("Invalid file name!\n");
            }
        } while (strcmp(sFileName, "students.txt") != 0);*/

        FILE* fStudents = fopen(sFileName, "r");

        Sstudent* pssTemp = (Sstudent*)malloc(sizeof(Sstudent));
        pssTemp = *pssHead;

        int i = 0;
        while (!feof(fStudents) && i< nStudentsCnt) {
            while (*pssHead != NULL && pssTemp->m_pNext != NULL) {
                pssTemp = pssTemp->m_pNext;
            }
            Sstudent* pssNewNode = (Sstudent*)malloc(sizeof(Sstudent));
            if (*pssHead != NULL) {
                pssTemp->m_pNext = pssNewNode;
                pssNewNode->m_pNext = NULL;
            }
            else {
                *pssHead = pssNewNode;
                pssNewNode->m_pNext = NULL;
            }

            int nDataCounter = 0;

                char sTempSurname[MAX_SIZE];
                char sTempName[MAX_SIZE];
                char sTempDate[MAX_SIZE], sTempMonth[MAX_SIZE], sTempYear[MAX_SIZE];
                char sTempMarks[MARKS_NUM][MAX_SIZE];

                //Surname

                //gets(sTempSurname);
                //rewind(stdin);
                fscanf(fStudents, "%s", sTempSurname);
                int nErrors = 0;
                int nLenSurn = strlen(sTempSurname);
                if (nLenSurn >= 380) {
                    printf("Line %i: File is empty\n", i + 1);
                    *pssHead = NULL;
                    printf("\nRESULT: \n");
                    return;
                }
                if (nLenSurn > MAX_LENTH) {
                    printf("Line %i Surname: The input is too long (maximum - %i)\n",i+1, MAX_LENTH);
                    *pssHead = NULL;
                    printf("\nRESULT: \n");
                    return;
                }
                for (int j = 0; j < nLenSurn; j++) {
                    int nFlag = 0;
                    if (isdigit(sTempSurname[j])) {
                        printf("Line %i Surname %i letter: ",i+1, j + 1);
                        printf("Surname cannot contain numbers!\n");
                        nFlag = 1;
                        nErrors++;
                    }
                    if (!isalpha(sTempSurname[j])) {
                        if (nFlag != 1) {
                            printf("Line %i Surname %i letter: ", i+1,j + 1);
                            printf("Surname cannot contain other symbols!\n");
                        }
                        nErrors++;
                    }
                    if (islower(sTempSurname[0])) {
                        sTempSurname[0] = toupper(sTempSurname[0]);
                    }
                }
                if (nErrors <= 0) {
                    //strcpy(pssNewNode->m_sSurname, sTempSurname);
                    nDataCounter++;
                }
                else{
                    *pssHead = NULL;
                    printf("\nRESULT: \n");
                    return;
                }
                nErrors = 0;

                //Name

                //gets(sTempName);
                //rewind(stdin);
                fscanf(fStudents, "%s", sTempName);
                int nLenName = strlen(sTempName);
                if (nLenName > MAX_LENTH) {
                    printf("Line %i Name: The input is too long (maximum - %i)\n",i+1 ,MAX_LENTH);
                    *pssHead = NULL;
                    printf("\nRESULT: \n");
                    return;
                }

                for (int j = 0; j < nLenName; j++) {
                    int nFlag = 0;
                    if (isdigit(sTempName[j])) {
                        printf("Line %i Name %i letter: ", i+1,j + 1);
                        printf("Name cannot contain numbers!\n");
                        nFlag = 1;
                        nErrors++;
                    }
                    if (!isalpha(sTempName[j])) {
                        if (nFlag != 1) {
                            printf("Line %i Name %i letter: ", i + 1, j+1);
                            printf("Name cannot contain other symbols!\n");
                        }
                        nErrors++;
                    }
                    if (islower(sTempName[0])) {
                        sTempName[0] = toupper(sTempName[0]);
                    }
                }
                if (nErrors <= 0) {
                    //strcpy(pssNewNode->m_sName, sTempName);
                    nDataCounter++;
                }
                else {
                    *pssHead = NULL;
                    printf("\nRESULT: \n");
                    return;
                }
                nErrors = 0;

                //Year

                //gets(sTempYear);
                //rewind(stdin);
                fscanf(fStudents, "%s", sTempYear);
                int nYear;
                int nLeapYear = 0;
                int nYearCheck1 = 0;
                int nYearCheck2 = strlen(sTempYear);
                for (int i = 0; i < nYearCheck2; i++) {
                    if (isdigit(sTempYear[i])) {
                        nYearCheck1++;
                    }
                }
                if (nYearCheck1 == nYearCheck2) {
                    nYear = atoi(sTempYear);
                    if (nYear >= 1950 && nYear <= 2100) {
                        nDataCounter++;
                        if (nYear % 4 == 0) {
                            if (nYear % 100 == 0 && nYear % 400 > 0) {
                                nLeapYear = 0;
                            }
                            else {
                                nLeapYear = 1;
                            }
                        }
                        else {
                            nLeapYear = 0;
                        }
                    }
                    else {
                        printf("Line %i Year: The value must be 1950-2015\n", i+1);
                        *pssHead = NULL;
                        printf("\nRESULT: \n");
                        return;
                    }
                }
                else {
                    printf("Line %i Year: Set value incorrect!\n", i+1);
                    *pssHead = NULL;
                    printf("\nRESULT: \n");
                    return;
                }

                //Month

                //gets(sTempMonth);
                //rewind(stdin);
                fscanf(fStudents, "%s", sTempMonth);
                int nMonth;
                int nMonthCheck1 = 0;
                int nMonthCheck2 = strlen(sTempMonth);
                for (int i = 0; i < nMonthCheck2; i++) {
                    if (isdigit(sTempMonth[i])) {
                        nMonthCheck1++;
                    }
                }
                if (nMonthCheck1 == nMonthCheck2) {
                    nMonth = atoi(sTempMonth);
                    if (nMonth > 0 && nMonth <= 12) {
                        nDataCounter++;
                    }
                    else {
                        printf("Line %i Month: The value must be 1-12\n",i+1);
                        *pssHead = NULL;
                        printf("\nRESULT: \n");
                        return;
                    }
                }
                else {
                    printf("Line %i Month: Set value incorrect!\n", i+1);
                    *pssHead = NULL;
                    printf("\nRESULT: \n");
                    return;
                }

                //Date

                //gets(sTempDate);
                //rewind(stdin);
                fscanf(fStudents, "%s", sTempDate);
                int nDate;
                int nDataCheck1 = 0;
                int nDataCheck2 = strlen(sTempDate);
                for (int i = 0; i < nDataCheck2; i++) {
                    if (isdigit(sTempDate[i])) {
                        nDataCheck1++;
                    }
                }
                if (nDataCheck1 == nDataCheck2) {
                    nDate = atoi(sTempDate);
                    if (nLeapYear == 0) {
                        if (nMonth == 2) {
                            if (nDate > 0 && nDate <= 28) { nDataCounter++; }
                            else {
                                printf("Line %i Date: The value must be 1-28\n", i + 1);
                                *pssHead = NULL;
                                printf("\nRESULT: \n");
                                return;
                            }
                        }
                        else if (nMonth % 2 == 0) {
                            if (nDate > 0 && nDate <= 31) { nDataCounter++; }
                            else {
                                printf("Line %i Date: The value must be 1-31\n", i+1);
                                *pssHead = NULL;
                                printf("\nRESULT: \n");
                                return;
                            }
                            //pssNewNode->m_nDate = nDate;
                        }
                        else if (nMonth % 2 != 0) {
                            if (nDate > 0 && nDate <= 30) { nDataCounter++; }
                            else {
                                printf("Line %i Date: The value must be 1-30\n", i+1);
                                *pssHead = NULL;
                                printf("\nRESULT: \n");
                                return;
                            }
                        }
                    }
                    else if (nLeapYear == 1) {
                        if (nMonth == 2) {
                            if (nDate > 0 && nDate <= 27) { nDataCounter++; }
                            else {
                                printf("Line %i Date: The value must be 1-27\n", i+1);
                                *pssHead = NULL;
                                printf("\nRESULT: \n");
                                return;
                            }
                        }
                        else if (nMonth % 2 == 0) {
                            if (nDate > 0 && nDate <= 30) { nDataCounter++; }
                            else {
                                printf("Line %i Date: The value must be 1-30\n", i+1);
                                *pssHead = NULL;
                                printf("\nRESULT: \n");
                                return;
                            }
                            //pssNewNode->m_nDate = nDate;
                        }
                        
                        else if (nMonth % 2 != 0) {
                            if (nDate > 0 && nDate <= 31) { nDataCounter++; }
                            else {
                                printf("Line %i Date: The value must be 1-31\n", i+1);
                                *pssHead = NULL;
                                printf("\nRESULT: \n");
                                return;
                            }
                        }
                    }
                }
                else {
                    printf("Line %i Date: Set value incorrect!\n", i+1);
                    *pssHead = NULL;
                    printf("\nRESULT: \n");
                    return;
                }

                //Marks
                int nMark[MARKS_NUM];
                int nErrorsMarks = 0;
                for (int k = 0; k < MARKS_NUM; k++) {
                    //gets(sTempMarks[i]);
                    //rewind(stdin);
                    fscanf(fStudents, "%s", sTempMarks[k]);
                    //int nMark;
                    int nMarkCheck1 = 0;
                    int nMarkCheck2 = strlen(sTempMarks[k]);
                    for (int j = 0; j < nMarkCheck2; j++) {
                        if (isdigit(sTempMarks[k][j])) {
                            nMarkCheck1++;
                        }
                    }
                    if (nMarkCheck1 == nMarkCheck2) {
                        nMark[k] = atoi(sTempMarks[k]);
                        if (nMark[k] >= 1 && nMark[k] <= 5) {
                            //pssNewNode->m_aMarks[i] = nMark[i];
                            nDataCounter++;
                        }
                        else {
                            printf("Line %i Mark %i: The value must be 1-5\n",i+1, k+1);
                            nErrorsMarks++;
                            *pssHead = NULL;
                            printf("\nRESULT: \n");
                            return;
                        }
                    }
                    else {
                        printf("Line %i Mark %i: Set value incorrect!\n", i + 1, k + 1);
                        nErrorsMarks++;
                        *pssHead = NULL;
                        printf("\nRESULT: \n");
                        return;
                    }
                }
                if (nErrorsMarks != 0) {
                    *pssHead = NULL;
                    printf("\nRESULT: \n");
                    return;
                }
                rewind(stdin);

                if (nDataCounter >= 10) {
                    strcpy(pssNewNode->m_sSurname, sTempSurname);
                    strcpy(pssNewNode->m_sName, sTempName);
                    pssNewNode->m_nDate = nDate;
                    pssNewNode->m_nMonth = nMonth;
                    pssNewNode->m_nYear = nYear;
                    for (int j = 0; j < MARKS_NUM; j++) {
                        pssNewNode->m_aMarks[j] = nMark[j];
                    }
                }
                else {
                    *pssHead = NULL;
                    printf("\nRESULT: \n");
                    return;
                }

            pssNewNode->m_fRatingScore = 0;
            for (int j = 0; j < MARKS_NUM; j++) {
                pssNewNode->m_fRatingScore += pssNewNode->m_aMarks[j];
            }
            pssNewNode->m_fRatingScore = pssNewNode->m_fRatingScore / MARKS_NUM;
            pssTemp = *pssHead;
            i++;
        }
        fclose(fStudents);
    } else if (cReadType[0] == '2' && cReadType[1] == '\0') {
        Sstudent* pssTemp = (Sstudent*)malloc(sizeof(Sstudent));
        pssTemp = *pssHead;

        int i = 0;
        while (i < nStudentsCnt) {
            while (*pssHead != NULL && pssTemp->m_pNext != NULL) {
                pssTemp = pssTemp->m_pNext;
            }
            Sstudent* pssNewNode = (Sstudent*)malloc(sizeof(Sstudent));
            if (*pssHead != NULL) {
                pssTemp->m_pNext = pssNewNode;
                pssNewNode->m_pNext = NULL;
            }
            else {
                *pssHead = pssNewNode;
                pssNewNode->m_pNext = NULL;
            }

            int nComplate = 0;
            do {
                printf("Enter data of %i student(Surname Name yyyy mm dd m1 m2 m3 m4 m5): \n", i+1);

                char sTempSurname[MAX_SIZE];
                char sTempName[MAX_SIZE];
                char sTempDate[MAX_SIZE], sTempMonth[MAX_SIZE], sTempYear[MAX_SIZE];
                char sTempMarks[MARKS_NUM][MAX_SIZE];

                //Surname
                
                //gets(sTempSurname);
                //rewind(stdin);
                scanf("%s", sTempSurname);
                int nErrors = 0;
                int nLenSurn = strlen(sTempSurname);
                if (nLenSurn > MAX_LENTH) {
                    printf("The input is too long (maximum - %i)\n", MAX_LENTH);
                    continue;
                }
                for (int i = 0; i < nLenSurn; i++) {
                    int nFlag = 0;
                    if (isdigit(sTempSurname[i])) {
                        printf("Surname %i letter: ", i + 1);
                        printf("Surname cannot contain numbers!\n");
                        nFlag = 1;
                        nErrors++;
                    }
                    if (!isalpha(sTempSurname[i])) {
                        if (nFlag != 1) {
                            printf("Surname %i letter: ", i + 1);
                            printf("Surname cannot contain other symbols!\n");
                        }
                        nErrors++;
                    }
                    if (islower(sTempSurname[0])) {
                        sTempSurname[0] = toupper(sTempSurname[0]);
                    }
                }
                if (nErrors <= 0) {
                    strcpy(pssNewNode->m_sSurname, sTempSurname);
                }
                else {
                    continue;
                }
                nErrors = 0;

                //Name
               
                //gets(sTempName);
                //rewind(stdin);
                scanf("%s", sTempName);
                int nLenName = strlen(sTempName);
                if (nLenName > MAX_LENTH) {
                    printf("The input is too long (maximum - %i)\n", MAX_LENTH);
                    continue;
                }

                for (int i = 0; i < nLenName; i++) {
                    int nFlag = 0;
                    if (isdigit(sTempName[i])) {
                        printf("Name %i letter: ", i+1);
                        printf("Name cannot contain numbers!\n");
                        nFlag = 1;
                        nErrors++;
                    }
                    if (!isalpha(sTempName[i])) {
                        if (nFlag != 1) {
                            printf("Name %i letter: ", i + 1);
                            printf("Name cannot contain other symbols!\n");
                        }
                        nErrors++;
                    }
                    if (islower(sTempName[0])) {
                        sTempName[0] = toupper(sTempName[0]);
                    }
                }
                if (nErrors <= 0) {
                    strcpy(pssNewNode->m_sName, sTempName);
                } else {
                    continue;
                }
                nErrors = 0;

                //Year
                
                //gets(sTempYear);
                //rewind(stdin);
                scanf("%s", sTempYear);
                int nYear;
                int nLeapYear = 0;
                int nYearCheck1 = 0;
                int nYearCheck2 = strlen(sTempYear);
                for (int i = 0; i < nYearCheck2; i++) {
                    if (isdigit(sTempYear[i])) {
                        nYearCheck1++;
                    }
                }
                if (nYearCheck1 == nYearCheck2) {
                    nYear = atoi(sTempYear);
                    if (nYear >= 1950 && nYear <= 2100) {
                        if (nYear % 4 == 0) {
                            if (nYear % 100 == 0 && nYear % 400 > 0) {
                                nLeapYear = 0;
                            }
                            else {
                                nLeapYear = 1;
                            }
                        }
                        else {
                            nLeapYear = 0;
                        }
                    }
                    else {
                        printf("The value must be 1950-2015\n");
                        continue;
                    }
                }
                else {
                    printf("Set value incorrect!\n");
                    continue;
                }

                //Month
                
                //gets(sTempMonth);
                //rewind(stdin);
                scanf("%s", sTempMonth);
                int nMonth;
                int nMonthCheck1 = 0;
                int nMonthCheck2 = strlen(sTempMonth);
                for (int i = 0; i < nMonthCheck2; i++) {
                    if (isdigit(sTempMonth[i])) {
                        nMonthCheck1++;
                    }
                }
                if (nMonthCheck1 == nMonthCheck2) {
                    nMonth = atoi(sTempMonth);
                    if (nMonth > 0 && nMonth <= 12) {
                    }
                    else {
                        printf("The value must be 1-12\n");
                        continue;
                    }
                }
                else {
                    printf("Set value incorrect!\n");
                    continue;
                }

                //Date
                
                //gets(sTempDate);
                //rewind(stdin);
                scanf("%s", sTempDate);
                int nDate;
                int nDataCheck1 = 0;
                int nDataCheck2 = strlen(sTempDate);
                for (int i = 0; i < nDataCheck2; i++) {
                    if (isdigit(sTempDate[i])) {
                        nDataCheck1++;
                    }
                }
                //printf("lep year: %i", nLeapYear);
                if (nDataCheck1 == nDataCheck2) {
                    nDate = atoi(sTempDate);
                    if (nLeapYear == 0) {
                        if (nMonth == 2) {
                            if (nDate > 0 && nDate <= 28) { }
                            else {
                                printf("The value must be 1-28\n");
                                continue;
                            }
                        }
                        else if (nMonth % 2 == 0) {
                            if (nDate > 0 && nDate <= 31) { }
                            else {
                                printf("The value must be 1-31\n");
                                continue;
                            }
                            //pssNewNode->m_nDate = nDate;
                        }
                        else if (nMonth % 2 != 0) {
                            if (nDate > 0 && nDate <= 30) { }
                            else {
                                printf("The value must be 1-30\n");
                                continue;
                            }
                        }
                    }
                    else{
                        if (nMonth == 2) {
                            if (nDate > 0 && nDate <= 27) {}
                            else {
                                printf("The value must be 1-27\n");
                                continue;
                            }
                        }
                        else if (nMonth % 2 == 0) {
                            if (nDate > 0 && nDate <= 30) {}
                            else {
                                printf("The value must be 1-30\n");
                                continue;
                            }
                            //pssNewNode->m_nDate = nDate;
                        }
                        else if (nMonth % 2 != 0) {
                            if (nDate > 0 && nDate <= 31) {}
                            else {
                                printf("The value must be 1-31\n");
                                continue;
                            }
                        }
                    }
                }
                else {
                    printf("Set value incorrect!\n");
                    continue;
                }


                pssNewNode->m_nDate = nDate;
                pssNewNode->m_nMonth = nMonth; 
                pssNewNode->m_nYear = nYear;

                //Marks
                int nErrorsMarks = 0;
                for (int i = 0; i < MARKS_NUM; i++) {
                    //gets(sTempMarks[i]);
                    //rewind(stdin);
                    scanf("%s", sTempMarks[i]);
                    int nMark;
                    int nMarkCheck1 = 0;
                    int nMarkCheck2 = strlen(sTempMarks[i]);
                    for (int j = 0; j < nMarkCheck2; j++) {
                        if (isdigit(sTempMarks[i][j])) {
                            nMarkCheck1++;
                        }
                    }
                    if (nMarkCheck1 == nMarkCheck2) {
                        nMark = atoi(sTempMarks[i]);
                        if (nMark >= 1 && nMark <= 5) {
                            pssNewNode->m_aMarks[i] = nMark;
                        }
                        else {
                            printf("The value must be 1-5\n");
                            nErrorsMarks++;
                            break;
                        }
                    }
                    else {
                        printf("Set value incorrect!\n");
                        nErrorsMarks++;
                        break;
                    }
                }
                if (nErrorsMarks != 0) {
                    continue;
                }
            nComplate = 1;
            rewind(stdin);
            } while (nComplate <= 0);

            pssNewNode->m_fRatingScore = 0;
            for (int j = 0; j < MARKS_NUM; j++) {
                pssNewNode->m_fRatingScore += pssNewNode->m_aMarks[j];
            }
            pssNewNode->m_fRatingScore = pssNewNode->m_fRatingScore / MARKS_NUM;
            pssTemp = *pssHead;
            i++;
        }
    }
    printf("\nRESULT: \n");
}

//------------------------------------------------------------------------------
// Functions for better output tabulation.
// Take number of need minus symbols
void PrintRow(int nNumOfRowSym) {
    for (int i = 0; i < nNumOfRowSym; i++) {
        printf("-");
    }
}
// Functions for better output tabulation.
void PrintColumn() {
    printf("|");
}

// Displays the student data in a table.
// Takes the address of a pointer to the first element of the list.
void PrintList(Sstudent **pssHead) {
    if (*pssHead == NULL) {
        printf("The list is empty!\n");
        return;
    }
    int nNumOfRowSym = 92;
    PrintRow(nNumOfRowSym);
    printf("\n");
    PrintColumn(); printf("Surname\t"); PrintColumn(); printf("Name\t\t"); 
    PrintColumn(); printf("Date\t\t"); PrintColumn();
    for (int i = 0; i < MARKS_NUM; i++) {
        printf("M%i   ", i + 1); PrintColumn();
    }
    printf("Rating score"); PrintColumn(); printf("\n");
    PrintRow(nNumOfRowSym);
    printf("\n");

    int nSymAfterDot = 1;
    Sstudent* pssTemp = *pssHead;

    while (pssTemp != NULL) {
        PrintColumn();
        printf("%s   \t", pssTemp->m_sSurname);
        PrintColumn();
        printf("%s   \t", pssTemp->m_sName);
        PrintColumn();
        printf("%i.", pssTemp->m_nDate);
        printf("%i.", pssTemp->m_nMonth);
        printf("%i\t", pssTemp->m_nYear);
        PrintColumn();
        for (int k = 0; k < MARKS_NUM; k++) {
            printf("  %.*i  ", nSymAfterDot,pssTemp->m_aMarks[k]);
            PrintColumn();
        }
        printf("   %.*f    ",nSymAfterDot+2, pssTemp->m_fRatingScore);
        PrintColumn();
        printf("\n");
        pssTemp = pssTemp->m_pNext;
    }
    pssTemp = NULL;
    PrintRow(nNumOfRowSym);
    printf("\n");
}

//------------------------------------------------------------------------------
// Saves the results of the program to a file.Takes the address of a pointer 
// to the first element of the list, the number of the action to be performed
// and name of the file for note.
void NoteList(Sstudent **pssHead, int cEction, char *sNoteFileName) {
    FILE *fNote = fopen(sNoteFileName, "a");
    Sstudent* pssTemp = *pssHead;

    if (cEction == 1) {
        fprintf(fNote, "\nREADING: \n");
    } else if (cEction == 2) {
        fprintf(fNote, "\nSORTING: \n");
    } else if (cEction == 3) {
        fprintf(fNote, "\nDELETE BY AGE: \n");
    } else if (cEction == 4) {
        fprintf(fNote, "\nDELETE BY MARKS: \n");
    } else if (cEction == 5) {
        fprintf(fNote, "\nADD NEW ELEMENT: \n");
    }

    while (pssTemp != NULL) {
        fprintf(fNote, "%s ", pssTemp->m_sSurname);
        fprintf(fNote, "%s ", pssTemp->m_sName);
        fprintf(fNote, "%i.", pssTemp->m_nDate);
        fprintf(fNote, "%i.", pssTemp->m_nMonth);
        fprintf(fNote, "%i ", pssTemp->m_nYear);
        for (int i = 0; i < MARKS_NUM; i++) {
            fprintf(fNote, "%i ", pssTemp->m_aMarks[i]);
        }
        fprintf(fNote, "|%.*f\n",3 ,pssTemp->m_fRatingScore);

        pssTemp = pssTemp->m_pNext;
    }
    pssTemp = NULL;
    fclose(fNote);
}

//------------------------------------------------------------------------------
// A function for calculating the average age from a list.
// Takes the address of a pointer to the first element of the list. Returns 
// the value of the average age and sets the age of each student.
long CalculateMiddleAge(Sstudent **pHead) {
    Sstudent *pssTemp = *pHead;
    long lStaticAge = 1 + 31 * 11 + 12 * 31 * 22;
    long lMiddleAge = 0;
    int i = 0;
    while (pssTemp != NULL) {
        long lAgeInDays = pssTemp->m_nDate + 31 * (pssTemp->m_nMonth - 1) + 12 
            * 31 * (pssTemp->m_nYear - 2000);
        lAgeInDays = lStaticAge - lAgeInDays;
        pssTemp->m_lAge = lAgeInDays;
        lMiddleAge += lAgeInDays;
        pssTemp = pssTemp->m_pNext;
        i++;
    }
    lMiddleAge = lMiddleAge / i;
    pssTemp = NULL;
    return lMiddleAge;
}

// Deletes students whose age is smaller than a given value of middle age by list.
// Takes the address of a pointer to the first element of the list.
// Returns the value of the address of the pointer to the first element of 
// the list.
Sstudent *RemoveByAge(Sstudent **pssHead) {
    printf("\nRemoving by age: \n");

    long lMiddleAge = CalculateMiddleAge(pssHead);
    while ((*pssHead)->m_lAge < lMiddleAge && (*pssHead)->m_pNext != NULL) {
        *pssHead = (*pssHead)->m_pNext;
    }

    Sstudent *pssTemp = *pssHead;
    Sstudent *pssPrev = *pssHead;

    while (pssTemp != NULL) {
        if (pssTemp->m_lAge < lMiddleAge) {
            if (pssTemp->m_pNext == NULL) {
                if (pssPrev == pssTemp) {
                    *pssHead = NULL;
                    return *pssHead;
                }
                pssPrev->m_pNext = NULL;
                return *pssHead;
            } else {
                pssPrev->m_pNext = pssTemp->m_pNext;
                pssTemp = pssPrev;
            }
        }
        pssPrev = pssTemp;
        pssTemp = pssTemp->m_pNext;
    }
    pssTemp = NULL;
    pssPrev = NULL;
    return *pssHead;
}

//------------------------------------------------------------------------------
// Sorts student data by rating score in ascending order. Takes the address of 
// a pointer to the first element of the list. Returns the value of the address 
// of the pointer to the first element of the list.
Sstudent *SortList(Sstudent **pssHead) {
    printf("\nSORTING: \n");

    Sstudent *pssTemp = *pssHead;
    if (!pssTemp || !pssTemp->m_pNext)
        return pssTemp;

    Sstudent *pssSorted = NULL;

    while (pssTemp != NULL) {
        Sstudent *pPrev = pssTemp;
        Sstudent **ppTrail = &pssSorted;
        pssTemp = pssTemp->m_pNext;
        while (!(*ppTrail == NULL || pPrev->m_fRatingScore 
            < (*ppTrail)->m_fRatingScore)) {
            ppTrail = &(*ppTrail)->m_pNext;
        }
        pPrev->m_pNext = *ppTrail;
        *ppTrail = pPrev;
    }
    return pssSorted;
}

//------------------------------------------------------------------------------
// Adds new items to a list with already added items.Reading can do from a file
// and from the command line. The addition takes place at the end of the list.
// Takes the address of a pointer to the first element of the list.
void AddNewElement(Sstudent **pssHead) {

    int nReadType;
    char cReadType[MAX_SIZE];
    do {
        printf("Enter type of reading (1 from file, 2 from comand line): ");
        gets(cReadType);
        rewind(stdin);
        if ((cReadType[0] != '1' && cReadType[0] != '2') ||
            cReadType[1] != '\0') {
            printf("Value is incorrect!\n");
            continue;
        }
        nReadType = atoi(cReadType);
    } while ((cReadType[0] != '1' && cReadType[0] != '2') || cReadType[1] != '\0');

    if (nReadType == 1) {
        char sAddFileName[MAX_SIZE] = "addNew.txt";
        /*char sAddFileName[MAX_SIZE];
        do {
            printf("Specify the name of the reading file (name.txt): ");
            gets(sAddFileName);
            rewind(stdin);
            if (strcmp(sAddFileName, "addNew.txt") != 0) {
                printf("Invalid file name!\n");
            }
        } while (strcmp(sAddFileName, "addNew.txt") != 0);*/
        FILE* fNewElements = fopen(sAddFileName, "r");

        char cStudentsCnt[MAX_SIZE];
        int nNewElement;
        int nCheck1;
        int nCheck2;
        do {
            printf("How many students want you add? ");
            gets(cStudentsCnt);
            rewind(stdin);
            int temp = 0;
            nCheck1 = 0;
            nCheck2 = strlen(cStudentsCnt);
            for (int i = 0; i < nCheck2; i++) {
                if (isdigit(cStudentsCnt[i])) {
                    nCheck1++;
                }
            }
            if (nCheck1 == nCheck2) {
                temp = atoi(cStudentsCnt);
                if (temp > MAX_STUDENTS) {
                    printf("The set value is greater than the maximum: %s > %i\n", cStudentsCnt, MAX_STUDENTS);
                    nCheck1--;
                    continue;
                }
                else {
                    nNewElement = temp;
                }
            }
            else {
                printf("Set value incorrect!\n");
                continue;
            }
        } while (nCheck1 != nCheck2);

        int i = 0;
        while (i < nNewElement && !feof(fNewElements)) {
            Sstudent* pssNewNode = (Sstudent*)malloc(sizeof(Sstudent));

            int nDataCounter = 0;

            char sTempSurname[MAX_SIZE];
            char sTempName[MAX_SIZE];
            char sTempDate[MAX_SIZE], sTempMonth[MAX_SIZE], sTempYear[MAX_SIZE];
            char sTempMarks[MARKS_NUM][MAX_SIZE];

            //Surname

            //gets(sTempSurname);
            //rewind(stdin);
            fscanf(fNewElements, "%s", sTempSurname);
            int nErrors = 0;
            int nLenSurn = strlen(sTempSurname);
            if (nLenSurn >= 380) {
                printf("Line %i: Tape is empty\n", i + 1);
                //*pssHead = NULL;
                printf("\nRESULT: \n");
                return;
            }
            if (nLenSurn > MAX_LENTH) {
                printf("Line %i Surname: The input is too long (maximum - %i)\n", i + 1, MAX_LENTH);
                //*pssHead = NULL;
                printf("\nRESULT: \n");
                return;
            }
            for (int j = 0; j < nLenSurn; j++) {
                int nFlag = 0;
                if (isdigit(sTempSurname[j])) {
                    printf("Line %i Surname %i letter: ", i + 1, j + 1);
                    printf("Surname cannot contain numbers!\n");
                    nFlag = 1;
                    nErrors++;
                }
                if (!isalpha(sTempSurname[j])) {
                    if (nFlag != 1) {
                        printf("Line %i Surname %i letter: ", i + 1, j + 1);
                        printf("Surname cannot contain other symbols!\n");
                    }
                    nErrors++;
                }
                if (islower(sTempSurname[0])) {
                    sTempSurname[0] = toupper(sTempSurname[0]);
                }
            }
            if (nErrors <= 0) {
                //strcpy(pssNewNode->m_sSurname, sTempSurname);
                nDataCounter++;
            }
            else {
                //*pssHead = NULL;
                printf("\nRESULT: \n");
                return;
            }
            nErrors = 0;

            //Name

            //gets(sTempName);
            //rewind(stdin);
            fscanf(fNewElements, "%s", sTempName);
            int nLenName = strlen(sTempName);
            if (nLenName > MAX_LENTH) {
                printf("Line %i Name: The input is too long (maximum - %i)\n", i + 1, MAX_LENTH);
                //*pssHead = NULL;
                printf("\nRESULT: \n");
                return;
            }

            for (int j = 0; j < nLenName; j++) {
                int nFlag = 0;
                if (isdigit(sTempName[j])) {
                    printf("Line %i Name %i letter: ", i + 1, j + 1);
                    printf("Name cannot contain numbers!\n");
                    nFlag = 1;
                    nErrors++;
                }
                if (!isalpha(sTempName[j])) {
                    if (nFlag != 1) {
                        printf("Line %i Name %i letter: ", i + 1, j + 1);
                        printf("Name cannot contain other symbols!\n");
                    }
                    nErrors++;
                }
                if (islower(sTempName[0])) {
                    sTempName[0] = toupper(sTempName[0]);
                }
            }
            if (nErrors <= 0) {
                //strcpy(pssNewNode->m_sName, sTempName);
                nDataCounter++;
            }
            else {
                //*pssHead = NULL;
                printf("\nRESULT: \n");
                return;
            }
            nErrors = 0;

            //Year

            //gets(sTempYear);
            //rewind(stdin);
            fscanf(fNewElements, "%s", sTempYear);
            int nYear;
            int nLeapYear = 0;
            int nYearCheck1 = 0;
            int nYearCheck2 = strlen(sTempYear);
            for (int i = 0; i < nYearCheck2; i++) {
                if (isdigit(sTempYear[i])) {
                    nYearCheck1++;
                }
            }
            if (nYearCheck1 == nYearCheck2) {
                nYear = atoi(sTempYear);
                if (nYear >= 1950 && nYear <= 2100) {
                    nDataCounter++;
                    if (nYear % 4 == 0) {
                        if (nYear % 100 == 0 && nYear % 400 > 0) {
                            nLeapYear = 0;
                        }
                        else {
                            nLeapYear = 1;
                        }
                    }
                    else {
                        nLeapYear = 0;
                    }
                }
                else {
                    printf("Line %i Year: The value must be 1950-2015\n", i + 1);
                    //*pssHead = NULL;
                    printf("\nRESULT: \n");
                    return;
                }
            }
            else {
                printf("Line %i Year: Set value incorrect!\n", i + 1);
                //*pssHead = NULL;
                printf("\nRESULT: \n");
                return;
            }

            //Month

            //gets(sTempMonth);
            //rewind(stdin);
            fscanf(fNewElements, "%s", sTempMonth);
            int nMonth;
            int nMonthCheck1 = 0;
            int nMonthCheck2 = strlen(sTempMonth);
            for (int i = 0; i < nMonthCheck2; i++) {
                if (isdigit(sTempMonth[i])) {
                    nMonthCheck1++;
                }
            }
            if (nMonthCheck1 == nMonthCheck2) {
                nMonth = atoi(sTempMonth);
                if (nMonth > 0 && nMonth <= 12) {
                    nDataCounter++;
                }
                else {
                    printf("Line %i Month: The value must be 1-12\n", i + 1);
                    //*pssHead = NULL;
                    printf("\nRESULT: \n");
                    return;
                }
            }
            else {
                printf("Line %i Month: Set value incorrect!\n", i + 1);
                //*pssHead = NULL;
                printf("\nRESULT: \n");
                return;
            }

            //Date

            //gets(sTempDate);
            //rewind(stdin);
            fscanf(fNewElements, "%s", sTempDate);
            int nDate;
            int nDataCheck1 = 0;
            int nDataCheck2 = strlen(sTempDate);
            for (int i = 0; i < nDataCheck2; i++) {
                if (isdigit(sTempDate[i])) {
                    nDataCheck1++;
                }
            }
            if (nDataCheck1 == nDataCheck2) {
                nDate = atoi(sTempDate);
                if (nLeapYear == 0) {
                    if (nMonth == 2) {
                        if (nDate > 0 && nDate <= 28) { nDataCounter++; }
                        else {
                            printf("Line %i Date: The value must be 1-28\n", i + 1);
                            //*pssHead = NULL;
                            printf("\nRESULT: \n");
                            return;
                        }
                    }
                    else if (nMonth % 2 == 0) {
                        if (nDate > 0 && nDate <= 31) { nDataCounter++; }
                        else {
                            printf("Line %i Date: The value must be 1-31\n", i + 1);
                            //*pssHead = NULL;
                            printf("\nRESULT: \n");
                            return;
                        }
                        //pssNewNode->m_nDate = nDate;
                    }
                    else if (nMonth % 2 != 0) {
                        if (nDate > 0 && nDate <= 30) { nDataCounter++; }
                        else {
                            printf("Line %i Date: The value must be 1-30\n", i + 1);
                            //*pssHead = NULL;
                            printf("\nRESULT: \n");
                            return;
                        }
                    }
                }
                else if (nLeapYear == 1) {
                    if (nMonth == 2) {
                        if (nDate > 0 && nDate <= 27) { nDataCounter++; }
                        else {
                            printf("Line %i Date: The value must be 1-27\n", i + 1);
                            //*pssHead = NULL;
                            printf("\nRESULT: \n");
                            return;
                        }
                    }
                    else if (nMonth % 2 == 0) {
                        if (nDate > 0 && nDate <= 30) { nDataCounter++; }
                        else {
                            printf("Line %i Date: The value must be 1-30\n", i + 1);
                            //*pssHead = NULL;
                            printf("\nRESULT: \n");
                            return;
                        }
                        //pssNewNode->m_nDate = nDate;
                    }

                    else if (nMonth % 2 != 0) {
                        if (nDate > 0 && nDate <= 31) { nDataCounter++; }
                        else {
                            printf("Line %i Date: The value must be 1-31\n", i + 1);
                            //*pssHead = NULL;
                            printf("\nRESULT: \n");
                            return;
                        }
                    }
                }
            }
            else {
                printf("Line %i Date: Set value incorrect!\n", i + 1);
                //*pssHead = NULL;
                printf("\nRESULT: \n");
                return;
            }

            //Marks
            int nMark[MARKS_NUM];
            int nErrorsMarks = 0;
            for (int k = 0; k < MARKS_NUM; k++) {
                //gets(sTempMarks[i]);
                //rewind(stdin);
                fscanf(fNewElements, "%s", sTempMarks[k]);
                //int nMark;
                int nMarkCheck1 = 0;
                int nMarkCheck2 = strlen(sTempMarks[k]);
                for (int j = 0; j < nMarkCheck2; j++) {
                    if (isdigit(sTempMarks[k][j])) {
                        nMarkCheck1++;
                    }
                }
                if (nMarkCheck1 == nMarkCheck2) {
                    nMark[k] = atoi(sTempMarks[k]);
                    if (nMark[k] >= 1 && nMark[k] <= 5) {
                        //pssNewNode->m_aMarks[i] = nMark[i];
                        nDataCounter++;
                    }
                    else {
                        printf("Line %i Mark %i: The value must be 1-5\n", i + 1, k + 1);
                        nErrorsMarks++;
                        //*pssHead = NULL;
                        printf("\nRESULT: \n");
                        return;
                    }
                }
                else {
                    printf("Line %i Mark %i: Set value incorrect!\n", i + 1, k + 1);
                    nErrorsMarks++;
                    //*pssHead = NULL;
                    printf("\nRESULT: \n");
                    return;
                }
            }
            if (nErrorsMarks != 0) {
                //*pssHead = NULL;
                printf("\nRESULT: \n");
                return;
            }
            rewind(stdin);

            if (nDataCounter >= 10) {
                strcpy(pssNewNode->m_sSurname, sTempSurname);
                strcpy(pssNewNode->m_sName, sTempName);
                pssNewNode->m_nDate = nDate;
                pssNewNode->m_nMonth = nMonth;
                pssNewNode->m_nYear = nYear;
                for (int j = 0; j < MARKS_NUM; j++) {
                    pssNewNode->m_aMarks[j] = nMark[j];
                }
            }
            else {
                //*pssHead = NULL;
                printf("\nRESULT: \n");
                return;
            }

            pssNewNode->m_fRatingScore = 0;
            for (int j = 0; j < MARKS_NUM; j++) {
                pssNewNode->m_fRatingScore += pssNewNode->m_aMarks[j];
            }
            pssNewNode->m_fRatingScore = pssNewNode->m_fRatingScore / MARKS_NUM;

            Sstudent* pssTemp = *pssHead;

            if (*pssHead == NULL) {
                *pssHead = pssNewNode;
            }
            else {
                while (pssTemp->m_pNext != NULL) {
                    pssTemp = pssTemp->m_pNext;
                }
                pssTemp->m_pNext = pssNewNode;
            }
            pssNewNode->m_pNext = NULL;
            i++;
        }
        if (i < nNewElement) {
            printf("The file was not completely filled, all existing data was taken!\n");
        }
        fclose(fNewElements);
    }
    else if (nReadType == 2) {
        char cStudentsCnt[MAX_SIZE];
        int nNewElement;
        int nCheck1;
        int nCheck2;
        do {
            printf("How many students want you add? ");
            gets(cStudentsCnt);
            rewind(stdin);
            int temp = 0;
            nCheck1 = 0;
            nCheck2 = strlen(cStudentsCnt);
            for (int i = 0; i < nCheck2; i++) {
                if (isdigit(cStudentsCnt[i])) {
                    nCheck1++;
                }
            }
            if (nCheck1 == nCheck2) {
                temp = atoi(cStudentsCnt);
                if (temp > MAX_STUDENTS) {
                    printf("The set value is greater than the maximum: %s > %i\n", cStudentsCnt, MAX_STUDENTS);
                    nCheck1--;
                    continue;
                }
                else {
                    nNewElement = temp;
                }
            }
            else {
                printf("Set value incorrect!\n");
                continue;
            }
        } while (nCheck1 != nCheck2);

        int i = 0;
        while (i < nNewElement) {
            Sstudent* pssNewNode = (Sstudent*)malloc(sizeof(Sstudent));
            int nComplate = 0;
            do {
                printf("Enter data of %i student(Surname Name yyy mm dd m1 m2 m3 m4 m5): \n", i + 1);

                char sTempSurname[MAX_SIZE];
                char sTempName[MAX_SIZE];
                char sTempDate[MAX_SIZE], sTempMonth[MAX_SIZE], sTempYear[MAX_SIZE];
                char sTempMarks[MARKS_NUM][MAX_SIZE];

                //Surname

                //gets(sTempSurname);
                //rewind(stdin);
                scanf("%s", sTempSurname);
                int nErrors = 0;
                int nLenSurn = strlen(sTempSurname);
                if (nLenSurn > MAX_LENTH) {
                    printf("The input is too long (maximum - %i)\n", MAX_LENTH);
                    continue;
                }
                for (int i = 0; i < nLenSurn; i++) {
                    int nFlag = 0;
                    if (isdigit(sTempSurname[i])) {
                        printf("Surname %i letter: ", i + 1);
                        printf("Surname cannot contain numbers!\n");
                        nFlag = 1;
                        nErrors++;
                    }
                    if (!isalpha(sTempSurname[i])) {
                        if (nFlag != 1) {
                            printf("Surname %i letter: ", i + 1);
                            printf("Surname cannot contain other symbols!\n");
                        }
                        nErrors++;
                    }
                    if (islower(sTempSurname[0])) {
                        sTempSurname[0] = toupper(sTempSurname[0]);
                    }
                }
                if (nErrors <= 0) {
                    strcpy(pssNewNode->m_sSurname, sTempSurname);
                }
                else {
                    continue;
                }
                nErrors = 0;

                //Name

                //gets(sTempName);
                //rewind(stdin);
                scanf("%s", sTempName);
                int nLenName = strlen(sTempName);
                if (nLenName > MAX_LENTH) {
                    printf("The input is too long (maximum - %i)\n", MAX_LENTH);
                    continue;
                }

                for (int i = 0; i < nLenName; i++) {
                    int nFlag = 0;
                    if (isdigit(sTempName[i])) {
                        printf("Name %i letter: ", i + 1);
                        printf("Name cannot contain numbers!\n");
                        nFlag = 1;
                        nErrors++;
                    }
                    if (!isalpha(sTempName[i])) {
                        if (nFlag != 1) {
                            printf("Name %i letter: ", i + 1);
                            printf("Name cannot contain other symbols!\n");
                        }
                        nErrors++;
                    }
                    if (islower(sTempName[0])) {
                        sTempName[0] = toupper(sTempName[0]);
                    }
                }
                if (nErrors <= 0) {
                    strcpy(pssNewNode->m_sName, sTempName);
                }
                else {
                    continue;
                }
                nErrors = 0;

                //Year

                //gets(sTempYear);
                //rewind(stdin);
                scanf("%s", sTempYear);
                int nYear;
                int nLeapYear = 0;
                int nYearCheck1 = 0;
                int nYearCheck2 = strlen(sTempYear);
                for (int i = 0; i < nYearCheck2; i++) {
                    if (isdigit(sTempYear[i])) {
                        nYearCheck1++;
                    }
                }
                if (nYearCheck1 == nYearCheck2) {
                    nYear = atoi(sTempYear);
                    if (nYear >= 1950 && nYear <= 2100) {
                        if (nYear % 4 == 0) {
                            if (nYear % 100 == 0 && nYear % 400 > 0) {
                                nLeapYear = 0;
                            }
                            else {
                                nLeapYear = 1;
                            }
                        }
                        else {
                            nLeapYear = 0;
                        }
                    }
                    else {
                        printf("The value must be 1950-2015\n");
                        continue;
                    }
                }
                else {
                    printf("Set value incorrect!\n");
                    continue;
                }

                //Month

                //gets(sTempMonth);
                //rewind(stdin);
                scanf("%s", sTempMonth);
                int nMonth;
                int nMonthCheck1 = 0;
                int nMonthCheck2 = strlen(sTempMonth);
                for (int i = 0; i < nMonthCheck2; i++) {
                    if (isdigit(sTempMonth[i])) {
                        nMonthCheck1++;
                    }
                }
                if (nMonthCheck1 == nMonthCheck2) {
                    nMonth = atoi(sTempMonth);
                    if (nMonth > 0 && nMonth <= 12) {
                    }
                    else {
                        printf("The value must be 1-12\n");
                        continue;
                    }
                }
                else {
                    printf("Set value incorrect!\n");
                    continue;
                }

                //Date

                //gets(sTempDate);
                //rewind(stdin);
                scanf("%s", sTempDate);
                int nDate;
                int nDataCheck1 = 0;
                int nDataCheck2 = strlen(sTempDate);
                for (int i = 0; i < nDataCheck2; i++) {
                    if (isdigit(sTempDate[i])) {
                        nDataCheck1++;
                    }
                }
                if (nDataCheck1 == nDataCheck2) {
                    nDate = atoi(sTempDate);
                    if (nLeapYear == 0) {
                        if (nMonth == 2) {
                            if (nDate > 0 && nDate <= 28) {}
                            else {
                                printf("The value must be 1-28\n");
                                continue;
                            }
                        }
                        else if (nMonth % 2 == 0) {
                            if (nDate > 0 && nDate <= 31) {}
                            else {
                                printf("The value must be 1-31\n");
                                continue;
                            }
                            //pssNewNode->m_nDate = nDate;
                        }
                        else if (nMonth % 2 != 0) {
                            if (nDate > 0 && nDate <= 30) {}
                            else {
                                printf("The value must be 1-30\n");
                                continue;
                            }
                        }
                    }
                    else if (nLeapYear == 1){
                        if (nMonth == 2) {
                            if (nDate > 0 && nDate <= 27) {}
                            else {
                                printf("The value must be 1-27\n");
                                continue;
                            }
                        }
                        else if (nMonth % 2 == 0) {
                            if (nDate > 0 && nDate <= 30) {}
                            else {
                                printf("The value must be 1-30\n");
                                continue;
                            }
                            //pssNewNode->m_nDate = nDate;
                        }
                        else if (nMonth % 2 != 0) {
                            if (nDate > 0 && nDate <= 31) {}
                            else {
                                printf("The value must be 1-31\n");
                                continue;
                            }
                        }
                    }
                }
                else {
                    printf("Set value incorrect!\n");
                    continue;
                }


                pssNewNode->m_nDate = nDate;
                pssNewNode->m_nMonth = nMonth;
                pssNewNode->m_nYear = nYear;

                //Marks
                int nErrorsMarks = 0;
                for (int i = 0; i < MARKS_NUM; i++) {
                    //gets(sTempMarks[i]);
                    //rewind(stdin);
                    scanf("%s", sTempMarks[i]);
                    int nMark;
                    int nMarkCheck1 = 0;
                    int nMarkCheck2 = strlen(sTempMarks[i]);
                    for (int j = 0; j < nMarkCheck2; j++) {
                        if (isdigit(sTempMarks[i][j])) {
                            nMarkCheck1++;
                        }
                    }
                    if (nMarkCheck1 == nMarkCheck2) {
                        nMark = atoi(sTempMarks[i]);
                        if (nMark >= 1 && nMark <= 5) {
                            pssNewNode->m_aMarks[i] = nMark;
                        }
                        else {
                            printf("The value must be 1-5\n");
                            nErrorsMarks++;
                            break;
                        }
                    }
                    else {
                        printf("Set value incorrect!\n");
                        nErrorsMarks++;
                        break;
                    }
                }
                if (nErrorsMarks != 0) {
                    continue;
                }
                nComplate = 1;
                rewind(stdin);
            } while (nComplate <= 0);

            pssNewNode->m_fRatingScore = 0;
            for (int j = 0; j < MARKS_NUM; j++) {
                pssNewNode->m_fRatingScore += pssNewNode->m_aMarks[j];
            }
            pssNewNode->m_fRatingScore = pssNewNode->m_fRatingScore / MARKS_NUM;

            Sstudent* pssTemp = *pssHead;

            if (*pssHead == NULL) {
                *pssHead = pssNewNode;
            }
            else {
                while (pssTemp->m_pNext != NULL) {
                    pssTemp = pssTemp->m_pNext;
                }
                pssTemp->m_pNext = pssNewNode;
            }
            pssNewNode->m_pNext = NULL;
            i++;
        }
    }
    printf("\nRESULT: \n");
}


//------------------------------------------------------------------------------
// Removes students by grade number for a specific exam.Takes the address of a 
// pointer to the first element of the list. Returns the value of the address 
// of the pointer to the first element of the list.
Sstudent *RemoveByMarks(Sstudent **pssHead) {
    printf("\nRemoving by marks: \n");

    char sMarkForDel[MAX_SIZE];
    int nMarkForDel;

    int nConf1 = 0;
    do {
        printf("\nEnter mark: \n");
        gets(sMarkForDel);
        rewind(stdin);
        int nMarkDelCheck1 = 0;
        int nMarkDelCheck2 = strlen(sMarkForDel);
        for (int i = 0; i < nMarkDelCheck2; i++) {
            if (isdigit(sMarkForDel[i])) {
                nMarkDelCheck1++;
            }
        }
        if (nMarkDelCheck1 == nMarkDelCheck2) {
            nMarkForDel = atoi(sMarkForDel);
            if (nMarkForDel >= 1 && nMarkForDel <= 5) {

            }
            else {
                printf("The value must be 1-5\n");
                continue;
            }
        }
        else {
            printf("Set value incorrect!\n");
            continue;
        }
        nConf1 = 1;
    } while (nConf1 == 0);

    char sPosMarkForDel[MAX_SIZE];
    int nPosMarkForDel;

    int nConf2 = 0;
    do {
        printf("\nEnter position of mark: \n");
        gets(sPosMarkForDel);
        rewind(stdin);
        int nPosDelCheck1 = 0;
        int nPosDelCheck2 = strlen(sPosMarkForDel);
        for (int i = 0; i < nPosDelCheck2; i++) {
            if (isdigit(sPosMarkForDel[i])) {
                nPosDelCheck1++;
            }
        }
        if (nPosDelCheck1 == nPosDelCheck2) {
            nPosMarkForDel = atoi(sPosMarkForDel);
            if (nPosMarkForDel >= 1 && nPosMarkForDel <= 5) {

            }
            else {
                printf("The value must be 1-5\n");
                continue;
            }
        }
        else {
            printf("Set value incorrect!\n");
            continue;
        }
        nConf2 = 1;
    } while (nConf2 == 0);

    nPosMarkForDel--;

    while ((*pssHead)->m_aMarks[nPosMarkForDel] == nMarkForDel && 
        (*pssHead)->m_pNext != NULL) {
        *pssHead = (*pssHead)->m_pNext;
    }

    Sstudent *pssTemp = *pssHead;
    Sstudent *pssPrev = *pssHead;

    while (pssTemp != NULL) {
        if (pssTemp->m_aMarks[nPosMarkForDel] == nMarkForDel) {
            if (pssTemp->m_pNext == NULL) {
                if (pssPrev == pssTemp) {
                    *pssHead = NULL;
                    return *pssHead;
                }
                pssPrev->m_pNext = NULL;
                return *pssHead;
            } else {
                pssPrev->m_pNext = pssTemp->m_pNext;
                pssTemp = pssPrev;
            }
        }
        pssPrev = pssTemp;
        pssTemp = pssTemp->m_pNext;
    }
    pssPrev = NULL;
    pssTemp = NULL;
    return *pssHead;
}

//------------------------------------------------------------------------------
// Clear the list of students. Takes the address of a pointer to the first 
// element of the list.
void ClearList(Sstudent **pssHead) {
    Sstudent *pssTemp = *pssHead;
    Sstudent *pssNext;

    while (pssTemp != NULL) {
        pssNext = pssTemp->m_pNext;
        free(pssTemp);
        pssTemp = pssNext;
    }
    *pssHead = NULL;
}

//------------------------------------------------------------------------------
// The main function. Used to select functions.
int main() {
    setlocale(LC_CTYPE, "ukr");
    printf("START\n");

    char sNoteFileName[MAX_SIZE] = "result.txt";

    /*char sNoteFileName[MAX_SIZE];
    do {
        printf("Specify the name of the saving file (name.txt): ");
        gets(sNoteFileName);
        rewind(stdin);
        if (strcmp(sNoteFileName, "result.txt") != 0) {
            printf("Invalid file name!\n");
        }
    } while (strcmp(sNoteFileName, "result.txt") != 0);*/

    FILE *fNote = fopen(sNoteFileName, "wb");
    fprintf(fNote, "START\n");
    fclose(fNote);

    Sstudent *pssHead = NULL;
    char sConfirmation[MAX_SIZE];
    do {
        rewind(stdin);
        char cEction[MAX_SIZE];
        printf("\nSelect an action: \n");
        printf("\n1 Reading data \n");
        printf("2 Sorting by increasing rating score \n");
        printf("3 Removal of students younger than middle age \n");
        printf("4 Removal of students based on exam grades \n");
        printf("5 Add new elements \n");
        printf("6 Clear the list \n");
        printf("0 Exit the program\n");
        printf("\nEnter number: \n");

        gets(cEction);
        rewind(stdin);

        if (cEction[0] == '1' && cEction[1] == '\0') {
            ReadingDataOfStudents(&pssHead);
            PrintList(&pssHead);
            NoteList(&pssHead, atoi(cEction), sNoteFileName);
        }

        if (cEction[0] == '2' && cEction[1] == '\0' && pssHead != NULL) {
            pssHead = SortList(&pssHead);
            PrintList(&pssHead);
            NoteList(&pssHead, atoi(cEction), sNoteFileName);
        }
        else if (cEction[0] == '2' && cEction[1] == '\0' && pssHead == NULL) {
            printf("No data found to sort!\n\n");
        }

        if (cEction[0] == '3' && cEction[1] == '\0' && pssHead != NULL) {
            RemoveByAge(&pssHead);
            PrintList(&pssHead);
            NoteList(&pssHead, atoi(cEction), sNoteFileName);
        }
        else if (cEction[0] == '3' && cEction[1] == '\0' && pssHead == NULL) {
            printf("No data found to removal!\n\n");
        }

        if (cEction[0] == '4' && cEction[1] == '\0' && pssHead != NULL) {
            RemoveByMarks(&pssHead);
            PrintList(&pssHead);
            NoteList(&pssHead, atoi(cEction), sNoteFileName);
        }
        else if (cEction[0] == '4' && cEction[1] == '\0' && pssHead == NULL) {
            printf("No data found to removal!\n\n");
        }

        if (cEction[0] == '5' && cEction[1] == '\0') {
            AddNewElement(&pssHead);
            PrintList(&pssHead);
            NoteList(&pssHead, atoi(cEction), sNoteFileName);
        }

        if (cEction[0] == '6' && cEction[1] == '\0' && pssHead != NULL) {
            char sConfirmClearEction[MAX_SIZE];
            do {
                printf("Do you realy want to clear the list (0 - no, 1 - yes)?\n");
                gets(sConfirmClearEction);
                rewind(stdin);
                if ((sConfirmClearEction[0] != '0' && sConfirmClearEction[0] != '1') ||
                    sConfirmClearEction[1] != '\0') {
                    printf("Value is incorrect!\n");
                    continue;
                }
                if (sConfirmClearEction[0] == '0' &&
                    sConfirmClearEction[1] == '\0') {
                    break;
                }
            } while (sConfirmClearEction[0] != '1' ||
                sConfirmClearEction[1] != '\0');

            if (sConfirmClearEction[0] == '0' && sConfirmClearEction[1] == '\0') {
                PrintList(&pssHead);
            }
            else if (sConfirmClearEction[0] == '1' && sConfirmClearEction[1] == '\0') {
                ClearList(&pssHead);
                PrintList(&pssHead);
                NoteList(&pssHead, atoi(cEction), sNoteFileName);
            }
        }
        else if (cEction[0] == '6' && cEction[1] == '\0' && pssHead == NULL) {
            printf("The list is empty!\n\n");
        }

        if (cEction[0] == '0' && cEction[1] == '\0') {
            do {
                printf("Do you realy want to close the program(0 - no, 1 - yes)?\n");
                gets(sConfirmation);
                rewind(stdin);
               if ((sConfirmation[0] != '0' && sConfirmation[0] != '1') ||
                    sConfirmation[1] != '\0') {
                    printf("Value is incorrect!\n");
                    continue;
                }
                if (sConfirmation[0] == '0' &&
                    sConfirmation[1] == '\0') {
                    break;
                }
            } while (sConfirmation[0] != '1' ||
                sConfirmation[1] != '\0');
        }

        if (cEction[1] != '\0') {
            printf("The value is incorrect!\n");
            continue;
        }
        if (cEction[0] != '0' && cEction[0] != '1' && cEction[0] != '2' &&
            cEction[0] != '3' && cEction[0] != '4' && cEction[0] != '5' && 
            cEction[0] != '6' && cEction[1] == '\0') {
            printf("No such action exists!\n");
            continue;
        }
    } while (sConfirmation[0] != '1' && sConfirmation[0] != '\0');

    printf("\nEnd of work!\n");
    return 0;
}