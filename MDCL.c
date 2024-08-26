#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*
Author: Perengrine
Purpose: Modular Double Circular Linked List
Dependancies: stdbool.h (to get proper return values). Struct Definitions need to be included in the header file
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


/* Structure Definitions */

struct Node  				// the struct containing all the information a Node will store
{
	void* data;			// dynamically allocated variable to store strings
	int position;			// node position in list
	struct Node* next;		// the next node in list 0 being all the way at the left, next would point to 1 on the right, if tail node, this node will point to head
	struct Node* prev;		// the previous node in the list. If this node is the head node, it will point to the tail
};

struct NodeManager  			// this is the wrapper for all nodes in an instance of NodeManager. Each array of nodes (Determined at list creation) is managed through this
{
	char ListID[30];		// used to Identify the specific list
	int NodeCount;			// the amount of nodes to be created by the create list function
	struct Node* head;		// should always point to the 0 index of the node array
	struct Node* tail;		// should always point to the last index of the node array
	struct Node* NodeArray;		// this is a pointer to the node array for this instance of NodeManager
};


/* Function Prototypes */

struct NodeManager* CreateList		(int NodeCount, const char* ListID);				 // creates a list (an instance of NodeManager) with the specified amount of nodes
struct Node* InsertNodeAtEnd		(struct NodeManager*);						 // inserts a node at the end of the list (to the right), this becomes the tail
struct Node* InsertNodeAtBeginning	(struct NodeManager*);						 // inserts a node at the beginning of the list (to the left), this becomes the head
struct Node* InsertNodeAtPosition	(struct NodeManager*, int position);				 // inserts a node at a given position which corrosponds to the node's index
struct Node* FindNodeData		(struct NodeManager*, void* data, size_t DataSize);		 // finds the first occurance of a node with specific data and returns the node
bool DeleteList				(struct NodeManager*);						 // deletes a given list and returns whether the operaiton was successful or not
bool DeleteAllNodes			(struct NodeManager*);						 // deletes all nodes
bool DeleteNodeAtEnd			(struct NodeManager*);						 // deletes the tail and returns whether the operaiton was successful or not
bool DeleteNodeAtBeginning		(struct NodeManager*);						 // deletes the head and returns whether the operaiton was successful or not
bool DeleteNodeAtPosition		(struct NodeManager*, int position);				 // deletes a node at a specific node and returns the success of the operation
bool SetNodeData			(struct NodeManager*, int position, void* data); 		 // sets the char data of a node at the specified position for the given list
bool EmptyNodeData			(struct NodeManager*, int position);				 // sets the char data of a given node to 0s for the given list
bool SortList				(bool (*SortMethod) (struct NodeManager*), struct NodeManager*); // sorts a list based on the passed in algorithm 
bool _AlphanumSortList			(struct NodeManager*);						 // internal function, sorts list alphanumerically
void _RefreshList			(struct NodeManager*);						 // updates node addresses and positions


/* Functions */

bool (*AlphaSort) (struct NodeManager*) = &_AlphanumSortList; // make sure to include this in the header file

struct NodeManager* CreateList(int NodeCount, const char* ListID)
{
	// error checking node count
	if (NodeCount <= 0) // this is <= 0 and not just <0 because of how calloc works when allocating memory
	{
		fprintf(stderr, "\nInvalid NodeCount\n");
		return NULL;
	}

	// creating an instance of NodeManager called manager
	struct NodeManager* manager = calloc(1, sizeof(struct NodeManager));	// allocating memory for our node manager on the heap

	// error checking NodeManager
	if (manager == NULL)
	{
		perror("Failed to allocate memory for NodeManager");
		return NULL;
	}

	// creating array of struct nodes
	struct Node* NodeArray = calloc(NodeCount, sizeof(struct Node));		// allocating memory for our array of nodes on the heap

	// error checking NodeArray
	if (NodeArray == NULL)
	{
		perror("Failed to allocate memory for NodeArray");
		free(manager);
		return NULL;
	}

	// initializing NodeManager variables
	strncpy(manager->ListID, ListID, sizeof(manager->ListID) - 1); // copying the passed in list id to the variable in the nodemanager instance
	manager->ListID[sizeof(manager->ListID) - 1] = '\0'; // ensuring there is a null terminator at the end of ListID
	manager->NodeCount = NodeCount;
	manager->head = &NodeArray[0];
	manager->tail = &NodeArray[NodeCount - 1];
	manager->NodeArray = NodeArray;

	// initializing array of nodes/setting links
	for (int i = 0; i < NodeCount; i++)
	{
		if (i == 0) // if the current node in the loop is the head node
		{
			NodeArray[i].prev = &NodeArray[NodeCount - 1];
			NodeArray[i].next = &NodeArray[i + 1];
		}
		else if (i == NodeCount - 1) // if the current node in the loop is the tail node
		{
			NodeArray[i].prev = &NodeArray[i - 1];
			NodeArray[i].next = &NodeArray[0];
		}
		else
		{
			NodeArray[i].prev = &NodeArray[i - 1];
			NodeArray[i].next = &NodeArray[i + 1];
		}

		NodeArray[i].position = i;
	}


	return manager; // returns a pointer to the manager struct which contains the needed information to deal with the list
}


struct Node* InsertNodeAtEnd(struct NodeManager* NodeManager) // Realloc for expanding, do error checking
{
	// error checking passed in NodeManager pointer
	if (NodeManager == NULL)
	{
		fprintf(stderr, "\nNodeManager in InsertNodeAtEnd Function is NULL\n");
		return NULL;
	}

	// setting local variables to NodeManager's NodeCount and NodeArray for readability
	int NodeCount = NodeManager->NodeCount;
	struct Node* NodeArray = NodeManager->NodeArray;

	// reallocating memory for the new node
	struct Node* TempNodeArray = realloc(NodeArray, (NodeCount + 1) * sizeof(struct Node));

	// error checking our newly allocated memory
	if (TempNodeArray == NULL)
	{
		perror("Failed to allocate memory for TempNodeArray");
		return NULL;
	}

	// updating NodeManager variables and updating our corrosponding variables to the new NodeManager ones
	NodeManager->NodeCount += 1;
	NodeManager->NodeArray = TempNodeArray;
	NodeCount = NodeManager->NodeCount;
	NodeArray = NodeManager->NodeArray;
	
	// reassigning head, tail, prev, and next addresses incase of a new memory block when reallocating memory
	NodeManager->head = &NodeArray[0];
	NodeManager->tail = &NodeArray[NodeCount - 1];
	for (int i = NodeCount - 1; i >= 0; i--)
	{

		if (i == 0) // updating head node
		{
			
			NodeArray[i].position = 0;
			NodeArray[i].prev = &NodeArray[NodeCount - 1];
			NodeArray[i].next = &NodeArray[i + 1];
		}
		else if (i == NodeCount - 1) // creating our new node
		{
			NodeArray[i].next = &NodeArray[0];
			NodeArray[i].prev = &NodeArray[i - 1];
			NodeArray[i].position = i;
		}
		else // updating all other nodes
		{	
			NodeArray[i].next = &NodeArray[i + 1];
			NodeArray[i].prev = &NodeArray[i - 1];
			NodeArray[i].position = i;
		}

	}


	// returning pointer to the new end node
	return NodeManager->tail;
}


struct Node* InsertNodeAtBeginning(struct NodeManager* NodeManager)
{
	// error checking passed in NodeManager pointer
	if (NodeManager == NULL)
	{
		fprintf(stderr, "\nNodeManager in InsertNodeAtBeginning Function is NULL\n");
		return NULL;
	}

	// setting local variables to NodeManager's NodeCount and NodeArray for readability
	int NodeCount = NodeManager->NodeCount;
	struct Node* NodeArray = NodeManager->NodeArray;

	// reallocating memory for the new node
	struct Node* TempNodeArray = realloc(NodeArray, (NodeCount + 1) * sizeof(struct Node));

	// error checking our newly allocated memory
	if (TempNodeArray == NULL)
	{
		perror("Failed to allocate memory for TempNodeArray");
		return NULL;
	}

	// updating NodeManager variables and updating our corrosponding variables to the new NodeManager ones
	NodeManager->NodeCount += 1;
	NodeManager->NodeArray = TempNodeArray;
	NodeCount = NodeManager->NodeCount;
	NodeArray = NodeManager->NodeArray;

	// reassigning head and tail addresses incase of a new memory block when reallocating memory
	NodeManager->head = &NodeArray[0];
	NodeManager->tail = &NodeArray[NodeCount - 1];


	// shifting loop
	for (int i = NodeCount - 1; i > 0; i--)
	{

		NodeArray[i - 1].position += 1;
		NodeArray[i] = NodeArray[i - 1];

	}

	// reassigning head, tail, prev, and next addresses incase of a new memory block when reallocating memory
	for (int i = NodeCount - 1; i >= 0; i--)
	{

		if (i == 0) // creating our new node
		{
			
			NodeArray[i].position = 0;
			NodeArray[i].prev = &NodeArray[NodeCount - 1];
			NodeArray[i].next = &NodeArray[i + 1];
		}
		else if (i == NodeCount - 1) // updating tail node
		{
			NodeArray[i].next = &NodeArray[0];
			NodeArray[i].prev = &NodeArray[i - 1];
			NodeArray[i].position = i;
		}
		else // updating all other nodes
		{
			NodeArray[i].next = &NodeArray[i + 1];
			NodeArray[i].prev = &NodeArray[i - 1];
			NodeArray[i].position = i;
		}

	}


	// returning pointer to the new beginning node
	return NodeManager->head;
}


struct Node* InsertNodeAtPosition(struct NodeManager* NodeManager, int position)
{
	// error checking passed in NodeManager pointer
	if (NodeManager == NULL)
	{
		fprintf(stderr, "\nNodeManager in InsertNodeAtPosition Function is NULL\n");
		return NULL;
	}


	// setting local variables to NodeManager's NodeCount and NodeArray for readability
	int NodeCount = NodeManager->NodeCount;
	struct Node* NodeArray = NodeManager->NodeArray;

	if (position < 0 || position > NodeCount)
	{
		fprintf(stderr, "\nPosition arguement is out of bounds\n");
		return NULL;
	}

	// reallocating memory for the new node
	struct Node* TempNodeArray = realloc(NodeArray, (NodeCount + 1) * sizeof(struct Node));

	// error checking our newly allocated memory
	if (TempNodeArray == NULL)
	{
		perror("Failed to allocate memory for TempNodeArray");
		return NULL;
	}

	// updating NodeManager variables and updating our corrosponding variables to the new NodeManager ones
	NodeManager->NodeCount += 1;
	NodeManager->NodeArray = TempNodeArray;
	NodeCount = NodeManager->NodeCount;
	NodeArray = NodeManager->NodeArray;

	// end and beginning edge case handling
	if (position == NodeCount - 1)
	{
		InsertNodeAtEnd(NodeManager);
		return false;
	}
	else if (position == 0)
	{
		InsertNodeAtBeginning(NodeManager);
		return false;
	}

	// reassigning head and tail addresses incase of a new memory block when reallocating memory
	NodeManager->head = &NodeArray[0];
	NodeManager->tail = &NodeArray[NodeCount - 1];


	// shifting loop
	for (int i = NodeCount - 1; i > position; i--)
	{
		NodeArray[i] = NodeArray[i - 1];
		NodeArray[i].position = i;
	}

	// reassigning head, tail, prev, and next addresses incase of a new memory block when reallocating memory
	for (int i = NodeCount - 1; i >= 0; i--)
	{

		if (i == 0) // creating new node, add a edge case for positions that are at 0 or tail
		{
			NodeManager->head = &NodeArray[i];
			NodeManager->tail = &NodeArray[NodeCount - 1];
			NodeArray[i].prev = &NodeArray[NodeCount - 1];
			NodeArray[i].next = &NodeArray[i + 1];
		}
		else if (i == NodeCount - 1) // updating tail node
		{
			NodeArray[i].next = &NodeArray[0];
			NodeArray[i].prev = &NodeArray[i - 1];
			NodeArray[i].position = i;
		}
		else // updating all other nodes
		{
			NodeArray[i].next = &NodeArray[i + 1];
			NodeArray[i].prev = &NodeArray[i - 1];
			NodeArray[i].position = i;
		}

	}


	return &NodeManager->NodeArray[position];
}


bool DeleteList(struct NodeManager* NodeManager)
{
	// error checking passed in NodeManager and NodeArray pointer
	if (NodeManager == NULL)
	{
		fprintf(stderr, "\nNodeManager in DeleteList Function is NULL\n");
		return false;
	}

	if (NodeManager->NodeArray == NULL)
	{
		fprintf(stderr, "\nNodeArray in DeleteList Function is NULL\n");
		return false;
	}
	
	// freeing nodearray and setting it to null
	free(NodeManager->NodeArray);
	NodeManager->NodeArray = NULL;

	// freeing nodemanager memory	
	free(NodeManager);

	// setting nodemanager to NULL for error checking purposes
	NodeManager = NULL;

	return true;
}


bool DeleteAllNodes(struct NodeManager* NodeManager)
{
	// error checking passed in NodeManager and NodeArray pointer
	if (NodeManager == NULL)
	{
		fprintf(stderr, "\nNodeManager in DeleteAllNodes Function is NULL\n");
		return false;
	}

	if (NodeManager->NodeArray == NULL)
	{
		fprintf(stderr, "\nNodeArray in DeleteAllNodes Function is NULL\n");
		return false;
	}

	// freeing nodearray and setting it to null
	free(NodeManager->NodeArray);
	NodeManager->NodeArray = NULL;

	return true;
}


bool DeleteNodeAtEnd(struct NodeManager* NodeManager)
{
	// error checking passed in NodeManager pointer
	if (NodeManager == NULL)
	{
		fprintf(stderr, "\nNodeManager in DeleteNodeAtEnd Function is NULL\n");
		return false;
	}

	// setting local variables to NodeManager's NodeCount and NodeArray for readability
	NodeManager->NodeCount -= 1;
	int NodeCount = NodeManager->NodeCount;
	struct Node* NodeArray = NodeManager->NodeArray;

		// shrinking memory
	struct Node* TempNodeArray = realloc(NodeArray, (NodeCount) * sizeof(struct Node));

	// error checking our newly allocated memory
	if (TempNodeArray == NULL)
	{
		perror("Failed to allocate memory for TempNodeArray");
		return false;
	}

	NodeManager->NodeArray = TempNodeArray;
	NodeArray = NodeManager->NodeArray;

	for (int i = NodeCount - 1; i >= 0; i--)
	{

		if (i == 0) // updating head node
		{
			NodeArray[i].prev = &NodeArray[NodeCount - 1];
			NodeArray[i].next = &NodeArray[i + 1];
		}
		else if (i == NodeCount - 1) // setting the new tail node
		{
			NodeArray[i].next = &NodeArray[0];
			NodeArray[i].prev = &NodeArray[i - 1];
			NodeArray[i].position = i;
			NodeManager->tail = &NodeArray[i];
		}
		else // updating all other nodes
		{
			NodeArray[i].next = &NodeArray[i + 1];
			NodeArray[i].prev = &NodeArray[i - 1];
			NodeArray[i].position = i;
		}
	}


	return true;
}


bool DeleteNodeAtBeginning(struct NodeManager* NodeManager)
{
	// error checking passed in NodeManager pointer
	if (NodeManager == NULL)
	{
		fprintf(stderr, "\nNodeManager in DeleteNodeAtBeginning Function is NULL\n");
		return false;
	}

	// setting local variables to NodeManager's NodeCount and NodeArray for readability
	NodeManager->NodeCount -= 1;
	int NodeCount = NodeManager->NodeCount;
	struct Node* NodeArray = NodeManager->NodeArray;


	// shifting loop
	for (int i = 0; i < NodeCount; i++)
	{
		NodeArray[i] = NodeArray[i + 1];
		NodeArray[i].position = i;
	}


	// shrinking memory
	struct Node* TempNodeArray = realloc(NodeArray, (NodeCount) * sizeof(struct Node));

	// error checking our newly allocated memory
	if (TempNodeArray == NULL)
	{
		perror("Failed to allocate memory for TempNodeArray");
		return false;
	}

	NodeManager->NodeArray = TempNodeArray;

	_RefreshList(NodeManager);

	return true;
}


bool DeleteNodeAtPosition(struct NodeManager* NodeManager, int position)
{
	// error checking passed in NodeManager pointer
	if (NodeManager == NULL)
	{
		fprintf(stderr, "\nNodeManager in DeleteNodeAtBeginning Function is NULL\n");
		return false;
	}

	// setting local variables to NodeManager's NodeCount and NodeArray for readability
	NodeManager->NodeCount -= 1;
	int NodeCount = NodeManager->NodeCount;
	struct Node* NodeArray = NodeManager->NodeArray;

	// Making sure position is within bound
	if (position < 0 || position > NodeCount)
	{
		fprintf(stderr, "\nPosition arguement is out of bounds\n");
		return false;
	}

	// end and beginning edge case handling
	if (position == NodeCount - 1)
	{
		DeleteNodeAtEnd(NodeManager);
		return false;
	}
	else if (position == 0)
	{
		DeleteNodeAtBeginning(NodeManager);
		return false;
	}

	// shifting loop
	for (int i = position; i < NodeCount; i++)
	{
		NodeArray[i] = NodeArray[i + 1];
		NodeArray[i].position = i;
	}

	// shrinking memory
	struct Node* TempNodeArray = realloc(NodeArray, (NodeCount) * sizeof(struct Node));

	// error checking our newly allocated memory
	if (TempNodeArray == NULL)
	{
		perror("Failed to allocate memory for TempNodeArray");
		return false;
	}

	// Updating NodeArray in NodeManager and our copy
	NodeManager->NodeArray = TempNodeArray;

	_RefreshList(NodeManager);

	return true;
}


bool SetNodeData(struct NodeManager* NodeManager, int position, void* data)
{
	// error checking passed in NodeManager pointer
	if (NodeManager == NULL)
	{
		fprintf(stderr, "\nNodeManager in SetNodeData Function is NULL\n");
		return NULL;
	}

		// error checking data
	if (data ==  NULL)
	{
		fprintf(stderr, "\nData in SetNodeData Function is NULL\n");
		return false;
	}

	// setting local variables to NodeManager's NodeCount and NodeArray for readability
	int NodeCount = NodeManager->NodeCount;
	struct Node* NodeArray = NodeManager->NodeArray;

	// error checking position value
	if (position > NodeCount -1 || position < 0)
	{
		fprintf(stderr, "\nPosition arguement is out of bounds\n");
		return false;
	}

	NodeArray[position].data = data;


	return true;
}


struct Node* FindNodeData(struct NodeManager* NodeManager, void* data, size_t DataSize)
{

	// error checking passed in NodeManager pointer
	if (NodeManager == NULL)
	{
		fprintf(stderr, "\nNodeManager in SetNodeData Function is NULL\n");
		return NULL;
	}

		// error checking data
	if (data ==  NULL)
	{
		fprintf(stderr, "\nData in SetNodeData Function is NULL\n");
		return false;
	}
	
	// setting local variables to NodeManager's NodeCount and NodeArray for readability
	int NodeCount = NodeManager->NodeCount;
	struct Node* NodeArray = NodeManager->NodeArray;

	// Looking for the node with the data using memcmp
	for (int i = 0; i < NodeCount; i++)
	{
		if (NodeArray[i].data == NULL) // if you try to memcmp on with a null pointer, you get a seg fault
		{
			continue;
		}
		else if (memcmp(NodeArray[i].data, data, DataSize) == 0)
		{
			return &NodeArray[i];
		}
	}
	return NULL;
}


bool EmptyNodeData(struct NodeManager* NodeManager, int position)
{
		// error checking passed in NodeManager pointer
	if (NodeManager == NULL)
	{
		fprintf(stderr, "\nNodeManager in EmptyNodeData Function is NULL\n");
		return false;
	}

	// setting local variables to NodeManager's NodeCount and NodeArray for readability
	int NodeCount = NodeManager->NodeCount;
	struct Node* NodeArray = NodeManager->NodeArray;

	// error checking position value
	if (position > NodeCount -1 || position < 0)
	{
		fprintf(stderr, "\nPosition arguement is out of bounds\n");
		return false;
	}

	// emptying the data
	NodeArray[position].data = NULL;

	return true;
}

bool _AlphanumSortList(struct NodeManager* NodeManager)
{
	// error checking passed in NodeManager pointer
	if (NodeManager == NULL)
	{
		fprintf(stderr, "\nNodeManager in AlphanumSortList Function is NULL\n");
		return false;
	}

	// Setting local variables to NodeManager struct
	struct Node* NodeArray = NodeManager->NodeArray;
	int NodeCount = NodeManager->NodeCount;
	struct Node TempNode;

	
	for (int i = 0; i < NodeCount - 1; i++) // for every node we have, the following code will loop through
	{
		for (int j = 0; j < NodeCount - 1; j++) // for every node we have, the following code will loop through every node we have once
		{
			if (NodeArray[j].data == NULL) // if our current node as no data
			{
				if (NodeArray[j + 1].data != NULL) // if our current node has no data but the next node does
				{
					TempNode = NodeArray[j];
					NodeArray[j] = NodeArray[j + 1];
					NodeArray[j + 1] = TempNode;
				}

			}
			else // if the current node has data
			{
				if (NodeArray[j + 1].data != NULL) // if the next node has data too
				{
					// cloning the data for comparison
					char* CurrentNodeData = (char*)NodeArray[j].data;
					char* NextNodeData = (char*)NodeArray[j + 1].data;

					// checking if the asci values are greater for the first character
					if (strncasecmp(CurrentNodeData, NextNodeData, strlen(CurrentNodeData)) > 0) // if the current node is greater in the alphabet, swap
					{
						TempNode = NodeArray[j];
						NodeArray[j] = NodeArray[j + 1];
						NodeArray[j + 1] = TempNode;
					}
				}
			}
		}
	}
	
	return true;
}


bool SortList(bool (*SortMethod) (struct NodeManager*), struct NodeManager* NodeManager)
{
	// error checking passed in NodeManager pointer
	if (NodeManager == NULL)
	{
		fprintf(stderr, "\nNodeManager in SortList Function is NULL\n");
		return false;
	}

	// error checking passed in function pointer
	if (SortMethod == NULL)
	{
		fprintf(stderr, "\nSortMethod in SortList Function is NULL\n");
		return false;
	}

	bool success = SortMethod(NodeManager);
	_RefreshList(NodeManager);
	return success;
}

void _RefreshList (struct NodeManager* NodeManager)
{
	// error checking passed in NodeManager pointer
	if (NodeManager == NULL)
	{
		fprintf(stderr, "\nNodeManager in _RefreshList Function is NULL\n");
	}


	int NodeCount = NodeManager->NodeCount;
	struct Node* NodeArray = NodeManager->NodeArray;

	for (int i = NodeCount - 1; i >= 0; i--)
	{

		if (i == 0) // updating head node
		{
			
			NodeArray[i].position = 0;
			NodeArray[i].prev = &NodeArray[NodeCount - 1];
			NodeArray[i].next = &NodeArray[i + 1];
			NodeManager->head = &NodeArray[i];

		}
		else if (i == NodeCount - 1) // setting the tail node
		{
			NodeArray[i].next = &NodeArray[0];
			NodeArray[i].prev = &NodeArray[i - 1];
			NodeArray[i].position = i;
			NodeManager->tail = &NodeArray[i];
		}
		else // updating all other nodes
		{
			NodeArray[i].next = &NodeArray[i + 1];
			NodeArray[i].prev = &NodeArray[i - 1];
			NodeArray[i].position = i;
		}
	}
}
