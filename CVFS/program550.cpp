#include<stdio.h>
#include<stdlib.h>


// Conditional pre-processing
int main()
{

    #ifdef _WIN32
      system("cls");
    #else
      system("clear");
    #endif
    return 0;
}