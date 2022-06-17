//database.h

#ifndef DATABASE_H
#define DATABASE_H
#include "common.h"

/**
 * @brief 数据库结构体
 *
 * [车辆基本信息]->[struct:value]
 *      |车辆编号->carId
 *      |车辆品牌->carBrand
 *      |型号->carModel
 *      |原价->carPrice
 *      |车龄->carAge
 *      [车辆故障]->[struct:carFault]
 *          |是否有大修->hasRepair
 *          |是否有故障->hasFault
 *          |故障描述->faultDescribe
 * [订单信息]->[struct:rderInfo]
 *      |状态{入/出库/预定/已售}->status
 *      |日期->date
 *      |进价->inPrice
 *      |销售价->outPrice
 *      |估计价->estimatePrice
 *      |实售价->realPrice
 *      [卖家信息]->[struct:personInfo]
 *          |类型->type=personType_seller
 *          |卖家联系人姓名->name
 *          |电话->phone
 *      [买家信息]->[struct:personInfo]
 *          |类型->type=personType_buyer
 *          |客户名称->name
 *          |电话->phone
 *      [经手人信息]->[struct:personInfo]
 *          |类型->type=personType_handler
 *          |经手人->name
 *          |电话->phone
 *      [员工信息]->[struct:personInfo]
 *          |类型->type=personType_employee
 *          |销售员姓名->name
 *          |工号->id
 */
 //车辆故障
typedef struct carFault {
    enum BooleanDef hasRepair;//是否有大修
    enum BooleanDef hasFault;//是否有故障
    StringItem* faultDescribe;//故障描述
}carFault;
//车辆基本信息
typedef struct carBaseInfo {
    int carId;//车辆编号
    StringItem* carBrand;//车辆品牌
    StringItem* carModel;//车辆型号
    unsigned int carPrice;//车辆原价
    unsigned int carAge;//车龄
    carFault* fault;//车辆故障
}carBaseInfo;
//车辆入库信息
enum carStatus {
    carStatus_unknown = 0,//未知
    carStatus_inStock,//在库
    carStatus_outStock,//出库
    carStatus_reserved,//预定
    carStatus_sold//已售
};
//人员类型
enum personType {
    personType_unknown = 0,//未知
    personType_seller,//卖家
    personType_buyer,//买家
    personType_handler,//经手人
    personType_employee//员工
};
//人员信息
typedef struct personInfo {
    enum personType type;//人员类型
    StringItem* name;//姓名
    StringItem* phone;//电话
    int id;//工号
}personInfo;
//订单信息
typedef struct orderInfo {
    enum carStatus status;//车辆状态
    Date* date;//日期
    unsigned int inPrice;//进价
    unsigned int outPrice;//销售价
    unsigned int estimatePrice;//估计价
    unsigned int realPrice;//实售价
    personInfo* seller;//卖家信息
    personInfo* buyer;//买家信息
    personInfo* handler;//经手人信息
    personInfo* employee;//员工信息
}orderInfo;
//车辆信息
typedef struct carInfoItem {
    carBaseInfo* info;//车辆基本信息
    orderInfo* order;//订单信息
}carInfoItem;
//链表（双向）
typedef struct ListNode {
    int index;//索引
    carInfoItem* value;//车辆信息
    struct ListNode* next;//下一个节点
    struct ListNode* prev;//上一个节点
}ListNode;
//升降序
enum UDMode {
    UDMode_Up = 0,//升序
    UDMode_Down//降序
};
#include "utils.h"
#include "mdb.h"

//查询接口
carInfoItem** QueryByEmployeeId(ListNode* nodelink, int id, int* len);
carInfoItem** QueryByHandlerName(ListNode* nodelink, StringItem* name, int* len);
carInfoItem** QueryByHandlerPhone(ListNode* nodelink, StringItem* phone, int* len);
carInfoItem** QueryByHandlerName(ListNode* nodelink, StringItem* name, int* len);
carInfoItem** QueryByBuyerPhone(ListNode* nodelink, StringItem* phone, int* len);
carInfoItem** QueryByBuyerName(ListNode* nodelink, StringItem* name, int* len);
carInfoItem** QueryBySellerPhone(ListNode* nodelink, StringItem* phone, int* len);
carInfoItem** QueryBySellerName(ListNode* nodelink, StringItem* name, int* len);
carInfoItem** QueryByOnSale(ListNode* nodelink, enum BooleanDef unselect, int* len);
carInfoItem** QueryByRealPrice(ListNode* nodelink, int min, int max, int* len);
carInfoItem** QueryByEstimatePrice(ListNode* nodelink, int min, int max, int* len);
carInfoItem** QueryByOutPrice(ListNode* nodelink, int min, int max, int* len);
carInfoItem** QueryByInPrice(ListNode* nodelink, int min, int max, int* len);
carInfoItem** QueryByDate(ListNode* nodelink, Date* min, Date* max, int* len);
carInfoItem** QueryByCarStatus(ListNode* nodelink, enum carStatus status, int* len);
carInfoItem** QueryByCarHasFault(ListNode* nodelink, enum BooleanDef unselect, int* len);
carInfoItem** QueryByCarHasRepair(ListNode* nodelink, enum BooleanDef unselect, int* len);
carInfoItem** QueryByCarAge(ListNode* nodelink, int min, int max, int* len);
carInfoItem** QueryByCarPrice(ListNode* nodelink, int min, int max, int* len);
carInfoItem** QueryByCarModel(ListNode* nodelink, StringItem* carModel, int* len);
carInfoItem** QueryByCarBrand(ListNode* nodelink, StringItem* carBrand, int* len);
carInfoItem* QueryByCarId(ListNode* nodelink, int carId);

//排序接口
ListNode* SortByCarId(ListNode* nodelink, enum UDMode udmode);
ListNode* SortByCarBrand(ListNode* nodelink, enum UDMode udmode);
ListNode* SortByCarModel(ListNode* nodelink, enum UDMode udmode);
ListNode* SortByCarPrice(ListNode* nodelink, enum UDMode udmode);
ListNode* SortByCarAge(ListNode* nodelink, enum UDMode udmode);
ListNode* SortByCarHasRepair(ListNode* nodelink, enum UDMode udmode);
ListNode* SortByCarHasFault(ListNode* nodelink, enum UDMode udmode);
ListNode* SortByCarStatus(ListNode* nodelink, enum UDMode udmode);
ListNode* SortByDate(ListNode* nodelink, enum UDMode udmode);
ListNode* SortByInPrice(ListNode* nodelink, enum UDMode udmode);
ListNode* SortByOutPrice(ListNode* nodelink, enum UDMode udmode);
ListNode* SortByEstimatePrice(ListNode* nodelink, enum UDMode udmode);
ListNode* SortByRealPrice(ListNode* nodelink, enum UDMode udmode);
ListNode* SortBySellerName(ListNode* nodelink, enum UDMode udmode);
ListNode* SortBySellerPhone(ListNode* nodelink, enum UDMode udmode);
ListNode* SortByBuyerName(ListNode* nodelink, enum UDMode udmode);
ListNode* SortByBuyerPhone(ListNode* nodelink, enum UDMode udmode);
ListNode* SortByHandlerName(ListNode* nodelink, enum UDMode udmode);
ListNode* SortByHandlerPhone(ListNode* nodelink, enum UDMode udmode);
ListNode* SortByEmployeeName(ListNode* nodelink, enum UDMode udmode);
ListNode* SortByEmployeeId(ListNode* nodelink, enum UDMode udmode);

//添加接口
ListNode* appendDataByItem(ListNode* nodelink, carInfoItem* item);
ListNode* appendData(ListNode* nodelink, int carId, StringItem* carBrand, StringItem* carModel, int carPrice, int carAge,
int hasRepair, int hasFault, StringItem* faultDescribe,
int status, Date* date,
int inPrice, int outPrice, int estimatePrice, int realPrice,
StringItem* sellername, StringItem* sellerphone,
StringItem* buyername, StringItem* buyerphone,
StringItem* handlername, StringItem* handlerphone,
StringItem* employeename, int employeeid);

//删除接口
ListNode* deleteDataByNode(ListNode* nodelink, ListNode* node);
ListNode* deleteDataByItem(ListNode* nodelink, carInfoItem* item);
ListNode* deleteDataByCarId(ListNode* nodelink, int carId);
ListNode* deleteDataByIndex(ListNode* nodelink, int index);

//修改接口
carInfoItem* modifyDataByItem(carInfoItem* item, StringItem* Key, StringItem* Value);
ListNode* modifyDataByNode(ListNode* nodelink, StringItem* Key, StringItem* Value);
#endif
