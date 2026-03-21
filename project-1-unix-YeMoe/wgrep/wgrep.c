// Name: Ye Moe
// Objective: Creating a wgrep.c file to search for a term in a file (or files) that the user specifies and prints out the lines containing it
// Compile using `gcc -o wgrep wgrep.c -Wall -Werror` provided from the GitHub repo
// Used strstr() from the Useful Functions on the GitHub repo

// Note:
// 1. ./wgrep foo bar.txt should accept two arguments, and look for the term "foo" in the bar.txt file 
// 2. Search terms are case sensitive
// 4. ./wgrep without any other arguments should print "wgrep: searchterm [file ...]" followed by a newline and exit with status 1 
// 5. ./wgrep should still work without any file provided, but instead of reading from a file, wgrep should read from standard input
// 6. If the file cannot be opened, it should print "wgrep: cannot open file" followed by a newline and exit with status 1
// 7. If an empty string is the search term, then wgrep can "either match NO lines or match ALL lines"

#include <stdio.h>
#include <string.h> // for strstr()

int main(int argc, char *argv[]) {
    FILE *fp; // file pointer
    if (argc == 1) { // no search term case
        printf("wgrep: searchterm [file ...]\n");
        return 1;
    }
    else if (argc == 2) { // case to read from standard input
        FILE *stream = stdin; // read from standard input
        char buffer[1024]; 
        while (fgets(buffer, sizeof(buffer), stream) != NULL) { // loop through input
            if (strstr(buffer, argv[1]) != NULL) {
                printf("%s", buffer);
            }
        }
    }
    else { // for the case to loop through the files
        for (int i = 2; i < argc; i++) { // start from 2 because 1 is the search term
            fp = fopen(argv[i], "r");
            if (fp == NULL) {
                printf("wgrep: cannot open file\n");
                return 1;
            }
            char buffer[1024];
            while (fgets(buffer, sizeof(buffer), fp) != NULL) {
                if (strstr(buffer, argv[1]) != NULL) {
                    printf("%s", buffer);
                }
            }
            fclose(fp);
        }
    }
    return 0;
}