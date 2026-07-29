#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "hbjudge.h"
#include "hbsetting.h"

#define DIGIT_COUNT 4
#define INPUT_BUFFER_SIZE 100
#define INPUT_TEXT_FORMAT "%99s"
#define DECIMAL_BASE 10

int main(void)
{
    int correctNumber;
    int answerNumber;
    int isCorrect = 0;
    int inputLength;
    int isNumber;
    int index;
    char inputText[INPUT_BUFFER_SIZE];

    /* 毎回違う答えを作るために乱数を準備する */
    srand((unsigned int)time(NULL));
    correctNumber = makeCorrect();

    printf("Hit & Blowゲームを始めます。\n");

    while (isCorrect == 0) {
        printf("4桁の数字を入力してください: ");

        if (scanf(INPUT_TEXT_FORMAT, inputText) != 1) {
            printf("入力を読み込めませんでした。\n");
            return 1;
        }

        inputLength = (int)strlen(inputText);
        if (inputLength != DIGIT_COUNT) {
            printf("4桁の数字を入力してください。\n");
            continue;
        }

        isNumber = 1;
        for (index = 0; index < DIGIT_COUNT; index++) {
            if (inputText[index] < '0' || inputText[index] > '9') {
                isNumber = 0;
            }
        }

        if (isNumber == 0) {
            printf("数字だけを入力してください。\n");
            continue;
        }

        /* 先頭の0を確認した後でintに変える */
        answerNumber = 0;
        for (index = 0; index < DIGIT_COUNT; index++) {
            answerNumber = answerNumber * DECIMAL_BASE;
            answerNumber = answerNumber + (inputText[index] - '0');
        }

        isCorrect = checkCorrect(correctNumber, answerNumber);
    }

    return 0;
}
