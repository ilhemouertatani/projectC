#ifndef AVISRECLAM_H_INCLUDED
#define AVISRECLAM_H_INCLUDED
#include <gtk/gtk.h>
// D�finition de la structure Feedback
typedef struct {   
    char id_ar[15];    
    char id_citoyen[15];
    char id_parking[15];
    int type_feedback;  // Utilisation 1 avis et 2 reclamation
    int day;
    int month;
    int year;
    int note;
    char commentaire[250];
}Feedback;
// Structure représentant un parking
typedef struct {
    int id_parking;           // Identifiant unique du parking
    char nom_parking[100];    // Nom du parking
    char region_parking[100]; // Région du parking
    int capacite;             // Capacité du parking
    int nbPlaces;             // Nombre de places disponibles
    int nombre_bloc;          // Nombre de blocs dans le parking
    char type_terrain[20];    // Type de parking (aérien, souterrain, sur surface)
    char date_ajout[20];      // Date d'ajout du parking    
} Parking;



// Structure pour associer un parking avec la note la plus élevée des avis
typedef struct {
    int id_parking;   // Identifiant du parking
    float note_max;   // Note la plus élevée
} ParkingAvecNote;


// Prototypes des fonctions
int ajouterFeedback(char *file, Feedback fb);
int modifierFeedback(char *file, char *id_citoyen, Feedback fb);
int supprimerFeedback(char *file, char *id_citoyen);
Feedback rechercherFeedback(char *file, char *id_citoyen);
void afficher_feedback(GtkWidget *liste, char *id_citoyen_connecte);


#endif // AVISRECLAM_H_INCLUDED
