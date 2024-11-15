#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ALPHABET_SIZE 26
typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    bool is_end_of_word;
} TrieNode;
TrieNode *createNode() {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    node->is_end_of_word = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    return node;
}
void insert(TrieNode *root, const char *word) {
    TrieNode *node = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (node->children[index] == NULL) {
            node->children[index] = createNode();
        }
        node = node->children[index];
    }

    node->is_end_of_word = true;
}
bool search(TrieNode *root, const char *word) {
    TrieNode *node = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (node->children[index] == NULL) {
            return false;
        }
        node = node->children[index];
    }
    return node->is_end_of_word;
}
int main() {
    TrieNode *root = createNode();
    insert(root, "casa");
    insert(root, "carro");
    printf("Busca por 'casa': %s\n", search(root, "casa") ? "Encontrado" : "Não encontrado");
    printf("Busca por 'carro': %s\n", search(root, "carro") ? "Encontrado" : "Não encontrado");
    printf("Busca por 'cachorro': %s\n", search(root, "cachorro") ? "Encontrado" : "Não encontrado");
    return 0;
}
