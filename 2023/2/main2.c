#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int RED = 0;
static const int GREEN = 1;
static const int BLUE = 2;

static const int FALSE = 0;
static const int TRUE = 1;
static const int EOL = 2;

static const int MAX_RED = 12;
static const int MAX_GREEN = 13;
static const int MAX_BLUE = 14;

static const int SKIP_RED = 3;
static const int SKIP_GREEN = 5;
static const int SKIP_BLUE = 4;

int scan_game_num(char *line, int *game_num) {
    char *start = line + 5;
    char *ptr = strchr(start, ':');
    if (ptr == NULL) {
        return 0;
    }
    *ptr = '\0';
    *game_num = atoi(start);
    return ptr - line + 2;
}

int scan_num(char *line, int *num) {
    char *start = line;
    char *ptr = strchr(start, ' ');
    if (ptr == NULL) {
        return 0;
    }
    *ptr = '\0';
    *num = atoi(start);
    return ptr - line + 1;
}

int scan_color(char *line, int *color, int *is_end_set) {

    char *p = line;
    if (line[0] == 'r') {
        *color = RED;
        p += SKIP_RED;
    } else if (line[0] == 'g') {
        *color = GREEN;
        p += SKIP_GREEN;
    } else if (line[0] == 'b') {
        *color = BLUE;
        p += SKIP_BLUE;
    } else {
        return FALSE;
    }

    if (p[0] == ';') {
        *is_end_set = TRUE;
    } else if (p[0] == '\0' || p[0] == '\n') {
        *is_end_set = EOL;
    }
    return p - line + 2;
}

int game_power(char *line, const int max_red, const int max_green, const int max_blue) {
    int val = 0;
    int color = 0;
    int skip = 1;
    int is_end = 0;
    // track the min necessary for each color
    int min_red = -1;
    int min_green = -1;
    int min_blue = -1;

    while (is_end != EOL) {
        is_end = 0;
        skip = scan_num(line, &val);
        line += skip;
        skip = scan_color(line, &color, &is_end);
        switch (color) {
            case RED:
                if (min_red < val) {
                    min_red = val;
                }
                break;
            case GREEN:
                if (min_green < val) {
                    min_green = val;
                }
                break;
            case BLUE:
                if (min_blue < val) {
                    min_blue = val;
                }
                break;
            default:
                printf("Invalid color\n");
                return FALSE;
        }
        // if (is_end == TRUE) {
        //     printf("End of Set\n");
        // } else if (is_end == EOL) {
        //     printf("End of Line\n");
        // }
        line += skip;
    }

    printf("min_red = %d, min_green = %d, min_blue = %d\n", min_red, min_green, min_blue);
    
    return min_red * min_blue * min_green;
}

// Part 1
//Determine which games would have been possible if the bag had been loaded with only 12 red cubes, 13 green cubes, and 14 blue cubes. What is the sum of the IDs of those games?
// Part 2
// The power of a set of cubes is equal to the numbers of red, green, and blue cubes multiplied together. The power of the minimum set of cubes in game 1 is 48. In games 2-5 it was 12, 1560, 630, and 36, respectively. Adding up these five powers produces the sum 2286.
//
// For each game, find the minimum set of cubes that must have been present. What is the sum of the power of these sets?
int main() {
    int sum = 0;
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Could not open file\n");
        return -11;
    }

    char line[256];
    int game_num = 0;
    while (fgets(line, sizeof(line), file)) {
        int skip = 0;
        int power = 0;
        skip = scan_game_num(line, &game_num);
        // printf("game_num = %d, line = %s\n", game_num, line);
        power = game_power(line + skip, MAX_RED, MAX_GREEN, MAX_BLUE);
        printf("game_num = %d, power = %d\n", game_num, power);
        sum += power;
    }
    printf("sum of power for games = %d\n", sum);

    return 0;
}
