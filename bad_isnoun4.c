#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_NOUNS 1000
#define MAX_NOUN_LEN 50

// Array to hold the list of nouns loaded from the file
char *noun_list[MAX_NOUNS];
int noun_list_size = 0;

// Function to load nouns from a file
void load_nouns(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open noun list file: %s", filename);
        exit(1);
    }

    char line[MAX_NOUN_LEN];
    while (fgets(line, sizeof(line), file) != NULL && noun_list_size < MAX_NOUNS) {
        // Remove trailing newline
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        // Allocate memory for the noun and store it
        noun_list[noun_list_size] = malloc(strlen(line) + 1);
        if (noun_list[noun_list_size] == NULL) {
            printf("Memory allocation failed.\n");
            fclose(file);
            exit(1);
        }
        strcpy(noun_list[noun_list_size], line);
        noun_list_size++;
    }

    fclose(file);
}

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
    // Load nouns from the file before processing input
    load_nouns("nouns.txt");

    if (noun_list_size == 0) {
        printf("Noun list is empty. Please check 'nouns.txt'.\n");
        // Free any allocated memory (though none expected)
        return 1;
    }

    char sentence[1024];
    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        printf("Error reading input.\n");
        // Free allocated memory
        for (int i = 0; i < noun_list_size; i++) {
            free(noun_list[i]);
        }
        return 1;
    }

    // Remove trailing newline if present
    size_t len = strlen(sentence);
    if (len > 0 && sentence[len - 1] == '\n') {
        sentence[len - 1] = '\0';
    }

    // Tokenize the sentence into words
    char *words[MAX_NOUNS];
    int word_count = 0;

    // Define delimiters including common punctuation
    const char *delimiters = " ,.-!?;:\"()[]{}";

    char *token = strtok(sentence, delimiters);
    while (token != NULL && word_count < MAX_NOUNS) {
        // Allocate memory for the token
        words[word_count] = malloc(strlen(token) + 1);
        if (words[word_count] == NULL) {
            printf("Memory allocation failed.\n");
            // Free previously allocated words
            for (int i = 0; i < word_count; i++) {
                free(words[i]);
            }
            // Free noun list
            for (int i = 0; i < noun_list_size; i++) {
                free(noun_list[i]);
            }
            return 1;
        }
        strcpy(words[word_count], token);
        to_lowercase(words[word_count]);
        word_count++;
        token = strtok(NULL, delimiters);
    }

    printf("Identified nouns:\n");
    // For better readability, add spaces or newlines
    for (int i = 0; i < word_count; i++) {
        if (is_noun(words[i])) {
            printf("%s", words[i]); // print each noun on a new line
        }
        free(words[i]);
    }

    // Free noun list memory
    for (int i = 0; i < noun_list_size; i++) {
        free(noun_list[i]);
    }

    return 0;
}
