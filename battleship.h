#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <iostream>
#include <ctime>
#include <vector>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <cstdlib>
#include <algorithm>
#include <sstream>

using namespace std;

const int N = 10;
const int NUM_SHIPS = 10;

// Глобальные константы
extern const char SHIP;
extern const char HIT;
extern const char MISS;
extern const char EMPTY;
extern const char UNKNOWN;
extern const char DEAD;
extern const int COLOR_RED;
extern const int COLOR_GREEN;
extern const int COLOR_YELLOW;
extern const int COLOR_BLUE;
extern const char* RESET;
extern const char* BLUE;
extern const char* GREEN_BG;


// Прототипы функций
void showmap(int map[N][N], int mask[N][N], bool maskUse);
void set_rand_ships(int map[N][N], int size_ship, int ship_id);
int shotInShips(int map[N][N], int x, int y, int ships[NUM_SHIPS + 1], int mask[N][N]);
bool ship_in_map(int x, int y, int dir, int size_ship);
void set_manually_ships(int map[N][N], int size_ship, int ship_id);
vector<string> get_map_lines(int map[N][N], int mask[N][N], bool useMask);
string getColoredString(char c, int color);
int getArrowKey();
void printColored(char c, int color);
void markAroundKilledShip(int map[N][N], int mask[N][N], int ship_id);
int getch();
void clearScreen();


// Структура для прицельной стрельбы
struct TargetingState {
    int state;
    int firstHitX;
    int firstHitY;
    int lastHitX;
    int lastHitY;
    int direction;
    vector<int> directionsToTry;
};

// Направления движения
extern const int dx[4];
extern const int dy[4];

#endif
