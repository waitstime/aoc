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

int is_game_possible(char *line, const int max_red, const int max_green, const int max_blue) {
    int val = 0;
    int color = 0;
    int skip = 1;
    int is_end = 0;
    while (is_end != EOL) {
        is_end = 0;
        skip = scan_num(line, &val);
        line += skip;
        skip = scan_color(line, &color, &is_end);
        switch (color) {
            case RED:
                // printf("RED %d\n", val);
                if (val > max_red) {
                    // printf("Game is not possible because RED\n");
                    return FALSE;
                }
                break;
            case GREEN:
                // printf("GREEN %d\n", val);
                if (val > max_green) {
                    // printf("Game is not possible because GREEN\n");
                    return FALSE;
                }
                break;
            case BLUE:
                // printf("BLUE %d\n", val);
                if (val > max_blue) {
                    // printf("Game is not possible because BLUE\n");
                    return FALSE;
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
    
    return TRUE;
}

// Part 1
//Determine which games would have been possible if the bag had been loaded with only 12 red cubes, 13 green cubes, and 14 blue cubes. What is the sum of the IDs of those games?
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
        int possible = 0;
        skip = scan_game_num(line, &game_num);
        // printf("game_num = %d, line = %s\n", game_num, line);
        possible = is_game_possible(line + skip, MAX_RED, MAX_GREEN, MAX_BLUE);
        if (possible) {
            sum += game_num;
        }
    }
    printf("sum of possible games = %d\n", sum);

    return 0;
}
