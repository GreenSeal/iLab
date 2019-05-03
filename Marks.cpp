#include"CPU.h"

std::vector<elem_table_comands> Marks (std::vector<elem_table_comands> CmdTable) {
	std::vector<elem_table_comands> CmdWithMarks;
	std::vector<elem_table_marks> TableMarks;
	std::vector<elem_table_comands>::iterator it_cmd = CmdTable.begin();
	unsigned int size_cmd = CmdTable.size();
	int i = 0, j = 0, k = 0, code_error = 1;
	
	for(i = 0; i <= size_cmd - 1; i++, it_cmd++) {
		
		if(CmdTable[i].type == MARK && CmdTable[i].comand_value.mark[strlen(CmdTable[i].comand_value.mark) - 1] == ':') {
			elem_table_marks elem;
			elem.mark = CmdTable[i].comand_value.mark;
			elem.adr = i;

			TableMarks.push_back(elem);
			CmdTable.erase(it_cmd);
			i--;
			it_cmd--;
			continue;
		}
	}

	unsigned int size_marks = TableMarks.size();
	std::vector<elem_table_marks>::iterator it_marks = TableMarks.begin();
	size_cmd = CmdTable.size();

	for(i = 0; i <= size_cmd - 1; i++) {
		
		if(CmdTable[i].type == JUMP) {

			std::string buf1 = CmdTable[i + 1].comand_value.mark;

			std::cout << buf1 << std::endl;
			
			for(j = 0, it_marks = TableMarks.begin(); j <= size_marks - 1; j++, it_marks++) {

				code_error = 1;
				std::string buf2 = TableMarks[j].mark;

				std::cout << buf2 << std::endl;

				if(buf1 + ":" == buf2) {
					CmdTable[i + 1].type = ARG;
					CmdTable[i + 1].comand_value.elem_arg.arg_type = NUM;
					CmdTable[i + 1].comand_value.elem_arg.arg.arg_value = TableMarks[j].adr;
					TableMarks.erase(it_marks);
					j--;
					it_marks--;
					code_error = 0;
					break;	
				}
			}

			if(code_error == 1) {
				printf("No marks for jump in code!!\n");
				std::abort();
			}
		}
	}

	if(TableMarks.size() != 0) {
		printf("Too many marks!!\n");
		std::abort();
	}

	return CmdTable;
}
