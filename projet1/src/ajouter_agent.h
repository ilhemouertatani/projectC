#ifndef AJOUTER_AGENT_H
#define AJOUTER_AGENT_H
#include <gtk/gtk.h>
typedef struct {
    int jour;
    int mois;
    int annee;
} Date_agent;

typedef struct {
char id[15];
char nom[50];
char prenom[50];
Date_agent date_naissance; 
int sexe;
char region[50];
char telephone[20];
char email[50];
int services_agent[4];
} Agent;

typedef struct {
  int jour;
  int mois;
  int annee;
}Date;

typedef struct {
  char id_reservation[15];
  Date date_debut;
  int Hdebut;
  int Mdebut;
  int duree;
  int etat;
  int natureD; //0 si heure , 1 si jours
 char id_utilisateur[15];
 char id_parking[15];
}Reservation;
typedef struct ReservationNode ReservationNode;
struct ReservationNode {
    Reservation data;
   ReservationNode *next;
};
typedef ReservationNode* Liste;

// Déclarations des fonctions

int ajouter(char *filename, Agent agent);
void afficher_agents(GtkWidget *liste); 
Agent rechercher_agent(const char *file, const char *id_recherche);
int obtenir_index_region(char *region);
int supprimerAgent(char *file, char *id);
void filtrer_agents_par_region(GtkWidget *liste, GtkComboBoxText *combo_box);
void afficher_agents_par_region(GtkWidget *liste, const char *region);
void chargerListeFiltreeDansTreeView(GtkWidget *treeview, Liste list);
Liste filtreReservationParDate(const char *file, Date dateRecherche);
void libererListeReservations(Liste list);
#endif 
