#include <stdint.h>
#include <string>

using namespace std;

class Caisse{
private:
    uint16_t clients_en_caisse;
    bool ouverte;
    bool etat_a_changer;
    
public:

    Caisse();

    string affiche_info();

    bool est_Ouverte();

    void sortir_client();
    void add_client_en_caisse();
    int sortir_tout_les_clients();

    void ouvrir_caisse();
    void fermer_caisse();
    void changer_caisse();

    // Getter
    int get_clients_en_caisse();
    void reset_clients_en_caisse();

    void changer_etat();
    void reset_changement();
    bool a_changer();
    string get_changement();

};