
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"
#include "functions.c"


#define FLUSH stdin=freopen(NULL,"r",stdin)
#define RMN(str) str[strcspn(str,"\n")]=0
#define MAX_LEN 50


int main() {
    char fileName[MAX_LEN];
    printf("File to load records from: \n");
    //Input Variable
    fgets(fileName, MAX_LEN, stdin);
    FLUSH;
    RMN(fileName);

    char menuChoice[MAX_LEN];
    int menuChoiceInt;
    do{
        //Menu Prompt
        printf("\nPlease select:");
        printf("\n1.\tList records");
        printf("\n2.\tSort records");
        printf("\n3.\tFind records");
        printf("\n4.\tAdd record");
        printf("\n5.\tDelete record");
        printf("\nPlease select operation: ");

        fgets(menuChoice, MAX_LEN, stdin);
        FLUSH;
        RMN(menuChoice);
        menuChoiceInt = strtol(menuChoice,NULL, 10);
        if(menuChoiceInt < 1 || menuChoiceInt > 6){
            printf("Please Select an option listed above 1-5\n");
        }    
    }while(menuChoiceInt < 1 || menuChoiceInt > 6);
    

    if(menuChoiceInt == 1){
        //List Records
        //char recordName[] = "records.csv";
        record_link* head = createRecords(fileName);
        printLinkedList(head);  
    }else if(menuChoiceInt == 2){
        //Sort Records
        record_link* sortHead = createRecords(fileName);
        record_BST_node* headBST = sortRecords(sortHead);
        char choice[MAX_LEN];   
        do{
            printf("Ascending or Descending?\n1 - Ascending\n0 - Descending\n");
            fgets(choice, MAX_LEN, stdin);
            FLUSH;
            RMN(choice);
            if(choice[0] == '1'){
                printf("Ascending: \n");
                inorderPrint(headBST);
            }else if(choice[0] == '0'){
                printf("Descending: \n");
                reverseOrderPrint(headBST);            
            }else{
                printf("Please select 1 or 0\n");
            }   
        }while(choice[0] != '1' && choice[0] != '0');  
    }else if(menuChoiceInt == 3){
        //Find Records        
        record_link* findHead = createRecords(fileName); //Create LL
        stack_t* searchResults = searchRecords(findHead);
//        printStack(searchResults);
        saveFileFromStack(searchResults, newFile());
    }else if(menuChoiceInt == 4){
        //Add Record
        record_link* head = createRecords(fileName);
        addRecord(head); 
        saveFile(head, newFile());
    }else if(menuChoiceInt == 5){
        //Delete
        record_link* head =  deleteRecord(fileName);
        saveFile(head, newFile());
    }else{
        printf("Bad Menu Selection!!\n");
    }
    
    
    
    

    return 0;
}
