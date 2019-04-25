#pragma once

#include<stdio.h>
#include<assert.h>
#include<vector>
#include<string>
#include<iostream>

enum args {NONE, NUM, REG};
enum regs {AX, BX, CX, DX};
enum type_comands {FUNC, ARG};

std::vector<char> Loading(FILE* File);
std::vector<std::string> Tokenisation(FILE* ASMFile);

struct elem_table_func {
	std::string func;
	int code_func;

	elem_table_func(){
		func = "";
		code_func = 0;
	};
	~elem_table_func(){
		func = "";
		code_func = 0;
	};
	elem_table_func(const elem_table_func& copyelem){
		func = copyelem.func;
		code_func = copyelem.code_func;
	};
};

union arg{
	int value;
	regs reg;
};

struct elem_table_args {
	
	args type_arg;
	union arg uni;
};

struct elem_table_comands {
	
	type_comands type;
	union value_comand {
		int code_func;
		struct elem_table_arg;
	};

};
