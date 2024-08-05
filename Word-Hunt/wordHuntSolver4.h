#ifndef WORDHUNTSOLVER
#define WORDHUNTSOLVER


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
//#include <windows.h>
//#include <unistd.h>


typedef struct TrieNode_s{
    char data;
    struct TrieNode_s ** children;
    int is_leaf;
} TrieNode;

typedef struct HashNode_s{
    int hash;
    char * name;
    struct HashNode_s * left;
    struct HashNode_s * right;
} HashNode;




TrieNode * make_trienode(char data); // Allocates memory for a new TrieNode and returns a pointer to it
void       free_trienode(TrieNode* node); // Frees the memory allocated for a TrieNode
TrieNode * insert_trie(TrieNode* root, char* word); // Inserts a word into the Trie
int        search_trie(TrieNode * root, char* word); // returns 1 if a word exists within the tree
void       print_trie(TrieNode* root); 
void       print_search(TrieNode* root, char* word);
void       combo(int row, int col, char *word, char *board, bool visited[4][4], TrieNode *root,  HashNode * solutions);

TrieNode * load_trie(char * filename);

void hashTreeToArray(HashNode * root, char solutions[500][20], int * numSolutions);
int insertHashNode(HashNode * root, char * word);
HashNode * makeHashTable();
HashNode * makeHashNode(char * word);
int calculateHash(char * word);
void freeHashNode(struct HashNode_s * node);

#endif