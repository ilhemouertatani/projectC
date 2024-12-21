
#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>  // Pour utiliser strcpy

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "compte.h"

char *ID_ilhem;
int sexe;
int check[2] = {0, 0};
int i;


void on_femme_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        sexe = 0; // Femme
    }
}

void on_homme_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        sexe = 1; // Homme
    }
}


void on_annuler_clicked(GtkButton *button, gpointer user_data) {

GtkWidget *creer_un_compte;
    GtkWidget *Liste_des_citoyens;
   
    GtkWidget *treeview;
   
    creer_un_compte= lookup_widget(button, "creer_un_compte");
    gtk_widget_destroy(creer_un_compte);
    Liste_des_citoyens= lookup_widget(button, "Liste_des_citoyens");
    Liste_des_citoyens = create_Liste_des_citoyens ();
    gtk_widget_show (Liste_des_citoyens);

    treeview= lookup_widget(Liste_des_citoyens, "treeview1");

    // Ajouter le signal row_activated pour supprimer une réservation
  g_signal_connect(treeview, "row_activated", G_CALLBACK(on_treeview1_row_activated), NULL);
    afficherListeComptes(treeview, "compte.txt");






    // Code pour annuler (à définir selon vos besoins)
    // Par exemple, effacer les champs ou fermer la fenêtre
}

void on_checkbutton1_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        check[0] = 1;
    }
}

void on_checkbutton2_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        check[1] = 1;
    }
}



void
on_btnconnecter_clicked                (GtkButton       *button,
                                        gpointer         user_data)
 {
    // Déclaration des widgets utilisés
    GtkWidget *login;
    GtkWidget *password;

    // Déclaration des variables d'entrée
    char entrylogin[30];
    char entrypassword[30];
    Compte c;

    // Associer les widgets à des variables
    login = lookup_widget(button, "entryLogin");
    password = lookup_widget(button, "password");

    // Récupérer les données
    strcpy(entrylogin, gtk_entry_get_text(GTK_ENTRY(login)));
    strcpy(entrypassword, gtk_entry_get_text(GTK_ENTRY(password)));

    // Rechercher le compte correspondant au login
    c = rechercherCompte("compte.txt", entrylogin);

    // Vérifier si le compte a été trouvé et si le mot de passe est correct
    if (strcmp(c.id_compte, "") == 0) {
        // Compte non trouvé : afficher une boîte de dialogue d'erreur
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Compte non trouvé");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    } else if (strcmp(c.mdp, entrypassword) != 0) {
        // Mot de passe incorrect : afficher une boîte de dialogue d'erreur
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Mot de passe incorrect");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    } else {
        // Connexion réussie : afficher une boîte de dialogue de succès
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_INFO,
                                                   GTK_BUTTONS_OK,
                                                   "Compte connecté avec succès !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}



void
on_btnValider_clicked                  (GtkButton       *button,
                                        gpointer         user_data)


{
    // Déclaration des widgets utilisés
    GtkWidget *login;
    GtkWidget *nom;
    GtkWidget *prenom;
    GtkWidget *num_tel;
    GtkWidget *adresse;
    GtkWidget *password;
    GtkWidget *jour;
    GtkWidget *mois;
    GtkWidget *annee;
    GtkWidget *tyype;

    // Déclaration des variables d'entrée
    Compte c;
    int out;
    int i;

    // Associer les widgets à des variables
    login = lookup_widget(button, "login");
    nom = lookup_widget(button, "nom");
    prenom = lookup_widget(button, "prenom");
    num_tel = lookup_widget(button, "num_tel");
    adresse = lookup_widget(button, "adresse");
    password = lookup_widget(button, "password");
    jour = lookup_widget(button, "jourC");
    mois = lookup_widget(button, "moisC");
    annee = lookup_widget(button, "anneeC");
    tyype = lookup_widget(button, "tyype");

    // Vérifier si tous les champs sont remplis, à l'exception du type de compte
    if (strlen(gtk_entry_get_text(GTK_ENTRY(login))) == 0 ||
        strlen(gtk_entry_get_text(GTK_ENTRY(nom))) == 0 ||
        strlen(gtk_entry_get_text(GTK_ENTRY(prenom))) == 0 ||
        strlen(gtk_entry_get_text(GTK_ENTRY(num_tel))) == 0 ||
        strlen(gtk_entry_get_text(GTK_ENTRY(adresse))) == 0 ||
        strlen(gtk_entry_get_text(GTK_ENTRY(password))) == 0 ||
        gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour)) == 0 ||
        gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois)) == 0 ||
        gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee)) == 0)
    {
        // Créer une boîte de dialogue d'erreur pour les champs manquants
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Il faut remplir tous les champs");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // Déclaration des données d'entrée après la validation des champs
    strcpy(c.id_compte, gtk_entry_get_text(GTK_ENTRY(login)));
    strcpy(c.nom, gtk_entry_get_text(GTK_ENTRY(nom)));
    strcpy(c.prenom, gtk_entry_get_text(GTK_ENTRY(prenom)));
    strcpy(c.adresse, gtk_entry_get_text(GTK_ENTRY(adresse)));
    strcpy(c.telephone, gtk_entry_get_text(GTK_ENTRY(num_tel)));
    strcpy(c.mdp, gtk_entry_get_text(GTK_ENTRY(password)));

    // Récupérer l'état des CheckButtons pour les notifications
    for (i = 0; i < 2; i++) {
        c.notif[i] = check[i];  // Remplir le tableau c.notif avec l'état des cases à cocher
    }

    // Récupérer le type de compte sélectionné dans le ComboBox
    const char *type_compte = gtk_combo_box_get_active_text(GTK_COMBO_BOX(tyype));

    // Vérification du type de compte sélectionné
    if (type_compte == NULL || (strcmp(type_compte, "administrateur") != 0 && strcmp(type_compte, "utilisateur") != 0)) {
        // Créer une boîte de dialogue d'erreur pour le type de compte invalide
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Il faut choisir un type valide");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // Assignation de la nature du compte
    if (strcmp(type_compte, "administrateur") == 0) {
        c.natureC = 1;
    } else if (strcmp(type_compte, "utilisateur") == 0) {
        c.natureC = 0;
    }

    // Traitement du sexe : valeur à définir (ex: 1 pour homme, 0 pour femme)
    if (sexe) {
        c.sexe = 1;  // Par exemple, 1 pour homme
    } else {
        c.sexe = 0;  // 0 pour femme
    }

    // Récupérer la date de naissance
    c.date.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour));
    c.date.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois));
    c.date.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee));

    // Ajouter le compte en appelant la fonction correspondante
    out = ajouterCompte("compte.txt", c);

    // Afficher un message d'erreur ou de succès avec une boîte de dialogue
    if (out == 0) {
        // Créer une boîte de dialogue d'erreur pour l'ajout du compte
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Problème d'ajout du compte");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    } else {
        // Créer une boîte de dialogue d'information pour le succès de l'ajout du compte
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_INFO,
                                                   GTK_BUTTONS_OK,
                                                   "Compte ajouté avec succès !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}








void
on_f_toggled                           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)


 {
    if (gtk_toggle_button_get_active(togglebutton)) {
        sexe = 0; // Femme
    }
}

void
on_h_toggled                           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)

 {
    if (gtk_toggle_button_get_active(togglebutton)) {
        sexe = 1; // Homme
    }
}




void
on_checkbutton3_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton)) {
        check[0] = 1;
    }
}


void
on_checkbutton4_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton)) {
        check[1] = 1;
    }
}


void
on_recher_clicked                      (GtkButton       *button,
                                        gpointer         user_data)


 {
    // Déclaration des widgets
    GtkWidget *login, *nom, *prenom, *num_tel, *adresse, *password, *jour, *mois, *annee;
    GtkWidget *tyype;
    GtkWidget *checkbutton1, *checkbutton2;
    Compte c;

    // Récupération des widgets de l'interface
    login = lookup_widget(button, "idmodif");
    nom = lookup_widget(button, "nommodif");
    prenom = lookup_widget(button, "prenommodif");
    num_tel = lookup_widget(button, "numtelmodif");
    adresse = lookup_widget(button, "adressemodif");
    password = lookup_widget(button, "mdpmodif");
    jour = lookup_widget(button, "spinjour");
    mois = lookup_widget(button, "spinmois");
    annee = lookup_widget(button, "spinannee");
    tyype = lookup_widget(button, "typemodif");
    checkbutton1 = lookup_widget(button, "checkbutton3");
    checkbutton2 = lookup_widget(button, "checkbutton4");

    // Récupération de l'ID du compte
    const char *ID_ilhem = gtk_entry_get_text(GTK_ENTRY(login));

    // Vérification si l'entrée ID est vide
    if (ID_ilhem == NULL || strcmp(ID_ilhem, "") == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Veuillez entrer un identifiant.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // Recherche du compte à partir de l'ID dans le fichier
    c = rechercherCompte("compte.txt", ID_ilhem);  // Fonction à implémenter

    // Vérifier si le compte existe
    if (strcmp(c.id_compte, "") != 0) {
        // Mise à jour des champs avec les données du compte trouvé
        gtk_entry_set_text(GTK_ENTRY(nom), c.nom);
        gtk_entry_set_text(GTK_ENTRY(prenom), c.prenom);
        gtk_entry_set_text(GTK_ENTRY(num_tel), c.telephone);
        gtk_entry_set_text(GTK_ENTRY(adresse), c.adresse);
        gtk_entry_set_text(GTK_ENTRY(password), c.mdp);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(jour), c.date.jour);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(mois), c.date.mois);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(annee), c.date.annee);
       
        // Cocher le bon bouton radio pour le type de compte
        if (c.natureC == 1) {
            gtk_combo_box_set_active(GTK_COMBO_BOX(tyype), 0);  // Administrateur
        } else {
            gtk_combo_box_set_active(GTK_COMBO_BOX(tyype), 1);  // Utilisateur
        }

        // Mise à jour des CheckButtons pour les notifications
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton1), c.notif[0] == 1);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton2), c.notif[1] == 1);

        // Mise à jour du sexe : radio ou combo box
        if (c.sexe == 1) {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(lookup_widget(button, "h")), TRUE);
        } else {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(lookup_widget(button, "f")), TRUE);
        }

    } else {
        // Afficher un message d'erreur si le compte n'existe pas
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "L'identifiant recherché n'existe pas.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}






void
on_afficherC_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
GtkTreeView *treeview;
treeview=GTK_TREE_VIEW(lookup_widget(button, "treeview1"));
afficherListeComptes(treeview,"compte.txt");

}


void
on_treeview1_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_supprimer_citoyen_clicked           (GtkButton       *button,
                                        gpointer         user_data)
 {
    GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(GTK_WIDGET(button), "treeview1"));
    GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);
    GtkTreeModel *model;
    GtkTreeIter iter;

    // Vérification qu'une ligne est sélectionnée
    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        char *id_citoyen;

        // Obtenir l'ID du citoyen sélectionné
        gtk_tree_model_get(model, &iter, 0, &id_citoyen, -1);

        // Demander confirmation avant suppression
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(treeview))),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_QUESTION,
                                                   GTK_BUTTONS_YES_NO,
                                                   "Voulez-vous vraiment supprimer le citoyen %s ?", id_citoyen);
        gint response = gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        // Si l'utilisateur confirme la suppression
        if (response == GTK_RESPONSE_YES) {
            // Appeler la fonction de suppression de citoyen (en utilisant la fonction supprimerCompte)
            supprimerCompte("compte.txt", id_citoyen);

            // Supprimer la ligne du TreeView
            gtk_list_store_remove(GTK_LIST_STORE(model), &iter);

            // Afficher un message de succès
            GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(treeview))),
                                                               GTK_DIALOG_MODAL,
                                                               GTK_MESSAGE_INFO,
                                                               GTK_BUTTONS_OK,
                                                               "Le citoyen %s a été supprimé avec succès.", id_citoyen);
            gtk_dialog_run(GTK_DIALOG(success_dialog));
            gtk_widget_destroy(success_dialog);
        }

        g_free(id_citoyen);
    } else {
        // Aucune ligne sélectionnée
        GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(treeview))),
                                                         GTK_DIALOG_MODAL,
                                                         GTK_MESSAGE_WARNING,
                                                         GTK_BUTTONS_OK,
                                                         "Veuillez sélectionner un citoyen à supprimer.");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
    }
}





void
on_valider_modification_clicked        (GtkButton       *button,
                                        gpointer         user_data)

{
    // Déclaration des widgets utilisés
    GtkWidget *login;
    GtkWidget *nom;
    GtkWidget *prenom;
    GtkWidget *num_tel;
    GtkWidget *adresse;
    GtkWidget *password;
    GtkWidget *jour;
    GtkWidget *mois;
    GtkWidget *annee;
    GtkWidget *tyype;

    // Déclaration des variables d'entrée
    Compte c;
    int out;
    int i;

    // Associer les widgets à des variables
    login = lookup_widget(button, "idmodif");
    nom = lookup_widget(button, "nommodif");
    prenom = lookup_widget(button, "prenommodif");
    num_tel = lookup_widget(button, "numtelmodif");
    adresse = lookup_widget(button, "adressemodif");
    password = lookup_widget(button, "mdpmodif");
    jour = lookup_widget(button, "spinjour");
    mois = lookup_widget(button, "spinmois");
    annee = lookup_widget(button, "spinannee");
    tyype = lookup_widget(button, "typemodif");

    // Récupérer les données de l'interface
    strcpy(c.id_compte, gtk_entry_get_text(GTK_ENTRY(login)));
    strcpy(c.nom, gtk_entry_get_text(GTK_ENTRY(nom)));
    strcpy(c.prenom, gtk_entry_get_text(GTK_ENTRY(prenom)));
    strcpy(c.adresse, gtk_entry_get_text(GTK_ENTRY(adresse)));
    strcpy(c.telephone, gtk_entry_get_text(GTK_ENTRY(num_tel)));
    strcpy(c.mdp, gtk_entry_get_text(GTK_ENTRY(password)));

    // Récupérer l'état des CheckButtons pour les notifications
    for (i = 0; i < 2; i++) {
        c.notif[i] = check[i];  // Remplir le tableau c.notif avec l'état des cases à cocher
    }

    // Récupérer le type de compte sélectionné dans le ComboBox
    const char *type_compte = gtk_combo_box_get_active_text(GTK_COMBO_BOX(tyype));

    // Vérification du type de compte sélectionné
    if (type_compte == NULL || (strcmp(type_compte, "administrateur") != 0 && strcmp(type_compte, "utilisateur") != 0)) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Il faut choisir un type valide");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // Assignation de la nature du compte
    if (strcmp(type_compte, "administrateur") == 0) {
        c.natureC = 1;
    } else if (strcmp(type_compte, "utilisateur") == 0) {
        c.natureC = 0;
    }

    // Traitement du sexe : valeur à définir (ex: 1 pour homme, 0 pour femme)
    if (sexe) {
        c.sexe = 1;  // Par exemple, 1 pour homme
    } else {
        c.sexe = 0;  // 0 pour femme
    }

    // Récupérer la date de naissance
    c.date.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour));
    c.date.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois));
    c.date.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee));

    // Modifier le compte en appelant la fonction correspondante
    out = modifierCompte("compte.txt", c.id_compte, c);  // Passez l'ID du compte et la structure complète

    // Afficher un message d'erreur ou de succès avec une boîte de dialogue
    if (out == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Problème de modification du compte");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_INFO,
                                                   GTK_BUTTONS_OK,
                                                   "Compte modifié avec succès !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}






void
on_annuler_modification_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{

GtkWidget *creer_un_compte;
    GtkWidget *Liste_des_citoyens;
   
    GtkWidget *treeview;
   
    creer_un_compte= lookup_widget(button, "creer_un_compte");
    gtk_widget_destroy(creer_un_compte);
    Liste_des_citoyens= lookup_widget(button, "Liste_des_citoyens");
    Liste_des_citoyens = create_Liste_des_citoyens ();
    gtk_widget_show (Liste_des_citoyens);

    treeview= lookup_widget(Liste_des_citoyens, "treeview1");

    // Ajouter le signal row_activated pour supprimer un compte
  g_signal_connect(treeview, "row_activated", G_CALLBACK(on_treeview1_row_activated), NULL);
    afficherListeComptes(treeview, "compte.txt");



}


void
on_ajouter_un_compte__clicked          (GtkButton       *button,
                                        gpointer         user_data)
 {
    GtkWidget *creer_un_compte;
    GtkWidget *Liste_des_citoyens;
    GtkWidget *treeview;

    // Trouver la fenêtre "Liste_des_citoyens" via lookup_widget
    Liste_des_citoyens = lookup_widget(button, "Liste_des_citoyens");

    // Fermer la fenêtre "Liste_des_citoyens"
    gtk_widget_destroy(Liste_des_citoyens);

    // Créer et afficher la fenêtre "creer_un_compte"
    creer_un_compte = create_creer_un_compte(); // Assurez-vous que cette fonction existe et crée la fenêtre
    gtk_widget_show(creer_un_compte);

    // Optionnel : Affichage de la liste des comptes dans le treeview
    treeview = lookup_widget(creer_un_compte, "treeview1"); // Utilisez "creer_un_compte" comme fenêtre active
    if (treeview != NULL) {
        g_signal_connect(treeview, "row_activated", G_CALLBACK(on_treeview1_row_activated), NULL);
        afficherListeComptes(treeview, "compte.txt"); // Affichage des comptes dans la treeview
    }
}



void
on_modifier_un_compte_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *modification;  // Fenêtre de modification
    GtkWidget *Liste_des_citoyens;  // Fenêtre de liste des citoyens
    GtkWidget *treeview;  // Treeview pour afficher la liste des comptes

    // Trouver la fenêtre "Liste_des_citoyens" via lookup_widget
    Liste_des_citoyens = lookup_widget(button, "Liste_des_citoyens");

    // Fermer la fenêtre "Liste_des_citoyens"
    gtk_widget_destroy(Liste_des_citoyens);

    // Créer et afficher la fenêtre "modification"
    modification = create_modification();  // Assurez-vous que cette fonction existe et crée la fenêtre
    gtk_widget_show(modification);

    // Optionnel : Affichage de la liste des comptes dans le treeview
    treeview = lookup_widget(modification, "treeview1");  // Utilisez "modification" comme fenêtre active
    if (treeview != NULL) {
        g_signal_connect(treeview, "row_activated", G_CALLBACK(on_treeview1_row_activated), NULL);
        afficherListeComptes(treeview, "compte.txt");  // Affichage des comptes dans le treeview
    }
}






/*void
on_acceuil_citoyen_clicked             (GtkButton       *button,
                                        gpointer         user_data)
  {  GtkWidget *connexion;
    GtkWidget *Liste_des_citoyens;
   
    GtkWidget *treeview;
   
    Liste_des_citoyens= lookup_widget(button, "Liste_des_citoyens");
    gtk_widget_destroy(Liste_des_citoyens);
    connexion= lookup_widget(button, "connexion");
    connexion = create_connexion ();
    gtk_widget_show (connexion);

    treeview= lookup_widget(Liste_des_citoyens, "treeview1");}


*/





void
on_acceuil_cit_clicked                 (GtkButton       *button,
                                        gpointer         user_data)


{  GtkWidget *connexion;
    GtkWidget *Liste_des_citoyens;
   
    GtkWidget *treeview;
   
    Liste_des_citoyens= lookup_widget(button, "Liste_des_citoyens");
    gtk_widget_destroy(Liste_des_citoyens);
    connexion= lookup_widget(button, "connexion");
    connexion = create_connexion ();
    gtk_widget_show (connexion);

    treeview= lookup_widget(Liste_des_citoyens, "treeview1");}




