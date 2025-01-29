#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

const int taille = 4;
const int nbcoul= 6;

// generation d'un code secret aleatoire
std::vector<int> genererCodeSecret() {
    std::vector<int> code;
    for (int i = 0; i < taille; ++i) {
        code.push_back(rand() % nbcoul + 1);
    }
    return code;
}

// comparaison d'une tentative avec le code secret
void evaluerTentative(const std::vector<int>& codeSecret, const std::vector<int>& tentative, int& bienPlaces, int& malPlaces) {
    bienPlaces = 0;
    malPlaces = 0;

    std::vector<bool> marquesCode(taille, false);
    std::vector<bool> marquesTentative(taille, false);

    // verification des pions biens places
    for (int i = 0; i < taille; ++i) {
        if (tentative[i] == codeSecret[i]) {
            ++bienPlaces;
            marquesCode[i] = true;
            marquesTentative[i] = true;
        }
    }

    // Verification des pions mal places
    for (int i = 0; i < taille; ++i) {
        if (!marquesTentative[i]) {
            for (int j = 0; j < taille; ++j) {
                if (!marquesCode[j] && tentative[i] == codeSecret[j]) {
                    ++malPlaces;
                    marquesCode[j] = true;
                    break;
                }
            }
        }
    }
}

// lecture lorsque l'utilisateur effectue une tentative
std::vector<int> lireTentative() {
    std::vector<int> tentative(taille);
    std::cout << "Entrez votre tentative (" << taille << " chiffres entre 1 et " << nbcoul << ") : ";
    for (int i = 0; i < taille; ++i) {
        std::cin >> tentative[i];
    }
    return tentative;
}

int main() {
    srand(time(0));

    std::cout << "Bienvenue dans le jeu Mastermind !\n";

    // faire ressortir le code secret
    std::vector<int> codeSecret = genererCodeSecret();

    // variables
    int bienPlaces = 0, malPlaces = 0;
    int tentativesRestantes = 10;

    // boucle pour le jeu
    while (tentativesRestantes > 0) {
        std::cout << "\n Il vous reste " << tentativesRestantes << " tentatives." << std::endl;

        // Lire la tentative de l'utilisateur
        std::vector<int> tentative = lireTentative();

        // evaluer la tentative
        evaluerTentative(codeSecret, tentative, bienPlaces, malPlaces);

        // Afficher les resultats
        std::cout << "Bien places : " << bienPlaces << ", Mal places : " << malPlaces << std::endl;

        // Verifier si le joueur a gagne 
        if (bienPlaces == taille) {
            std::cout << "Felicitations ! Vous avez trouve le code secret !\n";
            return 0;
        }

        --tentativesRestantes;
    }

    // Si les tentatives du joueur sont terminees
    std::cout << "\n Vous avez epuise vos tentatives. Le code secret etait : ";
    for (int chiffre : codeSecret) {
        std::cout << chiffre << " ";
    }
    std::cout << "\n";

    return 0;
}
