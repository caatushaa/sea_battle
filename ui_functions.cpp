#include "battleship.h"

void printColored(char c, int color) {
    cout << "\033[1;3" << color << "m" << c << "\033[0m";
}
int getArrowKey() {
    int ch = getch();
    if (ch == 27) {
        ch = getch();
        if (ch == 91) {
            ch = getch();
            return ch;
        }
    }
    return ch;
}
int getch() {
    struct termios oldt, newt; // Структуры для хранения настроек терминала
    int ch;  // Переменная для считанного символа

    // Получаем текущие настройки терминала (стандартный ввод STDIN_FILENO) и сохраняем их в oldt для последующего восстановления
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    
    // Изменяем флаги управления терминалом:
    // ~ICANON - отключаем канонический режим (теперь не нужно нажимать Enter)
    // ~ECHO   - отключаем отображение вводимых символов
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Применяем новые настройки немедленно (TCSANOW)
    ch = getchar();
    // Восстанавливаем оригинальные настройки терминала
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void clearScreen() {
    system("clear");
    cout.flush();
}


