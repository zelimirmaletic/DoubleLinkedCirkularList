#include "doubleChainedCircularList.h"
void main(void)
{
	int answer;
	do
	{
		int numberOfProcesses;
		NODE *pHead = 0, *pTail = 0;
		printf("\n*************************************************\n");
		printf("******* P R O C E S S  E X E C U T I O N ********\n");
		printf("*************************************************\n\n");
		do
		{
			printf("Number of processes to execute--->");
			scanf("%d", &numberOfProcesses);
		} while (numberOfProcesses <= 1 || numberOfProcesses > 100);

		loadProcesses(&pHead, &pTail, numberOfProcesses);

		printf("\n --------------LIST OF PROCESSES--------------\n");
		printf("******************\n");
		printf("Name          Time\n");
		printf("******************\n");
		printAll(pHead, pTail);
		printf("******************\n\n");

		int choice;
		do
		{
			printf("What is the order of execution?\n");
			printf("Type [0] for forward, or [1] for backward order.\n");
			scanf("%d", &choice);
		} while (choice != 1 && choice != 0);

		char ans[6];
		do
		{
			printf("Processes are ready for execution!\nType START to begin execution.--->");
			scanf("%s", ans);
		} while (strcmp(ans, "START"));

		printf("\n -----------EXECUTION OF PROCESSES-----------\n");
		printf("********************************************\n");
		printf("Name          Time        Percentage\n");
		printf("********************************************\n");
		if (!choice)
			executeProcessesF(pHead, pTail);
		else
			executeProcessesB(pHead, pTail);
		printf("********************************************\n\n");

		printf("\n*************************************************\n");
		printf("**********%3d BITES OF MEMORY FREED UP!**********\n", (int)(numberOfNodes(pHead, pTail) * sizeof(NODE)));
		printf("*************************************************\n");
		deleteList(&pHead, &pTail);
		printf("\n\n\n\nDo you want to do another execution?Type [0] for exi,\n or anything else do continue!\n");
		printf("Your answer--->"); scanf("%d", &answer);
		printf("\n\n\n\n");
	} while (answer != 0);
	system("PAUSE");
}