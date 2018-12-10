/*   PROCESS MANIPULATION LIBRARY   */

//Libaraies:
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#pragma warning(disable: 4996)

//Defining a PROCESS data type
typedef struct process
{
	char processName[11];
	int  executionTime;//in seconds
}PROCESS;

//Definig NODE data type:
typedef struct node
{
	PROCESS nodeProcess;
	struct node *next;//pointer to next node
	struct node *prev;//pointer to previous node
}NODE;

/*OTHER FUNCTIONS*/
void printAll(NODE *pHead, NODE *pTail)
{
	NODE *tmp = pHead;
	int i = 1;
	do
	{
		printf("%2d.%10s %3ds\n", i++, tmp->nodeProcess.processName, tmp->nodeProcess.executionTime);
		tmp = tmp->next;
	} while (tmp != pHead);
}
int numberOfNodes(NODE *pHead, NODE *pTail)
{
	int counter = 0;
	NODE *tmp = pHead;
	do
	{
		counter++;
		tmp = tmp->next;
	} while (tmp != pHead);
	return counter;
}

/*FUNCTIONS FOR ADING*/

NODE * blankNode(void)//something like default constructor in C++
{
	NODE *newNode = (NODE *)calloc(1, sizeof(NODE));
	return newNode;
}

NODE * addToBegining(NODE ** pHead, NODE ** pTail, PROCESS newProcess)
{
	NODE *newNode = blankNode();
	newNode->nodeProcess = newProcess;
	if (*pHead == 0 && *pTail == 0)
	{
		*pHead = *pTail = newNode;
		newNode->next = newNode->prev = newNode;
	}
	else
	{
		newNode->next = *pHead;
		(*pHead)->prev = newNode;
		*pHead = newNode;
		newNode->prev = *pTail;
		(*pTail)->next = newNode;
	}
	return newNode;
}

NODE * addAtEnd(NODE ** pHead, NODE ** pTail, PROCESS newProcess)
{
	NODE *newNode = blankNode();
	newNode->nodeProcess = newProcess;
	if (*pHead == 0 && *pTail == 0)
	{
		*pHead = *pTail = newNode;
		newNode->next = newNode->prev = newNode;
	}
	else
	{
		newNode->next = *pHead;
		(*pHead)->prev = newNode;
		newNode->prev = *pTail;
		(*pTail)->next = newNode;
		*pTail = newNode;
	}
	return newNode;
}

NODE *addBefore(NODE **pHead, NODE **pTail, NODE *position, PROCESS newProcess)
{
	if (position == *pHead)
		return addToBegining(pHead, pTail, newProcess);
	else if (position == *pTail)
		return addAtEnd(pHead, pTail, newProcess);
	else
	{
		NODE *newNode = blankNode();
		newNode->nodeProcess = newProcess;

		newNode->next = position;
		newNode->prev = position->prev;
		position->prev->next = newNode;
		position->prev = newNode;
		return newNode;
	}
}

NODE *addAfter(NODE **pHead, NODE **pTail, NODE *position, PROCESS newProcess)
{
	if (position == *pHead)
		return addToBegining(pHead, pTail, newProcess);
	else if (position == *pTail)
		return addAtEnd(pHead, pTail, newProcess);
	else
	{
		NODE *newNode = blankNode();
		newNode->nodeProcess = newProcess;

		newNode->next = position->next;
		newNode->prev = position;
		position->next->prev = newNode;
		position->next = newNode;
		return newNode;
	}
}

NODE * addAt(NODE ** pHead, NODE ** pTail, PROCESS newProcess, int position)
{
	int nodesCount = numberOfNodes(*pHead, *pTail);
	if (position > nodesCount + 1 || position < 1)
		return 0;
	else if (position == 1)
		return addToBegining(pHead, pTail, newProcess);
	else if (position == nodesCount || position == nodesCount + 1)
		return addAtEnd(pHead, pTail, newProcess);
	else
	{
		NODE *tmp = *pHead;
		for (int i = 1; i < position; i++)
			tmp = tmp->next;
		return addAfter(pHead, pTail, tmp, newProcess);
	}
}

/*FUNCTIONS FOR DELETING*/
void deleteHead(NODE **pHead, NODE **pTail)
{
	if (*pHead == 0 && *pTail == 0)
		return;
	NODE *tmp = *pHead;
	*pHead = (*pHead)->next;
	(*pHead)->prev = *pTail;
	(*pTail)->next = *pHead;
	free(tmp);
}

void deleteTail(NODE **pHead, NODE **pTail)
{
	if (*pHead == 0 && *pTail == 0)
		return;
	NODE *tmp = *pTail;
	*pTail = (*pTail)->prev;
	(*pTail)->next = *pHead;
	(*pHead)->prev = *pTail;
	free(tmp);
}

void deleteAt(NODE **pHead, NODE  **pTail, NODE *pDelete)
{
	if (*pHead == 0 && *pTail == 0)
		return;
	else if (pDelete == *pHead)
		deleteHead(pHead, pTail);
	else if (pDelete == *pTail)
		deleteTail(pHead, pTail);
	else
	{
		pDelete->next->prev = pDelete->prev;
		pDelete->prev->next = pDelete->next;
		free(pDelete);
	}
}

void deleteNode(NODE **pHead, NODE **pTail, char *key)
{
	if (*pHead == 0 && *pTail == 0)
		return;
	if (!strcmp(key, (*pHead)->nodeProcess.processName))
		deleteHead(pHead, pTail);
	else if (!strcmp(key, (*pTail)->nodeProcess.processName))
		deleteTail(pHead, pTail);
	else
	{
		NODE *tmp = (*pHead)->next;
		do
		{
			if (!strcmp(key, tmp->nodeProcess.processName))
			{
				deleteAt(pHead, pTail, tmp);
				return;
			}
			tmp = tmp->next;
		} while (tmp != *pTail);
	}
}

int deleteList(NODE **pHead, NODE **pTail)
{
	if (*pHead == 0 && *pTail == 0)
		return 0;
	NODE *tmp = *pHead;
	do
	{
		*pHead = tmp->next;
		free(tmp);
	} while (tmp == *pTail);
	*pHead = *pTail = 0;
	return 1;
}
/*
void deleteAllCopies(NODE **pHead, NODE **pTail, char *key)
{
	if (*pHead == 0 && *pTail == 0)
		return;
	if (!strcmp(key, (*pHead)->nodeProcess.processName))
		deleteHead(pHead, pTail);
	else if (!strcmp(key, (*pTail)->nodeProcess.processName))
		deleteTail(pHead, pTail);
	else
	{
		NODE *tmp = (*pHead)->next;
		do
		{
			if (!strcmp(key, tmp->nodeProcess.processName))
			{
				deleteAt(pHead, pTail, tmp);
			}
			tmp = tmp->next;
		} while (tmp != *pTail);
	}
}
*/

/*PROCESS MANIPULATION FUNCTIONS*/
void loadProcesses(NODE **pHead, NODE **pTail, int numberOfProcesses)
{
	printf("-------------PROCESS LOADING---------------\n");
	for (int i = 0; i < numberOfProcesses; i++)
	{
		PROCESS newProcess;
		printf("\t%d.Process:\n",i+1);
		printf("\t\tName: ");
		scanf("%s", newProcess.processName);
		printf("\n");
		printf("\t\tTime: ");
		scanf("%d", &newProcess.executionTime);
		printf("\n");
		addAtEnd(pHead, pTail, newProcess);
	}
}

void executeProcessesF(NODE *pHead, NODE *pTail)
{
	NODE *tmp = pHead;
	int i = 1;
	int timeSum = 0;
	do
	{
		printf("%2d.%10s %3ds", i++, tmp->nodeProcess.processName, tmp->nodeProcess.executionTime);
		timeSum += tmp->nodeProcess.executionTime;
		for (int i = 0; i < tmp->nodeProcess.executionTime; i++)
		{
			printf(".");
			Sleep(1000);
		}
		printf("100%c\n", 37);// printing % sing
		tmp = tmp->next;
	} while (tmp != pHead);
	printf("\n All processes took %ds of time!\n", timeSum);
}

void executeProcessesB(NODE *pHead, NODE *pTail)
{
	NODE *tmp = pTail;
	int i = 1;
	int timeSum = 0;
	do
	{
		printf("%2d.%10s %3ds", i++, tmp->nodeProcess.processName, tmp->nodeProcess.executionTime);
		timeSum += tmp->nodeProcess.executionTime;
		for (int i = 0; i < tmp->nodeProcess.executionTime; i++)
		{
			Sleep(1000);
			printf(".");
		}
		printf("100%c\n",37);
		tmp = tmp->prev;
	} while (tmp != pTail);
	printf("\n All processes took %ds of time!\n", timeSum);
}





