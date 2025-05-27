#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "budget.h"

void showExpenseDistribution(Entry entries[], int count) {
    float totalIncome = 0, totalExpense = 0;
    float needs = 0, wants = 0;

    for (int i = 0; i < count; i++) {
        if (strcmp(entries[i].type, "income") == 0) {
            totalIncome += entries[i].amount;
        } else if (strcmp(entries[i].type, "expense") == 0) {
            totalExpense += entries[i].amount;

            if (strcmp(entries[i].subtype, "Needs") == 0) {
                needs += entries[i].amount;
            } else if (strcmp(entries[i].subtype, "Wants") == 0) {
                wants += entries[i].amount;
            }
        }
    }

    printf("\n===== Expense Distribution Report =====\n");
    printf("Total Income: $%.2f\n", totalIncome);
    printf("Total Expenses: $%.2f\n", totalExpense);

    if (totalExpense > 0 && totalIncome > 0) {
        printf("Needs: $%.2f (%.2f%% of expenses, %.2f%% of income)\n",
            needs,
            (needs / totalExpense) * 100,
            (needs / totalIncome) * 100);

        printf("Wants: $%.2f (%.2f%% of expenses, %.2f%% of income)\n",
            wants,
            (wants / totalExpense) * 100,
            (wants / totalIncome) * 100);
    }

    printf("Net Balance: $%.2f\n", totalIncome - totalExpense);
    printf("=======================================\n\n");
}

int compareById(const void *a, const void *b) {
    Entry *e1 = (Entry *)a;
    Entry *e2 = (Entry *)b;
    return e1->id - e2->id;
}

int compareByDate(const void *a, const void *b) {
    Entry *e1 = (Entry *)a;
    Entry *e2 = (Entry *)b;
    return strcmp(e1->date, e2->date);
}

int compareByAmount(const void *a, const void *b) {
    Entry *e1 = (Entry *)a;
    Entry *e2 = (Entry *)b;
    if (e1->amount < e2->amount) return -1;
    else if (e1->amount > e2->amount) return 1;
    else return 0;
}

int compareByDescription(const void *a, const void *b) {
    Entry *e1 = (Entry *)a;
    Entry *e2 = (Entry *)b;
    return strcmp(e1->description, e2->description);
}

void sortEntries(Entry entries[], int count) {
    int choice;
    printf("\nSort Menu\n");
    printf("1. Sort by ID\n");
    printf("2. Sort by Date\n");
    printf("3. Sort by Amount\n");
    printf("4. Sort by Description\n");
    printf("Choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            qsort(entries, count, sizeof(Entry), compareById);
            printf("Entries sorted by ID.\n");
            break;
        case 2:
            qsort(entries, count, sizeof(Entry), compareByDate);
            printf("Entries sorted by Date.\n");
            break;
        case 3:
            qsort(entries, count, sizeof(Entry), compareByAmount);
            printf("Entries sorted by Amount.\n");
            break;
        case 4:
            qsort(entries, count, sizeof(Entry), compareByDescription);
            printf("Entries sorted by Description.\n");
            break;
        default:
            printf("Invalid sort option.\n");
            return;
    }
}

void addEntry(Entry entries[], int count) {
    Entry newEntry;
    newEntry.id = (count == 0) ? 1 : entries[count - 1].id + 1;

    char useToday;
    printf("Use today's date? (y/n): ");
    scanf(" %c", &useToday);

    if (useToday == 'y' || useToday == 'Y') {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        snprintf(newEntry.date, sizeof(newEntry.date), "%04d-%02d-%02d",
                 tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    } else {
        printf("Enter date (YYYY-MM-DD): ");
        scanf("%s", newEntry.date);
    }
    
    printf("Enter type (Income/Expense): ");
    scanf("%s", newEntry.type);

    printf("Enter category: ");
    scanf("%s", newEntry.category);

    printf("Enter description: ");
    getchar(); // Consume leftover newline
    fgets(newEntry.description, sizeof(newEntry.description), stdin);
    newEntry.description[strcspn(newEntry.description, "\n")] = 0; // remove trailing newline

    printf("Enter amount: ");
    scanf("%f", &newEntry.amount);

    entries[count] = newEntry;
    count++;

    // Append entry to finances.txt
    FILE *file = fopen("finances.txt", "a");
    if (file == NULL) {
        printf("Error: Unable to open finances.txt for writing.\n");
    }
    // Write in correct format: ID|DATE|TYPE|CATEGORY|DESCRIPTION|AMOUNT
    fprintf(file, "%d|%s|%s|%s|%s|%.2f\n",
            newEntry.id,
            newEntry.date,
            newEntry.type,
            newEntry.category,
            newEntry.description,
            newEntry.amount);
    fclose(file);
    printf("Entry added successfully with ID %d.\n", newEntry.id);
}

#include <stdio.h>
#include <string.h>
#include "budget.h"

void modifyEntry(Entry entries[], int count, const char *filename) {
    int targetId;
    printf("Enter the ID of the entry to modify: ");
    scanf("%d", &targetId);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (entries[i].id == targetId) {
            found = 1;
            printf("\nCurrent Entry:\n");
            printf("ID: %d\n", entries[i].id);
            printf("Date: %s\n", entries[i].date);
            printf("Type: %s\n", entries[i].type);
            printf("Category: %s\n", entries[i].subtype);
            printf("Description: %s\n", entries[i].description);
            printf("Amount: %.2f\n", entries[i].amount);

            int choice;
            printf("\nWhat would you like to modify?\n");
            printf("1. Date\n");
            printf("2. Amount\n");
            printf("Choice: ");
            scanf("%d", &choice);

            if (choice == 1) {
                char newDate[11];
                printf("Enter new date (YYYY-MM-DD): ");
                scanf("%s", newDate);
                strncpy(entries[i].date, newDate, sizeof(entries[i].date));
                printf("Date updated successfully.\n");
            } else if (choice == 2) {
                float newAmount;
                printf("Enter new amount: ");
                scanf("%f", &newAmount);
                entries[i].amount = newAmount;
                printf("Amount updated successfully.\n");
            } else {
                printf("Invalid choice. No changes made.\n");
                return;
            }

            // Overwrite the file
            FILE *file = fopen(filename, "w");
            if (!file) {
                printf("Error: Could not open file for writing.\n");
                return;
            }

            for (int j = 0; j < count; j++) {
                fprintf(file, "%d|%s|%s|%s|%s|%.2f\n",
                        entries[j].id,
                        entries[j].date,
                        entries[j].type,
                        entries[j].subtype,
                        entries[j].description,
                        entries[j].amount);
            }

            fclose(file);
            printf("Entry updated successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("No entry with ID %d found.\n", targetId);
    }
}

void filterByMonth(Entry entries[], int count) {
    int year, month;
    char targetPrefix[8]; // "YYYY-MM" + null terminator

    printf("Enter year (e.g., 2025): ");
    scanf("%d", &year);
    printf("Enter month (1-12): ");
    scanf("%d", &month);

    snprintf(targetPrefix, sizeof(targetPrefix), "%04d-%02d", year, month);

    printf("\nTransactions for %s\n", targetPrefix);
    printf("===========================\n\n");

    printf("%-5s %-12s %-10s %-12s %-20s %-10s\n", "ID", "Date", "Type", "Category", "Description", "Amount");
    printf("------------------------------------------------------------------------\n");

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strncmp(entries[i].date, targetPrefix, 7) == 0) {
            printf("%-5d %-12s %-10s %-12s %-20s $%.2f\n",
                   entries[i].id,
                   entries[i].date,
                   entries[i].type,
                   entries[i].subtype,
                   entries[i].description,
                   entries[i].amount);
            found = 1;
        }
    }

    if (!found) {
        printf("No entries found for %s.\n", targetPrefix);
    }
}
