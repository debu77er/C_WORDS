#include <stdio.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_WORDS 100
#define MAX_WORD_LENGTH 100

int main() {
    char line[MAX_LINE];
    char *words[MAX_WORDS];
    int word_count = 0;

    printf("Enter a sentence: ");
    if (fgets(line, sizeof(line), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    // Remove trailing newline character if present
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
        line[len - 1] = '\0';
    }

    // Tokenize the input line into words
    char *token = strtok(line, " ");
    while (token != NULL && word_count < MAX_WORDS) {
        words[word_count++] = token;
        token = strtok(NULL, " ");
    }

    // Display all words
    printf("Words in the sentence:\n");
    for (int i = 0; i < word_count; i++) {
        printf("%s\n", words[i]);
    }

    return 0;
}
