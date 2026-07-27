#include <stdlib.h>

#include "hbsetting.h"

#define DIGIT_COUNT 4
#define DECIMAL_BASE 10

int makeCorrect(void)
{
    int digits[DIGIT_COUNT];
    int newDigit;
    int isDuplicate;
    int correctNumber = 0;
    int digitIndex = 0;
    int comparisonIndex;

    /* 同じ数字を使わない答えを作る */
    while (digitIndex < DIGIT_COUNT) {
        newDigit = rand() % DECIMAL_BASE;
        isDuplicate = 0;

        for (comparisonIndex = 0; comparisonIndex < digitIndex; comparisonIndex++) {
            if (digits[comparisonIndex] == newDigit) {
                isDuplicate = 1;
            }
        }

        if (isDuplicate == 0) {
            digits[digitIndex] = newDigit;
            digitIndex++;
        }
    }

    /* 4個の数字を一つのintにする */
    for (digitIndex = 0; digitIndex < DIGIT_COUNT; digitIndex++) {
        correctNumber = correctNumber * DECIMAL_BASE;
        correctNumber = correctNumber + digits[digitIndex];
    }

    return correctNumber;
}
