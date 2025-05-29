#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct {
    int number;
    char name[20];
    float balance;
}account;
int main(){
    account* an_account = (account*)malloc(sizeof(account));
    an_account->number = 1;
    strcpy(an_account->name, "raja");
    an_account->balance = 0.0;

    printf("Account No: %d\n", an_account->number);
    printf("Name      : %s\n", an_account->name);
    printf("Balance   : %d\n",an_account->balance);
    return 0;
}