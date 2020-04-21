#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "functions.h"

#define MAX_LEN 50
#define FLUSH stdin=freopen(NULL,"r",stdin)
#define RMN(str) str[strcspn(str,"\n")]=0

///STRUCUTRES///

//Basic Structure
typedef struct { 
    char* sin; 
    char* firstName; 
    char* lastName; 
    char* salary;
} stack_t; 

//Structure As LL Link
typedef struct link record_link;
struct link{ 
    char* sin; 
    char* firstName; 
    char* lastName; 
    char* salary;
    record_link *link;
}; 

//Structure as BST Node
typedef struct node record_BST_node;
struct node{ 
    char* sin; 
    char* firstName; 
    char* lastName; 
    char* salary;
    record_BST_node *leftChild;
    record_BST_node *rightChild;
};

///SIGNATURES///
//LIST
record_link* (createRecordLink(char*));
record_link* createRecords(char*);
char* createStructPtr(char* token);
void printLinkedList(record_link*);
void createFile(record_link*, char*, char*);

//ADD
void addRecord(record_link*);

//Delete
void deleteHead(record_link**);
record_link* deleteRecord(char*);

//Sort
record_BST_node* sortRecords(record_link*, int);
record_BST_node* convertLinkToBST(record_link*);
record_BST_node* insertNode(record_BST_node*, record_BST_node*);
void inorderPrint(record_BST_node*);
void reverseOrderPrint(record_BST_node*);
///FUNCTIONS///

record_link* createRecords(char* fileName){
    FILE* file = fopen(fileName, "r"); 
    if (file == NULL) {
        printf("Error opening input file\n");
        exit(-1);
    }
    char buffer[1024];    
    record_link* head = NULL; 
    record_link* current = NULL;
    record_link* temp = NULL;
    char* header = fgets(buffer, sizeof(buffer), file);//Store Header
   
    while(fgets(buffer, sizeof(buffer), file) != NULL){//EOF Code
        current = createRecordLink(buffer);
        if(head == NULL){
          head = current;
          temp = current;
        }else{
            temp->link = current;
            temp = current;            
        }
   }
    temp->link = NULL; //Terminate Last Link
    fclose(file);
    return head;
}

record_link* createRecordLink(char* input){
    char* token = strtok(input, ",");    
    char* ptr = (char*) calloc(strlen(token)+1, sizeof(char));
    if(ptr == NULL){
        printf("Memory Allocation Failed\n");
        exit(-1);
    }
    //Verification SIN
    if(strlen(token) != 9){
        printf("Bad Data");
        exit(-1);
    }
    strcpy(ptr, token);  
    
    // Verification First Name
    record_link* link = (record_link*)malloc(sizeof(record_link));   
    link->sin = ptr;
    link->firstName = createStructPtr(token);
    link->lastName = createStructPtr(token);
    link->salary = createStructPtr(token);
    return link;
}

char* createStructPtr(char* token){
    token = strtok(NULL, ",");
    if(strlen(token) == 0){//Verify
        printf("Bad Data");
        exit(-1);
    }
    char* ptr = (char*) calloc(strlen(token)+1, sizeof(char));
    if(ptr == NULL){
        printf("Memory Allocation Failed\n");
        exit(-1);
    }
    strcpy(ptr, token);    
    return ptr;
}

void printLinkedList(record_link* head){
    record_link* current = head;
    record_link* temp = NULL;
   //Print All Records
    while(current != NULL){
        printf("\nRecord: \n");
        printf("SIN: %s\n", current->sin);
        printf("First Name: %s\n", current->firstName);
        printf("Last Name: %s\n", current->lastName);
        printf("Salary: %s\n", current->salary);
        temp = current;
        current = current->link;
        free(temp);
    }
}


void createFile(record_link* node, char* fileName, char* header){
    FILE* fout = fopen(fileName, "w");
    fprintf(fout, "%s\n", header);//Print Header
    while(node != NULL){//Print All records 
        fputs(node->sin,fout);
        fputs(node->firstName,fout);
        fputs(node->lastName,fout);
        fputs(node->salary,fout);
        node = node->link;
    }
    fclose(fout);//Close File
    printf("%s has been saved\n", fileName);
}

void addRecord(record_link* head){
    record_link* node = head;
    
    //traverse to the end of the LL
    while(node->link != NULL){
        node = node->link;
    }
    printf("Adding a new record:\n");
    
    //SIN
    char sin[MAX_LEN];    
    do{
        printf("SIN: ");
        fgets(sin, MAX_LEN, stdin);     
        FLUSH;
        RMN(sin);
        if(strlen(sin) != 9){
            printf("Incorrect SIN, Please try again\n");            
        }
    }while(strlen(sin) != 9);
    
    //First Name
    char firstName[MAX_LEN];
    do{
        printf("First name: ");
        fgets(firstName, MAX_LEN, stdin);  
        FLUSH;
        RMN(firstName); 
        if(strlen(firstName) == 0){
            printf("Cannot be empty\n");
        }
    }while(strlen(firstName) == 0);

    
    //Last Name
    char lastName[MAX_LEN];
    do{
        printf("Last name: ");
        fgets(lastName, MAX_LEN, stdin);  
        FLUSH;
        RMN(lastName);         
        if(strlen(lastName) == 0){
            printf("Cannot be empty\n");
        }
    }while(strlen(lastName) == 0);
 
    
    //Salary
    char salary[MAX_LEN];
    do{
        printf("Salary: ");
        fgets(salary, MAX_LEN, stdin);  
        FLUSH;
        RMN(salary);  
        if(strlen(salary) == 0){
            printf("Cannot be empty\n");
        }
    }while(strlen(salary) == 0);
        
    printf("Record Added\n");
    
    char temp[MAX_LEN*4];
    strcpy(temp,sin);
    strcat(temp,",");
    strcat(temp,firstName);
    strcat(temp,",");
    strcat(temp,lastName);
    strcat(temp,",");
    strcat(temp,salary);    
    node->link = createRecordLink(temp);
    node->link->link = NULL;
}

void deleteHead(record_link** head){
    record_link* toDelete = *head;
    *head = (*head)->link;
    free(toDelete->sin);
    free(toDelete->firstName);
    free(toDelete->lastName);
    free(toDelete->salary);
    free(toDelete);
}

record_link* deleteRecord(char* recordName){
    record_link* headDelete = createRecords(recordName);
    char deleteChoice[MAX_LEN];
    int deleteChoiceInt = 0;
    char key[MAX_LEN];
    record_link* node = headDelete;
    record_link* previous = headDelete;

    
    do{
        printf("Which value would you like to delete by?\n");
        printf("1. SIN \n2. First Name \n3. Last Name \n4. Salary\n");
        fgets(deleteChoice, MAX_LEN, stdin);
        FLUSH;
        RMN(deleteChoice);  
        deleteChoiceInt = strtol(deleteChoice, NULL, 10);
        if(deleteChoiceInt > 5 || deleteChoiceInt < 1){
            printf("Please a number from 1-4\n");
        }
    }while(deleteChoiceInt > 5 || deleteChoiceInt < 1);
    printf("What do you want to search? ");
    fgets(key, MAX_LEN, stdin);
    FLUSH;
    RMN(key);   

            
    if(deleteChoice[0] == '1'){
            while(node != NULL){
                if(!strcmp(key,node->sin)){
                    if(node == headDelete){
                        deleteHead(&headDelete);    
                        previous = headDelete;
                        node = node->link;
                    }
                    break;
                }                
                previous = node;
                node = node->link;
            }       
    }        
    
    if(deleteChoice[0] == '2'){
            while(node != NULL){
                if(!strcmp(key,node->firstName)){  
                    if(node == headDelete){
                        deleteHead(&headDelete);        
                        previous = headDelete;
                        node = node->link;                   
                    }
                    break;
                }                
                previous = node;
                node = node->link;
            }       
    }
    
    if(deleteChoice[0] == '3'){
            while(node != NULL){
                if(!strcmp(key,node->lastName)){
                    if(node == headDelete){
                        deleteHead(&headDelete);       
                        previous = headDelete;
                        node = node->link;                    
                    }
                    break;
                }                
                previous = node;
                node = node->link;
            }       
    }
    
    if(deleteChoice[0] == '4'){
            while(node != NULL){
                if(!strcmp(key,node->salary)){  
                    if(node == headDelete){
                        deleteHead(&headDelete);        
                        previous = headDelete;
                        node = node->link;                   
                    }
                    break;
                }                
                previous = node;
                node = node->link;
            }       
    }    
    
    //Repair Link
    previous->link = node->link;
    
    //Delete / Free Memory
    free(node->sin);
    free(node->firstName);
    free(node->lastName);
    free(node->salary);
    free(node);

    return headDelete;
}


record_BST_node* sortRecords(record_link* oldHead, int direc){    
    //direction 1 = ascending 0 = descending
    record_BST_node* head = NULL;
    record_BST_node* currentNode = head;
    record_BST_node* newNode;
    record_link* nextLink = NULL;
    
    if(head == NULL){
        nextLink = oldHead->link;
        head = convertLinkToBST(oldHead);
        currentNode = head;
    }
  
    if(direc){//Ascending
        while(nextLink != NULL){
            newNode = convertLinkToBST(nextLink);
            insertNode(head, newNode);
            nextLink = nextLink->link; //Set Next Link
        }
    }else{//Descending
        while(nextLink != NULL){
            newNode = convertLinkToBST(nextLink);
            insertNode(head, newNode);
            nextLink = nextLink->link; //Set Next Link
        }
    }
    
    return head;
}



record_BST_node* convertLinkToBST(record_link* old){
    record_BST_node* newNode = (record_BST_node*) malloc(sizeof(record_BST_node));
    if(newNode == NULL){
        printf("Not enough memory for BST_Node");
        exit(-1);
    }
    newNode->sin = old->sin;
    newNode->firstName = old->firstName;
    newNode->lastName = old->lastName;
    newNode->salary = old->salary;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}



record_BST_node* insertNode(record_BST_node* currentNode, record_BST_node* newNode){
    if(currentNode == NULL){
        return newNode;
    }    
    if(strtol(newNode->sin,NULL,10) < strtol(currentNode->sin,NULL,10)){
        currentNode->leftChild = insertNode(currentNode->leftChild, newNode);
    }else{
        currentNode->rightChild = insertNode(currentNode->rightChild, newNode);
    }  
    return currentNode;
}

void inorderPrint(record_BST_node* root){
    if(root !=NULL){
        inorderPrint(root->leftChild);
        printf("SIN: %s\n", root->sin);
        inorderPrint(root->rightChild);
    }
}

void reverseOrderPrint(record_BST_node* root){
    if(root !=NULL){
        reverseOrderPrint(root->rightChild);
        printf("SIN: %s\n", root->sin);
        reverseOrderPrint(root->leftChild);
    }
}