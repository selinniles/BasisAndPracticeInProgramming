#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define user1 "Firuz"
#define user2 "Eldor"
#define pw1 "p@assw0rd"
#define pw2 "pAsswOrd"

int withdraw(int balance,int amount){  //withdraw money from the account
    return balance-amount;
}
int putMoney(int balance,int amount){  //add money to the account
    return balance+amount;
}
void getLastOperation(int i){  //print what the last option is based on the last operation
    if (i==1){
        printf("Checked Balance\n");
    }
    else if(i==2){
        printf("Withdrawal\n");
    }
    else if(i==4){
        printf("Added Money\n");
    }
    else
        printf("No last operation\n");
}
int checkBalance(int balance){ //get the last balance
    return balance;
}

void log_user(char name[],char password[],int i){
    int j=0;  //to save the last operation
    int all_options[100];  //to save the operations
    bool logged = true; //it will return false if the user log out
    int option;
    int amount;
    int balances[3] = {2000,5000,0}; //the two users already have some money, and the user who creates the account has zero money
    printf("\nUsername: %s\nPassword: %s\nBalance: %d\n", name,password,balances[i]);
            while(logged){
                    printf("\n1. Check balance (Enter 1);\n2. Withdraw money (Enter 2);\n3. Last Operation(Enter 3);\n4. Put money (Enter 4);\n0. Exit (Enter 0);\n");
                    scanf("%d",&option); //choose option
                    all_options[j] = option; //save options that is chosen
                    switch(option){
            case 0:
                printf("Thank you for banking with us!\n\n");
                logged=false; //to get out of the while loop
                break;
            case 1:
                printf("\nUser: %s\nBalance: %d\n\n",name,checkBalance(balances[i])); //call the function to check balance of the user
                break;
            case 2:
                printf("Enter amount: ");
                scanf("%d",&amount); //save the amount that will be taken from the account
                if(amount>balances[i]){ //check if the amount is more than the balance
                    printf("Withdrawal amount exceeded account balance.\n\n");
                    break;
                }
                else{
                    balances[i] =withdraw(balances[i],amount); //withdraw the money from the account
                    break;
                }
            case 3:
                printf("\nName: %s\nCurrent Balance: %d\nLast Operation: ",name,checkBalance(balances[i]));
                getLastOperation(all_options[j-1]); //since the last operation is always 3, I should get the one before that
                printf("\n\n");
                break;
            case 4:
                printf("Enter amount: "); //enter the amount to put money on the account.
                scanf("%d",&amount); //save the amount
                balances[i] = putMoney(balances[i],amount); //call the function to add some money to the account
                printf("\n\n");
                break;
            default:
                break;
        }
        j++; //increase j to save new operation
    }
}

int checkUser(char name[], char pw[]){
    int check_user1 = strcmp(user1,name); //compare user names
    int check_pw1 = strcmp(pw1,pw); //compare passwords
    int check_user2 = strcmp(user2,name);  //compare user names
    int check_pw2 = strcmp(pw2,pw);  //compare passwords
    if(check_user1 == 0 && check_pw1 == 0)  //to check if the user name and the password matches
        return 0;
    else if(check_user2 == 0 && check_pw2 == 0)  //to check if the user name and the password matches
        return 1;
        else  //they do not match
            return 3;
}
void signin(){
    char name[100];
    char password[100];
    printf("Please enter your name: ");
    scanf("%s",name);  //save the user name
    fflush(stdin);
    printf("Please enter a password you choose: ");
    scanf("%s",password);  //save the password
    log_user(name,password,2);  //log user to the bank account
}
int main(void)
{
    char user[100];
    char password[100];
    bool notExit=true; //the boolean for the whole bank
    bool ask =true; //the boolean to ask questions when the user is logged in
    int user_num;

    while(notExit){
            char main;
            fflush(stdin);
            printf("\n**********Welcome to your bank!**********\n~~Please type \"l\" to log in or \"c\" to create an account or \"e\" to exit~~\n");
            scanf("%c",&main); //save the option

            if(main=='l'){
                    while(ask){
                            fflush(stdin);
                        printf("\nLogin\nUsername: ");
                        scanf("%s",user); //save the user name
                    fflush(stdin);
                        printf("Password: ");
                        scanf("%s",password);  //save the user name
                        user_num=checkUser(user,password);  //check if the user name and the password matches by calling the function
                        if(user_num==0){
                                log_user(user1,pw1,0); //log the first user in
                                break;
                        }
                        else if(user_num==1){
                                log_user(user2,pw2,1); //log the second user in
                                break;
                        }
                        else{
                            printf("The username and the password does not match. Please try again.\n");
                            printf("If you do not have an account and want to create one please type \"c\" or \"e\" to go to main menu.\n");
                            fflush(stdin);
                            scanf("%c",&main);  //save the option


                            if(main=='c'){
                                signin();  //call the function to create a new account
                                break;
                            }
                            else if(main=='e'){
                                break; //exit the loop if the user wants to exit
                            }
                            else
                                continue;
                            }
                    }
            }
            else if(main=='c'){
                signin();//call the function to create a new account
                break;
            }
            else if(main=='e'){
                    printf("\nThank you for using the bank. Have a good day!\n");
                    break;  //exit the loop if the user wants to exit
            }
    }

    return 0;
}
