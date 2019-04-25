#include"CPU.h"

#if 0
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
#endif

#if 1
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
#endif

std::vector<struct elem_table_func> CreateTableFunc () {
	
	std::vector<struct elem_table_func> Table;
	struct elem_table_func elem1;
	elem1.func = "push";
	elem1.code_func = 1;
	
	struct elem_table_func elem2;
	elem2.func = "pop";
	elem2.code_func = 2;

	struct elem_table_func elem3;
	elem3.func = "add";
	elem3.code_func = 3;

	struct elem_table_func elem4;
	elem4.func = "sub";
	elem4.code_func = 4;

	struct elem_table_func elem5;
	elem5.func = "mul";
	elem5.code_func = 5;

	struct elem_table_func elem6;
	elem6.func = "div";
	elem6.func = 6;

	Table.push_back(elem1);
	Table.push_back(elem2);
	Table.push_back(elem3);
	Table.push_back(elem4);
	Table.push_back(elem5);
	Table.push_back(elem6);

	return Table;
}

std::vector<struct elem_table_args> CreateTableArgs () {

	std::vector<struct elem_table_args> Table;
	struct elem_table_args elem1;
	elem1.type_arg = NONE;
	elem1.uni.value = 0;

	struct elem_table_args elem2;
	elem2.type_arg = NUM;
	elem2.uni.value = 0;

	struct elem_table_args elem3;
	elem3.type_arg = REG;
	elem3.uni.reg = AX;

	Table.push_back(elem1);
	Table.push_back(elem2);
	Table.push_back(elem3);

	return Table;
}


