# SFSD-Projet-TP<br>
<p><b>Simulateur de Gestion de Fichiers</b><br>
Ce document explique comment utiliser le simulateur de gestion de fichiers implémenté en C. <br>
<b>Fonctionnalités Principales</b><br>
Le programme permet de gérer des fichiers et leur contenu à l’aide de plusieurs opérations :<br>

1. Initialisation du Disque<br>

Lors de l'exécution, il vous sera demandé de saisir :<br>

Le nombre de blocs disponibles pour la mémoire secondaire.<br>

La taille maximale de chaque bloc.<br>

2. Création de Fichiers<br>

Créez un nouveau fichier en spécifiant :<br>

Son nom.<br>

Le nombre d’enregistrements.<br>

L'organisation globale (à choix entre contiguë et chaînée).<br>

L'organisation interne (à choix entre non triée et triée).<br>

3. Gestion des Enregistrements<br>

Pour chaque fichier, vous pouvez effectuer les opérations suivantes :<br>

Insertion : Ajouter un nouvel enregistrement.<br>

Recherche : Trouver un enregistrement en fonction de son ID.<br>

Modification : Mettre à jour les données d’un enregistrement existant.<br>

Suppression : Supprimer un enregistrement en fonction de son ID.<br>

4. Affichage et Traitement des Données<br>

Afficher le contenu du fichier : Voir tous les enregistrements d'un fichier.<br>

Trier les enregistrements : Trier les enregistrements par ID.<br>

Défragmenter le fichier : Organiser les blocs pour réduire les espaces inutilisés.<br>

5. Gestion de la Mémoire Secondaire<br>

Compactage : Regrouper les blocs alloués pour libérer l’espace contigu.<br>

Vider la mémoire : Réinitialiser tous les blocs.<br>

6. Gestion des Fichiers<br>

Renommer un fichier : Modifier le nom d’un fichier existant.<br>

Supprimer un fichier : Supprimer complètement un fichier et libérer les blocs associés.<br>

7. Visualisation des Métadonnées<br>

Afficher les informations importantes comme :<br>

L'organisation globale et interne.<br>

Le nombre d’enregistrements.<br>

8. Visualisation de l'État de la Mémoire<br>

Voir l’état de la mémoire secondaire :<br>

Les blocs libres et occupés.<br>

Les noms des fichiers utilisant les blocs.<br>

9. Quitter le Programme<br>

Terminer l'exécution proprement.<br>
<b>Exemple d'Utilisation</b><br>
1-Initialisez la mémoire secondaire avec 100 blocs de taille 50.<br>

2-Créez un fichier "Fichier1" avec 5 enregistrements, organisation globale contiguë et interne triée.<br>

3-Insérez un enregistrement avec l'ID 1 et les données "Test1" et un enregistrement avec l'ID 2 et les données "Test2".<br>

4-Affichez le contenu de "Fichier1".<br>

5-Modifiez les données de l'enregistrement avec l'ID 1 en "UpdatedTest1".<br>

6-Trier les enregistrements.<br>

7-Defragmenter le fichier.<br>

8-Compacter la memoire.<br>

9-Renommer le fichier "Fichier1" par "Fichier2".<br>

10-Afficher les metadonnees de "Fichier2".<br>

11- Afficher l'etat de la memoire secondaire.<br>

12-Rechercher l'enregistrement avec l'ID 2.<br>

13-Supprimez l'enregistrement avec l'ID 1.<br>

14-Supprimez lz fichier "Fichier2".<br>

15-Quitter le programme.<br></P>

