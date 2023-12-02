#include <stdio.h>

static int VALUES[10] = {0,1,2,3,4,5,6,7,8,9};

int lut(char c) {
    return VALUES[c - '0'];
}
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
int main() {
    int sum = 0;
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Could not open file\n");
        return -11;
    }

    printf("sizeof(int) = %lu\n", sizeof(int));

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int i = 0;
        char *first,*second;
        char v = line[i];
        while (v != '\0') {
            if (v >= '0' && v <= '9') {
                first = &line[i];
                break;
            }
            i++;
            v = line[i];
        }
        while (v != '\0') {
            if (v >= '0' && v <= '9') {
                second = &line[i];
            }
            i++;
            v = line[i];
        }
        //printf("%s  - %c%c - %d\n", line, *first, *second, lut(*first)*10 + lut(*second));
        sum += lut(*first)*10 + lut(*second);
    }

    printf("sum = %d\n", sum);

    fclose(file);

    return 0;
}