#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

    // Show sorted entries
    printEntries(entries, count);
}

void printEntries(Entry entries[], int count) {
    printf("Sort Menu");

    printf("Choice: %-1i",count);  
}