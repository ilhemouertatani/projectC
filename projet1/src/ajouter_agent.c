#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include "ajouter_agent.h"


int ajouter(char *filename, Agent agent) {
    FILE *f = fopen(filename, "a"); // Ouvre le fichier en mode ajout (append)

    if (f != NULL) {
        // Écriture des informations de l'agent dans le fichier
        fprintf(f, "%s %s %s %d %d %d %d %s %s %s %d %d %d %d\n", 
                agent.id, 
                agent.nom, 
                agent.prenom, 
                agent.date_naissance.jour,
                agent.date_naissance.mois,
                agent.date_naissance.annee, 
                agent.sexe, 
                agent.region, 
                agent.telephone, 
                agent.email, 
                agent.services_agent[0], agent.services_agent[1], 
                agent.services_agent[2], agent.services_agent[3]);

        fclose(f); // Fermeture du fichier
        return 1;  // Succès
    } else {
        return 0;  // Échec, fichier non ouvert
    }
}

int obtenir_index_region(char *region) {
   int i;
    const char *regions[] = {"Centre_ville_Tunis","Sidi_Bousaid","El_Manzeh","Lac1","Lac2","Marsa","Carthage","Centre_ville_Manouba","Zone_Indus_Manouba","Centre_Ville_Ben_Arous","Zone_Indus_Ben_Arous", "Azur_City" , "Tunis_City", "Manar_City", "Tunisia_Mall"};
    for (i = 0; i < 15; i++) {
        if (strcmp(region, regions[i]) == 0) {
            return i;
        }
    }
    return -1;  // Si la région n'est pas trouvée
}


void afficher_agents(GtkWidget *liste) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkListStore *store;
    GtkTreeIter iter;

    // Variables pour stocker les données
    char id[15];
    char nom[50], prenom[50], region[50],email[30], telephone[20];
    int jour, mois, annee, sexe;
    int services_agent[4]; // Stocke les services : lavage, gonflage, recharge, assistance
    FILE *f;

    // Récupération du modèle existant
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));

    if (store == NULL) {
        // Création des colonnes si elles n'existent pas
        if (gtk_tree_view_get_columns(GTK_TREE_VIEW(liste)) == NULL) {
            // Colonne ID
            renderer = gtk_cell_renderer_text_new();
            column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

            // Colonne Nom
            renderer = gtk_cell_renderer_text_new();
            column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 1, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

            // Colonne Prénom
            renderer = gtk_cell_renderer_text_new();
            column = gtk_tree_view_column_new_with_attributes("Prénom", renderer, "text", 2, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

            // Colonne Région
            renderer = gtk_cell_renderer_text_new();
            column = gtk_tree_view_column_new_with_attributes("Région", renderer, "text", 3, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

            // Colonne Téléphone
            renderer = gtk_cell_renderer_text_new();
            column = gtk_tree_view_column_new_with_attributes("Téléphone", renderer, "text", 4, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        }
    }

    // Création d'un nouveau modèle
    store = gtk_list_store_new(5, 
        G_TYPE_STRING, // ID
        G_TYPE_STRING, // Nom
        G_TYPE_STRING, // Prénom
        G_TYPE_STRING, // Région
        G_TYPE_STRING  // Téléphone
    );

    // Lecture des données depuis le fichier "agent.txt"
    f = fopen("agent.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%s %s %s %d %d %d %d %s %s %s %d %d %d %d",
                      id, nom, prenom, &jour, &mois, &annee, &sexe,
                      region, telephone,email, &services_agent[0], &services_agent[1], 
                      &services_agent[2], &services_agent[3])!=EOF) {

            // Ajout des données au modèle
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                0, id,
                1, nom,
                2, prenom,
                3, region,
                4, telephone,
                -1);
        }
        fclose(f);
    }

    // Attacher le modèle au TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store); // Libération du modèle après l'attachement
}

Agent rechercher_agent(const char *file, const char *id_recherche) {
    FILE *f = fopen(file, "r");
    Agent a; // Déclaration de la structure pour l'agent

    // Initialisation de l'agent avec des valeurs par défaut
    strcpy(a.id, "");

    if (f != NULL) {
        // Lire chaque ligne du fichier
        while (fscanf(f, "%s %s %s %d %d %d %d %s %s %s %d %d %d %d\n", 
                      a.id, a.nom, a.prenom, 
                      &a.date_naissance.jour, &a.date_naissance.mois, &a.date_naissance.annee, &a.sexe, a.region, a.telephone, a.email,&a.services_agent[0], &a.services_agent[1], 
                      &a.services_agent[2], &a.services_agent[3]) != EOF) {
            
            // Comparer l'ID de l'agent avec l'ID recherché
            if (strcmp(id_recherche, a.id) == 0) {
                fclose(f); // Fermer le fichier si l'agent est trouvé
                return a;  // Retourner l'agent trouvé
            }
        }
        fclose(f); // Fermer le fichier si aucune correspondance n'est trouvée
    }

    // Si l'agent n'est pas trouvé, l'ID reste vide
    return a;
}

int supprimerAgent(char *file, char *id) {
    int val = 0; // Variable pour indiquer si un agent a été trouvé
    Agent a;
    FILE *f = fopen(file, "r");
    FILE *f2 = fopen("temp.txt", "w"); // Fichier temporaire

    // Vérification que les fichiers ont été ouverts avec succès
    if (f != NULL && f2 != NULL) {
        // Lire chaque agent dans le fichier
        while (fscanf(f, "%s %s %s %d %d %d %d %s %s %s %d %d %d %d\n", 
                a.id, a.nom, a.prenom, 
                &a.date_naissance.jour, &a.date_naissance.mois, &a.date_naissance.annee, 
                &a.sexe, a.region, a.telephone, a.email, 
                &a.services_agent[0], &a.services_agent[1], 
                &a.services_agent[2], &a.services_agent[3]) != EOF) {
            
            // Vérifier si l'ID de l'agent correspond à l'ID à supprimer
            if (strcmp(id, a.id) == 0) {
                val = 1; // Agent trouvé
            } else {
                // Écrire l'agent dans le fichier temporaire si il ne correspond pas
                fprintf(f2, "%s %s %s %d %d %d %d %s %s %s %d %d %d %d\n", 
                    a.id, a.nom, a.prenom, 
                    a.date_naissance.jour, a.date_naissance.mois, a.date_naissance.annee, 
                    a.sexe, a.region, a.telephone, a.email, 
                    a.services_agent[0], a.services_agent[1], 
                    a.services_agent[2], a.services_agent[3]);
            }
        }
    }
    fclose(f);
    fclose(f2);

    // Remplacer l'ancien fichier par le fichier temporaire
    remove(file);
    rename("temp.txt", file);

    return val;
}

void filtrer_agents_par_region(GtkWidget *liste, GtkComboBoxText *combo_box) {
    const char *region_selected = gtk_combo_box_text_get_active_text(combo_box);
    
    if (region_selected != NULL) {
        // Obtenir l'indice de la région sélectionnée
        int index_region = obtenir_index_region((char *)region_selected);
        
        if (index_region != -1) {
            // La région existe, maintenant filtrez les agents selon cette région
            // Réinitialiser la liste affichée (on pourrait vider la liste et la recharger)
            afficher_agents_par_region(liste, region_selected);  // Assurez-vous que cette fonction filtre par région
        } else {
            // Si la région n'est pas valide (ou sélectionné aucune), afficher tous les agents
            afficher_agents(liste);
        }
    }
}
void afficher_agents_par_region(GtkWidget *liste, const char *region) {
GtkListStore *store;
    GtkTreeIter iter;
    char id[15], nom[50], prenom[50], region_agent[50], email[30], telephone[20];
    int jour, mois, annee, sexe;
    int services_agent[4];
    FILE *f;

    // Création d'un nouveau modèle
    store = gtk_list_store_new(5, 
        G_TYPE_STRING, // ID
        G_TYPE_STRING, // Nom
        G_TYPE_STRING, // Prénom
        G_TYPE_STRING, // Région
        G_TYPE_STRING  // Téléphone
    );

    // Lecture des données depuis le fichier "agent.txt"
    f = fopen("agent.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%s %s %s %d %d %d %d %s %s %s %d %d %d %d",
                      id, nom, prenom, &jour, &mois, &annee, &sexe,
                      region_agent, telephone, email, &services_agent[0], 
                      &services_agent[1], &services_agent[2], &services_agent[3]) != EOF) {

            // Filtrer par région
            if (strcmp(region, region_agent) == 0) {
                // Ajouter les données au modèle
                gtk_list_store_append(store, &iter);
                gtk_list_store_set(store, &iter,
                    0, id,
                    1, nom,
                    2, prenom,
                    3, region_agent,
                    4, telephone,
                    -1);
            }
        }
        fclose(f);
    }

    // Associer le modèle filtré au TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store); // Libération du modèle après l'attachement
}


Liste filtreReservationParDate(const char *file, Date dateRecherche) {
    FILE *f = fopen(file, "r");
    Reservation r;
    Liste head = NULL, temp = NULL, newNode = NULL;

    if (f != NULL) {
        while (fscanf(f, "%s %d %d %d %d %d %d %d %d %s %s\n",
                      r.id_reservation,
                      &r.date_debut.jour, &r.date_debut.mois, &r.date_debut.annee,
                      &r.Hdebut, &r.Mdebut,
                      &r.duree, &r.etat, &r.natureD,
                      r.id_utilisateur, r.id_parking) != EOF) {
            
            // Vérifier si la date de la réservation correspond à la date recherchée
            if (r.date_debut.jour == dateRecherche.jour &&
                r.date_debut.mois == dateRecherche.mois &&
                r.date_debut.annee == dateRecherche.annee) {

                // Ajouter la réservation à la liste filtrée
                newNode = (Liste)malloc(sizeof(Liste));
                if (newNode == NULL) {
                    printf("Erreur d'allocation mémoire\n");
                    break;
                }
                newNode->data = r;
                newNode->next = NULL;

                if (head == NULL) {
                    head = newNode;
                } else {
                    temp->next = newNode;
                }
                temp = newNode;
            }
        }
        fclose(f);
    } else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }

    return head;
}

void chargerListeFiltreeDansTreeView(GtkWidget *treeview, Liste list) {
    GtkListStore *store;
    GtkTreeIter iter;

    // Créer un modèle ListStore pour le TreeView
    store = gtk_list_store_new(6,
        G_TYPE_STRING, // ID Réservation
        G_TYPE_STRING, // Nom Parking
        G_TYPE_STRING, // Date Début
        G_TYPE_STRING, // Heure Début
        G_TYPE_INT,    // Durée
        G_TYPE_STRING  // État
    );

    char date_debut_str[12], heure_debut_str[6];

    // Parcourir la liste des réservations filtrées
    while (list != NULL) {
        char nom_parking[30] = "Inconnu"; // Remplacez par le nom réel du parking si nécessaire

        // Conversion des données pour affichage
        sprintf(date_debut_str, "%02d/%02d/%04d", list->data.date_debut.jour, list->data.date_debut.mois, list->data.date_debut.annee);
        sprintf(heure_debut_str, "%02d:%02d", list->data.Hdebut, list->data.Mdebut);

        // Ajouter la réservation au modèle
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
            0, list->data.id_reservation,
            1, nom_parking,
            2, date_debut_str,
            3, heure_debut_str,
            4, list->data.duree,
            5, list->data.etat ? "Validee" : "Annulee",
            -1
        );

        list = list->next;
    }

    // Libérer la liste des réservations
    libererListeReservations(list);

    // Associer le modèle au TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
    g_object_unref(store); // Libérer le store
}
void libererListeReservations(Liste list) {
    Liste temp;
    while (list != NULL) {
        temp = list;
        list = list->next;
        free(temp); // Libère chaque élément de la liste
    }
}
