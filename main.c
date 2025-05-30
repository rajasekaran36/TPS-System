#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct {
    int number;
    char name[20];
    float balance;
}account;

typedef struct{
    int no_of_accounts;
    account* accounts;
}bank;

void init(){
    FILE* fp = fopen("bank.dat", "wb");
    account an_account = {1,"user", 0.0};
    fwrite(&an_account, sizeof(account),1,fp);
    fclose(fp);
}

void create_account(bank* a_bank, char* name){
    a_bank->accounts = (account*)realloc(a_bank->accounts, (a_bank->no_of_accounts + 1)*sizeof(account));
    a_bank->accounts[a_bank->no_of_accounts].number = a_bank->no_of_accounts + 1;
    strcpy(a_bank->accounts[a_bank->no_of_accounts].name, name);
    a_bank->accounts[a_bank->no_of_accounts].balance = 0.0;
    a_bank->no_of_accounts++;
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
void save_bank(bank* a_bank){
    FILE* fp = fopen("bank.dat","wb");
     printf("save - size of bank: %d\n", a_bank->no_of_accounts);
    for(int i=0;i<a_bank->no_of_accounts;i++){
        fwrite(&a_bank->accounts[i],sizeof(account),1,fp);
    }
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

bank* load_bank(){

    FILE* fp = fopen("bank.dat","rb");
    fseek(fp,0,SEEK_END);
    int file_size = ftell(fp);
    int total_records = file_size/sizeof(account);
    printf("Total Records: %d\n", total_records);
    fseek(fp,0,SEEK_SET);

    bank* a_bank = (bank*)malloc(sizeof(bank));
    a_bank->accounts = (account*)malloc(sizeof(account)*5);

    for(int i=0;i<total_records;i++){
        fread(&a_bank->accounts[i],sizeof(account),1,fp);
    }
    a_bank->no_of_accounts = total_records;
    printf("size of bank: %d\n", a_bank->no_of_accounts);
    return a_bank;
}
int main(){
    //init();
    bank* a_bank = load_bank();
    account* an_account = &a_bank->accounts[0];

    display_account(an_account);
    int option = 0;
    do{
        int amount = 0;
        printf("1.Display Account\n"
               "2.Deposit Account\n"
               "3.WithDraw Account\n"
               "4.Create Account\n"
               "5.Exit\n"
               "Enter your choice: ");
        scanf("%d",&option);
        
        switch(option){
            case 1:
            display_account(an_account);
            break;
            
            case 2:
            
            printf("Enter amount to be deposited: ");
            scanf("%d", &amount);
            deposit_account(an_account, amount);
            break;

            case 3:
            printf("Enter amount to be withdrawn: ");
            scanf("%d", &amount);
            withdraw_account(an_account, amount);
            break;

            case 4:
            printf("Enter account holder name:");
            char name[20];
            scanf("%s",name);
            create_account(a_bank,name);
            break;

            case 5:
            save_bank(a_bank);
            break;
        }
    }while(option<=4);

    return 0;
}