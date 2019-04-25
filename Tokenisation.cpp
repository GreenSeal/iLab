#include <stdio.h>
#include <assert.h>
#include <vector>
#include <string>
#include <iostream>

std::vector<char> Loading(FILE* File) {
	
	int i = 0;
	std::vector<char> FileChar;
	while(fgetc(File) != EOF) {
		
		fseek(File, -sizeof(char) , SEEK_CUR);
		FileChar.push_back(fgetc(File));
	}

	return FileChar;
}

std::vector<std::string> Tokenisation(FILE* ASMFile) {
	
	std::vector<char> VectorFile = Loading (ASMFile);
	std::vector<char>::iterator it_file = VectorFile.begin();
	std::vector<std::string> Tokens;
	std::vector<std::string>::iterator it_tokens = Tokens.begin();
	char bufchar = '0';
	std::string bufstring = "";

	for(it_file; it_file != VectorFile.end(); it_file++) {
		
		bufchar = *it_file;
		
		if(isspace(bufchar) != 0) {
			Tokens.push_back(bufstring);
			bufstring = "";
		}

		else {
			bufstring = bufstring + bufchar;
		}
	}

	for (it_tokens = Tokens.begin(); it_tokens != Tokens.end(); it_tokens++) {
		std::cout << *it_tokens;
		printf(" ");
	}
	
	return Tokens;
}

int main () {
	FILE* ASMFile = fopen("ASM.txt","r");
	Tokenisation(ASMFile);
	std::vector<int> arr_int;
	fclose(ASMFile);
	return 0;
}
