#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);

int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

    printf("[----- [김상수] [2018038078] -----]");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
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
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
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

	} while(command != 'q' && command != 'Q');

	return 1;
}

/**
 * @brief 
 * 
 * 리스트가 이미 있다면 초기화를 한 후
 * 헤드를 만들어준다.
 * 
 * @param h 
 * @return int 
 */
int initialize(listNode** h) {

	if(*h != NULL)
		freeList(*h);

	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/**
 * @brief 
 * 
 * 다음 값이 자기 자신을 가리키고 있으면 헤드만 초기화를 해주고
 * 아니라면 다음값이 널 또는 헤드가 아닐때까지 넘어가면서 할당해제해준다.
 * 
 * @param h 
 * @return int 
 */
int freeList(listNode* h){

	if(h->rlink == h)
	{
		free(h);
		return 1;
	}

	listNode* p = h->rlink;

	listNode* prev = NULL;
	while(p != NULL && p != h) {
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);
	return 0;
}


/**
 * @brief 
 * 
 * 비어있는지 확인을 하고 아니라면
 * 마찬가지로 다음 값이 널이거나 헤드가 아닐 경우까지 노드의 값을 출력한다.
 * 이후 노드가 메모리에서 어떻게 배치되어 있는지 확인하기 위해 각 노드의 주소를 출력해준다.
 * 
 * @param h 
 */
void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);

	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}

/**
 * @brief 
 * 
 * 넣을 값이 들어있는 노드를 만들어주고
 * 리스트가 비어있는지 확인한 다음 비어있다면
 *  첫 노드로써 넣어주고 아니라면
 *  마지막 노드 뒤에 새 노드를 추가한다.
 * 
 * @param h 
 * @param key 
 * @return int 
 */
int insertLast(listNode* h, int key) {

	if (h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->rlink == h)
	{
		h->rlink = node;
		h->llink = node;
		node->rlink = h;
		node->llink = h;
	} else {
		h->llink->rlink = node;
		node->llink = h->llink;
		h->llink = node;
		node->rlink = h;
	}

	return 1;
}

/**
 * @brief 
 * 
 * 비어있으면 없다고 알리고 함수를 종료 한다.
 * 아니라면 마지막 노드를 삭제하고 삭제 전 마지막 노드의 이전 노드와 헤드 노드를 연결한다.
 * 
 * @param h 
 * @return int 
 */
int deleteLast(listNode* h) {

	if (h->llink == h || h == NULL)
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* nodetoremove = h->llink;

	nodetoremove->llink->rlink = h;
	h->llink = nodetoremove->llink;

	free(nodetoremove);

	return 1;
}

/**
 * @brief 
 * 
 * 새 노드를 만들어준다.
 * 첫 노드를 새 노드의 다음으로, 헤드를 새노드로 만들어준다.
 * 
 * @param h 
 * @param key 
 * @return int 
 */
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;


	node->rlink = h->rlink;
	h->rlink->llink = node;
	node->llink = h;
	h->rlink = node;


	return 1;
}


/**
 * @brief 
 * 
 * 비어있는지 체크를 한다.
 * 두번 째 노드를 첫번째 노드 역할로 만든 다음에 첫번째 노드를 삭제한다.
 * 
 * @param h 
 * @return int 
 */
int deleteFirst(listNode* h) {

	if (h == NULL || h->rlink == h)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* nodetoremove = h->rlink;

	nodetoremove->rlink->llink = h;
	h->rlink = nodetoremove->rlink;

	free(nodetoremove);

	return 1;

}

/**
 * @brief 
 * 
 * 노드를 하나하나 옮기면서
 * 각 노드의 왼쪽과 오른쪽을 바꿔준다.
 * 
 * @param h 
 * @return int 
 */
int invertList(listNode* h) {

	if(h->rlink == h || h == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink;
	listNode *trail = h;
	listNode *middle = h;

	h->llink = h->rlink;

	while(n != NULL && n != h){
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	h->rlink = middle;

	return 0;
}

/**
 * @brief 
 * 
 * 리스트가 비어있지 않다면, 새 노드를 생성하고 주어진 키 값을 할당하고
 * 그리고 리스트를 순회하면서 적절한 위치에 새 노드를 삽입한다.
 * 만약 리스트가 비어 있거나 새 노드의 키 값이 리스트의 모든 노드의 키 값보다 작다면, 새 노드는 리스트의 맨 앞에 삽입.
 * 그 외의 경우에는, 새 노드의 키 값이 기존 노드의 키 값보다 크거나 같은 첫 번째 위치에 삽입된다.
 * 
 * @param h 
 * @param key 
 * @return int 
 */
int insertNode(listNode* h, int key) {

	if(h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	if (h->rlink == h)
	{
		insertFirst(h, key);
		return 1;
	}

	listNode* n = h->rlink;

	while(n != NULL && n != h) {
		if(n->key >= key) {
			if(n == h->rlink) {
				insertFirst(h, key);
			} else { 
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
				n->llink = node;
			}
			return 0;
		}

		n = n->rlink;
	}

	insertLast(h, key);
	return 0;
}

/**
 * @brief 
 * 
 * 리스트를 순회하면서 주어진 키 값을 가지는 노드를 검색.
 * 해당 노드를 찾으면, 그 노드를 리스트에서 제거하고 메모리를 해제.
 * 만약 해당 노드를 찾지 못한다면, 해당 키 값을 가지는 노드가 없다는 메시지를 출력.
 * 
 * @param h 
 * @param key 
 * @return int 
 */
int deleteNode(listNode* h, int key) {

	if (h->rlink == h || h == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink;

	while(n != NULL && n != h) {
		if(n->key == key) {
			if(n == h->rlink) {
				deleteFirst(h);
			} else if (n->rlink == h){
				deleteLast(h);
			} else {
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n);
			}
			return 0;
		}

		n = n->rlink;
	}

	printf("cannot find the node for key = %d\n", key);
	return 0;
}
