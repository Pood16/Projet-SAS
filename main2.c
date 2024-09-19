#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//structure d'un admin
typedef struct{
    char nom[40];
    int identifiant;
    char mot_de_passe[40];

}Admin;
Admin admin = {"LAHCEN", 0, "Lahcen@admin.123"};
//structure pour grouper les clients
typedef struct{
    int identifiant;
    char nom[30];
    char prenom[30];
    char phone[11];
    char password[40];
}User;
User users[100];
int user_count = 0;

//fonction d'iinscription
void sign_up(){
    char pass[40];

    printf("\nEntrer les informations suivantes :\n");
    printf("Nom : ");
    fgets(users[user_count].nom,30, stdin);
    users[user_count].nom[strcspn(users[user_count].nom, "\n")] = '\0';

    printf("Prenom : ");
    fgets(users[user_count].prenom,30, stdin);
    users[user_count].prenom[strcspn(users[user_count].prenom, "\n")] = '\0';

    printf("mobile phone : ");
    scanf("%d", &users[user_count].phone);
    getchar();
    while(1){
        printf("password : ");
        fgets(pass,40, stdin);
        int status = pass_check(pass);
        if (status == 0){
            strcpy(users[user_count].password, pass);
            printf("Compte est crrer avec succes.\n");
            break;
        }
        else {
            printf("password doit contenir au moins 8 caracteres : Un caractere majuscule, miniscule et caractere special (par exemple : !@#$%^&*)\n");
            printf("Respecter la formule de mot de passe et essayer autre fois : \n");
        }

    }
    user_count++;
    users[user_count].identifiant = user_count; //admin = 0 
    printf("your identifiant est %d\n", users[user_count].identifiant);
}
//verifier les contraintes de mots de passe
int pass_check(char pass[]){//les contraintes de mot de passe
    int majuscule = 0, miniscule = 0, chiffre = 0, speciale = 0;
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
        //strcpy(users[user_count].password, pass);
        return 0;
    }
    else{
        
        return 1;
    }

}
//Fonction de connexion
void sign_in(){
    int id;
    char pass[40];
    int tentative=0;
    printf("Entrer les informations suivantes : \n");
    while(1){
        printf("Identifiant : ");
        scanf("%d", &id);
        getchar();
        printf("mot de passe : ");
        fgets(pass, 40, stdin);
        pass[strcspn(pass, "\n")] = '\0';
        for (int i=0; i<user_count; i++){
            if (users[i].identifiant == id && strcmp(users[i].password, pass) == 0){
                printf("sign in successfully\n");
                break;
            }
            else{
                printf("Verifier vos informations.\n");
                break;
            }
        }
    }
    

}
/* declaration des fonctions*/
void admin_tache();
void agent_reclamation();
void client();
void sign_in();
void sign_up();
int pass_check(char pass[]);
/* Fin declaration des Fonctions*/




/*les taches possibles pour un admin */
void admin_tache(){
    int status;
    system("@cls");
    printf("Choisit l'opperation : ");
    scanf("%d", &status);
    do{
        printf("Bienvenue : \n");
        printf("1.  Afficher La list des reclamations.\n");
        printf("2.  Modifier une reclamation.\n");
        printf("3.  supprimer une reclamation.\n");
        printf("4.  Traiter une reclamation.\n");
        printf("5.  Rechercher une reclamation.\n");
        printf("6.  Afficher les reclamations par priorite.\n");
        printf("7.  Afficher le nombre total de reclamations.\n");
        printf("8.  Afficher le taux de resolution des reclamations.\n");
        printf("9.  Le delai de Traitement des reclamations.\n");
    }while (status != 0);
    
}
/* partie d'agent de reclamation */
void agent_reclamation(){
    printf("test\n");
}
/* partie de client*/
void client(){
    printf("\nBienvenue.\n\n");
    int status_client;
        printf("1.  inscription.\n");
        printf("2.  connextion.\n");
        printf("choix d'opperation : ");
        scanf("%d", &status_client);
        getchar();
        if (status_client == 1){
            sign_up();
        }
        if(status_client == 2){
            sign_in();
        }  
}

int main(){
    int option;
    do{
        printf("\tBienvenue : \n");
        printf("Vous etes : \n");
        printf("1.  Administrateur.\n");
        printf("2.  Agent de Reclamation.\n");
        printf("3.  Client.\n");
        printf("0.  pour quitter le programme.\n");
        printf("Choisit votre role : ");
        scanf("%d", &option);
        getchar();
        switch(option){
            case 1: 
                admin_tache();
                break;
            case 2:
                agent_reclamation();
                break;
            case 3:
                client();
                break;
            case 4:
                break;
            default:
                printf("Le choix n'existe plus.");
                break;
        }
    }while(option != 0);
    return 0;
}