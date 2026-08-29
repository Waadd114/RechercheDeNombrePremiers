# Recherche de nombres premiers (multithread)

Programme C++23 qui calcule tous les nombres premiers jusqu'à une valeur maximale donnée, en répartissant le travail sur plusieurs threads.

## Sommaire

- [Le sujet](#le-sujet)
- [Principe de l'algorithme](#principe-de-lalgorithme)
- [Architecture du code](#architecture-du-code)
- [Compilation](#compilation)
- [Utilisation](#utilisation)
- [Résultats](#résultats)
- [Structure du projet](#structure-du-projet)

## Le sujet

On cherche à calculer l'ensemble des nombres premiers compris entre 2 et une valeur maximale choisie par l'utilisateur. Le test de primalité se fait par décomposition des diviseurs : un nombre est premier si aucune division euclidienne par les entiers compris entre 2 et sa racine carrée n'a de reste nul.

Le programme doit :
- écrire les nombres premiers trouvés dans un fichier texte ;
- permettre de comparer le temps d'exécution selon le nombre de threads utilisés ;
- répartir le travail de recherche entre plusieurs threads pour accélérer le calcul.

## Principe de l'algorithme

Le calcul est réparti entre threads par un système de **pas fixe** : avec `n` threads, le thread numéro `i` teste les nombres `2+i`, `2+i+n`, `2+i+2n`, ... jusqu'à la valeur maximale. Chaque nombre n'est donc testé qu'une seule fois, par un seul thread, sans aucun recouvrement.

Exemple avec une valeur maximale de 11 et 2 threads (thread 0 en rouge, thread 1 en bleu) :

| 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 |
|---|---|---|---|---|---|---|---|----|----|
| 🔴 | 🔵 | 🔴 | 🔵 | 🔴 | 🔵 | 🔴 | 🔵 | 🔴 | 🔵 |

Chaque thread accumule ses propres nombres premiers trouvés dans son résultat local. Une fois tous les threads terminés, leurs résultats sont fusionnés puis triés par ordre croissant avant d'être écrits dans le fichier de sortie.

## Architecture du code

Le programme est organisé en quatre classes, chacune avec une responsabilité unique :

| Classe | Rôle |
|---|---|
| `Nombres` | Fonction utilitaire statique `estPremier(long)` : test de primalité. |
| `ChercheurPremiers` | Le travail confié à **un** thread : teste une plage de nombres avec un pas donné, stocke son propre résultat. |
| `CalculateurPremiers` | Orchestre les `ChercheurPremiers` : les crée, les lance en threads, attend leur fin, fusionne et trie les résultats, écrit le fichier. |
| `Chronometre` | Petit chronomètre RAII pour mesurer le temps total d'exécution. |

Les threads sont gérés avec `std::jthread` (C++20/23), qui rejoint automatiquement chaque thread à sa destruction — pas de `pthread_join` ni de transtypage `void*` à gérer manuellement. Comme chaque `ChercheurPremiers` porte son propre résultat, deux threads n'écrivent jamais dans la même donnée : aucun mutex n'est nécessaire.

## Compilation

Le projet utilise **CMake** (minimum requis : voir `CMakeLists.txt`) et nécessite un compilateur supportant le C++23 (`std::jthread`, `std::format`).

### Avec CLion

1. Ouvrir le dossier du projet dans CLion : il détecte automatiquement `CMakeLists.txt`.
2. Choisir le profil **Release** en haut à droite (recommandé pour un exécutable à distribuer).
3. Cliquer sur le bouton ▶️ (Run), ou builder seul avec le marteau 🔨.

### En ligne de commande

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

L'exécutable est généré dans le dossier `build/` (`Recherche_de_nombre_premiers.exe`).

## Utilisation

Au lancement, le programme demande deux valeurs :

```
Valeur maximale: 1000000
nombre(s) de thread(s) a creer: 4
```

Il crée ensuite les threads, calcule les nombres premiers, et écrit le résultat dans un fichier nommé automatiquement d'après les paramètres saisis :

```
NbPremiersThreads_4_1000000.txt
```

Ce fichier contient tous les nombres premiers trouvés (un par ligne), suivis du nombre total de nombres premiers trouvés. Le temps d'exécution (en microsecondes, millisecondes, secondes et minutes) est affiché dans le terminal.

## Résultats

Mesures réalisées sur une machine avec 1 CPU / 4 cœurs à 2.50 GHz (turbo 3.50 GHz), 6 Go de RAM.

**Séquentiel (1 thread) :**

| Itérations | 100 | 1 000 | 100 000 | 1 000 000 | 10 000 000 |
|---|---|---|---|---|---|
| Temps (s) | 0,189 | 0,029 | 0,186 | 2,884 | 68,8 |

**Parallélisé :**

| Itérations | 100 | 1 000 | 100 000 | 1 000 000 | 10 000 000 |
|---|---|---|---|---|---|
| 2 threads | 0,033 | 0,035 | 0,11 | 1,075 | 20,51 |
| 4 threads | 0,38 | 0,034 | 0,102 | 0,82 | 13,098 |
| 8 threads | 0,35 | 0,036 | 0,105 | 0,681 | 9,123 |

Sur 10 000 000 d'itérations, passer de 1 à 8 threads divise le temps d'exécution par environ **7,5**. Le gain est net dès 2 threads, et continue de s'améliorer en ajoutant des threads, avec un rendement qui diminue progressivement (le nombre de cœurs physiques de la machine de test étant de 4).

## Structure du projet

```
.
├── CMakeLists.txt
├── main.cpp
├── Nombre.h / .cpp                         # Test de primalité
├── ChercheurPremiers.h / .cpp              # Travail d'un thread
├── CalculateurPremiers.h / .cpp            # Orchestration des threads
└── Chronometre.h / .cpp                    # Mesure du temps d'exécution
```
