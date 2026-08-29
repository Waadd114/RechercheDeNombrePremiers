#ifndef RECHERCHE_DE_NOMBRE_PREMIERS_CALCULATEURPREMIERS_H
#define RECHERCHE_DE_NOMBRE_PREMIERS_CALCULATEURPREMIERS_H
#pragma once
#include <string>
#include <vector>
#include "ChercheurPremiers.h"

/**
 * Class d'orchestration les ChercheurPremiers : les crée, les lance chacun dans un thread, attend leur fin, fusionne
 * et trie les résultats.
 */
class CalculateurPremiers
{
public:
    CalculateurPremiers(unsigned nombreThreads, long nbMax);
    void executer();
    void sauvegarder(const std::string& nomFichier) const;
    [[nodiscard]] const std::vector<long>& premiers() const;

private:
    unsigned nombreThreads_;
    long nbMax_;
    std::vector<ChercheurPremiers> chercheurs_;
    std::vector<long> premiers_;
};

#endif //RECHERCHE_DE_NOMBRE_PREMIERS_CALCULATEURPREMIERS_H
