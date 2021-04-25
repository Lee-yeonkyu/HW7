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
	
	printf("[----- [이연규] [2018038038] -----]\n\n\n");
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

	(*h) = (headNode*)malloc(sizeof(headNode)); //헤더노드 메모리 할당.
	(*h)->first=NULL; // 초기화

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
		while(last->rlink !=NULL)//last의 r링크가 가리키는 값이 없을때까지 반복해 마지막 노드를 찾는다.
			last=last->rlink;//last노드의 rlink가 가리키는 곳을 last로 바꾼다.

		last->rlink=New; //last의 rlink가 New를 가르키도록 지정한다.
		New->llink=last->rlink->llink; //new의 llink를 last의 다음값의 llink와 같이 바꾼다.
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	listNode *del;
	listNode *pre;

	pre=h->first; // 삭제할 노드의 앞의 노드를 첫번째로 지정.
	del=h->first->rlink; //삭제할 노드를 두번째로 지정.
	if(h->first==NULL) return -1; //빈노드면 종료.
	if(h->first->rlink==NULL) { //노드가 한개라면
		free(h->first); //그 노드의 할당 해제.
		h->first=NULL;
		return 0;
	}
	else{
		while(del->rlink !=NULL){//노드를 끝까지 반복한다.
			pre=del; //pre에 del값을 넣어준다.
			del=del->rlink; // del의 r링크가 가르키는 값으로 del을 바꿔준다.
		}
		free(del); //del을 할당 해제해준다.
		pre->rlink=NULL;
	}
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
		h->first=Node; //first가 노드를 가리키게 한다.
		h->first->llink=h->first;
		return 0;}
	else{
		Node->rlink=h->first; //노드의 rlink가 first를 가리키게한다.
		h->first->llink=Node; //first의 llink가 node를 가리키게 한다.
		Node->llink=NULL;
		h->first=Node;} //node를 first로 지정해준다.
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode *del;
	if(h->first==NULL) {return 0;}  // 공백일시 함수 나간다.
	del=h->first;//first가 del을 가르키게한다.
	h->first=h->first->rlink; //first가 first의 링크값을 가르키도록 지정.
	free(del); //del 할당해제

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	listNode *p,*q,*r;

		if(h->first==NULL){return 0;}
		p=h->first; //p는 현재 가리키는 노드 , q는 이전 노드
		q=NULL;
		while(p!=NULL)
		{
			r=q;		//r은 q, q는 p를 차례로 따라간다.

			q=p;
			p=p->rlink; // p를 미리 옮겨놓고
			q->rlink=r; //q의 링크의 방형을 바꿔준다.
		}
		h->first=q; // q는 역순으로 되있는 리스트의 헤드 포인터.
		return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode *New=(listNode*)malloc(sizeof(listNode));
	listNode *temp=(listNode*)malloc(sizeof(listNode));
	listNode *pre=(listNode*)malloc(sizeof(listNode));
	New->key=key;
	New->llink=NULL;	New->rlink=NULL;
	pre->llink=NULL;	pre->rlink=NULL;
	temp=h->first;

	if(h->first==NULL){ // h가 공백이라면
			h->first=New;//first가 new를 가리킨다.
			h->first->llink=h->first; //first의 llink가 자기 자신을 가리킨다.
			return 0;}
	while((temp->key) < key){//입력받은 키값보다 리스트안의 키값이 클때까지 반복한다.
		if(temp->rlink==NULL){//모든 수보다 입력한 키값이 크다면 마지막에 넣어준다.
			temp->rlink=New; //last의 rlink가 New를 가르키도록 지정한다.
			New->llink=temp->rlink->llink; //new의 llink를 last의 다음값의 llink와 같이 바꾼다.
			return 0;
		}
		pre=temp; //temp를 pre에 복사.
		temp=temp->rlink; //temp노드가 가르키는 곳을 temp로 바꾼다.
	}
	if(pre->rlink==NULL){
		New->rlink=h->first; //fisrt가 가리키는 곳을 New의rlink도 가리키게한다.
		h->first->llink=New; //first의 llink가 New를 가리키게 한다.
		New->llink=NULL; //New의 llink를 없애주고.
		h->first=New;//first가 New를 가리키게 한다.
		return 0;
	}
	New->rlink=pre->rlink;//New의 rlink값을 pre의 rlink값과 같게한다.
	New->llink=pre; //New의 llink로 pre를 가리킨다.
	pre->rlink->llink=New;//pre의 다음값의 llink로 New를 가리킨다.
	pre->rlink=New; // pre의 다음값으로 New를 지정한다.
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	listNode *find =(listNode*)malloc(sizeof(listNode));
	listNode *pre =(listNode*)malloc(sizeof(listNode));
	listNode *del;
	pre->rlink=NULL;
	find=h->first; // first가 가르키는 값을 find로 놓는다.

	while(find->key !=key){//find의 키값과 같은 값이 나올때까지 반복해 원하는 노드를 찾는다.
		pre=find;//find값을 pre에 넣어준다.
		if(find->rlink==NULL) return 0; //모든 값이 다른경우 함수에서 나간다.
		del=find->rlink;//find가 가르키는 곳을 del이 가르키게 한다.
		find=find->rlink;//find노드가 가르키는 곳을 find로 바꾼다.
		}
	if(pre->rlink == NULL) h->first=h->first->rlink; // 첫번째 키가 같다면 첫번째 노드를 없애준다.
	pre->rlink=find->rlink; //find가 가르키고있는 값을 pre가 가르킨다.
	free(del);

		return 0;
}


