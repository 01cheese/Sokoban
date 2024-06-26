#include <iostream>
#include <cstdlib>

using namespace std;

struct Position {
    int x;
    int y;
};

const char WORKER_CHAR = 'R';
const char PACKAGE_CHAR = 'x';
const char PLACE_CHAR = 'O';
const char WALL_CHAR = '#';

const char FIRST_MAP[100][200] = {
        "########################",
        "######            ######",
        "####    R           ####",
        "###     ### #### xx  ###",
        "###            #     ###",
        "###     #      #     ###",
        "###     #    O #     ###",
        "###     ########     ###",
        "####                 ###",
        "###O                 ###",
        "#######         ########",
        "########################",
};

const char SECOND_MAP[100][200] = {
        "#######################",
        "########   ############",
        "######## x ############",
        "######## x ###O########",
        "########## ###O########",
        "##########    O########",
        "######### x #  ########",
        "#########R  ###########",
        "#######################"
};

const char THIRD_MAP[100][200] = {
        "########################",
        "##########          ####",
        "#########OR    #########",
        "########### x  #########",
        "###   ###O# x  #########",
        "##    ### # O  #########",
        "##    ###x  xxO#########",
        "##    ###   O  #########",
        "########################"
};

enum direction {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NONE
};

void findPosition(char MAP[100][200], Position* worker, Position* package, Position* place,
                  int* packageCounter, int* placeCounter) {
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 200; j++) {
            if (MAP[i][j] == WORKER_CHAR) {
                worker->x = j;
                worker->y = i;
                MAP[i][j] = ' ';
            } else if (MAP[i][j] == PACKAGE_CHAR) {
                package[*packageCounter].x = j;
                package[*packageCounter].y = i;
                MAP[i][j] = ' ';
                (*packageCounter)++;
            } else if (MAP[i][j] == PLACE_CHAR) {
                place[*placeCounter].x = j;
                place[*placeCounter].y = i;
                (*placeCounter)++;
            }
        }
    }
}

void printMap(char MAP[100][200], Position* worker, Position* package, Position* place, int packageCounter) {
    system("cls");
    cout << "\n\n\n";
    for (int i = 0; i < 100; i++) {
        bool nextLine = false;
        cout << "\t\t\t";
        for (int j = 0; j < 200; j++) {
            char field = ' ';

            if ((worker->y == i) && (worker->x == j)) {
                cout << WORKER_CHAR;
                continue;
            }

            for (int k = 0; k < packageCounter; k++) {
                if ((package[k].x == j) && (package[k].y == i)) {
                    field = PACKAGE_CHAR;
                    break;
                } else if ((place[k].x == j) && (place[k].y == i)) {
                    field = PLACE_CHAR;
                }
            }

            if (field != ' ') {
                cout << field;
                continue;
            }

            if (MAP[i][j] != '\0') {
                cout << MAP[i][j];
                nextLine = true;
            }
        }
        if (nextLine) cout << endl;
    }
}

bool checkWall(char MAP[100][200], Position* package, Position* new_worker, Position* new_package,
               int packageCounter, int packageNumber) {
    if (MAP[new_worker->y][new_worker->x] == WALL_CHAR) return true;

    if (packageNumber >= 0) {
        if (MAP[new_package->y][new_package->x] == WALL_CHAR) return true;

        for (int i = 0; i < packageCounter; i++) {
            if ((package[i].x == new_package->x) && (package[i].y == new_package->y)) return true;
        }
    }
    return false;
}

void movement(char MAP[100][200], Position* worker, Position* package, Position* place,
              int* packageCounter, int* movesCounter, bool* gameEnd) {
    char key = cin.get();
    direction dir = NONE;

    switch (key) {
        case 'w':
            dir = UP;
            break;
        case 'a':
            dir = LEFT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'q':
            exit(0);
        default:
            if ((int)key != 10) {
                cout << " Invalid input: " << key << endl;
                system("pause");
            }
            break;
    }

    Position new_worker = *worker;
    Position new_package;

    if (dir == UP) new_worker.y--;
    else if (dir == DOWN) new_worker.y++;
    else if (dir == LEFT) new_worker.x--;
    else if (dir == RIGHT) new_worker.x++;

    int current_package = -1;

    for (int i = 0; i < *packageCounter; i++) {
        if ((package[i].x == new_worker.x) && (package[i].y == new_worker.y)) {
            new_package = package[i];
            current_package = i;
            break;
        }
    }

    if (current_package >= 0) {
        if (dir == UP) new_package.y--;
        else if (dir == DOWN) new_package.y++;
        else if (dir == LEFT) new_package.x--;
        else if (dir == RIGHT) new_package.x++;
    }

    if (!checkWall(MAP, package, &new_worker, &new_package, *packageCounter, current_package)) {
        *worker = new_worker;
        if (current_package >= 0) {
            package[current_package] = new_package;
        }
        (*movesCounter)++;
    }

    int onPlace[10] = {0};
    for (int k = 0; k < *packageCounter; k++) {
        for (int m = 0; m < *packageCounter; m++) {
            if ((package[k].x == place[m].x) && (package[k].y == place[m].y)) {
                onPlace[k] = 1;
            }
        }
    }

    *gameEnd = true;
    for (int k = 0; k < *packageCounter; k++) {
        if (!onPlace[k]) {
            *gameEnd = false;
            break;
        }
    }
}

void copyMap(const char FROM_MAP[100][200], char TO_MAP[100][200]) {
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 200; j++) {
            TO_MAP[i][j] = FROM_MAP[i][j];
        }
    }
}

int main() {
    char name[40];
    char choice;
    bool gameStart = false;
    bool gameEnd = false;
    int movesCounter = 0;

    Position worker = {0, 0};
    Position package[10];
    int packageCounter = 0;
    Position place[10];
    int placeCounter = 0;
    char currentMap[100][200];

    cout << " \n\n \t\t\t WELCOME TO SOKOBAN GAME! " << endl;
    cout << " \n\t Enter your name: ";
    cin >> name;
    cout << "\n\t Hello " << name << "!" << endl;

    while (!gameStart) {
        cout << " \t Choose your map: \n";
        cout << " \t\t1. First Map " << endl;
        cout << " \t\t2. Second Map " << endl;
        cout << " \t\t3. Third Map " << endl;
        cout << "\n\t\t";
        cin >> choice;

        switch (choice) {
            case '1':
                copyMap(FIRST_MAP, currentMap);
                gameStart = true;
                break;
            case '2':
                copyMap(SECOND_MAP, currentMap);
                gameStart = true;
                break;
            case '3':
                copyMap(THIRD_MAP, currentMap);
                gameStart = true;
                break;
            case 'q':
                exit(0);
            default:
                system("cls");
                cout << "\n Invalid option. Choose once again.  " << endl;
        }
    }

    findPosition(currentMap, &worker, package, place, &packageCounter, &placeCounter);

    while (!gameEnd) {
        printMap(currentMap, &worker, package, place, packageCounter);
        movement(currentMap, &worker, package, place, &packageCounter, &movesCounter, &gameEnd);
    }

    if (gameEnd) {
        system("cls");
        cout << "\n\n \t\t\t You have won, " << name << "! Congratulations! \n" << endl;
        cout << " \t\t\t Number of moves: " << movesCounter << endl;
    }

    system("pause");
    return 0;
}
