#include <cstdlib>
#include "stdio.h"
#include <string.h>
#include <unistd.h>

using namespace std;

int MAX = 900;

int main(int argc, char** argv) {
    FILE *fp;
    printf("Lab2 Bukhtiarov P3418 ");
    for(int i =1; i < argc; i++) { // ignore 0 argument whith exec path
    printf("Argument %d: %s\n", i, argv[i]);
    }
    char cwd[MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("Current working dir: %s\n", cwd);
    }
    
    char* fullPath;
    char slash[2] = {'/'};
    fullPath = (char*)malloc(strlen(cwd)+strlen(argv[1]) + strlen(slash)); /* make space for the new string (should check the return value ...) */
    strcpy(fullPath, cwd); /* copy name into the new var */
    strcat(fullPath, slash);
    strcat(fullPath, argv[1]); /* add the extension */
    
    /*
    printf(slash);
    printf("\n");
    printf(fullPath);
    printf("\n");
    */
    
    fp=fopen(fullPath, "r");
    char buffer[MAX];
    int countOfLines = 0;
    if(fp != NULL) {
        printf("File opened;");
        printf("\n");
        while (fgets(buffer, MAX, fp) != NULL) {
            int length = strlen(buffer);
            if(buffer[length -1] == '\n' ) {
            if(strcmp(buffer, "") != 0) {
            countOfLines++;
            if(countOfLines >= 10) {
                continue;
            }
            printf("%s", buffer);
            }
        }
        }
        //printf("%d",countOfLines / 2);
        printf("\n");
        //printf("%s", buffer);
        fclose(fp);
    }
    
    return 0;
}

