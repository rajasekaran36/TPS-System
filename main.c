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

bank* a_bank = NULL;


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
    printf("Bank details saved to file (bank.dat)\n");
}

bank* load_bank(){
    FILE* fp = fopen("bank.dat","rb");
    fseek(fp,0,SEEK_END);
    int file_size = ftell(fp);
    int total_records = file_size/sizeof(account);
    fseek(fp,0,SEEK_SET);

    bank* a_bank = (bank*)malloc(sizeof(bank));
    a_bank->accounts = (account*)malloc(sizeof(account)*5);

    for(int i=0;i<total_records;i++){
        fread(&a_bank->accounts[i],sizeof(account),1,fp);
    }
    a_bank->no_of_accounts = total_records;
    return a_bank;
}

account* get_account(bank* a_bank, int account_no){
    if(account_no<=a_bank->no_of_accounts){
        return &a_bank->accounts[account_no-1];
    }
    return NULL;
}

void display_all_accounts(bank* a_bank){
    account* an_account = NULL;
    for(int i=0;i<a_bank->no_of_accounts;i++){
        an_account = &a_bank->accounts[i];
        printf("%d\t%s\t%2.f\n", an_account->number,an_account->name,an_account->balance);
    }
}
void reset_system(){
    FILE* fp = fopen("bank.dat", "wb");
    fclose(fp);
}

void admin_operations(){
    int option = 0;
    printf("1.Load Bank\n"
           "2.Display All Accounts\n"
           "3.Save Bank\n"
           "4.System Reset\n"
           "5.Enter your choice: ");
    scanf("%d", &option);
    switch(option){
        case 1: 
        a_bank = load_bank();
        break;

        case 2:
        display_all_accounts(a_bank);
        break;

        case 3:
        save_bank(a_bank);
        break;

        case 4:
        reset_system();
        break;
    }
}
void init(){
    if(is_file_empty()==0){
        char name[20];
        printf("The Bank is Empty --- Create your First Account\n");
        a_bank = (bank*)malloc(sizeof(bank));
        printf("Enter your name: ");
        scanf("%s",name);
        a_bank->accounts = (account*)malloc(sizeof(account));
        a_bank->accounts->number = 1;
        strcpy(a_bank->accounts->name, name);
        a_bank->accounts->balance = 0.0;
        a_bank->no_of_accounts = 1;
        save_bank(a_bank);
        init();
    }
    else{
        a_bank = load_bank();
    }
}

void access_account(){
    account* an_account = NULL;
    printf("Enter account number: ");
        int account_no = 0;
        scanf("%d", &account_no);
        an_account = get_account(a_bank, account_no);
        
        if(an_account!=NULL){
            int option = 0;
            do{
                int amount = 0;
                printf("1.Display Account\n"
                    "2.Deposit Account\n"
                    "3.WithDraw Account\n"
                    "4.Exit\n"
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
                }
            }while(option<4);
        }
        else{
            printf("Account not exist\n\n");
        }
}
int main(){
    init();
    char choice = 'Y';
    int option = 0;
    do{
        account* an_account = NULL;
        do {
            printf("\nWELCOME TO BANK\n");
            printf("---------------\n");
            printf("1.Access Account\n"
                "2.Create Account\n"
                "3.Display All Accounts\n"
                "4.Exit\n"
                "Enter your choice: ");
            
                scanf("%d", &option);
                switch(option){
                    case 1:
                    access_account();
                    break;
                    
                    case 2:
                    printf("Enter account holder name:");
                    char name[20];
                    scanf("%s",name);
                    create_account(a_bank,name);
                    break;

                    case 3:
                    display_all_accounts(a_bank);
                    break;
                }
            }while(option<4);
            save_bank(a_bank);

            printf("Continue (Y/N): ");
            scanf(" %c", &choice);

    }while(choice!='N');
    return 0;
}