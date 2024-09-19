#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int pass_check(char pass[]);

typedef struct{
    int identifiant;
    char nom[30];
    char prenom[30];
    char phone[11];
    char password[40];
}User;
User users[100];
int user_count = 0;
int id = 0;


void user_compte(){
    char pass[40];
    printf("\nEntrer les informations suivantes :\n");

    printf("Nom : ");
    fgets(users[user_count].nom,30, stdin);
    users[user_count].nom[strcspn(users[user_count].nom, "\n")] = '\0';

    printf("Prenom : ");
    fgets(users[user_count].prenom,30, stdin);
    users[user_count].prenom[strcspn(users[user_count].prenom, "\n")] = '\0';

    printf("Entrer a valide mobile : ");
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
    users[user_count].identifiant = user_count;
   
}
int pass_check(char pass[]){
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




int main(){
    int option;
    
    do{
        printf("\t\nMenu : \n");
        printf("1. Gestion des utilisateurs.\n");
        printf("2. Gestion des reclamations.\n");
        printf("3. Statistiques et Rapports\n");
        printf("\tEntrer votre choix : ");
        scanf("%d", &option);
        getchar();
        switch(option){
            case 1:
                user_compte();
                
                break;
        }

    }while(option != 6);
    system("pause");
    return 0;
}