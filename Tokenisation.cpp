#include "CPU.h"

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
	unsigned int size_file = VectorFile.size();
	int i = 0;

	for(i = 0; i <= size_file - 1; i++) {
		
		bufchar = VectorFile[i];
		
		if(isspace(bufchar) != 0 && bufstring != "") {
			Tokens.push_back(bufstring);
			bufstring = "";
		}

		if(isspace(VectorFile[i]) != 0 && bufstring == "") continue;

		else {
			bufstring = bufstring + bufchar;
		}
	}
	
	return Tokens;
}

int main () {
	FILE* ASMFile = fopen("ASM.txt","r");
	std::vector<std::string> TokenTable = Tokenisation(ASMFile);
	std::vector<struct elem_table_comands> CmdTable = Translation(TokenTable);
	Logics(CmdTable);
	CmdTable = Marks(CmdTable);
	CPU(CmdTable);
	fclose(ASMFile);
	return 0;
}
