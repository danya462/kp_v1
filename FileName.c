#define _USE_MATH_DEFINES 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define TEAMS 9
#define MATCHES 16

void Points(char results[MATCHES][TEAMS], int scores[TEAMS]) {
    int i, j;


    for (i = 0; i < TEAMS; i++) {
        scores[i] = 0;
    }


    for (i = 0; i < MATCHES; i++) {
        int attempts[TEAMS] = { 0 };

        // цикл отвечает за случайную генирацию + и -
        for (j = 0; j < TEAMS; j++) {

            results[i][j] = (rand() % 2) ? '+' : '-';

            attempts[j] = rand() % 11;
        }


        for (j = 0; j < TEAMS; j++) {
            if (results[i][j] == '+') {
                scores[j] += 4;

                if (attempts[j] >= 3) {
                    scores[j] += 1;
                }
            }
            else if (results[i][j] == '-') {
                scores[j] += 2;
            }
        }


        for (j = 0; j < TEAMS; j++) {
            if (results[i][j] == '-') {
                int opponent = (j + 1) % TEAMS;
                if (attempts[j] - attempts[opponent] <= 7) {
                    scores[j] += 1;
                }
            }
        }
    }
}


void printResults(char results[MATCHES][TEAMS]) {
    printf("\nРезультаты матчей:\n");
    printf("Команда № | ");

    for (int i = 0; i < MATCHES; i++) {
        printf("%d ", i + 1);
    }

    printf("\n---------------------------------------------\n");

    for (int team = 0; team < TEAMS; team++) {
        printf("Команда %d | ", team + 1);
        for (int match = 0; match < MATCHES; match++) {
            printf("%c ", results[match][team]);
        }
        printf("\n");
    }
}


int main() {
    setlocale(LC_CTYPE, "RUS");
    char results[MATCHES][TEAMS];
    int scores[TEAMS];

    // Инициализация генератора случайных чисел
    srand(time(NULL));

    Points(results, scores);


    printResults(results);

    printf("\nОчки команд:\n");
    for (int i = 0; i < TEAMS; i++) {
        printf("Команда %d: %d очков\n", i + 1, scores[i]);
    }

    return 0;
}