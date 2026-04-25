#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to convert string to lowercase for comparison
void to_lowercase(char *str) {
    for (; *str; ++str) {
        *str = tolower(*str);
    }
}

// Check if the word is in the list of nouns
int is_noun(const char *word) {
    // Predefined list of nouns (expand as needed)
    const char *nouns[] = {
        "dog",
        "cat",
        "car",
        "tree",
        "book",
        "computer",
        "flower",
        "city",
        "child",
        "music"
    };
    int num_nouns = sizeof(nouns) / sizeof(nouns[0]);

    // Create a modifiable copy of the input word
    char buffer[100];
    strncpy(buffer, word, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    to_lowercase(buffer);

    for (int i = 0; i < num_nouns; i++) {
        if (strcmp(buffer, nouns[i]) == 0) {
            return 1; // Yes, it's a noun
        }
    }
    return 0; // Not found in list
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <word>\n", argv[0]);
        return 1;
    }

    const char *word = argv[1];

    if (is_noun(word)) {
        printf("'%s' is a noun.\n", word);
    } else {
        printf("'%s' is NOT a noun.\n", word);
    }

    return 0;
}
