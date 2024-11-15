#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define ALPHABET_SIZE 26
typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord; 
} TrieNode;

TrieNode* createNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    } return node; }

void insert(TrieNode* root, const char* word) {
    TrieNode* current = root;
    while (*word) {
        int index = *word - 'a';
        if (current->children[index] == NULL) {
            current->children[index] = createNode();
        } current = current->children[index];
        word++;
    } current->isEndOfWord = true;}
bool search(TrieNode* root, const char* word) {
    TrieNode* current = root;
    while (*word) {
        int index = *word - 'a';
        if (current->children[index] == NULL) {
            return false;
        } current = current->children[index];
        word++;
    } return current->isEndOfWord; }
void suggestWords(TrieNode* root, char* prefix, int level) {
    if (root->isEndOfWord) {
        prefix[level] = '\0';
        printf("%s\n", prefix);
    } for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            prefix[level] = 'a' + i;
            suggestWords(root->children[i], prefix, level + 1); } } }

void spellCheck(TrieNode* root, const char* word) {
    if (search(root, word)) {
        printf("A palavra '%s' está correta.\n", word);
    } else {
        printf("A palavra '%s' está incorreta. Sugestões:\n", word);
        TrieNode* current = root;
        char prefix[100];
        strcpy(prefix, word);
        int level = 0;
        while (*word && current) {
            int index = *word - 'a';
            if (current->children[index] == NULL) {
                break;
            } current = current->children[index];
            word++;
            level++; }
        suggestWords(current, prefix, level); } }

int main() {
    TrieNode* root = createNode();
    insert(root, "aba");
    insert(root, "boca");
    insert(root, "anda");
    insert(root, "bala");
    insert(root, "brasil");
    insert(root, "bruno");
    char word[100];
    printf("Digite uma palavra para verificar: ");
    scanf("%s", word);
    for (int i = 0; word[i]; i++) {
        word[i] = tolower(word[i]);
    } spellCheck(root, word);
    return 0;
}