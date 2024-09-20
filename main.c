#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_CLIENT 100
#define MAX_CHARACTER 50
#define MAX_RECLAMATION 300
/*...... les Fonctions .........*/
void role();
//void gestion_reclamation();
//void statistique();
int password_check(char pass[]);
void admin_tache();
void agent_de_reclamation_tache();
void client_tache();
void creer_reclamation();
void afficher_reclamation();
void modifier_reclamation();
void supprimer_reclamation();
/*......... end Fonction ..........*/
/*........... block dess structures ...........*/
typedef struct {
    char nom[40];
    int identifiant;
    char password[40];
    int admin_role;
}Admin;
Admin admin = {"admin", 0000, "Admin@2024", 0};
//information dec lient
typedef struct{
    char nom[40];
    char prenom[40];
    int identifiant;
    char password[40];
    int user_role;
}Client;

Client users[MAX_CLIENT];
int user_counter = 0;
//contenue de reclamation
typedef struct{
    int ID;
    char motif[40];
    char description[300];
    char _status[40];
    char categorie[40];
    char date[40];
}Reclamation;
Reclamation reclamations[MAX_RECLAMATION];

/*....................... end block des structores .............*/
/*............ Block de definition des Fonction ..................*/

/* ....................... Fonction de creation de compte ......................*/
void creer_compte(){
    Client rolle = {.user_role = 2};
    printf("\nEntrer les informations suivantes :\n");
    printf("Nom : ");
    fgets(users[user_counter].nom, 40, stdin);
    users[user_counter].nom[strcspn(users[user_counter].nom, "\n")] = '\0';

    printf("Prenom : ");
    fgets(users[user_counter].prenom,40, stdin);
    users[user_counter].prenom[strcspn(users[user_counter].prenom, "\n")] = '\0';

    

    while(1){
        char pass[40];
        printf("password : ");
        fgets(pass, 40, stdin);
        pass[strcspn(pass, "\n")] = '\0';
        int status = password_check(pass);
        if(status == 1){
            strcpy(users[user_counter].password, pass);
            users[user_counter].identifiant = user_counter; 
            printf("Compte est creer avec succes.\n");
            break;
        }
        else {
            printf("password doit contenir au moins 8 caracteres : Un caractere majuscule, miniscule et caractere special (par exemple : !@#$%^&*)\n");
            printf("Respecter la formule de mot de passe et essayer autre fois : \n");
        }   
    }
    printf("------> user identifiant : %d\n",users[user_counter].identifiant);
    user_counter++;  
}
/*........... attribue role ............*/
void role(){
    int iden, rol, found = 0;
    printf("Entrer l'identifiant de l'utilisateur : ");
    scanf("%d", &iden);
    printf("choisi le nouveau role: ");
    scanf("%d", &rol);//1 pour agent de recla et 2 pour client
    for (int i=0; i<user_counter; i++){
        if (users[i].identifiant == iden){
            found = 1;
            users[i].user_role = rol;
        }
    }
    if (found){
        printf("Le role a ete bien changer.\n");
    }

}
/*............................. verifier les contraintes de mots de passe ..............*/
int password_check(char pass[]){
    int majuscule = 0, miniscule = 0, chiffre = 0, speciale = 0;
    int verify = 0;
     if(strlen(pass)>=8){
        for (int i =0; i<strlen(pass); i++){
            if (pass[i]>=65 && pass[i]<=90){
                majuscule = 1;    
            }
            else if(pass[i]>=97 && pass[i]<= 122){
                miniscule = 1;
            }
            else if(pass[i] >= 33 && pass[i] <= 47 || pass[i] >= 58 && pass[i] <= 64 || pass[i] >= 91 && pass[i] <= 96 || pass[i] >= 123 && pass[i] <= 126){
                speciale = 1;
            }
            else {
                chiffre = 1;
            }
        }
    }
    if (majuscule && miniscule && chiffre && speciale){
        verify = 1;
    }
    return verify;
}
/*................... Fonction de connexion ..........................*/
void connecter(){
    int id, rolle;
    char pass[40];
    int tentative=0;
    int login = 0;
    printf("Entrer les informations suivantes : \n");
    while(1){
        printf("Identifiant : ");
        scanf("%d", &id);
        getchar();
        printf("mot de passe : ");
        fgets(pass, 40, stdin);
        pass[strcspn(pass, "\n")] = '\0';
        //getchar();
        //check if the user is an admin
        if(id == admin.identifiant && strcmp(admin.password, pass) == 0){
            admin_tache();
            return;
        }
        for (int i=0; i<user_counter; i++){
            printf("user id : %d and entred is %d\n", users[i].identifiant, id);
            if (users[i].identifiant == id && strcmp(users[i].password, pass) == 0 ){//&& users[i].user_role == 2
                client_tache();
                login = 1;
                break;
            }
            else if(users[i].identifiant == id && strcmp(users[i].password, pass) == 0 && users[i].user_role == 1){
                //printf("Bonjour %s\n", users[i].nom);
                agent_de_reclamation_tache();
                login = 1;
                break;
            }
            
            else{
                printf("mot de passe ou identifiant est incorrecte.\n");
                tentative++;   
            }
            }
            if (login) {
                return; // Exit the while loop after successful login
            }
            if(tentative == 3){
                printf("Essayer apres 30 minutes.\n");
                return;
            }
        
    }
}
int reclamation_counter = 0;

/* creation de reclamation......*/
void creer_reclamation() {
    printf("rempli les informations suivantes pour creer votre reclamation : \n");
    printf("Motif : ");
    fgets(reclamations[reclamation_counter].motif, 40, stdin);
    reclamations[reclamation_counter].motif[strcspn(reclamations[reclamation_counter].motif, "\n")] = '\0';

    printf("Categorie : ");
    fgets(reclamations[reclamation_counter].categorie, 40, stdin);
    reclamations[reclamation_counter].categorie[strcspn(reclamations[reclamation_counter].categorie, "\n")] = '\0';

    printf("Description : ");
    fgets(reclamations[reclamation_counter].description, 300, stdin);
    reclamations[reclamation_counter].description[strcspn(reclamations[reclamation_counter].description, "\n")] = '\0';

    printf("Status : ");
    fgets(reclamations[reclamation_counter]._status, 40, stdin);
    reclamations[reclamation_counter]._status[strcspn(reclamations[reclamation_counter]._status, "\n")] = '\0';

    time_t date = time(NULL);
    strcpy(reclamations[reclamation_counter].date, ctime(&date));
    reclamations[reclamation_counter].ID = reclamation_counter + 1;
 printf("reclamation a ete bien creer.\n");
    reclamation_counter++;
}
/*      afficher les reclamations existes   */
void afficher_reclamation() {
    for (int i = 0; i < reclamation_counter; i++) {
        printf("====== Reclamation %d ========\n", i + 1);
        printf("Motif : %s\n", reclamations[i].motif);
        printf("category : %s\n", reclamations[i].categorie);
        printf("Description : %s\n", reclamations[i].description);
        printf("status : %s\n", reclamations[i]._status);
        printf("date : %s",reclamations[i].date );
    }
}
/*........... Fonction de modification de reclamation .........*/




/*............... Creation des Menus ..................*/
/*................... admin menu .....................*/
void admin_tache(){
    int status;
    do{
        printf("\n========== Admin menu ==========\n");
        printf("1.  gestion des utilisateurs.\n");
        printf("2.  gestion des reclamations.\n");
        printf("3.  generation des statistiques.\n");
        printf("0.  Revenue au menu principale.\n");
        printf("Choisit l'opperation : ");
        scanf("%d", &status);
        getchar();
        switch (status){
            case 1:
                role();
                break;
            case 2:
                //gestion_reclamation();
                printf("1");
                break;
            case 3:
                //statistique();
                printf("2");
                break;
        }
    }while (status != 0);
    
}
/*....................... client menu ..............*/
void client_tache() {
    int client_option;
    do {
        printf("\n========== Client menu ==========\n");
        printf("[1].    Ajouter une reclamation.\n");
        printf("[2].    Modifier une reclamation.\n");
        printf("[3].    Supprimer une reclamation.\n");
        printf("veillez saisir votre choix: ");
        scanf("%d", &client_option);
        getchar();
        switch (client_option) {
            case 1:
                creer_reclamation();
                break;
            case 2:
                afficher_reclamation();
                break;
        }
    } while (client_option != 0);
}
/*............ agent de reclamation .........*/
void agent_de_reclamation_tache(){
    int choix_agent;
      do {
        printf("\n========== Agent Menu ==========\n");
        printf("1. Afficher toute les reclamations\n");
        printf("2. Traiter la reclamation\n");
        printf("0. deconnexion\n");
        printf("veuillez entrer votre choice: ");
        scanf("%d", &choix_agent);
        printf("\n*************************\n\n");
        getchar();

        switch (choix_agent) {
            case 1:
                printf("traitement");
                break;
            case 2:
                printf("traitement\n");
                break;
            case 0:
                printf("deconnexion ...\n");
                break;
            default:
                printf("invalid choice. essayer a nouveau\n");
        }
    } while (choix_agent != 0);
}


int main(){
    int choix;
    do{
        printf("===== Bienvenue Sur votre application de gestion de vos reclamations =======\n");
        printf("[1].    nouveau client.\n");
        printf("[2].    connecter.\n");
        printf("[0].    Quitter.\n");
        printf("============================================================================\n");
        printf("Entrer  votre choix : ");
        scanf("%d", &choix);
        getchar();
        switch(choix){
            case 1:
                creer_compte();
                break;
            case 2:
                connecter();
                break;
            case 3:
                break;
            default:
                printf("Le chix n'exist pas!.\n");
                break;
        }
    }while(choix != 0);
    return 0;
}