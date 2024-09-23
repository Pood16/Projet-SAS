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
int recherche_date();
void recherche_status();
void recherche_nom();
void recherche_identifiant();
//void menu_gestion();
//global variables et initialisation
int user_count = 1;
int reclamation_count = 0;
//user structure
typedef struct {
    char nom[50];
    int role;
    char password[50];
    int identifiant;
}User;
User users[MAX_USERS];
//Creer un admin
void admin(){
    strcpy(users[0].nom, "admin");
    users[0].role=0;
    strcpy(users[0].password, "Admin@2024");
    users[0].identifiant = 0;
}
//structure des reclamations
typedef struct{
    int ID;
    int user_identifiant;
    char motif[30];
    char description[200];
    char categorie[30];
    char status[30];
    char date[30];
    time_t datE;
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
    printf("nom : ");
    fgets(client.nom, 50, stdin);
    client.nom[strcspn(client.nom, "\n")] = '\0';
    while(1){
        //saisir le mot de passe de client
        printf("password : ");
        fgets(client.password, 50, stdin);
        client.password[strcspn(client.password, "\n")] = '\0';
        //Verifier si le mot de passe recpecte les conditions
        int status = password_check(client.password, client.nom);
        if (status){
            valid = 1;
            break;
        }
        else {
            printf("\n........... Attention : \n");
            printf("Le mot de passe doit contenir au moins 8 caracteres : \n");
            printf("Un caractere majuscule, minuscule, chiffre et un caractere special (par exemple : !@#$^&*)\n");
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
        printf("3 tentatives de connexion echouees. Veuillez ressayer apres 10 secondes.\n");
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
        printf("nom  : %s\n", users[i].nom);
        printf("user identifiant : %d\n", users[i].identifiant);
        printf("user role : %d\n", users[i].role);
        printf("mot de passe : %s\n", users[i].password);
        printf("***************************************\n");
    }
    }
    
}
//Partie 2 : Fonctions de gestions des Reclamations
int nouveau_reclamation = 1;
void creer_reclamation(){
    if (reclamation_count > MAX_RECLAMATION){
        printf("impossible de creer une reclamation pour le moment.\n");
    }
    else {
        strcpy(reclamations[reclamation_count].status, "en cours");
        reclamations[reclamation_count].ID = nouveau_reclamation;
        printf("Entrer votre identifiat : ");
        scanf("%d", &reclamations[reclamation_count].user_identifiant);
        getchar();
        printf("motif : ");
        fgets(reclamations[reclamation_count].motif, 30, stdin);
        reclamations[reclamation_count].motif[strcspn(reclamations[reclamation_count].motif, "\n")] = '\0';
        printf("description : ");
        fgets(reclamations[reclamation_count].description, 200, stdin);
        reclamations[reclamation_count].description[strcspn(reclamations[reclamation_count].description, "\n")] = '\0';
        printf("categorie : ");
        fgets(reclamations[reclamation_count].categorie, 30, stdin);
        reclamations[reclamation_count].categorie[strcspn(reclamations[reclamation_count].categorie, "\n")] = '\0';
        time_t Date = time(NULL);
        reclamations[reclamation_count].datE = time(NULL);
        strcpy(reclamations[reclamation_count].date, ctime(&Date));
        printf("reclamation numero %d a ete bien creer avec un ID %d.\n", nouveau_reclamation, nouveau_reclamation);
        nouveau_reclamation++;
        reclamation_count++;
    }
}
void afficher_reclamation(){
    if (reclamation_count == 0){
        printf("pas de  reclamation!\n");
    }
    else{
            int index_identifiant;
            printf("*********************\n");
            printf("    >>      liste des reclamations : \n");
            for (int i=0; i<reclamation_count; i++){
                for (int j=0; j<user_count; j++){
                    if (reclamations[i].user_identifiant == users[j].identifiant){
                        index_identifiant = j;
                        break;
                    }
                }
                printf("client : %s\n", users[index_identifiant].nom);
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
    time_t modification_time = time(NULL);
    int id_reclamation;
    int index_reclamation = -1;
    //verifier si la reclamation existe
    if (reclamation_count == 0){
        printf("opperation impossible : Pas de reclamation.\n");
        //return;
    }
    //chercher la position de reclamation
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
    if(index_reclamation < 0 || index_reclamation > reclamation_count){
        printf("reclamation avec cet ID n'existe pas pour le moment.\n");
        return;
    }
    else if (users[index_reclamation].role == 0 || users[index_reclamation].role == 1 || users[index_reclamation].role == 2 && (reclamations[index_reclamation].ID == users[index_reclamation].identifiant && difftime(modification_time, reclamations[index_reclamation].datE) < 24 * 3600)){
           printf("*************************************************\n");
           printf("nouveau motif : ");
           fgets(reclamations[index_reclamation].motif, 30, stdin);
           reclamations[index_reclamation].motif[strcspn(reclamations[index_reclamation].motif, "\n")] = '\0';
           printf("nouveau description : ");
           fgets(reclamations[index_reclamation].description, 200, stdin);
           reclamations[index_reclamation].description[strcspn(reclamations[index_reclamation].description, "\n")] = '\0';
           printf("categorie : ");
           fgets(reclamations[index_reclamation].categorie, 30, stdin);
           reclamations[index_reclamation].categorie[strcspn(reclamations[index_reclamation].categorie, "\n")] = '\0';
           printf("Reclamtion est bien modifier.\n");
        }
    else {
        printf("Impossible de modifier cette reclamation.\n");
        return;
    }
}
void supprimer_reclamation(){
    int id_spprimer;
    int index_supprimer;
    printf("Entrer ID de reclamtion a supprimer : ");
    scanf("%d", &id_spprimer);
    for (int i=0; i<reclamation_count; i++){
        if (id_spprimer == reclamations[i].ID){
            index_supprimer = i;
        }
    }
    if(index_supprimer < 0 || index_supprimer > reclamation_count){
        printf("reclamation avec cet ID n'existe pas pour le moment.\n");
        return;
    }
    else if (users[index_supprimer].role == 0 || users[index_supprimer].role == 1 || (users[index_supprimer].role == 2 && (reclamations[index_supprimer].ID == users[index_supprimer].identifiant))){
        for (int i= index_supprimer; i<reclamation_count -1 ; i++){
            reclamations[i] = reclamations[i+1];
        }
        reclamation_count--;
        printf("Reclamation est bien supprimer.\n");
    }
    else {
        printf("Impossible de supprimer cette reclamation.\n");
        return;
    }
    
}
int status_traiter_counter = 0;
void traiter_reclamation(){
    int id_traiter;
    if (reclamation_count == 0){
        printf("Pas de reclamation a traiter.\n");
        return;
    }
    printf("Entrer ID de reclamation a traiter : ");
    scanf("%d", &id_traiter);
    getchar();
    int index_traiter = -1;
    for (int i=0; i<reclamation_count; i++){
        if(reclamations[i].user_identifiant == id_traiter){
            index_traiter = i;
            break;
        }
    }
    if(index_traiter == -1){
        printf("Reclamation a traiter n'existe pas.!\n");
    }
    else {
        printf("choisit le nouveau status : \n");
        printf("    en cours.\n");
        printf("    resolue.\n");
        printf("    fermee.\n");
        fgets(reclamations[index_traiter].status, 30, stdin);
        reclamations[index_traiter].status[strcspn(reclamations[index_traiter].status, "\n")] = '\0';
        printf("status et bien traiter.\n");
        status_traiter_counter++;
    } 
}
void chercher_reclamation(){
    int type_recherche;
    printf("Entrer la methode de recherche d'un reclamation : \n");
    printf("[1].    cherche par ID.\n");
    printf("[2].    cherche par nom.\n");
    printf("[3].    cherche par status.\n");
    printf("[4].    chercher par date/\n");
    printf("Entrer le nombre de votre choix : ");
    scanf("%d", &type_recherche);
    getchar();
    switch(type_recherche){
   
        case 1:
            recherche_identifiant();
            break;
        case 2:
            recherche_nom();
            break;
        case 3:
            recherche_status();
            break;
        

        case 0:
            break;
        default :
            printf("choix invalide!\n");
    }
}
void recherche_identifiant(){
    int indice;
    int indice_chercher = -1;
    printf("Entrer ID du reclamation chercher : ");
    scanf("%d", &indice);
    getchar();
    // if( indice > nouveau_reclamation){
    //     printf("Pas de reclamation avec cette ID.\n");
    // }
    // else {
    //     for (int i=0; i<reclamation_count; i++){
    //         if(indice == reclamations[i].ID){
    //             indice_chercher = i;
    //         }
    //     }

    
        for (int i=0; i<reclamation_count; i++){
            if(indice == reclamations[i].ID){
                indice_chercher = i;
            }
        }

    if (indice_chercher == -1){
        printf("Pas de reclamation avec cette ID.\n");
    }
    else {
        for (int i=0; i<reclamation_count; i++){
            if(reclamations[i].user_identifiant == users[indice_chercher].identifiant){
                printf("*********************************************\n");
                printf("Reclamation rechercher : \n");
                printf("client : %s\n", users[indice_chercher].nom);
                printf("reclamation ID: %d\n", reclamations[i].ID);
                printf("motif : %s\n", reclamations[i].motif);
                printf("categorie : %s\n", reclamations[i].categorie);
                printf("Description : %s\n", reclamations[i].description);
                printf("status de reclamation : %s\n", reclamations[i].status);
                printf("date : %s\n",reclamations[i].date );
                printf("*********************************************\n");
            }
        }
    }
}
void recherche_nom(){
    char client_nom[30];
    int client_indice = -1;
    printf("Entrer le nom de client : ");
    fgets(client_nom, 30, stdin);
    client_nom[strcspn(client_nom, "\n")] = '\0';
    for (int i=0; i<user_count; i++){
        if(strcmp(client_nom, users[i].nom) == 0){
            client_indice = i;
        }
    }
    if(client_indice == -1){
        printf("Pas de recla,ation avec cette nom.\n");
    }
    else {
         for (int i=0; i<reclamation_count; i++){
            if(reclamations[i].user_identifiant == users[client_indice].identifiant){
                printf("*********************************************\n");
                printf("Reclamation rechercher : \n");
                printf("client : %s\n", users[client_indice].nom);
                printf("reclamation ID: %d\n", reclamations[i].ID);
                printf("motif : %s\n", reclamations[i].motif);
                printf("categorie : %s\n", reclamations[i].categorie);
                printf("Description : %s\n", reclamations[i].description);
                printf("status de reclamation : %s\n", reclamations[i].status);
                printf("date : %s\n",reclamations[i].date );
                printf("*********************************************\n");
        
        }
        
    }
    }  
}
void recherche_status(){
    char status_chercher[20];
    printf("Choisit status de reclamation chercher : \n");
    printf("en cours\n");
    printf("rejete\n");
    printf("resolue\n");
    fgets(status_chercher, 20, stdin);
    status_chercher[strcspn(status_chercher, "\n")] = '\0';
    for (int i=0; i<reclamation_count; i++){
        if(strcmp(status_chercher, reclamations[i].status) == 0){
            printf("\n");
            //zid le nom mais apres modification de fonction de recherche par id
            printf("reclamation ID: %d\n", reclamations[i].ID);
            printf("motif : %s\n", reclamations[i].motif);
            printf("categorie : %s\n", reclamations[i].categorie);
            printf("Description : %s\n", reclamations[i].description);
            printf("status de reclamation : %s\n", reclamations[i].status);
            printf("date : %s\n",reclamations[i].date );
        }
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
        printf("5.  supprimer reclamation.\n");
        printf("6.  traitement des reclamations.\n");
        //test
        printf("7.  chercher reclamation.\n");
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
            case 5:
                supprimer_reclamation();
                break;
            case 6:
                traiter_reclamation();
                break;
            case 7:
                chercher_reclamation();
                break;
            case 0:
                break;
            default:
                printf("choix invalide!\n");
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
        printf("2. Modifier reclamation\n");
        printf("3. Supprimer une reclamation.\n");
        printf("4. traitement des reclamations.\n");
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
            case 3:
                supprimer_reclamation();
                break;
            case 4:
                traiter_reclamation();
                break;
            case 0:
                break;
            default:
                printf("invalid choice. essayer a nouveau\n");
                break;
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
            case 3: 
                supprimer_reclamation();
                break;
            case 0:
                break; 
            default :
                printf("choix invalide!\n");
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