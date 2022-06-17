#include "utils.h"

char* getNowTimeString() {
    typedef struct loguse_Time_YMD_HMS {
        int year;
        int month;
        int day;
        int hour;
        int minute;
        int second;
    }loguse_Time_YMD_HMS;
    loguse_Time_YMD_HMS* curDate = (loguse_Time_YMD_HMS*)malloc(sizeof(loguse_Time_YMD_HMS));
    memset(curDate, 0, sizeof(loguse_Time_YMD_HMS));
    char* timeBuf = (char*)malloc(sizeof(char) * 200);
    time_t now;
    struct tm* timeNow;
    time(&now);
    timeNow = localtime(&now);
    curDate->year = timeNow->tm_year + 1900;
    curDate->month = timeNow->tm_mon + 1;
    curDate->day = timeNow->tm_mday;
    curDate->hour = timeNow->tm_hour;
    curDate->minute = timeNow->tm_min;
    curDate->second = timeNow->tm_sec;
    // yyyy-MM-dd HH:mm:ss
    if (curDate->second < 10)
        sprintf(timeBuf, "%d-%d-%d %d:%d:0%d", curDate->year, curDate->month, curDate->day,
                                curDate->hour, curDate->minute, curDate->second);
    else
        sprintf(timeBuf, "%d-%d-%d %d:%d:%d", curDate->year, curDate->month, curDate->day,
                                curDate->hour, curDate->minute, curDate->second);
    free(curDate);
    return timeBuf;
}
//打日志（顺便append日志）
void mkerrlog(char* errmsg) {
    printf("%s\n", errmsg);
    FILE* fp;
    char* logfile = "errlog.txt";
    fp = fopen(logfile, "a");
    if (fp == NULL) {
        //mkerrlog里别mkerrlog了
        printf("当前状态不支持错误日志，请检查errlog.txt读写情况和程序权限！\n");
        return;
    }
    char* t = getNowTimeString();
    fprintf(fp, "\n<%s TK_START>\n%s\n<%s TK_END>\n", t, errmsg, t);
    free(t);
    fclose(fp);
}
Buffer* readFile(const char* file, enum BooleanDef AsString) {
    Buffer* buffer = (Buffer*)malloc(sizeof(Buffer));
    buffer->buffer = NULL;
    buffer->size = 0;
    buffer->isFail = 0;
    FILE* fp = fopen(file, "rb");
    if (fp == NULL) {
        buffer->isFail = 1;
        char* errmsg = malloc(sizeof(char) * 200 + strlen(file));
        memset(errmsg, 0, sizeof(char) * 200 + strlen(file));
        sprintf(errmsg, "文件 %s 打开失败！", file);
        mkerrlog(errmsg);
        free(errmsg);
        return buffer;
    }
    fseek(fp, 0, SEEK_END);
    buffer->size = ftell(fp);
    if (AsString == Boolean_TRUE) {
        buffer->size++;
    }
    fseek(fp, 0, SEEK_SET);
    buffer->buffer = (char*)malloc(buffer->size);
    fread(buffer->buffer, sizeof(char), buffer->size, fp);
    fclose(fp);
    if (AsString == Boolean_TRUE) {
        buffer->buffer[buffer->size - 1] = '\0';
    }
    return buffer;
}
void writeFile(const char* file, Buffer* buffer) {
    FILE* fp = fopen(file, "w");
    if (fp == NULL) {
        char* errmsg = malloc(sizeof(char) * 200 + strlen(file));
        memset(errmsg, 0, sizeof(char) * 200 + strlen(file));
        sprintf(errmsg, "文件 %s 打开失败！", file);
        mkerrlog(errmsg);
        free(errmsg);
        return;
    }
    if (buffer->AsString == Boolean_TRUE) {
        fwrite(buffer->buffer, buffer->size - 1, 1, fp);
    } else {
        fwrite(buffer->buffer, buffer->size, 1, fp);
    }
    fclose(fp);
}
//int2binchar
char* int2char(int num, char* buf) {
    if (buf == NULL) {
        if (sizeof(int) == 4) {
            char charint[4] = { 0 };
            buf = charint;
        } else {
            char charint[8] = { 0 };
            buf = charint;
        }
    }
    if (sizeof(int) == 4) {
        memcpy(buf, (char*)&num, 4);
    } else {
        memcpy(buf, (char*)&num, 8);
    }
    return buf;
}
//binchar2int
int char2int(char* charint, int len) {
    if (len == 4) {
        if (sizeof(int) == 4) {
            char intbuf[4] = { 0 };
            memcpy(intbuf, charint, 4);
            int num = *((int*)intbuf);
            return num;
        }
        char intbuf[8] = { 0 };
        memcpy(intbuf, charint, 4);
        int num = *((int*)intbuf);
        return num;
    } else {
        if (sizeof(int) == 4) {//超长情况放弃了，如果不长，后头都是0
            char intbuf[4] = { 0 };
            memcpy(intbuf, charint, 4);
            int num = *((int*)intbuf);
            return num;
        }
        char intbuf[8] = { 0 };
        memcpy(intbuf, charint, 8);
        int num = *((int*)intbuf);
        return num;
    }
}
StringItem* Int2StringItem(int i) {
    StringItem* item = (StringItem*)malloc(sizeof(StringItem));
    item->str = (char*)malloc(sizeof(char) * 10);
    memset(item->str, 0, sizeof(char) * 10);
    sprintf(item->str, "%d", i);
    item->size = 10;
    return item;
}
int StringItem2Int(StringItem* item) {
    if (item == NULL) {
        mkerrlog("StringItem2Int:StringItem*==NULL！");
        return 0;
    }
    int n = 0;
    sscanf(item->str, "%d", &n);
    return n;
}
ListNode* getTailNode(ListNode* nodelink) {
    if (nodelink == NULL) {
        mkerrlog("getTailNode:存在空节点！");
        return NULL;
    }
    ListNode* tail = nodelink;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    return tail;
}
ListNode* getHeadNode(ListNode* nodelink) {
    if (nodelink == NULL) {
        mkerrlog("getHeadNode:存在空节点！");
        return NULL;
    }
    ListNode* head = nodelink;
    while (head->prev != NULL) {
        head = head->prev;
    }
    return head;
}
ListNode* addListNode(ListNode* tail, carInfoItem* value) {
    if (value == NULL) {
        mkerrlog("addListNode:carInfoItem*==NULL！");
        return NULL;
    }
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    if (tail == NULL) {//head
        node->index = 1;
    } else {
        node->index = tail->index + 1;
    }
    node->value = value;
    node->next = NULL;
    node->prev = NULL;
    if (tail == NULL) {//head不用折腾
        return node;
    }
    //前后绑定
    tail->next = node;
    node->prev = tail;
    return node;
}
//删除节点
void deleteListNode(ListNode* node) {
    if (node == NULL) {
        mkerrlog("deleteListNode:存在空节点！");
        return;
    }
    //前后绑定
    if (node->prev != NULL) {
        node->prev->next = node->next;
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
    //index重置
    if (node->next != NULL) {
        ListNode* curnode = node->next;
        while (curnode != NULL) {
            curnode->index = curnode->index - 1;
            curnode = curnode->next;
        }
    }
    //释放内存(突然有点后悔分层了)
    freeStringItem(node->value->info->carBrand);
    freeStringItem(node->value->info->carModel);
    freeStringItem(node->value->info->fault->faultDescribe);
    free(node->value->info->fault);
    free(node->value->info);
    free(node->value->order->date);
    freeStringItem(node->value->order->seller->name);
    freeStringItem(node->value->order->seller->phone);
    free(node->value->order->seller);
    freeStringItem(node->value->order->buyer->name);
    freeStringItem(node->value->order->buyer->phone);
    free(node->value->order->buyer);
    freeStringItem(node->value->order->handler->name);
    freeStringItem(node->value->order->handler->phone);
    free(node->value->order->handler);
    freeStringItem(node->value->order->employee->name);
    freeStringItem(node->value->order->employee->phone);
    free(node->value->order->employee);
    free(node->value->order);
    free(node);
}
//重新矫正绑定（传入任意一个就可以矫正，前提是可以正确获取到head）
void rebindListNode(ListNode* node) {
    if (node == NULL) {
        mkerrlog("rebindListNode:存在空节点！");
        return;
    }
    ListNode* head = getHeadNode(node);
    ListNode* curnode = head;
    ListNode* tmp;
    int index = 1;
    while (curnode != NULL) {
        curnode->index = index;//重新绑定index
        tmp = curnode->next;
        if (tmp == NULL) {
            curnode->next = NULL;
        } else {
            curnode->next->prev = curnode;//重新绑定前后绑定
        }
        curnode = tmp;
        index++;
    }
}
void rebindListNodeIndex(ListNode* node) {
    if (node == NULL) {
        mkerrlog("rebindListNodeIndex:存在空节点！");
        return;
    }
    ListNode* head = getHeadNode(node);
    ListNode* curnode = head;
    int index = 1;
    while (curnode != NULL) {
        curnode->index = index;//重新绑定index
        curnode = curnode->next;
        index++;
    }
}
//交换两个节点
void exchangeListNode(ListNode* node1, ListNode* node2) {
    if (node1 == NULL || node2 == NULL) {//如果有一个为空，则不交换
        mkerrlog("exchangeListNode:存在空节点！");
        return;
    }
    int indexOf1 = node1->index;
    int indexOf2 = node2->index;
    if (indexOf1 == indexOf2) {//相同节点
        return;
    }
    if (indexOf1 > indexOf2) {//保证前小后大
        int tmp = indexOf1;
        indexOf1 = indexOf2;
        indexOf2 = tmp;
        ListNode* tmpnode = node1;
        node1 = node2;
        node2 = tmpnode;
    }
    //交换绑定
    ListNode* tmpnode1 = node1->prev;
    ListNode* tmpnode2 = node1->next;
    ListNode* tmpnode3 = node2->prev;
    ListNode* tmpnode4 = node2->next;
    node2->prev = tmpnode1;
    if (tmpnode1 != NULL) {
        tmpnode1->next = node2;
    }
    node2->next = tmpnode2;
    if (tmpnode2 != NULL) {
        tmpnode2->prev = node2;
    }
    node1->prev = tmpnode3;
    if (tmpnode3 != NULL) {
        tmpnode3->next = node1;
    }
    node1->next = tmpnode4;
    if (tmpnode4 != NULL) {
        tmpnode4->prev = node1;
    }
    rebindListNodeIndex(node1);//矫正绑定index
}
//index=0:head
//index=-1:tail
//遵循负数倒叙原则
//如果index超出长度，报错
void insertListNode(ListNode* nodelink, ListNode* newnode, int index) {
    if (nodelink == NULL || newnode == NULL) {//如果为空，则插入到头部
        mkerrlog("insertListNode:待插入的节点或者原节点链表为空！");
        return;
    }
    ListNode* tmp;
    int count = 0;
    int flagok = 0;
    if (index < 0) {//如果是尾部插入
        ListNode* tail = getTailNode(nodelink);
        if (index == -1) {//尾部
            newnode->next = NULL;
            newnode->prev = tail;
            tail->next = newnode;
        } else {
            tmp = tail;
            //负向索引是从1开始的
            while (tmp != NULL) {
                count++;
                if (-count == index) {
                    //交换绑定
                    if (tmp->prev == NULL) {//head
                        newnode->prev = NULL;
                        newnode->next = tmp;
                        tmp->prev = newnode;
                    } else {
                        newnode->prev = tmp->prev;
                        newnode->next = tmp;
                        tmp->prev->next = newnode;
                        tmp->prev = newnode;
                    }
                    flagok = 1;
                    break;
                }
                tmp = tmp->next;
            }
            if (flagok == 0) {
                char* errmsg = malloc(sizeof(char) * 200);
                memset(errmsg, 0, sizeof(char) * 200);
                sprintf(errmsg, "insertListNode:插入的位置(%d)超出链表长度！", index);
                mkerrlog(errmsg);
                free(errmsg);
                return;
            }
        }
    } else {
        ListNode* head = getHeadNode(nodelink);
        if (index == 0) {//头部
            newnode->prev = NULL;
            newnode->next = head;
            head->prev = newnode;
        } else {
            tmp = head;
            count--;//正向索引是从0开始的
            while (tmp != NULL) {
                count++;
                if (count == index) {
                    //交换绑定
                    if (tmp->next == NULL) {//tail
                        newnode->next = NULL;
                        newnode->prev = tmp;
                        tmp->next = newnode;
                    } else {
                        newnode->prev = tmp;
                        newnode->next = tmp->next;
                        tmp->next->prev = newnode;
                        tmp->next = newnode;
                    }
                    flagok = 1;
                    break;
                }
                tmp = tmp->next;
            }
            if (flagok == 0) {
                char* errmsg = malloc(sizeof(char) * 200);
                memset(errmsg, 0, sizeof(char) * 200);
                sprintf(errmsg, "insertListNode:插入的位置(%d)超出链表长度！", index);
                mkerrlog(errmsg);
                free(errmsg);
                return;
            }

        }
    }
    rebindListNodeIndex(nodelink);
}
int charcmp(char* chars1, char* chars2, int len) {
    if (chars1 == NULL || chars2 == NULL) {
        return 0;
    }
    int i = 0;
    for (i = 0; i < len; i++) {
        if (chars1[i] != chars2[i]) {
            return 1;
        }
    }
    return 0;
}
void freeStringItem(StringItem* item) {
    if (item == NULL) {
        return;
    }
    if (item->str != NULL) {
        free(item->str);
    }
    free(item);
}
void setStringItem(StringItem* item, char* str) {
    if (item == NULL) {
        mkerrlog("setStringItem:待修改的字符串为空！");
        return;
    }
    if (item->str != NULL) {
        free(item->str);
    }
    int len = strlen(str);
    item->str = malloc(sizeof(char) * (len + 1));
    memcpy(item->str, str, len);
    item->str[len] = '\0';
    item->size = len + 1;
}
void printCarInfoItem(carInfoItem* item) {
    if (item == NULL) {
        mkerrlog("printCarInfoItem:carInfoItem*==NULL！");
        return;
    }
    printf("车辆编号:%d\n", item->info->carId);
    printf("车辆品牌:%s\n", item->info->carBrand->str);
    printf("车辆型号:%s\n", item->info->carModel->str);
    printf("原价:%d\n", item->info->carPrice);
    printf("车龄:%d\n", item->info->carAge);
    printf("是否有大修:%s\n", item->info->fault->hasRepair == Boolean_TRUE ? "是" : "否");
    printf("是否有故障:%s\n", item->info->fault->hasFault == Boolean_TRUE ? "是" : "否");
    printf("故障描述:%s\n", item->info->fault->faultDescribe->str);
    printf("状态:%s\n", item->order->status == carStatus_inStock ? "入库" :
    (item->order->status == carStatus_outStock ? "出库" :
        (item->order->status == carStatus_reserved ? "预定" :
            (item->order->status == carStatus_sold ? "已售" : "未知"))));
    printf("日期:%d/%d/%d\n", item->order->date->year, item->order->date->month, item->order->date->day);
    printf("进价:%d\n", item->order->inPrice);
    printf("销售价:%d\n", item->order->outPrice);
    printf("估计价:%d\n", item->order->estimatePrice);
    if (item->order->realPrice == -1) {
        printf("实售价:未售（未知）\n");
    } else {
        printf("实售价:%d\n", item->order->realPrice);
    }
    printf("卖家:\n");
    // printf("类型:%d\n", item->order->seller->type);
    printf("姓名:%s\n", item->order->seller->name->str);
    printf("电话:%s\n", item->order->seller->phone->str);
    printf("买家:\n");
    // printf("类型:%d\n", item->order->buyer->type);
    printf("姓名:%s\n", item->order->buyer->name->str);
    printf("电话:%s\n", item->order->buyer->phone->str);
    printf("经手人:\n");
    // printf("类型:%d\n", item->order->handler->type);
    printf("姓名:%s\n", item->order->handler->name->str);
    printf("电话:%s\n", item->order->handler->phone->str);
    printf("员工:\n");
    // printf("类型:%d\n", item->order->employee->type);
    printf("姓名:%s\n", item->order->employee->name->str);
    printf("员工编号:%d\n", item->order->employee->id);
}
void printListNode(ListNode* node) {
    if (node == NULL) {
        mkerrlog("printListNode:ListNode*==NULL！");
        return;
    }
    printf("node addr is %d\n", node);
    printf("node index is %d\n", node->index);
    printf("node value addr is %d\n", node->value);
    printf("node prev addr is %d\n", node->prev);
    printf("node next addr is %d\n", node->next);
    printCarInfoItem(node->value);
}
int StringItemcmp(StringItem* item1, StringItem* item2) {
    if (item1 == NULL || item2 == NULL) {
        return 0;
    }
    if (item1->size != item2->size) {
        return 1;
    }
    return charcmp(item1->str, item2->str, item1->size);
}
ListNode* creatListNodeByCarInfoItems(carInfoItem** items, int size) {
    if (size == 0) {//这种情况是上一步没结果导致的（不是错误）
        return NULL;
    }
    if (items == NULL) {
        mkerrlog("creatListNodeByCarInfoItems:carInfoItem**==NULL");
        return NULL;
    }
    ListNode* head = NULL;
    ListNode* tail = NULL;
    int i = 0;
    for (i = 0; i < size; i++) {
        tail = addListNode(tail, items[i]);
        if (i == 0) {
            head = tail;
        }
    }
    rebindListNode(head);
    return head;
}
ListNode* creatListNodeByListNodes(ListNode** nodes, int size) {
    if (nodes == NULL) {
        mkerrlog("creatListNodeByListNodes:nodes**==NULL");
        return NULL;
    }
    int i = 0;
    for (i = 0; i < size; i++) {
        nodes[i]->index = i + 1;
        nodes[i]->prev = NULL;
        nodes[i]->next = NULL;
        if (i != 0) {
            nodes[i]->prev = nodes[i - 1];
        }
        if (i != size - 1) {
            nodes[i]->next = nodes[i + 1];
        }
    }
    rebindListNode(nodes[0]);
    return nodes[0];
}
StringItem* trim(char* str, int size) {
    if (str == NULL) {
        mkerrlog("trim:没有传入字符串！");
        return NULL;
    }
    int i;
    int offset;
    for (offset = 0; offset < size; offset++) {
        if (str[offset] != ' ') {
            break;
        }
    }
    for (i = size - 1; i >= 0; i--) {
        if (str[i] != ' ') {
            break;
        }
    }
    if (i < offset) {
        return NULL;
    }
    StringItem* item = (StringItem*)malloc(sizeof(StringItem));
    item->size = i - offset + 2;
    item->str = (char*)malloc(item->size);
    memcpy(item->str, str + offset, item->size);
    item->str[item->size - 1] = '\0';
    return item;
}
//无限深度读取int
#define isNum_getint(c) ((c >= '0' && c <= '9')||(c == '-'))
char* getint(char* str, int* callback_result) {
    if (str == NULL) {
        mkerrlog("getint:没有传入字符串！");
        return NULL;
    }
    if (callback_result == NULL) {
        mkerrlog("getint:callback_result==NULL！");
        return NULL;
    }
    int i = 0;
    int size = strlen(str);
    int isNegative = 0;
    int Num = 0;
    for (i = 0; i < size; i++) {
        if (isNum_getint(str[i])) {
            if (str[i] == '-') {
                isNegative = 1;
            }
            Num = Num * 10 + (str[i] - '0');
        } else {
            while (i < size && !isNum_getint(str[i])) {
                i++;
            }
            break;
        }
    }
    if (isNegative) {
        *callback_result = -Num;
    } else {
        *callback_result = Num;
    }
    if (i == size) {
        return NULL;
    }
    return str + i;
}
//浅层拷贝ListNode
ListNode* shallowCloneListNodes(ListNode* node) {
    if (node == NULL) {
        mkerrlog("cloneListNode:ListNode*==NULL！");
        return NULL;
    }
    ListNode* head = NULL;
    ListNode* tail = getHeadNode(node);
    ListNode* newNode = NULL;
    while (tail != NULL) {
        newNode = addListNode(newNode, tail->value);
        if (head == NULL) {
            head = newNode;
        }
        tail = tail->next;
    }
    rebindListNode(head);
    return head;
}