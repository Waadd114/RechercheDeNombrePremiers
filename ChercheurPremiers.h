#ifndef RECHERCHE_DE_NOMBRE_PREMIERS_CHERCHEUR_H
#define RECHERCHE_DE_NOMBRE_PREMIERS_CHERCHEUR_H
#pragma once
#include <vector>

/**
* Class de travail confié à UN thread : chercher les nombres premiers parmi {debut, debut+pas, debut+2*pas, ...}
* tant que c'est < fin.
*/
class ChercheurPremiers {
    public:
        ChercheurPremiers(long debut, long fin, long pas);
        void chercher();
        [[nodiscard]] const std::vector<long>& resultats() const;

    private:
        long debut_;
        long fin_;
        long pas_;
        std::vector<long> resultats_{};
};

#endif //RECHERCHE_DE_NOMBRE_PREMIERS_CHERCHEUR_H
