#ifndef BUDGET_H
#define BUDGET_H

typedef struct {
    int id;
    char date[11];
    char type[10];
    char subtype[20];
    char category[10];
    char description[50];
    float amount;
} Entry;
void showExpenseDistribution(Entry entries[], int count);
void sortEntries(Entry entries[], int count);
void addEntry(Entry entries[], int count);
void modifyEntry(Entry entries[], int count, const char *filename);
void filterByMonth(Entry entries[], int count);

#endif
