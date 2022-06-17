//peekTool.h

#ifndef PEEKTOOL_H
#define PEEKTOOL_H
#include "common.h"
#include "utils.h"
enum peekEnum {
    peekEnum_START = 0,

    peekEnum_carId,//车辆编号
    peekEnum_carBrand,//车辆品牌
    peekEnum_carModel,//车辆型号
    peekEnum_carPrice,//车辆原价
    peekEnum_carAge,//车龄
    peekEnum_hasRepair,//是否有大修
    peekEnum_hasFault,//是否有故障
    peekEnum_faultDescribe,//故障描述
    peekEnum_status,//状态
    peekEnum_date,//日期
    peekEnum_inPrice,//进价
    peekEnum_outPrice,//销售价
    peekEnum_estimatePrice,//估计价
    peekEnum_realPrice,//实售价
    peekEnum_seller,//卖家
    peekEnum_buyer,//买家
    peekEnum_handler,//经手人
    peekEnum_employee,//员工
    peekEnum_person_name,//姓名
    peekEnum_person_phone,//电话
    peekEnum_person_id,//工号

    peekEnum_END,
};

typedef struct peekToolPage {
    int page;//第几页
    StringItem* content;//页面内容
    struct peekToolPage* next;//下一页
    struct peekToolPage* prev;//上一页
}peekToolPage;

int* getPeekFullModeParam(int* size);
peekToolPage* peekTooladdPage(peekToolPage* head, StringItem* content);
char* makeCarInfoItemStringTitle(int* param, int size);
char* makeCarInfoItemString(carInfoItem* item, int* param, int size);
peekToolPage* peekTool_genPeekpage(ListNode* nodelink, int* param, int size);
StringItem* getPeekPage(peekToolPage* page, int pageNum);
#endif