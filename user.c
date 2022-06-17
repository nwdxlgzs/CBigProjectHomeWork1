#include "user.h"
//随便找了个RC4的算法用于加密（不是吧，不是吧，这玩意不加密等着泄露？？？）
void RC4(unsigned char* key, int keylen, unsigned char* data, int datalen) {
    if (key == NULL && keylen == 0) {
        //默认秘钥
        char rc4_key[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+/-_=";
        int rc4_key_len = 67;
        int i;
        for (i = 0; i < rc4_key_len; i++) {
            rc4_key[i] = (char)rc4_key[i] ^ 0xCC;//不管怎么，key绝对不能明文存储，所以这里xor一下
        }
        key = rc4_key;
        keylen = rc4_key_len;
    }
    int i, j, k, t;
    unsigned char s[256];
    for (i = 0; i < 256; i++) {
        s[i] = i;
    }
    j = 0;
    for (i = 0; i < 256; i++) {
        j = (j + s[i] + key[i % keylen]) % 256;
        t = s[i];
        s[i] = s[j];
        s[j] = t;
    }
    i = 0;
    j = 0;
    for (k = 0; k < datalen; k++) {
        i = (i + 1) % 256;
        j = (j + s[i]) % 256;
        t = s[i];
        s[i] = s[j];
        s[j] = t;
        data[k] ^= s[(s[i] + s[j]) % 256];
    }
}
/*
读取用户数据
@param 获取账户集大小的int指针
@return 账户集
*/
user_data** readUserData(int* size) {
    const char* user_data_path = "user.data";
    //读取文件
    FILE* fp = fopen(user_data_path, "rb");
    int notfound = 0;
    if (fp == NULL) {
        notfound = 1;
    } else {
        fseek(fp, 0, SEEK_END);
        int ssize = ftell(fp);
        fclose(fp);
        if (ssize <= 32) {
            notfound = 1;
        }
    }
    //首次激活dev账户
    if (notfound) {
        user_data* userData = (user_data*)malloc(sizeof(user_data));
        userData->userType = userType_dev;
        userData->account = devmodeaccount;
        userData->password = devmodepassword;
        *size = 1;
        user_data** ruserData = (user_data**)malloc(sizeof(user_data*) * 1);
        ruserData[0] = userData;
        return ruserData;
    }
    Buffer* encbuffer = readFile(user_data_path, Boolean_TRUE);
    //解密
    RC4(NULL, 0, encbuffer->buffer, encbuffer->size);
    //解析数据
    int firstlensize = 0;
    for (;;) {
        char ch = encbuffer->buffer[firstlensize];
        if (ch == '\n' || ch == '\0') {
            break;
        }
        firstlensize++;
    }
    char SIZECHAR[100] = { 0 };
    memcpy(SIZECHAR, encbuffer->buffer, firstlensize);
    int UDsize = 0;
    sscanf(SIZECHAR, "%d", &UDsize);
    *size = UDsize;
    user_data** userData = (user_data**)malloc(sizeof(user_data*) * UDsize);
    char* buffer = encbuffer->buffer + firstlensize + 1;
    int offset = 0;
    for (int i = 0; i < UDsize; i++) {
        int loffset = 0;
        user_data* userDatai = (user_data*)malloc(sizeof(user_data));
        char* account = (char*)malloc(sizeof(char) * 1024);
        memset(account, 0, 1024);
        char* password = (char*)malloc(sizeof(char) * 1024);
        memset(account, 0, 1024);
        userDatai->account = account;
        userDatai->password = password;
        userData[i] = userDatai;
        for (;;) {
            char ch = buffer[offset + loffset];
            if (ch == '\n' || ch == '\0') {
                break;
            }
            loffset++;
        }
        char userType[1024] = { 0 };
        memcpy(userType, buffer + offset, loffset);
        sscanf(userType, "%d %s %s", &userDatai->userType, userDatai->account, userDatai->password);
        offset += loffset + 1;
    }
    return userData;
}
/*
保存用户数据
@param 账户集，账户集大小
*/
void saveUserData(user_data** userData, int size) {
    const char* user_data_path = "user.data";
    Buffer* buffer = (Buffer*)malloc(sizeof(Buffer));
    char UDCHAR[409600] = { 0 };//直接分配409600，反正账户不会很多
    buffer->buffer = UDCHAR;
    buffer->size = 409600;
    sprintf(UDCHAR, " %d\n", size);
    for (int i = 0; i < size; i++) {
        char userType[1024] = { 0 };
        sprintf(userType, " %d %s %s\n", userData[i]->userType, userData[i]->account, userData[i]->password);
        sprintf(UDCHAR, "%s%s", UDCHAR, userType);
    }
    buffer->size = strlen(UDCHAR);
    //加密
    RC4(NULL, 0, buffer->buffer, buffer->size);
    //写入文件
    writeFile(user_data_path, buffer);
}
/*
添加用户
需要使用当前账户来开设新账户，有权限管辖
@param userData nowsize controler userType account password
*/
void addUserData(user_data** userData, int nowsize, user_data* controler,
enum userType userType, StringItem* account, StringItem* password) {
    if (controler == NULL) {
        mkerrlog("当前正在尝试在没有账户的情况下添加账户！这是不被允许的，请使用dev开设初始账户！");
        return;
    }
    user_data** new_userData = (user_data**)malloc(sizeof(user_data*) * (nowsize + 1));
    int i;
    for (i = 0; i < nowsize; i++) {
        new_userData[i] = userData[i];
    }
    user_data* new_userDatai = (user_data*)malloc(sizeof(user_data));
    switch (controler->userType) {
        case userType_dev://dev最高权限，可以设置任意等级账户
            new_userDatai->userType = userType;
            new_userDatai->account = account->str;
            new_userDatai->password = password->str;
            new_userData[i] = new_userDatai;
            saveUserData(new_userData, nowsize + 1);
            break;
        case userType_admin://admin不可以设置dev或者admin等级账户
            if (userType > userType_admin) {//可以设置的低等级账户
                new_userDatai->userType = userType;
                new_userDatai->account = account->str;
                new_userDatai->password = password->str;
                new_userData[i] = new_userDatai;
                saveUserData(new_userData, nowsize + 1);
            } else {
                mkerrlog("admin：权限不够，不能设置同级或者更高级账户！");
            }
            break;
        case userType_manager://manager不可以设置dev或者admin或manager等级账户
            if (userType > userType_manager) {//可以设置的低等级账户
                new_userDatai->userType = userType;
                new_userDatai->account = account->str;
                new_userDatai->password = password->str;
                new_userData[i] = new_userDatai;
                saveUserData(new_userData, nowsize + 1);
            } else {
                mkerrlog("manager：权限不够，不能设置同级或者更高级账户！");
            }
            break;
        case userType_employee://employee不可以设置dev或者admin或manager或employee等级账户
            if (userType > userType_employee) {//可以设置的低等级账户
                new_userDatai->userType = userType;
                new_userDatai->account = account->str;
                new_userDatai->password = password->str;
                new_userData[i] = new_userDatai;
                saveUserData(new_userData, nowsize + 1);
            } else {
                mkerrlog("employee：权限不够，不能设置同级或者更高级账户！");
            }
            break;
        case userType_cust:
            mkerrlog("cust：没有权限创建账户，请找员工及以上等级的人开通！");
            break;
        default:
            mkerrlog("未知用户类型！");
            break;
    }
}
/*
登录
@param 账户集指针，账户集大小指针，账户，密码
@return 登录成功返回用户
*/
user_data* login(user_data*** userData, int* nowsize, StringItem* account, StringItem* password) {
    *userData = readUserData(nowsize);
    for (int i = 0; i < *nowsize; i++) {
        if (strcmp((*userData)[i]->account, account->str) == 0 && strcmp((*userData)[i]->password, password->str) == 0) {
            return (*userData)[i];
        }
    }
    return NULL;
}
/*
登出
@param 账户指针
@return -1：登出失败，0：登出成功
*/
int logout(user_data* controler) {
    free(controler->account);
    free(controler->password);
    controler->userType = -1;
    free(controler);
    return 0;
}
/*
删户
@param 账户集，账户集大小，账户，待删除账户
@return -1：登出失败，0：登出成功
*/
int removeUserData(user_data** userData, int nowsize, user_data* controler, StringItem* account) {
    if (controler == NULL) {
        mkerrlog("当前正在尝试在没有账户的情况下删除账户！这是不被允许的，请使用dev删除任意非dev账户！");
        return -1;
    }
    int i;
    user_data* target = NULL;
    for (i = 0; i < nowsize; i++) {
        if (strcmp(userData[i]->account, account->str) == 0) {
            target = userData[i];
            break;
        }
    }
    if (target == NULL) {
        mkerrlog("没有找到待删除的账户！");
        return -1;
    }
    if (target->userType == userType_dev) {
        mkerrlog("dev账户不能删除！");
        return -1;
    }
    int index = i;
    int ok = 0;
    switch (controler->userType) {
        case userType_dev://dev最高权限，可以删除任意等级账户
            if (target->userType > userType_dev) {//可以删除的低等级账户
                ok = 1;
            }
            break;
        case userType_admin://admin可以删除非dev和admin等级账户
            if (target->userType > userType_admin) {//可以删除的低等级账户
                ok = 1;
            }
            break;
        case userType_manager://manager可以删除非dev、admin和manager等级账户
            if (target->userType > userType_manager) {//可以删除的低等级账户
                ok = 1;
            }
            break;
        case userType_employee://employee可以删除非dev、admin、manager和employee等级账户
            if (target->userType > userType_employee) {//可以删除的低等级账户
                ok = 1;
            }
            break;
        case userType_cust:
            mkerrlog("cust：没有权限删除账户！");
            break;
        default:
            mkerrlog("未知用户类型！");
            break;
    }
    if (ok == 1) {
        free(target->account);
        free(target->password);
        free(target);
        userData[index] = NULL;
        for (i = index; i < nowsize - 1; i++) {
            userData[i] = userData[i + 1];
        }
        saveUserData(userData, nowsize - 1);
        return 0;
    }
    return -1;
}
