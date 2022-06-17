//mdb.h

#ifndef MDB_H
#define MDB_H
#include "utils.h"

//mdb��Ԥ��̶���ֵ
enum MDB_ITEM_TK {
    //��ʼ�ͽ������
    TK_START = 0,
    TK_END,
    //�����
    TK_carId,//�������
    TK_carBrand,//����Ʒ��
    TK_carModel,//�����ͺ�
    TK_carPrice,//����ԭ��
    TK_carAge,//����
    TK_hasRepair,//�Ƿ��д���
    TK_hasFault,//�Ƿ��й���
    TK_faultDescribe,//��������
    TK_status,//״̬
    TK_date,//����
    TK_inPrice,//����
    TK_outPrice,//���ۼ�
    TK_estimatePrice,//���Ƽ�
    TK_realPrice,//ʵ�ۼ�
    TK_person,//��Ա
};
char* get_MDB_HEADER_TK();
ListNode* readAllFromMdb(char* mdbpath);
void saveAsMdb(char* mdbpath, ListNode* nodelink);
carInfoItem* gen_Empty_carInfoItem();
ListNode* readTxtData(char* txtpath);
#define MDB_DEFAULT_PATH "database.mdb"



#endif