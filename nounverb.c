#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Define maximum limits
#define MAX_WORDS 1000
#define MAX_WORD_LEN 50

// Noun list: common nouns for demonstration
const char *noun_list[] = {
    "dog", "cat", "car", "city", "book", "apple", "flower", "tree", "river", "mountain"
};
const int noun_list_size = sizeof(noun_list) / sizeof(noun_list[0]);

// Verb list: common verbs for demonstration
const char *verb_list[] = {
    "run", "jump", "drive", "write", "read", "eat", "sleep", "walk", "talk", "listen"
};
const int verb_list_size = sizeof(verb_list) / sizeof(verb_list[0]);

// Function to convert a string to lowercase (action: normalize text)
void convert_to_lowercase(char *str) {
    for (; *str; ++str) {
        *str = tolower(*str);
    }
}

// Function to check if a word is a noun (classification: noun detector)
int check_if_noun(const char *word) {
    for (int i = 0; i < noun_list_size; i++) {
        if (strcmp(word, noun_list[i]) == 0) {
            return 1; // is noun
        }
    }
    return 0; // not noun
}

// Function to check if a word is a verb (classification: verb detector)
int check_if_verb(const char *word) {
    for (int i = 0; i < verb_list_size; i++) {
        if (strcmp(word, verb_list[i]) == 0) {
            return 1; // is verb
        }
    }
    return 0; // not verb
}

int main() {
    char sentence[1024];

    // Input: User provides a sentence (action: input)
    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    // Remove trailing newline (action: clean input)
    size_t len = strlen(sentence);
    if (len > 0 && sentence[len - 1] == '\n') {
        sentence[len - 1] = '\0';
    }

    // Tokenize sentence into words (action: split sentence)
    char *words[MAX_WORDS];
    int word_count = 0;

    // Define delimiters for splitting (punctuation and spaces)
    const char *delimiters = " ,.-!?;:\"()[]{}";

    // Extract words from the sentence (action: parse)
    char *token = strtok(sentence, delimiters);
    while (token != NULL && word_count < MAX_WORDS) {
        // Allocate memory for each word (action: allocate)
        words[word_count] = malloc(strlen(token) + 1);
        if (words[word_count] == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }
        strcpy(words[word_count], token);
        // Convert to lowercase for uniformity (action: normalize)
        convert_to_lowercase(words[word_count]);
        word_count++;
        token = strtok(NULL, delimiters);
    }

    // Classify and display nouns and verbs (action: identify)
    printf("Identified words:\n");
    for (int i = 0; i < word_count; i++) {
        if (check_if_noun(words[i])) {
            printf("Noun: %s\n", words[i]);
        }
        // Check if the word is a verb
        if (check_if_verb(words[i])) {
            printf("Verb: %s\n", words[i]);
        }
        free(words[i]); // Free allocated memory (action: cleanup)
    }

    return 0;
}
