#include "Stack.h"

Stack::Stack() {
	Head = new StackNode;
	Head -> data = 0;
	Head -> prev = NULL;
	Cur = Head;
}

Stack::~Stack() {
	while(Cur != NULL) {
	Cur -> data = 0;
	Cur = Cur -> prev;
	}
}

StackNode* Stack::PushData(int data_) {
	StackNode* Buf = new StackNode;
	Buf -> data = data_;
	Buf -> prev = Cur;
	Cur = Buf;
	return Cur;
}

StackNode* Stack::Pop(int* reg) {
	*reg = Cur -> data;
	Cur = Cur -> prev;
	return Cur;
}

StackNode* Stack::PushReg(int* reg) {
	StackNode* Buf = new StackNode;
	Buf -> data = *reg;
	Buf -> prev = Cur;
	Cur = Buf;
	return Cur;
}

StackNode* Stack::Add() {
	int b = Cur -> data;
	Cur = Cur -> prev;
	int a = Cur -> data;
	Cur -> data = b + a;
	return Cur;
}

StackNode* Stack::Sub() {
	int b = Cur -> data;
        Cur = Cur -> prev;
        int a = Cur -> data;
        Cur -> data = b - a;
        return Cur;
}

StackNode* Stack::Mul() {
	int b = Cur -> data;
        Cur = Cur -> prev;
        int a = Cur -> data;
        Cur -> data = b * a;
	return Cur;
}

StackNode* Stack::Div() {
        int b = Cur -> data;
        Cur = Cur -> prev;
        int a = Cur -> data;
        Cur -> data = b / a;
        return Cur;
}

