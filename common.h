//common.h

#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>

 //Date
typedef struct Date {
    int year;//年
    int month;//月
    int day;//日
} Date;
//BooleanDef
enum BooleanDef {
    Boolean_TRUE = 1,
    Boolean_FALSE = 0
};
//字符串
typedef struct StringItem {
    char* str;//字符串
    int size;//字符串长度
}StringItem;
// //键值对
// typedef struct Pair {
//     void* key;//键
//     void* value;//值
// }Pair;



#endif
