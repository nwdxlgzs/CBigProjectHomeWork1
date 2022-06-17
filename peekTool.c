#include "peekTool.h"

/*
����Ĭ�ϵ�ȫ���鿴ѡ��
���������ֱ�����㼴��
*/
int* getPeekFullModeParam(int* size) {
    int* param = (int*)malloc(sizeof(int) * (peekEnum_END - peekEnum_START - 1));
    int i = peekEnum_START + 1;
    for (; i < peekEnum_END; i++) {
        param[i - peekEnum_START - 1] = i;
    }
    *size = peekEnum_END - peekEnum_START - 1;
    return param;
}
/*
peekToolPage*������ӵĺ���
@param head content
*/
peekToolPage* peekTooladdPage(peekToolPage* head, StringItem* content) {
    peekToolPage* page = (peekToolPage*)malloc(sizeof(peekToolPage));
    if (head == NULL) {
        page->page = 1;
    } else {
        page->page = head->page + 1;
    }
    page->content = content;
    page->next = NULL;
    page->prev = NULL;
    if (head != NULL) {
        head->next = page;
        page->prev = head;
    }
    return page;
}
char* makeCarInfoItemStringTitle(int* param, int size) {
    if (param == NULL || size == 0) {
        return NULL;
    }
    char* str = malloc(sizeof(char) * 2048);
    memset(str, 0, 2048);
    int i = 0;
    int showname = 0;
    int showphone = 0;
    int showid = 0;
    for (; i < size; i++) {
        if (param[i] == 0) {
            continue;
        }
        switch (param[i]) {
            case peekEnum_person_name:
                showname = 1;
                break;
            case peekEnum_person_phone:
                showphone = 1;
                break;
            case peekEnum_person_id:
                showid = 1;
                break;
            default:
                break;
        }
    }
    for (i = 0; i < size; i++) {
        if (param[i] == 0) {
            continue;
        }
        switch (param[i]) {
            case peekEnum_carId:
                sprintf(str, "%s%10s ", str, "�������");
                break;
            case peekEnum_carBrand:
                sprintf(str, "%s%12s ", str, "����Ʒ��");
                break;
            case peekEnum_carModel:
                sprintf(str, "%s%10s ", str, "�����ͺ�");
                break;
            case peekEnum_carPrice:
                sprintf(str, "%s%10s ", str, "ԭ��");
                break;
            case peekEnum_carAge:
                sprintf(str, "%s%6s ", str, "����");
                break;
            case peekEnum_hasRepair:
                sprintf(str, "%s%11s ", str, "�Ƿ��д���");
                break;
            case peekEnum_hasFault:
                sprintf(str, "%s%11s ", str, "�Ƿ��й���");
                break;
            case peekEnum_faultDescribe:
                sprintf(str, "%s%15s ", str, "��������");
                break;
            case peekEnum_status:
                sprintf(str, "%s%6s ", str, "״̬");
                break;
            case peekEnum_date:
                sprintf(str, "%s%12s ", str, "����");
                break;
            case peekEnum_inPrice:
                sprintf(str, "%s%10s ", str, "����");
                break;
            case peekEnum_outPrice:
                sprintf(str, "%s%10s ", str, "���ۼ�");
                break;
            case peekEnum_estimatePrice:
                sprintf(str, "%s%10s ", str, "���Ƽ�");
                break;
            case peekEnum_realPrice:
                sprintf(str, "%s%10s ", str, "ʵ�ۼ�");
                break;
            case peekEnum_seller:
                if (showname)
                    sprintf(str, "%s%10s ", str, "��������");
                if (showphone)
                    sprintf(str, "%s%14s ", str, "���ҵ绰");
                break;
            case peekEnum_buyer:
                if (showname)
                    sprintf(str, "%s%10s ", str, "�������");
                if (showphone)
                    sprintf(str, "%s%14s ", str, "��ҵ绰");
                break;
            case peekEnum_handler:
                if (showname)
                    sprintf(str, "%s%10s ", str, "����������");
                if (showphone)
                    sprintf(str, "%s%14s ", str, "�����˵绰");
                break;
            case peekEnum_employee:
                if (showname)
                    sprintf(str, "%s%10s ", str, "Ա������");
                if (showid)
                    sprintf(str, "%s%10s ", str, "Ա�����");
                break;
            default:
                break;
        }
    }
    return str;
}
char* makeCarInfoItemString(carInfoItem* item, int* param, int size) {
    if (item == NULL || param == NULL || size == 0) {
        return NULL;
    }
    char* str = malloc(sizeof(char) * 2048);
    memset(str, 0, 2048);
    int i = 0;
    int showname = 0;
    int showphone = 0;
    int showid = 0;
    for (; i < size; i++) {
        if (param[i] == 0) {
            continue;
        }
        switch (param[i]) {
            case peekEnum_person_name:
                showname = 1;
                break;
            case peekEnum_person_phone:
                showphone = 1;
                break;
            case peekEnum_person_id:
                showid = 1;
                break;
            default:
                break;
        }
    }
    for (i = 0; i < size; i++) {
        if (param[i] == 0) {
            continue;
        }
        switch (param[i]) {
            case peekEnum_carId:
                sprintf(str, "%s%10d ", str, item->info->carId);
                break;
            case peekEnum_carBrand:
                sprintf(str, "%s%12s ", str, item->info->carBrand->str);
                break;
            case peekEnum_carModel:
                sprintf(str, "%s%10s ", str, item->info->carModel->str);
                break;
            case peekEnum_carPrice:
                sprintf(str, "%s%10d ", str, item->info->carPrice);
                break;
            case peekEnum_carAge:
                sprintf(str, "%s%6d ", str, item->info->carAge);
                break;
            case peekEnum_hasRepair:
                sprintf(str, "%s%11s ", str, item->info->fault->hasRepair == Boolean_TRUE ? "��" : "��");
                break;
            case peekEnum_hasFault:
                sprintf(str, "%s%11s ", str, item->info->fault->hasFault == Boolean_TRUE ? "��" : "��");
                break;
            case peekEnum_faultDescribe:
                sprintf(str, "%s%15s ", str, item->info->fault->faultDescribe->str);
                break;
            case peekEnum_status:
                sprintf(str, "%s%6s ", str, item->order->status == carStatus_inStock ? "���" :
                    (item->order->status == carStatus_outStock ? "����" :
                        (item->order->status == carStatus_reserved ? "Ԥ��" :
                            (item->order->status == carStatus_sold ? "����" : "δ֪"))));
                break;
            case peekEnum_date:
                {
                    char date[15] = { 0 };
                    sprintf(date, "%d/%d/%d", item->order->date->year, item->order->date->month, item->order->date->day);
                    sprintf(str, "%s%12s ", str, date);
                    break;
                }
            case peekEnum_inPrice:
                sprintf(str, "%s%10d ", str, item->order->inPrice);
                break;
            case peekEnum_outPrice:
                sprintf(str, "%s%10d ", str, item->order->outPrice);
                break;
            case peekEnum_estimatePrice:
                sprintf(str, "%s%10d ", str, item->order->estimatePrice);
                break;
            case peekEnum_realPrice:
                if (item->order->realPrice == -1) {
                    sprintf(str, "%s%10s ", str, "δ��");
                } else {
                    sprintf(str, "%s%10d ", str, item->order->realPrice);
                }
                break;
            case peekEnum_seller:
                if (showname)
                    sprintf(str, "%s%10s ", str, item->order->seller->name->str);
                if (showphone)
                    sprintf(str, "%s%14s ", str, item->order->seller->phone->str);
                break;
            case peekEnum_buyer:
                if (showname)
                    sprintf(str, "%s%10s ", str, item->order->buyer->name->str);
                if (showphone)
                    sprintf(str, "%s%14s ", str, item->order->buyer->phone->str);
                break;
            case peekEnum_handler:
                if (showname)
                    sprintf(str, "%s%10s ", str, item->order->handler->name->str);
                if (showphone)
                    sprintf(str, "%s%14s ", str, item->order->handler->phone->str);
                break;
            case peekEnum_employee:
                if (showname)
                    sprintf(str, "%s%10s ", str, item->order->employee->name->str);
                if (showid)
                    sprintf(str, "%s%10d ", str, item->order->employee->id);
                break;
            default:
                break;
        }
    }
    return str;
}

peekToolPage* peekTool_genPeekpage(ListNode* nodelink, int* param, int size) {
    rebindListNodeIndex(nodelink);
    ListNode* head = getHeadNode(nodelink);
    ListNode* tail = getTailNode(nodelink);
    int len = tail->index - head->index + 1;
    peekToolPage* page = NULL;
    peekToolPage* tpage = NULL;
    ListNode* cur = head;
    int i = 0;
    char* STR = malloc(sizeof(char) * 2048 * 10);
    memset(STR, 0, 2048 * 10);
    char* title = makeCarInfoItemStringTitle(param, size);
    sprintf(STR, "%s\n", title);
    while (cur != NULL) {
        i++;
        sprintf(STR, "%s%s\n", STR, makeCarInfoItemString(cur->value, param, size));
        if (i % 10 == 0) {
            StringItem* str = (StringItem*)malloc(sizeof(StringItem));
            setStringItem(str, STR);
            tpage = peekTooladdPage(tpage, str);
            if (page == NULL) {
                page = tpage;
            }
            STR = malloc(sizeof(char) * 2048 * 10);
            memset(STR, 0, 2048 * 10);
            sprintf(STR, "%s\n", title);
        }
        cur = cur->next;
    }
    StringItem* str = (StringItem*)malloc(sizeof(StringItem));
    setStringItem(str, STR);
    tpage = peekTooladdPage(tpage, str);
    if (page == NULL) {
        page = tpage;
    }
    free(title);
    return page;
}
StringItem* getPeekPage(peekToolPage* page, int pageNum) {
    if (page == NULL) {
        return NULL;
    }
    peekToolPage* cur = page;
    //��ͷ��ʼ��
    while (cur != NULL) {
        if (cur->prev != NULL) {
            cur = cur->prev;
        } else {
            break;
        }
    }
    while (cur != NULL) {
        if (cur->page == pageNum) {
            return cur->content;
        }
        cur = cur->next;
    }
    return NULL;
}