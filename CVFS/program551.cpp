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

#define REGULARFILE 1
#define SPECIALFILE 2

////////////////////////////////////////////////////////////////////////////////////////////////
//
//  User Defined Macros for error handlinig
//
////////////////////////////////////////////////////////////////////////////////////////////////

#define ERR_INVALIDE_PARAMETER -1

#define ERR_NO_INODES -2

#define ERR_FILE_ALREADY_EXIST -3
#define ERR_FILE_NOT_EXIST -4

#define ERR_MAX_FILES_OPEN -8

#define ERR_PERMISSION_DENIDE -5

#define ERR_INSUFFICIENT_SPACE -6
#define ERR_INSUFFICIENT_DATA -7

////////////////////////////////////////////////////////////////////////////////////////////////
//
//  User Defined Structures
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
    int FileType;
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

// Global Varible decalration
BootBlock bootobj;
SuperBlock superobj;
UAREA uareaobj;

PINODE head = NULL;

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
        newn->FileType = 0;
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

//////////////////////////////////////////////////////////////////////////////////////////////
//
//      Function Name :     DisplayHelp
//      Description :        it is use to display the help page
//      Author :            Rushikesh Baban Dhande
//      Date :              14/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////////////

void DisplayHelp()
{
    printf("------------------------------------------------------------\n");
    printf("----------------- Rushikesh CVFS Help Page ----------------\n");
    printf("------------------------------------------------------------\n");

    printf("man    : It is used to Display manual page\n");
    printf("clear  : It is used to clear the terminal\n");
    printf("creat  : It is used to create new file\n");
    printf("write  : It is used to write the data into the file\n");
    printf("read   : It is used to read the data from the file\n");
    printf("stat   : It is used to display statistical information\n");
    printf("unlink : It is used to delete the file\n");
    printf("exit   : It is used to terminate Rushikesh CVFS\n");

    printf("------------------------------------------------------------\n");
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//      Function Name :     ManPageDisplay
//      Description :       It is use to display man page
//      Author :            Rushikesh Baban Dhande
//      Date :              14/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////////////

void ManPageDisplay(char Name[])
{
    if (strcmp("ls", Name) == 0)
    {
        printf("About : It is used to list the names of all files\n");
        printf("Usage : ls\n");
    }
    else if (strcmp("man", Name) == 0)
    {
        printf("About : It is used to display manual page\n");
        printf("Usage : man command_name\n");
        printf("command_name : It is the name of command");
    }
    else if (strcmp("exit", Name) == 0)
    {
        printf("About : It is used to terminate the shell\n");
        printf("Usage : exit\n");
    }
    else if (strcmp("clear", Name) == 0)
    {
        printf("About : It is used to clear the shell\n");
        printf("Usage : clear\n");
    }
    else
    {
        printf("No manual entry for %s\n", Name);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////
//
//      Function Name :     IsFileExist
//      Description :       It is use to check wether file alredy exist or not
//      input:              It accepts file name
//      output:             It returns true or false
//      Author :            Rushikesh Baban Dhande
//      Date :              16/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////////////

bool IsFileExist(
    char *name // File
)
{
    PINODE temp = head;
    bool bFlag = false;

    while (temp != NULL)
    {
        if ((strcmp(name, temp->FileName)) == 0 && (temp->FileType == REGULARFILE))
        {
            bFlag = true;
            break;
        }
        temp = temp->next;
    }
    return bFlag;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//      Function Name :     CreateFile
//      Description :       It is use to create new regular file
//      input:              It accepts file name and permissions
//      output:             It returns the file descripter
//      Author :            Rushikesh Baban Dhande
//      Date :              16/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////////////

int CreateFile(
    char *name,    // Name of new file
    int permission // Permission of that file
)
{
    PINODE temp = head;
    int i = 0;

    printf("Total number of inodes remining : %d\n", superobj.FreeInodes);

    // If name is missing
    if (name == NULL)
    {
        return ERR_INVALIDE_PARAMETER;
    }

    // If the permission value is wrong
    // permission -> 1 -> READ
    // permission -> 2 -> WRITE
    // permission -> 3 -> READ + WRITE
    if (permission < 1 || permission > 3)
    {
        return ERR_INVALIDE_PARAMETER;
    }

    // If the inodes are full
    if (superobj.FreeInodes == 0)
    {
        return ERR_NO_INODES;
    }

    // If file is already present
    if (IsFileExist(name) == true)
    {
        return ERR_FILE_ALREADY_EXIST;
    }

    // Search empty Inode
    while (temp != NULL)
    {
        if (temp->FileType == 0)
        {
            break;
        }
        temp = temp->next;
    }
    
    // No node avaliable
    if (temp == NULL)
    {
        printf("There is no inode\n");
        return ERR_NO_INODES;
    }

    // Search for empty UFDT entry
    // Note 0 1 2 are reserved
    for (i = 3; i < MAXOPENFILES; i++)
    {
        if (uareaobj.UFDT[i] == NULL)
        {
            break;
        }
    }

    // UFDT is Full
    if (i == MAXOPENFILES)
    {
        return ERR_MAX_FILES_OPEN;
    }

    // Allocate ememory for file table
    uareaobj.UFDT[i] = (PFILETABLE)malloc(sizeof(FILETABLE));

    // Initialise file table
    uareaobj.UFDT[i]->ReadOffset = 0;
    uareaobj.UFDT[i]->WriteOffset = 0;
    uareaobj.UFDT[i]->Mode = permission;

    // Connect file table with Inode
    uareaobj.UFDT[i]->ptrinode = temp;

    // Iniialise elements of Inode
    strcpy(uareaobj.UFDT[i]->ptrinode->FileName, name);
    uareaobj.UFDT[i]->ptrinode->FileSize = MAXFILESIZE;
    uareaobj.UFDT[i]->ptrinode->ActualFileSize = 0;
    uareaobj.UFDT[i]->ptrinode->FileType = REGULARFILE;
    uareaobj.UFDT[i]->ptrinode->ReferenceCount = 1;
    uareaobj.UFDT[i]->ptrinode->Permission = permission;

    // Allocate ememory for files data
    uareaobj.UFDT[i]->ptrinode->Buffer = (char *)malloc(MAXFILESIZE); // 50Byte memory allocate

    superobj.FreeInodes--;

    return i; // File descriptor
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
    char Command[5][20] = {{'\0'}};
    int iCount = 0;
    int iRet = 0;

    StartAuxillaryDataInitialisation();

    printf("------------------------------------------------------------\n");
    printf("----------- Rushikesh CVFS Started Successfully -----------\n");
    printf("------------------------------------------------------------\n");

    // Infinite Listening Shell
    while (1)
    {
        fflush(stdin);

        strcpy(str, "");

        printf("\nRushikesh CVFS : > ");
        fgets(str, sizeof(str), stdin);

        iCount = sscanf(str, "%s %s %s %s %s ", Command[0], Command[1], Command[2], Command[3], Command[4]);

        fflush(stdin);

        if (iCount == 1)
        {
            // Rushikesh CVFS : > exit
            if (strcmp("exit", Command[0]) == 0)
            {
                printf("Thanku for using Rushikesh CVFS\n");
                printf("Deallocating all the allocated resourcess\n");

                break;
            }
            // Rushikesh CVFS : > ls
            else if (strcmp("ls", Command[0]) == 0)
            {
                printf("Inside ls\n");
            }
            // Rushikesh CVFS : > help
            else if (strcmp("help", Command[0]) == 0)
            {
                DisplayHelp();
            }

        } // End of else if 1
        else if (iCount == 2)
        {
            // Rushikesh CVFS : > man ls
            if (strcmp("man", Command[0]) == 0)
            {
                ManPageDisplay(Command[1]);
            }

        } // End of else if 2
        else if (iCount == 3)
        {
            // Rushikesh CVFS : > creat Ganesh.txt 3
            if (strcmp("creat", Command[0]) == 0)
            {

                iRet = CreateFile(Command[1], atoi(Command[2]));

                if (iRet == ERR_INVALIDE_PARAMETER)
                {
                    printf("Error : Unable to create the file as parameters are invalide..\n");
                    printf("Please refer the man page\n");
                }

                if (iRet == ERR_NO_INODES)
                {
                    printf("Error : Unable to create file as there are no inode\n");
                }

                if (iRet == ERR_FILE_ALREADY_EXIST)
                {
                    printf("Error : Unable to create file beacause the file is already present\n");
                }
                if (iRet == ERR_MAX_FILES_OPEN)
                {
                    printf("Error : Unable to create file\n");
                    printf("Max open file limit reached\n");
                }
                printf("File gets successfully created with FD %d\n",iRet);
            }
        } // End of else if 3
        else if (iCount == 4)
        {

        } // End of else if 4
        // Rushikesh CVFS : > clear
        else if (strcmp("clear", Command[0]) == 0)
        {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
        }
        else
        {
            printf("Command not fount...!\n");
            printf("Plase refer help option to get more information \n");
        } // End of else

    } // End of while

    return 0;
} // End of main