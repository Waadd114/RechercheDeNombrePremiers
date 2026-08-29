#ifndef RECHERCHE_DE_NOMBRE_PREMIERS_CHRONOMETRE_H
#define RECHERCHE_DE_NOMBRE_PREMIERS_CHRONOMETRE_H
#pragma once
#include <chrono>

/**
* Chronomètre RAII : démarre à la construction, elapsed() donne, le temps écoulé depuis.
*/
class Chronometre
{
    public:
    Chronometre();
    [[nodiscard]] std::chrono::steady_clock::duration elapsed() const;

    private:
        std::chrono::steady_clock::time_point debut_;
};

#endif //RECHERCHE_DE_NOMBRE_PREMIERS_CHRONOMETRE_H
