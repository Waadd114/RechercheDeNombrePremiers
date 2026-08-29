#include "ChercheurPremiers.h"
#include "Nombre.h"
#include <vector>

ChercheurPremiers::ChercheurPremiers(long debut, long fin, long pas) : debut_(debut), fin_(fin), pas_(pas) {}

void ChercheurPremiers::chercher()
{
    for (long i = debut_; i < fin_; i += pas_) {
        if (Nombres::estPremier(i)) {
            resultats_.push_back(i);
        }
    }
}

const std::vector<long>& ChercheurPremiers::resultats() const
{
    return resultats_;
}
