//common.h

#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

 //Date
typedef struct Date {
    int year;//��
    int month;//��
    int day;//��
} Date;
//BooleanDef
enum BooleanDef {
    Boolean_TRUE = 1,
    Boolean_FALSE = 0
};
//�ַ���
typedef struct StringItem {
    char* str;//�ַ���
    int size;//�ַ�������
}StringItem;
// //��ֵ��
// typedef struct Pair {
//     void* key;//��
//     void* value;//ֵ
// }Pair;



#endif