/* Purpose: Spelling checker
 * Author: Samia Rahman 
 * Date:12th november
 * References:
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 20
#define MAX_LINES 100
#define MAX_LENGTH_OF_WORDS 10
#define MAX_SENTECE_OF_WORDS 10

int min(int a, int b, int c) {
    if (a < b && a < c) {
        return a;
    } else if (b < a && b < c) {
        return b;
    } else {
        return c;
    }
}

int levenshtein_distance(char *first_word, char *second_word) {
    int word1 = strlen(first_word);
    int word2 = strlen(second_word);

    int distance_words[word1 + 1][word2 + 1];

    for (int i = 0; i <= word1; i++) {
        distance_words[i][0] = i;
    }
    for (int j = 0; j <= word2; j++) {
        distance_words[0][j] = j;
    }
    for (int i = 1; i <= word1; i++) {
        for (int j = 1; j <= word2; j++) {
            distance_words[i][j] = min(distance_words[i - 1][j] + 1, distance_words[i][j - 1] + 1, distance_words[i - 1][j - 1] + (first_word[i - 1] != second_word[j - 1]));
        }
    }
    return distance_words[word1][word2];
}

int closest_distance(char new_s[], char dictionary[MAX_WORDS][MAX_LENGTH_OF_WORDS], int n) {
    int closest_ind = 0;
    int distance_min = levenshtein_distance(new_s, dictionary[0]);

    for (int k = 1; k < n; k++) {
        int distance = levenshtein_distance(new_s, dictionary[k]);
        if (distance < distance_min) {
            distance_min = distance;
            closest_ind = k;
        }
    }

    return closest_ind;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    while (getchar() != '\n');  

    char dictionary[MAX_WORDS][MAX_LENGTH_OF_WORDS];
    for (int i = 0; i < n; i++) {
        scanf("%s", dictionary[i]);
    }
    getchar();  

    for (int i = 0; i < m; i++) {
        char new_s[MAX_SENTECE_OF_WORDS * (MAX_LENGTH_OF_WORDS + 1)];
        int count = 0;

        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c == ' ' || c == '\0') {
                if (count > 0) {
                    new_s[count] = '\0';

                    int closest_ind = closest_distance(new_s, dictionary, n);
                    printf("%s ", dictionary[closest_ind]);

                    count = 0;
                }
            } else {
                new_s[count++] = c;
            }
        }

        if (count > 0) {
            new_s[count] = '\0';

            int closest_ind = closest_distance(new_s, dictionary, n);
            printf("%s ", dictionary[closest_ind]);
        }

        printf("\n");
    }

    return 0;
}
