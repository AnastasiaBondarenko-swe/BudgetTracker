#ifndef BUDGET_H
#define BUDGET_H

typedef struct {
    int id;
    char date[11];
    char type[10];
    char subtype[20];
    char description[100];
    float amount;
} Entry;

void showExpenseDistribution(Entry entries[], int count);
void sortEntries(Entry entries[], int count);
void printEntries(Entry entries[], int count);


#endif
