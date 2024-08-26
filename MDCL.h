#ifndef DOUBLE_CIRCULAR_LINKED_LIST_H
#define DOUBLE_CIRCULAR_LINKED_LIST_H


/*
Author: Perengrine
Purpose: Modular Double Circular Linked List
Dependancies: stdbool.h (for proper return values)
Note: Struct Definitions and Function Prototypes are included in this header file.
*/

/* Structure Definitions */

struct Node {
    void* data;            // dynamically allocated variable to store data
    int position;          // node position in list
    struct Node* next;     // points to the next node, or to head if tail
    struct Node* prev;     // points to the previous node, or to tail if head
};

struct NodeManager {
    char ListID[30];       // used to identify the specific list
    int NodeCount;         // the number of nodes created by CreateList
    struct Node* head;     // points to the head node (index 0)
    struct Node* tail;     // points to the tail node (last index)
    struct Node* NodeArray; // pointer to the array of nodes
};

/* Function Prototypes */

struct NodeManager* CreateList(int NodeCount, const char* ListID);
struct Node* InsertNodeAtEnd(struct NodeManager*);
struct Node* InsertNodeAtBeginning(struct NodeManager*);
struct Node* InsertNodeAtPosition(struct NodeManager*, int position);
struct Node* FindNodeData(struct NodeManager*, void* data, size_t DataSize);
bool DeleteList(struct NodeManager*);
bool DeleteAllNodes(struct NodeManager*);
bool DeleteNodeAtEnd(struct NodeManager*);
bool DeleteNodeAtBeginning(struct NodeManager*);
bool DeleteNodeAtPosition(struct NodeManager*, int position);
bool SetNodeData(struct NodeManager*, int position, void* data);
bool EmptyNodeData(struct NodeManager*, int position);
bool SortList(bool (*SortMethod)(struct NodeManager*), struct NodeManager*);
bool _AlphanumSortList(struct NodeManager*);
void _RefreshList(struct NodeManager*);

/* Function Pointer for Alphanumeric Sort */
extern bool (*AlphaSort)(struct NodeManager*);

#endif // DOUBLE_CIRCULAR_LINKED_LIST_H