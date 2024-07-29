#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 200 //let's be honest more than this would break your machine
#define MAX_WORD_LENGTH 100 //This should be a lot lower tbh



// Sets the first letter of a word to lowercase Func
void toLower(char *word, char *result){
    strcpy(result, word);
    if (isupper(result[0])){
        result[0] = tolower(result[0]);
    }
}




// Set the first letter of a word to an uppercase Func
void toUpper(char *word, char *result){
    strcpy(result, word);
    if (islower(result[0])){
        result[0] = toupper(result[0]);
    }
}




// Recursive func that generates all unique combinations
void generateCombo(char words[][MAX_WORD_LENGTH], int n, int index, char *current, int used[], FILE *outputFile){

    if (index == n){
        return;
    }

    for (int i = 0; i < n; i++){
        if (!used[i]){
            used[i] = 1;
            char newCombo[MAX_WORD_LENGTH * MAX_WORDS];
            if (current[0] != '\0'){
                sprintf(newCombo, "%s%s", current, words[i]);
            } 
            else{
                sprintf(newCombo, "%s", words[i]);
            }
            fprintf(outputFile, "%s\n", newCombo);
            generateCombo(words, n, index + 1, newCombo, used, outputFile);
            used[i] = 0;
        }
    }
}




int main(int argc, char *argv[]){

    if (argc != 2){
        printf("Usage: %s <wordlist_file>\n", argv[0]);

        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL){
        perror("Error opening file");

        return 1;
    }

    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int wordCount = 0;

    while (fscanf(file, "%s", words[wordCount]) != EOF){
        wordCount++;
        if (wordCount >= MAX_WORDS){
            printf("Too many words in file. Max limit is %d.\n", MAX_WORDS);
            fclose(file);

            return 1;
        }
    }

    fclose(file);

    int option;
    printf("Select an option:\n");
    printf("1: Combine all words as they are.\n");
    printf("2: Combine all words, including both the original and first letter opposite-case versions.\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &option);

    FILE *outputFile = fopen("newWordList.txt", "w");
   
    if (outputFile == NULL){
        perror("Error creating the file");
        
        return 1;
    }

    int used[MAX_WORDS] = {0};

    if (option == 1){
        // Generate combinations with all the words untouched
        generateCombo(words, wordCount, 0, "", used, outputFile);
    } 
   
    else if (option == 2){
        // Generate combinations with all the words untouched first
        generateCombo(words, wordCount, 0, "", used, outputFile);

        // Resets array for the upper/lowercase words
        memset(used, 0, sizeof(used));

        // Generate combinations for each word's first letter in lowercase while others remain the same
        for (int i = 0; i < wordCount; i++){
            char modifiedWords[MAX_WORDS][MAX_WORD_LENGTH];
            for (int j = 0; j < wordCount; j++){
                if (i == j){
                    toLower(words[j], modifiedWords[j]);
                } 
                else{
                    strcpy(modifiedWords[j], words[j]);
                }
            }
            generateCombo(modifiedWords, wordCount, 0, "", used, outputFile);
        }


        // Resets array for the upper/lowercase words
        memset(used, 0, sizeof(used));

        //Generate combos for each word's first letter in uppercase while others remain the same and so forth
        for (int i = 0; i < wordCount; i++){
            char modifiedWords[MAX_WORDS][MAX_WORD_LENGTH];
            for (int j = 0; j < wordCount; j++){
                if (i == j){
                    toUpper(words[j], modifiedWords[j]);
                } 
                else{
                    strcpy(modifiedWords[j], words[j]);
                }
            }
            generateCombo(modifiedWords, wordCount, 0, "", used, outputFile);
        }
    }

    fclose(outputFile);
    printf("New wordlist created: newWordList.txt\n");

    return 0;
}
