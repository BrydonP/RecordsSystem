
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.c"

#define FLUSH stdin=freopen(NULL,"r",stdin)
#define RMN(str) str[strcspn(str,"\n")]=0
#define MAX_LEN 50


int main() {
    FILE* fin;
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
            printf("Ascending or Descending?\n 1 - Ascending\n0 - Descending\n");
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
        }while(choice[0] != '1' && choice[0] != '2');    
    }else if(menuChoiceInt == 3){
        //Find Records        
        record_link* findHead = createRecords(fileName); //Create LL
        stack_t* searchResults = searchRecords(findHead);
        printStack(searchResults);
    }else if(menuChoiceInt == 4){
        //Add Record
        record_link* head = createRecords(fileName);
        addRecord(head);
        char input[MAX_LEN];
        do{
           printf("Would you like to add another record? (Y/N)\n");
           fgets(input, MAX_LEN, stdin);
           FLUSH;
           RMN(input);  
           if(input[0] == 'Y'){
               addRecord(head);
           }else{
               printf("Please choose Y or N");
           }                    
       }while(input[0] == 'Y');           
    }else if(menuChoiceInt == 5){
        //Delete
        record_link* head =  deleteRecord(fileName);
    }else{
        printf("Bad Menu Selection!!\n");
    }
    
    
    
    

    return 0;
}

    /* 
     * ==============START================
     * =========Save displayed records===========
     * ==================================
     */
//    char line [1000];
//    printf("\nSave displayed records in the file (press Enter to skip):");
//    char newFileName[MAX_LEN];
//    //Input Variable
//    fgets(newFileName, MAX_LEN, stdin);
//    FLUSH;
////    RMN(buffer);
//
//    if (newFileName != "\n") {
//
//        FILE* fout;
//        //Name of output file output csv must be change to variable so its dynamic
//        fout = fopen(newFileName, "w");
//        //Check for any problem creating the new csv file
//        if (fout == NULL) {
//            perror("Error opening output file\n");
//            system("pause");
//            exit(1);
//
//        }
//        //Creates the header of the file
//        fprintf(fout, "ID,FirstName,LastName,Number\n");
//
//        //Goes through all the lines and prints them into the new file skipping the header
//        while (fgets(line, sizeof (line), fin) != NULL) {
//            fputs(line, fout);
//        }
//        printf("\nData saved in the file name of file");
//        
//        //closes output file
//         fclose(fout);
//
//
//    }


//    return 0;
//}


