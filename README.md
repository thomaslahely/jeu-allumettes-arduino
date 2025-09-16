#  Jeu d'Allumettes Arduino

Un jeu d'allumettes implémenté sur Arduino elegoo mega 2560 avec écran LCD et un clavier 4x4. L'ordinateur utilise l'algorithme MinMax pour jouer.

##  Règles du Jeu

- **Objectif** : Forcer l'adversaire à prendre la dernière allumette
- **Départ** : 21 allumettes
- **Tour de jeu** : Chaque joueur peut prendre 1, 2 ou 3 allumettes

##  Composants Nécessaires

### Hardware
- 1 × Arduino Uno/Mega (ici fait avec elegoo mega 2560)
- 1 × Écran LCD
- 1 × Clavier matriciel 4x4
- Câbles de connexion (male to male)
- Breadboard 

### Bibliothèques Arduino
```cpp
#include <Keypad.h>
#include <LiquidCrystal.h>
```

## 📋 Branchements

### Écran LCD (16x2)
| Pin LCD | Pin Arduino |
|---------|-------------|
| VSS     | GND         |
| VDD     | 5V          |
| V0      | Potentiomètre (contraste) |
| RS      | Pin 7       |
| Enable  | Pin 8       |
| D4      | Pin 9       |
| D5      | Pin 10      |
| D6      | Pin 11      |
| D7      | Pin 12      |
| A       | 5V (rétroéclairage) |
| K       | GND (rétroéclairage) |

### Clavier 4x4
| Clavier | Pin Arduino |
|---------|-------------|
| Ligne 1 | Pin 23      |
| Ligne 2 | Pin 25      |
| Ligne 3 | Pin 27      |
| Ligne 4 | Pin 29      |
| Colonne 1 | Pin 31    |
| Colonne 2 | Pin 33    |
| Colonne 3 | Pin 35    |
| Colonne 4 | Pin 37    |

### Disposition du Clavier
```
1  2  3  A
4  5  6  B  
7  8  9  C
*  0  #  D
```
*Seules les touches 1, 2, 3 sont utilisées pour le jeu*

## 🎯 Fonctionnement

### Interface Utilisateur
1. **Démarrage** : Affiche le nombre d'allumettes
2. **Tour du joueur** : Choisir 1, 2 ou 3 allumettes avec le clavier
3. **Tour de l'ordinateur** : L'IA calcule avec l'algorithme Minmax et joue 
4. **Fin de partie** : Annonce du gagnant

### Intelligence Artificielle - Algorithme MinMax

L'ordinateur utilise l'algorithme MinMax pour jouer de façon optimale :

```cpp
int minMax(int allumettes, int joueur) {
    // Cas terminal : plus d'allumettes
    if (allumettes == 0) {
        return (joueur == 1) ? 1 : -1;  // +1 si ordi gagne, -1 si perd
    }
    
    // Joueur maximisant (ordi)
    if (joueur == 1) {
        int max_eval = -1000;
        for(int i = 1; i <= 3; i++) {
            if (allumettes - i >= 0) {
                int eval = minMax(allumettes - i, 2);
                max_eval = max(max_eval, eval);
            }
        }
        return max_eval;
    }
    // Joueur minimisant (humain)  
    else {
        int min_eval = 1000;
        for(int i = 1; i <= 3; i++) {
            if (allumettes - i >= 0) {
                int eval = minMax(allumettes - i, 1);
                min_eval = min(min_eval, eval);
            }
        }
        return min_eval;
    }
}
```

### Stratégie Optimale
L'algorithme garantit que l'ordinateur :
- **Gagne** toujours s'il joue en premier avec 21 allumettes
- **Maintient** des positions gagnantes (laisse un multiple de 4 allumettes + 1)



Projet éducatif - Libre d'utilisation et de modification.

---

*Amusez-vous bien avec ce classique des jeux de stratégie ! 🎮🔥*
