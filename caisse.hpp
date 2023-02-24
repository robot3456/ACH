#include <stdint.h>
#include <string>

using namespace std;

class caisse
{
private:
    uint16_t clients_en_caisse;
    bool ouverte;
    
public:

    caisse();

    int sortir_client();

    string affiche_info();

    bool isOuverte();

    void add_client_en_caisse();
    void ouvrir_caisse();
    void fermer_caisse();

    int get_clients_en_caisse();
};