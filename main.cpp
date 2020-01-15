#include <cstdlib>
#include "stdio.h"
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>

using namespace std;

extern int errno ;

int MAX = 9000;

int displayNameOfFile = 0;

int maxBufLines = 10;

int fileNameIndex = 0;

void proceedFile(int descIn, int descOut, char* nameOfFile  ) {    
    int countOfLines = 0;
    
    if(descIn >= 0) {
        write (descOut, "File opened; \n", 14);
        printf("File opened;");
        printf("\n");
        if(displayNameOfFile == 1 && fileNameIndex != 0) {
        write (descOut, "==>", 3);
        write (descOut, nameOfFile, 5);
        write (descOut, "<==\n", 4);
        printf("==> %s <== \n", nameOfFile);
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
    int blockDisplayNameOfFile = 0;
    int enableStdIn = 0;
    mode_t mode = S_IRUSR | S_IWUSR;
    int flags = O_WRONLY | O_CREAT;
    int fr = open ("output.txt", flags, mode);
    printf("Lab2 Bukhtiarov P3418 ");
    for(int i =1; i < argc; i++) { // ignore 0 argument whith exec path
    printf("Argument %d: %s\n", i, argv[i]);
    if(strcmp(argv[i], "-n") == 0) {
        if(*argv[i+1] >= '0' && *argv[i+1] <= '9' ) {
        maxBufLines = atoi(argv[i+1]);
        }
        else {
        fprintf(stderr, "Not a digit passed for '-n' argument \n");
        write (fr, "Not a digit passed for '-n' argument \n", 38);
        }
        i++;
        continue;
    }
    if(strcmp(argv[i], "-c") == 0) {
        if(*argv[i+1] >= '0' && *argv[i+1] <= '9' ) {
        MAX = atoi(argv[i+1]);
        }
        else {
        fprintf(stderr, "Not a digit passed for '-c' argument \n");
        write (fr, "Not a digit passed for '-c' argument \n", 38);
        }
        i++;
        continue;
    }
    if(strcmp(argv[i], "-v") == 0) {
        displayNameOfFile = 1;
        continue;
    }
    if(strcmp(argv[i], "-q") == 0) {
        blockDisplayNameOfFile = 1;
        continue;
    }
    
    if(strcmp(argv[i], "-") == 0) {
        enableStdIn = 1;
        continue;
    }
   
    if(strcmp(argv[i], "-n") && strcmp(argv[i], "-c") && strcmp(argv[i], "-v") && strcmp(argv[i], "-q") && (strstr(argv[i], ".txt") == NULL)) {
    fprintf(stderr, "Wrong argument is passed \n");
    }
    }
    if(enableStdIn == 0) {
    
    char cwd[90];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("Current working dir: %s\n", cwd);
    }
    
    int fileIndex[10];
    while(strstr(argv[fileNameIndex], ".txt") == NULL) {
    fileNameIndex++;
    }
    int z = 0;
    fileIndex[z] = fileNameIndex;
    while(strstr(argv[fileNameIndex], ".txt") != NULL) {
    fileIndex[z] = fileNameIndex;
    fileNameIndex++;
    if(fileNameIndex >= argc ) {
        break; 
    }
    if(blockDisplayNameOfFile != 1) {
    displayNameOfFile = 1;
    }
    z++;
    }
    
    for(int i = 0; i <= z; ++ i) {
    int fd = open (argv[fileIndex[i]], O_RDONLY);
    if (fd < 0)
    {
        //fprintf(stderr, "Value of errno: %d\n", errno);
        fprintf(stderr, "Error opening file: %s\n", strerror( errno ));
        write (fr, "Error opening file \n", 20);
        write (fr, strerror( errno ), 25);
        
    }
    proceedFile(fd, fr, argv[fileIndex[i]] );
    close (fd);
    }
    close (fr);
    }
    else {
    char buffer[MAX];
    int lines = 0;

    int iter = 0;
    while (fgets(buffer, MAX+1, stdin) && buffer[0] != '\n') {
        int l = strlen(buffer);
        if('\n'==buffer[l-1])
        {
            lines++;
        }

        write (fr, &buffer, strlen(buffer));
        
        if(lines >= maxBufLines) {
            break;
        }
        if( MAX != 9000) {
            break;
        }

    }
    }
    return 0;
}
