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
record_link* (createRecordLink(char*));
void printRecords(char*);
char* createStructPtr(char* token);
void printLinkedList(record_link*);
void createFile(record_link*, char*, char*);

///FUNCTIONS///

void printRecords(char* fileName){
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
    printLinkedList(head);
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
        printf("Record: \n");
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
