#include <iostream>
#include <string.h>
#include <stdlib.h>
#define TAM 5000

void zerarFrase(char *aux);
void zerarVetor(int *vetor);
char *lerDados();
char *dobrarMeta(char *palavra);
char *criptografaDados(char *palavra_pre_processada, int *vetorGlobalEnxerto, int *vetorGlobalNMaus, int *cont);
char *enxerto(char *palavra, int *vetorGlobalEnxerto, int *cont);
char *nMaus(char *palavra,  int *vetorGlobalNMaus, int *cont);
char *MaxLetra(char *palavra, int *cont);
char *descriptografia(char *palavra_criptografada, int *vetorGlobalEnxerto, int *vetorGlobalNMaus);
char *descriptografaEnxerto(char *palavra, int *vetorGlobalEnxerto, int *cont);
char *descriptografaNMaus(char *palavra, int *vetorGlobalNMaus, int *cont);
char *descriptografaMaxLetra(char *palavra);
char *voltarMeta(char *palavra_original_pre_processada);

int main(int argc, char** argv) {
	
	int *vetorGlobalEnxerto = (int*)malloc(TAM * sizeof(int));				// vetor pra armazenar todas as posições em que foi aplicado enxerto na string.
	int *vetorGlobalNMaus = (int*)malloc(TAM * sizeof(int));				// vetor pra armazenar todas as posições originais de nMaus na string.
	
	int cont = 0;
	
	zerarVetor(vetorGlobalEnxerto);
	zerarVetor(vetorGlobalNMaus);
	
	char *palavra = lerDados();
	char *palavra_pre_processada = dobrarMeta(palavra);
	
	
	
	printf("\nA string pre processada eh: %s \n", palavra_pre_processada);
	
	char *palavra_criptografada = criptografaDados(palavra_pre_processada, vetorGlobalEnxerto, vetorGlobalNMaus, &cont);
	
	printf("\nA string criptografada eh: %s \n", palavra_criptografada);

	char *palavra_original_pre_processada = descriptografia(palavra_criptografada, vetorGlobalEnxerto, vetorGlobalNMaus);
	
	printf("\nA string original pre processada eh: %s \n", palavra_original_pre_processada);
	
	char *palavra_original = voltarMeta(palavra_original_pre_processada);
	
	printf("\nA string original eh: %s \n\n", palavra_original);
	
	system("pause");
	return 0;
}

char* lerDados(){
	char *palavra = (char *)malloc(TAM * sizeof(char));
	zerarFrase(palavra);
	printf("\n Digite uma string: ");
	gets(palavra);
	return palavra;
}

char* dobrarMeta(char *palavra){
	
	int i,j=0;
	int tam = strlen(palavra);
	char *aux = (char*)malloc(TAM * sizeof(char));
	char *pre_processamento = (char*)malloc(TAM * sizeof(char));
	
	zerarFrase(aux);
	zerarFrase(pre_processamento);
	
	for(i = 0; i <= tam; i++){
		
		aux[j] = palavra[i];
		aux[j+1] = '\0';
		
		if((palavra[i+1]==' ')||(palavra[i+1]=='\0')){
			if(strcmp(aux,"meta") == 0){
				strcat(pre_processamento,"dobrarmeta");
				strcat(pre_processamento, " ");
				zerarFrase(aux);
				j=0;
				i++;
				
			}else{
				strcat(pre_processamento,aux);
				strcat(pre_processamento, " ");
				zerarFrase(aux);
				j=0;
				i++;
			}
		}else{
			j++;
		}
	}
	
	return pre_processamento;
}

void zerarFrase(char *aux){
	aux[0] = '\0'; 
}

void zerarVetor(int *vetor){
	int i;
	for(i = 0; i <= TAM; i++){
		vetor[i] = -1;
	} 
}

char *voltarMeta(char *palavra_original_pre_processada){
	
	int i,j=0;
	int tam = strlen(palavra_original_pre_processada);
	
	char *aux = (char*)malloc(TAM * sizeof(char));
	char *palavra_original = (char*)malloc(TAM * sizeof(char));
	
	zerarFrase(aux);
	zerarFrase(palavra_original);
	
	for(i = 0; i < tam; i++){
		
		aux[j] = palavra_original_pre_processada[i];
		aux[j+1] = '\0';
		
		if((palavra_original_pre_processada[i+1]==' ')||(palavra_original_pre_processada[i+1]=='\0')){
			
			if(strcmp(aux," dobrarmeta") == 0){
				
				strcat(palavra_original," meta");
				zerarFrase(aux);
				j=0;
				
			}else if(strcmp(aux,"dobrarmeta ") == 0){
				
				strcat(palavra_original,"meta ");
				zerarFrase(aux);
				j=0;
			
			}else if(strcmp(aux,"dobrarmeta") == 0){
				
				strcat(palavra_original,"meta");
				zerarFrase(aux);
				j=0;
			
			}else{
				
				strcat(palavra_original,aux);
				zerarFrase(aux);
				j=0;
			}
		}else{
			j++;
		}
	}
	
	strcat(palavra_original, " ");
	return palavra_original;
	
}

char *criptografaDados(char *palavra_pre_processada, int *vetorGlobalEnxerto, int *vetorGlobalNMaus, int *cont){
	
	int i,j=0;
	
	char *aux = (char*)malloc(TAM * sizeof(char));
	
	char *palavra_c = (char*)malloc(TAM * sizeof(char));
	
	int a = 1;
	int tam = strlen(palavra_pre_processada);
	
	zerarFrase(aux);
	zerarFrase(palavra_c);
	
	for(i = 0; i < tam; i++){
		
		aux[j] = palavra_pre_processada[i];
		aux[j+1] = '\0';

		if((palavra_pre_processada[i+1]==' ')||(palavra_pre_processada[i+1]=='\0')){
			if(a == 1){
						
				aux = enxerto(aux, vetorGlobalEnxerto, cont);
				strcat(palavra_c, aux);
				zerarFrase(aux);
				a++;
				j = 0;
				i++;
				
			} else if(a == 2){
				 
				aux = nMaus(aux, vetorGlobalNMaus, cont);
				strcat(palavra_c, aux);
				zerarFrase(aux);
				a++;
				j = 0;
				i++;
				
			} else if(a == 3){
				
				aux = MaxLetra(aux, cont);
				strcat(palavra_c, aux);
				zerarFrase(aux);
				a = 1;
				j = 0;
				i++;
			}
		}else{
			
			j++;
		}
	}
	
	return palavra_c;

}

char *enxerto(char *palavra, int *vetorGlobalEnxerto, int *cont){		
	
	int i;
	
	int tamV = strlen(palavra);									// mostra o tamanho da substring para saber quantas casas percorrer com cada letra.	
	
	char *aux = (char*)malloc(tamV * sizeof(char));				// vetor a ser preenchido com a palavra criptografado.
	zerarFrase(aux);
		
	int auxZ = 'z'- tamV; 										// criei esse parametro para saber quando a letra será z.
	
	for (i = 0; i < tamV ; i++){ 
	
		if (palavra[i] >= auxZ){
			aux[i] = 'z';										// inicio a posiçao do vetor com a letra z ja que ele so entra na condição sabendo q a letra sera maior que z.
			aux[i+1] = '\0';										
			vetorGlobalEnxerto[*cont] = 'z' - palavra[i]; 
			(*cont)++;
			
		}else{
			aux[i] = palavra[i] + tamV;				
			aux[i+1] = '\0';
			vetorGlobalEnxerto[*cont] = tamV;
			(*cont)++;
			}
			
		}
	
	strcat(aux, " ");
	(*cont)++;
	return aux;
	
}

char *nMaus(char *palavra, int *vetorGlobalNMaus, int *cont){
	
	int tam = strlen(palavra);
	
	char *aux = (char*)malloc(tam * sizeof(char));				/*tentei fazer utilizando apenas 1 vetor aux, mas estava me dando muitos erros de invasao de memoria e sobrava lixo no vetor*/
	char *aux6= (char*)malloc(tam * sizeof(char));
    char *aux9 = (char*)malloc(tam * sizeof(char));
    char *resto = (char*)malloc(tam * sizeof(char));
    
	zerarFrase(aux);
	zerarFrase(aux6);
	zerarFrase(aux9);
	zerarFrase(resto);
	
    int i;
    int i6=0, i9=0, ir=0;
    
     for (i=0; i<tam; i++){ 
        if (palavra[i] == '6'){        
            aux6[i6] = palavra[i];
            aux6[i6+1]= '\0';
            vetorGlobalNMaus[*cont] = 6;
            i6++;
            (*cont)++;
            
        }else if (palavra[i]=='9'){
            aux9 [i9] = palavra[i];
            aux9[i9+1]= '\0';
            vetorGlobalNMaus[*cont] = 9;
            i9++;
            (*cont)++;
            
        }else{
            resto[ir] = palavra[i];
            resto[ir+1] = '\0';
            vetorGlobalNMaus[*cont] = 1;
            ir++;
            (*cont)++;
        }
    }

        strcat(aux, aux6);
        strcat(aux, resto);
        strcat(aux, aux9);
    	strcat(aux, " "); 
    	(*cont)++;
    	
    return aux;
}

char *MaxLetra(char *palavra, int *cont){
	
	int tam = strlen(palavra);
	char *aux = (char*)malloc(tam * sizeof(char));
    zerarFrase(aux);
    int i, p; 
    
    char maior = palavra[0];
          
    for(i = 0; i < tam; i++){
        if(palavra[i] >= maior){
        	maior = palavra[i];
        }
	}
    p = 0;
    for(i = 0; i < tam; i++){
    	
        if(palavra[i] == maior){
            aux[p] = maior;
            aux[p+1] = maior;
            aux[p+2] = '\0';
            p+=2;
            (*cont)+=2;
            
        }else{
            aux[p] = palavra[i];
            aux[p+1] = '\0';
            p++;
            (*cont)++;
            
        }
	}
	
	strcat(aux, " ");
	(*cont)++; 
    return aux;
}

char *descriptografia(char *palavra_criptografada, int *vetorGlobalEnxerto, int *vetorGlobalNMaus){
	
	int cont = 0;
	
	char *aux = (char*)malloc(TAM * sizeof(char));
	char *palavra_original_pre_processada = (char*)malloc(TAM * sizeof(char));
	
	int a = 1;
	int i;
	int j = 0;
	int tam = strlen(palavra_criptografada);
	
	zerarFrase(aux);
	zerarFrase(palavra_original_pre_processada);
	
	for(i = 0; i < tam; i++){
		
		aux[j] = palavra_criptografada[i];
		aux[j+1] = '\0';
		
		if((palavra_criptografada[i+1]==' ')||(palavra_criptografada[i+1]=='\0')){
			
			if(a == 1){
						
				aux = descriptografaEnxerto(aux, vetorGlobalEnxerto, &cont);
				strcat(palavra_original_pre_processada, aux);
				zerarFrase(aux);
				a++;
				j = 0;
				i++;
				
			} else if(a == 2){
				
				aux = descriptografaNMaus(aux, vetorGlobalNMaus, &cont);
				strcat(palavra_original_pre_processada, aux);
				zerarFrase(aux);
				a++;
				j = 0;
				i++;
				
			} else if(a == 3){
				
				aux = descriptografaMaxLetra(aux);
				strcat(palavra_original_pre_processada, aux);
				zerarFrase(aux);
				a = 1;
				j = 0;
				i++;
			}
			
		}else{
			
			j++;
		}
	}
	
	return palavra_original_pre_processada;

}

char *descriptografaEnxerto(char *palavra, int *vetorGlobalEnxerto, int *cont){
	
	int i;
	
	int tam = strlen(palavra);								
	
	char *aux = (char*)malloc(tam * sizeof(char));			// vetor a ser preenchido com o enxerto descriptografado.
	
	zerarFrase(aux);
		
				
		for (i = 0; i < tam; i++){
					
			if (vetorGlobalEnxerto[*cont] != -1){
				
				if (palavra[i] == 'z'){
					aux[i] = ('z' - vetorGlobalEnxerto[*cont]);
					aux[i+1] = '\0';	
					(*cont)++;					
			
				}else{	
					aux[i] = (palavra[i] - vetorGlobalEnxerto[*cont]);
					aux[i+1] = '\0';
					(*cont)++;
				}	
			
			}else{
				(*cont)++;
				i--;
			}
		}
	
	strcat(aux, " ");	
	return aux;
}

char *descriptografaNMaus(char *palavra, int *vetorGlobalNMaus, int *cont){
	
		int tam = strlen(palavra);
	
	char *aux = (char*)malloc(tam * sizeof(char));				/*tentei fazer utilizando apenas 1 vetor aux, mas estava me dando muitos erros de invasao de memoria e sobrava lixo no vetor*/
	char *aux6= (char*)malloc(tam * sizeof(char));
    char *aux9 = (char*)malloc(tam * sizeof(char));
    char *resto = (char*)malloc(tam * sizeof(char));
    
	zerarFrase(aux);
	zerarFrase(aux6);
	zerarFrase(aux9);
	zerarFrase(resto);
	
    int i, p;
    int i6 = 0, i9 = 0, ir = 0;
    
     for (i = 0; i < tam; i++){ 
        if (palavra[i] == '6'){        
            aux6[i6] = palavra[i];
            aux6[i6+1]= '\0';
            i6++;
            
        }else if (palavra[i]=='9'){
            aux9 [i9] = palavra[i];
            aux9[i9+1]= '\0';
            i9++;
            
        }else{
            resto[ir] = palavra[i];
            resto[ir+1] = '\0';
            ir++;
        }
    }
    
		p = 0;
		
		
			for (i = 0; i < tam; i++){
				
				if(vetorGlobalNMaus[*cont] != -1){
					
					if(vetorGlobalNMaus[*cont] == 9){
						aux[i] = '9';
						aux[i+1] = '\0';
						(*cont)++;
				
					} else if (vetorGlobalNMaus[*cont] == 6){
						aux[i] = '6';
						aux[i+1] = '\0';
						(*cont)++;
				
					} else if(vetorGlobalNMaus[*cont] == 1){
						aux[i] = resto[p];
						aux[i+1] = '\0';
						p++;
						(*cont)++;
					}
				}else{
					(*cont)++;
					i--;
				}		
			}
	
	strcat(aux, " "); 	
    return aux;	
}

char *descriptografaMaxLetra(char *palavra){
	
	int tam = strlen(palavra);
	
	char *aux=(char*)malloc(tam*sizeof(char));
	
	char maior = palavra[0];
	
    zerarFrase(aux);
     
    int i, p; 
          
    for(i = 1; i < tam; i++){
        if(palavra[i] >= maior){
        	maior = palavra[i];
        }
	}
	
    p=0;
    
    for(i = 0; i < tam; i++){
        if(palavra[p] != maior){
            aux[i] = palavra[p];
            aux[i+1] = '\0';
			p++;
			
        }else{
            aux[i] = palavra[p];
            aux[i+1] = '\0';
            p+=2;
        }
	}
	  
	strcat(aux, " ");  
    return aux;
	
}


