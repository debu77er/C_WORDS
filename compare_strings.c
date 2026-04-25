#include <stdio.h>

// Function to compare two strings
int compareStrings(const char *str1, const char *str2) {
    // Loop until characters in both strings match or until a null terminator is reached
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    // Return the difference of the ASCII values of the first unmatched characters
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

int main() {
    const char *string1 = "hello";
    const char *string2 = "hello";
    const char *string3 = "world";

    printf("Comparing '%s' and '%s': %d", string1, string2, compareStrings(string1, string2));
    printf("Comparing '%s' and '%s': %d", string1, string3, compareStrings(string1, string3));

    return 0;
}