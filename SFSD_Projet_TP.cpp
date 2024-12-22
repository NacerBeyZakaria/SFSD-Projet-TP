#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 10
#define MAX_DATA_SIZE 50


// Declaration des structures
typedef struct {
    int id;
    char data[MAX_DATA_SIZE];
} Enregistrement;

typedef struct {
    int is_free;
    char fichier_nom[50];
    int next_bloc;
    int nb_enregistrements;
    Enregistrement enreg;
} Bloc;

typedef struct {
    char nom[50];
    int nb_enregistrements;
    int organisation_globale;
    int organisation_interne;
    Bloc *blocs[MAX_DATA_SIZE];
} Fichier;

typedef struct {
    char nom_fichier[50];            
    int taille_fichier_blocs;       
    int taille_fichier_enregs;       
    int adresse_premier_bloc;        
    int mode_org_globale;            
    int mode_org_interne;            
} Metadata;

Bloc *memoire = NULL;

// Les Fonctins
void initialiser_disque(int nb_blocs, int taille_bloc) {
    memoire = (Bloc *)malloc(nb_blocs * sizeof(Bloc));
    if (memoire == NULL) {
        printf("Erreur de memoire !\n");
        exit(1);
    }
    for (int i = 0; i < nb_blocs; i++) {
        memoire[i].is_free = 1;
        memoire[i].next_bloc = -1;
    }
}

void creer_fichier(Fichier *fichier) {
    printf("Entrez le nom du fichier: ");
    scanf("%s", fichier->nom);

    printf("Entrez le nombre d'enregistrements: ");
    scanf("%d", &fichier->nb_enregistrements);

    printf("Choisissez l'organisation globale (0 pour Contigue, 1 pour Chainee): ");
    scanf("%d", &fichier->organisation_globale);

    printf("Choisissez l'organisation interne (0 pour Non Triee, 1 pour Triee): ");
    scanf("%d", &fichier->organisation_interne);

    for (int i = 0; i < fichier->nb_enregistrements; i++) {
        fichier->blocs[i] = NULL;
    }
}

void afficher_fichier(Fichier *fichier) {
    printf("Nom du fichier: %s\n", fichier->nom);
    printf("Nombre d'enregistrements: %d\n", fichier->nb_enregistrements);
    for (int i = 0; i < fichier->nb_enregistrements; i++) {
        if (fichier->blocs[i] != NULL) {
            printf("ID: %d, Donnees: %s\n", fichier->blocs[i]->enreg.id, fichier->blocs[i]->enreg.data);
        }
    }
}

void inserer_enregistrement(Fichier *fichier, Enregistrement enreg) {
    if (fichier->organisation_globale == 0) {
        for (int i = 0; i < fichier->nb_enregistrements; i++) {
            if (fichier->blocs[i] == NULL) {
                fichier->blocs[i] = &memoire[i];
                fichier->blocs[i]->enreg = enreg;
                fichier->blocs[i]->is_free = 0;
                break;
            }
        }
    } else {
        for (int i = 0; i < fichier->nb_enregistrements; i++) {
            if (fichier->blocs[i] == NULL) {
                fichier->blocs[i] = &memoire[i];
                fichier->blocs[i]->enreg = enreg;
                fichier->blocs[i]->is_free = 0;
                if (i < fichier->nb_enregistrements - 1) {
                    fichier->blocs[i]->next_bloc = i + 1;
                } else {
                    fichier->blocs[i]->next_bloc = -1;
                }
                break;
            }
        }
    }
}

void rechercher_enregistrement(Fichier *fichier, int id) {
    for (int i = 0; i < fichier->nb_enregistrements; i++) {
        if (fichier->blocs[i] != NULL && fichier->blocs[i]->enreg.id == id) {
            printf("Enregistrement trouve: ID = %d, Donnees = %s\n", fichier->blocs[i]->enreg.id, fichier->blocs[i]->enreg.data);
            return;
        }
    }
    printf("Enregistrement non trouve.\n");
}

void modifier_enregistrement(Fichier *fichier, int id, char *new_data) {
    for (int i = 0; i < fichier->nb_enregistrements; i++) {
        if (fichier->blocs[i] != NULL && fichier->blocs[i]->enreg.id == id) {
            strcpy(fichier->blocs[i]->enreg.data, new_data);
            printf("Enregistrement modifie: ID = %d, Donnees = %s\n", fichier->blocs[i]->enreg.id, fichier->blocs[i]->enreg.data);
            return;
        }
    }
    printf("Enregistrement non trouve.\n");
}

void supprimer_enregistrement(Fichier *fichier, int id) {
    for (int i = 0; i < fichier->nb_enregistrements; i++) {
        if (fichier->blocs[i] != NULL && fichier->blocs[i]->enreg.id == id) {
            fichier->blocs[i]->is_free = 1;
            fichier->blocs[i] = NULL;
            printf("Enregistrement supprime: ID = %d\n", id);
            return;
        }
    }
    printf("Enregistrement non trouve.\n");
}

void trier_enregistrements(Fichier *fichier) {
    for (int i = 0; i < fichier->nb_enregistrements - 1; i++) {
        for (int j = i + 1; j < fichier->nb_enregistrements; j++) {
            if (fichier->blocs[i] != NULL && fichier->blocs[j] != NULL &&
                fichier->blocs[i]->enreg.id > fichier->blocs[j]->enreg.id) {
                Bloc *temp = fichier->blocs[i];
                fichier->blocs[i] = fichier->blocs[j];
                fichier->blocs[j] = temp;
            }
        }
    }
    printf("Les enregistrements ont ete tries.\n");
}

void defragmenter_fichier(Fichier *fichier) {
    int index = 0;
    for (int i = 0; i < fichier->nb_enregistrements; i++) {
        if (fichier->blocs[i] != NULL) {
            if (i != index) {
                fichier->blocs[index] = fichier->blocs[i];
                fichier->blocs[i] = NULL;
            }
            index++;
        }
    }
    printf("Le fichier a ete defragmente.\n");
}

void creer_metadata(Fichier *fichier, Metadata *metadata) {
    strcpy(metadata->nom_fichier, fichier->nom);
    metadata->taille_fichier_blocs = fichier->nb_enregistrements;
    metadata->taille_fichier_enregs = fichier->nb_enregistrements;
    metadata->adresse_premier_bloc = (fichier->blocs[0] != NULL) ? fichier->blocs[0] - memoire : -1;
    metadata->mode_org_globale = fichier->organisation_globale;
    metadata->mode_org_interne = fichier->organisation_interne;
}

int recherche_binaire(Fichier *fichier, int id) {
    int gauche = 0;
    int droite = fichier->nb_enregistrements - 1;

    while (gauche <= droite) {
        int milieu = (gauche + droite) / 2;
        if (fichier->blocs[milieu] != NULL && fichier->blocs[milieu]->enreg.id == id) {
            printf("Enregistrement trouve au bloc %d\n", milieu);
            return milieu;
        } else if (fichier->blocs[milieu] != NULL && fichier->blocs[milieu]->enreg.id < id) {
            gauche = milieu + 1;
        } else {
            droite = milieu - 1;
        }
    }

    printf("Enregistrement non trouve.\n");
    return -1;
}

int verifier_espace_disponible(Fichier *fichier) {
    int espaces_libres = 0;
    for (int i = 0; i < MAX_DATA_SIZE; i++) {
        if (memoire[i].is_free == 1) {
            espaces_libres++;
        }
    }

    if (espaces_libres >= fichier->nb_enregistrements) {
        return 1;
    } else {
        printf("Espace insuffisant, veuillez effectuer un compactage.\n");
        return 0;
    }
}

void mettre_a_jour_etat_blocs() {
    for (int i = 0; i < MAX_DATA_SIZE; i++) {
        if (memoire[i].is_free == 0 && memoire[i].next_bloc == -1) {
            memoire[i].is_free = 1;
        }
    }
}

void vider_MS() {
    for (int i = 0; i < MAX_DATA_SIZE; i++) {
        memoire[i].is_free = 1;
        memoire[i].next_bloc = -1;
    }
}
void compactage() {
    int i = 0;
    for (int j = 0; j < MAX_DATA_SIZE; j++) {
        if (memoire[j].is_free == 0) {
            if (i != j) {
                memoire[i] = memoire[j];  
                memoire[j].is_free = 1;   
            }
            i++;
        }
    }
    printf("Compactage effectue.\n");
}

void renommer_fichier(Fichier *fichier, char *new_name) {
    strcpy(fichier->nom, new_name);
    printf("Le fichier a ete renomme en %s.\n", fichier->nom);
}

void afficher_metadonnees(Fichier *fichier) {
    printf("Metadonnees du fichier %s:\n", fichier->nom);
    printf("Organisation globale: %d\n", fichier->organisation_globale);
    printf("Organisation interne: %d\n", fichier->organisation_interne);
    printf("Nombre d'enregistrements: %d\n", fichier->nb_enregistrements);
}

void supprimer_fichier(Fichier *fichier) {
    for (int i = 0; i < fichier->nb_enregistrements; i++) {
        if (fichier->blocs[i] != NULL) {
            fichier->blocs[i]->is_free = 1;
            fichier->blocs[i] = NULL;
        }
    }
    printf("Le fichier %s a ete supprime.\n", fichier->nom);
}

int choisir_fichier(Fichier *fichiers, int nb_fichiers) {
    int choix;
    printf("\nChoisissez un fichier:\n");
    for (int i = 0; i < nb_fichiers; i++) {
        printf("%d. %s\n", i + 1, fichiers[i].nom);
    }
    printf("Entrez le numero du fichier: ");
    scanf("%d", &choix);
    return choix - 1;
}
void afficherEtatMemoire() {
    printf("\nEtat de la memoire secondaire :\n");
    for (int i = 0; i < MAX_DATA_SIZE; i++) {
        printf("---------------------\n");
        printf("| ");
        if (memoire[i].is_free) {
            printf("\033[1;32mLibre\033[0m");
        } else {
            printf("\033[1;31m%-8s %2d enreg\033[0m", memoire[i].fichier_nom, memoire[i].nb_enregistrements);
        }
        printf(" |\n");
        printf("---------------------\n");
    }
}

// Menu Principle
int main(){
	Fichier fichier;
	Metadata metadata;
    Fichier fichiers[MAX_FILES];
    int nb_fichiers = 0;
    int choix, id;
    Enregistrement enreg;
    char nouvelle_donnee[MAX_DATA_SIZE];
    int nb_blocs, taille_bloc;

    printf("Entrez le nombre de blocs disponibles pour le disque: ");
    scanf("%d", &nb_blocs);
    printf("Entrez la taille maximale du bloc (facteur de blocage): ");
    scanf("%d", &taille_bloc);

    initialiser_disque(nb_blocs, taille_bloc);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Creer un fichier\n");
        printf("2. Inserer un enregistrement\n");
        printf("3. Rechercher un enregistrement\n");
        printf("4. Modifier un enregistrement\n");
        printf("5. Supprimer un enregistrement\n");
        printf("6. Afficher le contenu du fichier\n");
        printf("7. Trier les enregistrements\n");
        printf("8. Defragmenter le fichier\n");
        printf("9. Compacter la memoire\n");
        printf("10. Vider la memoire\n");
		printf("11. Renommer un fichier\n");
        printf("12. Supprimer un fichier\n");
        printf("13. Afficher les metadonnees\n");
        printf("14. Afficher l'etat de la memoire secondaire\n");
        printf("15. Quitter\n");
        printf("Choisissez une option: ");
        scanf("%d", &choix);

        switch (choix) {
        case 1:
            if (nb_fichiers < MAX_FILES) {
                creer_fichier(&fichiers[nb_fichiers]);
                nb_fichiers++;
            } else {
                printf("Limite de fichiers atteinte.\n");
            }
            break;

        case 2:
            if (nb_fichiers == 0) {
                printf("Aucun fichier n'a ete cree.\n");
            } else {
                int index_fichier = choisir_fichier(fichiers, nb_fichiers);
                printf("Entrez l'ID de l'enregistrement: ");
                scanf("%d", &enreg.id);
                printf("Entrez les donnees de l'enregistrement: ");
                getchar();
                fgets(enreg.data, MAX_DATA_SIZE, stdin);
                enreg.data[strcspn(enreg.data, "\n")] = 0;
                inserer_enregistrement(&fichiers[index_fichier], enreg);
            }
            break;

        case 3:
        	  if (nb_fichiers == 0) {
                printf("Aucun fichier n'a ete cree.\n");
            } else {
                int index_fichier = choisir_fichier(fichiers, nb_fichiers);
                printf("Entrez l'ID de l'enregistrement a rechercher: ");
                scanf("%d", &id);
                rechercher_enregistrement(&fichiers[index_fichier], id);
            }
            break;

           

        case 4:
        	 if (nb_fichiers == 0) {
                printf("Aucun fichier n'a ete cree.\n");
            } else {
                int index_fichier = choisir_fichier(fichiers, nb_fichiers);
                printf("Entrez l'ID de l'enregistrement a modifier: ");
                scanf("%d", &id);
                printf("Entrez les nouvelles donnees: ");
                getchar();
                fgets(nouvelle_donnee, MAX_DATA_SIZE, stdin);
                nouvelle_donnee[strcspn(nouvelle_donnee, "\n")] = 0;
                modifier_enregistrement(&fichiers[index_fichier], id, nouvelle_donnee);
            }
            break;

          
        case 5:
        	if (nb_fichiers == 0) {
                printf("Aucun fichier n'a ete cree.\n");
            } else {
                int index_fichier = choisir_fichier(fichiers, nb_fichiers);
                printf("Entrez l'ID de l'enregistrement a supprimer: ");
                scanf("%d", &id);
                supprimer_enregistrement(&fichiers[index_fichier], id);
            }
            break;

           
        case 6:
        	 if (nb_fichiers == 0) {
                printf("Aucun fichier n'a ete cree.\n");
            } else {
                int index_fichier = choisir_fichier(fichiers, nb_fichiers);
                afficher_fichier(&fichiers[index_fichier]);
            }
            break;

            
        case 7:
            if (nb_fichiers == 0) {
                printf("Aucun fichier n'a ete cree.\n");
            } else {
                int index_fichier = choisir_fichier(fichiers, nb_fichiers);
                trier_enregistrements(&fichiers[index_fichier]);
            }
            break;

        case 8:
            if (nb_fichiers == 0) {
                printf("Aucun fichier n'a ete cree.\n");
            } else {
                int index_fichier = choisir_fichier(fichiers, nb_fichiers);
                defragmenter_fichier(&fichiers[index_fichier]);
            }
            break;

        case 9:
           compactage();
            creer_metadata(&fichier, &metadata);
            break;
            
        case 10:
        	vider_MS();
            creer_metadata(&fichier, &metadata);
            break;
           
        case 11:
        	 if (nb_fichiers == 0) {
                printf("Aucun fichier n'a ete cree.\n");
            } else {
                int index_fichier = choisir_fichier(fichiers, nb_fichiers);
                char nouveau_nom[50];
                printf("Entrez le nouveau nom du fichier: ");
                scanf("%s", nouveau_nom);
                renommer_fichier(&fichiers[index_fichier], nouveau_nom);
            }
            break;


        case 12:
        	 if (nb_fichiers == 0) {
                printf("Aucun fichier n'a ete cree.\n");
            } else {
                int index_fichier = choisir_fichier(fichiers, nb_fichiers);
                supprimer_fichier(&fichiers[index_fichier]);
                // Shift files down in the array after deletion
                for (int i = index_fichier; i < nb_fichiers - 1; i++) {
                    fichiers[i] = fichiers[i + 1];
                }
                nb_fichiers--;
            }
            break;

         
		case 13:
			  if (nb_fichiers == 0) {
                printf("Aucun fichier n'a ete cree.\n");
            } else {
                int index_fichier = choisir_fichier(fichiers, nb_fichiers);
                afficher_metadonnees(&fichiers[index_fichier]);
            }
            break;
        case 14:
		 afficherEtatMemoire();
                break;
		case 15:
		   printf("Au revoir!\n");
            exit(0);    
        default:
            printf("Option invalide, essayez encore.\n");
            break;
        }
    }
    return 0;
}

