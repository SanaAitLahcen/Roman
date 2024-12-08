#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
using namespace std;

// Fonction pour nettoyer les mots (enlever la ponctuation, espaces, etc.)
static string nettoyerMot(const string& mot) 
{
    string nettoye;
    for (char c : mot) 
    {
        if (isalpha(c)) 
        { 
            nettoye.push_back(tolower(c)); // Convertir en minuscule
        }
    }
    return nettoye;
}

int main() 
{
    map<string, map<int, vector<int>>> dictionnaire;

    ifstream file{ "Fich.txt" };
    string ligne, mot;
    int numeroLigne = 0;

    if (file.is_open()) 
    {
        while (getline(file, ligne)) // Lire le fichier ligne par ligne
        { 
            numeroLigne++;
            stringstream ss(ligne); // Pour extraire les mots de la ligne
            int position = 0; // Position du mot dans la ligne
            while (ss >> mot) 
            {
                position++;
                mot = nettoyerMot(mot); // Nettoyer le mot

                if (!mot.empty()) // Si le mot n'est pas vide après nettoyage
                { 
                    // Ajouter la position dans le dictionnaire
                    dictionnaire[mot][numeroLigne].push_back(position);
                }
            }
        }
    }
    else 
    {
        cerr << "Erreur: Impossible d'ouvrir le fichier." << endl;
        return 1;
    }

    cout << "Contenu du dictionnaire :\n";
    for (const auto& pair : dictionnaire) 
    {
        cout << pair.first << " :\n";
        for (const auto& ligne : pair.second) 
        {
            cout << "  Ligne " << ligne.first << " : positions ";
            for (int pos : ligne.second) 
            {
                cout << pos << " ";
            }
            cout << endl;
        }
    }

    cout << "\nEntrez un mot à chercher : ";
    string motRecherche;
    cin >> motRecherche;

    motRecherche = nettoyerMot(motRecherche); // Nettoyer le mot recherché

    auto it = dictionnaire.find(motRecherche);
    if (it != dictionnaire.end()) 
    {
        cout << "Le mot \"" << motRecherche << "\" apparait dans :\n";
        for (const auto& ligne : it->second) 
        {
            cout << "  Ligne " << ligne.first << " : positions ";
            for (int pos : ligne.second) 
            {
                cout << pos << " ";
            }
            cout << endl;
        }
    }
    else 
    {
        cout << "Le mot \"" << motRecherche << "\" n'existe pas dans le fichier." << endl;
    }

    return 0;
}
