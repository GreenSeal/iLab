#include "CPU.h"

std::vector<struct elem_table_func> CreateTableFunc () {
	
	std::vector<struct elem_table_func> Table;
	struct elem_table_func elem1;
	elem1.func = "push";
	elem1.code_func = CMD_PUSH;
	
	struct elem_table_func elem2;
	elem2.func = "pop";
	elem2.code_func = CMD_POP;

	struct elem_table_func elem3;
	elem3.func = "add";
	elem3.code_func = CMD_ADD;

	struct elem_table_func elem4;
	elem4.func = "sub";
	elem4.code_func = CMD_SUB;
	
	struct elem_table_func elem5;
	elem5.func = "mul";
	elem5.code_func = CMD_MUL;

	struct elem_table_func elem6;
	elem6.func = "div";
	elem6.code_func = CMD_DIV;

	struct elem_table_func elem7;
	elem7.func = "in";
	elem7.code_func = CMD_IN;

	struct elem_table_func elem8;
	elem8.func = "out";
	elem8.code_func = CMD_OUT;

	Table.push_back(elem1);
	Table.push_back(elem2);
	Table.push_back(elem3);
	Table.push_back(elem4);
	Table.push_back(elem5);
	Table.push_back(elem6);
	Table.push_back(elem7);
	Table.push_back(elem8);

	return Table;
}

std::vector<elem_table_reg> CreateTableReg () {
	std::vector<elem_table_reg> Table;
	
	struct elem_table_reg elem1;
	elem1.reg = "ax";
	elem1.cmd_reg = AX;
	
	struct elem_table_reg elem2;
	elem2.reg = "bx";
	elem2.cmd_reg = BX;

	struct elem_table_reg elem3;
	elem3.reg = "cx";
	elem3.cmd_reg = CX;

	struct elem_table_reg elem4;
	elem4.reg = "dx";
	elem4.cmd_reg = DX;

	Table.push_back(elem1);
	Table.push_back(elem2);
	Table.push_back(elem3);
	Table.push_back(elem4);

	return Table;

}

std::vector<elem_table_jump> CreateTableJump () {
	std::vector<elem_table_jump> Table;

	struct elem_table_jump elem1;
	elem1.jump = "je";
	elem1.cmd_jump = JE;

	Table.push_back(elem1);

	return Table;
}

std::vector<struct elem_table_comands> Translation (std::vector<std::string> TokenTable){
	std::vector<struct elem_table_comands> CmdTable;
	unsigned int size_tokens = TokenTable.size();
	std::vector<elem_table_func> TableFunc = CreateTableFunc();
	unsigned int size_funcs = TableFunc.size();
	std::vector<elem_table_reg> TableReg = CreateTableReg();
	unsigned int size_regs = TableReg.size();
	std::vector<elem_table_jump> TableJump = CreateTableJump();
	unsigned int size_jump = TableJump.size();	
	int i = 0, j = -1, k = 0, m = 0, code_jump = 0;

	for(i = 0; i <= size_tokens - 1; i++) {
		j++;
		int code_error = 1;
		
		for(k = 0; k <= size_funcs - 1; k++){
			if(TokenTable[i] == TableFunc[k].func) {
				struct elem_table_comands elem;
				elem.type = FUNC;
				elem.comand_value.code_func = TableFunc[k].code_func;
				
				CmdTable.push_back(elem);

				code_error = 0;
				break;
			}
		}

		for(m = 0; m <= size_regs - 1; m++){
	
			if(TokenTable[i] == TableReg[m].reg) {
				struct elem_table_comands elem;
				elem.type = ARG;
				elem.comand_value.elem_arg.arg_type = REG;
				elem.comand_value.elem_arg.arg.reg = TableReg[m].cmd_reg; 
				CmdTable.push_back(elem);

				code_error = 0;
				break;
			}
		}

		for(k = 0; k <= size_jump - 1; k++) {
			if(TokenTable[i] == TableJump[k].jump) {
				struct elem_table_comands elem;
				elem.type = JUMP;
				elem.comand_value.code_jump = TableJump[k].cmd_jump;

				CmdTable.push_back(elem);
				
				code_error = 0;
				code_jump = 1;
				break;
			}
		}

		if(code_error == 0) continue; 

		if(atoi(TokenTable[i].c_str()) != 0) {
			struct elem_table_comands elem;
			elem.type = ARG;
			elem.comand_value.elem_arg.arg_type = NUM;
			elem.comand_value.elem_arg.arg.arg_value = atoi(TokenTable[i].c_str()); 

			CmdTable.push_back(elem);

			continue;
		}

		if(code_jump == 1) {
			struct elem_table_comands elem;
			elem.type = MARK;
			elem.comand_value.mark = strdup(TokenTable[i].c_str());

			CmdTable.push_back(elem);

			code_jump = 0;
			continue;
		}

		if(TokenTable[i][TokenTable[i].size() - 1] == ':'){
			struct elem_table_comands elem;
			elem.type = MARK;
			elem.comand_value.mark = strdup(TokenTable[i].c_str());

			CmdTable.push_back(elem);
		}

		else {
			printf("Incorrect function or argument!!\n");
			std::abort();
		}
	
	}

	return CmdTable;
}
