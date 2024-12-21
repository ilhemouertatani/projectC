#ifndef COMPTE_H_INCLUDED
#define COMPTE_H_INCLUDED
#include<string.h>
#include <gtk/gtk.h>
typedef struct {
int jour ;
int mois ;
int annee;
}Date;
typedef struct {
    char id_compte[20];
    char nom[30];
    char prenom[30];
    char telephone[15];
    char adresse[50];
    char mdp[20];
    int sexe; // 0 pour femme, 1 pour homme
    Date date;
    int natureC; // 0 pour utilisateur et 1 pour administrateur 
    int notif[2];
} Compte;
int ajouterCompte(char *,Compte);
int modifierCompte(char *,char *id,Compte);
int supprimerCompte(char *,char *id);
Compte rechercherCompte(char *,char *);
//void afficherListeComptes(char *);
void afficherListeComptes(GtkTreeView *liste, char *file);




#endif // COMPTE_H_INCLUDED


