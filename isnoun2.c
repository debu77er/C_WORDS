#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 50

// A small list of common nouns for demonstration
const char *noun_list[] = {
    "dog", "cat", "car", "city", "book", "apple", "flower", "tree", "river", "mountain"
};
const int noun_list_size = sizeof(noun_list) / sizeof(noun_list[0]);

// Function to convert a string to lowercase
void to_lowercase(char *str) {
    for (; *str; ++str) {
        *str = tolower(*str);
    }
}

// Function to check if a word is in the noun list
int is_noun(const char *word) {
    for (int i = 0; i < noun_list_size; i++) {
        if (strcmp(word, noun_list[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char sentence[1024];
    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    // Remove trailing newline if present
    size_t len = strlen(sentence);
    if (len > 0 && sentence[len - 1] == '\n') {
        sentence[len - 1] = '\0';
    }

    // Tokenize the sentence into words
    char *words[MAX_WORDS];
    int word_count = 0;

    char *token = strtok(sentence, " ,.-!?;:\"()[]{}");
    while (token != NULL && word_count < MAX_WORDS) {
        words[word_count] = malloc(strlen(token) + 1);
        if (words[word_count] == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }
        strcpy(words[word_count], token);
        to_lowercase(words[word_count]);
        word_count++;
        token = strtok(NULL, " ,.-!?;:\"()[]{}");
    }

    printf("Identified nouns:\n");
    for (int i = 0; i < word_count; i++) {
        if (is_noun(words[i])) {
            printf("%s", words[i]);
        }
        free(words[i]);
    }

    return 0;
}
