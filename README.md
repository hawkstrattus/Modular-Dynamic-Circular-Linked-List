/*
Author: Perengrine

Purpose: Modular Double Circular Linked List

Dependancies: stdbool.h (to get proper return values)

Examples: (Note that CreateList must always be used first and DeleteList must ALWAYS be used before termination of a program) (EVERY LIST MUST BE DELETED TO FREE THE MEMORY)

	Function:	CreateList(int NodeCount, const char* ListID)
	Example:	struct NodeManager* MyListManager = CreateList(10, "MyListName");

	Function:	InsertNodeAtEnd(struct NodeManager*);
	Example:	struct Node* MyNewEndNode = InsertNodeAtEnd(MyListManager);

	Function:	InsertNodeAtBeginning(struct NodeManager*);
	Example:	struct Node* MyNewBeginningNode = InsertNodeAtBeginning(MyListManager);

	Function:	InsertNodeAtPosition(struct NodeManager*, int position);
	Example:	struct Node* MyNewPositionedNode = InsertNodeAtPosition(MyListManager, 3);

	Function:	SetNodeData(struct NodeManager*, int position, void* data);
	Example:	int MyDataIWantToStoreInANode = 432
			bool SuccessOnTrueFailiureOnFalse = SetNodeData(MyListManager, 7, &MyDataIWantToStoreInANode);

	Function:	EmptyNodeData(struct NodeManager*, int position);
	Example:	bool SuccessOnTrueFailiureOnFalse = EmptyNodeData(MyListManager, 7);

	Function:	DeleteNodeAtEnd(struct NodeManager*);
	Example:	bool SuccessOnTrueFailiureOnFalse = DeleteNodeAtEnd(MyListManager);

	Function:	DeleteNodeAtBeginning(struct NodeManager*);
	Example:	bool SuccessOnTrueFailiureOnFalse = DeleteNodeAtBeginning(MyListManager);

	Function:	DeleteNodeAtPosition(struct NodeManager*);
	Example:	bool SuccessOnTrueFailiureOnFalse = DeleteNodeAtPosition(MyListManager, 4);

	Function:	DeleteList(struct NodeManager*);
	Example:	bool SuccessOnTrueFailiureOnFalse = DeleteList(MyListManager);

	Function:	SortList(bool (*SortMethod) (struct NodeManager*), struct NodeManager*);
	Example:	bool SuccessOnTrueFailiureOnFalse = SortList(AlphaSort, MyListManager);

*/
