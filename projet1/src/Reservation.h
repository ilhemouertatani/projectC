#ifndef RESERVATION_H
#define RESERVATION_H
#include <gtk/gtk.h>
#include <string.h>123
#include <stdlib.h>
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
Liste filtreReservationCombine(char *file, int etat, Date dateDebut, char *idU);
void chargerListeFiltreeDansTreeView(GtkWidget *treeview, Liste l);
void libererListeReservations(Liste list);
 // représentant un parking

Parking chercherParking(char *file,int id);
void modifierParking(char *file,Parking p);


void configurerTreeView(GtkTreeView *treeview);
void remplirTreeViewAvecDonnees(GtkTreeView *treeview, Parking *parkings, int taille);
GtkListStore *creerModeleTreeView();
Parking *rechercherParkingsParRegion(char *file, char *region, int *taille);


void pre_remplir_formulaire(GtkButton  *button,const gchar *id_reservation);
void afficher_reservation(GtkWidget *liste);
gint compare_dates(GtkTreeModel *model, GtkTreeIter *a, GtkTreeIter *b, gpointer user_data);
gboolean show_sort_dialog(GtkWidget *parent);

int ajouterReservation(char *,Reservation);
int modifierReservation(char *,char *id,Reservation);
int supprimerReservation(char *,char *);
Reservation rechercherReservation(char *,char *);
int annulerReservation(char *,char *);
void afficherListeReservationParUtilisateur(char *file, char *id);
void imprimerReservation(Reservation r);

void filtreReservationParDateDebut(char *file, Date dateDebut,char *idU);
void filtreReservationParEtat(char *file, int etat,char *idU);

void trierReservationParDateDebut(char *file,char *idU);
int compterReservation(char *,char *);
int comparerDates(Date,Date);
void trierParkingParNbPlaces(Parking *resultat, int *taille);

//void afficherListeReservationParUtilisateur(char *file, char *id);

int estUnique(char *,char *);
int estValide(Reservation);
int estValideDate(Date);
#endif
