#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Function to check if a word is in the list of excluded words
int isExcludedWord(char *word) {
    char *excludedWords[] = {"the", "a", "an", "and", "but", "or", "in", "on", "at", "to", "for", "with"};
    int numExcludedWords = sizeof(excludedWords) / sizeof(excludedWords[0]);

    for (int i = 0; i < numExcludedWords; i++) {
        if (strcmp(word, excludedWords[i]) == 0) {
            return 1; // Word is excluded
        }
    }

    return 0; // Word is not excluded
}

int main() {
    char filepath[256];
    FILE *file;
    char ch;
    char word[100];
    int alphaCount = 0;
    int totalWordCount = 0;
    int excludedWordCount = 0;
    int paraCount = 1; // Count of paragraphs
    int lineCount = 0; // Count of lines
    int inWord = 0;
    int insideLine = 0; // Flag to track if currently inside a line
    int insidePara = 0; // Flag to track if currently inside a paragraph
    int insideSpace = 0; // Flag to track if currently inside consecutive spaces

    printf("Enter the full path of the file: ");
    scanf("%s", filepath);

    file = fopen(filepath, "r");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }

    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch)) {
            alphaCount++;
        }

        if (!isspace(ch) && !inWord) {
            inWord = 1;
            word[0] = ch;
            word[1] = '\0';
        } else if (!isspace(ch)) {
            int len = strlen(word);
            if (len < sizeof(word) - 1) {
                word[len] = ch;
                word[len + 1] = '\0';
            }
            insideSpace = 0; // Reset the flag when not inside consecutive spaces
        } else if (isspace(ch) && inWord) {
            inWord = 0;
            totalWordCount++;
            if (isExcludedWord(word)) {
                excludedWordCount++;
            }
        }
        if (ch == '.'||ch=='!'|ch=='?') {
            if (!insideLine) {
                lineCount++;
                insideLine = 1;
            }
        } else {
            insideLine = 0;
        }
    }
        
    if (ch == '\n') {
            
            if (!insidePara) {   
                paraCount++;             
                insidePara= 1;
            }
        } else {
            insidePara = 0; // Reset the flag when not inside a line
        }

    if (inWord) {
        totalWordCount++;
        if (isExcludedWord(word)) {
            excludedWordCount++;
        }
    }

    fclose(file);


    int effWordCount=totalWordCount-excludedWordCount;
    if(alphaCount==0){
        printf("The file is completely empty.\n");
        return 0;
    }
    printf("Number of alphabets: %d\n", alphaCount);
    printf("Number of total words: %d\n", totalWordCount);
    printf("Number of excluded words: %d\n", excludedWordCount);
    printf("Ratio of excluded words to total words: %d:%d\n",excludedWordCount, totalWordCount);
    printf("Number of effective words: %d\n", effWordCount);
    printf("Number of lines: %d\n", lineCount);
    printf("Number of paragraphs: %d\n",paraCount);
    return 0;
}
