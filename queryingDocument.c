
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n) {
    return document[n-1][m-1][k-1];
}

char** kth_sentence_in_mth_paragraph(char**** document, int k, int m) { 
    return document[m-1][k-1];
}

char*** kth_paragraph(char**** document, int k) {
    return document[k-1];
}

char**** get_document(char* text) {
    // Allocate memory for paragraphs
    char**** document = malloc(MAX_PARAGRAPHS * sizeof(char***));
    
    // Split text into paragraphs
    char* paragraph = strtok(text, "\n");
    int para_count = 0;
    
    while (paragraph != NULL && para_count < MAX_PARAGRAPHS) {
        // Allocate memory for sentences in current paragraph
        char*** sentences = malloc(MAX_CHARACTERS * sizeof(char**));
        
        // Split paragraph into sentences
        char* sentence = strtok(paragraph, ".");
        int sent_count = 0;
        
        while (sentence != NULL && sent_count < MAX_CHARACTERS) {
            // Skip leading whitespace
            while (*sentence == ' ') sentence++;
            
            // Allocate memory for words in current sentence
            char** words = malloc(MAX_CHARACTERS * sizeof(char*));
            
            // Split sentence into words
            char* word = strtok(sentence, " ");
            int word_count = 0;
            
            while (word != NULL && word_count < MAX_CHARACTERS) {
                words[word_count] = malloc((strlen(word)+1) * sizeof(char));
                strcpy(words[word_count], word);
                word_count++;
                word = strtok(NULL, " ");
            }
            
            // Reallocate to exact size
            words = realloc(words, word_count * sizeof(char*));
            sentences[sent_count] = words;
            sent_count++;
            sentence = strtok(NULL, ".");
        }
        
        // Reallocate to exact size
        sentences = realloc(sentences, sent_count * sizeof(char**));
        document[para_count] = sentences;
        para_count++;
        paragraph = strtok(NULL, "\n");
    }
    
    // Reallocate to exact size
    document = realloc(document, para_count * sizeof(char***));
    return document;
}

int main() {
    char* text = "Learning C is fun.\nLearn arrays, strings, pointers.\nAnd malloc, calloc, realloc, free!";
    char**** document = get_document(text);

    // Test queries
    char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, 3, 1, 2);
    printf("3rd word in 1st sentence of 2nd paragraph: %s\n", word);
    
    char** sentence = kth_sentence_in_mth_paragraph(document, 1, 3);
    printf("1st sentence in 3rd paragraph: ");
    for (int i = 0; sentence[i] != NULL; i++) {
        printf("%s ", sentence[i]);
    }
    printf("\n");
    
    char*** paragraph = kth_paragraph(document, 1);
    printf("1st paragraph: ");
    for (int i = 0; paragraph[i] != NULL; i++) {
        for (int j = 0; paragraph[i][j] != NULL; j++) {
            printf("%s ", paragraph[i][j]);
        }
        printf(". ");
    }
    printf("\n");
    
    // Free memory
    for (int p = 0; document[p] != NULL; p++) {
        for (int s = 0; document[p][s] != NULL; s++) {
            for (int w = 0; document[p][s][w] != NULL; w++) {
                free(document[p][s][w]);
            }
            free(document[p][s]);
        }
        free(document[p]);
    }
    free(document);
    
    return 0;
}
