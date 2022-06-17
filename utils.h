//utils.h

#ifndef UTILS_H
#define UTILS_H
#include "common.h"
#include "database.h"
#include <time.h>
#include <unistd.h>

//������־
void mkerrlog(char* errmsg);
//��������Buffer
typedef struct Buffer {
    enum BooleanDef isFail;//�Ƿ�ʧ��
    char* buffer;//������
    int size;//��������С
    enum BooleanDef AsString;//�Ƿ����
}Buffer;
Buffer* readFile(const char* file, enum BooleanDef AsString);
void writeFile(const char* file, Buffer* buffer);
char* getNowTimeString();
int char2int(char* charint, int len);
char* int2char(int num, char* buf);
int StringItem2Int(StringItem* item);
StringItem* Int2StringItem(int i);

void insertListNode(ListNode* nodelink, ListNode* newnode, int index);
void exchangeListNode(ListNode* node1, ListNode* node2);
void rebindListNodeIndex(ListNode* node);
void rebindListNode(ListNode* node);
void deleteListNode(ListNode* node);
ListNode* addListNode(ListNode* tail, carInfoItem* value);
ListNode* getHeadNode(ListNode* nodelink);
ListNode* getTailNode(ListNode* nodelink);
int charcmp(char* chars1, char* chars2, int len);
void freeStringItem(StringItem* item);
void setStringItem(StringItem* item, char* str);
void printCarInfoItem(carInfoItem* item);
void printListNode(ListNode* node);
int StringItemcmp(StringItem* item1, StringItem* item2);
ListNode* creatListNodeByCarInfoItems(carInfoItem** items, int size);
ListNode* creatListNodeByListNodes(ListNode** nodes, int size);
StringItem* trim(char* str, int size);
char* getint(char* str, int* callback_result);
ListNode* shallowCloneListNodes(ListNode* node);
#endif