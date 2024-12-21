#include<stdio.h>
#include "compte.h"
#include <gtk/gtk.h>
int ajouterCompte(char *file, Compte c) {
    FILE *f = fopen(file, "a"); // Ouvrir le fichier en mode ajout (append)

    if (f != NULL && strcmp(c.id_compte,"")!=0) {
        // Écrire les données du compte dans le fichier
        fprintf(f, "%s %s %s %s %s %s %d %d %d %d %d %d %d\n",
                c.id_compte,
                c.nom,
                c.prenom,
                c.telephone,
                c.adresse,
                c.mdp,
                c.sexe,
                c.date.jour,
                c.date.mois,
                c.date.annee,
                c.natureC,
                c.notif[0],
                c.notif[1]);

        fclose(f);
        return 1; // Ajout réussi
    } else {
        return 0; // Échec de l'ouverture du fichier
    }
}
int modifierCompte(char *file, char *id_compte,Compte modC) {
    FILE *f = fopen(file, "r");
    FILE *fnew = fopen("temp.txt", "w");
    Compte c;
    int val = 0;

    if (f != NULL && fnew != NULL) {
        while (fscanf(f, "%s %s %s %s %s %s %d %d %d %d %d %d %d\n",
                      c.id_compte,
                      c.nom, c.prenom, c.telephone,
                      c.adresse, c.mdp,
                      &c.sexe,
                      &c.date.jour, &c.date.mois, &c.date.annee ,&c.natureC,&c.notif[0],&c.notif[1]) != EOF) {

            // Vérification si l'ID correspond
            if (strcmp(id_compte, c.id_compte) == 0) {
                c=modC;
                val = 1; // Modification effectuée
            }

            // Écrire les données dans le fichier temporaire (modifiées ou inchangées)
            fprintf(fnew, "%s %s %s %s %s %s %d %d %d %d %d %d %d\n",
                    c.id_compte,
                    c.nom, c.prenom, c.telephone,
                    c.adresse, c.mdp,
                    c.sexe,
                    c.date.jour, c.date.mois, c.date.annee ,c.natureC,c.notif[0],c.notif[1]);
        }

        fclose(f);
        fclose(fnew);

        // Remplacer le fichier original par le fichier temporaire
        remove(file);
        rename("temp.txt", file);
    } else {
        if (f != NULL) fclose(f);
        if (fnew != NULL) fclose(fnew);
        return 0; // Échec de l'ouverture du fichier
    }

    return val; // 1 si modification effectuée, sinon 0
}

int supprimerCompte(char *file, char *id_compte) {
    int val = 0; // Indiquer si un compte a été trouvé
    Compte c;
    FILE *f = fopen(file, "r");
    FILE *fnew = fopen("temp.txt", "w"); // Fichier temporaire

    // Vérification que les fichiers ont été ouverts avec succès
    if (f != NULL && fnew != NULL) {
        // Lecture de chaque compte dans le fichier
        while (fscanf(f, "%s %s %s %s %s %s %d %d %d %d %d %d %d\n",
                      c.id_compte,
                      c.nom, c.prenom, c.telephone,
                      c.adresse, c.mdp,
                      &c.sexe,
                      &c.date.jour, &c.date.mois, &c.date.annee,
                      &c.natureC,&c.notif[0],&c.notif[1]) != EOF) {

            // Vérifier si l'ID du compte correspond à l'ID à supprimer
            if (strcmp(id_compte, c.id_compte) == 0) {
                val = 1; // Compte trouvé, on ne l'écrit pas dans le fichier temporaire
            } else {
                // Écrire le compte dans le fichier temporaire s'il ne correspond pas
                fprintf(fnew, "%s %s %s %s %s %s %d %d %d %d %d %d %d\n",
                        c.id_compte,
                        c.nom, c.prenom, c.telephone,
                        c.adresse, c.mdp,
                        c.sexe,
                        c.date.jour, c.date.mois, c.date.annee,
                        c.natureC,c.notif[0] ,c.notif[1]);
            }
        }
        fclose(f);
        fclose(fnew);

        // Remplacer le fichier original par le fichier temporaire
        remove(file);
        rename("temp.txt", file);
    } else {
        if (f != NULL) fclose(f);
        if (fnew != NULL) fclose(fnew);
        return 0; // Échec de l'ouverture du fichier
    }

    return val; // 1 si suppression effectuée, sinon 0
}




Compte rechercherCompte(char *file, char *id_compte) {
    FILE *f = fopen(file, "r");
    Compte c;  // Déclaration de la variable pour stocker les données du compte

    // Initialiser l'ID du compte à une chaîne vide au cas où aucune correspondance ne serait trouvée


    if (f != NULL) {
        // Lire chaque compte dans le fichier
        while (fscanf(f, "%s %s %s %s %s %s %d %d %d %d %d %d %d\n",
                      c.id_compte, c.nom, c.prenom, c.telephone,
                      c.adresse, c.mdp, &c.sexe,
                      &c.date.jour, &c.date.mois, &c.date.annee,&c.natureC,&c.notif[0],&c.notif[1]) != EOF) {

            // Vérifier si l'ID du compte correspond à l'ID recherché
            if (strcmp(id_compte, c.id_compte) == 0) {
                fclose(f); // Fermer le fichier avant de retourner
                return c; // Retourner le compte trouvé
            }
        }
        fclose(f); // Fermer le fichier si aucune correspondance n'est trouvée
         }
      strcpy(c.id_compte, "");
    // Si aucune correspondance n'est trouvée, retourner un compte avec ID vide
    return c;
}

/*void afficherListeComptes(char *file) {
    FILE *f = fopen(file, "r");
    Compte c;

    if (f != NULL) {
        printf("Liste des comptes :\n");

        // Lire chaque ligne du fichier et afficher les informations du compte
        while (fscanf(f, "%s %s %s %s %s %s %d %d %d %d %d\n",
                      c.id_compte, c.nom, c.prenom, c.telephone,
                      c.adresse, c.mdp, &c.sexe,
                      &c.date.jour, &c.date.mois, &c.date.annee ,c.natureC) != EOF) {

            // Afficher les informations de chaque compte
            printf("Compte ID: %s, Nom: %s, Prénom: %s, Téléphone: %s, Adresse: %s, Sexe: %d, Date de naissance: %02d/%02d/%d\n",
                c.id_compte, c.nom, c.prenom, c.telephone, c.adresse, c.sexe, c.date.jour, c.date.mois, c.date.annee);
        }

        fclose(f);
    } else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
}
*/


// Fonction pour afficher les comptes dans une GtkTreeView



void afficherListeComptes(GtkTreeView *liste, char *file) {
    Compte c;
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkListStore *store;
    GtkTreeIter iter;

    // Ouverture du fichier
    FILE *f = fopen(file, "r");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    // Créer un modèle de liste (GtkListStore) pour les 9 colonnes
    store = gtk_list_store_new(9,
        G_TYPE_STRING, // ID du compte
        G_TYPE_STRING, // Nom
        G_TYPE_STRING, // Prénom
        G_TYPE_STRING, // Téléphone
        G_TYPE_STRING, // Adresse
        G_TYPE_STRING, // Mot de passe
        G_TYPE_STRING, // Sexe (Homme/Femme)
        G_TYPE_STRING, // Date de naissance (format : jour/mois/année)
        G_TYPE_STRING  // Type de compte (Utilisateur ou Administrateur)
    );

    // Associer le modèle à la GtkTreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));

    // Ajouter les colonnes à la GtkTreeView
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("ID Compte", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Prénom", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Téléphone", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Adresse", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Mot de passe", renderer, "text", 5, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Sexe", renderer, "text", 6, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Date de naissance", renderer, "text", 7, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Type de compte", renderer, "text", 8, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    // Lire les données du fichier et les ajouter dans le store
    while (fscanf(f, "%s %s %s %s %s %s %d %d %d %d %d %d %d\n",
                  c.id_compte, c.nom, c.prenom, c.telephone,
                  c.adresse, c.mdp, &c.sexe,
                  &c.date.jour, &c.date.mois, &c.date.annee, &c.natureC ,&c.notif[0],&c.notif[1]) != EOF) {

        // Format de la date de naissance (jour/mois/année)
        char date_naissance[11]; // Format : dd/mm/yyyy
        snprintf(date_naissance, sizeof(date_naissance), "%02d/%02d/%04d", c.date.jour, c.date.mois, c.date.annee,c.notif[0],c.notif[0]);

        // Déterminer le type de compte : utilisateur ou administrateur
        const char *type_compte = (c.natureC == 1) ? "Administrateur" : "Utilisateur";

        // Ajouter une nouvelle ligne au store et remplir les colonnes
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, c.id_compte,         // ID du compte
                           1, c.nom,               // Nom
                           2, c.prenom,            // Prénom
                           3, c.telephone,         // Téléphone
                           4, c.adresse,           // Adresse
                           5, c.mdp,               // Mot de passe
                           6, c.sexe == 1 ? "Homme" : "Femme", // Sexe
                           7, date_naissance,      // Date de naissance
                           8, type_compte,         // Type de compte
                           -1); // Indicateur de fin de ligne
    }

    fclose(f);

    // Dé-référencer le modèle de liste
    g_object_unref(store);
}

