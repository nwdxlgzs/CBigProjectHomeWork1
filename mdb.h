//mdb.h

#ifndef MDB_H
#define MDB_H
#include "utils.h"

//mdb的预设固定键值
enum MDB_ITEM_TK {
    //开始和结束标记
    TK_START = 0,
    TK_END,
    //常规键
    TK_carId,//车辆编号
    TK_carBrand,//车辆品牌
    TK_carModel,//车辆型号
    TK_carPrice,//车辆原价
    TK_carAge,//车龄
    TK_hasRepair,//是否有大修
    TK_hasFault,//是否有故障
    TK_faultDescribe,//故障描述
    TK_status,//状态
    TK_date,//日期
    TK_inPrice,//进价
    TK_outPrice,//销售价
    TK_estimatePrice,//估计价
    TK_realPrice,//实售价
    TK_person,//人员
};
char* get_MDB_HEADER_TK();
ListNode* readAllFromMdb(char* mdbpath);
void saveAsMdb(char* mdbpath, ListNode* nodelink);
carInfoItem* gen_Empty_carInfoItem();
ListNode* readTxtData(char* txtpath);
#define MDB_DEFAULT_PATH "database.mdb"



#endif