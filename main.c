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
    printf("Balance   : %.2f\n\n",an_account->balance);
}
void deposit_account(account* an_account, int amount){
    an_account->balance += amount;
    printf("The amount %d is deposited in the account\n", amount);
    display_account(an_account);
}
void withdraw_account(account* an_account, int amount){
    if(amount<=an_account->balance){
        an_account->balance -= amount;
        printf("The amount %d is debited from the account\n",amount);
    }
    else{
        printf("Request Denied: Due to Insufficient Balance\n");
    }
    display_account(an_account);
}
int is_file_empty(){
    int size = 0;
    FILE* fp = fopen("bank.dat","rb");
    fseek(fp,0,SEEK_END);
    size = ftell(fp);
    fclose(fp);
    return size;
}
void save_account(account* an_account){
    FILE* fp = fopen("bank.dat","wb");
    fwrite(an_account,sizeof(account),1,fp);
    fclose(fp);
    printf("Account details saved to file (bank.dat)\n");
}
account* load_account(){
    FILE* fp = fopen("bank.dat","rb");
    account* an_account = (account*)malloc(sizeof(account));
    fread(an_account,sizeof(account),1,fp);
    fclose(fp);
    printf("Account details fetched from file (bank.dat)\n");
    return an_account;
}
int main(){
    account* an_account = NULL;
    if(is_file_empty()!=0){
        an_account = load_account();
    }
    else{
        an_account = create_account(1,"raja");
    }
    display_account(an_account);
    int option = 0;
    do{
        printf("1.Display Account\n"
               "2.Deposit Account\n"
               "3.WithDraw Account\n"
               "4.Exit\n"
               "Enter your choice: ");
        scanf("%d",&option);
        
    }while(option<=5);

    return 0;
}