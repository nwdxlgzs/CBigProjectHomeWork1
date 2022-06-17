#include "database.h"
/**
 * @brief 数据库
 * 这是抽象化出来的数据库，底层是mdb.c驱动数据，这是提供上层包装的接口
 *
 */


 //==========================================================================================
 //
 //
 //                                        查询序实现
 //
 //
 //==========================================================================================

  /*
  通过QueryByCarId查询到对应链表节点值
  @param nodelink{任意一个数据链表节点} carId{车辆编号}
  @return carInfoItem*
  这是唯一一个能确定某一个的方法了
  */
carInfoItem* QueryByCarId(ListNode* nodelink, int carId) {
    if (nodelink == NULL) {
        mkerrlog("QueryByCarId:链表节点不存在！");
        return NULL;
    }
    if (carId < 0) {
        mkerrlog("QueryByCarId:carId不能小于0！");
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
通过QueryByCarBrand查询到对应链表节点值数组的指针
@param nodelink{任意一个数据链表节点} carBrand{车辆品牌} len{统计长度}
@return carInfoItem**
*/
carInfoItem** QueryByCarBrand(ListNode* nodelink, StringItem* carBrand, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByCarBrand:链表节点不存在！");
        return NULL;
    }
    if (carBrand == NULL) {
        mkerrlog("QueryByCarBrand:carBrand不存在！");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByCarBrand:len不能小于0！");
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
    *len = i;//返回统计长度
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
通过QueryByCarModel查询到对应链表节点值数组的指针
@param nodelink{任意一个数据链表节点} carModel{车辆品牌} len{统计长度}
@return carInfoItem**
*/
carInfoItem** QueryByCarModel(ListNode* nodelink, StringItem* carModel, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByCarModel:链表节点不存在！");
        return NULL;
    }
    if (carModel == NULL) {
        mkerrlog("QueryByCarModel:carModel不存在！");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByCarModel:len不能小于0！");
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
    *len = i;//返回统计长度
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
通过QueryByCarPrice查询到对应链表节点值数组的指针
@param nodelink{任意一个数据链表节点} min{最低值} max{最高值} len{统计长度}
@return carInfoItem**
*/
carInfoItem** QueryByCarPrice(ListNode* nodelink, int min, int max, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByCarPrice:链表节点不存在！");
        return NULL;
    }
    if (min < 0) {
        mkerrlog("QueryByCarPrice:min不能是负数！");
        return NULL;
    }
    if (max < 0) {
        mkerrlog("QueryByCarPrice:max不能是负数！");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByCarPrice:len不能小于0！");
        return NULL;
    }
    //我就不报错了，大小互换就是了
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
    *len = i;//返回统计长度
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}



/*
通过QueryByCarAge查询到对应链表节点值数组的指针
@param nodelink{任意一个数据链表节点} min{最低值} max{最高值} len{统计长度}
@return carInfoItem**
*/
carInfoItem** QueryByCarAge(ListNode* nodelink, int min, int max, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByCarAge:链表节点不存在！");
        return NULL;
    }
    if (min < 0) {
        mkerrlog("QueryByCarAge:min不能是负数！");
        return NULL;
    }
    if (max < 0) {
        mkerrlog("QueryByCarAge:max不能是负数！");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByCarAge:len不能小于0！");
        return NULL;
    }
    //我就不报错了，大小互换就是了
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
    *len = i;//返回统计长度
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
通过QueryByCarHasRepair查询到对应链表节点值数组的指针
@param nodelink{任意一个数据链表节点} unselect{反选} len{统计长度}
@return carInfoItem**
*/
carInfoItem** QueryByCarHasRepair(ListNode* nodelink, enum BooleanDef unselect, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByCarAge:链表节点不存在！");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByCarAge:len不能小于0！");
        return NULL;
    }
    carInfoItem** dst = (carInfoItem**)malloc(sizeof(carInfoItem*) * (*len));
    ListNode* head = getHeadNode(nodelink);
    ListNode* cur = head;
    int i = 0;
    while (cur != NULL) {
        int hasRepair = cur->value->info->fault->hasRepair;
        if (unselect) {//反选
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
    *len = i;//返回统计长度
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
通过QueryByCarHasFault查询到对应链表节点值数组的指针
@param nodelink{任意一个数据链表节点} unselect{反选} len{统计长度}
@return carInfoItem**
*/
carInfoItem** QueryByCarHasFault(ListNode* nodelink, enum BooleanDef unselect, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByCarHasFault:链表节点不存在！");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByCarHasFault:len不能小于0！");
        return NULL;
    }
    carInfoItem** dst = (carInfoItem**)malloc(sizeof(carInfoItem*) * (*len));
    ListNode* head = getHeadNode(nodelink);
    ListNode* cur = head;
    int i = 0;
    while (cur != NULL) {
        int hasRepair = cur->value->info->fault->hasFault;
        if (unselect) {//反选
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
    *len = i;//返回统计长度
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
通过QueryByCarStatus查询到对应链表节点值数组的指针
@param nodelink{任意一个数据链表节点} unselect{反选} len{统计长度}
@return carInfoItem**
*/
carInfoItem** QueryByCarStatus(ListNode* nodelink, enum carStatus status, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByCarStatus:链表节点不存在！");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByCarStatus:len不能小于0！");
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
    *len = i;//返回统计长度
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
通过QueryByDate查询到对应链表节点值数组的指针
@param nodelink{任意一个数据链表节点} min{起始天} max{终止天} len{统计长度}
@return carInfoItem**
*/
carInfoItem** QueryByDate(ListNode* nodelink, Date* min, Date* max, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByDate:链表节点不存在！");
        return NULL;
    }
    if (min < 0) {
        mkerrlog("QueryByDate:min不能是负数！");
        return NULL;
    }
    if (max < 0) {
        mkerrlog("QueryByDate:max不能是负数！");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByDate:len不能小于0！");
        return NULL;
    }
    //我就不报错了，大小互换就是了
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
        if (date->year >= min->year && date->year <= max->year) {//年份比较
            if (date->month >= min->month && date->month <= max->month) {//月份比较
                if (date->day >= min->day && date->day <= max->day) {//日期比较
                    dst[i++] = cur->value;
                }
            }
        }
        cur = cur->next;
    }
    *len = i;//返回统计长度
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}



/*
通过QueryByInPrice查询到对应链表节点值数组的指针
@param nodelink{任意一个数据链表节点} min{起始价格} max{终止价格} len{统计长度}
@return carInfoItem**
*/
carInfoItem** QueryByInPrice(ListNode* nodelink, int min, int max, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByInPrice:链表节点不存在！");
        return NULL;
    }
    if (min < 0) {
        mkerrlog("QueryByInPrice:min不能是负数！");
        return NULL;
    }
    if (max < 0) {
        mkerrlog("QueryByInPrice:max不能是负数！");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByDate:len不能小于0！");
        return NULL;
    }
    //我就不报错了，大小互换就是了
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
    *len = i;//返回统计长度
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
通过QueryByOutPrice查询到对应链表节点值数组的指针
@param nodelink{任意一个数据链表节点} min{起始价格} max{终止价格} len{统计长度}
@return carInfoItem**
*/
carInfoItem** QueryByOutPrice(ListNode* nodelink, int min, int max, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByOutPrice:链表节点不存在！");
        return NULL;
    }
    if (min < 0) {
        mkerrlog("QueryByOutPrice:min不能是负数！");
        return NULL;
    }
    if (max < 0) {
        mkerrlog("QueryByOutPrice:max不能是负数！");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByOutPrice:len不能小于0！");
        return NULL;
    }
    //我就不报错了，大小互换就是了
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
    *len = i;//返回统计长度
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
通过QueryByEstimatePrice查询到对应链表节点值数组的指针
@param nodelink{任意一个数据链表节点} min{起始价格} max{终止价格} len{统计长度}
@return carInfoItem**
*/
carInfoItem** QueryByEstimatePrice(ListNode* nodelink, int min, int max, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByEstimatePrice:链表节点不存在！");
        return NULL;
    }
    if (min < 0) {
        mkerrlog("QueryByEstimatePrice:min不能是负数！");
        return NULL;
    }
    if (max < 0) {
        mkerrlog("QueryByEstimatePrice:max不能是负数！");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByEstimatePrice:len不能小于0！");
        return NULL;
    }
    //我就不报错了，大小互换就是了
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
    *len = i;//返回统计长度
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
通过QueryByRealPrice查询到对应链表节点值数组的指针
@param nodelink{任意一个数据链表节点} min{起始价格} max{终止价格} len{统计长度}
@return carInfoItem**
*/
carInfoItem** QueryByRealPrice(ListNode* nodelink, int min, int max, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByRealPrice:链表节点不存在！");
        return NULL;
    }
    if (min < 0) {
        mkerrlog("QueryByRealPrice:min不能是负数！");
        return NULL;
    }
    if (max < 0) {
        mkerrlog("QueryByRealPrice:max不能是负数！");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByRealPrice:len不能小于0！");
        return NULL;
    }
    //我就不报错了，大小互换就是了
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
    *len = i;//返回统计长度
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
通过QueryByOnSale查询到对应链表节点值数组的指针
@param nodelink{任意一个数据链表节点} unselect{反选} len{统计长度}
@return carInfoItem**
*/
carInfoItem** QueryByOnSale(ListNode* nodelink, enum BooleanDef unselect, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByOnSale:链表节点不存在！");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByOnSale:len不能小于0！");
        return NULL;
    }
    carInfoItem** dst = (carInfoItem**)malloc(sizeof(carInfoItem*) * (*len));
    ListNode* head = getHeadNode(nodelink);
    ListNode* cur = head;
    int i = 0;
    while (cur != NULL) {
        int price = cur->value->order->realPrice;
        if (unselect) {
            if (price != -1) {//已售
                dst[i++] = cur->value;
            }
        } else {
            if (price == -1) {//未售
                dst[i++] = cur->value;
            }
        }
        cur = cur->next;
    }
    *len = i;//返回统计长度
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
通过QueryBySellerName查询到对应链表节点值数组的指针
@param nodelink{任意一个数据链表节点} name{名字} len{统计长度}
@return carInfoItem**
*/
carInfoItem** QueryBySellerName(ListNode* nodelink, StringItem* name, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryBySellerName:链表节点不存在！");
        return NULL;
    }
    if (name == NULL) {
        mkerrlog("QueryBySellerName:name不能为空！");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryBySellerName:len不能小于0！");
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
    *len = i;//返回统计长度
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
通过QueryBySellerPhone查询到对应链表节点值数组的指针
@param nodelink{任意一个数据链表节点} phone{手机号} len{统计长度}
@return carInfoItem**
*/
carInfoItem** QueryBySellerPhone(ListNode* nodelink, StringItem* phone, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryBySellerPhone:链表节点不存在！");
        return NULL;
    }
    if (phone == NULL) {
        mkerrlog("QueryBySellerPhone:phone不能为空！");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryBySellerPhone:len不能小于0！");
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
    *len = i;//返回统计长度
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
通过QueryByBuyerName查询到对应链表节点值数组的指针
@param nodelink{任意一个数据链表节点} name{名字} len{统计长度}
@return carInfoItem**
*/
carInfoItem** QueryByBuyerName(ListNode* nodelink, StringItem* name, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByBuyerName:链表节点不存在！");
        return NULL;
    }
    if (name == NULL) {
        mkerrlog("QueryByBuyerName:name不能为空！");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByBuyerName:len不能小于0！");
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
    *len = i;//返回统计长度
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
通过QueryByBuyerPhone查询到对应链表节点值数组的指针
@param nodelink{任意一个数据链表节点} phone{手机号} len{统计长度}
@return carInfoItem**
*/
carInfoItem** QueryByBuyerPhone(ListNode* nodelink, StringItem* phone, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByBuyerPhone:链表节点不存在！");
        return NULL;
    }
    if (phone == NULL) {
        mkerrlog("QueryByBuyerPhone:phone不能为空！");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByBuyerPhone:len不能小于0！");
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
    *len = i;//返回统计长度
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
通过QueryByHandlerName查询到对应链表节点值数组的指针
@param nodelink{任意一个数据链表节点} name{名字} len{统计长度}
@return carInfoItem**
*/
carInfoItem** QueryByHandlerName(ListNode* nodelink, StringItem* name, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByHandlerName:链表节点不存在！");
        return NULL;
    }
    if (name == NULL) {
        mkerrlog("QueryByHandlerName:name不能为空！");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByHandlerName:len不能小于0！");
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
    *len = i;//返回统计长度
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
通过QueryByHandlerPhone查询到对应链表节点值数组的指针
@param nodelink{任意一个数据链表节点} phone{手机号} len{统计长度}
@return carInfoItem**
*/
carInfoItem** QueryByHandlerPhone(ListNode* nodelink, StringItem* phone, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByHandlerPhone:链表节点不存在！");
        return NULL;
    }
    if (phone == NULL) {
        mkerrlog("QueryByHandlerPhone:phone不能为空！");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByHandlerPhone:len不能小于0！");
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
    *len = i;//返回统计长度
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}



/*
通过QueryByEmployeeName查询到对应链表节点值数组的指针
@param nodelink{任意一个数据链表节点} name{名字} len{统计长度}
@return carInfoItem**
*/
carInfoItem** QueryByEmployeeName(ListNode* nodelink, StringItem* name, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByEmployeeName:链表节点不存在！");
        return NULL;
    }
    if (name == NULL) {
        mkerrlog("QueryByEmployeeName:name不能为空！");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByEmployeeName:len不能小于0！");
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
    *len = i;//返回统计长度
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}


/*
通过QueryByEmployeeId查询到对应链表节点值数组的指针
@param nodelink{任意一个数据链表节点} phone{手机号} len{统计长度}
@return carInfoItem**
*/
carInfoItem** QueryByEmployeeId(ListNode* nodelink, int id, int* len) {
    if (nodelink == NULL) {
        mkerrlog("QueryByEmployeeId:链表节点不存在！");
        return NULL;
    }
    if (id < 0) {
        mkerrlog("QueryByEmployeeId:id不能为负数！");
        return NULL;
    }
    if (*len < 0) {
        mkerrlog("QueryByEmployeeId:len不能小于0！");
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
    *len = i;//返回统计长度
    if (i == 0) {
        free(dst);
        return NULL;
    }
    return dst;
}

//==========================================================================================
//
//
//                                        排序实现
//
//
//==========================================================================================

/*
通过SortByCarId排序
@param nodelink{任意一个数据链表节点} udmode{升降序}
@return ListNode*
*/
ListNode* SortByCarId(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByCarId:链表节点不存在！");
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
通过SortByCarBrand排序
@param nodelink{任意一个数据链表节点} udmode{升降序}
@return ListNode*
*/
ListNode* SortByCarBrand(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByCarBrand:链表节点不存在！");
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
通过SortByCarModel排序
@param nodelink{任意一个数据链表节点} udmode{升降序}
@return ListNode*
*/
ListNode* SortByCarModel(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByCarModel:链表节点不存在！");
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
通过SortByCarPrice排序
@param nodelink{任意一个数据链表节点} udmode{升降序}
@return ListNode*
*/
ListNode* SortByCarPrice(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByCarPrice:链表节点不存在！");
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
通过SortByCarAge排序
@param nodelink{任意一个数据链表节点} udmode{升降序}
@return ListNode*
*/
ListNode* SortByCarAge(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByCarAge:链表节点不存在！");
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
通过SortByCarHasRepair排序
@param nodelink{任意一个数据链表节点} udmode{升降序}
@return ListNode*
*/
ListNode* SortByCarHasRepair(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByCarHasRepair:链表节点不存在！");
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
通过SortByCarHasFault排序
@param nodelink{任意一个数据链表节点} udmode{升降序}
@return ListNode*
*/
ListNode* SortByCarHasFault(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByCarHasFault:链表节点不存在！");
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
通过SortByCarStatus排序
@param nodelink{任意一个数据链表节点} udmode{升降序}
@return ListNode*
*/
ListNode* SortByCarStatus(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByCarStatus:链表节点不存在！");
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
通过SortByDate排序
@param nodelink{任意一个数据链表节点} udmode{升降序}
@return ListNode*
*/
ListNode* SortByDate(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByDate:链表节点不存在！");
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
通过SortByInPrice排序
@param nodelink{任意一个数据链表节点} udmode{升降序}
@return ListNode*
*/
ListNode* SortByInPrice(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByInPrice:链表节点不存在！");
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
通过SortByOutPrice排序
@param nodelink{任意一个数据链表节点} udmode{升降序}
@return ListNode*
*/
ListNode* SortByOutPrice(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByOutPrice:链表节点不存在！");
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
通过SortByEstimatePrice排序
@param nodelink{任意一个数据链表节点} udmode{升降序}
@return ListNode*
*/
ListNode* SortByEstimatePrice(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByEstimatePrice:链表节点不存在！");
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
通过SortByRealPrice排序
@param nodelink{任意一个数据链表节点} udmode{升降序}
@return ListNode*
*/
ListNode* SortByRealPrice(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByRealPrice:链表节点不存在！");
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
通过SortBySellerName排序
@param nodelink{任意一个数据链表节点} udmode{升降序}
@return ListNode*
*/
ListNode* SortBySellerName(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortBySellerName:链表节点不存在！");
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
通过SortBySellerPhone排序
@param nodelink{任意一个数据链表节点} udmode{升降序}
@return ListNode*
*/
ListNode* SortBySellerPhone(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortBySellerPhone:链表节点不存在！");
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
通过SortByBuyerName排序
@param nodelink{任意一个数据链表节点} udmode{升降序}
@return ListNode*
*/
ListNode* SortByBuyerName(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByBuyerName:链表节点不存在！");
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
通过SortByBuyerPhone排序
@param nodelink{任意一个数据链表节点} udmode{升降序}
@return ListNode*
*/
ListNode* SortByBuyerPhone(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByBuyerPhone:链表节点不存在！");
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
通过SortByHandlerName排序
@param nodelink{任意一个数据链表节点} udmode{升降序}
@return ListNode*
*/
ListNode* SortByHandlerName(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByHandlerName:链表节点不存在！");
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
通过SortByHandlerPhone排序
@param nodelink{任意一个数据链表节点} udmode{升降序}
@return ListNode*
*/
ListNode* SortByHandlerPhone(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByHandlerPhone:链表节点不存在！");
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
通过SortByEmployeeName排序
@param nodelink{任意一个数据链表节点} udmode{升降序}
@return ListNode*
*/
ListNode* SortByEmployeeName(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByEmployeeName:链表节点不存在！");
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
通过SortByEmployeeId排序
@param nodelink{任意一个数据链表节点} udmode{升降序}
@return ListNode*
*/
ListNode* SortByEmployeeId(ListNode* nodelink, enum UDMode udmode) {
    if (nodelink == NULL) {
        mkerrlog("SortByEmployeeId:链表节点不存在！");
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
//                                        添加实现
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
//                                        删除实现
//
//
//==========================================================================================

ListNode* deleteDataByNode(ListNode* nodelink, ListNode* node) {
    if (nodelink == NULL) {
        mkerrlog("deleteDataByIndex:链表节点不存在！");
        return NULL;
    }
    if (node == NULL) {
        mkerrlog("deleteDataByIndex:节点不存在！");
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
        mkerrlog("deleteDataByItem:链表节点不存在！");
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
        sprintf(errmsg, "deleteDataByIndex:没有找到carInfoItem地址是%d的节点！", item);
        mkerrlog(errmsg);
        free(errmsg);
        return NULL;
    }
    return deleteDataByNode(nodelink, cur);
}
ListNode* deleteDataByCarId(ListNode* nodelink, int carId) {
    if (nodelink == NULL) {
        mkerrlog("deleteDataByCarId:链表节点不存在！");
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
        sprintf(errmsg, "deleteDataByIndex:没有找到carId为%d的节点！", carId);
        mkerrlog(errmsg);
        free(errmsg);
        return NULL;
    }
    return deleteDataByNode(nodelink, cur);
}
ListNode* deleteDataByIndex(ListNode* nodelink, int index) {
    if (nodelink == NULL) {
        mkerrlog("deleteDataByIndex:链表节点不存在！");
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
        sprintf(errmsg, "deleteDataByIndex:没有找到第%d个节点！", index);
        mkerrlog(errmsg);
        free(errmsg);
        return NULL;
    }
    return deleteDataByNode(nodelink, cur);
}

//==========================================================================================
//
//
//                                        修改实现
//
//
//==========================================================================================

carInfoItem* modifyDataByItem(carInfoItem* item, StringItem* Key, StringItem* Value) {
    if (item == NULL) {
        mkerrlog("modifyDataByItem:carInfoItem不存在！");
        return NULL;
    }
    if (strcmp(Key->str, "carId") == 0 || strcmp(Key->str, "车辆编号") == 0) {
        int n;
        sscanf(Value->str, "%d", &n);
        item->info->carId = n;
        freeStringItem(Value);
    } else if (strcmp(Key->str, "carBrand") == 0 || strcmp(Key->str, "车辆品牌") == 0) {
        freeStringItem(item->info->carBrand);
        item->info->carBrand = Value;
    } else if (strcmp(Key->str, "carModel") == 0 || strcmp(Key->str, "车辆型号") == 0) {
        freeStringItem(item->info->carModel);
        item->info->carModel = Value;
    } else if (strcmp(Key->str, "carPrice") == 0 || strcmp(Key->str, "原价") == 0) {
        int n;
        sscanf(Value->str, "%d", &n);
        item->info->carPrice = n;
        freeStringItem(Value);
    } else if (strcmp(Key->str, "carAge") == 0 || strcmp(Key->str, "车龄") == 0) {
        int n;
        sscanf(Value->str, "%d", &n);
        item->info->carAge = n;
        freeStringItem(Value);
    } else if (strcmp(Key->str, "hasRepair") == 0 || strcmp(Key->str, "是否有大修") == 0) {
        if (strcmp(Value->str, "是") == 0 || strcmp(Value->str, "1") == 0) {
            item->info->fault->hasRepair = 1;
            freeStringItem(Value);
        } else if (strcmp(Value->str, "否") == 0 || strcmp(Value->str, "0") == 0) {
            item->info->fault->hasRepair = 0;
            freeStringItem(Value);
        } else {
            mkerrlog("modifyDataByItem:hasRepair值错误！");
            freeStringItem(Value);
            return NULL;
        }
    } else if (strcmp(Key->str, "hasFault") == 0 || strcmp(Key->str, "是否有故障") == 0) {
        if (strcmp(Value->str, "是") == 0 || strcmp(Value->str, "1") == 0) {
            item->info->fault->hasFault = 1;
            freeStringItem(Value);
        } else if (strcmp(Value->str, "否") == 0 || strcmp(Value->str, "0") == 0) {
            item->info->fault->hasFault = 0;
            freeStringItem(Value);
        } else {
            mkerrlog("modifyDataByItem:hasFault值错误！");
            freeStringItem(Value);
            return NULL;
        }
    } else if (strcmp(Key->str, "faultDescribe") == 0 || strcmp(Key->str, "故障描述") == 0) {
        freeStringItem(item->info->carModel);
        item->info->fault->faultDescribe = Value;
    } else if (strcmp(Key->str, "status") == 0 || strcmp(Key->str, "状态") == 0) {
        if (strcmp(Value->str, "在库") == 0 || strcmp(Value->str, "1") == 0) {
            item->order->status = 1;
            freeStringItem(Value);
        } else if (strcmp(Value->str, "出库") == 0 || strcmp(Value->str, "2") == 0) {
            item->order->status = 2;
            freeStringItem(Value);
        } else if (strcmp(Value->str, "预定") == 0 || strcmp(Value->str, "3") == 0) {
            item->order->status = 3;
            freeStringItem(Value);
        } else if (strcmp(Value->str, "已售") == 0 || strcmp(Value->str, "4") == 0) {
            item->order->status = 4;
            freeStringItem(Value);
        } else {
            mkerrlog("modifyDataByItem:status值错误！");
            freeStringItem(Value);
            return NULL;
        }
    } else if (strcmp(Key->str, "date") == 0 || strcmp(Key->str, "日期") == 0) {
        int y, m, d;
        sscanf(Value->str, "%d/%d/%d", &y, &m, &d);
        item->order->date->year = y;
        item->order->date->month = m;
        item->order->date->day = d;
        freeStringItem(Value);
    } else if (strcmp(Key->str, "inPrice") == 0 || strcmp(Key->str, "进价") == 0) {
        int n;
        sscanf(Value->str, "%d", &n);
        item->order->inPrice = n;
        freeStringItem(Value);
    } else if (strcmp(Key->str, "outPrice") == 0 || strcmp(Key->str, "销售价") == 0) {
        int n;
        sscanf(Value->str, "%d", &n);
        item->order->outPrice = n;
        freeStringItem(Value);
    } else if (strcmp(Key->str, "estimatePrice") == 0 || strcmp(Key->str, "估计价") == 0) {
        int n;
        sscanf(Value->str, "%d", &n);
        item->order->estimatePrice = n;
        freeStringItem(Value);
    } else if (strcmp(Key->str, "realPrice") == 0 || strcmp(Key->str, "实售价") == 0) {
        if (strcmp(Value->str, "未售") == 0) {
            item->order->realPrice = -1;
        } else {
            int n;
            sscanf(Value->str, "%d", &n);
            item->order->realPrice = n;
        }
        freeStringItem(Value);
    } else if (strcmp(Key->str, "sellerName") == 0 || strcmp(Key->str, "卖家姓名") == 0) {
        freeStringItem(item->order->seller->name);
        item->order->seller->name = Value;
    } else if (strcmp(Key->str, "sellerPhone") == 0 || strcmp(Key->str, "卖家电话") == 0) {
        freeStringItem(item->order->seller->phone);
        item->order->seller->phone = Value;
    } else if (strcmp(Key->str, "buyerName") == 0 || strcmp(Key->str, "买家姓名") == 0) {
        freeStringItem(item->order->buyer->name);
        item->order->buyer->name = Value;
    } else if (strcmp(Key->str, "buyerPhone") == 0 || strcmp(Key->str, "买家电话") == 0) {
        freeStringItem(item->order->buyer->phone);
        item->order->buyer->phone = Value;
    } else if (strcmp(Key->str, "handlerName") == 0 || strcmp(Key->str, "经手人姓名") == 0) {
        freeStringItem(item->order->handler->name);
        item->order->handler->name = Value;
    } else if (strcmp(Key->str, "handlerPhone") == 0 || strcmp(Key->str, "经手人电话") == 0) {
        freeStringItem(item->order->handler->phone);
        item->order->handler->phone = Value;
    } else if (strcmp(Key->str, "employeeName") == 0 || strcmp(Key->str, "员工姓名") == 0) {
        freeStringItem(item->order->employee->name);
        item->order->employee->name = Value;
    } else if (strcmp(Key->str, "employeeId") == 0 || strcmp(Key->str, "员工编号") == 0) {
        int n;
        sscanf(Value->str, "%d", &n);
        item->order->employee->id = n;
        freeStringItem(Value);
    } else {
        char* errmsg = malloc(sizeof(char) * (200 + Key->size));
        memset(errmsg, 0, 200 + Key->size);
        sprintf(errmsg, "modifyData:没有找到%s的修改项！", Key->str);
        mkerrlog(errmsg);
        free(errmsg);
        return NULL;
    }
    freeStringItem(Key);
    return item;
}
ListNode* modifyDataByNode(ListNode* nodelink, StringItem* Key, StringItem* Value) {
    if (nodelink == NULL) {
        mkerrlog("modifyData:链表节点不存在！");
        return NULL;
    }
    modifyDataByItem(nodelink->value, Key, Value);
    return nodelink;
}