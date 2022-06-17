//database.h

#ifndef DATABASE_H
#define DATABASE_H
#include "common.h"

/**
 * @brief ���ݿ�ṹ��
 *
 * [����������Ϣ]->[struct:value]
 *      |�������->carId
 *      |����Ʒ��->carBrand
 *      |�ͺ�->carModel
 *      |ԭ��->carPrice
 *      |����->carAge
 *      [��������]->[struct:carFault]
 *          |�Ƿ��д���->hasRepair
 *          |�Ƿ��й���->hasFault
 *          |��������->faultDescribe
 * [������Ϣ]->[struct:rderInfo]
 *      |״̬{��/����/Ԥ��/����}->status
 *      |����->date
 *      |����->inPrice
 *      |���ۼ�->outPrice
 *      |���Ƽ�->estimatePrice
 *      |ʵ�ۼ�->realPrice
 *      [������Ϣ]->[struct:personInfo]
 *          |����->type=personType_seller
 *          |������ϵ������->name
 *          |�绰->phone
 *      [�����Ϣ]->[struct:personInfo]
 *          |����->type=personType_buyer
 *          |�ͻ�����->name
 *          |�绰->phone
 *      [��������Ϣ]->[struct:personInfo]
 *          |����->type=personType_handler
 *          |������->name
 *          |�绰->phone
 *      [Ա����Ϣ]->[struct:personInfo]
 *          |����->type=personType_employee
 *          |����Ա����->name
 *          |����->id
 */
 //��������
typedef struct carFault {
    enum BooleanDef hasRepair;//�Ƿ��д���
    enum BooleanDef hasFault;//�Ƿ��й���
    StringItem* faultDescribe;//��������
}carFault;
//����������Ϣ
typedef struct carBaseInfo {
    int carId;//�������
    StringItem* carBrand;//����Ʒ��
    StringItem* carModel;//�����ͺ�
    unsigned int carPrice;//����ԭ��
    unsigned int carAge;//����
    carFault* fault;//��������
}carBaseInfo;
//���������Ϣ
enum carStatus {
    carStatus_unknown = 0,//δ֪
    carStatus_inStock,//�ڿ�
    carStatus_outStock,//����
    carStatus_reserved,//Ԥ��
    carStatus_sold//����
};
//��Ա����
enum personType {
    personType_unknown = 0,//δ֪
    personType_seller,//����
    personType_buyer,//���
    personType_handler,//������
    personType_employee//Ա��
};
//��Ա��Ϣ
typedef struct personInfo {
    enum personType type;//��Ա����
    StringItem* name;//����
    StringItem* phone;//�绰
    int id;//����
}personInfo;
//������Ϣ
typedef struct orderInfo {
    enum carStatus status;//����״̬
    Date* date;//����
    unsigned int inPrice;//����
    unsigned int outPrice;//���ۼ�
    unsigned int estimatePrice;//���Ƽ�
    unsigned int realPrice;//ʵ�ۼ�
    personInfo* seller;//������Ϣ
    personInfo* buyer;//�����Ϣ
    personInfo* handler;//��������Ϣ
    personInfo* employee;//Ա����Ϣ
}orderInfo;
//������Ϣ
typedef struct carInfoItem {
    carBaseInfo* info;//����������Ϣ
    orderInfo* order;//������Ϣ
}carInfoItem;
//����˫��
typedef struct ListNode {
    int index;//����
    carInfoItem* value;//������Ϣ
    struct ListNode* next;//��һ���ڵ�
    struct ListNode* prev;//��һ���ڵ�
}ListNode;
//������
enum UDMode {
    UDMode_Up = 0,//����
    UDMode_Down//����
};
#include "utils.h"
#include "mdb.h"

//��ѯ�ӿ�
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

//����ӿ�
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

//��ӽӿ�
ListNode* appendDataByItem(ListNode* nodelink, carInfoItem* item);
ListNode* appendData(ListNode* nodelink, int carId, StringItem* carBrand, StringItem* carModel, int carPrice, int carAge,
int hasRepair, int hasFault, StringItem* faultDescribe,
int status, Date* date,
int inPrice, int outPrice, int estimatePrice, int realPrice,
StringItem* sellername, StringItem* sellerphone,
StringItem* buyername, StringItem* buyerphone,
StringItem* handlername, StringItem* handlerphone,
StringItem* employeename, int employeeid);

//ɾ���ӿ�
ListNode* deleteDataByNode(ListNode* nodelink, ListNode* node);
ListNode* deleteDataByItem(ListNode* nodelink, carInfoItem* item);
ListNode* deleteDataByCarId(ListNode* nodelink, int carId);
ListNode* deleteDataByIndex(ListNode* nodelink, int index);

//�޸Ľӿ�
carInfoItem* modifyDataByItem(carInfoItem* item, StringItem* Key, StringItem* Value);
ListNode* modifyDataByNode(ListNode* nodelink, StringItem* Key, StringItem* Value);
#endif
