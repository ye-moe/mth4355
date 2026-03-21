// Name: Ye Moe
// Objective: Creating a wsed.c file to either substitute or translate based on val1 and val2 specified by the user
// Compile using `gcc -o wsed wsed.c -Wall -Werror` provided from the GitHub repo

// Some notes:
// 1. ./wsed must be used with an option, either -m substitution or -m translation, two vales and a file
// 2. In -m substitution, the length of the values should match, and then replace that portion
// 3. In -m translation, the characters in val1 should replcae the corresponding ones in val2, and the lengths should still match
// 4. Also, there should be ./wsed --help and ./wsed -h for help message
// 5. If there is not enough argument count, print "wsed: [option] [val1] [val2] [file]" and exit with status 1
// 6. /.wsed can only take either substitution or translation, one at a time. If both is used, print "wsed: [option] [val1] [val2] [file]" and exit with status 1

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *val1 = NULL, *val2 = NULL, *filename;

    if (argc == 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) { // help case from test 10.out
        printf("Usage: wsed [-m mode] [initial] [final] [file]\n");
        printf("-m  mode\n\t\"substitution\" or \"translation\". Default: substitution.\n");
        printf("initial & final\n\t in substitution, all occurrences of initial in [file] are replaced with final\n\t in translation, each character in initial is replaced with the the corresponding character from final in [file]\n");
        return 0;
    }

    // Argument parsing
    if (argc == 4) { // default case which is substitution
        val1 = argv[1];
        val2 = argv[2];
        filename = argv[3];
    }

    else if (argc == 6) { // Must be: ./wsed -m <mode> val1 val2 file
        if (strcmp(argv[1], "-m") != 0) {
            printf("wsed: [option] [val1] [val2] [file]\n");
            return 1;
        }

        if (strcmp(argv[2], "substitution") == 0) { // substitution
            val1 = argv[3];
            val2 = argv[4];
        }
        else if (strcmp(argv[2], "translation") == 0) { // translation
            val1 = argv[3];
            val2 = argv[4];
        }
        else { // error case
            printf("wsed: [option] [val1] [val2] [file]\n");
            return 1;
        }
        filename = argv[5];
    }
    
    else { // Any other arg count is wrong formatting
        printf("wsed: [option] [val1] [val2] [file]\n");
        return 1;
    }

    // Translation-only length check
    if (strcmp(argv[2], "translation") == 0) {
        if (strlen(val1) != strlen(val2)) { // check the lengths of the portion
            printf("wsed: Translation strings not equal length\n");
            return 1;
        }
    }

    // Open file
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("wsed: cannot open file\n");
        return 1;
    }

    // Read and process line by line (like wcat/wgrep)
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (strcmp(argv[2], "translation") == 0) { // translation
            for (int i = 0; buffer[i] != '\0'; i++) {
                char c = buffer[i];
                int found = 0;
                for (int j = 0; val1[j] != '\0'; j++) {
                    if (c == val1[j]) {
                        printf("%c", val2[j]);  // print the replacement character
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    printf("%c", c);  // print the original character
                }
            }
        } 
        else { // substitution            
            size_t val1_len = strlen(val1);
            int i = 0;
            while (buffer[i] != '\0') {
                if (strncmp(&buffer[i], val1, val1_len) == 0) {
                    printf("%s", val2); // print the replacement string
                    i += val1_len;  // skip past the matched portion
                } 
                else {
                    printf("%c", buffer[i]);    // print the original character
                    i++;
                }
            }
        }
    }
    fclose(fp);
    return 0;
}
