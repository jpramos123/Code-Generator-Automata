#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int nSimbols = 0;
int nStates = 0;
int initState = 0;
int finalStates = 0;
int tab = 0;

void writeHeaderGoto(ofstream&);
void writeStateLabel(ofstream&,int);
void writeSimbol(ofstream& file,int, int, char*);
void tabula(ofstream&,int);
void writeIfGoto(ofstream&, char*, int, int);
void writeLabel(ofstream&, int);
void writeElse(ofstream&);
void writeFinalStateGoto(ofstream&);
void writeRejectGoto(ofstream&);
void writeRejectLabel(ofstream&);
void writeAcceptLabel(ofstream&);

// Function mode
void writeIfFun(ofstream&, char*, int, int);
void writeMain(ofstream&);
void writeHeaderFun(ofstream&);
void writeFunReference(ofstream&);
void writeFun(ofstream&,int);
void writeRejectCall(ofstream&);
void writeFinalStateFun(ofstream&);
void writeRejectFun(ofstream&);
void writeAcceptFun(ofstream&);

int fileExist(string);

int main()
{
cout << "executando programa..."<<endl;
cout << "* Gerador de Programas *"<<endl;
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

while(fileExist(name)){
	cout << "O arquivo ja existe, digite outro nome" <<endl;
	cin >> name;
}
ofstream file;
file.open(name+".c");


int mode = 0;
cout << "Qual o metodo será utilizado? 0 - Funcao || 1 - GoTo " << endl;
cin >> mode;

if(mode == 0){
	writeHeaderFun(file);
	writeFunReference(file);
	writeMain(file);
	for(int state = 0; state < nStates; state++){
		tab = 1;
		writeFun(file,state);
			
		for (int i = 0; i < finalStates; i++){
			if(state == vecFinalStates[i]){
				writeFinalStateFun(file);
				writeElse(file);
			}
		}
		for(int simbol = 0; simbol < nSimbols; simbol++){
			if(matSimbToState[state][simbol] != -1){
				writeIfFun(file, vecSimbols, simbol, matSimbToState[state][simbol]);
				writeElse(file);
			}
		}
		writeRejectCall(file);
		tab = 0;
		tabula(file, tab);
		file << "}\n";
	}
	writeRejectFun(file);
	writeAcceptFun(file);

}
else
	if(mode == 1){	
		writeHeaderGoto(file);
		for(int state = 0; state < nStates; state++){
			tab = 1;
			writeLabel(file, state);

			for (int i = 0; i < finalStates; i++){
				if(state == vecFinalStates[i]){
					writeFinalStateGoto(file);
					writeElse(file);
				}
			}
			
			for(int simbol = 0; simbol < nSimbols; simbol++){
				if(matSimbToState[state][simbol] != -1){
					writeIfGoto(file, vecSimbols, simbol, matSimbToState[state][simbol]);
					writeElse(file);
					}						
			}
			writeRejectGoto(file);
		}
		tab = 0; // Reset tab
		writeRejectLabel(file);
		writeAcceptLabel(file);
		file << "}\n"; // Close main
		file.close();
	}
	else{
		cout << "Nenhuma escolha valida!" << endl;
		return 2;
	}


}

int fileExist(string name){
	FILE *file;
	string fullName = name+".c";
	if(file = fopen(fullName.c_str(),"r")){
		fclose(file);
		return 1;
	}
	return 0;	
}

// Functions related to Function mode
void writeHeaderFun(ofstream& file){
	file << "#include<stdio.h>\n\n";
}

void writeFunReference(ofstream& file){

	for (int i = 0; i < nStates; i++){
		file << "void e"+to_string(i)+"(char*,int);\n";
	}
	file << "void aceita();\n";
	file << "void rejeita();\n\n";
}

void writeMain(ofstream& file){

	file << "int main(){\n\n";
	file << "char word[200];\n";
	file << "int i = 0;\n";
	file << "gets(word);\n\n";
	file << "e"+to_string(initState)+"(word,i);"+"\n";
	file << "}\n\n";

}
void writeFinalStateFun(ofstream& file){
	
	tabula(file,tab);
	file << "if(word[i] == 0){\n";
	tab ++;

	tabula(file,tab);
	file << "aceita();\n";
	tab--;
	
	tabula(file,tab);
	file << "}\n";
}

void writeRejectFun(ofstream& file){
	
	tabula(file,tab);
	file << "void rejeita(){\n";
	tab++;
	tabula(file,tab);
	file << "printf(\"REJEITADO!!!\");\n";
	file << "return 1;\n";
	tab--;
	tabula(file,tab);
	file << "}\n\n";
}

void writeAcceptFun(ofstream& file){

	tabula(file,tab);
	file << "void aceita(){\n";
	tab++;
	tabula(file,tab);
	file << "printf(\"ACEITO!!!\");\n";
	file << "return 0;\n";
	tab--;
	tabula(file,tab);
	file << "}\n";
}


void writeRejectCall(ofstream& file){

	tabula(file,tab);
	file << "rejeita();\n";
	tab--;
}

void writeIfFun(ofstream& file, char* vecSimbols, int simbol, int nextState){
	
	tabula(file,tab);
	file << "if(word[i] == "+to_string(vecSimbols[simbol])+"){\n";
	tab++;

	tabula(file,tab);
	file << "i++;\n";

	tabula(file,tab);
	file << "e"+to_string(nextState)+"(word,i);\n";
	tab--;

	tabula(file,tab);
	file << "}\n";

}

void writeFun(ofstream& file, int state){

	file << "void e"+to_string(state)+"(char* word,int i){\n";

}

// Functions related to Goto mode
void writeRejectLabel(ofstream& file){
	
	tabula(file,tab);
	file << "REJEITA:\n";
	tab++;
	tabula(file,tab);
	file << "printf(\"REJEITADO!!!\");\n";
	tabula(file,tab);
	file << "return 1;\n\n";
	tab--;
}

void writeAcceptLabel(ofstream& file){

	tabula(file,tab);
	file << "ACEITA:\n";
	tab++;
	tabula(file,tab);
	file << "printf(\"ACEITO!!!\");\n";
	tabula(file,tab);
	file << "return 0;\n";
	tab--;
}
void writeFinalStateGoto(ofstream& file){
	
	tabula(file,tab);
	file << "if(word[i] == 0){\n";
	tab ++;

	tabula(file,tab);
	file << "goto ACEITA;\n";
	tab--;
	
	tabula(file,tab);
	file << "}\n";
}

void writeRejectGoto(ofstream& file){

	tabula(file,tab);
	file << "goto REJEITA;\n\n";
	tab--;
}

void writeIfGoto(ofstream& file, char* vecSimbols, int simbol, int nextState){
	
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
void writeHeaderGoto(ofstream& file){
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
