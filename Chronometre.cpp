#include "Chronometre.h"

Chronometre::Chronometre() : debut_(std::chrono::steady_clock::now()) {}

std::chrono::steady_clock::duration Chronometre::elapsed() const
{
    return std::chrono::steady_clock::now() - debut_;
}