#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <time.h>
#include <windows.h>
#define MAX_USERS 100
#define MAX_RECLAMATION 100

// Function declarations
void admin();
void creer_compte();
int password_check(char pass[], char name[]);
void admin_menu();
void agent_menu();
void client_menu();
int user_role(int index);
void menu_role(int userRole);
void recherche_status();
void recherche_nom();
void recherche_identifiant();
void connecter_vous();
void gerer_role();
void list_users();
void creer_reclamation();
void afficher_reclamation_client();
void afficher_reclamation();
void afficher_par_priorite();
void modifier_reclamation();
void supprimer_reclamation();
void traiter_reclamation();
void chercher_reclamation();

// Global variables and initialization
int user_count = 1;
int reclamation_count = 0;
int user_index = 0;
time_t tmp = 0;
// User structure
typedef struct {
    char nom[50];
    int role;
    char password[50];
    int identifiant;
} User;
User users[MAX_USERS];
// Reclamation structure
typedef struct {
    int ID;
    int userIndex;
    int user_identifiant;
    char motif[30];
    char description[200];
    char categorie[30];
    char status[30];
    char date[30];
    time_t datE;
    char prioriter[30];
    int ordre_prioriter;
} Reclamation;
Reclamation reclamations[MAX_RECLAMATION];

// Create an admin
void admin() {
    strcpy(users[0].nom, "admin");
    users[0].role = 0;
    strcpy(users[0].password, "Admin@2024");
    users[0].identifiant = 0;
}

// Create an account
void creer_compte() {
    if (user_count >= MAX_USERS) {
        printf("Impossible de creer le compte!\n");
        printf("Le maximum des clients est atteint.\n");
        return;
    }

    User client;
    client.role = 2; // 2 user = client
    client.identifiant = user_count;

    printf("Entrer les informations suivantes : \n");
    printf("nom : ");
    fgets(client.nom, sizeof(client.nom), stdin);
    client.nom[strcspn(client.nom, "\n")] = '\0';

    while (1) {
        printf("password : ");
        fgets(client.password, sizeof(client.password), stdin);
        client.password[strcspn(client.password, "\n")] = '\0';

        if (password_check(client.password, client.nom)) {
            users[user_count] = client;
            printf("Compte est cree avec l'identifiant : %d\n", user_count);
            user_count++;
            break;
        } else {
            printf("\n........... Attention : \n");
            printf("Le mot de passe doit contenir au moins 8 caracteres : \n");
            printf("Un caractere majuscule, minuscule, chiffre et un caractere special (par exemple : !@#$^&*)\n");
            printf("Il ne doit pas contenir votre nom.\n");
            printf("Veuillez essayer a nouveau.\n");
            printf("....................................\n");
        }
    }
}

// Check password
int password_check(char pass[], char name[]) {
    int majuscule = 0, minuscule = 0, chiffre = 0, caractere = 0;
    if (strlen(pass) < 8 || strstr(pass, name) != NULL) {
        return 0;
    }

    for (int i = 0; pass[i]; i++) {
        if (pass[i] >= 'A' && pass[i] <= 'Z') majuscule = 1;
        else if (pass[i] >= 'a' && pass[i] <= 'z') minuscule = 1;
        else if (pass[i] >= '0' && pass[i] <= '9') chiffre = 1;
        else caractere = 1;
    }

    return (majuscule && minuscule && caractere && chiffre);
}

// Login function
int tentative = 0;
void connecter_vous() {
    char pass[50];
    int id;
    printf("Entrer votre identifiant : ");
    scanf("%d", &id);
    getchar();
    printf("Entrer votre mot de passe : ");
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = '\0';

    for (int i = 0; i < user_count; i++) {
        if (users[i].identifiant == id && strcmp(users[i].password, pass) == 0) {
            user_index = i;
            menu_role(users[i].role);
            tentative = 0;
            return;
        }
    }

    printf("Identifiant ou mot de passe incorrect. Tentatives restantes : %d\n", 2 - tentative);
    tentative++;
    if (tentative >= 3) {
        printf("Trop de tentatives incorrectes. Essayez apres 5 secondes.\n");
        Sleep(5000);
        tentative = 0;
    }
    connecter_vous();
}

//  user role
void menu_role(int userRole) {
    switch (userRole) {
        case 0: admin_menu(); break;
        case 1: agent_menu(); break;
        case 2: client_menu(); break;
        default: printf("Role non reconnu.\n");
    }
}

// Manage user role
void gerer_role() {
    int id, newRole;
    printf("l'identifiant de l'utilisateur a modifier : ");
    scanf("%d", &id);
    printf("le nouveau role (admin -> 0,agent -> 1,client -> 2): ");
    scanf("%d", &newRole);

    if (newRole < 0 || newRole > 2) {
        printf("Role invalide.\n");
        return;
    }

    for (int i = 0; i < user_count; i++) {
        if (users[i].identifiant == id) {
            users[i].role = newRole;
            printf("Le role est bien change.\n");
            return;
        }
    }
    printf("Utilisateur non trouve.\n");
}

// List users
void list_users() {
    if (user_count == 0) {
        printf("Pas d'utilisateurs!\n");
        return;
    }

    printf("======= Liste des utilisateurs : \n");
    for (int i = 0; i < user_count; i++) {
        printf("***************************************\n");
        printf("Informations de l'utilisateur %d : \n", i + 1);
        printf("nom  : %s\n", users[i].nom);
        printf("user identifiant : %d\n", users[i].identifiant);
        printf("user role : %d\n", users[i].role);
        printf("***************************************\n");
    }
}

// Creer Reclamation
void creer_reclamation() {
    if (reclamation_count >= MAX_RECLAMATION) {
        printf("Impossible de creer une reclamation pour le moment.\n");
        return;
    }
    Reclamation new_reclamation;
        new_reclamation.userIndex = user_index;
        new_reclamation.ID = reclamation_count + 1;
        strcpy(new_reclamation.status, "en cours");
        printf("information de reclamation : \n");
        printf("motif : ");
        fgets(new_reclamation.motif, sizeof(new_reclamation.motif), stdin);
        new_reclamation.motif[strcspn(new_reclamation.motif, "\n")] = '\0';

        printf("description : ");
        fgets(new_reclamation.description, sizeof(new_reclamation.description), stdin);
        new_reclamation.description[strcspn(new_reclamation.description, "\n")] = '\0';

        printf("categorie : ");
        fgets(new_reclamation.categorie, sizeof(new_reclamation.categorie), stdin);
        new_reclamation.categorie[strcspn(new_reclamation.categorie, "\n")] = '\0';
        time(&tmp);
        time_t Date = time(NULL);
        strcpy(new_reclamation.date, ctime(&Date));


        time(&reclamations[reclamation_count].datE);//pour le mot de passe

        if (strstr(new_reclamation.description, "critique") != NULL) {
            strcpy(new_reclamation.prioriter, "Haute");
            new_reclamation.ordre_prioriter = 0;
        } else if (strstr(new_reclamation.description, "regulier") != NULL) {
            strcpy(new_reclamation.prioriter, "moyenne");
            new_reclamation.ordre_prioriter = 1;
        } else {
            strcpy(new_reclamation.prioriter, "basse");
            new_reclamation.ordre_prioriter = 2;
        }
        reclamations[reclamation_count] = new_reclamation;
        reclamation_count++;
        printf("Reclamation numero %d a ete bien creee avec un ID %d.\n", reclamation_count, new_reclamation.ID);
   

    
}
// Afficher tous les reclamations
void afficher_reclamation() {
    if (reclamation_count == 0) {
        printf("Pas de reclamation!\n");
        return;
    }
    for (int i = 0; i < reclamation_count; i++) {
        printf("***************************************\n");
        printf("client : %s\n", users[reclamations[i].userIndex].nom);
        printf("Reclamation ID: %d\n", reclamations[i].ID);
        printf("motif : %s\n", reclamations[i].motif);
        printf("categorie : %s\n", reclamations[i].categorie);
        printf("Description : %s\n", reclamations[i].description);
        printf("status de reclamation : %s\n", reclamations[i].status);
        printf("status de priorite : %s\n", reclamations[i].prioriter);
        printf("ordre de priorite : %d\n", reclamations[i].ordre_prioriter);
        printf("date : %s\n", reclamations[i].date);
        printf("***************************************\n");
    }
}

// afficher par ordre de priorite
void afficher_par_priorite() {
    if (reclamation_count == 0) {
        printf("Pas de reclamation!\n");
        return;
    }

    Reclamation temp_reclamations[MAX_RECLAMATION];
    memcpy(temp_reclamations, reclamations, sizeof(reclamations));

    for (int i = 0; i < reclamation_count - 1; i++) {
        for (int j = 0; j < reclamation_count - i - 1; j++) {
            if (temp_reclamations[j].ordre_prioriter > temp_reclamations[j + 1].ordre_prioriter) {
                Reclamation temp = temp_reclamations[j];
                temp_reclamations[j] = temp_reclamations[j + 1];
                temp_reclamations[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < reclamation_count; i++) {
        printf("***************************************\n");
        printf("Reclamation ID: %d\n", temp_reclamations[i].ID);
        printf("User ID: %d\n", temp_reclamations[i].user_identifiant);
        printf("motif : %s\n", temp_reclamations[i].motif);
        printf("categorie : %s\n", temp_reclamations[i].categorie);
        printf("Description : %s\n", temp_reclamations[i].description);
        printf("status de reclamation : %s\n", temp_reclamations[i].status);
        printf("status de priorite : %s\n", temp_reclamations[i].prioriter);
        printf("ordre de priorite : %d\n", temp_reclamations[i].ordre_prioriter);
        printf("date : %s\n", temp_reclamations[i].date);
        printf("***************************************\n");
    }
}

// modifierreclamation
void modifier_reclamation() {
    int id_reclamation;
    
    printf("ID de reclamation : ");
    scanf("%d", &id_reclamation);
    getchar();
    for (int i=0; i<reclamation_count; i++){
        if (id_reclamation == reclamations[i].ID){
            printf("ID existe\n");
            int rec_index = i;
            
                if (users[user_index].role == 0 || users[user_index].role == 1 ){
                    printf("Nouveau motif : ");
                fgets(reclamations[i].motif, sizeof(reclamations[i].motif), stdin);
                reclamations[i].motif[strcspn(reclamations[i].motif, "\n")] = '\0';
                printf("Nouvelle description : ");
                fgets(reclamations[i].description, sizeof(reclamations[i].description), stdin);
                reclamations[i].description[strcspn(reclamations[i].description, "\n")] = '\0';
                printf("Nouvelle categorie : ");
                fgets(reclamations[i].categorie, sizeof(reclamations[i].categorie), stdin);
                reclamations[i].categorie[strcspn(reclamations[i].categorie, "\n")] = '\0';
                printf("Reclamation modifiee avec succes.\n");
                }
                else {
                printf("Pas de reclamation avec cette ID.\n");
            }
                
            }
        }
        
        
}
void modifier_reclamation_client(){
    int id_reclamation;
    int exist = 0;
    printf("ID de reclamation a modifier : ");
    scanf("%d", &id_reclamation);
    getchar();
    for (int i=0; i<reclamation_count; i++){
        if (id_reclamation == reclamations[i].ID && reclamations[i].userIndex == user_index){ 
            exist = 1;
            time_t date_actuelle = time(NULL);
            if (difftime(date_actuelle, tmp) < 20){
                printf("Nouveau motif : ");
                fgets(reclamations[i].motif, sizeof(reclamations[i].motif), stdin);
                reclamations[i].motif[strcspn(reclamations[i].motif, "\n")] = '\0';
                printf("Nouvelle description : ");
                fgets(reclamations[i].description, sizeof(reclamations[i].description), stdin);
                reclamations[i].description[strcspn(reclamations[i].description, "\n")] = '\0';
                printf("Nouvelle categorie : ");
                fgets(reclamations[i].categorie, sizeof(reclamations[i].categorie), stdin);
                reclamations[i].categorie[strcspn(reclamations[i].categorie, "\n")] = '\0';
                printf("Reclamation modifiee avec succes.\n");
            }
            else {
                printf("vous avez depassez 24 heures.\n");
            } 
        }
    }
    if (!exist){
        printf("Pas de reclamation avec cette ID\n");
    }

}
// supprimer reclamation
void supprimer_reclamation() {
    int id_supprimer;
    printf("Entrer ID de reclamation a supprimer : ");
    scanf("%d", &id_supprimer);

    int index_supprimer = -1;
    for (int i = 0; i < reclamation_count; i++) {
        if (id_supprimer == reclamations[i].ID) {
            index_supprimer = i;
            break;
        }
    }
    if (index_supprimer == -1) {
        printf("Reclamation avec cet ID n'existe pas.\n");
        return;
    }
    int user_role = users[user_index].role;
    if (user_role == 0 || user_role == 1 || (user_role == 2 && reclamations[index_supprimer].userIndex == users[user_index].identifiant)) {
        for (int i = index_supprimer; i < reclamation_count - 1; i++) {
            reclamations[i] = reclamations[i + 1];
        }
        reclamation_count--;
        printf("Reclamation supprimee avec succes.\n");
    } else {
        printf("Vous n'avez pas les droits pour supprimer cette reclamation.\n");
    }
}

// traiter reclamation
void traiter_reclamation() {
    int id_traiter;
    if (reclamation_count == 0) {
        printf("Pas de reclamation a traiter.\n");
        return;
    }

    printf("Entrer ID de reclamation a traiter : ");
    scanf("%d", &id_traiter);
    getchar();

    int index_traiter = -1;
    for (int i = 0; i < reclamation_count; i++) {
        if (reclamations[i].ID == id_traiter) {
            index_traiter = i;
            break;
        }
    }

    if (index_traiter == -1) {
        printf("Reclamation a traiter n'existe pas!\n");
        return;
    }

    printf("Choisir le nouveau statut :\n");
    printf("1. En cours\n");
    printf("2. Resolue\n");
    printf("3. Fermee\n");
    int choix;
    scanf("%d", &choix);
    getchar();

    switch (choix) {
        case 1:
            strcpy(reclamations[index_traiter].status, "en cours");
            break;
        case 2:
            strcpy(reclamations[index_traiter].status, "resolue");
            break;
        case 3:
            strcpy(reclamations[index_traiter].status, "fermee");
            break;
        default:
            printf("Choix invalide.\n");
            return;
    }

    printf("Statut modifie avec succes.\n");
}

//chercher reclamation
void chercher_reclamation() {
    int type_recherche;
    printf("Entrer la methode de recherche d'une reclamation : \n");
    printf("1. Chercher par ID\n");
    printf("2. Chercher par nom\n");
    printf("3. Chercher par statut\n");
    printf("Entrer le nombre de votre choix : ");
    scanf("%d", &type_recherche);
    getchar();

    switch(type_recherche) {
        case 1:
            recherche_identifiant();
            break;
        case 2:
            recherche_nom();
            break;
        case 3:
            recherche_status();
            break;
        default:
            printf("Choix invalide!\n");
    }
}

//chercher reclamation par ID
void recherche_identifiant() {
    int indice;
    printf("Entrer ID de la reclamation cherchee : ");
    scanf("%d", &indice);
    getchar();

    for (int i = 0; i < reclamation_count; i++) {
        if (indice == reclamations[i].ID) {
            printf("*********************************************\n");
            printf("Reclamation recherchee : \n");
            printf("client : %s\n", users[reclamations[i].ID].nom);
            printf("User ID: %d\n", reclamations[i].user_identifiant);
            printf("Motif : %s\n", reclamations[i].motif);
            printf("Categorie : %s\n", reclamations[i].categorie);
            printf("Description : %s\n", reclamations[i].description);
            printf("Statut : %s\n", reclamations[i].status);
            printf("Date : %s\n", reclamations[i].date);
            printf("*********************************************\n");
            return;
        }
    }
    printf("Pas de reclamation avec cet ID.\n");
}

// chercher reclamation par nom
void recherche_nom() {
    char client_nom[50];
    printf("Entrer le nom du client : ");
    fgets(client_nom, sizeof(client_nom), stdin);
    client_nom[strcspn(client_nom, "\n")] = '\0';
    int found = 0;
    for (int i = 0; i < user_count; i++) {
        if (strcmp(client_nom, users[reclamations[i].userIndex].nom) == 0) {
            found = 1;
                    printf("*********************************************\n");
                    printf("    Reclamation trouvee : \n");
                    printf("client : %s\n", users[reclamations[i].ID].nom);
                    printf("Motif : %s\n", reclamations[i].motif);
                    printf("Categorie : %s\n", reclamations[i].categorie);
                    printf("Description : %s\n", reclamations[i].description);
                    printf("Statut : %s\n", reclamations[i].status);
                    printf("Date : %s\n", reclamations[i].date);
                    printf("*********************************************\n");   
        }
        
    }
    if (!found) {
        printf("Pas de reclamation pour ce client.\n");
    }
}

// chercher par status
void recherche_status() {
    char status_chercher[20];
    printf("Choisir le statut de reclamation a chercher : \n");
    printf("1. En cours\n");
    printf("2. Resolue\n");
    printf("3. Fermee\n");
    int choix;
    scanf("%d", &choix);
    getchar();

    switch(choix) {
        case 1: 
            strcpy(status_chercher, "en cours");
            break;
        case 2:
            strcpy(status_chercher, "resolue");
            break;
        case 3:
            strcpy(status_chercher, "fermee"); 
            break;
        default: 
            printf("Choix invalide.\n");
            return;
    }

    int found = 0;
    for (int i = 0; i < reclamation_count; i++) {
        if (strcmp(status_chercher, reclamations[i].status) == 0) {
            printf("*********************************************\n");
            printf("client : %s\n", users[reclamations[i].ID].nom);
            printf("User ID: %d\n", reclamations[i].user_identifiant);
            printf("Motif : %s\n", reclamations[i].motif);
            printf("Categorie : %s\n", reclamations[i].categorie);
            printf("Description : %s\n", reclamations[i].description);
            printf("Statut : %s\n", reclamations[i].status);
            printf("Date : %s\n", reclamations[i].date);
            printf("*********************************************\n");
            found = 1;
        }
    }
    if (!found) {
        printf("Pas de reclamation avec ce statut.\n");
    }
}

// Admin menu
void admin_menu() {
    int choix_admin;
    do {
        printf("\n========== Menu Admin ==========\n");
        printf("1. Changer le role d'un utilisateur\n");
        printf("2. Afficher la liste des utilisateurs\n");
        printf("3. Afficher la liste des reclamations\n");
        printf("4. Modifier des reclamations\n");
        printf("5. Supprimer reclamation\n");
        printf("6. Traitement des reclamations\n");
        printf("7. Chercher reclamation\n");
        printf("8. Afficher reclamations par priorite\n");
        printf("0. Revenir au menu principal\n");
        printf("Choisir l'operation : ");
        scanf("%d", &choix_admin);
        getchar();

        switch (choix_admin) {
            case 1:
                gerer_role();
                break;
            case 2:
                list_users();
                break;
            case 3:
                afficher_reclamation();
                break;
            case 4:
                modifier_reclamation();
                break;
            case 5: 
                supprimer_reclamation();
                break;
            case 6:
                traiter_reclamation();
                break;
            case 7:
                chercher_reclamation();
                break;
            case 8:
                afficher_par_priorite();
                break;
            case 0: break;
            default: printf("Choix invalide!\n");
                break;
        }
    } while (choix_admin != 0);
}

// Agent menu
void agent_menu() {
    int choix_agent;
    do {
        printf("\n========== Menu Agent ==========\n");
        printf("1. Afficher toutes les reclamations\n");
        printf("2. Modifier reclamation\n");
        printf("3. Supprimer une reclamation\n");
        printf("4. Traitement des reclamations\n");
        printf("5. Chercher reclamation\n");
        printf("0. Deconnexion\n");
        printf("Veuillez entrer votre choix : ");
        scanf("%d", &choix_agent);
        getchar();

        switch (choix_agent) {
            case 1: afficher_reclamation();
                 break;
            case 2: modifier_reclamation();
                break;
            case 3: supprimer_reclamation();
                break;
            case 4: traiter_reclamation();
                break;
            case 5: chercher_reclamation();
                break;
            case 0: break;
            default: printf("Choix invalide. Essayez a nouveau\n"); break;
        }
    } while (choix_agent != 0);
}

// Client menu
void client_menu() {
    int client_option;
    do {
        printf("\n========== Menu Client ==========\n");
        printf("1. Ajouter une reclamation\n");
        printf("2. Modifier une reclamation\n");
        printf("3. Supprimer une reclamation\n");
        printf("0. Quitter menu\n");
        printf("Veuillez saisir votre choix : ");
        scanf("%d", &client_option);
        getchar();

        switch (client_option) {
            case 1: creer_reclamation();
                break;
            case 2: modifier_reclamation_client();
                break;
            case 3: supprimer_reclamation();
                break;
            case 0: break;
            default: printf("Choix invalide!\n");
                break;
        }
    } while (client_option != 0);
}

int main() {
    int choix;
    admin();  // initialiser admin

    do {
        printf("\n===== Bienvenue sur votre application de gestion des reclamations =======\n");
        printf("1. Nouveau client\n");
        printf("2. Se connecter\n");
        printf("0. Quitter\n");
        printf("============================================================================\n");
        printf("Entrer votre choix : ");
        scanf("%d", &choix);
        getchar();

        switch (choix) {
            case 1: creer_compte();
                break;
            case 2: connecter_vous();
                break;
            case 0: printf("Au revoir!\n");
                break;
            default: printf("Choix non valide!\n");
                break;
        }
    } while (choix != 0);
    system("pause");

    return 0;
}