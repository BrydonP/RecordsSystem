
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
    //Menu Prompt

    //     printf("\nPlease select:");
    //     printf("\n1.\tList records");
    //     printf("\n2.\tSort records");
    //     printf("\n3.\tFind records");
    //     printf("\n4.\tAdd record");
    //     printf("\n5.\tDelete record");
    //     printf("\nPlease select operation: ");
    //     
    //     //if sort
    //     printf("\nPlease select sort by attribute (1=SIN, 2=First Name, 3=Last Name, 4=Annual Income)");
    //     
    //     //if order
    //     printf("\nPlease select order (1=Ascending, 2=Descending)");

    /* 
     * ==============START================
     * =========Open chosen records File=========
     * ==================================
     */
    FILE* fin;
    char fileName[MAX_LEN];
    //Prompt to get filename
    printf("File to load records from: \n");
    //Input Variable
//    fgets(fileName, MAX_LEN, stdin);
//    FLUSH;
//    RMN(fileName);
    


    // List Records    
    char recordName[] = "records.csv";
    record_link* head = createRecords(recordName);
//    printLinkedList(head);

    
    
    // Add Record
//    addRecord(head);
//    char input[MAX_LEN];
//    do{
//        printf("Would you like to add another record? (Y/N)\n");
//        fgets(input, MAX_LEN, stdin);
//        FLUSH;
//        RMN(input);  
//        if(input[0] == 'Y'){
//            addRecord(head);
//        }else{
//            printf("Please choose Y or N");
//        }                    
//    }while(input[0] == 'Y');
    
    
    

    
    
    //Delete Record
//    record_link* head =  deleteRecord(recordName);
    
    


    
    
    //Sort Records
    
    record_BST_node* headBST = sortRecords(head, 1);
    printf("Ascending: \n");
    inorderPrint(headBST);
    printf("Descending: \n");
    reverseOrderPrint(sortRecords(head, 0));
    
    
    
    
    
    
    //Print Records
//    printLinkedList(head);
    
    
    return 0;
    
    
    /* 
     * ==============START================
     * =========Save displayed records===========
     * ==================================
     */
    char line [1000];
    printf("\nSave displayed records in the file (press Enter to skip):");
    char newFileName[MAX_LEN];
    //Input Variable
    fgets(newFileName, MAX_LEN, stdin);
    FLUSH;
//    RMN(buffer);

    if (newFileName != "\n") {

        FILE* fout;
        //Name of output file output csv must be change to variable so its dynamic
        fout = fopen(newFileName, "w");
        //Check for any problem creating the new csv file
        if (fout == NULL) {
            perror("Error opening output file\n");
            system("pause");
            exit(1);

        }
        //Creates the header of the file
        fprintf(fout, "ID,FirstName,LastName,Number\n");

        //Goes through all the lines and prints them into the new file skipping the header
        while (fgets(line, sizeof (line), fin) != NULL) {
            fputs(line, fout);
        }
        printf("\nData saved in the file name of file");
        
        //closes output file
         fclose(fout);


    }


    
   
   
    /* 
     * ===============END================
     * =========Save displayed records===========
     * ==================================
     */


    return 0;
}


