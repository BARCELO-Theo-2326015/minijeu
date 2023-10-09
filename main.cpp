#include <iostream>
#include <vector>

#include <chrono>
#include <thread>

#include <future>

using namespace std;

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

void renderMap(vector<vector<unsigned>> table) {
    // listage vertical
    for(unsigned i = 0; i < table.size(); ++i) {
        // listage horizontal
        for(unsigned j = 0; j < table[i].size(); ++j) {
            switch(table[i][j])
            {
                case 1:
                    cout << " ";
                    break;
                case 2:
                    cout << "*";
                    break;
                default:
                    cout << " ";
            }
        }
        cout << endl;
    }
}

void createMap(vector<vector<unsigned>> table, unsigned nbColumn, vector<vector<unsigned>> snakeWhere) {
    // création des différentes cases verticales du tableau
    for(unsigned i = 0; i < nbColumn; ++i) {
        // creation d'un tableau par case pour cases horizontales
        vector<unsigned> newTable;

        // création des différentes cases horizontales du nouveau tableau
        for(unsigned j = 0; j < nbColumn; ++j) {
            // ajout de la case verticale
            if(j == snakeWhere[0][0] && i == snakeWhere[0][1]) newTable.push_back(2);
            else newTable.push_back(1);
        }

        // ajout de la table verticale
        table.push_back(newTable);
    }
}

void changeSnakePosition(unsigned snakeWhat, vector<vector<unsigned>> snakeWhere) {
    vector<unsigned> newPos = snakeWhere[0];
    switch(snakeWhat)
    {
        // a gauche
        case 1:
            // création de la nouvelle position
            newPos[0] = newPos[0]-1; // horizontal
            break;
        // a droite
        case 2:
            // création de la nouvelle position
            newPos[0] = newPos[0]+1; // horizontal
            break;
        // en haut
        case 3:
            // création de la nouvelle position
            newPos[1] = newPos[1]-1; // vertical
            break;
        // en bas
        case 4:
            // création de la nouvelle position
            newPos[1] = newPos[1]+1; // vertical
            break;
        default:
            break;
    }
    // insertion de la nouvelle position
    snakeWhere.insert(snakeWhere.begin(), snakeWhere[0]);
    // supression de la dernière position
    snakeWhere.resize(snakeWhere.size()-1);
}

int main()
{
    // affichage de titre
    cout << "Bienvenue dans le Snake (version mini)";
    sleep_for(seconds(1));
    cout << 3;
    sleep_for(seconds(1));
    cout << 2;
    sleep_for(seconds(1));
    cout << 1;
    sleep_for(seconds(1));

    // nombre de colomnes a définir
    unsigned nbColumn = 8;

    // variable du déplacement du snake
    unsigned snakeWhat = 1; // 1 = gauche, 2 = droite, 3 = haut, 4 = bas

    // position du snake selon chaque pixels
    vector<vector<unsigned>> snakeWhere = {{nbColumn/2,nbColumn/2}};

    // création du tableau principal vertical
    vector<vector<unsigned>> table;

    // création de la map
    createMap(table, nbColumn, snakeWhere);

    // render original
    renderMap(table);

    // boucle
    while(true) {
        sleep_for(nanoseconds(500));

        // modification de la position du snake
        changeSnakePosition(snakeWhat, snakeWhere);

        // changement de la map
        createMap(table, nbColumn, snakeWhere);

        // render de la map
        renderMap(table);
    }

    return 0;
}
