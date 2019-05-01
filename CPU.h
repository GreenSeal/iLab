#pragma once

#include"Stack.h"
#include<assert.h>
#include<stdio.h>
#include<vector>
#include<string>
#include<cstring>
#include<iostream>

enum funcs {CMD_PUSH, CMD_POP, CMD_ADD, CMD_SUB, CMD_MUL, CMD_DIV, CMD_IN, CMD_OUT};
enum args {NUM, REG};
enum regs {AX, BX, CX, DX};
enum jumps{JE};
enum type_comands {FUNC, ARG, JUMP, MARK, NONE};

std::vector<char> Loading(FILE* File);
std::vector<std::string> Tokenisation(FILE* ASMFile);
std::vector<struct elem_table_func> CreateTableFunc();
std::vector<struct elem_table_reg> CreateTableReg();
std::vector<struct elem_table_comands> Translation(std::vector<std::string> TokenTable);
int Logics(std::vector<elem_table_comands> CmdTable);
std::vector<struct elem_table_comands> Marks(std::vector<struct elem_table_comands> CmdTable);
int CPU(std::vector<elem_table_comands> CmdTable);

struct elem_table_func {
	std::string func;
	funcs code_func;

	elem_table_func(){
		func = "";
		code_func = CMD_PUSH;
	};
	~elem_table_func(){
		func = "";
		code_func = CMD_PUSH;
	};
	elem_table_func(const elem_table_func& copyelem){
		func = copyelem.func;
		code_func = copyelem.code_func;
	};
};


struct elem_table_reg {
	std::string reg;
	regs cmd_reg;

	elem_table_reg(){
		reg = "";
		cmd_reg = AX; 
	};

	~elem_table_reg(){
		reg = "";
		cmd_reg = AX;
	};

	elem_table_reg(const elem_table_reg& copyelem) {
		reg = copyelem.reg;
		cmd_reg = copyelem.cmd_reg;
	};
};

struct elem_table_jump {
	std::string jump;
	jumps cmd_jump;

	elem_table_jump(){
		jump = "";
		cmd_jump = JE;
	};

	~elem_table_jump(){
		jump = "";
		cmd_jump = JE;
	};

	elem_table_jump(const elem_table_jump& copyelem) {
		jump = copyelem.jump;
		cmd_jump = copyelem.cmd_jump;
	};
};

struct elem_table_marks {
	const char* mark;
	int adr;
};

struct elem_table_comands {

	type_comands type;
	union value_comand {
		
		const char* mark;	
		jumps code_jump;
		funcs code_func;
		struct elem_table_arg {
			
			args arg_type;
			union value_arg{
				regs reg;
				int arg_value;
			} arg;
		
		} elem_arg;
	
	} comand_value;
};
