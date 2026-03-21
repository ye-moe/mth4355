// Name: Ye Moe
// Objective: Creating a wcat.c file to read a file (or files) that the user specifies and prints out the contents
// Compile using `gcc -o wcat wcat.c -Wall -Werror` provided from the GitHub repo
// Need to utilize fopen(), fgets(), fclose(), and printf()

// According to the Details section:
// 1. ./wcat somefile.txt should print the contents of the text file, and the exit code should be 0, usually by returning a 0 from main() or by calling exit(0)
// 2. ./wcat file1 file2 should print out each file in turn in that order. If both exist, the exit code should be 0
// 3. ./wcat with no arguments should just exit and return 0
// 4. ./wcat good.txt missing.txt another.txt should print the files in that order; however, if there is a failure with fopen() on a file, print "wcat: cannot open file" followed by a newline and exit code 1. Then, continue printing until the end of the file list is reached or there is an error message

#include <stdio.h> // header file from lab-tutorial 

int main(int argc, char *argv[]) {
    FILE *fp; // make the file pointer to read file
    if (argc == 1) { // case 3 where there is no argument
        return 0;
    }
    else {
        for (int i = 1; i < argc; i++) { // otherwise, loop through the files
            fp = fopen(argv[i], "r"); // open the file and read
            if (fp == NULL) { // if it fails, print the error message and exit code 1
                printf("wcat: cannot open file\n");
                return 1;
            }
            char buffer[1024];
            while (fgets(buffer, sizeof(buffer), fp) != NULL) { // read the file
                printf("%s", buffer); // and print it
            }
            fclose(fp); // close the file
        }
    }
    return 0;
}