#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// void alphabet();
// void nStates();
// void initState();
// void finalStates();

int nSimbols = 0;
int nStates = 0;
int initState = 0;
int finalStates = 0;
int tab = 0;

void writeHeader(ofstream&);
void writeStateLabel(ofstream&,int);
void writeSimbol(ofstream& file,int, int, char*);
void tabula(ofstream&,int);
void writeIf(ofstream&, char*, int, int);
void writeLabel(ofstream&, int);
void writeElse(ofstream&);
void writeFinalState(ofstream&);
void writeReject(ofstream&);
void writeRejectLabel(ofstream&);
void writeAcceptLabel(ofstream&);

int main()
{

cout << "\nQuantos simbolos tem o alfabeto? ";
cin >> nSimbols;

char vecSimbols[nSimbols];

for(int i = 0; i <  nSimbols; i++){
    cout << "\nQual o simbolo " << i << " ? ";
    cin >> vecSimbols[i];
}

cout << "\nQuantos estados tem o automato? ";
cin >> nStates;

cout << "\nQual o estado inicial? ";
cin >> initState;

cout << "\nQuantos estados finais? ";
cin >> finalStates;

int vecFinalStates[finalStates];
for(int i = 0; i < finalStates; i++){
    cout << "\nQual o estado final " << i << " ? ";
    cin >> vecFinalStates[i];
}

int matSimbToState[nStates][nSimbols];

for(int state = 0; state < nStates; state++){
    for(int simbol = 0; simbol <  nSimbols; simbol++){
        cout << "\nPara o estado 'e" << state << "'" << " e o simbolo " << "'" << vecSimbols[simbol] << "'" << " qual o proximo estado? ";
        cin >> matSimbToState[state][simbol];
    }
}


/*Creating file with a given name and writing the basic program header*/
string name;
cout << "Qual o nome do arquivo? " << endl;
cin >> name;

ofstream file;
file.open(name+".c");
writeHeader(file);

int mode = 0;
cout << "Qual o metodo será utilizado? 0 - Funcao || 1 - GoTo " << endl;
cin >> mode;

if(mode == 0){
/* Checking if it's a valid transition*/
	for(int state = 0; state < nStates; state++){
		for(int simbol = 0; simbol < nSimbols; simbol++){
			if(matSimbToState[state][simbol] >= 0){
			}
		}
	}
		}
else
	if(mode == 1){	
		int oldState = 0;	

		for(int state = 0; state < nStates; state++){
				tab = 1;
				writeLabel(file, state);
				//oldState = state;

			for (int i = 0; i < finalStates; i++){
				if(state == vecFinalStates[i]){
					writeFinalState(file);
					writeElse(file);
				}
			}
			
			for(int simbol = 0; simbol < nSimbols; simbol++){
				if(matSimbToState[state][simbol] != -1){
					writeIf(file, vecSimbols, simbol, matSimbToState[state][simbol]);
					writeElse(file);
					}						
			}
			writeReject(file);
		}
	}
	else{
		cout << "Nenhuma escolha valida!" << endl;
		return 2;
	}

	tab = 0; // Reset tab
	writeRejectLabel(file);
	writeAcceptLabel(file);
	file << "}\n"; // Close main
	file.close();
}

void writeRejectLabel(ofstream& file){
	
	tabula(file,tab);
	file << "REJEITA:\n";
	tab++;
	tabula(file,tab);
	file << "printf(\"REJEITADO!!!\");\n";
	file << "return 1\n";
	tab--;
}

void writeAcceptLabel(ofstream& file){

	tabula(file,tab);
	file << "ACEITA:\n";
	tab++;
	tabula(file,tab);
	file << "printf(\"ACEITO!!!\");\n";
	file << "return 0\n";
	tab--;
}
void writeFinalState(ofstream& file){
	
	tabula(file,tab);
	file << "if(word[i] == 0){\n";
	tab ++;

	tabula(file,tab);
	file << "goto ACEITA;\n";
	tab--;
	
	tabula(file,tab);
	file << "}\n";
}

void writeReject(ofstream& file){

	tabula(file,tab);
	file << "goto REJEITA;\n";
	tab--;
}

void writeIf(ofstream& file, char* vecSimbols, int simbol, int nextState){
	
	tabula(file,tab);
	file << "if(word[i] == "+to_string(vecSimbols[simbol])+"){\n";
	tab++;

	tabula(file,tab);
	file << "i++;\n";

	tabula(file,tab);
	file << "goto E"+to_string(nextState)+";\n";
	tab--;

	tabula(file,tab);
	file << "}\n";

}

void writeElse(ofstream& file){

	tabula(file,tab);
	file << "else\n";
	tab++;
}
void writeHeader(ofstream& file){
	file << "#include<stdio.h>\n\n";
	file << "int main(){\n\n";
	file << "char word[200];\n";
	file << "int i = 0;\n";
	file << "gets(word);\n\n";
	file << "E"+to_string(initState)+":"+"\n";
}

void writeLabel(ofstream& file, int state){
	if(state != initState){
		file << "E"+to_string(state)+":\n";
	}else
		return;
}


void tabula(ofstream& file, int times){
	for(int i = 0; i < times; i++){
		file << "\t";
	}
}
