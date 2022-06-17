#include "database.h"
/**
 * @brief ���ݿ�
 * ���ǳ��󻯳��������ݿ⣬�ײ���mdb.c�������ݣ������ṩ�ϲ��װ�Ľӿ�
 *
 */


 //==========================================================================================
 //
 //
 //                                        ��ѯ��ʵ��
 //
 //
 //==========================================================================================

  /*
  ͨ��QueryByCarId��ѯ����Ӧ����ڵ�ֵ
  @param nodelink{����һ����������ڵ�} carId{�������}
  @return carInfoItem*
  ����Ψһһ����ȷ��ĳһ���ķ�����
  */
carInfoItem* QueryByCarId(ListNode* nodelink, int carId) {
    if (nodelink == NULL) {
        mkerrlog("QueryByCarId:����ڵ㲻���ڣ�");
        return NULL;
    }
    if (carId < 0) {
        mkerrlog("QueryByCarId:carId����С��0��");
        return NULL;
    }
    ListNode* head = getHeadNode(nodelink);
    ListNode* cur = head;
    while (cur != NULL) {
        if (cur->value->info->carId == carId) {
            return cur->value;
        }
        cur = cur->next;
    }
    return NULL;
}

/*
ͨ��QueryByCarBrand��ѯ����Ӧ����ڵ�ֵ�����ָ��
@param nodelink{����һ����������ڵ�} carBrand{����Ʒ��} len{ͳ�Ƴ���}
@return carInfoItem**
*/
carInfoItem** QueryByCarBrand(ListNode* nodelink, StringItem* carBrand, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByCarBrand:����ڵ㲻���ڣ�");
        return NULL;
    }
    if (carBrand == NULL) {
        mkerrlog("QueryByCarBrand:carBrand�����ڣ�");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByCarBrand:len����С��0��");
        return NULL;
    }
    carInfoItem** dst = (carInfoItem**)malloc(sizeof(carInfoItem*) * (*len));
    ListNode* head = getHeadNode(nodelink);
    ListNode* cur = head;
    int i = 0;
    while (cur != NULL) {
        if (StringItemcmp(cur->value->info->carBrand, carBrand) == 0) {
            dst[i++] = cur->value;
        }
        cur = cur->next;
    }
    *len = i;//����ͳ�Ƴ���
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
ͨ��QueryByCarModel��ѯ����Ӧ����ڵ�ֵ�����ָ��
@param nodelink{����һ����������ڵ�} carModel{����Ʒ��} len{ͳ�Ƴ���}
@return carInfoItem**
*/
carInfoItem** QueryByCarModel(ListNode* nodelink, StringItem* carModel, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByCarModel:����ڵ㲻���ڣ�");
        return NULL;
    }
    if (carModel == NULL) {
        mkerrlog("QueryByCarModel:carModel�����ڣ�");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByCarModel:len����С��0��");
        return NULL;
    }
    carInfoItem** dst = (carInfoItem**)malloc(sizeof(carInfoItem*) * (*len));
    ListNode* head = getHeadNode(nodelink);
    ListNode* cur = head;
    int i = 0;
    while (cur != NULL) {
        if (StringItemcmp(cur->value->info->carModel, carModel) == 0) {
            dst[i++] = cur->value;
        }
        cur = cur->next;
    }
    *len = i;//����ͳ�Ƴ���
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
ͨ��QueryByCarPrice��ѯ����Ӧ����ڵ�ֵ�����ָ��
@param nodelink{����һ����������ڵ�} min{���ֵ} max{���ֵ} len{ͳ�Ƴ���}
@return carInfoItem**
*/
carInfoItem** QueryByCarPrice(ListNode* nodelink, int min, int max, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByCarPrice:����ڵ㲻���ڣ�");
        return NULL;
    }
    if (min < 0) {
        mkerrlog("QueryByCarPrice:min�����Ǹ�����");
        return NULL;
    }
    if (max < 0) {
        mkerrlog("QueryByCarPrice:max�����Ǹ�����");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByCarPrice:len����С��0��");
        return NULL;
    }
    //�ҾͲ������ˣ���С����������
    if (min > max) {
        min ^= max;
        max ^= min;
        min ^= max;
    }
    carInfoItem** dst = (carInfoItem**)malloc(sizeof(carInfoItem*) * (*len));
    ListNode* head = getHeadNode(nodelink);
    ListNode* cur = head;
    int i = 0;
    while (cur != NULL) {
        int price = cur->value->info->carPrice;
        if (price >= min && price <= max) {
            dst[i++] = cur->value;
        }
        cur = cur->next;
    }
    *len = i;//����ͳ�Ƴ���
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}



/*
ͨ��QueryByCarAge��ѯ����Ӧ����ڵ�ֵ�����ָ��
@param nodelink{����һ����������ڵ�} min{���ֵ} max{���ֵ} len{ͳ�Ƴ���}
@return carInfoItem**
*/
carInfoItem** QueryByCarAge(ListNode* nodelink, int min, int max, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByCarAge:����ڵ㲻���ڣ�");
        return NULL;
    }
    if (min < 0) {
        mkerrlog("QueryByCarAge:min�����Ǹ�����");
        return NULL;
    }
    if (max < 0) {
        mkerrlog("QueryByCarAge:max�����Ǹ�����");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByCarAge:len����С��0��");
        return NULL;
    }
    //�ҾͲ������ˣ���С����������
    if (min > max) {
        min ^= max;
        max ^= min;
        min ^= max;
    }
    carInfoItem** dst = (carInfoItem**)malloc(sizeof(carInfoItem*) * (*len));
    ListNode* head = getHeadNode(nodelink);
    ListNode* cur = head;
    int i = 0;
    while (cur != NULL) {
        int age = cur->value->info->carAge;
        if (age >= min && age <= max) {
            dst[i++] = cur->value;
        }
        cur = cur->next;
    }
    *len = i;//����ͳ�Ƴ���
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
ͨ��QueryByCarHasRepair��ѯ����Ӧ����ڵ�ֵ�����ָ��
@param nodelink{����һ����������ڵ�} unselect{��ѡ} len{ͳ�Ƴ���}
@return carInfoItem**
*/
carInfoItem** QueryByCarHasRepair(ListNode* nodelink, enum BooleanDef unselect, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByCarAge:����ڵ㲻���ڣ�");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByCarAge:len����С��0��");
        return NULL;
    }
    carInfoItem** dst = (carInfoItem**)malloc(sizeof(carInfoItem*) * (*len));
    ListNode* head = getHeadNode(nodelink);
    ListNode* cur = head;
    int i = 0;
    while (cur != NULL) {
        int hasRepair = cur->value->info->fault->hasRepair;
        if (unselect) {//��ѡ
            if (!hasRepair) {
                dst[i++] = cur->value;
            }
        } else {
            if (hasRepair) {
                dst[i++] = cur->value;
            }
        }
        cur = cur->next;
    }
    *len = i;//����ͳ�Ƴ���
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
ͨ��QueryByCarHasFault��ѯ����Ӧ����ڵ�ֵ�����ָ��
@param nodelink{����һ����������ڵ�} unselect{��ѡ} len{ͳ�Ƴ���}
@return carInfoItem**
*/
carInfoItem** QueryByCarHasFault(ListNode* nodelink, enum BooleanDef unselect, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByCarHasFault:����ڵ㲻���ڣ�");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByCarHasFault:len����С��0��");
        return NULL;
    }
    carInfoItem** dst = (carInfoItem**)malloc(sizeof(carInfoItem*) * (*len));
    ListNode* head = getHeadNode(nodelink);
    ListNode* cur = head;
    int i = 0;
    while (cur != NULL) {
        int hasRepair = cur->value->info->fault->hasFault;
        if (unselect) {//��ѡ
            if (!hasRepair) {
                dst[i++] = cur->value;
            }
        } else {
            if (hasRepair) {
                dst[i++] = cur->value;
            }
        }
        cur = cur->next;
    }
    *len = i;//����ͳ�Ƴ���
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
ͨ��QueryByCarStatus��ѯ����Ӧ����ڵ�ֵ�����ָ��
@param nodelink{����һ����������ڵ�} unselect{��ѡ} len{ͳ�Ƴ���}
@return carInfoItem**
*/
carInfoItem** QueryByCarStatus(ListNode* nodelink, enum carStatus status, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByCarStatus:����ڵ㲻���ڣ�");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByCarStatus:len����С��0��");
        return NULL;
    }
    carInfoItem** dst = (carInfoItem**)malloc(sizeof(carInfoItem*) * (*len));
    ListNode* head = getHeadNode(nodelink);
    ListNode* cur = head;
    int i = 0;
    while (cur != NULL) {
        if (cur->value->order->status == status) {
            dst[i++] = cur->value;
        }
        cur = cur->next;
    }
    *len = i;//����ͳ�Ƴ���
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
ͨ��QueryByDate��ѯ����Ӧ����ڵ�ֵ�����ָ��
@param nodelink{����һ����������ڵ�} min{��ʼ��} max{��ֹ��} len{ͳ�Ƴ���}
@return carInfoItem**
*/
carInfoItem** QueryByDate(ListNode* nodelink, Date* min, Date* max, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByDate:����ڵ㲻���ڣ�");
        return NULL;
    }
    if (min < 0) {
        mkerrlog("QueryByDate:min�����Ǹ�����");
        return NULL;
    }
    if (max < 0) {
        mkerrlog("QueryByDate:max�����Ǹ�����");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByDate:len����С��0��");
        return NULL;
    }
    //�ҾͲ������ˣ���С����������
    if (min > max) {
        Date* tmp = min;
        min = max;
        max = tmp;
    }
    carInfoItem** dst = (carInfoItem**)malloc(sizeof(carInfoItem*) * (*len));
    ListNode* head = getHeadNode(nodelink);
    ListNode* cur = head;
    int i = 0;
    while (cur != NULL) {
        Date* date = cur->value->order->date;
        if (date->year >= min->year && date->year <= max->year) {//��ݱȽ�
            if (date->month >= min->month && date->month <= max->month) {//�·ݱȽ�
                if (date->day >= min->day && date->day <= max->day) {//���ڱȽ�
                    dst[i++] = cur->value;
                }
            }
        }
        cur = cur->next;
    }
    *len = i;//����ͳ�Ƴ���
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}



/*
ͨ��QueryByInPrice��ѯ����Ӧ����ڵ�ֵ�����ָ��
@param nodelink{����һ����������ڵ�} min{��ʼ�۸�} max{��ֹ�۸�} len{ͳ�Ƴ���}
@return carInfoItem**
*/
carInfoItem** QueryByInPrice(ListNode* nodelink, int min, int max, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByInPrice:����ڵ㲻���ڣ�");
        return NULL;
    }
    if (min < 0) {
        mkerrlog("QueryByInPrice:min�����Ǹ�����");
        return NULL;
    }
    if (max < 0) {
        mkerrlog("QueryByInPrice:max�����Ǹ�����");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByDate:len����С��0��");
        return NULL;
    }
    //�ҾͲ������ˣ���С����������
    if (min > max) {
        min ^= max;
        max ^= min;
        min ^= max;
    }
    carInfoItem** dst = (carInfoItem**)malloc(sizeof(carInfoItem*) * (*len));
    ListNode* head = getHeadNode(nodelink);
    ListNode* cur = head;
    int i = 0;
    while (cur != NULL) {
        int price = cur->value->order->inPrice;
        if (price >= min && price <= max) {
            dst[i++] = cur->value;
        }
        cur = cur->next;
    }
    *len = i;//����ͳ�Ƴ���
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
ͨ��QueryByOutPrice��ѯ����Ӧ����ڵ�ֵ�����ָ��
@param nodelink{����һ����������ڵ�} min{��ʼ�۸�} max{��ֹ�۸�} len{ͳ�Ƴ���}
@return carInfoItem**
*/
carInfoItem** QueryByOutPrice(ListNode* nodelink, int min, int max, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByOutPrice:����ڵ㲻���ڣ�");
        return NULL;
    }
    if (min < 0) {
        mkerrlog("QueryByOutPrice:min�����Ǹ�����");
        return NULL;
    }
    if (max < 0) {
        mkerrlog("QueryByOutPrice:max�����Ǹ�����");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByOutPrice:len����С��0��");
        return NULL;
    }
    //�ҾͲ������ˣ���С����������
    if (min > max) {
        min ^= max;
        max ^= min;
        min ^= max;
    }
    carInfoItem** dst = (carInfoItem**)malloc(sizeof(carInfoItem*) * (*len));
    ListNode* head = getHeadNode(nodelink);
    ListNode* cur = head;
    int i = 0;
    while (cur != NULL) {
        int price = cur->value->order->outPrice;
        if (price >= min && price <= max) {
            dst[i++] = cur->value;
        }
        cur = cur->next;
    }
    *len = i;//����ͳ�Ƴ���
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
ͨ��QueryByEstimatePrice��ѯ����Ӧ����ڵ�ֵ�����ָ��
@param nodelink{����һ����������ڵ�} min{��ʼ�۸�} max{��ֹ�۸�} len{ͳ�Ƴ���}
@return carInfoItem**
*/
carInfoItem** QueryByEstimatePrice(ListNode* nodelink, int min, int max, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByEstimatePrice:����ڵ㲻���ڣ�");
        return NULL;
    }
    if (min < 0) {
        mkerrlog("QueryByEstimatePrice:min�����Ǹ�����");
        return NULL;
    }
    if (max < 0) {
        mkerrlog("QueryByEstimatePrice:max�����Ǹ�����");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByEstimatePrice:len����С��0��");
        return NULL;
    }
    //�ҾͲ������ˣ���С����������
    if (min > max) {
        min ^= max;
        max ^= min;
        min ^= max;
    }
    carInfoItem** dst = (carInfoItem**)malloc(sizeof(carInfoItem*) * (*len));
    ListNode* head = getHeadNode(nodelink);
    ListNode* cur = head;
    int i = 0;
    while (cur != NULL) {
        int price = cur->value->order->estimatePrice;
        if (price >= min && price <= max) {
            dst[i++] = cur->value;
        }
        cur = cur->next;
    }
    *len = i;//����ͳ�Ƴ���
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
ͨ��QueryByRealPrice��ѯ����Ӧ����ڵ�ֵ�����ָ��
@param nodelink{����һ����������ڵ�} min{��ʼ�۸�} max{��ֹ�۸�} len{ͳ�Ƴ���}
@return carInfoItem**
*/
carInfoItem** QueryByRealPrice(ListNode* nodelink, int min, int max, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByRealPrice:����ڵ㲻���ڣ�");
        return NULL;
    }
    if (min < 0) {
        mkerrlog("QueryByRealPrice:min�����Ǹ�����");
        return NULL;
    }
    if (max < 0) {
        mkerrlog("QueryByRealPrice:max�����Ǹ�����");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByRealPrice:len����С��0��");
        return NULL;
    }
    //�ҾͲ������ˣ���С����������
    if (min > max) {
        min ^= max;
        max ^= min;
        min ^= max;
    }
    carInfoItem** dst = (carInfoItem**)malloc(sizeof(carInfoItem*) * (*len));
    ListNode* head = getHeadNode(nodelink);
    ListNode* cur = head;
    int i = 0;
    while (cur != NULL) {
        int price = cur->value->order->realPrice;
        if (price == -1) {
            cur = cur->next;
            continue;
        }
        if (price >= min && price <= max) {
            dst[i++] = cur->value;
        }
        cur = cur->next;
    }
    *len = i;//����ͳ�Ƴ���
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
ͨ��QueryByOnSale��ѯ����Ӧ����ڵ�ֵ�����ָ��
@param nodelink{����һ����������ڵ�} unselect{��ѡ} len{ͳ�Ƴ���}
@return carInfoItem**
*/
carInfoItem** QueryByOnSale(ListNode* nodelink, enum BooleanDef unselect, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByOnSale:����ڵ㲻���ڣ�");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByOnSale:len����С��0��");
        return NULL;
    }
    carInfoItem** dst = (carInfoItem**)malloc(sizeof(carInfoItem*) * (*len));
    ListNode* head = getHeadNode(nodelink);
    ListNode* cur = head;
    int i = 0;
    while (cur != NULL) {
        int price = cur->value->order->realPrice;
        if (unselect) {
            if (price != -1) {//����
                dst[i++] = cur->value;
            }
        } else {
            if (price == -1) {//δ��
                dst[i++] = cur->value;
            }
        }
        cur = cur->next;
    }
    *len = i;//����ͳ�Ƴ���
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
ͨ��QueryBySellerName��ѯ����Ӧ����ڵ�ֵ�����ָ��
@param nodelink{����һ����������ڵ�} name{����} len{ͳ�Ƴ���}
@return carInfoItem**
*/
carInfoItem** QueryBySellerName(ListNode* nodelink, StringItem* name, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryBySellerName:����ڵ㲻���ڣ�");
        return NULL;
    }
    if (name == NULL) {
        mkerrlog("QueryBySellerName:name����Ϊ�գ�");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryBySellerName:len����С��0��");
        return NULL;
    }
    carInfoItem** dst = (carInfoItem**)malloc(sizeof(carInfoItem*) * (*len));
    ListNode* head = getHeadNode(nodelink);
    ListNode* cur = head;
    int i = 0;
    while (cur != NULL) {
        StringItem* sn = cur->value->order->seller->name;
        if (StringItemcmp(sn, name) == 0) {
            dst[i++] = cur->value;
        }
        cur = cur->next;
    }
    *len = i;//����ͳ�Ƴ���
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
ͨ��QueryBySellerPhone��ѯ����Ӧ����ڵ�ֵ�����ָ��
@param nodelink{����һ����������ڵ�} phone{�ֻ���} len{ͳ�Ƴ���}
@return carInfoItem**
*/
carInfoItem** QueryBySellerPhone(ListNode* nodelink, StringItem* phone, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryBySellerPhone:����ڵ㲻���ڣ�");
        return NULL;
    }
    if (phone == NULL) {
        mkerrlog("QueryBySellerPhone:phone����Ϊ�գ�");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryBySellerPhone:len����С��0��");
        return NULL;
    }
    carInfoItem** dst = (carInfoItem**)malloc(sizeof(carInfoItem*) * (*len));
    ListNode* head = getHeadNode(nodelink);
    ListNode* cur = head;
    int i = 0;
    while (cur != NULL) {
        StringItem* sp = cur->value->order->seller->phone;
        if (StringItemcmp(sp, phone) == 0) {
            dst[i++] = cur->value;
        }
        cur = cur->next;
    }
    *len = i;//����ͳ�Ƴ���
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
ͨ��QueryByBuyerName��ѯ����Ӧ����ڵ�ֵ�����ָ��
@param nodelink{����һ����������ڵ�} name{����} len{ͳ�Ƴ���}
@return carInfoItem**
*/
carInfoItem** QueryByBuyerName(ListNode* nodelink, StringItem* name, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByBuyerName:����ڵ㲻���ڣ�");
        return NULL;
    }
    if (name == NULL) {
        mkerrlog("QueryByBuyerName:name����Ϊ�գ�");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByBuyerName:len����С��0��");
        return NULL;
    }
    carInfoItem** dst = (carInfoItem**)malloc(sizeof(carInfoItem*) * (*len));
    ListNode* head = getHeadNode(nodelink);
    ListNode* cur = head;
    int i = 0;
    while (cur != NULL) {
        StringItem* sn = cur->value->order->buyer->name;
        if (StringItemcmp(sn, name) == 0) {
            dst[i++] = cur->value;
        }
        cur = cur->next;
    }
    *len = i;//����ͳ�Ƴ���
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
ͨ��QueryByBuyerPhone��ѯ����Ӧ����ڵ�ֵ�����ָ��
@param nodelink{����һ����������ڵ�} phone{�ֻ���} len{ͳ�Ƴ���}
@return carInfoItem**
*/
carInfoItem** QueryByBuyerPhone(ListNode* nodelink, StringItem* phone, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByBuyerPhone:����ڵ㲻���ڣ�");
        return NULL;
    }
    if (phone == NULL) {
        mkerrlog("QueryByBuyerPhone:phone����Ϊ�գ�");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByBuyerPhone:len����С��0��");
        return NULL;
    }
    carInfoItem** dst = (carInfoItem**)malloc(sizeof(carInfoItem*) * (*len));
    ListNode* head = getHeadNode(nodelink);
    ListNode* cur = head;
    int i = 0;
    while (cur != NULL) {
        StringItem* sp = cur->value->order->buyer->phone;
        if (StringItemcmp(sp, phone) == 0) {
            dst[i++] = cur->value;
        }
        cur = cur->next;
    }
    *len = i;//����ͳ�Ƴ���
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
ͨ��QueryByHandlerName��ѯ����Ӧ����ڵ�ֵ�����ָ��
@param nodelink{����һ����������ڵ�} name{����} len{ͳ�Ƴ���}
@return carInfoItem**
*/
carInfoItem** QueryByHandlerName(ListNode* nodelink, StringItem* name, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByHandlerName:����ڵ㲻���ڣ�");
        return NULL;
    }
    if (name == NULL) {
        mkerrlog("QueryByHandlerName:name����Ϊ�գ�");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByHandlerName:len����С��0��");
        return NULL;
    }
    carInfoItem** dst = (carInfoItem**)malloc(sizeof(carInfoItem*) * (*len));
    ListNode* head = getHeadNode(nodelink);
    ListNode* cur = head;
    int i = 0;
    while (cur != NULL) {
        StringItem* sn = cur->value->order->handler->name;
        if (StringItemcmp(sn, name) == 0) {
            dst[i++] = cur->value;
        }
        cur = cur->next;
    }
    *len = i;//����ͳ�Ƴ���
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
ͨ��QueryByHandlerPhone��ѯ����Ӧ����ڵ�ֵ�����ָ��
@param nodelink{����һ����������ڵ�} phone{�ֻ���} len{ͳ�Ƴ���}
@return carInfoItem**
*/
carInfoItem** QueryByHandlerPhone(ListNode* nodelink, StringItem* phone, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByHandlerPhone:����ڵ㲻���ڣ�");
        return NULL;
    }
    if (phone == NULL) {
        mkerrlog("QueryByHandlerPhone:phone����Ϊ�գ�");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByHandlerPhone:len����С��0��");
        return NULL;
    }
    carInfoItem** dst = (carInfoItem**)malloc(sizeof(carInfoItem*) * (*len));
    ListNode* head = getHeadNode(nodelink);
    ListNode* cur = head;
    int i = 0;
    while (cur != NULL) {
        StringItem* sp = cur->value->order->handler->phone;
        if (StringItemcmp(sp, phone) == 0) {
            dst[i++] = cur->value;
        }
        cur = cur->next;
    }
    *len = i;//����ͳ�Ƴ���
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}



/*
ͨ��QueryByEmployeeName��ѯ����Ӧ����ڵ�ֵ�����ָ��
@param nodelink{����һ����������ڵ�} name{����} len{ͳ�Ƴ���}
@return carInfoItem**
*/
carInfoItem** QueryByEmployeeName(ListNode* nodelink, StringItem* name, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByEmployeeName:����ڵ㲻���ڣ�");
        return NULL;
    }
    if (name == NULL) {
        mkerrlog("QueryByEmployeeName:name����Ϊ�գ�");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByEmployeeName:len����С��0��");
        return NULL;
    }
    carInfoItem** dst = (carInfoItem**)malloc(sizeof(carInfoItem*) * (*len));
    ListNode* head = getHeadNode(nodelink);
    ListNode* cur = head;
    int i = 0;
    while (cur != NULL) {
        StringItem* sn = cur->value->order->employee->name;
        if (StringItemcmp(sn, name) == 0) {
            dst[i++] = cur->value;
        }
        cur = cur->next;
    }
    *len = i;//����ͳ�Ƴ���
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
ͨ��QueryByEmployeeId��ѯ����Ӧ����ڵ�ֵ�����ָ��
@param nodelink{����һ����������ڵ�} phone{�ֻ���} len{ͳ�Ƴ���}
@return carInfoItem**
*/
carInfoItem** QueryByEmployeeId(ListNode* nodelink, int id, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByEmployeeId:����ڵ㲻���ڣ�");
        return NULL;
    }
    if (id < 0) {
        mkerrlog("QueryByEmployeeId:id����Ϊ������");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByEmployeeId:len����С��0��");
        return NULL;
    }
    carInfoItem** dst = (carInfoItem**)malloc(sizeof(carInfoItem*) * (*len));
    ListNode* head = getHeadNode(nodelink);
    ListNode* cur = head;
    int i = 0;
    while (cur != NULL) {
        if (cur->value->order->employee->id == id) {
            dst[i++] = cur->value;
        }
        cur = cur->next;
    }
    *len = i;//����ͳ�Ƴ���
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}

//==========================================================================================
//
//
//                                        ����ʵ��
//
//
//==========================================================================================

/*
ͨ��SortByCarId����
@param nodelink{����һ����������ڵ�} udmode{������}
@return ListNode*
*/
ListNode* SortByCarId(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByCarId:����ڵ㲻���ڣ�");
        return NULL;
    }
    rebindListNodeIndex(nodelink);
    ListNode* head = getHeadNode(nodelink);
    ListNode* tail = getTailNode(nodelink);
    ListNode* cur = head;
    int size = tail->index - head->index + 1;
    ListNode** arr = (ListNode**)malloc(sizeof(ListNode*) * size);
    int i = 0;
    while (cur != NULL) {
        arr[i++] = cur;
        cur = cur->next;
    }
    for (i = 0;i < size;i++) {
        int j;
        for (j = i + 1;j < size;j++) {
            if (udmode == UDMode_Up) {
                if (arr[i]->value->info->carId > arr[j]->value->info->carId) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            } else {
                if (arr[i]->value->info->carId < arr[j]->value->info->carId) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            }
        }
    }
    head = creatListNodeByListNodes(arr, size);
    free(arr);
    return head;
}

/*
ͨ��SortByCarBrand����
@param nodelink{����һ����������ڵ�} udmode{������}
@return ListNode*
*/
ListNode* SortByCarBrand(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByCarBrand:����ڵ㲻���ڣ�");
        return NULL;
    }
    rebindListNodeIndex(nodelink);
    ListNode* head = getHeadNode(nodelink);
    ListNode* tail = getTailNode(nodelink);
    ListNode* cur = head;
    int size = tail->index - head->index + 1;
    ListNode** arr = (ListNode**)malloc(sizeof(ListNode*) * size);
    int i = 0;
    while (cur != NULL) {
        arr[i++] = cur;
        cur = cur->next;
    }
    for (i = 0;i < size;i++) {
        int j;
        for (j = i + 1;j < size;j++) {
            if (udmode == UDMode_Up) {
                if (strcmp(arr[i]->value->info->carBrand->str, arr[j]->value->info->carBrand->str) > 0) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            } else {
                if (strcmp(arr[i]->value->info->carBrand->str, arr[j]->value->info->carBrand->str) < 0) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            }
        }
    }
    head = creatListNodeByListNodes(arr, size);
    free(arr);
    return head;
}


/*
ͨ��SortByCarModel����
@param nodelink{����һ����������ڵ�} udmode{������}
@return ListNode*
*/
ListNode* SortByCarModel(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByCarModel:����ڵ㲻���ڣ�");
        return NULL;
    }
    rebindListNodeIndex(nodelink);
    ListNode* head = getHeadNode(nodelink);
    ListNode* tail = getTailNode(nodelink);
    ListNode* cur = head;
    int size = tail->index - head->index + 1;
    ListNode** arr = (ListNode**)malloc(sizeof(ListNode*) * size);
    int i = 0;
    while (cur != NULL) {
        arr[i++] = cur;
        cur = cur->next;
    }
    for (i = 0;i < size;i++) {
        int j;
        for (j = i + 1;j < size;j++) {
            if (udmode == UDMode_Up) {
                if (strcmp(arr[i]->value->info->carModel->str, arr[j]->value->info->carModel->str) > 0) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            } else {
                if (strcmp(arr[i]->value->info->carModel->str, arr[j]->value->info->carModel->str) < 0) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            }
        }
    }
    head = creatListNodeByListNodes(arr, size);
    free(arr);
    return head;
}


/*
ͨ��SortByCarPrice����
@param nodelink{����һ����������ڵ�} udmode{������}
@return ListNode*
*/
ListNode* SortByCarPrice(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByCarPrice:����ڵ㲻���ڣ�");
        return NULL;
    }
    rebindListNodeIndex(nodelink);
    ListNode* head = getHeadNode(nodelink);
    ListNode* tail = getTailNode(nodelink);
    ListNode* cur = head;
    int size = tail->index - head->index + 1;
    ListNode** arr = (ListNode**)malloc(sizeof(ListNode*) * size);
    int i = 0;
    while (cur != NULL) {
        arr[i++] = cur;
        cur = cur->next;
    }
    for (i = 0;i < size;i++) {
        int j;
        for (j = i + 1;j < size;j++) {
            if (udmode == UDMode_Up) {
                if (arr[i]->value->info->carPrice > arr[j]->value->info->carPrice) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            } else {
                if (arr[i]->value->info->carPrice < arr[j]->value->info->carPrice) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            }
        }
    }
    head = creatListNodeByListNodes(arr, size);
    free(arr);
    return head;
}


/*
ͨ��SortByCarAge����
@param nodelink{����һ����������ڵ�} udmode{������}
@return ListNode*
*/
ListNode* SortByCarAge(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByCarAge:����ڵ㲻���ڣ�");
        return NULL;
    }
    rebindListNodeIndex(nodelink);
    ListNode* head = getHeadNode(nodelink);
    ListNode* tail = getTailNode(nodelink);
    ListNode* cur = head;
    int size = tail->index - head->index + 1;
    ListNode** arr = (ListNode**)malloc(sizeof(ListNode*) * size);
    int i = 0;
    while (cur != NULL) {
        arr[i++] = cur;
        cur = cur->next;
    }
    for (i = 0;i < size;i++) {
        int j;
        for (j = i + 1;j < size;j++) {
            if (udmode == UDMode_Up) {
                if (arr[i]->value->info->carAge > arr[j]->value->info->carAge) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            } else {
                if (arr[i]->value->info->carAge < arr[j]->value->info->carAge) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            }
        }
    }
    head = creatListNodeByListNodes(arr, size);
    free(arr);
    return head;
}


/*
ͨ��SortByCarHasRepair����
@param nodelink{����һ����������ڵ�} udmode{������}
@return ListNode*
*/
ListNode* SortByCarHasRepair(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByCarHasRepair:����ڵ㲻���ڣ�");
        return NULL;
    }
    rebindListNodeIndex(nodelink);
    ListNode* head = getHeadNode(nodelink);
    ListNode* tail = getTailNode(nodelink);
    ListNode* cur = head;
    int size = tail->index - head->index + 1;
    ListNode** arr = (ListNode**)malloc(sizeof(ListNode*) * size);
    int i = 0;
    while (cur != NULL) {
        arr[i++] = cur;
        cur = cur->next;
    }
    for (i = 0;i < size;i++) {
        int j;
        for (j = i + 1;j < size;j++) {
            if (udmode == UDMode_Up) {
                if (arr[i]->value->info->fault->hasRepair > arr[j]->value->info->fault->hasRepair) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            } else {
                if (arr[i]->value->info->fault->hasRepair < arr[j]->value->info->fault->hasRepair) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            }
        }
    }
    head = creatListNodeByListNodes(arr, size);
    free(arr);
    return head;
}

/*
ͨ��SortByCarHasFault����
@param nodelink{����һ����������ڵ�} udmode{������}
@return ListNode*
*/
ListNode* SortByCarHasFault(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByCarHasFault:����ڵ㲻���ڣ�");
        return NULL;
    }
    rebindListNodeIndex(nodelink);
    ListNode* head = getHeadNode(nodelink);
    ListNode* tail = getTailNode(nodelink);
    ListNode* cur = head;
    int size = tail->index - head->index + 1;
    ListNode** arr = (ListNode**)malloc(sizeof(ListNode*) * size);
    int i = 0;
    while (cur != NULL) {
        arr[i++] = cur;
        cur = cur->next;
    }
    for (i = 0;i < size;i++) {
        int j;
        for (j = i + 1;j < size;j++) {
            if (udmode == UDMode_Up) {
                if (arr[i]->value->info->fault->hasFault > arr[j]->value->info->fault->hasFault) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            } else {
                if (arr[i]->value->info->fault->hasFault < arr[j]->value->info->fault->hasFault) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            }
        }
    }
    head = creatListNodeByListNodes(arr, size);
    free(arr);
    return head;
}

/*
ͨ��SortByCarStatus����
@param nodelink{����һ����������ڵ�} udmode{������}
@return ListNode*
*/
ListNode* SortByCarStatus(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByCarStatus:����ڵ㲻���ڣ�");
        return NULL;
    }
    rebindListNodeIndex(nodelink);
    ListNode* head = getHeadNode(nodelink);
    ListNode* tail = getTailNode(nodelink);
    ListNode* cur = head;
    int size = tail->index - head->index + 1;
    ListNode** arr = (ListNode**)malloc(sizeof(ListNode*) * size);
    int i = 0;
    while (cur != NULL) {
        arr[i++] = cur;
        cur = cur->next;
    }
    for (i = 0;i < size;i++) {
        int j;
        for (j = i + 1;j < size;j++) {
            if (udmode == UDMode_Up) {
                if (arr[i]->value->order->status > arr[j]->value->order->status) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            } else {
                if (arr[i]->value->order->status < arr[j]->value->order->status) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            }
        }
    }
    head = creatListNodeByListNodes(arr, size);
    free(arr);
    return head;
}

/*
ͨ��SortByDate����
@param nodelink{����һ����������ڵ�} udmode{������}
@return ListNode*
*/
ListNode* SortByDate(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByDate:����ڵ㲻���ڣ�");
        return NULL;
    }
    rebindListNodeIndex(nodelink);
    ListNode* head = getHeadNode(nodelink);
    ListNode* tail = getTailNode(nodelink);
    ListNode* cur = head;
    int size = tail->index - head->index + 1;
    ListNode** arr = (ListNode**)malloc(sizeof(ListNode*) * size);
    int i = 0;
    while (cur != NULL) {
        arr[i++] = cur;
        cur = cur->next;
    }
    for (i = 0;i < size;i++) {
        int j;
        for (j = i + 1;j < size;j++) {
            Date* d1 = arr[i]->value->order->date;
            Date* d2 = arr[j]->value->order->date;
            if (udmode == UDMode_Up) {
                if (d1->year > d2->year) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                } else if (d1->year == d2->year) {
                    if (d1->month > d2->month) {
                        ListNode* tmp = arr[i];
                        arr[i] = arr[j];
                        arr[j] = tmp;
                    } else if (d1->month == d2->month) {
                        if (d1->day > d2->day) {
                            ListNode* tmp = arr[i];
                            arr[i] = arr[j];
                            arr[j] = tmp;
                        }
                    }
                }
            } else {
                if (d1->year < d2->year) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                } else if (d1->year == d2->year) {
                    if (d1->month < d2->month) {
                        ListNode* tmp = arr[i];
                        arr[i] = arr[j];
                        arr[j] = tmp;
                    } else if (d1->month == d2->month) {
                        if (d1->day < d2->day) {
                            ListNode* tmp = arr[i];
                            arr[i] = arr[j];
                            arr[j] = tmp;
                        }
                    }
                }
            }
        }
    }
    head = creatListNodeByListNodes(arr, size);
    free(arr);
    return head;
}


/*
ͨ��SortByInPrice����
@param nodelink{����һ����������ڵ�} udmode{������}
@return ListNode*
*/
ListNode* SortByInPrice(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByInPrice:����ڵ㲻���ڣ�");
        return NULL;
    }
    rebindListNodeIndex(nodelink);
    ListNode* head = getHeadNode(nodelink);
    ListNode* tail = getTailNode(nodelink);
    ListNode* cur = head;
    int size = tail->index - head->index + 1;
    ListNode** arr = (ListNode**)malloc(sizeof(ListNode*) * size);
    int i = 0;
    while (cur != NULL) {
        arr[i++] = cur;
        cur = cur->next;
    }
    for (i = 0;i < size;i++) {
        int j;
        for (j = i + 1;j < size;j++) {
            if (udmode == UDMode_Up) {
                if (arr[i]->value->order->inPrice > arr[j]->value->order->inPrice) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            } else {
                if (arr[i]->value->order->inPrice < arr[j]->value->order->inPrice) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            }
        }
    }
    head = creatListNodeByListNodes(arr, size);
    free(arr);
    return head;
}


/*
ͨ��SortByOutPrice����
@param nodelink{����һ����������ڵ�} udmode{������}
@return ListNode*
*/
ListNode* SortByOutPrice(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByOutPrice:����ڵ㲻���ڣ�");
        return NULL;
    }
    rebindListNodeIndex(nodelink);
    ListNode* head = getHeadNode(nodelink);
    ListNode* tail = getTailNode(nodelink);
    ListNode* cur = head;
    int size = tail->index - head->index + 1;
    ListNode** arr = (ListNode**)malloc(sizeof(ListNode*) * size);
    int i = 0;
    while (cur != NULL) {
        arr[i++] = cur;
        cur = cur->next;
    }
    for (i = 0;i < size;i++) {
        int j;
        for (j = i + 1;j < size;j++) {
            if (udmode == UDMode_Up) {
                if (arr[i]->value->order->outPrice > arr[j]->value->order->outPrice) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            } else {
                if (arr[i]->value->order->outPrice < arr[j]->value->order->outPrice) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            }
        }
    }
    head = creatListNodeByListNodes(arr, size);
    free(arr);
    return head;
}


/*
ͨ��SortByEstimatePrice����
@param nodelink{����һ����������ڵ�} udmode{������}
@return ListNode*
*/
ListNode* SortByEstimatePrice(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByEstimatePrice:����ڵ㲻���ڣ�");
        return NULL;
    }
    rebindListNodeIndex(nodelink);
    ListNode* head = getHeadNode(nodelink);
    ListNode* tail = getTailNode(nodelink);
    ListNode* cur = head;
    int size = tail->index - head->index + 1;
    ListNode** arr = (ListNode**)malloc(sizeof(ListNode*) * size);
    int i = 0;
    while (cur != NULL) {
        arr[i++] = cur;
        cur = cur->next;
    }
    for (i = 0;i < size;i++) {
        int j;
        for (j = i + 1;j < size;j++) {
            if (udmode == UDMode_Up) {
                if (arr[i]->value->order->estimatePrice > arr[j]->value->order->estimatePrice) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            } else {
                if (arr[i]->value->order->estimatePrice < arr[j]->value->order->estimatePrice) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            }
        }
    }
    head = creatListNodeByListNodes(arr, size);
    free(arr);
    return head;
}


/*
ͨ��SortByRealPrice����
@param nodelink{����һ����������ڵ�} udmode{������}
@return ListNode*
*/
ListNode* SortByRealPrice(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByRealPrice:����ڵ㲻���ڣ�");
        return NULL;
    }
    rebindListNodeIndex(nodelink);
    ListNode* head = getHeadNode(nodelink);
    ListNode* tail = getTailNode(nodelink);
    ListNode* cur = head;
    int size = tail->index - head->index + 1;
    ListNode** arr = (ListNode**)malloc(sizeof(ListNode*) * size);
    int i = 0;
    while (cur != NULL) {
        arr[i++] = cur;
        cur = cur->next;
    }
    for (i = 0;i < size;i++) {
        int j;
        for (j = i + 1;j < size;j++) {
            if (udmode == UDMode_Up) {
                if (arr[i]->value->order->realPrice > arr[j]->value->order->realPrice) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            } else {
                if (arr[i]->value->order->realPrice < arr[j]->value->order->realPrice) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            }
        }
    }
    head = creatListNodeByListNodes(arr, size);
    free(arr);
    return head;
}

/*
ͨ��SortBySellerName����
@param nodelink{����һ����������ڵ�} udmode{������}
@return ListNode*
*/
ListNode* SortBySellerName(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortBySellerName:����ڵ㲻���ڣ�");
        return NULL;
    }
    rebindListNodeIndex(nodelink);
    ListNode* head = getHeadNode(nodelink);
    ListNode* tail = getTailNode(nodelink);
    ListNode* cur = head;
    int size = tail->index - head->index + 1;
    ListNode** arr = (ListNode**)malloc(sizeof(ListNode*) * size);
    int i = 0;
    while (cur != NULL) {
        arr[i++] = cur;
        cur = cur->next;
    }
    for (i = 0;i < size;i++) {
        int j;
        for (j = i + 1;j < size;j++) {
            if (udmode == UDMode_Up) {
                if (strcmp(arr[i]->value->order->seller->name->str, arr[j]->value->order->seller->name->str) > 0) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            } else {
                if (strcmp(arr[i]->value->order->seller->name->str, arr[j]->value->order->seller->name->str) < 0) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            }
        }
    }
    head = creatListNodeByListNodes(arr, size);
    free(arr);
    return head;
}

/*
ͨ��SortBySellerPhone����
@param nodelink{����һ����������ڵ�} udmode{������}
@return ListNode*
*/
ListNode* SortBySellerPhone(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortBySellerPhone:����ڵ㲻���ڣ�");
        return NULL;
    }
    rebindListNodeIndex(nodelink);
    ListNode* head = getHeadNode(nodelink);
    ListNode* tail = getTailNode(nodelink);
    ListNode* cur = head;
    int size = tail->index - head->index + 1;
    ListNode** arr = (ListNode**)malloc(sizeof(ListNode*) * size);
    int i = 0;
    while (cur != NULL) {
        arr[i++] = cur;
        cur = cur->next;
    }
    for (i = 0;i < size;i++) {
        int j;
        for (j = i + 1;j < size;j++) {
            if (udmode == UDMode_Up) {
                if (strcmp(arr[i]->value->order->seller->phone->str, arr[j]->value->order->seller->phone->str) > 0) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            } else {
                if (strcmp(arr[i]->value->order->seller->phone->str, arr[j]->value->order->seller->phone->str) < 0) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            }
        }
    }
    head = creatListNodeByListNodes(arr, size);
    free(arr);
    return head;
}


/*
ͨ��SortByBuyerName����
@param nodelink{����һ����������ڵ�} udmode{������}
@return ListNode*
*/
ListNode* SortByBuyerName(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByBuyerName:����ڵ㲻���ڣ�");
        return NULL;
    }
    rebindListNodeIndex(nodelink);
    ListNode* head = getHeadNode(nodelink);
    ListNode* tail = getTailNode(nodelink);
    ListNode* cur = head;
    int size = tail->index - head->index + 1;
    ListNode** arr = (ListNode**)malloc(sizeof(ListNode*) * size);
    int i = 0;
    while (cur != NULL) {
        arr[i++] = cur;
        cur = cur->next;
    }
    for (i = 0;i < size;i++) {
        int j;
        for (j = i + 1;j < size;j++) {
            if (udmode == UDMode_Up) {
                if (strcmp(arr[i]->value->order->buyer->name->str, arr[j]->value->order->buyer->name->str) > 0) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            } else {
                if (strcmp(arr[i]->value->order->buyer->name->str, arr[j]->value->order->buyer->name->str) < 0) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            }
        }
    }
    head = creatListNodeByListNodes(arr, size);
    free(arr);
    return head;
}

/*
ͨ��SortByBuyerPhone����
@param nodelink{����һ����������ڵ�} udmode{������}
@return ListNode*
*/
ListNode* SortByBuyerPhone(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByBuyerPhone:����ڵ㲻���ڣ�");
        return NULL;
    }
    rebindListNodeIndex(nodelink);
    ListNode* head = getHeadNode(nodelink);
    ListNode* tail = getTailNode(nodelink);
    ListNode* cur = head;
    int size = tail->index - head->index + 1;
    ListNode** arr = (ListNode**)malloc(sizeof(ListNode*) * size);
    int i = 0;
    while (cur != NULL) {
        arr[i++] = cur;
        cur = cur->next;
    }
    for (i = 0;i < size;i++) {
        int j;
        for (j = i + 1;j < size;j++) {
            if (udmode == UDMode_Up) {
                if (strcmp(arr[i]->value->order->buyer->phone->str, arr[j]->value->order->buyer->phone->str) > 0) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            } else {
                if (strcmp(arr[i]->value->order->buyer->phone->str, arr[j]->value->order->buyer->phone->str) < 0) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            }
        }
    }
    head = creatListNodeByListNodes(arr, size);
    free(arr);
    return head;
}



/*
ͨ��SortByHandlerName����
@param nodelink{����һ����������ڵ�} udmode{������}
@return ListNode*
*/
ListNode* SortByHandlerName(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByHandlerName:����ڵ㲻���ڣ�");
        return NULL;
    }
    rebindListNodeIndex(nodelink);
    ListNode* head = getHeadNode(nodelink);
    ListNode* tail = getTailNode(nodelink);
    ListNode* cur = head;
    int size = tail->index - head->index + 1;
    ListNode** arr = (ListNode**)malloc(sizeof(ListNode*) * size);
    int i = 0;
    while (cur != NULL) {
        arr[i++] = cur;
        cur = cur->next;
    }
    for (i = 0;i < size;i++) {
        int j;
        for (j = i + 1;j < size;j++) {
            if (udmode == UDMode_Up) {
                if (strcmp(arr[i]->value->order->handler->name->str, arr[j]->value->order->handler->name->str) > 0) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            } else {
                if (strcmp(arr[i]->value->order->handler->name->str, arr[j]->value->order->handler->name->str) < 0) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            }
        }
    }
    head = creatListNodeByListNodes(arr, size);
    free(arr);
    return head;
}

/*
ͨ��SortByHandlerPhone����
@param nodelink{����һ����������ڵ�} udmode{������}
@return ListNode*
*/
ListNode* SortByHandlerPhone(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByHandlerPhone:����ڵ㲻���ڣ�");
        return NULL;
    }
    rebindListNodeIndex(nodelink);
    ListNode* head = getHeadNode(nodelink);
    ListNode* tail = getTailNode(nodelink);
    ListNode* cur = head;
    int size = tail->index - head->index + 1;
    ListNode** arr = (ListNode**)malloc(sizeof(ListNode*) * size);
    int i = 0;
    while (cur != NULL) {
        arr[i++] = cur;
        cur = cur->next;
    }
    for (i = 0;i < size;i++) {
        int j;
        for (j = i + 1;j < size;j++) {
            if (udmode == UDMode_Up) {
                if (strcmp(arr[i]->value->order->handler->phone->str, arr[j]->value->order->handler->phone->str) > 0) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            } else {
                if (strcmp(arr[i]->value->order->handler->phone->str, arr[j]->value->order->handler->phone->str) < 0) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            }
        }
    }
    head = creatListNodeByListNodes(arr, size);
    free(arr);
    return head;
}


/*
ͨ��SortByEmployeeName����
@param nodelink{����һ����������ڵ�} udmode{������}
@return ListNode*
*/
ListNode* SortByEmployeeName(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByEmployeeName:����ڵ㲻���ڣ�");
        return NULL;
    }
    rebindListNodeIndex(nodelink);
    ListNode* head = getHeadNode(nodelink);
    ListNode* tail = getTailNode(nodelink);
    ListNode* cur = head;
    int size = tail->index - head->index + 1;
    ListNode** arr = (ListNode**)malloc(sizeof(ListNode*) * size);
    int i = 0;
    while (cur != NULL) {
        arr[i++] = cur;
        cur = cur->next;
    }
    for (i = 0;i < size;i++) {
        int j;
        for (j = i + 1;j < size;j++) {
            if (udmode == UDMode_Up) {
                if (strcmp(arr[i]->value->order->employee->name->str, arr[j]->value->order->employee->name->str) > 0) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            } else {
                if (strcmp(arr[i]->value->order->employee->name->str, arr[j]->value->order->employee->name->str) < 0) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            }
        }
    }
    head = creatListNodeByListNodes(arr, size);
    free(arr);
    return head;
}

/*
ͨ��SortByEmployeeId����
@param nodelink{����һ����������ڵ�} udmode{������}
@return ListNode*
*/
ListNode* SortByEmployeeId(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByEmployeeId:����ڵ㲻���ڣ�");
        return NULL;
    }
    rebindListNodeIndex(nodelink);
    ListNode* head = getHeadNode(nodelink);
    ListNode* tail = getTailNode(nodelink);
    ListNode* cur = head;
    int size = tail->index - head->index + 1;
    ListNode** arr = (ListNode**)malloc(sizeof(ListNode*) * size);
    int i = 0;
    while (cur != NULL) {
        arr[i++] = cur;
        cur = cur->next;
    }
    for (i = 0;i < size;i++) {
        int j;
        for (j = i + 1;j < size;j++) {
            if (udmode == UDMode_Up) {
                if (arr[i]->value->order->employee->id > arr[j]->value->order->employee->id) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            } else {
                if (arr[i]->value->order->employee->id < arr[j]->value->order->employee->id) {
                    ListNode* tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            }
        }
    }
    head = creatListNodeByListNodes(arr, size);
    free(arr);
    return head;
}


//==========================================================================================
//
//
//                                        ���ʵ��
//
//
//==========================================================================================
ListNode* appendDataByItem(ListNode* nodelink, carInfoItem* item) {
    if (nodelink == NULL) {
        return addListNode(nodelink, item);
    }
    rebindListNodeIndex(nodelink);
    ListNode* tail = getTailNode(nodelink);
    ListNode* newnode = addListNode(tail, item);
    return newnode;
}
ListNode* appendData(ListNode* nodelink, int carId, StringItem* carBrand, StringItem* carModel, int carPrice, int carAge,
int hasRepair, int hasFault, StringItem* faultDescribe,
int status, Date* date,
int inPrice, int outPrice, int estimatePrice, int realPrice,
StringItem* sellername, StringItem* sellerphone,
StringItem* buyername, StringItem* buyerphone,
StringItem* handlername, StringItem* handlerphone,
StringItem* employeename, int employeeid) {
    carInfoItem* item = gen_Empty_carInfoItem();
    item->info->carId = carId;
    freeStringItem(item->info->carBrand);
    item->info->carBrand = carBrand;
    freeStringItem(item->info->carModel);
    item->info->carModel = carModel;
    item->info->carPrice = carPrice;
    item->info->carAge = carAge;
    item->info->fault->hasRepair = hasRepair;
    item->info->fault->hasFault = hasFault;
    freeStringItem(item->info->fault->faultDescribe);
    item->info->fault->faultDescribe = faultDescribe;
    item->order->status = status;
    item->order->date->year = date->year;
    item->order->date->month = date->month;
    item->order->date->day = date->day;
    item->order->inPrice = inPrice;
    item->order->outPrice = outPrice;
    item->order->estimatePrice = estimatePrice;
    item->order->realPrice = realPrice;
    freeStringItem(item->order->seller->name);
    item->order->seller->name = sellername;
    freeStringItem(item->order->seller->phone);
    item->order->seller->phone = sellerphone;
    freeStringItem(item->order->buyer->name);
    item->order->buyer->name = buyername;
    freeStringItem(item->order->buyer->phone);
    item->order->buyer->phone = buyerphone;
    freeStringItem(item->order->handler->name);
    item->order->handler->name = handlername;
    freeStringItem(item->order->handler->phone);
    item->order->handler->phone = handlerphone;
    freeStringItem(item->order->employee->name);
    item->order->employee->name = employeename;
    item->order->employee->id = employeeid;
    return appendDataByItem(nodelink, item);
}
//==========================================================================================
//
//
//                                        ɾ��ʵ��
//
//
//==========================================================================================

ListNode* deleteDataByNode(ListNode* nodelink, ListNode* node) {
    if (nodelink == NULL) {
        mkerrlog("deleteDataByIndex:����ڵ㲻���ڣ�");
        return NULL;
    }
    if (node == NULL) {
        mkerrlog("deleteDataByIndex:�ڵ㲻���ڣ�");
        return NULL;
    }
    rebindListNode(nodelink);
    ListNode* head = getHeadNode(nodelink);
    if (head == node) {
        head = node->next;
    }
    deleteListNode(node);
    return head;
}
ListNode* deleteDataByItem(ListNode* nodelink, carInfoItem* item) {
    if (nodelink == NULL) {
        mkerrlog("deleteDataByItem:����ڵ㲻���ڣ�");
        return NULL;
    }
    rebindListNode(nodelink);
    ListNode* head = getHeadNode(nodelink);
    ListNode* cur = head;
    while (cur != NULL) {
        if (cur->value == item) {
            break;
        }
        cur = cur->next;
    }
    if (cur == NULL) {
        char* errmsg = malloc(sizeof(char) * 200);
        memset(errmsg, 0, 200);
        sprintf(errmsg, "deleteDataByIndex:û���ҵ�carInfoItem��ַ��%d�Ľڵ㣡", item);
        mkerrlog(errmsg);
        free(errmsg);
        return NULL;
    }
    return deleteDataByNode(nodelink, cur);
}
ListNode* deleteDataByCarId(ListNode* nodelink, int carId) {
    if (nodelink == NULL) {
        mkerrlog("deleteDataByCarId:����ڵ㲻���ڣ�");
        return NULL;
    }
    rebindListNode(nodelink);
    ListNode* head = getHeadNode(nodelink);
    ListNode* cur = head;
    while (cur != NULL) {
        if (cur->value->info->carId == carId) {
            break;
        }
        cur = cur->next;
    }
    if (cur == NULL) {
        char* errmsg = malloc(sizeof(char) * 200);
        memset(errmsg, 0, 200);
        sprintf(errmsg, "deleteDataByIndex:û���ҵ�carIdΪ%d�Ľڵ㣡", carId);
        mkerrlog(errmsg);
        free(errmsg);
        return NULL;
    }
    return deleteDataByNode(nodelink, cur);
}
ListNode* deleteDataByIndex(ListNode* nodelink, int index) {
    if (nodelink == NULL) {
        mkerrlog("deleteDataByIndex:����ڵ㲻���ڣ�");
        return NULL;
    }
    rebindListNode(nodelink);
    ListNode* head = getHeadNode(nodelink);
    ListNode* cur = head;
    while (cur != NULL) {
        if (cur->index == index) {
            break;
        }
        cur = cur->next;
    }
    if (cur == NULL) {
        char* errmsg = malloc(sizeof(char) * 200);
        memset(errmsg, 0, 200);
        sprintf(errmsg, "deleteDataByIndex:û���ҵ���%d���ڵ㣡", index);
        mkerrlog(errmsg);
        free(errmsg);
        return NULL;
    }
    return deleteDataByNode(nodelink, cur);
}

//==========================================================================================
//
//
//                                        �޸�ʵ��
//
//
//==========================================================================================

carInfoItem* modifyDataByItem(carInfoItem* item, StringItem* Key, StringItem* Value) {
    if (item == NULL) {
        mkerrlog("modifyDataByItem:carInfoItem�����ڣ�");
        return NULL;
    }
    if (strcmp(Key->str, "carId") == 0 || strcmp(Key->str, "�������") == 0) {
        int n;
        sscanf(Value->str, "%d", &n);
        item->info->carId = n;
        freeStringItem(Value);
    } else if (strcmp(Key->str, "carBrand") == 0 || strcmp(Key->str, "����Ʒ��") == 0) {
        freeStringItem(item->info->carBrand);
        item->info->carBrand = Value;
    } else if (strcmp(Key->str, "carModel") == 0 || strcmp(Key->str, "�����ͺ�") == 0) {
        freeStringItem(item->info->carModel);
        item->info->carModel = Value;
    } else if (strcmp(Key->str, "carPrice") == 0 || strcmp(Key->str, "ԭ��") == 0) {
        int n;
        sscanf(Value->str, "%d", &n);
        item->info->carPrice = n;
        freeStringItem(Value);
    } else if (strcmp(Key->str, "carAge") == 0 || strcmp(Key->str, "����") == 0) {
        int n;
        sscanf(Value->str, "%d", &n);
        item->info->carAge = n;
        freeStringItem(Value);
    } else if (strcmp(Key->str, "hasRepair") == 0 || strcmp(Key->str, "�Ƿ��д���") == 0) {
        if (strcmp(Value->str, "��") == 0 || strcmp(Value->str, "1") == 0) {
            item->info->fault->hasRepair = 1;
            freeStringItem(Value);
        } else if (strcmp(Value->str, "��") == 0 || strcmp(Value->str, "0") == 0) {
            item->info->fault->hasRepair = 0;
            freeStringItem(Value);
        } else {
            mkerrlog("modifyDataByItem:hasRepairֵ����");
            freeStringItem(Value);
            return NULL;
        }
    } else if (strcmp(Key->str, "hasFault") == 0 || strcmp(Key->str, "�Ƿ��й���") == 0) {
        if (strcmp(Value->str, "��") == 0 || strcmp(Value->str, "1") == 0) {
            item->info->fault->hasFault = 1;
            freeStringItem(Value);
        } else if (strcmp(Value->str, "��") == 0 || strcmp(Value->str, "0") == 0) {
            item->info->fault->hasFault = 0;
            freeStringItem(Value);
        } else {
            mkerrlog("modifyDataByItem:hasFaultֵ����");
            freeStringItem(Value);
            return NULL;
        }
    } else if (strcmp(Key->str, "faultDescribe") == 0 || strcmp(Key->str, "��������") == 0) {
        freeStringItem(item->info->carModel);
        item->info->fault->faultDescribe = Value;
    } else if (strcmp(Key->str, "status") == 0 || strcmp(Key->str, "״̬") == 0) {
        if (strcmp(Value->str, "�ڿ�") == 0 || strcmp(Value->str, "1") == 0) {
            item->order->status = 1;
            freeStringItem(Value);
        } else if (strcmp(Value->str, "����") == 0 || strcmp(Value->str, "2") == 0) {
            item->order->status = 2;
            freeStringItem(Value);
        } else if (strcmp(Value->str, "Ԥ��") == 0 || strcmp(Value->str, "3") == 0) {
            item->order->status = 3;
            freeStringItem(Value);
        } else if (strcmp(Value->str, "����") == 0 || strcmp(Value->str, "4") == 0) {
            item->order->status = 4;
            freeStringItem(Value);
        } else {
            mkerrlog("modifyDataByItem:statusֵ����");
            freeStringItem(Value);
            return NULL;
        }
    } else if (strcmp(Key->str, "date") == 0 || strcmp(Key->str, "����") == 0) {
        int y, m, d;
        sscanf(Value->str, "%d/%d/%d", &y, &m, &d);
        item->order->date->year = y;
        item->order->date->month = m;
        item->order->date->day = d;
        freeStringItem(Value);
    } else if (strcmp(Key->str, "inPrice") == 0 || strcmp(Key->str, "����") == 0) {
        int n;
        sscanf(Value->str, "%d", &n);
        item->order->inPrice = n;
        freeStringItem(Value);
    } else if (strcmp(Key->str, "outPrice") == 0 || strcmp(Key->str, "���ۼ�") == 0) {
        int n;
        sscanf(Value->str, "%d", &n);
        item->order->outPrice = n;
        freeStringItem(Value);
    } else if (strcmp(Key->str, "estimatePrice") == 0 || strcmp(Key->str, "���Ƽ�") == 0) {
        int n;
        sscanf(Value->str, "%d", &n);
        item->order->estimatePrice = n;
        freeStringItem(Value);
    } else if (strcmp(Key->str, "realPrice") == 0 || strcmp(Key->str, "ʵ�ۼ�") == 0) {
        if (strcmp(Value->str, "δ��") == 0) {
            item->order->realPrice = -1;
        } else {
            int n;
            sscanf(Value->str, "%d", &n);
            item->order->realPrice = n;
        }
        freeStringItem(Value);
    } else if (strcmp(Key->str, "sellerName") == 0 || strcmp(Key->str, "��������") == 0) {
        freeStringItem(item->order->seller->name);
        item->order->seller->name = Value;
    } else if (strcmp(Key->str, "sellerPhone") == 0 || strcmp(Key->str, "���ҵ绰") == 0) {
        freeStringItem(item->order->seller->phone);
        item->order->seller->phone = Value;
    } else if (strcmp(Key->str, "buyerName") == 0 || strcmp(Key->str, "�������") == 0) {
        freeStringItem(item->order->buyer->name);
        item->order->buyer->name = Value;
    } else if (strcmp(Key->str, "buyerPhone") == 0 || strcmp(Key->str, "��ҵ绰") == 0) {
        freeStringItem(item->order->buyer->phone);
        item->order->buyer->phone = Value;
    } else if (strcmp(Key->str, "handlerName") == 0 || strcmp(Key->str, "����������") == 0) {
        freeStringItem(item->order->handler->name);
        item->order->handler->name = Value;
    } else if (strcmp(Key->str, "handlerPhone") == 0 || strcmp(Key->str, "�����˵绰") == 0) {
        freeStringItem(item->order->handler->phone);
        item->order->handler->phone = Value;
    } else if (strcmp(Key->str, "employeeName") == 0 || strcmp(Key->str, "Ա������") == 0) {
        freeStringItem(item->order->employee->name);
        item->order->employee->name = Value;
    } else if (strcmp(Key->str, "employeeId") == 0 || strcmp(Key->str, "Ա�����") == 0) {
        int n;
        sscanf(Value->str, "%d", &n);
        item->order->employee->id = n;
        freeStringItem(Value);
    } else {
        char* errmsg = malloc(sizeof(char) * (200 + Key->size));
        memset(errmsg, 0, 200 + Key->size);
        sprintf(errmsg, "modifyData:û���ҵ�%s���޸��", Key->str);
        mkerrlog(errmsg);
        free(errmsg);
        return NULL;
    }
    freeStringItem(Key);
    return item;
}
ListNode* modifyDataByNode(ListNode* nodelink, StringItem* Key, StringItem* Value) {
    if (nodelink == NULL) {
        mkerrlog("modifyData:����ڵ㲻���ڣ�");
        return NULL;
    }
    modifyDataByItem(nodelink->value, Key, Value);
    return nodelink;
}