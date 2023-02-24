#include <stdint.h>

class caisse
{
private:
    uint16_t clients_en_caisse;
    bool ouverte;
    
public:

    caisse();

    int sortir_client();

    void affiche_clients_en_caisse();
    void affiche_ouverte();
    void affiche_info();

    bool isOuverte();
    void add_client_en_caisse();
    void ouvrir_caisse();
    void fermer_caisse();

};