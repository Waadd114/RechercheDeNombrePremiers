#include "CalculateurPremiers.h"

#include <fstream>
#include <iostream>
#include <thread>

CalculateurPremiers::CalculateurPremiers(unsigned nombreThreads, long nbMax): nombreThreads_(nombreThreads), nbMax_(nbMax) {}

void CalculateurPremiers::executer() {
    std::cout << "Creation de " << nombreThreads_ << " threads\n";

    chercheurs_.reserve(nombreThreads_);

    for (unsigned i = 0; i < nombreThreads_; ++i)
        chercheurs_.emplace_back(2 + static_cast<long>(i),nbMax_ + 1,static_cast<long>(nombreThreads_));

    {
        std::vector<std::jthread> threads;
        threads.reserve(nombreThreads_);

        for (auto& chercheur : chercheurs_)
            threads.emplace_back(&ChercheurPremiers::chercher, &chercheur);
    }

    for (const auto& chercheur : chercheurs_) {
        const auto& partiels = chercheur.resultats();
        premiers_.insert(premiers_.end(), partiels.begin(), partiels.end());
    }

    std::sort(premiers_.begin(), premiers_.end());
}

void CalculateurPremiers::sauvegarder(const std::string& nomFichier) const {
    std::ofstream flux(nomFichier);

    for (long p : premiers_)
        flux << p << '\n';

    flux << "nombre total de nombre premier: " << premiers_.size() << '\n';
}

const std::vector<long>& CalculateurPremiers::premiers() const {
    return premiers_;
}