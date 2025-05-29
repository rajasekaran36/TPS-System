#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct {
    int number;
    char name[20];
    float balance;
}account;
account* create_account(int number, char* name){
    account* new_account = (account*)malloc(sizeof(account));
    new_account->number = 1;
    strcpy(new_account->name, name);
    new_account->balance = 0.0;
    return new_account;
}
void display_account(account* an_account){
    printf("Account No: %d\n", an_account->number);
    printf("Name      : %s\n", an_account->name);
    printf("Balance   : %d\n\n",an_account->balance);
}
int main(){
    account* an_account = create_account(1,"raja");
    display_account(an_account);
    return 0;
}