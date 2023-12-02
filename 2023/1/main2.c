#include <stdio.h>
#include <string.h>

static int VALUES[10] = {0,1,2,3,4,5,6,7,8,9};
static const int NUMS_LEN = 9;
static const char* NUMS[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
static const char NUMS_LEN_LUT[] = {3, 3, 5, 4, 4, 3, 5, 5, 4};

int lut(char c) {
    return VALUES[c - '0'];
}

// return the number of characters to skip if found or 0 if nothing found.
int findWordNum(unsigned int start, char *line, int * val) {
    char v = line[start];
    if (v != 'o' && v != 't' && v != 'f' && v != 's' && v != 'e' && v != 'n') {
        return 0;
    }
    for (int i = 0; i < NUMS_LEN; i++) {
        if (memcmp(line + start, NUMS[i], NUMS_LEN_LUT[i]) == 0) {
            *val = i + 1;
            return NUMS_LEN_LUT[i];
        }
    }
    return 0;
}

int findNum(unsigned int start, char *line, int *val, int findOne) {
    int i = start;
    char v = line[i];
    while (v != '\0') {
        int j = 0;
        v = line[i];
        if (v >= '0' && v <= '9') {
            *val = lut(v);
            if (findOne) {
                return i;
            }
            i++;
            continue;
        }

        // otherwise, it might be a word
        j = findWordNum(i, line, val);
        if (j && findOne) {
            return i + j;
        } else {
            i++;
        }
    }

    return i;
}
// Part One
// The newly-improved calibration document consists of lines of text; each line originally contained a specific calibration value that the Elves now need to recover. On each line, the calibration value can be found by combining the first digit and the last digit (in that order) to form a single two-digit number.
//
// For example:
//
// 1abc2
// pqr3stu8vwx
// a1b2c3d4e5f
// treb7uchet
// In this example, the calibration values of these four lines are 12, 38, 15, and 77. Adding these together produces 142.
//
// Consider your entire calibration document. What is the sum of all of the calibration values?
// --- Part Two ---
// Your calculation isn't quite right. It looks like some of the digits are actually spelled out with letters: one, two, three, four, five, six, seven, eight, and nine also count as valid "digits".
//
// Equipped with this new information, you now need to find the real first and last digit on each line. For example:
//
// two1nine
// eightwothree
// abcone2threexyz
// xtwone3four
// 4nineeightseven2
// zoneight234
// 7pqrstsixteen
// In this example, the calibration values are 29, 83, 13, 24, 42, 14, and 76. Adding these together produces 281.
int main() {
    int sum = 0;
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Could not open file\n");
        return -11;
    }

    // printf("sizeof(int) = %lu\n", sizeof(int));

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int i = 0;
        int first = 0;
        int second = 0;
        char v = line[i];
        i = findNum(0, line, &first, 1);
        findNum(i, line, &second, 0);
        printf("first = %d, second = %d, line = %s", first, second, line);
        sum += first*10 + second;
    }

    printf("sum = %d\n", sum);

    fclose(file);

    return 0;
}