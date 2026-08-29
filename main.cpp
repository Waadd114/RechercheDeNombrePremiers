#include <iostream>

#include "CalculateurPremiers.h"
#include "Chronometre.h"

int main()
{
    long nb = 0;
    unsigned nbThreads = 0;

    std::cout << "Valeur maximale: ";

    if (!(std::cin >> nb) || nb < 0) {
        std::cerr << "Valeur invalide.\n";
        return 1;
    }

    std::cout << "nombre(s) de thread(s) a creer: ";

    if (!(std::cin >> nbThreads) || nbThreads == 0) {
        std::cerr << "Nombre de threads invalide.\n";
        return 1;
    }

    Chronometre chrono;

    CalculateurPremiers calculateur(nbThreads, nb);
    calculateur.executer();

    std::string nomFichier = std::format("NbPremiersThreads_{}_{}.txt", nbThreads, nb);
    calculateur.sauvegarder(nomFichier);

    const auto duree = chrono.elapsed();
    std::ostringstream oss;

    oss << "Temps d'execution : " << std::chrono::duration_cast<std::chrono::microseconds>(duree).count() << " microsecondes ";
    oss << "(" << std::chrono::duration_cast<std::chrono::milliseconds>(duree).count() << " milliseconde(s), ";
    oss << std::chrono::duration_cast<std::chrono::seconds>(duree).count() << " seconde(s), ";
    oss << std::chrono::duration_cast<std::chrono::minutes>(duree).count() << " minute(s)) ";

    std::cout << oss.str();

    return 0;
}
