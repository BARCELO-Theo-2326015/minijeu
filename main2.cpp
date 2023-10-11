#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> litUnFichier (const string & chemin)
{
    vector<string> toutesLesLignes;
    ifstream ifs (chemin);
    if (!ifs) return toutesLesLignes;
    for (string uneLigne;getline(ifs, uneLigne);)
        toutesLesLignes.push_back(uneLigne);
    return toutesLesLignes;
}

template <typename T>
void afficheVecteur (const vector<T> & V)
{
    for (const T & val : V)
        cout << val << endl;
    cout << endl;
}

// procédure affichePendu
void affichePendu(const unsigned etat) {
    switch(etat) {
        case 0:
            cout << endl;;
            break;
        case 1:
            cout << "_";
            break;
        case 2:
            cout << "  |   " << endl << "_____" << endl;
            break;
        case 3:
            cout << "  ___" << endl << "  |   " << endl << "_____" << endl;
            break;
        case 4:
            cout << "etat 4" << endl;
            break;
        case 5:
            cout << "etat 5" << endl;
            break;
        case 6:
            cout << "etat 6" << endl;
            break;
        case 7:
            cout << "etat 7" << endl;
            break;
        case 8:
            cout << "etat 8" << endl;
            break;
        case 9:
            cout << "etat 9" << endl;
            break;
        case 10:
            cout << "etat 10" << endl;
            break;
        case 11:
            cout << "etat 11" << endl;
            break;
        default:
            cout << "Il y a un problème..." << endl;
            break;
    }
}

int checkMot(vector<char> lettresDecouvertes, string mot) {
    string motcache;
    bool trouve = false;
    for(unsigned i = 0; i < mot.size()-1; ++i) {
        while(true) {
            ++i;
            if(i > lettresDecouvertes.size()-1) break;
            if(lettresDecouvertes[i] == mot[i]) trouve = true;
        }
        if(trouve) motcache = mot[i];
    }
    return (motcache == mot);
}

void afficheMot(vector<char> lettresDecouvertes, string mot) {
    string motcache;
    bool trouve = false;
    for(unsigned i = 0; i < mot.size()-1; ++i) {
        while(true) {
            ++i;
            if(i > lettresDecouvertes.size()-1) break;
            if(lettresDecouvertes[i] == mot[i]) trouve = true;
        }
        if(trouve) motcache = mot[i];
        else motcache = "_";
        cout << motcache;
    }
}

void decouverteLettre(vector<char> lettresDecouvertes, char lettre) {
    unsigned i = 0;
    bool trouve = false;
    while(true) {
        ++i;
        if(i > lettresDecouvertes.size()-1) break;
        if(lettresDecouvertes[i] == lettre) trouve = true;
    }
    if(!trouve) lettresDecouvertes.push_back(lettre);
}

int main()
{
    // variable pour les lettres découvertes
    vector<char> lettresDecouvertes;
    // état du pendu
    unsigned etat = 0;

    // lecture du fichier en vecteur
    vector<string> dicoFR (litUnFichier("../tp1_prendu/liste_francais.txt"));

    // configuration du random
    srand(time(NULL));

    // mot aléatoire
    unsigned N = 0 + rand() % (dicoFR.size() - 0);
    string mot = dicoFR[N];

    // système de lecture du mot utilisateur
    char lettre;
    cout << "Essayez de deviner le mot : ";
    cin >> lettre;
    cout << endl;

    // système infini du pendu avec points d'arrêt
    while(true) {
        // verifie si l'utilisateur a trouvé une lettre
        bool trouve = false;
        for(unsigned i = 0; i < mot.size()-1; ++i) {
            if(lettre == mot[i]) {
                cout << "Vous avez découvert une lettre !";
                decouverteLettre(lettresDecouvertes, lettre);
                trouve = true;
            } else {
                cout << "Vous n'avez pas découvert de lettre...";
            }
        }

        // verifie si on a gagné
        string motutilisateur;
        motutilisateur = lettre;
        if(checkMot(lettresDecouvertes, mot) || mot == motutilisateur) {
            cout << "Vous avez gagné !";
            break;
        }

        // si l'utilisateur n'a pas trouvé de lettre, on augmente l'état
        if(!trouve) ++etat;

        // affiche le pendu et le mot
        affichePendu(etat);
        afficheMot(lettresDecouvertes, mot);

        // si l'état est trop haut, le pendu est terminé, on perd
        if(etat == 11) {
            cout << "Vous avez perdu !";
            break;
        }
    }
    return 0;
}
