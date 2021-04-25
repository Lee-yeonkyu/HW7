/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;//이전 노드를 가르키는 포인터
	struct Node* rlink;//이후 노드를 가르키는 포인터
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
        - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {

	if((*h)!= NULL)//h가 공백이 아니라면
			freeList(*h);//할당 해제

	(*h) = (headNode*)malloc(sizeof(headNode));
	(*h)->first=NULL;

	return 1;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

		listNode* last=(listNode*)malloc(sizeof(listNode));
		listNode* New =(listNode*)malloc(sizeof(listNode)); //새로운 노드를 할당해준다.
		New->key=key;
		New->rlink=NULL; //링크 필드는 아직 받지 않았기에 공백 할당.
		New->llink=NULL;

		if(h->first==NULL){ // h가 공백이라면
				h->first=New;
				h->first->llink=h->first;
				return 0;
		}
			last=h->first; //first가 가리키는 값을 last로 놓는다.
			while(last->rlink !=NULL){//last의 r링크가 가리키는 값이 없을때까지 반복해 마지막 노드를 찾는다.
				last=last->rlink;//last노드의 rlink가 가리키는 곳을 last로 바꾼다.
			}
			last->rlink=New; //last의 rlink가 New를 가르키도록 지정한다.
			New->llink=last->rlink->llink; //new의 llink를 last의 다음값의 llink와 같이 바꾼다.
			return 1;
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {


	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode *Node = (listNode *)malloc(sizeof(listNode));
	Node->llink=NULL;
	Node->rlink=NULL;
	Node->key=key;

	if(h->first==NULL){ // h가 공백이라면
		h->first=Node;
		h->first->llink=h->first;
		return 0;}
	else{
		Node->rlink=h->first;
		h->first->llink=Node;
		Node->llink=h->first;
		h->first=Node;}
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode *New=(listNode*)malloc(sizeof(listNode));
	listNode *temp=(listNode*)malloc(sizeof(listNode));
	New->key=key;
	New->llink=NULL;
	New->rlink=NULL;
	temp=h->first;

	if(h->first==NULL){
		h->first=New; // Node를 첫노드로 지정.
		h->first->llink=New; //llink를 자기 자신을 지목
		h->first->rlink=New; //rlink를 자기 자신을 지목
	}
	while((temp->key) < key){//입력받은 키값보다 리스트안의 키값이 클때까지 반복한다.
		if(temp->rlink==NULL){//모든 수보다 입력한 키값이 크다면 마지막에 넣어준다.
			New->llink=temp;
			New->rlink=temp->rlink;
			temp->rlink=New;
			return 0;
		}
		temp=temp->rlink; //temp노드가 가르키는 곳을 temp로 바꾼다.
	}
	if(temp==h->first){
		temp->llink=h->first->llink; // temp의 llink가 first의 이전노드를 가리킨다.
		temp->rlink=h->first; //temp의 rlink는 first를 가리키게 된다.
		h->first->llink=temp; //first의 llink를 새로운 헤더인 temp를 지목하게 한다.
		h->first=temp; //temp를 새로운 첫노드로 지정.
	}
	New->llink=temp->llink;
	temp->llink->rlink=New;
	New->rlink=temp;
	temp->llink=New;

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	return 1;
}

