#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// Definim un alias per a l'unordered_map que emmagatzemarà les traduccions
using TraduccionsMap = unordered_map<string, string>;

// Funció per llegir el fitxer de traduccions i emmagatzemar-les en un unordered_map
TraduccionsMap llegirFitxerTraduccions(const string& Traduccio) {
    TraduccionsMap traduccions;
    ifstream fitxer(Traduccio);
    if (!fitxer) {
        cerr << "Error en obrir el fitxer de traduccions: " << Traduccio << endl;
        return traduccions; // Retornem un map buit en cas d'error
    }

    string linia;
    while (getline(fitxer, linia)) {
        size_t pos = linia.find(' ');
        if (pos != string::npos) {
            string clau = linia.substr(0, pos);
            string valor = linia.substr(pos + 1);
            traduccions[clau] = valor;
        }
        else {
            cerr << "Error: format de linia invalid en el fitxer de traduccions." << endl;
        }
    }

    fitxer.close();
    return traduccions;
}

// Funció per mostrar un text utilitzant les traduccions proporcionades
void mostrarText(const string& text, const TraduccionsMap& traduccions) {
    auto it = traduccions.find(text);
    if (it != traduccions.end()) {
        cout << it->second << endl;
    }
    else {
        cout << "Traduccio no disponible per aquest idioma." << endl;
    }
}

// Funció per validar si un idioma és vàlid
bool idiomaValid(const string& idioma) {
    // Llista d'idiomes vàlids
    const vector<string> idiomes_valids = { "CA", "EU", "GL", "OC", "ES", "EN", "FR", "DE", "IT", "PT", "NL", "SV", "PL", "DA" };
    // Comprovació si l'idioma és a la llista d'idiomes vàlids
    return find(idiomes_valids.begin(), idiomes_valids.end(), idioma) != idiomes_valids.end();
}

/// <summary>
/// Sol·licita una entrada de text a l'usuari i retorna el text introduït.
/// </summary>
/// <param name="prompt">La pregunta que s'ha de fer a l'usuari.</param>
/// <returns>La resposta de l'usuari en forma de cadena de caràcters.</returns>
string demanarText(string prompt)
{
    string resposta;
    cout << prompt;
    getline(cin, resposta);
    return resposta;
}

/// <summary>
/// Sol·licita una entrada numèrica a l'usuari i retorna el nombre introduït.
/// </summary>
/// <param name="prompt">La pregunta que s'ha de fer a l'usuari.</param>
/// <returns>La resposta de l'usuari com a nombre enter.</returns>
int demanarNumero(string prompt)
{
    int resposta;
    cout << prompt;
    cin >> resposta;
    return resposta;
}

/// <summary>
/// Explica la nova història utilitzant les dades proporcionades.
/// </summary>
/// <param name="nom">El nom utilitzat a la història.</param>
/// <param name="nomPlural">El nom en plural utilitzat a la història.</param>
/// <param name="numero">El nombre utilitzat a la història.</param>
/// <param name="partCos">La part del cos utilitzada a la història.</param>
/// <param name="verb">El verb utilitzat a la història.</param>
void explicarHistoria(string nom, string nomPlural, int numero, string partCos, string verb)
{
    cout << "\nPreparat per una historia mega divertida!\n";
    cout << "En una dimensio on regnava la rebelia, va sorgir " << nom << ", posseidor/a de " << numero << " " << nomPlural << " letals.\n";
    cout << nom << ", decidit/a a desafiar les lleis de l avorriment, va optar per " << verb << " amb el seu " << partCos << " de manera explosiva.\n";
    cout << "Les ones d adrenalina van ressonar com un himne de la intensitat.\n";
    cout << "Fi de la historia extremadament divertida.\n";
}

int main() {
    // Llegir fitxer de traduccions del narrador
    TraduccionsMap traduccionsNarrador = llegirFitxerTraduccions("Traduccio2.txt");
    // Demanar a l'usuari que seleccioni un idioma
    string idioma;
    cout << "Selecciona un idioma (CA, EU, GL, OC, ES, EN, FR, DE, IT, PT, NL, SV, PL, DA): ";
    cin >> idioma;

    // Validar l'idioma ingressat
    while (!idiomaValid(idioma)) {
        cout << "Idioma no valid. Torna a intentar: ";
        cin >> idioma;
    }

    // Mostrar presentació del narrador en l'idioma seleccionat
    mostrarText(idioma, traduccionsNarrador);

    cout << "Benvingut a Mad Libs. \n\n";
    cout << "Respon les seguents preguntes per ajudar a crear una nova historia.\n";

    // Obtindre les entrades de l'usuari
    string nom;
    string nomPlural;
    cout << "Per favor, introdueix un nom: ";
    cin >> nom;
    cin.ignore(); // Limpiar el buffer del salto de línea

    cout << "Per favor, introdueix un nom en plural: ";
    getline(cin, nomPlural);

    string partCos = demanarText("Per favor, introdueix una part del cos: ");
    string verb = demanarText("Per favor, introdueix un verb: ");
    int numero = demanarNumero("Per favor, introdueix un numero: ");

    // Mostrar la història de Mad Libs
    explicarHistoria(nom, nomPlural, numero, partCos, verb);

    return 0;
}
