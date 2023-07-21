/*8. Морской бой (дополнительное задание)
Требуется реализовать упрощённую игру в морской бой. Игровое поле размером 10 на 10 клеток. 

Участвуют два игрока. В арсенале каждого из них 4 маленьких кораблика размером в одну клетку, 
3 небольших корабля размером в две клетки, 2 средних корабля размером в три клетки и один большой 
корабль размером в четыре клетки. Для простоты клетки поля пронумерованы по вертикали от 0 до 9 и по 
горизонтали от 0 до 9. Мы не будем использовать классические наименования клеток, такие как B4, C6, 
а просто два индекса. Вначале игроки по очереди расставляют корабли, начиная с самых маленьких и 
заканчивая большими. Маленькие корабли в одну клетку расставляются с помощью указания одной клетки-точки 
на поле, к примеру 2,1. Корабли размерностью от двух клеток и выше расставляются с помощью координат 
их начала и конца, к примеру: 0,1–0,3. Корабли могут быть установлены только строго вертикально или 
горизонтально. Установка корабля по диагонали недопустима, об этом тоже надо сообщить пользователю. 
Если корабль не может быть размещён на заданных клетках из-за того, что он столкнётся с другим кораблём 
(окажется на его клетках) или выйдет за пределы поля, то игроку должно быть сделано предупреждение, 
после которого он должен переставить корабль на новые валидные координаты. В нашем упрощённом варианте 
игры мы не будем обсчитывать соприкосновения кораблей друг с другом, а потому корабли вполне можно 
будет размещать друг к другу вплотную, борт к борту. После того как все корабли расставлены, начинается 
игра. Игроки по очереди атакуют друг друга, называя координаты выстрела. После выстрела в консоль выводится
информация о его результате: попал или мимо. Если выстрел успешен, клетка, на которой был корабль 
(или его фрагмент), затирается и становится пустой. Игра заканчивается тогда, когда все корабли одной из 
сторон будут полностью уничтожены. Как только это произойдёт, в консоль выводится информация с номером 
игрока, который победил.

Советы и рекомендации
Действия игроков практически одинаковые, их можно объединить в функции.

В программе достаточно иметь два поля, по одному на каждого игрока.

Лучше создать три отдельные функции: одну для размещения одного корабля, еще одну как обёртку над первой 
(она будет размещать все корабли), а третью для удара по координате. Также вам потребуются два глобальных
массива для двух отдельных участков моря:

bool field_1[10][10]; 
bool field_2[10][10];

Что оценивается
Корабли расставляются правильно.
Есть возможность выиграть.
Реализован понятный и удобный для пользователя интерфейс игры.
*/

#include <iostream>

const int SIZE = 10;

// наличие корабля на соответствующей позиции или отсутствие корабля.
bool field_1[SIZE][SIZE];
bool field_2[SIZE][SIZE];

// Функция для вывода игрового поля на экран
void printField(bool field[SIZE][SIZE]) 
{
    std::cout << "  "; // два пробела перед выводом столбцов
    // вывод столбцов
    for (int i = 0; i < SIZE; i++)
    {
        std::cout << i << " ";
    }
    std::cout << '\n';

    // вводим строки и заполняем их символами ■ и -
    for (int i = 0; i < SIZE; i++) 
    {
        std::cout << i << " ";
        for (int j = 0; j < SIZE; ++j) 
        {
            if (field[i][j])
                std::cout << "■ ";
            else
                std::cout << "- ";
        }
        std::cout << '\n';
    }
}

// Функция для размещения одного корабля на поле
bool placeShip(bool field[SIZE][SIZE], int x1, int y1, int x2, int y2)
{
    if (x1 < 0 || x1 >= SIZE || y1 < 0 || y1 >= SIZE ||
        x2 < 0 || x2 >= SIZE || y2 < 0 || y2 >= SIZE) 
    {
        std::cout << "Error! Ship is out of field" << '\n';
        return false;
    }

    // проверка на диоганаль
    if (x1 != x2 && y1 != y2) 
    {
        std::cout << "Error! The ship must be vertical or horizontal." << '\n';
        return false;
    }

    // пересекаечение кораблей
    for (int i = x1; i <= x2; i++) 
    {
        for (int j = y1; j <= y2; j++) 
        {
            if (field[i][j]) 
            {
                std::cout << "Error! The ship intersects with other ships." << '\n';
                return false;
            }
        }
    }

    // заполнение ячеек кораблем
    for (int i = x1; i <= x2; i++) 
    {
        for (int j = y1; j <= y2; j++) 
        {
            field[i][j] = true;
        }
    }
    return true;
}

// Функция для размещения всех кораблей одного игрока
void placeAllShips(bool field[SIZE][SIZE]) 
{
    std::cout << "Place of crusts on ships: " << '\n';

    int singleShipCount = 4;
    int doubleShipCount = 3;
    int tripleShipCount = 2;
    int quadShipCount = 1;

    while (singleShipCount + doubleShipCount + tripleShipCount + quadShipCount > 0) 
    {
        printField(field);

        int x1, y1, x2, y2;
        int ship;

        if (singleShipCount > 0) ship = 1;
        else if (doubleShipCount > 0) ship = 2;
        else if (tripleShipCount > 0) ship = 3;
        else if (quadShipCount > 0) ship = 4;

        std::cout << "Enter the coordinates of the " << ship << " cell: ";
        std::cin >> x1 >> y1;

        if (singleShipCount > 0) 
        {
            x2 = x1;
            y2 = y1;
            if (placeShip(field, x1, y1, x2, y2)) 
            {
                singleShipCount--;
                continue;
            }
        }

        std::cout << "Enter the second coordinates of the ship: ";
        std::cin >> x2 >> y2;

        int size = std::max(abs(x1 - x2), abs(y1 - y2)) + 1;

        if (size == 2 && doubleShipCount > 0) 
        {
            if (placeShip(field, x1, y1, x2, y2)) 
            {
                doubleShipCount--;
                continue;
            }
        }
        else if (size == 3 && tripleShipCount > 0) 
        {
            if (placeShip(field, x1, y1, x2, y2)) 
            {
                tripleShipCount--;
                continue;
            }
        }
        else if (size == 4 && quadShipCount > 0) 
        {
            if (placeShip(field, x1, y1, x2, y2)) 
            {
                quadShipCount--;
                continue;
            }
        }
        std::cout << "Error! It is impossible to place a ship with such coordinates." << '\n';
    }
}

// Функция для удара по координате на поле противника
void attack(bool field[SIZE][SIZE], bool enemyField[SIZE][SIZE], int x, int y) 
{
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) 
    {
        std::cout << "Error! Incorrect firing coordinates." << '\n';
        return;
    }

    if (enemyField[x][y]) 
    {
        std::cout << "Ship is shot down" << '\n';
        field[x][y] = false;
    }
    else 
    {
        std::cout << "Missed the mark!" << '\n';
    }
}

// Функция для проверки, остались ли корабли на поле
bool hasShipsLeft(bool field[SIZE][SIZE]) 
{
    for (int i = 0; i < SIZE; ++i) 
    {
        for (int j = 0; j < SIZE; ++j) 
        {
            if (field[i][j])
                return true;
        }
    }
    return false;
}

int main() 
{
    std::cout << "Player 1, place your ships:" << '\n';
    placeAllShips(field_1);

    std::cout << "Player 2, place your ships:" << '\n';
    placeAllShips(field_2);

    int currentPlayer = 1;

    while (true) 
    {
        std::cout << "Player's turn " << currentPlayer << '\n';
        int x, y;
        std::cout << "Enter the coordinates of the shot: ";
        std::cin >> x >> y;

        if (currentPlayer == 1) 
        {
            attack(field_2, field_1, x, y);
            if (!hasShipsLeft(field_2)) 
            {
                std::cout << "Player 1 wins!" << '\n';
                break;
            }
        }
        else
        {
            attack(field_1, field_2, x, y);
            if (!hasShipsLeft(field_1))
            {
                std::cout << "Player 2 wins!" << '\n';
                break;
            }
        }
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }
    return 0;
}
