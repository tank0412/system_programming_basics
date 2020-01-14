#include <cstdlib>
#include "stdio.h"
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>

using namespace std;

int MAX = 9000;

int displayNameOfFile = 0;

int maxBufLines = 10;

int fileNameIndex = 0;

void proceedFile(int descIn, int descOut, char** argv  ) {    
    char buffer[MAX];
    int countOfLines = 0;
    
    if(descIn >= 0) {
        write (descOut, "File opened; \n", 14);
        printf("File opened;");
        printf("\n");
        if(displayNameOfFile == 1 && fileNameIndex != 0) {
        write (descOut, "==>", 3);
        write (descOut, argv[fileNameIndex], 5);
        write (descOut, "<==\n", 4);
        printf("==> %s <== \n", argv[fileNameIndex]);
        }
        
        ssize_t ret;
	char ch;
        int length = 0;
        while ((ret = read (descIn, &ch, 1)) > 0)
	{
        length++;
        if(length == MAX) {
           putchar (ch);
           write (descOut, &ch, 1);
            //printf("%d > %d \n", length, MAX);
            break;
            }
            if(ch == '\n' ) {
            if(strcmp(&ch, "") != 0) {
            countOfLines++;
            if(countOfLines >= maxBufLines) {
                break;
            }
        }
        }
        putchar (ch);
        write (descOut, &ch, 1);
	}
    }
}

int main(int argc, char** argv) {
    printf("Lab2 Bukhtiarov P3418 ");
    for(int i =1; i < argc; i++) { // ignore 0 argument whith exec path
    printf("Argument %d: %s\n", i, argv[i]);
    if(strcmp(argv[i], "-n") == 0) {
        if(*argv[i+1] >= '0' && *argv[i+1] <= '9' ) {
        maxBufLines = atoi(argv[i+1]);
        }
    }
    if(strcmp(argv[i], "-c") == 0) {
        if(*argv[i+1] >= '0' && *argv[i+1] <= '9' ) {
        MAX = atoi(argv[i+1]);
        }
    }
        if(strcmp(argv[i], "-v") == 0) {
            displayNameOfFile = 1;
        }
    }
    char cwd[90];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("Current working dir: %s\n", cwd);
    }
    
    char* fullPath;
    char slash[2] = {'/'};
    while(strstr(argv[fileNameIndex], ".txt") == NULL) {
    fileNameIndex++;
    }
    fullPath = (char*)malloc(strlen(cwd)+strlen(argv[fileNameIndex]) + strlen(slash)); /* make space for the new string (should check the return value ...) */
    strcpy(fullPath, cwd); /* copy name into the new var */
    strcat(fullPath, slash);
    strcat(fullPath, argv[fileNameIndex]); /* add the extension */
    
    /*
    printf(slash);
    printf("\n");
    printf(fullPath);
    printf("\n");
      */
    
    int fd = open (argv[fileNameIndex], O_RDONLY);
    int fr = open ("output.txt", O_WRONLY | O_CREAT);
    
    proceedFile(fd, fr, argv);
    
    //printf("%d",countOfLines / 2);
    printf("\n");
    //printf("%s", buffer);
    //fclose(fp);
    close (fd);
    close (fr);
    return 0;
}

