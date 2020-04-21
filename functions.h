#ifndef FUNCTIONS_H

#define FUNCTIONS_H

#define MAX_LEN 50
#define FLUSH stdin=freopen(NULL,"r",stdin)
#define RMN(str) str[strcspn(str,"\n")]=0

///STRUCUTRES///

//Basic Structure

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

//Stack for Search Results
typedef struct { 
    int top; 
    size_t capacity; 
    record_link** array; 
} stack_t; 

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
record_BST_node* sortRecords(record_link*);
record_BST_node* convertLinkToBST(record_link*);
record_BST_node* insertNode(record_BST_node*, record_BST_node*);
void inorderPrint(record_BST_node*);
void reverseOrderPrint(record_BST_node*);

//FIND
////Stack
stack_t* createStack(size_t);
int isFull(stack_t*);
int isEmpty(stack_t*);
void push(stack_t*, record_link*);
record_link* pop(stack_t*);
stack_t* resizeStack(stack_t*); 
record_link* peek(stack_t*);

///
void printStack(stack_t*);
stack_t* searchRecords(record_link*);

//Savings Files
void saveFile(record_link*, FILE*);
FILE* newFile();
void saveFileFromStack(stack_t*, FILE*);
#endif /* FUNCTIONS_H */


