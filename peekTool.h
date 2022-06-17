//peekTool.h

#ifndef PEEKTOOL_H
#define PEEKTOOL_H
#include "common.h"
#include "utils.h"
enum peekEnum {
    peekEnum_START = 0,

    peekEnum_carId,//�������
    peekEnum_carBrand,//����Ʒ��
    peekEnum_carModel,//�����ͺ�
    peekEnum_carPrice,//����ԭ��
    peekEnum_carAge,//����
    peekEnum_hasRepair,//�Ƿ��д���
    peekEnum_hasFault,//�Ƿ��й���
    peekEnum_faultDescribe,//��������
    peekEnum_status,//״̬
    peekEnum_date,//����
    peekEnum_inPrice,//����
    peekEnum_outPrice,//���ۼ�
    peekEnum_estimatePrice,//���Ƽ�
    peekEnum_realPrice,//ʵ�ۼ�
    peekEnum_seller,//����
    peekEnum_buyer,//���
    peekEnum_handler,//������
    peekEnum_employee,//Ա��
    peekEnum_person_name,//����
    peekEnum_person_phone,//�绰
    peekEnum_person_id,//����

    peekEnum_END,
};

typedef struct peekToolPage {
    int page;//�ڼ�ҳ
    StringItem* content;//ҳ������
    struct peekToolPage* next;//��һҳ
    struct peekToolPage* prev;//��һҳ
}peekToolPage;

int* getPeekFullModeParam(int* size);
peekToolPage* peekTooladdPage(peekToolPage* head, StringItem* content);
char* makeCarInfoItemStringTitle(int* param, int size);
char* makeCarInfoItemString(carInfoItem* item, int* param, int size);
peekToolPage* peekTool_genPeekpage(ListNode* nodelink, int* param, int size);
StringItem* getPeekPage(peekToolPage* page, int pageNum);
#endif