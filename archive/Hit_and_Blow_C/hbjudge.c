#include <stdio.h>

#include "hbjudge.h"

#define DIGIT_COUNT 4
#define DECIMAL_BASE 10

int checkCorrect(int cor, int ans)
{
    int correctDigits[DIGIT_COUNT];
    int answerDigits[DIGIT_COUNT];
    int usedCorrect[DIGIT_COUNT] = {0};
    int usedAnswer[DIGIT_COUNT] = {0};
    int hitCount = 0;
    int blowCount = 0;
    int digitIndex;
    int comparisonIndex;

    /* 先頭が0の場合も4桁として分ける */
    for (digitIndex = DIGIT_COUNT - 1; digitIndex >= 0; digitIndex--) {
        correctDigits[digitIndex] = cor % DECIMAL_BASE;
        answerDigits[digitIndex] = ans % DECIMAL_BASE;
        cor = cor / DECIMAL_BASE;
        ans = ans / DECIMAL_BASE;
    }

    /* 数字と位置が同じ場所を調べる */
    for (digitIndex = 0; digitIndex < DIGIT_COUNT; digitIndex++) {
        if (correctDigits[digitIndex] == answerDigits[digitIndex]) {
            hitCount++;
            usedCorrect[digitIndex] = 1;
            usedAnswer[digitIndex] = 1;
        }
    }

    /* Hitではない場所からBlowを調べる */
    for (digitIndex = 0; digitIndex < DIGIT_COUNT; digitIndex++) {
        if (usedAnswer[digitIndex] == 0) {
            for (comparisonIndex = 0; comparisonIndex < DIGIT_COUNT; comparisonIndex++) {
                if (usedCorrect[comparisonIndex] == 0 &&
                    answerDigits[digitIndex] == correctDigits[comparisonIndex]) {
                    blowCount++;
                    usedCorrect[comparisonIndex] = 1;
                    usedAnswer[digitIndex] = 1;
                    break;
                }
            }
        }
    }

    printf("%d Hit %d Blow\n", hitCount, blowCount);

    if (hitCount == DIGIT_COUNT) {
        printf("正解です。おめでとうございます！\n");
        return 1;
    }

    return 0;
}
