#include <stdio.h>

int main(){
    int idade;
    scanf("%d", &idade);
    
    if(idade <= 11){
        printf("Criança");
    }

    else if((idade > 11) && (idade <= 17)){
        printf("Adolescente");
    }

    else if((idade > 17) && (idade <= 59)){
        printf("Adulto");
    }
    else{
        printf("Idoso");
    }
    return 0;
}