## Projet hypermarché en C++ par Qassim-Tayab MANSOOR et Kacper KUPIS

### **INSTALLATION:**
---

#### Commencez par vous rendre dans votre répertoire de travail. Exemple : 
```shell
cd /home/user/Downloads/
```

#### Clonez ce repo :
```shell
git clone https://github.com/robot3456/ACH
```
#### Allez dans le répertoire où vous avez cloné. Exemple : 

```shell
cd /home/user/Downloads/ACH/
```

#### Lancez le makefile : 
```shell
make 
```

#### Lancez le jeu : 
```shell
./JeuHypermarche
```

#### Vous devriez vous retrouver avec un écran comme cela : 
```shell
------------------------------------
| Bienvenue aux commandes de votre |                                 
|         HYPERMARCHE !            |
------------------------------------


---------- TABEAU DES MEILLEURS SCORES ----------
-------------------------------------------------
RANG    NOM                             SCORE
-------------------------------------------------
-------------------------------------------------                                                         

                        TOUR N°1
-----------------------------------------------------------------                                         
|                                                       Prix    |
|                                                               |
| ouverture/fermetures de caisses :     0  x  2cr       = 0cr   |
| caisse(s) ouverte(s) :                0  x  3cr       = 0cr   |
| clients en attente :                  0  x  2cr       = 0cr   |
| clients en caisse :                   0  x  1cr       = 0cr   |
| Tour:                                                   1cr   |
|       ------------------------------------------------        |
| Total:                                                  1cr   |
|                                                               |
-----------------------------------------------------------------

[-] Caisse 1         [Fermée]
[-] Caisse 2:        [Fermée]
[-] Caisse 3:        [Fermée]
[-] Caisse 4:        [Fermée]
[-] Caisse 5:        [Fermée]
[-] Caisse 6:        [Fermée]
[-] Caisse 7:        [Fermée]
[-] Caisse 8:        [Fermée]
[-] Caisse 9:        [Fermée]
[-] Caisse 10:       [Fermée]

Budget: 1000 crédits.
Clients dans l'hypermarché: 100, en attente de caisse: 0 et aux caisses: 0.

Action sur les caisses ...
Choisir une caisse à changer[1-10] OU changer l'état de toutes les caisses [A]. Appliquer les changements et jouer le tour[P] :  

``` 


### **TODO:**
---
- [x] Faire un devis des budgets à la fin tour (crédits consommé par quoi)
- [x] Afficher le score à la fin
- [x] Enregistrer les scores dans un fichier (faire classe, methodes)
- [x] Changer les étoiles 
- [x] Mettre les couleurs sur Fermée/ouvertes
- [x] Changer le saisie des actions pour ouvrir 1 caisse
- [x] Changer les noms des classes et les {}
- [x] Commenter le code 
- [x] Mettre tout en camelCase
- [x] Bouton pour changer l'etat de / pour ouvrir toutes les caisses
- [x] ATTENTION: Score::CreateFileIfExists() efface le fichier d'avant ! il faut le changer
- [x] Demander nom a l'utilisateur pour le stocker dans le tableau des scores
- [x] Erreur dans scorefile qd le nom du joueur est la touche <entrée> 
- [x] Devis ne se met pas à jour dans le do {} while
- [x] ResetDevis() dans la classe devis : pas de this 
- [x] Retirer les parties du code qui ne servent a rien 
- [x] CHANGER LE NOMBRE DE CLIENTS A 100 !
