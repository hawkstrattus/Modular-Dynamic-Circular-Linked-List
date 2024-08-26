/*
This was testing I did inside the C source file while I was building the program. Attached it to the end of the C source file and compile for output or add the code to a program where you have included libMDCL.
Also, these can serve as examples on how to use the program. This document is pretty much garbage, but just incase someone finds it useful, it's here.
*/

int main()
{

	struct NodeManager* List1Manager = CreateList(10, "List1");
	if (List1Manager == NULL)
	{
		printf("NULLLLL");
	}
	unsigned long long meh = 323;
	char string1[13] = "lel";
	char string2[13] = "ads";
	char string3[13] = "acs";
	SetNodeData(List1Manager, 2, &meh);

	struct Node* found = FindNodeData(List1Manager, &meh, sizeof(meh));
	printf("\n%d\n", found->position);
	printf("Data for 2 is: %d\n", *(int*)List1Manager->NodeArray[2].data);
	struct Node* NewEnd = InsertNodeAtEnd(List1Manager);
	printf("Data for 2 is: %d\n", *(int*)List1Manager->NodeArray[2].data);
	struct Node* NewBeg = InsertNodeAtBeginning(List1Manager);
	printf("Data for 3 is: %d\n", *(int*)List1Manager->NodeArray[3].data);
	struct Node* NewPos = InsertNodeAtPosition(List1Manager, 4);
	printf("Data for 4 is: %d\n", *(int*)List1Manager->NodeArray[3].data);
	printf("Position NewEnd is %d\n", NewEnd->position);
	printf("Position NewBeg is %d\n", NewBeg->position);
	printf("Position NewPos is %d\n", NewPos->position);
	DeleteNodeAtEnd(List1Manager);
	printf("Data for 3 is: %d\n", *(int*)List1Manager->NodeArray[3].data);
	DeleteNodeAtBeginning(List1Manager);
	printf("Data for 2 is: %d\n", *(int*)List1Manager->NodeArray[2].data);
	DeleteNodeAtPosition(List1Manager, 1);
	printf("Data for 1 is: %d\n", *(int*)List1Manager->NodeArray[1].data);
	DeleteNodeAtPosition(List1Manager, 2);
	printf("Data for 1 is: %d\n", *(int*)List1Manager->NodeArray[1].data);
	InsertNodeAtPosition(List1Manager, 0);
	printf("Data for 2 is: %d\n", *(int*)List1Manager->NodeArray[2].data);

	SortList(AlphaSort, List1Manager); 

	printf("ListID is: %s\n", List1Manager->ListID);	
	printf("NodeCount is: %d\n", List1Manager->NodeCount);
	printf("Head (NodeManager) is: %d\n", List1Manager->head->position);
	printf("Tail (NodeManager) is: %d\n", List1Manager->tail->position);
	printf("Position 0 is %d\n", List1Manager->NodeArray[0].position);
	printf("Position 0 (tail) is %d\n", List1Manager->NodeArray[10].next->position);
	printf("Position 0 (prev) is %d\n", List1Manager->NodeArray[1].prev->position);
	printf("Position 1 is %d\n", List1Manager->NodeArray[1].position);
	printf("Position 1 (next) is %d\n", List1Manager->NodeArray[0].next->position);
	printf("Position 1 (prev) is %d\n", List1Manager->NodeArray[2].prev->position);
	printf("Position 2 is %d\n", List1Manager->NodeArray[2].position);
	printf("Position 2 (next) is %d\n", List1Manager->NodeArray[1].next->position);
	printf("Position 2 (prev) is %d\n", List1Manager->NodeArray[3].prev->position);
	printf("Position 3 is %d\n", List1Manager->NodeArray[3].position);
	printf("Position 3 (next) is %d\n", List1Manager->NodeArray[2].next->position);
	printf("Position 3 (prev) is %d\n", List1Manager->NodeArray[4].prev->position);
	printf("Position 4 is %d\n", List1Manager->NodeArray[4].position);
	printf("Position 4 (next) is %d\n", List1Manager->NodeArray[3].next->position);
	printf("Position 4 (prev) is %d\n", List1Manager->NodeArray[5].prev->position);
	printf("Position 5 is %d\n", List1Manager->NodeArray[5].position);
	printf("Position 5 (next) is %d\n", List1Manager->NodeArray[4].next->position);
	printf("Position 5 (prev) is %d\n", List1Manager->NodeArray[6].prev->position);
	printf("Position 6 is %d\n", List1Manager->NodeArray[6].position);
	printf("Position 6 (next) is %d\n", List1Manager->NodeArray[5].next->position);
	printf("Position 6 (prev) is %d\n", List1Manager->NodeArray[7].prev->position);
	printf("Position 7 is %d\n", List1Manager->NodeArray[7].position);
	printf("Position 7 (next) is %d\n", List1Manager->NodeArray[6].next->position);
	printf("Position 7 (prev) is %d\n", List1Manager->NodeArray[8].prev->position);
	printf("Position 8 is %d\n", List1Manager->NodeArray[8].position);
	printf("Position 8 (next) is %d\n", List1Manager->NodeArray[7].next->position);
	printf("Position 8 (prev) is %d\n", List1Manager->NodeArray[9].prev->position);
	printf("Position 9 is %d\n", List1Manager->NodeArray[9].position);
	printf("Position 9 (next) is %d\n", List1Manager->NodeArray[8].next->position);
	printf("Position 9 (prev) is %d\n", List1Manager->NodeArray[10].prev->position);
	printf("Position 10 is %d\n", List1Manager->NodeArray[10].position);
	printf("Position 10 (next) is %d\n", List1Manager->NodeArray[9].next->position);
	printf("Position 10 (prev) is %d\n", List1Manager->NodeArray[0].prev->position);

	SetNodeData(List1Manager, 4, &string1);
	SetNodeData(List1Manager, 2, &string2);
	SetNodeData(List1Manager, 8, &string3);
	SetNodeData(List1Manager, 1, &meh);
	SortList(AlphaSort, List1Manager); // add more stuff and do more testing
	printf("Data for 0 is: %s\n", (char*)List1Manager->NodeArray[0].data);
	printf("Data for 1 is: %s\n", (char*)List1Manager->NodeArray[1].data);
	printf("Data for 2 is: %d\n", *(int*)List1Manager->NodeArray[2].data);
	printf("Data for 3 is: %s\n", (char*)List1Manager->NodeArray[3].data);


	return 0;
}
