#include "Nombre.h"
#include <cmath>

bool Nombres::estPremier(long nombre) {

    if (nombre < 2)
        return false;

    const long limite = static_cast<long>(std::sqrt(static_cast<double>(nombre)));

    for (long i = 2; i <= limite; ++i) {
        if (nombre % i == 0) {
            return false;
        }
    }

    return true;
}