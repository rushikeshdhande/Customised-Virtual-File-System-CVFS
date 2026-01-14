////////////////////////////////////////////////////////////////////////////////////////////////
//  Header File Inclusion
////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
/* #include<unistd.h> */
#include <stdbool.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////////////////////
//
//  User Defined Macros
//
////////////////////////////////////////////////////////////////////////////////////////////////

// Maximum file size that we allow in the project
#define MAXFILESIZE 50

#define MAXOPENFILES 20

#define MAXINODE 5

#define READ 1
#define WRITE 2
#define EXECUTE 4

#define START 0
#define CURRENT 1
#define END 2

#define EXECUTE_SUCCESS 0

////////////////////////////////////////////////////////////////////////////////////////////////
//
//  User Defined Function
//
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Structure name :     BootBock
//  Description :        Holds the information to boot the OS
//
////////////////////////////////////////////////////////////////////////////////////////////////

struct BootBlock
{
    char Information[100];
};

////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Structure name :     SuperBlock
//  Description :        Holds the information about the file system
//
////////////////////////////////////////////////////////////////////////////////////////////////

struct SuperBlock
{
    int TotalInodes;
    int FreeInodes;
};

////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Structure name :     Inode
//  Description :        Holds the information about the file
//
////////////////////////////////////////////////////////////////////////////////////////////////

#pragma pack(1)
struct Inode
{
    char FileName[20];
    int InodeNumber;
    int FileSize;
    int ActualFileSize;
    int ReferenceCount;
    int Permission;
    char *Buffer;
    struct Inode *next;
};

typedef struct Inode INODE;
typedef struct Inode *PINODE;
typedef struct Inode **PPINODE;

////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Structure name :     FileTable
//  Description :        Holds the information about opened file
//
////////////////////////////////////////////////////////////////////////////////////////////////

struct FileTable
{
    int ReadOffset;
    int WriteOffset;
    int Mode;
    PINODE ptrinode;
};

typedef FileTable FILETABLE;
typedef FileTable *PFILETABLE;

////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Structure name :     UAREA
//  Description :        Holds the information about process file
//
////////////////////////////////////////////////////////////////////////////////////////////////

struct UAREA
{
    char ProcessName[20];
    PFILETABLE UFDT[MAXOPENFILES];
};

////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Global variable or objects used in the project
//
////////////////////////////////////////////////////////////////////////////////////////////////

BootBlock bootobj;
SuperBlock superobj;
UAREA uareaobj;

PINODE head = NULL; // Global Varible decalration

//////////////////////////////////////////////////////////////////////////////////////////////
//
//      Function Name :     InitialiseUAREA
//      Description :       It is use to initialise uarea members
//      Author :            Rushikesh Baban Dhande
//      Date :              13/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////////////
void InitialiseUAREA()
{
    strcpy(uareaobj.ProcessName, "Myexe");

    int i = 0;
    for (i = 0; i < MAXOPENFILES; i++)
    {
        uareaobj.UFDT[i] = NULL;
    }
    printf("Rushikesh CVFS : UAREA gets initialise Successfully...\n");
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//      Function Name :     InitialiseSuperBlock
//      Description :       It is use to initialise Super Block members
//      Author :            Rushikesh Baban Dhande
//      Date :              13/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////////////

void InitialiseSuperBlock()
{
    superobj.TotalInodes = MAXINODE;
    superobj.FreeInodes = MAXINODE;

    printf("Rushikesh CVFS : Super block gets initialise Successfully...\n");
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//      Function Name :     CreateDILB
//      Description :       It is use to create linked list of inodes
//      Author :            Rushikesh Baban Dhande
//      Date :              13/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////////////

void CreateDILB()
{
    int i = 1;
    PINODE newn = NULL;
    PINODE temp = head;

    for (i = 1; i <= MAXINODE; i++)
    {
        newn = (PINODE)malloc(sizeof(INODE));

        strcpy(newn->FileName, "\0");
        newn->InodeNumber = i;
        newn->FileSize = 0;
        newn->ActualFileSize = 0;
        newn->ReferenceCount = 0;
        newn->Permission = 0;
        newn->Buffer = NULL;
        newn->next = NULL;

        if (temp == NULL) // LL is empty
        {
            head = newn;
            temp = head;
        }
        else // LL contains atlist 1 node
        {
            temp->next = newn;
            temp = temp->next;
        }
    }
    printf("Rushikesh CVFS : DILB created successfully...\n");
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//      Function Name :     StartAuxillaryDataInitialisation
//      Description :       It is use to call all such function which are
//                          used to initialise auxillary data
//      Author :            Rushikesh Baban Dhande
//      Date :              13/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////////////

void StartAuxillaryDataInitialisation()
{
    strcpy(bootobj.Information, "Booting process of Rushikesh CVFS is done");

    printf("%s\n", bootobj.Information);

    InitialiseSuperBlock();

    CreateDILB();

    InitialiseUAREA();

    printf("Rushikesh CVFS : Auxillary data initialise successfully...\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//     Entry point function of the project
//     Execution start from main function
//
////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    char str[80] = {'\0'};
    char Command[4][20];
    int iCount = 0;

    StartAuxillaryDataInitialisation();

    printf("------------------------------------------------------------\n");
    printf("----------- Rushikesh CVFS Started Successfully -----------\n");
    printf("------------------------------------------------------------\n");

    // infinite listing loop
    while (1)
    {
        fflush(stdin);

        strcpy(str, "");

        printf("\n Rushikesh CVFS : >");
        fgets(str, sizeof(str), stdin);
    
        
    }

    return 0;
}