#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CLIENT 100
#define MAX_CHARACTER 50
/*...... les Fonctions .........*/
int password_check(char pass[]);
void admin_tache();
void client_tache();
/*......... end Fonction ..........*/
typedef struct {
    char nom[40];
    int identifiant;
    char password[40];
}Admin;
Admin admin = {"admin", 0000, "Admin@2024"};
//information dec lient
typedef struct{
    char nom[40];
    char prenom[40];
    int identifiant;
    char password[40];
}Client;
Client users[MAX_CLIENT];
int user_counter = 0;
/* ....................... Fonction de creation de compte ......................*/
void creer_compte(){
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
    printf("your identifiant est %d\n", users[user_counter].identifiant);
    user_counter++;
    printf(".....................................................\n");   
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
    int id;
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
        //check if the user is an admin
        if(id == admin.identifiant && strcmp(admin.password, pass) == 0){
            admin_tache();
            return;
        }
        for (int i=0; i<user_counter; i++){
            //printf("user id : %d and entred is %d\n", users[i].identifiant, id);
            if (users[i].identifiant == id && strcmp(users[i].password, pass) == 0){
                printf("sign in successfully\n");
                login = 1;
                //call client menu 
                break;
            }
            else {
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
/*................... admin menu .....................*/
void admin_tache(){
    int status;
    do{
        printf("Taches d'un Administrateur : \n");
        printf("1.  Afficher La list des reclamations.\n");
        printf("2.  Modifier une reclamation.\n");
        printf("3.  supprimer une reclamation.\n");
        printf("4.  Traiter une reclamation.\n");
        printf("5.  Rechercher une reclamation.\n");
        printf("6.  Afficher les reclamations par priorite.\n");
        printf("7.  Afficher le nombre total de reclamations.\n");
        printf("8.  Afficher le taux de resolution des reclamations.\n");
        printf("9.  Le delai de Traitement des reclamations.\n");
        printf("0.  Revenue au menu principale.\n");
        printf("Choisit l'opperation : ");
        scanf("%d", &status);
        getchar();
    }while (status != 0);
    
}
void client_tache(){
    int client_option;
    do {
        printf("[1].    Ajouter une reclamation.\n");
        printf("[2].    Modifier une reclamation.\n");
        printf("[3].    Supprimer une reclamation.\n");
        //completer le menu
    }while (client_option !=0);

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