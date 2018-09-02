#include<stdio.h>

int main(){

char word[200];
int i = 0;
gets(word);

E0:
	if(word[i] == 0){ // 1 tab
		goto ACEITA; // 2 tab
	}				// 1 tab	
	else			// 1 tab
		if(word[i] == '97'){ // 1 tab
			i++;			// 2 tab
			goto E1;		// 2 tab
		}					// 1 tab
		else				// 1 tab
			if(word[i] == 92){ // 2 tab
				i++;			// 3 tab
				goto E2;		// 3 tab
			}					// 2 tab
E1:
