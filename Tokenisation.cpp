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
	//-----------------------------------------------------------
        unsigned int size_cmd = CmdTable.size(), i = 0;
        std::cout << std::endl << std::endl;
        for(i = 0; i <= size_cmd - 1; i++) {
                if(CmdTable[i].type == FUNC) std::cout << CmdTable[i].comand_value.code_func << std::endl;

                if(CmdTable[i].type == ARG && CmdTable[i].comand_value.elem_arg.arg_type == NUM) std::cout << CmdTable[i].comand_value.elem_arg.arg.arg_value << std::endl;

                if(CmdTable[i].type == ARG && CmdTable[i].comand_value.elem_arg.arg_type == REG) std::cout << CmdTable[i].comand_value.elem_arg.arg.reg << std::endl;

                if(CmdTable[i].type == JUMP) std::cout << CmdTable[i].comand_value.code_jump << std::endl;

                if(CmdTable[i].type == MARK) std::cout << CmdTable[i].comand_value.mark << std::endl;
        }
        //-----------------------------------------------------------
	Logics(CmdTable);
	CmdTable = Marks(CmdTable);
	CPU(CmdTable);
	fclose(ASMFile);
	return 0;
}
