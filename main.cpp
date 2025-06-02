#include "battleship.h"


int main() {
    srand(static_cast<unsigned int>(time(NULL)));
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    int map[N][N] = {0};
    int bot_map[N][N] = {0};
    int ships1[NUM_SHIPS + 1] = {0, 4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    int ships2[NUM_SHIPS + 1] = {0, 4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    int mask[N][N] = {0};
    int bot_mask[N][N] = {0};
    
    //Главное меню
    int key1 = 0;
    int selected = 0; //0 - Играть, 1 - Правила
    do {
        clearScreen();
        cout << BLUE << "╔════════════════════╗" << RESET << "\n";
        cout << BLUE << "║" << RESET << "    МОРСКОЙ БОЙ     " << BLUE << "║" << RESET << "\n";
        cout << BLUE << "╠════════════════════╣" << RESET << "\n";
        
        if (selected == 0) {
        cout << BLUE << "║" << GREEN_BG << " > ИГРАТЬ <         " << RESET << BLUE << "║" << RESET << "\n";
        } else {
        cout << BLUE << "║" << RESET << "   Играть           " << BLUE << "║" << RESET << "\n";
        }
        
        if (selected == 1) {
        cout << BLUE << "║" << GREEN_BG << " > ПРАВИЛА <        " << RESET << BLUE << "║" << RESET << "\n";
        } else {
        cout << BLUE << "║" << RESET << "   Правила          " << BLUE << "║" << RESET << "\n";
        }
        
        cout << BLUE << "╚════════════════════╝" << RESET << "\n";
        cout << "Используйте стрелки ↑/↓ и Enter для выбора" << "\n";
        
        int key = getArrowKey();
        switch(key) {
            case 65: //Стрелка вверх
                selected = 0;
                break;
            case 66: //Стрелка вниз
                selected = 1;
                break;
            case 10: // Enter
            case 13: // (альтернативный)
                key1 = selected + 1;
                break;
        }
        
        if (key1 == 2) {
            clearScreen();
            cout << BLUE << "╔════════════════════════════════════════╗"<< RESET << "\n";
            cout << BLUE << "║" << RESET << "              ПРАВИЛА ИГРЫ              " << BLUE << "║" << RESET << "\n";
            cout << BLUE << "╚════════════════════════════════════════╝"<< RESET << "\n";
            cout << " 1. Расставьте свои корабли на поле 10x10\n";
            cout << " 2. По очереди стреляйте по клеткам    \n";
            cout << " 3. Побеждает тот, кто первым потопит   \n";
            cout << "    все корабли противника             \n";
            cout << "                                        \n";
            cout << " Управление при расстановке:            \n";
            cout << " WASD - движение, R - поворот, Пробел - установка корабля  \n";
            cout << "\n";
            cout << "Нажмите любую клавишу для продолжения...";
            cout << "\n";
            getch();
            key1 = 0; // Сбрасываем выбор после показа правил
        }
    } while (key1 != 1);
    int key3 = 0;
    int selected2 = 0; //0 - Случайная, 1 - Ручная
    do {
        clearScreen();
        cout << BLUE << "╔══════════════════════════════╗" << RESET << "\n";
        cout << BLUE << "║" << RESET << "  РАССТАНОВКА КОРАБЛЕЙ        " << BLUE << "║" << RESET << "\n";
        cout << BLUE << "╠══════════════════════════════╣" << RESET << "\n";
        
        //"Случайная расстановка"
        if (selected2 == 0) {
        cout << BLUE << "║" << GREEN_BG << " > СЛУЧАЙНАЯ РАССТАНОВКА <    " << RESET << BLUE << "║" << RESET << "\n";
        } else {
        cout << BLUE << "║" << RESET << "   Случайная расстановка      " << BLUE << "║" << RESET << "\n";
        }
        
        //"Ручная расстановка"
        if (selected2 == 1) {
        cout << BLUE << "║" << GREEN_BG << " > РУЧНАЯ РАССТАНОВКА <       " << RESET << BLUE << "║" << RESET << "\n";
        } else {
        cout << BLUE << "║" << RESET << "   Ручная расстановка         " << BLUE << "║" << RESET << "\n";
        }
        
        cout << BLUE << "╚══════════════════════════════╝" << RESET << "\n";
        cout << "Используйте стрелки ↑/↓ и Enter для выбора" << "\n";
        
        int input = getArrowKey();
        switch(input) {
            case 65:
                selected2 = 0;
                break;
            case 66:
                selected2 = 1;
                break;
            case 10:
            case 13:
                key3 = selected2 + 1;
                break;
        }
        
        if (key3 == 1) {
            clearScreen();
            cout << BLUE << "╔══════════════════════════════╗" << RESET << "\n";
            cout << BLUE << "║" << RESET << "  СЛУЧАЙНАЯ РАССТАНОВКА...    " << BLUE << "║" << RESET << "\n";
            cout << BLUE << "╚══════════════════════════════╝" << RESET << "\n";
            sleep(1);
            for (int i = 1; i <= NUM_SHIPS; i++) {
                set_rand_ships(map, ships1[i], i);
                set_rand_ships(bot_map, ships2[i], i);
            }
            break;
        }
        else if (key3 == 2) {
    clearScreen();
    // Расстановка кораблей вручную
    int ship_sizes[] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    for (int i = 0; i < NUM_SHIPS; i++) {
        set_manually_ships(map, ship_sizes[i], i+1);
        clearScreen();
    }
    // Компьютер расставляет свои корабли случайно
    clearScreen();
    cout << BLUE << "╔══════════════════════════════╗" << RESET << "\n";
    cout << BLUE << "║" << RESET << "  КОМПЬЮТЕР РАССТАВЛЯЕТ...    " << BLUE << "║" << RESET << "\n";
    cout << BLUE << "╚══════════════════════════════╝" << RESET << "\n";
    sleep(1);
    for (int i = 1; i <= NUM_SHIPS; i++) {
        set_rand_ships(bot_map, ships2[i], i);
    }
    break;
}

} while (true);
    
    // Основной игровой цикл
    bool turn = 0; // 0 - ход компьютера, 1 - ход игрока
    bool winPeople = false, winBot = false;
    int x = 0, y = 0, xB = 0, yB = 0;
    
    //Состояние прицельной стрельбы компьютера
    TargetingState targetState;
    bool targetingMode = false; //Режим прицельной стрельбы
    
    while (!winPeople && !winBot) {
        int resultShoting = 0;
        bool shotMade = false; //Флаг, что выстрел сделан
        clearScreen();
        
        //Получаем строки для полей
        vector<string> playerLines = get_map_lines(map, mask, false);
        vector<string> botLines = get_map_lines(bot_map, bot_mask, true);
        
        cout << BLUE << "╔════════════════════╗" << RESET << "    " << BLUE << "╔════════════════════╗" << RESET << "\n";
        cout << BLUE << "║" << RESET << "     ВАШЕ ПОЛЕ      " << BLUE << "║" << RESET << "    "
             << BLUE << "║" << RESET << "  ПОЛЕ КОМПЬЮТЕРА   " << BLUE << "║" << RESET << "\n";
        cout << BLUE << "╚════════════════════╝" << RESET << "    " << BLUE << "╚════════════════════╝" << RESET << "\n";
        
        for (int i = 0; i < playerLines.size(); i++) {
            cout << playerLines[i] << "    " << botLines[i] << endl;
        }
        
        if (turn == 1) { // Ход игрока
            cout << "\n";
            cout << "ВАШ ХОД:\n";
    
            // Обработка ввода с проверкой
            bool validInput = false;
                while (!validInput) {
                    cout << "Введите координаты (два числа через пробел) -> ";
                    // Считываем всю строку
                    string input;
                    getline(cin, input);
                    // Проверяем, что в строке ровно два числа
                    istringstream iss(input);
                    if (!(iss >> x >> y)) {
                        cout << "Ошибка! Введите 2 цифры.\n";
                        continue;
                    }
                    // Проверяем, что после двух чисел нет лишних символов
                    char extra;
                    if (iss >> extra) {
                        cout << "Ошибка! Введите только два числа.\n";
                        continue;
                    }
                    // Проверка диапазона
                    if (x < 0 || x >= N || y < 0 || y >= N) {
                        cout << "Координаты должны быть от 0 до " << N-1 << "!\n";
                        continue;
                    }
                    // Проверка, не стреляли ли сюда ранее
                    if (bot_mask[x][y] == 1) {
                        cout << "Вы уже стреляли в эту клетку!\n";
                        continue;
                    }
                    
                    validInput = true;
                }
            
            resultShoting = shotInShips(bot_map, x, y, ships2, bot_mask);
            
            if (resultShoting == 1) {
                cout << "Попал! Корабль ранен!\n";
            }
            else if (resultShoting == 2) {
                bool life = false;
                for (int i = 1; i <= NUM_SHIPS; i++) {
                    if (ships2[i] != 0) life = true;
                }
                
                if (!life) {
                    winPeople = true;
                }
                
                cout << "УБИТ! Корабль уничтожен!\n";
            }
            else {
                cout << "Промах! Ход переходит к компьютеру.\n";
                turn = !turn;
            }
            sleep(2);
        }
        else { // Ход компьютера
            cout << "\n";
            cout << "ХОД КОМПЬЮТЕРА\n";
            
            // Прицельная стрельба
            if (targetingMode) {
                // Начальная фаза: проверка направлений вокруг первого попадания
                if (targetState.state == 0) {
                    while (!targetState.directionsToTry.empty() && !shotMade) {
                        int d = targetState.directionsToTry.back();
                        targetState.directionsToTry.pop_back();
                        int x = targetState.firstHitX + dx[d];
                        int y = targetState.firstHitY + dy[d];
                        
                        if (x >= 0 && x < N && y >= 0 && y < N && mask[x][y] == 0) {
                            resultShoting = shotInShips(map, x, y, ships1, mask);
                            shotMade = true;
                            
                            if (resultShoting == 0) { // Промах
                                turn = !turn; // Передача хода
                                cout << "Компьютер промахнулся!\n";
                            }
                            else { // Попадание
                                targetState.lastHitX = x;
                                targetState.lastHitY = y;
                                targetState.direction = d;
                                
                                // Удаление противоположного направления
                                int oppDir = (d + 2) % 4;
                                auto it = find(targetState.directionsToTry.begin(),
                                              targetState.directionsToTry.end(), oppDir);
                                if (it != targetState.directionsToTry.end()) {
                                    targetState.directionsToTry.erase(it);
                                }
                                
                                if (resultShoting == 2) { // Убийство
                                    targetingMode = false;
                                    cout << "Компьютер убил ваш корабль!\n";
                                }
                                else {
                                    targetState.state = 1; // Переход к движению по направлению
                                    cout << "Компьютер попал! Корабль ранен!\n";
                                }
                            }
                            break;
                        }
                    }
                    
                    // Если направления закончились
                    if (!shotMade && targetState.directionsToTry.empty()) {
                        targetingMode = false;
                    }
                }
                // Движение в текущем направлении
                else if (targetState.state == 1) {
                    int x = targetState.lastHitX + dx[targetState.direction];
                    int y = targetState.lastHitY + dy[targetState.direction];
                    
                    if (x >= 0 && x < N && y >= 0 && y < N && mask[x][y] == 0) {
                        resultShoting = shotInShips(map, x, y, ships1, mask);
                        shotMade = true;
                        
                        if (resultShoting == 0) { // Промах
                            turn = !turn;
                            targetState.state = 2; // Переход к проверке противоположного направления
                            cout << "Компьютер промахнулся!\n";
                        }
                        else if (resultShoting == 1) { // Ранение
                            targetState.lastHitX = x;
                            targetState.lastHitY = y;
                            cout << "Компьютер попал! Корабль ранен!\n";
                        }
                        else if (resultShoting == 2) { // Убийство
                            targetState.lastHitX = x;
                            targetState.lastHitY = y;
                            targetingMode = false;
                            cout << "Компьютер убил ваш корабль!\n";
                        }
                    }
                    else { // Недопустимая клетка
                        targetState.state = 2; // Переход к проверке противоположного направления
                    }
                }
                // Проверка противоположного направления
                else if (targetState.state == 2) {
                    int oppDir = (targetState.direction + 2) % 4;
                    int x = targetState.firstHitX + dx[oppDir];
                    int y = targetState.firstHitY + dy[oppDir];
                    
                    if (x >= 0 && x < N && y >= 0 && y < N && mask[x][y] == 0) {
                        resultShoting = shotInShips(map, x, y, ships1, mask);
                        shotMade = true;
                        
                        if (resultShoting == 0) { // Промах
                            turn = !turn;
                            targetingMode = false; // Возврат к случайной стрельбе
                            cout << "Компьютер промахнулся!\n";
                        }
                        else { // Попадание
                            targetState.lastHitX = x;
                            targetState.lastHitY = y;
                            targetState.direction = oppDir;
                            
                            if (resultShoting == 2) { // Убийство
                                targetingMode = false;
                                cout << "Компьютер убил ваш корабль!\n";
                            }
                            else {
                                targetState.state = 3; // Переход к движению в противоположном направлении
                                cout << "Компьютер попал! Корабль ранен!\n";
                            }
                        }
                    }
                    else { // Недопустимая клетка
                        targetingMode = false; // Возврат к случайной стрельбе
                    }
                }
                // Движение в противоположном направлении
                else if (targetState.state == 3) {
                    int x = targetState.lastHitX + dx[targetState.direction];
                    int y = targetState.lastHitY + dy[targetState.direction];
                    
                    if (x >= 0 && x < N && y >= 0 && y < N && mask[x][y] == 0) {
                        resultShoting = shotInShips(map, x, y, ships1, mask);
                        shotMade = true;
                        
                        if (resultShoting == 0) { // Промах
                            turn = !turn;
                            targetingMode = false; // Возврат к случайной стрельбе
                            cout << "Компьютер промахнулся!\n";
                        }
                        else if (resultShoting == 1) { // Ранение
                            targetState.lastHitX = x;
                            targetState.lastHitY = y;
                            cout << "Компьютер попал! Корабль ранен!\n";
                        }
                        else if (resultShoting == 2) { // Убийство
                            targetState.lastHitX = x;
                            targetState.lastHitY = y;
                            targetingMode = false;
                            cout << "Компьютер убил ваш корабль!\n";
                        }
                    }
                    else { // Недопустимая клетка
                        targetingMode = false; // Возврат к случайной стрельбе
                    }
                }
            }
            
            // Случайная стрельба
            if (!targetingMode && !shotMade) {
                do {
                    xB = rand() % N;
                    yB = rand() % N;
                    resultShoting = shotInShips(map, xB, yB, ships1, mask);
                } while (resultShoting == 3); // Пока не найдем нестрелянную клетку

                shotMade = true;
                
                if (resultShoting == 0) {
                    turn = !turn;
                    cout << "Компьютер промахнулся!\n";
                }
                else if (resultShoting == 1) {
                    //Переход в режим прицельной стрельбы
                    targetingMode = true;
                    targetState.state = 0;
                    targetState.firstHitX = xB;
                    targetState.firstHitY = yB;
                    targetState.lastHitX = xB;
                    targetState.lastHitY = yB;
                    targetState.direction = -1;
                    targetState.directionsToTry = {0, 1, 2, 3}; //Все направления
                    cout << "Компьютер попал! Корабль ранен!\n";
                }
                else if (resultShoting == 2) {
                    cout << "Компьютер убил ваш корабль!\n";
                }
            }
            sleep(2);
        }
        
        //Проверка на победу
        winPeople = true;
        winBot = true;
        
        for (int i = 1; i <= NUM_SHIPS; i++) {
            if (ships2[i] > 0) winPeople = false;
            if (ships1[i] > 0) winBot = false;
        }
    }
    
    //Вывод результата игры
    clearScreen();
    cout << BLUE << "╔══════════════════════════════╗" << RESET << "\n";
    if (winPeople) {
        cout << BLUE << "║" << RESET << "         ВЫ ПОБЕДИЛИ!         " << BLUE << "║" << RESET << "\n";
    }
    else {
        cout << BLUE << "║" << RESET << "        ВЫ ПРОИГРАЛИ...       " << BLUE << "║" << RESET << "\n";
    }
    cout << BLUE << "╠══════════════════════════════╣" << RESET << "\n";
    cout << BLUE << "║" << RESET << " Нажмите любую клавишу для    " << BLUE << "║" << RESET << "\n";
    cout << BLUE << "║" << RESET << " выхода...                    " << BLUE << "║" << RESET << "\n";
    cout << BLUE << "╚══════════════════════════════╝" << RESET << "\n";
    getch();
    return 0;
}

