#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct TrieNode {
    int index;
    struct TrieNode* children[26]; 
} TrieNode;
TrieNode* createNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->index = -1; 
    for (int i = 0; i < 26; i++)
        node->children[i] = NULL;
    return node;
}

int insertWord(TrieNode* root, const char* word, int currentIndex) {
    TrieNode* current = root;

    for (int i = 0; i < strlen(word); i++) {
        int charIndex = word[i] - 'a'; 
        if (current->children[charIndex] == NULL) {
            current->children[charIndex] = createNode();
        }
        current = current->children[charIndex];
    } if (current->index == -1) {
        current->index = currentIndex; 
        return currentIndex + 1; 
    } return currentIndex; }

int searchWord(TrieNode* root, const char* word) {
    TrieNode* current = root;
    for (int i = 0; i < strlen(word); i++) {
        int charIndex = word[i] - 'a';
        if (current->children[charIndex] == NULL)
            return -1; 
        current = current->children[charIndex];
    }
    return current->index; 
}

void freeTrie(TrieNode* root) {
    for (int i = 0; i < 26; i++) {
        if (root->children[i] != NULL)
            freeTrie(root->children[i]);
    }
    free(root);
}

int main() {
    TrieNode* root = createNode();
    int currentIndex = 0; 
    char* words[] = { "apple", "banana", "grape", "apple", "orange", "banana" };
    int numWords = sizeof(words) / sizeof(words[0]);
    printf("Compactação de palavras:\n");
    for (int i = 0; i < numWords; i++) {
        int index = searchWord(root, words[i]);
        if (index == -1) {
            // Palavra não encontrada, insere na árvore
            currentIndex = insertWord(root, words[i], currentIndex);
            printf("'%s' -> Índice %d (inserido)\n", words[i], currentIndex - 1);
        } else {
            printf("'%s' -> Índice %d (existente)\n", words[i], index); } }
    freeTrie(root);
    return 0;
}
