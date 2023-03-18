#include "Jeu.hpp"

#include <iostream>

using namespace std;

/**
 * @brief Constructeur par défaut de la classe Jeu
 *
 */
Jeu::Jeu(){

    //initialisation par défaut du jeu
    this->credits=STARTING_CREDITS;
    this->clientsEnCourses=STARTING_CLIENTS_EN_COURSE;
    this->clientsEnAttente=STARTING_CLIENTS_EN_ATTENTE;

    this->hypermarcheVide=false;
    this->tour=1;

    this->devis.resetDevis();

    this->errorMessage="";

    for(int i=0; i<NB_CAISSES; i++){
        this->caisses[i] = new Caisse();
        this->changementsCaisse[i] = '-';
    }
}

/**
 * @brief Destructeur de la classe Jeu
 * 
 */
Jeu::~Jeu(){

    for(int i=0; i<NB_CAISSES; i++){
        delete this->caisses[i];
    }

}

/**
 * @brief Accesseur de la variable HypermarcheVide
 * 
 * @return HypermarcherVide 
 */
bool Jeu::getHypermarcheVide(){
    return this->hypermarcheVide;
}

/**
 * @brief Renvoie l'état du hypermarché
 * 
 * @return true si l'hypermarché est vide
 * @return false si l'hypermarché n'est pas vide
 */
bool Jeu::hypermarcheEstVide(){

    if(this->clientsEnCourses>0)
        return false;

    if(this->clientsEnAttente>0)
        return false;

    
    for(int i=0; i<NB_CAISSES; i++){
        if (this->caisses[i]->getClientsEnCaisse()>0){
            return false;
        }
    }

    this->hypermarcheVide = true;
    return true;
}

/**
 * @brief Accesseur du numéro du tour actuel
 * 
 * @return int numéro du tour actuel
 */
int Jeu::getTour(){
    return this->tour;
}

/**
 * @brief Setter de la variable Tour
 * 
 * @param tourActuel Tour à changer
 */
void Jeu::setTour(int tourActuel){
    this->tour=tourActuel;
}

/**
 * @brief Accesseur de la variable credits
 * 
 * @return int crédits du Joueur
 */
int Jeu::getCredits(){
    return this->credits;
}

/**
 * @brief Réinitialise les valeurs à celles de départ
 * afin de pouvroi recommencer une nouvelle partie
 */
void Jeu::reset(){

    this->credits=STARTING_CREDITS;
    this->hypermarcheVide=false;
    this->clientsEnCourses=STARTING_CLIENTS_EN_COURSE;
    this->clientsEnAttente=0;

    // Pour chaque caisse, remettre le nombre de clients à 0
    // et fermer la caisse (passée à l'état "false")
    for(int i=0; i<NB_CAISSES; i++){
        this->caisses[i]->resetClientsEnCaisse();
        this->caisses[i]->fermerCaisse();
    }
}

/**
 * @brief Sort un clients de chaque caisse ouverte s'il y a au moins un client dans la caisse
 * 
 */
void Jeu::sortirClientsDesCaisses(){
    vector<int> caissesOuvertes = getCaissesOuvertes();

    /* On ne fait rien si aucune caisse est ouverte */
    if(caissesOuvertes.size()==0){
        return; 
    }

    /* Sort un client pour chaque caisse ouverte */
    for(int num_caisse : caissesOuvertes){
        if(this->caisses[num_caisse]->getClientsEnCaisse()==0){
            continue;
        }
        this->caisses[num_caisse]->sortirClient();
    }

}

/**
 * @brief Attribue un nombre aléatoire de clients en attente
 * 
 * @return int le nombre de clients qui sont mis en attente ou -1 s'il y a un nombre négatif de clients qui font les courses
 */
int Jeu::mettreClientsEnAttente()
{
    /* On renvoie 0 direct si aucun clients ne fait les courses */
    if (this->clientsEnCourses==0)
        return 0;

    /* On renvoie -1 s'il y a un nombre de clients en course négatif */
    if (this->clientsEnCourses<0)
        return -1;

    /* Initialisation de rand */
    std::srand(time(NULL));

    /* Variable qui va compter le nombre de clients en course en moins */
    int clientsEnMoins = 0;

    /* On itère sur tout les clients en course, on a une chance de 1/2 pour que le clients
    passe en attente */
    for(int i=0; i<this->clientsEnCourses; i++){
        if(std::rand()%2){
            clientsEnMoins++;
            this->clientsEnAttente++;
        }
    }

    this->clientsEnCourses-=clientsEnMoins;
    return clientsEnMoins;
}

/**
 * @brief Envoie les clients en attente dans les caisses ouvertes
 * 
 * @return int 0 si aucun clients n'a été envoyé en caisse, 1 si les clients en attente ont été envoyé en caisse, -1 s'il y a eu un problème
 */
int Jeu::metttreClientsEnCaisses()
{
    /* On renvoie 0 s'il y a aucun clients en attente */
    if (this->clientsEnAttente==0)
        return 0;

    /* On initialise une liste des caisses ouvertes, ainsi que le nombre de caisses ouvertes */
    vector<int> caisseOuvertes = this->getCaissesOuvertes();
    int nbCaissesOuvertes = caisseOuvertes.size();

    /* Renvoie 0 s'il n'y a aucune caisse ouverte */
    if (nbCaissesOuvertes==0)
        return 0;

    /* Variable pour choisir une caisse ouverte aléatoire */
    int caisseOuverteAleatoire;

    /* On itère sur tout les clients en attente */
    for(int i=0; i<this->clientsEnAttente; i++){

        /* On choisit une caisse ouverte aléatoire */
        caisseOuverteAleatoire = caisseOuvertes[rand()%nbCaissesOuvertes];

        /* Ajout du client à la caisse aléatoire choisie */
        this->caisses[caisseOuverteAleatoire]->ajouterClientEnCaisse();
    }

    /* Lorsque tous les clients en attente on été placés, 
    on remet le nombre de clients en attente à 0 et on renvoie 1 */
    this->clientsEnAttente=0;
    return 1;
}

/**
 * @brief Demande l'action que le joueur souhaite faire sur les caisses, le joueur peut choisir d'ouvrir/fermer une ou toutes les caisses ou de passer le tour
 * 
 * @return true Si le joueur a choisi de passer le tour.
 * @return false  Si le joueur a choisi d'ouvir/fermer une caisse ou toutes les caisses ou s'il y a eu une erreur de saisie.
 */
bool Jeu::actionsSurCaisses(){

    string choix;

    cout << endl;
    cout << "Action sur les caisses ..." << endl;
    cout << this->errorMessage << endl;
    cout << "Choisir une caisse à changer[1-10] OU changer l'état de toutes les caisses [A]. Appliquer les changements et jouer le tour[P] :";
    getline(cin, choix);
    
    // Suppression du caractère \n de la chaine pour obtenir uniquement le choix de l'utilisateur
    if (!choix.empty() && choix[choix.length()-1] == '\n'){
        choix.erase(choix.length()-1);
    }

    // Vérification que la saisie a été faite correctement
    if(cin.fail()){
        this->errorMessage= "\033[1;31mErreur dans la saisie du choix, veuillez réessayer.\033[0m";
        cin.clear();
        return false;
    }

    // Mise en majuscules de la chaine de caractère afin de pouvoir entrer "p" ou "P" (case insensitive)
    for(auto & c: choix) c = toupper(c);

    if(choix=="P"){
        this->errorMessage="";
        return true;
    }
    
    if(choix=="A"){
        for(int i=0; i<NB_CAISSES; i++){
            if(!this->caisses[i]->estOuverte())
                this->caisses[i]->changerEtat();
        }
        return false;
    }

    // Si la saisie de l'utilisateur est valide, alors on effectue les actions qu'il souhaite sur les caisses
    try{
        int choixNumCaisse = stoi(choix);
        if(choixNumCaisse<=NB_CAISSES && choixNumCaisse>=1){
            this->caisses[choixNumCaisse-1]->changerEtat();
            this->errorMessage="";
            return false;
        }

    // Sinon on gère l'exception en demandant une nouvelle saisie
    }catch(exception &err){
        this->errorMessage= "\033[1;31mErreur dans la saisie du choix, veuillez réessayer.\033[0m";
        return false;
    }

    // Demande à l'utilisateur d'entrer une saisie valide
    this->errorMessage="\033[1;31mVeuillez selectionner \"[1-10\" ou \'P\'\033[0m";
    return false;

}

/**
 * @brief Inverse l'état des caisses sélectionnées par le joueur
 * 
 */
void Jeu::changerCaisses(){
    for(int i=0; i<NB_CAISSES; i++){

        if (this->caisses[i]->aChanger()){
            this->caisses[i]->changerCaisse();

            if(!this->caisses[i]->estOuverte()){
                this->clientsEnAttente+=this->caisses[i]->sortirTousLesClients();
            }
            this->caisses[i]->resetChangement();
        }
    }
}

/**
 * @brief Supprime le montant du devis aux crédits du joueur
 * 
 */
void Jeu::facturation(){
    this->credits-=this->devis.getTotal();
}

/**
 * @brief Affiche les états des caisses.
 * Ex : [-]   Caisse 1:   [Fermée]
 * 
 */
void Jeu::afficheEtatsCaisses(){
    for(int i=0; i<NB_CAISSES; i++){
        cout << this->caisses[i]->getChangement() << " Caisse " << i+1 << ":\t"<< this->caisses[i]->afficheInfoCaisse() << endl;
    }   
}

/**
 * @brief Affiche le budget du joueur
 * 
 */
void Jeu::afficheBudget(){
    cout << "Budget: " << this->credits << " crédits." << endl;
}

/**
 * @brief Affiche le nombre de clients dans l'hypermarché, les clients en attente de caisse et les clients en caisse
 * 
 */
void Jeu::affichePositionClients(){

    vector<int> caissesOuvertes = getCaissesOuvertes();
    int clientsEnCaisses = 0;
    
    for(int numCaisse: caissesOuvertes){
        clientsEnCaisses += this->caisses[numCaisse]->getClientsEnCaisse();
    }
    cout << "Clients dans l'hypermarché: " << this->clientsEnCourses << ", en attente de caisse: " << this->clientsEnAttente << " et aux caisses: " << clientsEnCaisses << ".\n";
}

/**
 * @brief Calcule et affiche le devis du tour actuel
 * 
 */
void Jeu::afficheDevis(){

    this->devis.calculerDevis(this->caisses, NB_CAISSES, this->clientsEnAttente);
    this->devis.afficheDevis();
}

/**
 * @brief Renvoie un vecteur contenant les indices de toutes les caisses ouvertes
 * 
 * @return vector<int> Vecteur contenant les indices des caisses ouvertes, les indices ne peuvent être que entre 0 et NB_CAISSES-1
 */
vector<int> Jeu::getCaissesOuvertes(){
    vector<int> caissesOuvertes;

    for(int i=0;i<NB_CAISSES; i++){

        // Si la caisse est ouverte, ajouter son indice à la fin du vecteur <caissesOuvertes>
        if(caisses[i]->estOuverte()){
            caissesOuvertes.push_back(i);
        }
    }
    return caissesOuvertes;
}

