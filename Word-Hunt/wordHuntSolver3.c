#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
//#include <windows.h>
#include <unistd.h>
#define lengt 500;

// We start by making a 26-aray tree since we have 26 letters in the alphabet
// Each TrieNode will have 26 children and a flag to check if it's a leaf
typedef struct TrieNode_s{
    char data;
    struct TrieNode_s* children[26];
    int is_leaf;
} TrieNode;


TrieNode * make_trienode(char data); // Allocates memory for a new TrieNode and returns a pointer to it
void free_trienode(TrieNode* node); // Frees the memory allocated for a TrieNode
TrieNode* insert_trie(TrieNode* root, char* word); // Inserts a word into the Trie
int search_trie(TrieNode * root, char* word); // returns 1 if a word exists within the tree
void print_trie(TrieNode* root); 
void print_search(TrieNode* root, char* word);
void combo(int row, int col, char *word, char *board, bool visited[4][4], TrieNode *root,  int *num_solutions, char solutions[500][16]);

TrieNode * load_trie(char * filename);



int main(int argc, char * argv[]) {

    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[1]);
        exit(1);
    }

    // Load the trie from the file
    TrieNode* root2 = load_trie(argv[1]);

    char choice = 'y';
    char board[16];
    char solutions[500][16];
        for(int i = 0; i < 500; i++)
                strcpy(solutions[i], "");

    int num_solutions = 0;

    while(choice == 'y'){
        // have the user input what letters are on the board
        // search the trie for all the words that can be made
        printf("Enter the letters on the board from  left -> right, top -> bottom : ");
        scanf("%16s", board);
        for(int i = 0; i < 16; i++)
            board[i] = toupper(board[i]);


        // now we pass each letter in the board to the combo function
        for(int row=0; row<4; row++){
            for(int col=0; col<4; col++){
                bool visited[4][4] = {false};
                char word[16] = "";
                combo(row, col, word, board, visited, root2, &num_solutions, solutions);
            }
        }

        // sorts the solutions from longest to shortest
        for(int i = 0; i < num_solutions; i++){
            for(int j = i+1; j < num_solutions; j++){
                if(strlen(solutions[i]) < strlen(solutions[j])){
                    char temp[16];
                    strcpy(temp, solutions[i]);
                    strcpy(solutions[i], solutions[j]);
                    strcpy(solutions[j], temp);
                }
            }
        }

        // sorts the solutions longest to shortest and removes any repeated words
        for(int i = 0; i < num_solutions; i++){
            for(int j = i+1; j < num_solutions; j++){
                if (strcmp(solutions[j], "") != 0  && strcmp(solutions[i], solutions[j]) == 0){
                        strcpy(solutions[j], "");
                        num_solutions--;
                } 
                if (strlen(solutions[i]) < strlen(solutions[j])){
                    char temp[16];
                    strcpy(temp, solutions[i]);
                    strcpy(solutions[i], solutions[j]);
                    strcpy(solutions[j], temp);
                    
                }
            }
        }




        // Now we print the solutions
        for(int i = num_solutions-1; i >= 0; i--)
            printf("%ld: %s\n", strlen(solutions[i]), solutions[i]);
        printf("Total number of solutions: %d\n", num_solutions);


        printf("Would you like to try another list? (y/n): ");
        scanf(" %c", &choice);
        printf("\n------------------------------------\n\n\n");

        // Resets the number of solutions
        num_solutions = 0;
    }
    free_trienode(root2);
    return 0;
}


TrieNode* make_trienode(char data) {
    // Allocate memory for a TrieNode
    TrieNode* node = (TrieNode*) calloc (1, sizeof(TrieNode));
    for (int i=0; i<26; i++)
        node->children[i] = NULL;
    node->is_leaf = 0;
    node->data = data;
    return node;
}

void free_trienode(TrieNode* node) {
    // Free the trienode sequence
    for(int i=0; i<26; i++) {
        if (node->children[i] != NULL) {
            free_trienode(node->children[i]);
        }
        else {
            continue;
        }
    }
    free(node);
}

TrieNode* insert_trie(TrieNode* root, char* word) {
    // Inserts the word onto the Trie
    // ASSUMPTION: The word only has lower case characters
    TrieNode* temp = root;


    for (int i=0; word[i] != '\0' && word[i] != ' '; i++) {
        // finds the index of the character in the children array
        // It took me an hour to figure out why the file wasn't parsing and I was getting a segmentation fault
        // It turns out I was using 'a' instead of 'A' to get the index of the character causing an out of bounds
        if (temp->children[word[i] - 'A'] == NULL) {
            // If the corresponding child doesn't exist, we create that child
            temp->children[word[i] - 'A'] = make_trienode(word[i]);
        }
        temp = temp->children[word[i] - 'A'];
    }
    // At the end of the word, mark this node as the leaf node
    temp->is_leaf = 1;
    return root;
}

// Returns 1 if the word exists in the trie, 0 if it doesn't, 2 if word is a prefix
int search_trie(TrieNode* root, char* word)
{
    // Searches for word in the Trie
    TrieNode* temp = root;

    for(int i=0; word[i]!='\0'; i++)
    {
        int position = word[i] - 'A';
        if (temp->children[position] == NULL)
            return 0;
        else
            temp = temp->children[position];
    }
    if (temp != NULL && temp->is_leaf == 1)
        return 1;
    return 2;
}

void print_trie(TrieNode* root) {
    // Prints the nodes of the trie
    if (!root)
        return;
    TrieNode* temp = root;
    printf("%c -> ", temp->data);
    for (int i=0; i<26; i++) {
        print_trie(temp->children[i]); 
    }
}

void print_search(TrieNode* root, char* word) {
    printf("Searching for %s: ", word);
    if (search_trie(root, word) == 0)
        printf("Not Found\n");
    else if (search_trie(root, word) == 2)
        printf("Prefix Found\n");
    else
        printf("Found!\n");
}




TrieNode * load_trie(char * filename){
    printf("Please make sure the words are in ALL CAPS or else there will be a segment fault.\n");
    printf("Enter the name of your word list file without the \".txt\" extension: ");
    FILE *fp;
    /*
    scanf("%s", filename);
    //appends ".txt" to the filename
    strcat(filename, ".txt");
    fp = fopen(filename, "r");
    */
    fp = fopen(filename, "r");
    
    while(fp == NULL)
    {
        printf("Error opening file. Please make sure the file is in the same directory as the program and try again.\n");
        exit(1);
    }
        printf("File opened successfully\n");

    TrieNode *root = make_trienode('\0');
    char word[20];

    int counter = 0;
    while(fscanf(fp, "%s", word) == 1)
    {
        // printf("Word %d: %s\n", counter++, word); 
        root = insert_trie(root, word);
    }

    printf("File parsed successfully\n");
    printf("------------------------\n\n\n\n\n\n\n");

    fclose(fp);

    return root;
}

// Takes a 4x4 grid of bools to see if we already went over a letter
void combo(int row, int col, char *word, char *board, bool visited[4][4], TrieNode *root,  int *num_solutions, char solutions[500][16]){
    // Tests for edge cases and if we loop over the same letter
    if(row < 0 || row >= 4 || col < 0 || col >= 4 || visited[row][col])
    {
        return;
    }
    // Since the board is stored in a 1d array, we need to convert the 2d coordinates to 1d
    char letter = board[row*4 + col];
    visited[row][col] = true;

    // Add the letter to the current combination of letters
    char * temp = (char*) calloc (strlen(word) + 1, sizeof(char));
    strcpy(temp, word);
    temp[strlen(temp)] = letter;




    /*
    // DEBUGGING ----------------------------------------------- DEBUGGING

    //print out the current combination of letters and coordinates
    printf("Current word: %s Current Cord: [%d][%d] \n", temp, row, col);
    //print out the visited board
    printf("Visited board: \n");
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            printf("%d ", visited[i][j]);
        }
        printf("\n");
    }

    // There seems to be an issue where the visited board is not being reset properly after all calls
    // to combo are done for a given letter.

    // DEBUGGING ----------------------------------------------- DEBUGGING
    */




    // Check if the word is in the trie
    int result = search_trie(root, temp);
    if (result == 1)
    {
        // If it is, add it to the solutions array
        strcpy(solutions[*num_solutions], temp);
        //printf("Solution %d: %s\n", *num_solutions, solutions[*num_solutions]); //debugging -----------------------------------------------
        (*num_solutions)++;
    } else if (result == 0)
    {
        // if it isn't a prefix, we can stop iterating through the letters.
        // We also need to reset the visited array
        visited[row][col] = false;
        return;
    }
    
    // If it is a prefix, we need to continue iterating through the letters
    // Recursively call the function on all the adjacent letters
    combo(row - 1, col - 1, temp, board, visited, root, num_solutions, solutions);
    combo(row - 1, col, temp, board, visited, root, num_solutions, solutions);
    combo(row - 1, col + 1, temp, board, visited, root, num_solutions, solutions);
    combo(row, col - 1, temp, board, visited, root, num_solutions, solutions);
    combo(row, col + 1, temp, board, visited, root, num_solutions, solutions);
    combo(row + 1, col - 1, temp, board, visited, root, num_solutions, solutions);
    combo(row + 1, col, temp, board, visited, root, num_solutions, solutions);
    combo(row + 1, col + 1, temp, board, visited, root, num_solutions, solutions);

    // Reset the visited array for the letter since it has gone through all possible combinations
    visited[row][col] = false;

    free(temp);
}
