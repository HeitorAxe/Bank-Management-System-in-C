#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct user {
    char phone[50];
    char accountNum[50];
    char password[50];
    float balance;
};

//the file name should be already concatenated to the ".dat"
void saveUserChanges(struct user usr, char * filename){
    FILE * fp1;

     //updates the user file by rewriting it
    fp1 = fopen(filename, "w");//filename is already concatenated to .dat
    fwrite(&usr, sizeof(struct user), 1, fp1);

    if(fwrite != NULL) printf("\n OPERATION COMPLETE! \n");
    fclose(fp1);
}


int main(){
    int one = 1;

    while(one == 1){
        system("cls");
        //in linux it should be system(clear)
        struct user usr, usr1;
        FILE * fp;
        char filename[50], loginPhone[50], loginPassw[50];
        char transferToPhone[50];
        char cont = 'y';
        float amount;
        int opt, choice;

        printf("\n");
        printf("-=-=-=-=-=-=WELCOM TO THE BANK=-=-=-=-=-=-\n");
        printf("\n");
        printf("\nWhat do you want to do?");
        printf("\n");
        printf("\n  [1] Register an account");
        printf("\n  [2] Login to an account");

        printf("\n\nYour choice:\t");
        scanf("%d", &opt);

        if(opt == 1){
            system("cls");
            //in linux it should be system(clear)

            //takes user input
            printf("Enter your account number:\t");
            scanf("%s", usr.accountNum);
            printf("Enter your phone number:\t");
            scanf("%s", usr.phone);
            printf("Enter your new password:\t");
            scanf("%s", usr.password);

            usr.balance = 0;

            // this copies the user's phone number to the var filename
            strcpy(filename, usr.phone);

            //this concatenates tha var filename to the str ".dat" and creates a file
            // with that that name, and it also opens it.
            fp = fopen(strcat(filename, ".dat"), "w");

            //indicates what is going to be stored in the file, the size of
            //the strcuture, how many structures will be stored and file address
            fwrite(&usr, sizeof(struct user), 1, fp);//

            if(fwrite != 0){
                printf("\n\nAccount succcesfully registred\n");
            }else{
                printf("\n\nSomething went wrong, please try again.\n");
            }

            //closes the file
            fclose(fp);
        }

        else if(opt == 2){
            system("cls");
            //in linux it should be system(clear)
            
            printf("\nEnter your phone number:\t");
            scanf("%s", loginPhone);
            printf("\nEnter your password:\t");
            scanf("%s", loginPassw);

            // this copies the user's phone number to the var filename
            strcpy(filename, loginPhone);
            //opens the file in read mode
            fp = fopen(strcat(filename, ".dat"), "r");

            //check if the program could open a file with given name
            if(fp == NULL){
                printf("There is no account linked to this phone number!");
            }
            //in case it does:
            else{
                //tells the program what kind of structure and how many should be
                //read from which file, stores the strcucture in the variable address of usr
                fread(&usr, sizeof(struct user), 1, fp);

                //closes the file
                fclose(fp);

                //Checks the password
                //strcmp compares two strings
                if(!strcmp(loginPassw, usr.password)){
                    printf("\nPASSWORD MATCHED !");

                    //main login menu
                    while (cont == 'y')
                    {
                        printf("\n");
                        printf("-=-=-=-=-=-=WELCOM TO THE BANK=-=-=-=-=-=-\n");
                        printf("\n");
                        system("cls");
                        printf("\nSelect an option: ");
                        printf("\n  [1] Check Balance");
                        printf("\n  [2] Deposit");
                        printf("\n  [3] Withdraw");
                        printf("\n  [4] Transfer");
                        printf("\n  [5] Exit");
                        printf("\n");


                        printf("\nYour choice: ");
                        scanf("%d", &choice);

                        switch (choice)
                        {
                        case 1:
                            printf("\nYour current balance is $%.2f\n", usr.balance);
                            break;
                        case 2:
                            printf("\nEnter the amount:\t");
                            scanf("%f", &amount);
                            usr.balance += amount;
                            saveUserChanges(usr, filename);
                            break;
                        case 3:
                            printf("\nEnter the amount:\t");
                            scanf("%f", &amount);
                            if(amount > usr.balance) printf("\nInsufficient balance\n");

                            else{
                                usr.balance -= amount;
                                saveUserChanges(usr, filename);}

                            break;

                        case 4:
                            printf("\nInsert the receiver phone number:\t");
                            scanf("%s", transferToPhone);
                            printf("\nPlease enter the transference value:\t");
                            scanf("%f", &amount);
                            if(amount > usr.balance) printf("\nInsufficient balance\n");
                            else{
                                strcpy(filename, transferToPhone);
                                fp = fopen(strcat(filename, ".dat"), "r");
                                fread(&usr1, sizeof(struct user), 1, fp);
                                fclose(fp);
                                usr1.balance += amount;
                                
                                saveUserChanges(usr1, filename);

                                if(fwrite != NULL){
                                    printf("\nTransference Complete!");
                                    strcpy(filename, usr.phone);
                                    usr.balance -= amount;
                                    saveUserChanges(usr, strcat(filename, ".dat"));
                                }
                            }
                            break;
                        case 5:
                            exit(1);

                        
                        default:
                            break;
                        }

                        printf("\nWould you like to continue operations?[y/n]: ");
                        scanf("%s", &cont);

                    }                    
                }
                else{
                    printf("INVALID PASSWORD!");
                }
            }
        }
    }
    return 0;

}