#include <stdio.h>
#include <string.h>

// Structure d'adresse
typedef struct {
    char rue[40];
    char ville[30];
    int code_postal;
} Adresse;

// Structure  personne
typedef struct {
    char nom[20];
    int age;
    Adresse adresse;
} Personne;

// New personne
Personne creerPersonne() {
    Personne p;

    printf("Name: ");
    scanf(" %[^\n]s", p.nom);

    printf("Age: ");
    scanf("%d", &p.age);

    printf("Rue: ");
    scanf(" %[^\n]s", p.adresse.rue);

    printf("Ville: ");
    scanf(" %[^\n]s", p.adresse.ville);

    printf("Code postal: ");
    scanf("%d", &p.adresse.code_postal);

    return p;
}

// Afficher informations du personne
void afficherPersonne(Personne p) {
    printf("Nom: %s\n", p.nom);
    printf("Age: %d\n", p.age);
    printf("Adresse: %s, %s, %d\n", p.adresse.rue, p.adresse.ville, p.adresse.code_postal);
}

// mis a jour des informations
Personne mettreAJourPersonne(Personne p) {
    printf("\nMettre a jour les informations pour %s\n", p.nom);

    printf("Nouvel age: ");
    scanf("%d", &p.age);

    printf("Nouvelle rue: ");
    scanf(" %[^\n]s", p.adresse.rue);

    printf("Nouvelle ville: ");
    scanf(" %[^\n]s", p.adresse.ville);

    printf("New code postal: ");
    scanf("%d", &p.adresse.code_postal);

    return p;
}

// supprimer personne
Personne supprimerPersonne(Personne p) {
    strcpy(p.nom, "");
    p.age = -1;
    strcpy(p.adresse.rue, "");
    strcpy(p.adresse.ville, "");
    p.adresse.code_postal = -1;

    return p;
}

// SAVE File
void sauvegarderPersonnes(Personne personnes[], int nb_personnes) {
    FILE *fichier = fopen("personnes.txt", "w");
    if (fichier == NULL) {
        printf("Erreur: impossible de sauvegarder les donnees.\n");
        return;
    }

    for (int i = 0; i < nb_personnes; i++) {
        if (personnes[i].age != -1) {
            fprintf(fichier, "%s\n%d\n%s\n%s\n%d\n",
                    personnes[i].nom,
                    personnes[i].age,
                    personnes[i].adresse.rue,
                    personnes[i].adresse.ville,
                    personnes[i].adresse.code_postal);
        }
    }

    fclose(fichier);
}

// save infos in the file
int chargerPersonnes(Personne personnes[]) {
    FILE *fichier = fopen("personnes.txt", "r");
    if (fichier == NULL) {
        return 0;
    }

    int i = 0;
    while (fscanf(fichier, " %[^\n]s", personnes[i].nom) == 1) {
        fscanf(fichier, "%d", &personnes[i].age);
        fscanf(fichier, " %[^\n]s", personnes[i].adresse.rue);
        fscanf(fichier, " %[^\n]s", personnes[i].adresse.ville);
        fscanf(fichier, "%d", &personnes[i].adresse.code_postal);
        i++;
    }

    fclose(fichier);
    return i;
}

// MAIN Fonction
int main() {
    int choix, nb_personnes = 0, index;
    Personne personnes[100];  // Table personnes,  max 100

    // Upload infos
    nb_personnes = chargerPersonnes(personnes);

    do {
        printf("\n________________Menu:________________\n");
        printf("1- Creer une nouvelle personne\n");
        printf("2- Afficher tout personnes\n");
        printf("3- Mis a jour une personne\n");
        printf("4- Supprimer une personne\n");
        printf("5- Quitter\n");
        printf("________________ Votre Choix est:________________ ");
        scanf("%d", &choix);

        switch(choix) {
            case 1:
                if (nb_personnes < 100) {
                    personnes[nb_personnes] = creerPersonne();
                    nb_personnes++;
                } else {
                    printf("Limite de personnes atteinte.\n");
                }
                break;

            case 2:
                for (int i = 0; i < nb_personnes; i++) {
                    if (personnes[i].age != -1) {
                        afficherPersonne(personnes[i]);
                    }
                }
                break;

            case 3:
                printf("Numero de personne a mettre a jour (1 a %d): ", nb_personnes);
                scanf("%d", &index);
                if (index > 0 && index <= nb_personnes && personnes[index - 1].age != -1) {
                    personnes[index - 1] = mettreAJourPersonne(personnes[index - 1]);
                } else {
                    printf("Invalid Personne.\n");
                }
                break;

            case 4:
                printf("Numero de personne supprimer (1 a %d): ", nb_personnes);
                scanf("%d", &index);
                if (index > 0 && index <= nb_personnes && personnes[index - 1].age != -1) {
                    personnes[index - 1] = supprimerPersonne(personnes[index - 1]);
                    printf("Personne supprimer.\n");
                } else {
                    printf("Invalid Personne.\n");
                }
                break;

            case 5:
                printf("See you again\n");
                sauvegarderPersonnes(personnes, nb_personnes); // Final save
                break;

            default:
                printf("Choix invalide.\n");
                break;
        }
    } while (choix != 5);

    return 0;
}
