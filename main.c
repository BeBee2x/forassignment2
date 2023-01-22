#include "stdio.h"
#include "stdlib.h"
#define size 100
#define limit 50
#define true 1

int globalindex=-1;
char validGmail[]={'@','g','m','a','i','l','.','c','o','m'};
int gmailsize=sizeof(validGmail)/sizeof(validGmail[0]);

void loadingdatafromfile();
void printingdata();
void home();
void login();
int findingemail(char array[limit]);
void passwordchecking(int index);
void register_account();
int checklength(char array[limit]);
int emailValid(char array[limit]);
void emailinputting(char array[limit]);
void passwordConfirm();
void passwordinputting(char array[limit],int length);
void usernameValid();
int usernamefinding(char array[limit],int length);
void usernameinputting(char array[limit],int length);
void ageValid();
void dataSaving();

struct user{
    char username[limit];
    int age;
    char email[limit];
    char password[limit];
};

struct user info[size];

int main(){
        loadingdatafromfile();
        printingdata();
    while(globalindex<limit){
        home();
    }
}

void loadingdatafromfile(){
    FILE *fptr1;
    fptr1= fopen("data.txt","r");
    if(fptr1==NULL){
        printf("No one login here,You can be the first\n");
    }else{
        for (int i = 0; i < limit; i++) {
            fscanf(fptr1,"%d%s%d%s%s",&globalindex,&info[i].username,&info[i].age,info[i].email,&info[i].password);
            if(info[i].username=='\0'){
                break;
            }
        }
        if(globalindex!=-1){
            globalindex-=1;
        }
    }
    fclose(fptr1);
}

void printingdata(){
    for (int i = 0; i <=globalindex; i++) {
        printf("Id-%d Name-%s Age-%d Email-%s Password-%s\n",i+1,info[i].username,info[i].age,
               info[i].email,info[i].password);
    }
}

int checklength(char array[limit]){
    int i=0;
    while(array[i]!='\0'){
        i++;
    }
    return i;
}

int emailValid(char array[limit]){
    int count=0;
    int i= checklength(array);
    int k=gmailsize-1;
    if(i<gmailsize){
        return -1;
    }
    for (int j = i-1; j > (i-gmailsize)-1; j--) {
        if(array[j]==validGmail[k]){
            count++;
            k--;
        }
    }
    if(count!=gmailsize){
        return -1;
    }
    return 1;
}

void passwordConfirm(){
    char password[limit];
    char password2[limit];
    printf("Enter your password:");
    scanf(" %[^\n]",&password);
    printf("Confirm your password:");
    scanf(" %[^\n]",&password2);
    int count=0;
    int i=checklength(password);
    int j= checklength(password2);
    if(i!=j){
        printf("Your passwords are not match,Try again\n");
        passwordConfirm();
    }else{
        for (int k = 0; k < i; k++) {
            if(password[k]!=password2[k]){
                count=1;
            }
        }
        if(count!=0){
            printf("Your passwords are not match,Try again\n");
            passwordConfirm();
        }else{
            passwordinputting(password,i);
            printf("Your registration success\n");
        }
    }
}

void passwordinputting(char array[limit],int length){
    int i= length;
    for (int j = 0; j < i; j++) {
        info[globalindex].password[j]=array[j];
    }
}

void usernameValid(){
    char name[limit];
    int count=0;
    printf("Enter your nickname:");
    scanf(" %[^\n]",&name);
    int i= checklength(name);
    for(int j=0; j<i; j++){
        if(!(name[j]>47 && name[j]<58)){
            count++;
        }
    }
    if(count==i || count==0){
        printf("Name must be contain contain characters and numbers,can't be contain spaces\n");
        usernameValid();
    }else{
        count=0;
        for(int j=0; j<i; j++){
            if(!(name[j]>64 && name[j]<91 || name[j]>96 && name[j]<123 || name[j]>47 && name[j]<58)){
                count++;
            }
        }
        if(count!=0){
            printf("Name must be contain characters and numbers,can't be contain spaces\n");
            usernameValid();
        }else{
            int check=usernamefinding(name,i);
            if(check==1){
                printf("Username already taken\n");
                usernameValid();
            }
            usernameinputting(name,i);
        }
    }
}

int usernamefinding(char array[limit],int length){
    int count=0;
    for (int i = 0; i <= globalindex; i++) {
        int j= checklength(info[i].username);
        if(length==j){
            for (int k = 0; k < j; k++) {
                if(info[i].username[k]==array[k]){
                    count++;
                }
            }
            if(count==j){
                return 1;
            }else{
                count=0;
            }
        }
    }
    return -1;
}

void usernameinputting(char array[limit],int length){
    int i= length;
    for (int j = 0; j < i; j++) {
        info[globalindex].username[j]=array[j];
    }
}

void ageValid(){
    int age;
    printf("Enter your age:");
    scanf("%d",&age);
    if(age<18){
        printf("Only over 18 person can login\n");
    }else{
        info[globalindex].age=age;
    }

}

void dataSaving(){
    FILE *fptr;
    fptr=fopen("data.txt", "a");
    if(fptr==NULL){
        printf("File cannot open,Error[-]\n");
    }else{
        fprintf(fptr,"%d %s %d %s %s\n",globalindex+1,info[globalindex].username,
                info[globalindex].age,info[globalindex].email,info[globalindex].password);
    }
    fclose(fptr);
}

void home(){
    int homekey;
    printf("This is Home\n");
    printf("If you already have a account,press 1 to login:\n"
           "If you don't have a account,press 2 to create account:\n"
           "If you want to exit,press 3 to exit:");
    scanf("%d",&homekey);
    if(homekey==1){
            login();
    }else if(homekey==2){
        globalindex++;
        register_account();
    }else if(homekey==3){
        exit(1);
    }else{
        printf("Invalid option,try again\n");
        home();
    }
}

void login(){
    if(globalindex==-1){
        printf("No one login yet,Please register first\n");
        home();
    }else{
        char array[limit];
        while(true){
            printf("Enter your email:");
            scanf(" %[^\n]",&array);
            int check=emailValid(array);
            if(check!=1){
                printf("Your email is not valid\n");
            }else{
                break;
            }
        }
        int check= findingemail(array);
        if(check==-1){
            printf("Your email is not registered\n");
            login();
        }else{
            passwordchecking(check);
            printf("Login success\n");
            printf("Welcome Dear %s\n",info[check].username);
        }
    }
}

int findingemail(char array[limit]){
    int count=0;
    int length= checklength(array);
    for (int i = 0; i <= globalindex; i++) {
        int j= checklength(info[i].email);
        if(length==j){
            for (int k = 0; k < j; k++) {
                if(info[i].email[k]==array[k]){
                    count++;
                }
            }
            if(count==j){
                return i;
            }else{
                count=0;
            }
        }
    }
    return -1;
}

void emailinputting(char array[limit]){
    int i= checklength(array);
    for (int j = 0; j <i; j++) {
        info[globalindex].email[j]=array[j];
    }
}

void passwordchecking(int index){
    char password[limit];
    int count=0;
    printf("Enter your password:");
    scanf(" %[^\n]",&password);
    int i= checklength(password);
    int j= checklength(info[index].password);
    if(i!=j){
        printf("Your password is incorrect,Try again\n");
        passwordchecking(index);
    }else{
        for (int k = 0; k < i; k++) {
            if(password[k]!=info[index].password[k]){
                count=1;
            }
        }
        if(count==1){
            printf("Your password is incorrect,Try again\n");
            passwordchecking(index);
        }
    }
}

void register_account(){
    char email[limit];
    printf("This is register\n");
    while(true){
        printf("Enter your email:");
        scanf(" %[^\n]",&email);
        int check=emailValid(email);
        if(check!=1){
            printf("Your email is not valid\n");
        }else{
            break;
        }
    }
    int point=findingemail(email);
    if(point!=1){
        printf("Your email is already registered\n");
        globalindex-=1;
        home();
    }else{
        emailinputting(email);
        passwordConfirm();
        usernameValid();
        ageValid();
        dataSaving();
        printf("You are new user now\n");
    }
}