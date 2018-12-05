#include <stdio.h>
#include <stdlib.h>

typedef struct Node_ Node;

Node* Create(int data_to_fill);
int Print(Node AnyNode);
int Delete(Node* AddNode);
int Link(Node* next, Node* prev, Node* AddNode);
int Swap(Node* AddNode1, Node* AddNode2);
Node* Search(Node* AddNode, Node* AnyAddNode);
int Idx(Node* AddNode, Node* AnyAddNode);

struct Node_ {
    unsigned long long data; 
    Node* next;
    Node* prev;
};


/*int main() {
	Node New_Node1 = *(Create(1));
    Node New_Node2 = *(Create(2));
    Node New_Node3 = *(Create(3));
    //Link(&New_Node3, &New_Node1, &New_Node2);
    //Delete(&New_Node2);
    //PrintNode(New_Node2);
    //Swap(&New_Node2, &New_Node3);
    //printf("%d", ((New_Node1.next) -> data));
	return 0;
}*/
    
int Print(Node AnyNode) {
    
    printf("%llu\n", AnyNode.data);
    
    return 0;
}

Node* Create(unsigned long long data_to_fill) {
    
    Node* New_node = (Node*) calloc (1, sizeof(Node));
    
    New_node -> data = data_to_fill;
    New_node -> next = NULL;
    New_node -> prev = NULL;
    
    return New_node;
}

int Link(Node* next, Node* prev, Node* AddNode) {
    
    if (AddNode == NULL){
        printf("Node doesn't exist. Code 1");
        return 1;
    }
        
    AddNode -> next = next;
    AddNode -> prev = prev;
    if (next != NULL)
    next -> prev = AddNode;
    if(prev !=NULL)
    prev -> next = AddNode;
    
    return 0;
}

int Delete(Node* AddNode) {
    
    if (AddNode == NULL){
        printf("Node doesn't exist. Code 1");
        return 1;
    }
    
    AddNode -> next -> prev = AddNode -> prev;
    AddNode -> prev -> next = AddNode -> next;
    AddNode -> prev = NULL;
    AddNode -> next = NULL;
    free(AddNode);
    
    return 0;
}

int Swap(Node* AddNode1, Node* AddNode2) {
    
    if ((AddNode1 == NULL) || (AddNode2 == NULL)){
        printf("Node doesn't exist. Code 1");
        return 1;
    }
    
    if ((AddNode1 -> prev -> next) != NULL)
    (AddNode1 -> prev -> next) = AddNode2;
    
    (AddNode1 -> next) = (AddNode2 -> next);
    (AddNode2 -> next) = AddNode1;
    
    if((AddNode2 -> next -> prev) != NULL)
    (AddNode2 -> next -> prev) = AddNode2;
       
    (AddNode2 -> prev) = (AddNode1 -> prev);
    (AddNode1 -> prev) = AddNode2;
    
    return 0;
}

Node* Search(Node* AddNode, Node* AnyAddNode) {
    
    if ((AddNode == NULL) || (AnyAddNode == NULL)){
        printf("Node doesn't exist. Code 1");
        //return 1;
    }
    
    Node* buf = AnyAddNode;
    
    while((buf -> prev) != NULL)
        buf = buf -> prev;
    
    while((buf -> data) != (AddNode -> data)){
        buf = buf -> next;
        if (buf == NULL) {
            printf ("Node doesn't find");
            break;
        } 
    }
    return buf;  
}

int Idx(Node* AddNode, Node* AnyAddNode) {
    
    if ((AddNode == NULL) || (AnyAddNode == NULL)){
        printf("Node doesn't exist. Code 1");
        return 1;
    }
    
    Node* buf = AnyAddNode;
    int idx = 0;
    
    while((buf -> prev) != NULL)
        buf = buf -> prev;
        
    while((buf -> data) != (AddNode -> data)){
        buf = buf -> next;
        ++idx;
        if (buf == NULL) {
            printf ("Node doesn't find");
            break;
        } 
    }
    
    return idx;
}