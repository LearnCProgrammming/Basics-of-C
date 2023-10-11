#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAXLENGTH 11
#define MAXCOUNT 5

typedef char* STRING;

int isValidDate(const char *dateStr) {
    int year, month, day;
    if (sscanf(dateStr, "%4d%2d%2d", &year, &month, &day) != 3) {
        // Unable to parse the input string
        return 0; // false
    }      

    if (year < 0 || year > 9999) {
        // Year is out of range
        return 0; // false
    }

    if (month < 1 || month > 12) {
        // Month is out of range
        return 0; // false
    }

    if (day < 1 || day > 31) {
        // Day is out of range
        return 0; // false
    }

    // Check for months ending in 30 days
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return 0; // false
    }

    // Check for February
    if (month == 2 && day > 28) {
        return 0; // false
    }

    return 1; // true
}

// Function to compare names for sorting
int compareNames(const void *a, const void *b) {
    return strcmp(*(const STRING*)a, *(const STRING*)b);
}

// Function to sort names using bubble sort
void bubbleSort(STRING names[], int count) {
    int i, j;
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (strcmp(names[j], names[j + 1]) > 0) {
                STRING temp = names[j];
                names[j] = names[j + 1];
                names[j + 1] = temp;
            }
        }
    }
}

int main() {
    // Variables
    int count = 0;
    STRING names[MAXCOUNT];
    char nameInput[MAXLENGTH];
    char birthInput[9];
    STRING intro = "Records Entry and Sorting Program\nPlease input name and birthday (max: 5 entries).\n";
    STRING nameInputPrompt = "Name (First Last): ";
    STRING birthInputPrompt = "Birthday (YYYYMMDD): ";
    STRING nameTemplate = "%-10s %-8s Entry count: %2d malloc-address: %p -> %p\n";
    STRING sortedNamesTitle = "\nSorted records:\n";
    int length = 0;
    char c;
    int error = 0;
    int i;
    STRING temp;

    // Intro Template
    printf("%s", intro);

    // Get names and birthdays
    while (count < MAXCOUNT && !error) {
        printf("%s", nameInputPrompt);
        length = 0;

        // Get name
        while ((c = getchar()) != '\n' && length < MAXLENGTH - 1) {
            if (c != ' ') {
                nameInput[length++] = c;
            }
        }

        nameInput[length] = '\0'; // Null-terminate the string

        if (!strcmp(nameInput, "0")) {
            break;
        } else {
            printf("%s", birthInputPrompt);
            if (fgets(birthInput, sizeof(birthInput), stdin) == NULL) {
                error = 1; // Error reading input
                break;
            }

            if (birthInput[0] == '\n') {
                // Empty birthday input, terminate the program
                break;
            }

            birthInput[strlen(birthInput) - 1] = '\0'; // Remove the newline character

            if (!isValidDate(birthInput)) {
                printf("Invalid date format.\n");
                continue;
            }

            names[count] = malloc(strlen(nameInput) + 1); // Allocate memory for the name
            assert(names[count] != NULL);
            strcpy(names[count], nameInput);
            printf(nameTemplate, names[count], birthInput, count + 1, (void *)names[count], (void *)&names[count]);
            count++;
        }
    }

    if (!error) {
        // Sort names alphabetically using bubble sort
        bubbleSort(names, count);

        // Show sorted names and birthdays
        printf("%s", sortedNamesTitle);
        for (i = 0; i < count; i++) {
            printf(nameTemplate, names[i], "", i + 1, (void *)names[i], (void *)&names[i]);
            free(names[i]);
        }
    }

    return 0;
}

