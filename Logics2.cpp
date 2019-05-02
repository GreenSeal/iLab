#include "CPU.h"

int Logics(std::vector<elem_table_comands> CmdTable) {
	unsigned int size_cmd = CmdTable.size();
	int i = 0;	
	
	for(i = 0; i <= size_cmd - 1; i++) {
		if(CmdTable[i].type == FUNC) {
			if (CmdTable[i].comand_value.code_func[1] == '1') {
			
				if(i == size_cmd - 1) {
					printf("No argument for pop or push!!\n");
					std::abort();
				}
	
				else {
				
					if(CmdTable[i + 1].type != ARG) {
						printf("No argument for pop or push!!\n");
						std::abort();
					} 

					else continue;
				}
			}

			else {
				if(i == size_cmd - 1) continue;

				else {
					if (CmdTable[i + 1].type != ARG) continue;
					
					else {
						printf("Excess argument for non-argument function\n");
						std::abort();
					}
				}
			}
		}

			
		if(CmdTable[i].type == JUMP){
			
			if(i == size_cmd - 1) {
				printf("No mark for jump!!\n");
				std::abort();
			}

			else {
				
				if(CmdTable[i + 1].type != MARK) {
					printf("No mark for jump!\n");
					std::abort();
				}

				else continue;
			}
		}
			
		else continue;
	
	}

	return 0;
}
