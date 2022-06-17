//user.h

#ifndef USER_H
#define USER_H
#include "common.h"
#include "utils.h"
//������ģʽ�˻�������
#define devmodeaccount "nwdxlgzs@github.com"
#define devmodepassword "nwdxlgzs@github.com"

enum userType {
    userType_dev = 0,//������
    userType_admin,//����Ա
    userType_manager,//����
    userType_employee,//Ա��
    userType_cust,//�ͻ�
};
/**
 * @brief �洢�û������ݽṹ��δ����ʱ������֧�ֿո�ɶ�ģ�����һ���˻����ո񼸸���˼������
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