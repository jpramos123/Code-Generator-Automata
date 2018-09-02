#include <iostream>

using namespace std;

// Method to start with the basic questions about the program generator

char* alphabet(){
int nSimbols = 0;

printf("Quantos simbolos tem o alfabeto? ");
cin >> nSimbols;

char vecSimbols[nSimbols];

for (int i = 0; i < nSimbols; i++){
        printf("Qual o simbolo %d? ",i);
        cin >> vecSimbols[i];
    }
    return vecSimbols;
}

// Method to handle initialization of automata states
int nStates(){

int nStates = 0;
printf("Quantos estados tem o automato? ");
cin >> nStates;
return nStates;
}

int firstState(){

int firstState = 0;
printf("Qual o estado inicial? ");
cin >> firstState;
return firstState;

}


int* finalStates(char){

int nFinalStates = 0;
printf("Quantos estados finais? ");
cin >> nFinalStates;

int vecFinalStates[nFinalStates];

for(int i = 0; i < nFinalStates; i++){
    printf("Qual o estado final %d? ", i);
    cin >> vecFinalStates[i];
}

return vecFinalStates;

}

int nFinalStates