#include "CPU.h"

int In(int* reg) {
	int am = scanf("%d", reg);
	return am;
}

int Out(int* reg) {
	int am = printf("%d\n", *reg);
	return am;
}


int CPU(std::vector<elem_table_comands> CmdTable) {
	unsigned int size_cmd = CmdTable.size();
	int i = 0;
	Stack CmdStack;
	int ax = 0, bx = 0, cx = 0, dx = 0;

	for(i = 0; i <= size_cmd - 1; i++) {

		if (CmdTable[i].type == FUNC) {
			
			if(CmdTable[i].comand_value.code_func == CMD_PUSH) {
				
				assert(CmdTable[i + 1].type == ARG);

				if(CmdTable[i + 1].comand_value.elem_arg.arg_type == NUM) CmdStack.PushData(CmdTable[i + 1].comand_value.elem_arg.arg.arg_value);

				else {  
					assert(CmdTable[i + 1].comand_value.elem_arg.arg_type == REG);
					switch(CmdTable[i + 1].comand_value.elem_arg.arg.reg) {
						
						case AX: CmdStack.PushReg(&ax); break;
						case BX: CmdStack.PushReg(&bx); break;
						case CX: CmdStack.PushReg(&cx); break;
						case DX: CmdStack.PushReg(&dx); break;
						default: printf("Incorrect reg!!\n"); std::abort();
					}
				}
			}

			if(CmdTable[i].comand_value.code_func == CMD_POP) {
				
				assert(CmdTable[i + 1].type == ARG);

				switch(CmdTable[i + 1].comand_value.elem_arg.arg.reg) {
				
					case AX: CmdStack.Pop(&ax); break;
					case BX: CmdStack.Pop(&bx); break;
					case CX: CmdStack.Pop(&cx); break;
					case DX: CmdStack.Pop(&dx); break;
					default: printf("Incorrect reg!!!\n"); std::abort();
				}
			}

			if(CmdTable[i].comand_value.code_func == CMD_IN) {
				assert(CmdTable[i + 1].type == ARG);

				switch(CmdTable[i + 1].comand_value.elem_arg.arg.reg) {
					
					case AX: In(&ax); break;
					case BX: In(&bx); break;
					case CX: In(&cx); break;
					case DX: In(&dx); break;
					default: printf("Incorrect reg!!!!!\n"); std::abort();
				}
			}

			if(CmdTable[i].comand_value.code_func == CMD_OUT) {

                                assert(CmdTable[i + 1].type == ARG);

                                switch(CmdTable[i + 1].comand_value.elem_arg.arg.reg) {

                                        case AX: Out(&ax); break;
                                        case BX: Out(&bx); break;
                                        case CX: Out(&cx); break;
                                        case DX: Out(&dx); break;
                                        default: printf("Incorrect reg!!!!\n"); std::abort();
                                }
                        }


			if(CmdTable[i].comand_value.code_func == CMD_ADD) CmdStack.Add();

			if(CmdTable[i].comand_value.code_func == CMD_SUB) CmdStack.Sub();
			
			if(CmdTable[i].comand_value.code_func == CMD_MUL) CmdStack.Mul();

			if(CmdTable[i].comand_value.code_func == CMD_DIV) CmdStack.Div();

		}

		else {

			if(CmdTable[i].type == ARG) continue;

			if(CmdTable[i].type == JUMP) {
				
				if(CmdTable[i].comand_value.code_jump == JE) {
					CmdStack.Sub();
					CmdStack.Pop(&dx);
					
					if(dx == 0) {
						assert(CmdTable[i + 1].type == ARG);
						i = CmdTable[i + 1].comand_value.elem_arg.arg.arg_value;
						i--;

						continue;
					}

					else ;	
				}

				else {
					printf("Wrong jump!!\n");
					std::abort();
				}
			}

			else {
				printf("Anything wrong!!\n"); 
				std::abort();
			}

		}
	}
}
