#include "battleship.h"

// Глобальные константы
const char SHIP = 'O';
const char HIT = 'X';
const char MISS = '.';
const char EMPTY = '~';
const char UNKNOWN = ' ';
const char DEAD = '#';
const int COLOR_RED = 1;
const int COLOR_GREEN = 2;
const int COLOR_YELLOW = 3;
const int COLOR_BLUE = 4;
const char* BLUE = "\033[94m";
const char* RESET = "\033[0m";
const char* GREEN_BG = "\033[42m\033[30m";
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {-1, 0, 1, 0};

void showmap(int map[N][N], int mask[N][N], bool maskUse) {
    vector<string> lines = get_map_lines(map, mask, maskUse);
    for (const string& line : lines) {
        cout << line << endl;
    }
}

string getColoredString(char c, int color) {
    string s = "\033[1;3";
    s += to_string(color);
    s += 'm';
    s += c;
    s += "\033[0m";
    return s;
}

vector<string> get_map_lines(int map[N][N], int mask[N][N], bool useMask) {
    vector<string> lines;
    // Сначала определим, какие корабли полностью убиты
    bool deadShips[NUM_SHIPS + 1] = {false};
    // Проходим по всем кораблям
    for (int ship_id = 1; ship_id <= NUM_SHIPS; ship_id++) {
        deadShips[ship_id] = true; // Предполагаем, что корабль убит
        // Проверяем, есть ли хотя бы одна живая палуба у корабля
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (map[i][j] == ship_id) {
                    deadShips[ship_id] = false; // Нашли живую палубу
                    break;
                }
            }
            if (!deadShips[ship_id]) break; // Корабль жив, переходим к следующему
        }
    }

    // Отображаем координаты столбцов
    string header = "  ";
    for (int i = 0; i < N; i++) header += to_string(i) + " ";
    lines.push_back(header);
    
    // Отображаем поле
    for (int i = 0; i < N; i++) {
        string line = to_string(i) + " ";
        for (int j = 0; j < N; j++) {
            // Проверяем, нужно ли показывать содержимое клетки
            if (mask == nullptr || mask[j][i] == 1 || !useMask) {
                if (map[j][i] == 0) {
                    line += EMPTY; //Пустая клетка
                    line += " ";
                }
                // Промах
                else if (map[j][i] == -22) {
                    line += getColoredString(MISS, COLOR_BLUE);
                    line += " ";
                }
                else if (map[j][i] < 0) {
                    // Подбитая палуба
                    int ship_id = -map[j][i];
                    // Проверяем, убит ли корабль
                    if (ship_id >= 1 && ship_id <= NUM_SHIPS && deadShips[ship_id]) {
                        // Убитый корабль
                        line += getColoredString(DEAD, COLOR_RED);
                    } else {
                        // Раненый корабль
                        line += getColoredString(HIT, COLOR_YELLOW);
                    }
                    line += " ";
                }
                else if (map[j][i] > 0) {
                    // Живой корабль
                    if (!useMask) {
                        // На своем поле показываем корабли
                        line += getColoredString(SHIP, COLOR_GREEN);
                        line += " ";
                    } else {
                        // На поле противника не показываем живые корабли
                        line += EMPTY;
                        line += " ";
                    }
                }
            }
            else {
                // Клетка не открыта (для поля противника)
                line += UNKNOWN;
                line += " ";
            }
        }
        lines.push_back(line);
    }
    return lines;
}
void markAroundKilledShip(int map[N][N], int mask[N][N], int ship_id) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] == -ship_id) {
                // Обходим все соседние клетки (8 направлений)
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        int ni = i + dx;
                        int nj = j + dy;
                        if (ni >= 0 && ni < N && nj >=0 && nj < N) {
                            // Если клетка пустая и еще не открыта
                            if (mask[ni][nj] == 0 && map[ni][nj] == 0) {
                                mask[ni][nj] = 1;   // Помечаем как открытую
                                map[ni][nj] = -22; // Помечаем как промах
                            }
                        }
                    }
                }
            }
        }
    }
}

int shotInShips(int map[N][N], int x, int y, int ships[NUM_SHIPS + 1], int mask[N][N]) {
    // Проверка, стреляли ли уже в эту клетку
    if (mask[x][y] == 1) {
        return 3;
    }
    mask[x][y] = 1; // Помечаем клетку как открытую
    
    if (map[x][y] > 0) { // Попадание в живую палубу корабля
        int ship_id = map[x][y];
        ships[ship_id]--;
        map[x][y] = -ship_id; // Помечаем палубу как подбитую

        if (ships[ship_id] <= 0) {
            markAroundKilledShip(map, mask, ship_id);
            return 2; // Корабль убит
        } else {
            return 1; // Корабль ранен
        }
    }
    else if (map[x][y] == 0) { // Промах
        map[x][y] = -22;
        return 0;
    }
    
    // Если клетка уже была подбита или содержит промах
    return 0;
}

void set_rand_ships(int map[N][N], int size_ship, int ship_id) {
    int x,y;
    int dir = 0;
    int count_ship = 0;
    int count_tact = 0;
    while (count_ship < 1){
        count_tact++;
        if (count_tact > 1000){
            break; //Зашита от зацикливания
        }
        x = rand () % N; //Случайная начальная позиция
        y = rand () % N;
        int temp_x = x;
        int temp_y = y;
        dir = rand() % 4; //Случайное направление
        bool setting_is_possible = 1;
        //Проверка возможности размещения корабля
        for (int i = 0; i < size_ship; i++){
            if (x < 0 || y < 0 || x >= N || y >= N){
                setting_is_possible = 0;
                break;
            }
            if (map[x  ][y  ] >= 1 ||
                map[x  ][y+1] >= 1 ||
                map[x  ][y-1] >= 1 ||
                map[x+1][y  ] >= 1 ||
                map[x+1][y+1] >= 1 ||
                map[x+1][y-1] >= 1 ||
                map[x-1][y  ] >= 1 ||
                map[x-1][y+1] >= 1 ||
                map[x-1][y-1] >= 1 ){
                setting_is_possible = 0;
                break;
            }
            switch (dir){
                case 0:
                    x++; //Вправо
                    break;
                case 1:
                    y++; //Вниз
                    break;
                case 2:
                    x--; //Влево
                    break;
                case 3:
                    y--; //Вверх
                    break;
            }
        }
        //Если размещение возможно - ставим корабль
        if (setting_is_possible == 1){
            x = temp_x;
            y = temp_y;
            for (int i = 0; i < size_ship; i++){
                map[x][y] = ship_id;
                switch (dir){
                    case 0:
                        x++;
                        break;
                    case 1:
                        y++;
                        break;
                    case 2:
                        x--;
                        break;
                    case 3:
                        y--;
                        break;
                }
            }
            count_ship++;
        }
    }
}

bool ship_in_map(int x, int y, int dir, int size_ship) {
    bool in_map = 1;
    for (int i = 0; i < size_ship; i++){
        if (x < 0 || y < 0 || x >= N || y >= N){
            in_map = 0; // Корабль выходит за границы
            break;
        }
        switch(dir){
            case 0:
                x++; //Вправо
                break;
            case 1:
                y++; //Вниз
                break;
            case 2:
                x--; //Влево
                break;
            case 3:
                y--; //Вверх
                break;
        }
    }
    return in_map;
}

void set_manually_ships(int map[N][N], int size_ship, int ship_id) {
    int x = 0, y = 0; // Начальные координаты
    int dir = 0;      // Направление: 0 - горизонтально (вправо), 1 - вертикально (вниз)
    bool placed = false;
    
    // Временная карта для отображения текущего положения корабля
    int temp_map[N][N];
    for (int i = 0; i < N; i++) {
           for (int j = 0; j < N; j++) {
               temp_map[i][j] = map[i][j];
           }
       }
    
    while (!placed) {
        // Копируем оригинальную карту в временную
        for (int i = 0; i < N; i++) {
               for (int j = 0; j < N; j++) {
                   temp_map[i][j] = map[i][j];
               }
           }
        
        // Очищаем экран
        clearScreen();
        
        // "Ставим" корабль на временную карту для отображения
        int curr_x = x, curr_y = y;
        bool can_place = true;
        
        // Проверяем, можно ли поставить корабль
        for (int i = 0; i < size_ship; i++) {
            if (curr_x < 0 || curr_x >= N || curr_y < 0 || curr_y >= N) {
                can_place = false;
                break;
            }
            
            // Проверяем соседние клетки
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    int nx = curr_x + dx;
                    int ny = curr_y + dy;
                    if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                        if (map[nx][ny] > 0) {
                            can_place = false;
                            break;
                        }
                    }
                }
                if (!can_place) break;
            }
            if (!can_place) break;
            
            // Переходим к следующей клетке корабля
            if (dir == 0) curr_x++;
            else curr_y++;
        }
        
        // Если можно поставить, отображаем корабль на временной карте
        if (can_place) {
            curr_x = x;
            curr_y = y;
            for (int i = 0; i < size_ship; i++) {
                if (curr_x >= 0 && curr_x < N && curr_y >= 0 && curr_y < N) {
                    temp_map[curr_x][curr_y] = ship_id;
                }
                if (dir == 0) curr_x++;
                else curr_y++;
            }
        }
        
        // Отображаем карту
        cout << "Расстановка кораблей (размер устанавливаемого корабля: " << size_ship << ")\n";
        cout << "Управление: WASD - движение, R - поворот, SPACE - установить\n";
        cout << "\n";
        showmap(temp_map, nullptr, false);
        
        if (!can_place) {
            cout << "Невозможно поставить корабль здесь!\n";
        }
        
        // Обработка ввода
        char input = getch();
        switch (tolower(input)) {
            case 'w': if (y > 0) y--; break;
            case 's': if (y < N-1) y++; break;
            case 'a': if (x > 0) x--; break;
            case 'd': if (x < N-1) x++; break;
            case 'r': dir = (dir + 1) % 2; break; // Меняем направление
            case ' ': // Пробел - установить корабль
                if (can_place) {
                    // Устанавливаем корабль на основную карту
                    curr_x = x;
                    curr_y = y;
                    for (int i = 0; i < size_ship; i++) {
                        map[curr_x][curr_y] = ship_id;
                        if (dir == 0) curr_x++;
                        else curr_y++;
                    }
                    placed = true;
                    cout << "Корабль установлен!\n";
                    sleep(1);
                }
                break;
        }
    }
}
