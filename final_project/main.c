#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define user1 "Firuz"    //defining the shopkeepers and their passwords
#define user2 "Eldor"
#define pw1 "p@assw0rd"
#define pw2 "pAsswOrd"

//Selin Samra - 2020313582

/*
Create structures for both shopkeepers
 Create a function for shopkeepers to manage their stores and the info of the products they have
 if the shop owner chooses to add a new product, the file will be opened in the append mode
 if the shop owner choose to edit the products they already have, the line for the new version of the product will be written to the new file with the other products, and skip the old version of the product
 if the shop owner choose to remove a product copy all products into the new file except the one that will be removed
 if the customer chooses to see all products, two files for the both stores will be printed
 if the customer chooses to search a product with a specific letter, char pointer in the file look at every beginning in the files and print the product
*/

struct shopKeeper{   //structure for the shopkeepers
    int id;   //as first and second shopkeeper
    char user[10];
    char pw[10];
    char store_name[10];  //name for the files
};

void stores(struct shopKeeper user){
    bool logged = true; //it will return false if the user log out
    FILE *store,*newFile;  //file pointers
    int choice,t=0; //to save the choice in the menu
    int id,temp=1;
    char ch;  //to get the char in the files
    int* orderDates;  //to order expire dates
    int* lineOrder;  //to match line orders with the expire dates
    char cont;  //to press any key to continue
    char dates[10];  //to save the expire dates as string
    bool go;  //to something from the file
    char last[1];  //to get the last character in the file
    int i=0,k=0;
    char pn[15],p[15],q[15],ed[15];  //to save the input for editing or adding the products
    int count=1,tab=0;   //to count the lines and the number of tabs in the file
    while(logged){
        printf("\n***G25 Store %d***\nShopkeeper: ",user.id);  //print the shopkeeper's name and the store number
        printf("%s",user.user);
        fflush(stdin);
        printf("\n===========================================\n\t1.Show my products\n\t2.Sort products by expire date\n\t3.Add products\n\t4.Remove  products\n\t5.Edit products\n\t6:Log out\n===========================================\n\tEnter Your Choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("\n***G25 Store %d***\nShopkeeper: ",user.id);
                printf("%s",user.user);
                printf("\n\tProducts List: \nProduct Name\tPrice\tQuantity\tExpire Date\n");
                store = fopen(user.store_name,"r");  //open the source file
                if(store==NULL){   //check if its opened
                    printf("Cannot open file.");
                    exit(1);
                }
                while ((ch= fgetc(store)) !=EOF){
                    putchar(ch);   //print the all products from the file
                }
                fclose(store);  //close the file
                fflush(stdin);
                printf("\n\n\tPress any key to continue\n\n\t");  //go back to menu
                scanf("%c",&cont);
                break;
            case 2:
                printf("\n***G25 Store %d***\nShopkeeper: ",user.id);
                printf("%s",user.user);
                store = fopen(user.store_name,"r");  //open the source file
                if(store==NULL){   //check if its opened
                    printf("Cannot open file.");
                    exit(1);
                }
                int size = 10;
                lineOrder = (int*) calloc(size, sizeof(int));
                printf("\n===========================================\n\tProducts List by Expire  Date:\nProduct Name\tPrice\tQuantity\tExpire Date\n");
                orderDates = (int*) calloc(size, sizeof(int));  //create an array to order the expire dates
                count=1;   //initialize the line counter, tab counter and boolean
                i=0;
                tab=0;
                k=0;
                go=false;
                while ((ch= fgetc(store)) !=EOF){
                    if(ch=='\n'){
                        count++;   //count the lines
                    }
                    if(ch=='\t')  //count the number of tabs to get the expire dates
                        tab++;
                    if (tab==3)
                        go=true;
                    if(go){
                        if(ch!='-' ){  //when the string of expire date is reached save the numbers in an array and skip the "-"
                            dates[i] = ch;
                            i++;
                        }
                        if(ch == '\n' || ch==EOF){
                            if(k >= size){
                                orderDates = (int*) realloc(orderDates,(size*2) * sizeof(int));  //change the size if it is not enough
                                size*=2;
                            }
                            orderDates[k] = atoi(dates);  //change the expire dates from string to an integer
                            k++;  //to save the next one
                            i=0;  //to save the next date
                            tab=0;  //to go the next line
                            go=false;
                        }
                    }
                }
                lineOrder = (int*) realloc(lineOrder,(count-1) * sizeof(int));  //to match the line orders with the expire dates
                for (int j = 0; j < count-1; ++j) {
                    lineOrder[j]=j+1;  //initialize the lines
                }
                lineOrder[count-1]='\0';
                for (int m = 0; m < count-1; m++) {   //to order the expire dates with an ascending order and match the line orders with them
                    for (int j = m+1; j < count-1; j++) {
                        if(orderDates[m]>orderDates[j]){  //swapping
                            t = orderDates[m];
                            orderDates[m] = orderDates[j];
                            orderDates[j] = t;
                            t=lineOrder[m];
                            lineOrder[m]=lineOrder[j];
                            lineOrder[j]=t;
                        }
                    }
                }
                rewind(store);  //to go back to the beginning of the file

                i=0;
                go=true;
                while(go){
                    int line = 1;  //initialize the line number
                    while ((ch = getc(store)) != EOF)
                    {

                        if (ch == '\n')
                            line++;  //get the number of lines
                        if (line == lineOrder[i])  //if the line number is the same with the ordered version in the array it will print in that order
                        {
                            putchar(ch);
                        }

                    }
                    i++;
                    rewind(store); //go back to the starting point of the file
                    if(lineOrder[i+1]=='\0') //to print prettier
                        printf("\n");
                    if(lineOrder[i]=='\0')  //if it is the end boolean goes to false
                        go=false;
                }
                fclose(store);

                fflush(stdin);
                printf("\n\n\tPress any key to continue\n\n\t");
                scanf("%c",&cont);
                break;
            case 3:
                printf("\n***G25 Store %d***\nShopkeeper: ",user.id);
                printf("%s",user.user);
                store = fopen(user.store_name,"a+");  //open the source file in append mode
                if(store==NULL){   //check if its opened
                    printf("Cannot open file.");
                    exit(1);
                }
                fflush(stdin);
                printf("\n\tAdd New Product:\n\tProduct Name: ");
                fgets(pn,15,stdin);  //get the new product's name
                pn[strlen(pn)-1]='\0';
                fprintf(store,"%s",pn);  //save the new product's name into the file
                printf("\n\tPrice (per item): ");
                fgets(p,15,stdin);  //get the new product's price
                p[strlen(p)-1]='\0';
                fprintf(store,"\t%s",p);  //save the new product's price into the file
                printf("\n\tQuantity: ");
                fgets(q,15,stdin);   //get the new product's quantity
                q[strlen(q)-1]='\0';
                fprintf(store,"\t%s",q);   //save the new product's quantity into the file
                printf("\n\tExpire Date: ");
                fgets(ed,15,stdin);   //get the new product's expire date
                ed[strlen(ed)-1]='\0';
                fprintf(store,"\t%s",ed);   //save the new product's expire date into the file

                fseek(store,0L,SEEK_END);   //put pointer at the end of file
                fgets(last,1,store);   //get the last character from the file
                if(strcmp(last,"\n")!=0)  //if it is not \n write it into the file
                    putc('\n',store);
                fclose(store);
                fflush(stdin);
                printf("\n\n\tPress any key to continue\n\n\t");
                scanf("%c",&cont);
                break;
            case 4:
                printf("\n***G25 Store %d***\nShopkeeper: ",user.id);
                printf("%s",user.user);
                printf("\n\tProduct List:\nProduct Name\tProduct ID\n");
                store= fopen(user.store_name,"r");  //open the file
                if(store==NULL){  //check if its opened
                    printf("Can't open the file\n");
                    exit(1);
                }
                count=1;
                go=false;
                for (int i = 1; i < 20;){
                    while ((ch= fgetc(store)) !=EOF){  //get everything from the source file
                        if(ch=='\n'){    //count lines
                            printf("\t%d",count);  //print the line number(id of the product)
                            count++;
                        }

                        if(count==i){  //to start writing only the product's name
                            go=true;
                        }
                        if(go){
                            if(ch!='\t')  //print only the name of product
                                putchar(ch);
                            else{
                                go=false;
                                printf("\t");
                                i++;
                            }

                        }
                    }
                    i++;
                }
                printf("\n===========================================\nEnter ID of removing product: ");
                scanf("%d",&id);   //save the id of the product that will be removed
                newFile = fopen("same.txt", "w");  //open a new file to save the new version
                rewind(store);  //go to the beginning of the original file
                temp=1;  //initialize the temp
                while ((ch = getc(store)) != EOF)
                {
                    if (ch == '\n')  //get the lines
                        temp++;

                    if (temp != id)  //except the line to be deleted, copy all lines to the new file
                    {
                        putc(ch, newFile);
                    }
                }

                fclose(store);  //close the original file and the new file
                fclose(newFile);
                remove(user.store_name);  //delete the old file
                rename("same.txt", user.store_name);  //rename the new file as the old one
                fflush(stdin);
                printf("\n\n\tPress any key to continue\n\n\t");
                scanf("%c",&cont);
                break;
            case 5:
                printf("\n***G25 Store %d***\nShopkeeper: ",user.id);
                printf("%s",user.user);
                printf("\n\tProducts List: \nProduct Name\tPrice Quantity\tExpire Date\tProduct ID\n");
                store = fopen(user.store_name,"r");  //open the source file in read mode
                if(store==NULL){   //check if its opened
                    printf("Cannot open file.");
                    exit(1);
                }
                count=1;
                go=false;
                while ((ch= fgetc(store)) !=EOF){

                    if(ch=='\n'){  //count lines and print the id
                        printf("\t%d",count);
                        count++;
                    }
                    go=true;
                    if(go){
                        putchar(ch); //print the products
                        if(ch=='\n'){
                            go=false;
                        }

                    }
                }
                printf("\n===========================================\nEnter ID of editing product: ");
                fflush(stdin);
                scanf("%d",&id);  //save the id of the product that will be edited
                printf("\n===========================================\n\tEditing Product:\n\tProduct ID: %d\n\tProduct Name: ",id);

                newFile = fopen("same.txt", "w");  //open a new file to save the edited version
                rewind(store);  //go back to the beginning of the original file
                temp=1;  //initialize the temp
                while ((ch = getc(store)) != EOF)
                {
                    if (ch == '\n' )
                        temp++;

                    if(temp==id)  //if the line number(id) is same with the id in the input get the information and write to the new file
                    {
                        fflush(stdin);
                        fgets(pn,15,stdin);
                        pn[strlen(pn)-1]='\0';
                        fprintf(newFile,"\n%s",pn);
                        fflush(stdin);
                        printf("\n\tPrice (per item): ");
                        fgets(p,15,stdin);
                        p[strlen(p)-1]='\0';
                        fprintf(newFile,"\t%s",p);
                        fflush(stdin);
                        printf("\n\tQuantity: ");
                        fgets(q,15,stdin);
                        q[strlen(q)-1]='\0';
                        fprintf(newFile,"\t%s",q);
                        fflush(stdin);
                        printf("\n\tExpire Date: ");
                        fgets(ed,15,stdin);
                        ed[strlen(ed)-1]='\0';
                        fprintf(newFile,"\t%s",ed);
                        temp++;
                    }
                    if(temp!=id+1)   //do not save the old version of the product into the new file
                        putc(ch, newFile);

                }

                fclose(store);  //close the files
                fclose(newFile);

                remove(user.store_name);  //remove the old file
                rename("same.txt", user.store_name);  //rename the new file as the old name

                fflush(stdin);
                printf("\n\n\tPress any key to continue\n\n\t");
                scanf("%c",&cont);
                break;
            case 6:
                printf("Have a great day!");  //go back to the main menu
                logged=false;
                break;
            default:
                break;
        }
    }
}

struct shopKeeper createShopKeeper(int num){  //to create the structs for the both shopkeepers with their information
    if(num==1){
        struct shopKeeper one;
        one.id =1;
        strcpy(one.user,user1);
        strcpy(one.pw,pw1);
        strcpy(one.store_name,"store1.txt");
        return one;
    }
    if(num==2){
        struct shopKeeper two;
        two.id=2;
        strcpy(two.user,user2);
        strcpy(two.pw,pw2);
        strcpy(two.store_name,"store2.txt");
        return two;
    }
}
void user_choice(int num){
    if(num==1){
        struct shopKeeper one = createShopKeeper(1);  //create the shopkeeper
        stores(one);  //go to the stores options
    }
    if(num==2){
        struct shopKeeper two = createShopKeeper(2);  //create the shopkeeper
        stores(two);    //go to the stores options
    }

}

int checkUser(char name[], char pw[]){
    int check_user1 = strcmp(user1,name); //compare user names
    int check_pw1 = strcmp(pw1,pw); //compare passwords
    int check_user2 = strcmp(user2,name);  //compare user names
    int check_pw2 = strcmp(pw2,pw);  //compare passwords
    if(check_user1 == 0 && check_pw1 == 0)  //to check if the user name and the password matches
        return 1;
    else if(check_user2 == 0 && check_pw2 == 0)  //to check if the user name and the password matches
        return 2;
    else
        return 3;

}
void customer(struct shopKeeper userF, struct shopKeeper userE){   //get the both structs for the shopkeepers
    int choice;
    bool go;
    bool logged=true;
    FILE *store1, *store2;
    char ch,cont;
    while(logged){
        fflush(stdin);
        printf("\n***CUSTOMER PAGE***\n===========================================\n\t1.Show all products\n\t2.Search for specific product\n\t3.Go to start page\n===========================================\nEnter Your Choice: ");
        scanf("%d",&choice);
        switch (choice) {
            case 1:
                printf("\n***CUSTOMER PAGE***\n===========================================\n");
                printf("\tShow all products:\nProduct Name\tPrice\tQuantity\tExpire Date\tStore Name\tShopkeeper\n");
                store1 = fopen(userF.store_name,"r");  //open the first store's file
                store2 = fopen(userE.store_name,"r");  //open the second store's file
                if(store1==NULL){   //check if its opened
                    printf("Cannot open file.");
                    exit(1);
                }
                while ((ch= fgetc(store1)) !=EOF){
                    if(ch=='\n')  //count lines
                        printf("\tG25 Store 1\tFiruz\n");  //print the store name and the owner's name
                    else
                        putchar(ch);   //print the all products
                }
                if(store2==NULL){   //check if its opened
                    printf("Cannot open file.");
                    exit(1);
                }
                while ((ch= fgetc(store2)) !=EOF){
                    if(ch=='\n')  //count lines
                        printf("\tG25 Store 2\tEldor\n");  //print the store name and the owner's name
                    else
                        putchar(ch);  //print the all products
                }
                fclose(store1);  //close the files
                fclose(store2);
                fflush(stdin);
                printf("\n\n\tPress any key to continue\n\n\t");
                scanf("%c",&cont);
                break;
            case 2:
                fflush(stdin);
                printf("\n***CUSTOMER PAGE***\n===========================================\n");
                printf("\n\tSearch Product (Enter first letter): ");
                scanf("%c",&cont);  //save the letter that will be searched
                printf("\tResults:\nProduct Name\tPrice\tQuantity\tExpire Date\tStore Name\tShopkeeper\n");
                store1 = fopen(userF.store_name,"r");  //open the first store's file
                store2 = fopen(userE.store_name,"r");   //open the second store's file
                if(store1==NULL){   //check if its opened
                    printf("Cannot open file.");
                    exit(1);
                }
                go=false;
                while ((ch= fgetc(store1)) !=EOF){
                    if((int)ch==(int)cont){  //if the character is found boolean is true
                        go=true;
                    }
                    if(go){
                        if(ch!='\n')  //print the product that starts with that letter
                            putchar(ch);
                        else{
                            go=false;
                            printf("\tG25 Store 1\tFiruz\n");  //print the store name and the owner's name
                        }
                    }
                }
                if(store2==NULL){   //check if its opened
                    printf("Cannot open file.");
                    exit(1);
                }
                go=false;
                while ((ch= fgetc(store2)) !=EOF){
                    if((int)ch==(int)cont){  //if the character is found boolean is true
                        go=true;
                    }
                    if(go){
                        if(ch!='\n')  //print the product that starts with that letter
                            putchar(ch);
                        else{
                            go=false;
                            printf("\tG25 Store 2\tEldor\n");   //print the store name and the owner's name
                        }
                    }
                }
                fclose(store2);  //close the files
                fclose(store1);
                break;
            case 3:
                logged=false;  //go back to the menu
                break;
        }
    }
}


int main(void)
{
    int main;
    int counter=0;
    char user[100];
    char password[100];
    bool notExit=true; //the boolean for the whole program
    bool ask =true; //the boolean to check if the user name and password matches
    int user_num;
    struct shopKeeper one = createShopKeeper(1);  //structs for shopkeepers
    struct shopKeeper two = createShopKeeper(2);
    while(notExit) {
        fflush(stdin);
        printf("\n*** Welcome to SKKU Stores Management! ***\n===========================================\n");
        printf("\t1.Login as shopkeeper\n\t2.Search Products\n\t3.Exit\n===========================================\n\tEnter Your Choice: ");
        scanf("%d", &main); //save the option fot the main menu
        switch (main) {
            case 1:
                ask=true;
                while(ask){
                    printf("Login: ");  //ask the name of the shopkeeper
                    scanf("%s", user);  //save the name of the shopkeeper
                    printf("Password: ");  //ask for the password
                    scanf("%s", password);  //save for the password
                    user_num = checkUser(user, password);  //go to the function where it checks if the name and the password matches
                    if(user_num!=3){  //give three trials to match them
                        ask=false;
                    }
                    else{
                        counter++;  //counter increases if they do not match
                        printf("You have entered wrong login or password (%d/3 trials)\n",counter);  //print how many trials you have left
                        if(counter==3){  //if you reach the maximum number program exits
                            printf("\nProgram exits!");
                            exit(1);
                        }
                    }
                }
                user_choice(user_num);  //if you can successfully login it goes to the menu for the shopkeepers
                break;
            case 2:
                customer(one,two);  //if you choose the customer view version, it goes the the customer page view
                break;
            case 3:
                printf("\nThank you for using SKKU Stores Management!");  //exits the whole program
                return 0;
                break;
            default:
                break;
        }
    }
    return 0;
}


