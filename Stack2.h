#include<stdio.h>

struct StackNode {
        int data;
        StackNode* prev;
};

class Stack {
	public :
	//private:
		StackNode* Head;
		StackNode* Cur;

	//public:
		Stack();
		~Stack();
		StackNode* PushData(int data_);
		StackNode* Pop(int* reg);
		StackNode* PushReg(int* reg);
		StackNode* Add(); 
		StackNode* Sub();
		StackNode* Mul(); 
		StackNode* Div();
};
