#include "wordHuntSolver4.h"






int main(int argc, char *argv[])
{
//printf("Welcome to the Word Hunt Solver!\n");
// We can take in the filename as an argument or have it typed in by the user
    char filename[200];
    if (argc >= 2){ 
        strcpy(filename, argv[1]);
    } else {
        char temp[100];
        //printf("Please type in the wordlist you intend to use. Make sure to include .txt at the end:\n");
        strcpy(filename, ".\\WordLists\\");
        scanf("%s", temp);
        strcat(filename, temp);
    }
    //printf("%s\n", filename);
    TrieNode * root = load_trie(filename);

// We can take in the input either as an argument or typed in by the user
    char input[20];
    if (argc >= 3){
        strcpy(input, argv[2]);
    } else {
        printf("Please input the 16 letter grid, from Left -> Right, Top -> Bottom:\n");
        scanf("%16s", input);
    }
    for (int i = 0; i < 17; i++){
        input[i] = toupper(input[i]);
    }
    //printf("Input: %s\n", input);

    
    // We search for the words in the trie
    HashNode * solutions = makeHashTable();
    for (int row = 0; row < 4; row++){
        for (int col = 0; col < 4; col++){
            bool visited[4][4] = {false};
            char * tempWord = (char *) malloc(20*sizeof(char));
            strcpy(tempWord, "");
            combo(row, col, tempWord, input, visited, root, solutions);
            free(tempWord);
        }
    }

    
    // put all of the solutions into an array
    char sortedSolutions[500][20];
    int numSolutions = 0;
    hashTreeToArray(solutions->left, sortedSolutions, &numSolutions);
    hashTreeToArray(solutions->right, sortedSolutions, &numSolutions);
    
    freeHashNode(solutions);


    
    // sorts the solutions from longest to shortest
    //printf("Sorting solutions...\n");
    for(int i = 0; i < numSolutions; i++){
        for(int j = i+1; j < numSolutions; j++){
            if(strlen(sortedSolutions[i]) < strlen(sortedSolutions[j])){
                char temp[16];
                strcpy(temp, sortedSolutions[i]);
                strcpy(sortedSolutions[i], sortedSolutions[j]);
                strcpy(sortedSolutions[j], temp);
            }
        }
    }

    // Now we print the solutions to the file genAnswers.txt
    //printf("Printing solutions to file...\n");
    FILE * fp = fopen("genAnswers.txt", "w");
    fprintf(fp, "Num Solutions: %d\n", numSolutions);
    for(int i = 0; i < numSolutions; i++)
        if(strcmp(sortedSolutions[i], "") != 0)
        fprintf(fp, "%ld: %s\n", strlen(sortedSolutions[i]), sortedSolutions[i]);
    //printf("Total number of solutions: %d\n", numSolutions);
    fclose(fp);




    // We free the memory allocated for the trie
   free_trienode(root);

    return 0;
}




TrieNode* make_trienode(char data) {
    // Allocate memory for a TrieNode
    TrieNode* node = (TrieNode*) malloc(sizeof(TrieNode));
    node->children = (TrieNode**) malloc(26 * sizeof(TrieNode*));
    for (int i=0; i<26; i++) {
        node->children[i] = NULL;
    }
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
    }
    free(node->children);
    free(node);
}

// Inserts a word into the trie, returning the root node
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

// Takes a file path to a wordlist and constructs a trie, returns the root
TrieNode * load_trie(char * filename){
    FILE *fp;
    fp = fopen(filename, "r");
    if(fp == NULL){
        for (int i = 0; i < strlen(filename); i++){
            if(filename[i] == '\\'){
                filename[i] = '/';
            }
        }
        fp = fopen(filename, "r");
    } if (fp == NULL)
    {
        printf("Error opening file. Please make sure the file is in the same directory as the program and try again.\n");
        exit(1);
    }
    //printf("File opened successfully\n");
    TrieNode *root = make_trienode('\0');
    char word[20];

    //printf("Parsing file...\n");
    int counter = 0;
    while(fscanf(fp, "%s", word) == 1)
    {
        //printf("Word %d: %s\n", counter++, word); 
        root = insert_trie(root, word);
    }
    //printf("File parsed successfully\n");
    //printf("------------------------\n");
    fclose(fp);

    return root;
}

// Takes a 4x4 grid of bools to see if we already went over a letter
void combo(int row, int col, char *word, char *board, bool visited[4][4], TrieNode *root,  HashNode * solutions){
    //printf("Row: %d Col: %d\n", row, col);
    // Tests for edge cases and if we loop over the same letter
    if(row < 0 || row >= 4 || col < 0 || col >= 4){
        return;
    }
    if (visited[row][col]){
        return;
    }
    // Since the board is stored in a 1d array, we need to convert the 2d coordinates to 1d
    //printf(visited[row][col] ? "Visited: True \n" : "Visited: False \n");
    visited[row][col] = true;
    // Add the letter to the current combination of letters
    int length = strlen(word);
    word[length] = board[row*4 + col];
    word[length + 1] = '\0';
    //printf("Current Word: %s ", word);


    // Check if the word is in the trie
    int result = search_trie(root, word);
    //printf(" Result: %d\n", result);
    if (result == 1)
    {
        // If it is, add it to the solutions array
        insertHashNode(solutions, word);
    } else if (result == 0)
    {
        // if it isn't a prefix, we can stop iterating through the letters.
        // We also need to reset the visited array
        visited[row][col] = false;
        word[strlen(word) - 1] = '\0';
        return;
    }
    // If it is a prefix, we need to continue iterating through the letters
    // Recursively call the function on all the adjacent letters
    combo(row - 1, col - 1, word, board, visited, root, solutions);
    combo(row - 1, col, word, board, visited, root, solutions);
    combo(row - 1, col + 1, word, board, visited, root, solutions);
    combo(row, col - 1, word, board, visited, root, solutions);
    combo(row, col + 1, word, board, visited, root, solutions);
    combo(row + 1, col - 1, word, board, visited, root, solutions);
    combo(row + 1, col, word, board, visited, root, solutions);
    combo(row + 1, col + 1, word, board, visited, root, solutions);
    // Reset the visited array for the letter since it has gone through all possible combinations
    visited[row][col] = false;
    word[strlen(word) - 1] = '\0';
}

int calculateHash(char * word){
  int counter, hashAddress = 0;
  for (counter =0; word[counter]!='\0'; counter++){
    hashAddress = hashAddress*word[counter] + word[counter] + counter;
  }
  return hashAddress;
}

HashNode * makeHashNode(char * word){
    HashNode * newNode = (HashNode *) malloc(sizeof(HashNode));
    newNode->hash = calculateHash(word);
    newNode->name = (char *) malloc(20);
    strcpy(newNode->name, word);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

HashNode * makeHashTable(){
    HashNode * root = makeHashNode("");
    return root;
}

// Returns 0 if hash is already in, 1 if successfully added.
int insertHashNode(HashNode * root, char * word){
    HashNode * newNode = makeHashNode(word);
    HashNode * previous = root;
    HashNode * temp = root;

    while(temp != NULL){
        if(temp->hash == newNode->hash){
            //printf("%s already in table\n", word);
            freeHashNode(newNode);
            return 0;
        }
        previous = temp;
        if (temp->hash < newNode->hash)
            temp = temp->right;
        else
            temp = temp->left;
    }

    if (previous->hash < newNode->hash)
            previous->right = newNode;
        else
            previous->left = newNode;

    //printf("Inserted %s with Hash %d\n", newNode->name, newNode->hash);
    return 1;
}

void hashTreeToArray(HashNode * root, char solutions[500][20], int * numSolutions){
    if (root == NULL){
        return;
    }

    //printf("Adding %s to array\n", root->name);
    strcpy(solutions[*numSolutions], root->name);
    //printf("Added %s to array\n", solutions[*numSolutions]);
    *numSolutions += 1;
    //printf("NumSolutions: %d\n", *numSolutions);

    hashTreeToArray(root->left, solutions, numSolutions);
    hashTreeToArray(root->right, solutions, numSolutions);
}

void freeHashNode(struct HashNode_s * node){
    if (node == NULL){
        return;
    }
    free(node->name);
    freeHashNode(node->left);
    freeHashNode(node->right);
    free(node);
}