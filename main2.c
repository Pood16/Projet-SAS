#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <time.h>
#define MAX_USERS 100
#define MAX_RECLAMATION 100
//declaration des fonctions
void admin();
void creer_compte();
int password_check(char pass[], char name[]);
void admin_menu();
void agent_menu();
void client_menu();
int user_role(int index);
void menu_role(int userIndex);
//void menu_gestion();
//global variables et initialisation
int user_count = 1;
int reclamation_count = 0;
//user structure
typedef struct {
    char fullName[50];
    int role;
    char password[50];
    int identifiant;
}User;
User users[MAX_USERS];
//Creer un admin
void admin(){
    strcpy(users[0].fullName, "admin");
    users[0].role=0;
    strcpy(users[0].password, "Admin@2024");
    users[0].identifiant = 0;
}
//structure des reclamations
typedef struct{
    int ID;
    char motif[30];
    char description[200];
    char categorie[30];
    char status[30];
    char date[30];
}Reclamation;
Reclamation reclamations[MAX_RECLAMATION];
//creer un compte
void creer_compte(){
    //verifier qu il ya encore d'espace
    if (user_count > MAX_USERS){
        printf("impossible de creer le compte!\n");
        printf("Le maximum des clienrs est atteinte.\n");
    }
    User client;
    int valid = 0;
    client.role = 2;
    client.identifiant = user_count;
    printf("Entrer les informations suivantes : \n");
    //saisir le nom complet de client
    printf("nom et prenom : ");
    fgets(client.fullName, 50, stdin);
    client.fullName[strcspn(client.fullName, "\n")] = '\0';
    while(1){
        //saisir le mot de passe de client
        printf("password : ");
        fgets(client.password, 50, stdin);
        client.password[strcspn(client.password, "\n")] = '\0';
        //Verifier si le mot de passe recpecte les conditions
        int status = password_check(client.password, client.fullName);
        if (status){
            valid = 1;
            break;
        }
        else {
            printf("\n........... Attention : \n");
            printf("Le mot de passe doit contenir au moins 8 caracteres : \n");
            printf("Un caractere majuscule, minuscule, chiffre et un caractere special (par exemple : !@#$%^&*)\n");
            printf("Il ne doit pas contenir votre nom.\n");
            printf("Veuillez essayer a nouveau.\n");
            printf("....................................\n");
        }

    }
    if (valid){
        users[user_count] = client;
        printf("Compte est creer avec l'identifiant : %d\n", user_count);
        // test
        // printf("identifiant : %d\n", users[user_count].identifiant);
        // printf("password : %s\n", users[user_count].password);
        // printf("role : %d\n", users[user_count].role);
        // fin test
        user_count++;
    }
}
//verifier le mot de passe
int password_check(char pass[], char name[]){
    int majiscule, miniscule, chiffre, caractere;
    majiscule = miniscule = chiffre = caractere = 0;
    if (strlen(pass) < 8){
        return 0;
    }
    if (strstr(pass, name) != NULL){
        return 0;
    }
    for (int i=0; i<strlen(pass); i++){
        if (pass[i] >= 'A' && pass[i] <= 'Z') {
                majiscule = 1;    
        }
        else if (pass[i] >= 'a' && pass[i] <= 'z') {
                miniscule = 1;
        }
        else if ((pass[i] >= 33 && pass[i] <= 47) || (pass[i] >= 58 && pass[i] <= 64) || (pass[i] >= 91 && pass[i] <= 96) || (pass[i] >= 123 && pass[i] <= 126)) {
                caractere = 1;
        } 
        else if (pass[i] >= '0' && pass[i] <= '9') {  // Fix for digit
                chiffre = 1;
        }         
    }
    if (majiscule && miniscule && caractere && chiffre){
        return 1;
    }
}
//Fonction de connexion
void connecter_vous() {
    char pass[50];
    int id, index = -1, exist = 0, tentative = 0;
    while (tentative < 3) {  
        printf("identifiant : ");
        scanf("%d", &id);
        getchar();  
        printf("mot de passe : ");
        fgets(pass, 50, stdin);
        pass[strcspn(pass, "\n")] = '\0';  
        for (int i = 0; i < user_count; i++) {
            if (users[i].identifiant == id && strcmp(pass, users[i].password) == 0) {
                exist = 1;
                index = i;
                break;  
            }
        }
        if (exist) {
            menu_role(users[index].role);
            return;  
        } else {
            tentative++;  
            printf("Identifiant ou mot de passe incorrect. Tentatives restantes : %d\n", 3 - tentative);
        }
    }
    if (tentative == 3) {
        printf("3 tentatives de connexion échouées. Veuillez réessayer après 10 secondes.\n");
        sleep(10);  
    }
    connecter_vous();  
}

//fonction pour determiner le role de l'utilisateur
int user_role(int userIndex){
    if (users[userIndex].role == 0){
        return 0;//admine
    }
    if (users[userIndex].role == 1){
        return 1;//agent de reclamation
    }
    if (users[userIndex].role == 2){
        return 2;//client
    }
}
void menu_role(int userIndex){
    if (userIndex == 0){
        admin_menu();
    }
    else if (userIndex == 1){
        agent_menu();
    }
    else if (userIndex == 2){
        client_menu();
    }
}
void gerer_role(){
    int id, newRole;
    printf("Entrer l'identifiant de l'utilisateur a modifier : ");
    scanf("%d", &id);
    printf("Entrer le nouveau role pour cet utilisateur :\n");
    printf("0 pour un admin.\n");
    printf("1 pour un agent des reclamations.\n");
    printf("2 pour un client.\n");
    scanf("%d", &newRole);
    for (int i=0; i<user_count; i++){
        if (users[i].identifiant == id){
            users[i].role = newRole;
        }
    }
    printf("Le role est bien changer.\n");
}
void list_users(){
    if (user_count == 0){
        printf("Pas d'utilisateurs!.\n");
    }
    else {
        printf("======= Liste des utilisateurs : \n");
        for (int i=0; i<user_count; i++){
        printf("***************************************\n");
        printf("informations de l'utilisateur %d : \n", i+1);
        printf("nom complet : %s\n", users[i].fullName);
        printf("user identifiant : %d\n", users[i].identifiant);
        printf("user role : %d\n", users[i].role);
        printf("mot de passe : %s\n", users[i].password);
        printf("***************************************\n");
    }
    }
    
}
//Partie 2 : Fonctions de gestions des Reclamations
void creer_reclamation(){
    if (reclamation_count > MAX_RECLAMATION){
        printf("impossible de creer une reclamation pour le moment.\n");
    }
    else {
        strcpy(reclamations[reclamation_count].status, "en cours");
        reclamations[reclamation_count].ID = reclamation_count + 1;
        printf("motif : ");
        fgets(reclamations[reclamation_count].motif, 30, stdin);
        reclamations[reclamation_count].motif[strcspn(reclamations[reclamation_count].motif, "\n")] = '\0';
        printf("description : ");
        fgets(reclamations[reclamation_count].description, 200, stdin);
        reclamations[reclamation_count].description[strcspn(reclamations[reclamation_count].description, "\n")] = '\0';
        printf("categorie : ");
        fgets(reclamations[reclamation_count].categorie, 30, stdin);
        reclamations[reclamation_count].categorie[strcspn(reclamations[reclamation_count].categorie, "\n")] = '\0';
        time_t date = time(NULL);
        strcpy(reclamations[reclamation_count].date, ctime(&date));
        printf("reclamation numero %d a ete bien creer avec un ID %d.\n", reclamation_count + 1, reclamations[reclamation_count].ID);
        reclamation_count++;
    }
}
void afficher_reclamation(){
    if (reclamation_count == 0){
        printf("pas de  reclamation!\n");
    }
    else {
        printf(" ==== liste des reclamations : \n");
        for (int i=0; i<reclamation_count; i++){
        printf("client : %s\n", users[i+1].fullName);
        printf("reclamation ID: %d\n", reclamations[i].ID);
        printf("motif : %s\n", reclamations[i].motif);
        printf("categorie : %s\n", reclamations[i].categorie);
        printf("Description : %s\n", reclamations[i].description);
        printf("status de reclamation : %s\n", reclamations[i].status);
        printf("date : %s\n",reclamations[i].date );
    }
    }
    
}
void modifier_reclamation(){
    int id_reclamation;
    int index_reclamation;
    //verifier si la reclamation existe
    if (reclamation_count == 0){
        printf("opperation impossible : Pas de reclamation.\n");
        return;
    }
    //cherche la position de reclamation
    printf("Entrer  ID de reclamation a modifier : ");
    scanf("%d", &id_reclamation);
    getchar();
    for (int i=0; i<reclamation_count; i++){
        if (id_reclamation == reclamations[i].ID){
            index_reclamation = i;
            break;
        }
    }
    //exit si la reclamation n'existe pas
    if (index_reclamation == -1){
        printf("Pas de reclamation avec cet ID.\n");
        return;
    }
    if (users[index_reclamation].role == 0 || users[index_reclamation].role == 1 || users[index_reclamation].role == 2 && (reclamations[index_reclamation].ID == users[index_reclamation].identifiant)){
           printf("nouveau motif : ");
           fgets(reclamations[index_reclamation].motif, 30, stdin);
           reclamations[index_reclamation].motif[strcspn(reclamations[index_reclamation].motif, "\n")] = '\0';
           printf("nouveau description : ");
           fgets(reclamations[index_reclamation].description, 200, stdin);
           reclamations[index_reclamation].description[strcspn(reclamations[index_reclamation].description, "\n")] = '\0';
           printf("categorie : ");
           fgets(reclamations[index_reclamation].categorie, 30, stdin);
           reclamations[index_reclamation].description[strcspn(reclamations[index_reclamation].description, "\n")] = '\0';
           printf("Reclamtion est bien modifier.\n");
        }
}
//admin menu
void admin_menu(){
    int choix_admin;
    do{
        printf("\n========== Admin menu ==========\n");
        printf("1.  Changer le role d'un utilisateur.\n");
        printf("2.  afficher la liste des utilisateurs.\n");
        printf("3.  afficher liste des reclamations.\n");
        printf("4.  modifier des reclamations.\n");
        printf("0.  Revenue au menu principale.\n");
        printf("Choisit l'opperation : ");
        scanf("%d", &choix_admin);
        getchar();
        switch (choix_admin){
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
            case 0:
                break;
        }
    }while (choix_admin != 0);

}
//agent de reclamation menu
void agent_menu(){
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
                afficher_reclamation();
                break;
            case 2:
                modifier_reclamation();
                break;
            case 0:
                break;
            default:
                printf("invalid choice. essayer a nouveau\n");
        }
    } while (choix_agent != 0);
}
//menu de client
void client_menu() {
    int client_option;
    do {
        printf("\n========== Client menu ==========\n");
        printf("[1].    Ajouter une reclamation.\n");
        printf("[2].    Modifier une reclamation.\n");
        printf("[3].    Supprimer une reclamation.\n");
        printf("[0].    Quiter menu.\n");
        printf("veillez saisir votre choix: ");
        scanf("%d", &client_option);
        getchar();
        switch (client_option) {
            case 1:
                creer_reclamation();
                break;
            case 2:
                modifier_reclamation();
                break;
        }
    } while (client_option != 0);
}

int main() {
    int choix;
    admin();  
    do {
        printf("\n===== Bienvenue Sur votre application de gestion de vos reclamations =======\n");
        printf("[1].    Nouveau client.\n");
        printf("[2].    Se connecter.\n");
        printf("[0].    Quitter.\n");
        printf("============================================================================\n");
        printf("Entrer votre choix : ");
        scanf("%d", &choix);
        getchar();  
        switch (choix) {
            case 1:
                creer_compte();
                break;
            case 2:
                connecter_vous();
                break;
            case 0:
                break;
            default:
                printf("Choix non valide!.\n");
                break;
        }
    } while (choix != 0);

    return 0;
}