#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
struct node
{
    int data;
    struct node* left;
    struct node* right;
};

int parent(int i) {return (i - 1) / 2;}
int leftChild(int i) {return ((2 * i) + 1);}
int rightChild(int i) {return ((2 * i) + 2);}
// swaps to value
void swap( int *number_1, int *number_2 ) {
    int temp;
    temp = *number_1;
    *number_1 = *number_2;
    *number_2 = temp;}
//shifts bigger number to upper levels
void shiftUp(int index,int *heap)
{
    while (index > 0 && heap[parent(index)] < heap[index]) {
        swap(&heap[parent(index)], &heap[index]);
        index = parent(index);
    }
}
// insert new number to the heap
void insert(int p,int size,int *heap)
{
    size = size + 1;
    heap[size] = p;
    shiftUp(size, heap);
}
// converts max heap to node structure
struct node *create_nodes(int index, int heap[], int size){
    if (index > size) return NULL;
    struct  node * currentNode = calloc(1,sizeof(struct node));
    currentNode->data = heap[index];
    currentNode->left = create_nodes(leftChild(index),heap,size);
    currentNode->right = create_nodes(rightChild(index),heap,size);
    return currentNode;
}
// finds the height of given node
int height(struct node * currentNode){
    if(currentNode == '\0') return 0;
    int length_of_left = height(currentNode->left);
    int length_of_right = height(currentNode->right);
    if(length_of_left>length_of_right) return length_of_left+1;
    else return length_of_right+1;
}
// writes the current level to the file
void printCurrentLevel(struct node * currentNode, int level,FILE * filePointer){
    if(currentNode == '\0') return;
    else if (level ==0) {
        char string[3];
        itoa(currentNode->data,string,10);
        fputs(string, filePointer) ;
        fputs(" ", filePointer) ;}
    else{
        printCurrentLevel(currentNode->left,level-1,filePointer);
        printCurrentLevel(currentNode->right,level-1,filePointer);
    }
}
// traverse the nodes with bfs
void printAllLevels(struct node * currentNode,FILE * filePointer){
    int height_of_node = height(currentNode);
    for(int i =0;i<height_of_node;i++){
        printCurrentLevel(currentNode,i,filePointer);
    }
}

int main( )
{
    int number_of_elements = pow(2,27); // if you will try another number you should change this row, row 82 and row 115
    int number_of_characters = number_of_elements*3;
    int * max_heap; int * array;
    array = (int*) malloc(number_of_elements*sizeof(int));
    int size = 0;
    char filename[] = "2-27integer.txt"; //
    FILE *filePointer;
    char * dataToBeRead;
    dataToBeRead = (char*) malloc(number_of_characters * sizeof(char));
    filePointer = fopen(filename, "r");
    printf("Reading File...\n");
    while( fgets ( dataToBeRead, number_of_characters, filePointer ) != NULL )
    {
        char * token = strtok(dataToBeRead," ");
        while (token!= NULL) {
            int int_token = atoi(token);
            token = strtok(NULL, " ");
            array[size++] = int_token;
        }
    }
    printf("File is read\n");
    printf("Creating Heap...\n");
    free(dataToBeRead);
    fclose(filePointer) ;
    max_heap = (int*) malloc(number_of_elements*sizeof(int));
    clock_t begin = clock();
    for(int i=0;i<size;i++){
        insert(array[i],i-1,max_heap);
    }
    clock_t end = clock();
    free(array);
    printf("Heap is created\n");
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Spent time is %f seconds\n",time_spent);
    struct node * max_node;
    printf("Converting is processing...\n");
    max_node  = create_nodes(0, max_heap, size-1);
    printf("Converting is done\n");
    filePointer = fopen("results_2-27integer.txt", "w") ;
    free(max_heap); printf("Writing the data to the file...\n");
    printAllLevels(max_node,filePointer);
    printf("Data is writen");
    fclose(filePointer);
    free(max_node);
    return 0;
}