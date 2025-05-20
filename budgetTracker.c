#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "budget.h"

#define MAX_LINE_LEN 256
#define MAX_ENTRIES 1000

void printEntries(Entry entries[], int count) {
    printf("\nFinances Summary\n");
    printf("=================\n\n");

    printf("%-5s %-12s %-10s %-12s %-20s %-10s\n", "ID", "Date", "Type", "Category", "Description", "Amount");
    printf("------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-5d %-12s %-10s %-12s %-20s $%.2f\n",
               entries[i].id,
               entries[i].date,
               entries[i].type,
               entries[i].subtype,
               entries[i].description,
               entries[i].amount);
    }
}

int loadEntries(const char *filename, Entry entries[]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening file.\n");
        return -1;
    }

    char line[MAX_LINE_LEN];
    int count = 0;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // remove newline

        char *token = strtok(line, "|");
        if (token == NULL) continue;

        entries[count].id = atoi(token);

        token = strtok(NULL, "|");
        strncpy(entries[count].date, token, sizeof(entries[count].date));

        token = strtok(NULL, "|");
        strncpy(entries[count].type, token, sizeof(entries[count].type));

        token = strtok(NULL, "|");
        strncpy(entries[count].subtype, token, sizeof(entries[count].subtype));

        token = strtok(NULL, "|");
        strncpy(entries[count].description, token, sizeof(entries[count].description));

        token = strtok(NULL, "|");
        entries[count].amount = atof(token);

        count++;
    }

    fclose(file);
    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s finances.txt\n", argv[0]);
        return 1;
    }

    Entry entries[MAX_ENTRIES];
    int count = loadEntries(argv[1], entries);
    if (count < 0) return 1;

    int choice;

    do {
        printf("\nBudget Tracking System\n");
        printf("======================\n");
        printf("1. Display all entries\n");
        printf("2. Expense Distribution\n");
        printf("3. Sort Entries (coming soon)\n");
        printf("4. Add Entry (coming soon)\n");
        printf("5. Modify Entry (coming soon)\n");
        printf("6. Filter by Month (coming soon)\n");
        printf("7. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        system("clear"); // Use "cls" on Windows if needed

        switch (choice) {
            case 1:
                printEntries(entries, count);
                break;
            case 2:
                showExpenseDistribution(entries, count);
                break;
            case 3:
                sortEntries(entries, count);
                break;
            case 7:
                printf("Goodbye and thanks for using our budget tracker app!\n");
                break;
            default:
                printf("This option is not implemented yet.\n");
                break;
        }
    } while (choice != 7);

    return 0;
}
