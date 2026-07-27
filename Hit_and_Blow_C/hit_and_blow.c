#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int makeCorrect(void);
int Checkcorrect(int cor, int ans);

int main(void)
{
    int correct;
    int answer;
    int result;
    int hit = 0;
    int blow;
    int ch;

    /* 乱数の準備 */
    srand((unsigned int)time(NULL));
    correct = makeCorrect();

    while (hit != 4) {
        printf("4桁の数字を入力してください: ");

        if (scanf("%d", &answer) != 1) {
            printf("数字を入力してください。\n");
            while ((ch = getchar()) != '\n' && ch != EOF) {
                /* 入力を空にする */
            }
            continue;
        }

        if (answer < 1000 || answer > 9999) {
            printf("4桁の数字を入力してください。\n");
            continue;
        }

        result = Checkcorrect(correct, answer);
        hit = result / 10;
        blow = result % 10;

        printf("%d Hit %d Blow\n", hit, blow);
    }

    printf("おめでとうございます！正解です！\n");

    return 0;
}

int makeCorrect(void)
{
    int digit[4];
    int newDigit;
    int same;
    int correct = 0;
    int i = 0;
    int j;

    /* 重ならない数字を4個作る */
    while (i < 4) {
        if (i == 0) {
            newDigit = rand() % 9 + 1;
        } else {
            newDigit = rand() % 10;
        }
        same = 0;

        for (j = 0; j < i; j++) {
            if (digit[j] == newDigit) {
                same = 1;
            }
        }

        if (same == 0) {
            digit[i] = newDigit;
            i++;
        }
    }

    /* 4個の数字を一つのintにする */
    for (i = 0; i < 4; i++) {
        correct = correct * 10 + digit[i];
    }

    return correct;
}

int Checkcorrect(int cor, int ans)
{
    int corDigit[4];
    int ansDigit[4];
    int usedCor[4] = {0, 0, 0, 0};
    int usedAns[4] = {0, 0, 0, 0};
    int hit = 0;
    int blow = 0;
    int i;
    int j;

    /* intを4個の数字に分ける */
    for (i = 3; i >= 0; i--) {
        corDigit[i] = cor % 10;
        ansDigit[i] = ans % 10;
        cor = cor / 10;
        ans = ans / 10;
    }

    /* 同じ場所の数字を調べる */
    for (i = 0; i < 4; i++) {
        if (corDigit[i] == ansDigit[i]) {
            hit++;
            usedCor[i] = 1;
            usedAns[i] = 1;
        }
    }

    /* 違う場所にある同じ数字を調べる */
    for (i = 0; i < 4; i++) {
        if (usedAns[i] == 0) {
            for (j = 0; j < 4; j++) {
                if (usedCor[j] == 0 && ansDigit[i] == corDigit[j]) {
                    blow++;
                    usedCor[j] = 1;
                    usedAns[i] = 1;
                    break;
                }
            }
        }
    }

    /* 十の位をHit、一の位をBlowにする */
    return hit * 10 + blow;
}
