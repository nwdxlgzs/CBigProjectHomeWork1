//user.h

#ifndef USER_H
#define USER_H
#include "common.h"
#include "utils.h"
//开发者模式账户和密码
#define devmodeaccount "nwdxlgzs@github.com"
#define devmodepassword "nwdxlgzs@github.com"

enum userType {
    userType_dev = 0,//开发者
    userType_admin,//管理员
    userType_manager,//经理
    userType_employee,//员工
    userType_cust,//客户
};
/**
 * @brief 存储用户的数据结构（未加密时），不支持空格啥的！！！一个账户带空格几个意思？？？
 * size
 * userType account password
 * userType account password
 * ......
 */
typedef struct user_data {
    int userType;
    char* account;
    char* password;
}user_data;

void saveUserData(user_data** userData, int size);
user_data** readUserData(int* size);
void addUserData(user_data** userData, int nowsize, user_data* controler, enum userType userType, StringItem* account, StringItem* password);
user_data* login(user_data*** userData, int *nowsize, StringItem* account, StringItem* password);
int logout(user_data* controler);
int removeUserData(user_data** userData, int nowsize, user_data* controler, StringItem* account);
#endif