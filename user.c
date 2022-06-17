#include "user.h"
//������˸�RC4���㷨���ڼ��ܣ����ǰɣ����ǰɣ������ⲻ���ܵ���й¶��������
void RC4(unsigned char* key, int keylen, unsigned char* data, int datalen) {
    if (key == NULL && keylen == 0) {
        //Ĭ����Կ
        char rc4_key[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+/-_=";
        int rc4_key_len = 67;
        int i;
        for (i = 0; i < rc4_key_len; i++) {
            rc4_key[i] = (char)rc4_key[i] ^ 0xCC;//������ô��key���Բ������Ĵ洢����������xorһ��
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
��ȡ�û�����
@param ��ȡ�˻�����С��intָ��
@return �˻���
*/
user_data** readUserData(int* size) {
    const char* user_data_path = "user.data";
    //��ȡ�ļ�
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
    //�״μ���dev�˻�
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
    //����
    RC4(NULL, 0, encbuffer->buffer, encbuffer->size);
    //��������
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
�����û�����
@param �˻������˻�����С
*/
void saveUserData(user_data** userData, int size) {
    const char* user_data_path = "user.data";
    Buffer* buffer = (Buffer*)malloc(sizeof(Buffer));
    char UDCHAR[409600] = { 0 };//ֱ�ӷ���409600�������˻�����ܶ�
    buffer->buffer = UDCHAR;
    buffer->size = 409600;
    sprintf(UDCHAR, " %d\n", size);
    for (int i = 0; i < size; i++) {
        char userType[1024] = { 0 };
        sprintf(userType, " %d %s %s\n", userData[i]->userType, userData[i]->account, userData[i]->password);
        sprintf(UDCHAR, "%s%s", UDCHAR, userType);
    }
    buffer->size = strlen(UDCHAR);
    //����
    RC4(NULL, 0, buffer->buffer, buffer->size);
    //д���ļ�
    writeFile(user_data_path, buffer);
}
/*
����û�
��Ҫʹ�õ�ǰ�˻����������˻�����Ȩ�޹�Ͻ
@param userData nowsize controler userType account password
*/
void addUserData(user_data** userData, int nowsize, user_data* controler,
enum userType userType, StringItem* account, StringItem* password) {
    if (controler == NULL) {
        mkerrlog("��ǰ���ڳ�����û���˻������������˻������ǲ�������ģ���ʹ��dev�����ʼ�˻���");
        return;
    }
    user_data** new_userData = (user_data**)malloc(sizeof(user_data*) * (nowsize + 1));
    int i;
    for (i = 0; i < nowsize; i++) {
        new_userData[i] = userData[i];
    }
    user_data* new_userDatai = (user_data*)malloc(sizeof(user_data));
    switch (controler->userType) {
        case userType_dev://dev���Ȩ�ޣ�������������ȼ��˻�
            new_userDatai->userType = userType;
            new_userDatai->account = account->str;
            new_userDatai->password = password->str;
            new_userData[i] = new_userDatai;
            saveUserData(new_userData, nowsize + 1);
            break;
        case userType_admin://admin����������dev����admin�ȼ��˻�
            if (userType > userType_admin) {//�������õĵ͵ȼ��˻�
                new_userDatai->userType = userType;
                new_userDatai->account = account->str;
                new_userDatai->password = password->str;
                new_userData[i] = new_userDatai;
                saveUserData(new_userData, nowsize + 1);
            } else {
                mkerrlog("admin��Ȩ�޲�������������ͬ�����߸��߼��˻���");
            }
            break;
        case userType_manager://manager����������dev����admin��manager�ȼ��˻�
            if (userType > userType_manager) {//�������õĵ͵ȼ��˻�
                new_userDatai->userType = userType;
                new_userDatai->account = account->str;
                new_userDatai->password = password->str;
                new_userData[i] = new_userDatai;
                saveUserData(new_userData, nowsize + 1);
            } else {
                mkerrlog("manager��Ȩ�޲�������������ͬ�����߸��߼��˻���");
            }
            break;
        case userType_employee://employee����������dev����admin��manager��employee�ȼ��˻�
            if (userType > userType_employee) {//�������õĵ͵ȼ��˻�
                new_userDatai->userType = userType;
                new_userDatai->account = account->str;
                new_userDatai->password = password->str;
                new_userData[i] = new_userDatai;
                saveUserData(new_userData, nowsize + 1);
            } else {
                mkerrlog("employee��Ȩ�޲�������������ͬ�����߸��߼��˻���");
            }
            break;
        case userType_cust:
            mkerrlog("cust��û��Ȩ�޴����˻�������Ա�������ϵȼ����˿�ͨ��");
            break;
        default:
            mkerrlog("δ֪�û����ͣ�");
            break;
    }
}
/*
��¼
@param �˻���ָ�룬�˻�����Сָ�룬�˻�������
@return ��¼�ɹ������û�
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
�ǳ�
@param �˻�ָ��
@return -1���ǳ�ʧ�ܣ�0���ǳ��ɹ�
*/
int logout(user_data* controler) {
    free(controler->account);
    free(controler->password);
    controler->userType = -1;
    free(controler);
    return 0;
}
/*
ɾ��
@param �˻������˻�����С���˻�����ɾ���˻�
@return -1���ǳ�ʧ�ܣ�0���ǳ��ɹ�
*/
int removeUserData(user_data** userData, int nowsize, user_data* controler, StringItem* account) {
    if (controler == NULL) {
        mkerrlog("��ǰ���ڳ�����û���˻��������ɾ���˻������ǲ�������ģ���ʹ��devɾ�������dev�˻���");
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
        mkerrlog("û���ҵ���ɾ�����˻���");
        return -1;
    }
    if (target->userType == userType_dev) {
        mkerrlog("dev�˻�����ɾ����");
        return -1;
    }
    int index = i;
    int ok = 0;
    switch (controler->userType) {
        case userType_dev://dev���Ȩ�ޣ�����ɾ������ȼ��˻�
            if (target->userType > userType_dev) {//����ɾ���ĵ͵ȼ��˻�
                ok = 1;
            }
            break;
        case userType_admin://admin����ɾ����dev��admin�ȼ��˻�
            if (target->userType > userType_admin) {//����ɾ���ĵ͵ȼ��˻�
                ok = 1;
            }
            break;
        case userType_manager://manager����ɾ����dev��admin��manager�ȼ��˻�
            if (target->userType > userType_manager) {//����ɾ���ĵ͵ȼ��˻�
                ok = 1;
            }
            break;
        case userType_employee://employee����ɾ����dev��admin��manager��employee�ȼ��˻�
            if (target->userType > userType_employee) {//����ɾ���ĵ͵ȼ��˻�
                ok = 1;
            }
            break;
        case userType_cust:
            mkerrlog("cust��û��Ȩ��ɾ���˻���");
            break;
        default:
            mkerrlog("δ֪�û����ͣ�");
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
