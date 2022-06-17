#include "UIAction.h"
/*
�������UI�Ĵ�ӡ�����Ӧ
ûɶע�ͣ�����������˵�ĺ�����ˣ���дע��̫������
*/
static user_data* CurUserData = NULL;
static user_data** CurUserDatas = NULL;
static int CurUserDatasSize = 0;
static ListNode* nodelink = NULL;
static StringItem* nodelinkpath = NULL;
void Action_Welcome_case_errinput() {
    MessageBox(NULL, "ѡ��Ƿ������������룡", "����", MB_OK);
}
HANDLE HANDLE_Action_Welcome_case_errinput;
void Action_Welcome() {
    int choice = 0;
    scanf("%d", &choice);
    char tmp;
    while ((tmp = getchar()) != '\n');//��ջ�����
    switch (choice) {
        case 1://1.��¼�˺�
            UI_login();
            break;
        case 2://2.ע���˺�
            UI_register();
            break;
        case 3://3.�رճ���
            exit(0);
            break;
        default:
            HANDLE_Action_Welcome_case_errinput = (HANDLE)_beginthread(Action_Welcome_case_errinput, 0, NULL);
            UI_Welcome();
            WaitForSingleObject(HANDLE_Action_Welcome_case_errinput, INFINITE);
            break;
    }
}
void Action_login() {
    char account[1024] = { 0 };
    char ch = 0;
    int i = 0;
    for (;;) {
        ch = getchar();
        if (ch == '\n') {
            break;
        }
        account[i++] = ch;
    }
    StringItem* accitem = trim(account, i);
    if (accitem == NULL) {
        UI_Welcome();
        return;
    }
    UI_login_ask_password(accitem);
}
void Action_login_case_NULL_UD() {
    MessageBox(NULL, "������˺Ŵ��󣬲��޴��ˣ�", "����", MB_OK);
}
HANDLE HANDLE_Action_login_case_NULL_UD;
void Action_login_ask_password(StringItem* accitem) {
    char password[1024] = { 0 };
    char ch = 0;
    int i = 0;
    for (;;) {
        ch = getchar();
        if (ch == '\n') {
            break;
        }
        password[i++] = ch;
    }
    StringItem* passitem = trim(password, i);
    if (passitem == NULL) {
        UI_Welcome();
        return;
    }
    user_data*** userData = (user_data***)malloc(sizeof(user_data**));
    int size = 0;
    user_data* data = login(userData, &size, accitem, passitem);
    CurUserDatas = *userData;
    CurUserDatasSize = size;
    if (data == NULL) {
        HANDLE_Action_login_case_NULL_UD = (HANDLE)_beginthread(Action_login_case_NULL_UD, 0, NULL);
        UI_login();
        WaitForSingleObject(HANDLE_Action_login_case_NULL_UD, INFINITE);
        return;
    } else {
        CurUserData = data;
    }
    // if (CurUserData->userType > userType_employee) {//cust����û���ڸС���
    //     UI_Welcome();
    // } else {
    //     UI_MainMenu();
    // }
    UI_MainMenu();
}
void Action_register_case_NULL_CurUserData() {
    MessageBox(NULL, "���ȵ�¼�˺ţ���ʼע��ʹ��ʱʹ��dev�ȿ���adminȨ�޵��˺ź�ʹ�ã���", "����", MB_OK);
}
HANDLE HANDLE_Action_register_case_NULL_CurUserData;
void Action_register() {
    if (CurUserData == NULL) {
        HANDLE_Action_register_case_NULL_CurUserData = (HANDLE)_beginthread(Action_register_case_NULL_CurUserData, 0, NULL);
        UI_Welcome();
        WaitForSingleObject(HANDLE_Action_register_case_NULL_CurUserData, INFINITE);
        return;
    }
    char account[1024] = { 0 };
    char ch = 0;
    int i = 0;
    for (;;) {
        ch = getchar();
        if (ch == '\n') {
            break;
        }
        account[i++] = ch;
    }
    StringItem* accitem = trim(account, i);
    if (accitem == NULL) {
        UI_Welcome();
        return;
    }
    UI_register_ask_password(accitem);
}
void Action_register_ask_password(StringItem* accitem) {
    char password[1024] = { 0 };
    char ch = 0;
    int i = 0;
    for (;;) {
        ch = getchar();
        if (ch == '\n') {
            break;
        }
        password[i++] = ch;
    }
    StringItem* passitem = trim(password, i);
    if (passitem == NULL) {
        UI_Welcome();
        return;
    }
    UI_register_ask_type(accitem, passitem);
}
void Action_register_case_errtype() {
    MessageBox(NULL, "�����˴�������ͣ�", "����", MB_OK);
}
HANDLE HANDLE_Action_register_case_errtype;

void Action_register_ask_type(StringItem* accitem, StringItem* passitem) {
    char typestr[1024] = { 0 };
    char ch = 0;
    int i = 0;
    for (;;) {
        ch = getchar();
        if (ch == '\n') {
            break;
        }
        typestr[i++] = ch;
    }
    StringItem* typestritem = trim(typestr, i);
    if (typestritem == NULL) {
        UI_Welcome();
        return;
    }
    int type = userType_cust;
    if (strcmp(typestritem->str, "admin") == 0 || strcmp(typestritem->str, "1") == 0 || strcmp(typestritem->str, "����Ա") == 0) {
        type = userType_admin;
    } else if (strcmp(typestritem->str, "manager") == 0 || strcmp(typestritem->str, "2") == 0 || strcmp(typestritem->str, "����") == 0) {
        type = userType_manager;
    } else if (strcmp(typestritem->str, "employee") == 0 || strcmp(typestritem->str, "3") == 0 || strcmp(typestritem->str, "Ա��") == 0) {
        type = userType_employee;
    } else if (strcmp(typestritem->str, "cust") == 0 || strcmp(typestritem->str, "4") == 0 || strcmp(typestritem->str, "�ͻ�") == 0 || strcmp(typestritem->str, "customer") == 0 || strcmp(typestritem->str, "�û�") == 0) {
        type = userType_cust;
    } else {
        HANDLE_Action_register_case_errtype = (HANDLE)_beginthread(Action_register_case_errtype, 0, NULL);
        UI_register();
        WaitForSingleObject(HANDLE_Action_register_case_errtype, INFINITE);
        return;
    }
    addUserData(CurUserDatas, CurUserDatasSize, CurUserData, type, accitem, passitem);
    // if (CurUserData->userType > userType_employee) {//cust����û���ڸС���
    //     UI_Welcome();
    // } else {
    //     UI_MainMenu();
    // }
    UI_MainMenu();
}
void Action_MainMenu_case_noper() {
    MessageBox(NULL, "Ȩ�޲�����", "����", MB_OK);
}
HANDLE HANDLE_Action_MainMenu_case_noper;
void Action_MainMenu() {
    if (CurUserData == NULL) {
        UI_Welcome();
        return;
        // CurUserDatas = readUserData(&CurUserDatasSize);
        // CurUserData = CurUserDatas[0];
        // char* dir = "test.mdb";
        // StringItem* file = trim(dir, strlen(dir));
        // nodelinkpath = file;
        // nodelink = readAllFromMdb(dir);
    }
    int choice = 0;
    scanf("%d", &choice);
    char tmp;
    while ((tmp = getchar()) != '\n');//��ջ�����
    switch (choice) {
        case 1:
            {
                //1.�ǳ��˺�
                logout(CurUserData);
                CurUserData = NULL;
                CurUserDatas = NULL;
                CurUserDatasSize = 0;
                UI_Welcome();
                break;
            }
        case 2:
            {
                //2.ע���˺�
                UI_register();
                break;
            }
        case 3:
            {
                //3.�鿴�˺���Ϣ
                UI_peek_userinfo(CurUserData);
                break;
            }
        case 4:
            {
                //4.ɾ���˺�
                if (CurUserData->userType > userType_manager) {//employee��Ȩ
                    HANDLE_Action_MainMenu_case_noper = (HANDLE)_beginthread(Action_MainMenu_case_noper, 0, NULL);
                    UI_MainMenu();
                    WaitForSingleObject(HANDLE_Action_MainMenu_case_noper, INFINITE);
                    return;
                }
                UI_delete_user(CurUserData, CurUserDatas, &CurUserDatasSize);
                break;
            }
        case 5:
            {
                //5.��mdb���ݿ�
                if (CurUserData->userType > userType_employee) {//cust��Ȩ
                    HANDLE_Action_MainMenu_case_noper = (HANDLE)_beginthread(Action_MainMenu_case_noper, 0, NULL);
                    UI_MainMenu();
                    WaitForSingleObject(HANDLE_Action_MainMenu_case_noper, INFINITE);
                    return;
                }
                UI_openMDB();
                break;
            }
        case 6:
            {//6.txt���ݵ��루�Զ������ڵ�ǰmdb�б��棩
                if (CurUserData->userType > userType_manager) {//employee��Ȩ
                    HANDLE_Action_MainMenu_case_noper = (HANDLE)_beginthread(Action_MainMenu_case_noper, 0, NULL);
                    UI_MainMenu();
                    WaitForSingleObject(HANDLE_Action_MainMenu_case_noper, INFINITE);
                    return;
                }
                UI_txt_import(nodelink);
                break;
            }
        case 7:
            {
                //7.mdb����
                if (CurUserData->userType > userType_employee) {//cust��Ȩ
                    HANDLE_Action_MainMenu_case_noper = (HANDLE)_beginthread(Action_MainMenu_case_noper, 0, NULL);
                    UI_MainMenu();
                    WaitForSingleObject(HANDLE_Action_MainMenu_case_noper, INFINITE);
                    return;
                }
                UI_export_mdb(nodelink);
                break;
            }
        case 8:
            {//8.���뵥��������
                if (CurUserData->userType > userType_manager) {//employee��Ȩ
                    HANDLE_Action_MainMenu_case_noper = (HANDLE)_beginthread(Action_MainMenu_case_noper, 0, NULL);
                    UI_MainMenu();
                    WaitForSingleObject(HANDLE_Action_MainMenu_case_noper, INFINITE);
                    return;
                }
                UI_append_new_data();
                break;
            }
        case 9:
            {//9.ɾ������
                if (CurUserData->userType > userType_manager) {//employee��Ȩ
                    HANDLE_Action_MainMenu_case_noper = (HANDLE)_beginthread(Action_MainMenu_case_noper, 0, NULL);
                    UI_MainMenu();
                    WaitForSingleObject(HANDLE_Action_MainMenu_case_noper, INFINITE);
                    return;
                }
                UI_remove_data();
                break;
            }
        case 10:
            {//10.�鿴����
                if (CurUserData->userType > userType_employee) {//cust��Ȩ
                    HANDLE_Action_MainMenu_case_noper = (HANDLE)_beginthread(Action_MainMenu_case_noper, 0, NULL);
                    UI_MainMenu();
                    WaitForSingleObject(HANDLE_Action_MainMenu_case_noper, INFINITE);
                    return;
                }
                UI_peek_data();
                break;
            }
        case 11:
            {//11.�޸�����
                if (CurUserData->userType > userType_manager) {//employee��Ȩ
                    HANDLE_Action_MainMenu_case_noper = (HANDLE)_beginthread(Action_MainMenu_case_noper, 0, NULL);
                    UI_MainMenu();
                    WaitForSingleObject(HANDLE_Action_MainMenu_case_noper, INFINITE);
                    return;
                }
                UI_modify_data(nodelink);
                break;
            }
        case 12:
            {//12.����ͳ��
                if (CurUserData->userType > userType_employee) {//cust��Ȩ
                    HANDLE_Action_MainMenu_case_noper = (HANDLE)_beginthread(Action_MainMenu_case_noper, 0, NULL);
                    UI_MainMenu();
                    WaitForSingleObject(HANDLE_Action_MainMenu_case_noper, INFINITE);
                    return;
                }
                UI_analysis_data(nodelink);
                break;
            }
        case 13:
            {//13.�رճ���
                exit(0);
                break;
            }
        default:
            HANDLE_Action_Welcome_case_errinput = (HANDLE)_beginthread(Action_Welcome_case_errinput, 0, NULL);
            UI_MainMenu();
            WaitForSingleObject(HANDLE_Action_Welcome_case_errinput, INFINITE);
            return;
    }
}
void Action_peek_userinfo() {
    char ch;
    while ((ch = getchar()) != '\n');//��ջ�����
    UI_MainMenu();
}
void Action_delete_user_case_rmself() {
    MessageBox(NULL, "������ɾ���Լ����߳�ʼdev�˺ţ�", "����", MB_OK);
}
HANDLE HANDLE_Action_delete_user_case_rmself;
void Action_delete_user_case_rmerr() {
    MessageBox(NULL, "�����������������־��", "����", MB_OK);
}
HANDLE HANDLE_Action_delete_user_case_rmerr;
void Action_delete_user(user_data* lCurUserData, user_data** lCurUserDatas, int* lCurUserDatasSize) {
    char acc[1024] = { 0 };
    char ch = 0;
    int i = 0;
    for (;;) {
        ch = getchar();
        if (ch == '\n') {
            break;
        }
        acc[i++] = ch;
    }
    StringItem* accitem = trim(acc, i);
    if (accitem == NULL) {
        UI_MainMenu();
        return;
    }
    if (strcmp(accitem->str, lCurUserData->account) == 0 || strcmp(accitem->str, devmodeaccount) == 0) {
        HANDLE_Action_delete_user_case_rmself = (HANDLE)_beginthread(Action_delete_user_case_rmself, 0, NULL);
        UI_MainMenu();
        WaitForSingleObject(HANDLE_Action_delete_user_case_rmself, INFINITE);
        return;
    }
    int ok = removeUserData(lCurUserDatas, *lCurUserDatasSize, lCurUserData, accitem);
    if (ok != 0) {
        HANDLE_Action_delete_user_case_rmerr = (HANDLE)_beginthread(Action_delete_user_case_rmerr, 0, NULL);
        WaitForSingleObject(HANDLE_Action_delete_user_case_rmerr, INFINITE);
    } else {//���¶�ȡ����
        CurUserDatas = readUserData(&CurUserDatasSize);
    }
    UI_MainMenu();
}
void Action_openMDB_sendMsg() {
    MessageBox(NULL, "mdb���ݿ��ʧ�ܣ���鿴������־��", "����", MB_OK);
}
HANDLE HANDLE_Action_openMDB_sendMsg;
void Action_openMDB() {
    //���浱ǰ����Ȼ�����������ʱ������MDB�ļ���ָ��
    if (nodelink != NULL && nodelinkpath != NULL) {
        saveAsMdb(nodelinkpath->str, nodelink);
        ListNode* head = getHeadNode(nodelink);
        ListNode* cur = head;
        while (cur != NULL) {
            ListNode* nextn = cur->next;
            deleteListNode(cur);
            cur = nextn;
        }
        freeStringItem(nodelinkpath);
        nodelinkpath = NULL;
        nodelink = NULL;
    } else if (nodelink != NULL && nodelinkpath == NULL) {//û��ȡmdb����������
        char tmppath[1024] = { 0 };
        char* t = getNowTimeString();
        sprintf(tmppath, "%s-%s.temp.mdb", "tmp_database_auto_save", t);
        free(t);
        saveAsMdb(tmppath, nodelink);
        ListNode* head = getHeadNode(nodelink);
        ListNode* cur = head;
        while (cur != NULL) {
            ListNode* nextn = cur->next;
            deleteListNode(cur);
            cur = nextn;
        }
        nodelinkpath = NULL;
        nodelink = NULL;
    }
    char mdbpath[1024] = { 0 };
    char ch = 0;
    int i = 0;
    for (;;) {
        ch = getchar();
        if (ch == '\n') {
            break;
        }
        mdbpath[i++] = ch;
    }
    StringItem* accitem = trim(mdbpath, i);
    if (accitem == NULL) {
        accitem = (StringItem*)malloc(sizeof(StringItem));
        nodelink = readAllFromMdb(NULL);
        nodelinkpath = (StringItem*)malloc(sizeof(StringItem));
        nodelinkpath->size = strlen(MDB_DEFAULT_PATH) + 1;
        nodelinkpath->str = (char*)malloc(sizeof(char) * (nodelinkpath->size));
        memcpy(nodelinkpath->str, MDB_DEFAULT_PATH, nodelinkpath->size);
    } else {
        //win11�����ļ���ַ���ܻ��� ' or "
        if (accitem->str[0] == '\"' || accitem->str[0] == '\'') {
            char* nstr = (char*)malloc(accitem->size - 2);
            memcpy(nstr, accitem->str + 1, accitem->size - 2);//ȥ������(��β)
            nstr[accitem->size - 3] = '\0';
            accitem->str = nstr;
            accitem->size = accitem->size - 2;
        }
        nodelink = readAllFromMdb(accitem->str);
        nodelinkpath = accitem;
    }
    if (nodelink == NULL) {
        HANDLE_Action_openMDB_sendMsg = (HANDLE)_beginthread(Action_openMDB_sendMsg, 0, NULL);
        UI_MainMenu();
        WaitForSingleObject(HANDLE_Action_openMDB_sendMsg, INFINITE);
    } else {
        UI_MainMenu();
    }
}
void Action_txt_import(ListNode* Rnodelink) {
    char txtpath[1024] = { 0 };
    char ch = 0;
    int i = 0;
    for (;;) {
        ch = getchar();
        if (ch == '\n') {
            break;
        }
        txtpath[i++] = ch;
    }
    StringItem* accitem = trim(txtpath, i);
    if (accitem == NULL) {
        UI_MainMenu();
        return;
    }
    if (accitem->str[0] == '\"' || accitem->str[0] == '\'') {
        char* nstr = (char*)malloc(accitem->size - 2);
        memcpy(nstr, accitem->str + 1, accitem->size - 2);//ȥ������(��β)
        nstr[accitem->size - 3] = '\0';
        accitem->str = nstr;
        accitem->size = accitem->size - 2;
    }
    if (Rnodelink == NULL) {
        nodelink = readTxtData(accitem->str);
        Rnodelink = nodelink;
    } else {//�������
        ListNode* tail = getTailNode(Rnodelink);
        ListNode* newnode = readTxtData(accitem->str);
        if (newnode == NULL) {
            UI_MainMenu();
            return;
        }
        tail->next = newnode;
        newnode->prev = tail;
        rebindListNode(Rnodelink);
        nodelink = Rnodelink;
        if (nodelinkpath != NULL) {
            saveAsMdb(nodelinkpath->str, Rnodelink);
        } else if (nodelinkpath == NULL) {//û��ȡmdb����������
            char tmppath[1024] = { 0 };
            char* t = getNowTimeString();
            sprintf(tmppath, "%s-%s.temp.mdb", "tmp_database_auto_save", t);
            free(t);
            saveAsMdb(tmppath, Rnodelink);
        }
    }
    UI_MainMenu();
}
void Action_export_mdb_NULLNL() {
    MessageBox(NULL, "��ǰ�ǿ����ݵ������Ѿ�ִ�е��������ǿ��������⣡", "��ʾ", MB_OK);
}
HANDLE HANDLE_Action_export_mdb_NULLNL;
void Action_export_mdb(ListNode* nodelink) {
    char mdbpath[1024] = { 0 };
    char ch = 0;
    int i = 0;
    for (;;) {
        ch = getchar();
        if (ch == '\n') {
            break;
        }
        mdbpath[i++] = ch;
    }
    StringItem* mdbitem = trim(mdbpath, i);
    if (mdbitem != NULL) {
        if (nodelinkpath != NULL) {
            freeStringItem(nodelinkpath);
        }
        nodelinkpath = mdbitem;
    }
    if (nodelink == NULL) {
        //��Ҳ��һ�����
        char* MDB_HEADER_TK = get_MDB_HEADER_TK();
        FILE* fp = fopen(mdbpath, "wb");
        if (fp == NULL) {
            char* errmsg = malloc(sizeof(char) * 200 + strlen(mdbitem->str));
            memset(errmsg, 0, 200 + strlen(mdbitem->str));
            sprintf(errmsg, "mdb��%s��д��ʧ�ܣ�", mdbitem->str);
            mkerrlog(errmsg);
            free(errmsg);
            free(MDB_HEADER_TK);
            return;
        }
        //д��ͷ����Ϣ
        fwrite(MDB_HEADER_TK, sizeof(char), 4, fp);
        //sizeof(int)
        char MDB_PLATNFORM_INT_SIZE = sizeof(int) & 0xff;
        fwrite(&MDB_PLATNFORM_INT_SIZE, sizeof(char), 1, fp);
        //һ���ж��ٸ�
        int len = 0;
        fwrite(&len, sizeof(int), 1, fp);
        fclose(fp);
        free(MDB_HEADER_TK);
        HANDLE_Action_export_mdb_NULLNL = (HANDLE)_beginthread(Action_export_mdb_NULLNL, 0, NULL);
        UI_MainMenu();
        WaitForSingleObject(HANDLE_Action_export_mdb_NULLNL, INFINITE);
        return;
    } else {
        saveAsMdb(mdbitem->str, nodelink);
        UI_MainMenu();
    }
}
void Action_append_new_data() {
    if (nodelink != NULL) {
        nodelink = getTailNode(nodelink);
    }
    //��һ��̫�����ˣ�����UI-Action��ʽд�����ˣ�����е����ֹ���
    carInfoItem* newData = gen_Empty_carInfoItem();
    //ʵ����̫���ˣ�����ֻ��Ԥ��һ����
    char CII_K_ARR[][256] = {
        "�����복�����(carId)��",
        "�����복��Ʒ��(carBrand)��",
        "�����복���ͺ�(carModel)��",
        "������ԭ��(carPrice)��",
        "�����복��(carAge)��",
        "�������Ƿ��д���(hasRepair)��",
        "�������Ƿ��й���(hasFault)��",
        "���������������û������д���޹��ϡ�(faultDescribe)��",
        "������״̬(status)��",
        "����������(date)��",
        "���������(inPrice)��",
        "���������ۼ�(outPrice)��",
        "��������Ƽ�(estimatePrice)��",
        "������ʵ�ۼۣ�δ������д��-1��(realPrice)��",
        "��������������(sellerName)��",
        "���������ҵ绰(sellerPhone)��",
        "�������������(buyerName)��",
        "��������ҵ绰(buyerPhone)��",
        "�����뾭��������(handlerName)��",
        "�����뾭���˵绰(handlerPhone)��",
        "������Ա������(employeeName)��",
        "������Ա������(employeeId)��",
    };
    enum wanna_VTYPE {
        wanna_String = 0,
        wanna_Int,
        wanna_Boolean
    };
    int CII_V_ARR_TYPE[] = {
        //0
        wanna_Int,//carId
        wanna_String,//carBrand
        wanna_String,//carModel
        wanna_Int,//carPrice
        wanna_Int,//carAge
        //5
        wanna_Boolean,//hasRepair
        wanna_Boolean,//hasFault
        wanna_String,//faultDescribe
        wanna_String,//status
        wanna_String,//date
        //10
        wanna_Int,//inPrice
        wanna_Int,//outPrice
        wanna_Int,//estimatePrice
        wanna_Int,//realPrice
        wanna_String,//sellerName
        //15
        wanna_String,//sellerPhone
        wanna_String,//buyerName
        wanna_String,//buyerPhone
        wanna_String,//handlerName
        wanna_String,//handlerPhone
        //20
        wanna_String,//employeeName
        wanna_Int,//employeeId
    };
    int loops = sizeof(CII_V_ARR_TYPE) / sizeof(CII_V_ARR_TYPE[0]);
    int i;
    for (i = 0; i < loops; i++) {
        printf("%s", CII_K_ARR[i]);
        switch (CII_V_ARR_TYPE[i]) {
            case wanna_Int:
                {
                    int tmp = 0;
                    scanf("%d", &tmp);
                    char ch;
                    while ((ch = getchar()) != '\n');
                    switch (i) {
                        case 0://carId
                            newData->info->carId = tmp;
                            break;
                        case 3://carPrice
                            newData->info->carPrice = tmp;
                            break;
                        case 4://carAge
                            newData->info->carAge = tmp;
                            break;
                        case 10://inPrice
                            newData->order->inPrice = tmp;
                            break;
                        case 11://outPrice
                            newData->order->outPrice = tmp;
                            break;
                        case 12://estimatePrice
                            newData->order->estimatePrice = tmp;
                            break;
                        case 13://realPrice
                            newData->order->realPrice = tmp;
                            break;
                        case 21://employeeId
                            newData->order->employee->id = tmp;
                            break;
                    }
                    break;
                }
            case wanna_String:
                {
                    char tmp[256] = { 0 };
                    scanf("%s", tmp);
                    char ch;
                    while ((ch = getchar()) != '\n');
                    StringItem* stritem = trim(tmp, strlen(tmp));
                    switch (i) {
                        case 1:
                            {
                                //carBrand
                                freeStringItem(newData->info->carBrand);
                                newData->info->carBrand = stritem;
                                break;
                            }
                        case 2:
                            {
                                //carModel
                                freeStringItem(newData->info->carModel);
                                newData->info->carModel = stritem;
                                break;
                            }
                        case  7:
                            {
                                //faultDescribe
                                freeStringItem(newData->info->fault->faultDescribe);
                                newData->info->fault->faultDescribe = stritem;
                                break;
                            }
                        case 8:
                            {
                                //status
                                char* tmp = stritem->str;
                                if (strcmp(tmp, "δ֪") == 0 || strcmp(tmp, "unknown") == 0 || strcmp(tmp, "0") == 0) {
                                    newData->order->status = carStatus_unknown;
                                } else if (strcmp(tmp, "�ڿ�") == 0 || strcmp(tmp, "instock") == 0 || strcmp(tmp, "1") == 0) {
                                    newData->order->status = carStatus_inStock;
                                } else if (strcmp(tmp, "����") == 0 || strcmp(tmp, "outstock") == 0 || strcmp(tmp, "2") == 0) {
                                    newData->order->status = carStatus_outStock;
                                } else if (strcmp(tmp, "Ԥ��") == 0 || strcmp(tmp, "reserved") == 0 || strcmp(tmp, "3") == 0) {
                                    newData->order->status = carStatus_reserved;
                                } else if (strcmp(tmp, "����") == 0 || strcmp(tmp, "sold") == 0 || strcmp(tmp, "4") == 0) {
                                    newData->order->status = carStatus_sold;
                                } else {
                                    newData->order->status = carStatus_unknown;
                                }
                                freeStringItem(stritem);
                                tmp = NULL;
                                break;
                            }
                        case 9:
                            {
                                //date
                                int year, month, day;
                                sscanf(stritem->str, "%d/%d/%d", &year, &month, &day);
                                newData->order->date->year = year;
                                newData->order->date->month = month;
                                newData->order->date->day = day;
                                break;
                            }
                        case 14:
                            {
                                //sellerName
                                freeStringItem(newData->order->seller->name);
                                newData->order->seller->name = stritem;
                                break;
                            }
                        case 15:
                            {
                                //sellerPhone
                                freeStringItem(newData->order->seller->phone);
                                newData->order->seller->phone = stritem;
                                break;
                            }
                        case 16:
                            {
                                //buyerName
                                freeStringItem(newData->order->buyer->name);
                                newData->order->buyer->name = stritem;
                                break;
                            }
                        case 17:
                            {
                                //buyerPhone
                                freeStringItem(newData->order->buyer->phone);
                                newData->order->buyer->phone = stritem;
                                break;
                            }
                        case 18:
                            {
                                //handlerName
                                freeStringItem(newData->order->handler->name);
                                newData->order->handler->name = stritem;
                                break;
                            }
                        case 19:
                            {
                                //handlerPhone
                                freeStringItem(newData->order->handler->phone);
                                newData->order->handler->phone = stritem;
                                break;
                            }
                        case 20:
                            {
                                //employeeName
                                freeStringItem(newData->order->employee->name);
                                newData->order->employee->name = stritem;
                                break;
                            }
                    }
                    break;
                }
            case wanna_Boolean:
                {
                    char tmp[32] = { 0 };
                    scanf("%s", tmp);
                    char ch;
                    while ((ch = getchar()) != '\n');
                    int bool_tmp = 0;
                    if (strcmp(tmp, "true") == 0 || strcmp(tmp, "True") == 0 || strcmp(tmp, "TRUE") == 0
                    || strcmp(tmp, "1") == 0 || strcmp(tmp, "��") == 0 || strcmp(tmp, "yes") == 0 || strcmp(tmp, "Yes") == 0
                    || strcmp(tmp, "YES") == 0 || strcmp(tmp, "y") == 0 || strcmp(tmp, "Y") == 0 || strcmp(tmp, "��") == 0 ||
                    strcmp(tmp, "v") == 0 || strcmp(tmp, "V") == 0) {
                        bool_tmp = 1;
                    }
                    switch (i) {
                        case 5://hasRepair
                            newData->info->fault->hasRepair = bool_tmp;
                            break;
                        case 6://hasFault
                            newData->info->fault->hasFault = bool_tmp;
                            break;
                    }
                    break;
                }
            default:
                break;
        }
        printf("\n");
    }
    nodelink = addListNode(nodelink, newData);
    if (nodelink != NULL) {
        nodelink = getHeadNode(nodelink);
    }
    //save
    if (nodelinkpath != NULL)
        saveAsMdb(nodelinkpath->str, nodelink);
    //new one?
    char tmp[32] = { 0 };
    printf("�Ƿ������ӳ�����Ϣ��(y/n)��");
    scanf("%s", tmp);
    char ch;
    while ((ch = getchar()) != '\n');
    if (strcmp(tmp, "y") == 0 || strcmp(tmp, "Y") == 0 || strcmp(tmp, "yes") == 0 || strcmp(tmp, "Yes") == 0 || strcmp(tmp, "YES") == 0 || strcmp(tmp, "��") == 0 || strcmp(tmp, "��") == 0 || strcmp(tmp, "v") == 0 || strcmp(tmp, "V") == 0) {
        UI_append_new_data();
    } else {
        UI_MainMenu();
    }
}
void Action_remove_data() {
    char tmp[32] = { 0 };
    scanf("%s", tmp);
    StringItem* cid = trim(tmp, strlen(tmp));
    if (cid == NULL) {
        UI_MainMenu();
        return;
    }
    int ncid = 0;
    sscanf(cid->str, "%d", &ncid);
    deleteDataByCarId(nodelink, ncid);
    //save
    if (nodelinkpath != NULL)
        saveAsMdb(nodelinkpath->str, nodelink);
    UI_MainMenu();
}
void Action_peek_data_case_NULL() {
    MessageBox(NULL, "��ѯ��Ч��û���ҵ���س�����Ϣ��", "����", MB_OK);
}
HANDLE HANDLE_Action_peek_data_case_NULL;
void Action_peek_data_case_NULLNL() {
    MessageBox(NULL, "û�м������ݿ⣡", "����", MB_OK);
}
HANDLE HANDLE_Action_peek_data_case_NULLNL;
void Action_peek_data() {
    if (nodelink == NULL) {
        HANDLE_Action_peek_data_case_NULLNL = (HANDLE)_beginthread(Action_peek_data_case_NULLNL, 0, NULL);
        UI_MainMenu();
        WaitForSingleObject(HANDLE_Action_peek_data_case_NULLNL, INFINITE);
    }
    ListNode* Rlinknode = shallowCloneListNodes(nodelink);//��ֹ��ԭ����˳����ˣ���ǳ�㿽��
    ListNode* linknode = Rlinknode;
    /*
    ������ѡ��
    */
    printf("��ѡ��������(u/d������u)��");
    char tmp[32] = { 0 };
    scanf("%s", tmp);
    char ch;
    while ((ch = getchar()) != '\n');
    int UDM = UDMode_Up;
    if (strcmp(tmp, "u") == 0 || strcmp(tmp, "U") == 0 || strcmp(tmp, "up") == 0
    || strcmp(tmp, "Up") == 0 || strcmp(tmp, "UP") == 0 || strcmp(tmp, "0") == 0
    || strcmp(tmp, "��") == 0 || strcmp(tmp, "����") == 0 || strcmp(tmp, "������") == 0
    || strcmp(tmp, "����") == 0 || strcmp(tmp, "��") == 0) {
        UDM = UDMode_Up;
    } else if (strcmp(tmp, "d") == 0 || strcmp(tmp, "D") == 0 || strcmp(tmp, "down") == 0
    || strcmp(tmp, "Down") == 0 || strcmp(tmp, "DOWN") == 0 || strcmp(tmp, "1") == 0
    || strcmp(tmp, "��") == 0 || strcmp(tmp, "�½�") == 0 || strcmp(tmp, "�½���") == 0
    || strcmp(tmp, "����") == 0 || strcmp(tmp, "��") == 0) {
        UDM = UDMode_Down;
    }
    UI_clearScreen();
    /*
    ɸѡ��ʽѡ��
    */
    printf(
"��ѡ��ɸѡ��ʽ��Ĭ�Ͽ��ǲ���ɸѡ��֧�ֶ�����ѡ����ֵ��ϣ���\n\
1.������ţ�������ѯ��\n\
2.����Ʒ��\n\
3.�����ͺ�\n\
4.�۸�\n\
5.����\n\
6.�Ƿ��д���\n\
7.�Ƿ��й���\n\
8.״̬\n\
9.����\n\
10.����\n\
11.���ۼ�\n\
12.���Ƽ�\n\
13.ʵ�ۼ�\n\
14.���۵�\n\
15.��������\n\
16.���ҵ绰\n\
17.�������\n\
18.��ҵ绰\n\
19.����������\n\
20.�����˵绰\n\
21.Ա������\n\
��ѡ��");
    int findID = 0;
    //����Ҫ��Ԥ�ȸ������ռ䣬��ֹ����������
    int carItemLen = getTailNode(linknode)->index - getHeadNode(linknode)->index + 1;
    int QueryOptions[64] = { 0 };
    carInfoItem** carInfoItemList = NULL;
    int qoi = 0;
    char qochars[1024] = { 0 };
    char qochar;
    while ((qochar = getchar()) != '\n') {
        qochars[qoi++] = qochar;
    }
    int qosize;
    char* qochars2 = qochars;
    for (qosize = 0;qosize < 64;qosize++) {
        int temp = 0;
        qochars2 = getint(qochars2, &temp);
        QueryOptions[qosize] = temp;
        if (temp == 1) {
            findID = 1;
        }
        if (qochars2 == NULL) {
            qosize++;
            break;
        }
    }
    for (qoi = 0;qoi < 64;qoi++) {//���ɸѡ������
        int QueryOption = QueryOptions[qoi];
        if (QueryOption == 0) {
            break;
        }
        switch (QueryOption) {
            case 1:
                {
                    printf("��ѡ������ţ�");
                    int carId = 0;
                    scanf("%d", &carId);
                    while ((ch = getchar()) != '\n');
                    carInfoItem* cii = QueryByCarId(linknode, carId);
                    if (cii == NULL) {
                        HANDLE_Action_peek_data_case_NULL = (HANDLE)_beginthread(Action_peek_data_case_NULL, 0, NULL);
                        UI_MainMenu();
                        WaitForSingleObject(HANDLE_Action_peek_data_case_NULL, INFINITE);
                        return;
                    }
                    carItemLen = 1;
                    carInfoItemList = (carInfoItem**)malloc(sizeof(carInfoItem*));
                    carInfoItemList[0] = cii;
                    linknode = creatListNodeByCarInfoItems(carInfoItemList, carItemLen);
                    break;
                }
            case 2:
                {
                    printf("��ѡ����Ʒ�ƣ�");
                    char carBrand[64] = { 0 };
                    scanf("%s", carBrand);
                    while ((ch = getchar()) != '\n');
                    StringItem* cb = trim(carBrand, strlen(carBrand));
                    if (cb == NULL) {
                        HANDLE_Action_peek_data_case_NULL = (HANDLE)_beginthread(Action_peek_data_case_NULL, 0, NULL);
                        UI_MainMenu();
                        WaitForSingleObject(HANDLE_Action_peek_data_case_NULL, INFINITE);
                        return;
                    }
                    carInfoItemList = QueryByCarBrand(linknode, cb, &carItemLen);
                    linknode = creatListNodeByCarInfoItems(carInfoItemList, carItemLen);
                    freeStringItem(cb);
                    break;
                }
            case 3:
                {
                    printf("��ѡ�����ͺţ�");
                    char carModel[64] = { 0 };
                    scanf("%s", carModel);
                    while ((ch = getchar()) != '\n');
                    StringItem* cm = trim(carModel, strlen(carModel));
                    if (cm == NULL) {
                        HANDLE_Action_peek_data_case_NULL = (HANDLE)_beginthread(Action_peek_data_case_NULL, 0, NULL);
                        UI_MainMenu();
                        WaitForSingleObject(HANDLE_Action_peek_data_case_NULL, INFINITE);
                        return;
                    }
                    carInfoItemList = QueryByCarModel(linknode, cm, &carItemLen);
                    linknode = creatListNodeByCarInfoItems(carInfoItemList, carItemLen);
                    break;
                }
            case 4:
                {
                    printf("��ѡ�����۸����䣺");
                    int min = 0;
                    int max = 0;
                    scanf("%d", &min);
                    scanf("%d", &max);
                    while ((ch = getchar()) != '\n');
                    carInfoItemList = QueryByCarPrice(linknode, min, max, &carItemLen);
                    linknode = creatListNodeByCarInfoItems(carInfoItemList, carItemLen);
                    break;
                }
            case 5:
                {
                    printf("��ѡ�������䣺");
                    int min = 0;
                    int max = 0;
                    scanf("%d", &min);
                    scanf("%d", &max);
                    while ((ch = getchar()) != '\n');
                    carInfoItemList = QueryByCarAge(linknode, min, max, &carItemLen);
                    linknode = creatListNodeByCarInfoItems(carInfoItemList, carItemLen);
                    break;
                }
            case 6:
                {
                    printf("��ѡ���Ƿ��д��޵ķ�ѡ��");
                    char strtmp[64] = { 0 };
                    scanf("%s", strtmp);
                    while ((ch = getchar()) != '\n');
                    int UisRepair = Boolean_FALSE;
                    if (strcmp(strtmp, "��") == 0 || strcmp(strtmp, "1") == 0 || strcmp(strtmp, "true") == 0 || strcmp(strtmp, "True") == 0
                    || strcmp(strtmp, "TRUE") == 0 || strcmp(strtmp, "YES") == 0 || strcmp(strtmp, "yes") == 0 || strcmp(strtmp, "Yes") == 0) {
                        UisRepair = Boolean_TRUE;
                    } else if (strcmp(strtmp, "��") == 0 || strcmp(strtmp, "0") == 0 || strcmp(strtmp, "false") == 0 || strcmp(strtmp, "False") == 0
                    || strcmp(strtmp, "FALSE") == 0 || strcmp(strtmp, "NO") == 0 || strcmp(strtmp, "no") == 0 || strcmp(strtmp, "No") == 0) {
                        UisRepair = Boolean_FALSE;
                    }
                    carInfoItemList = QueryByCarHasRepair(linknode, UisRepair, &carItemLen);
                    linknode = creatListNodeByCarInfoItems(carInfoItemList, carItemLen);
                    break;
                }
            case 7:
                {
                    printf("��ѡ���Ƿ��й��ϵķ�ѡ��");
                    char strtmp[64] = { 0 };
                    scanf("%s", strtmp);
                    while ((ch = getchar()) != '\n');
                    int UisFault = Boolean_FALSE;
                    if (strcmp(strtmp, "��") == 0 || strcmp(strtmp, "1") == 0 || strcmp(strtmp, "true") == 0 || strcmp(strtmp, "True") == 0
                    || strcmp(strtmp, "TRUE") == 0 || strcmp(strtmp, "YES") == 0 || strcmp(strtmp, "yes") == 0 || strcmp(strtmp, "Yes") == 0) {
                        UisFault = Boolean_TRUE;
                    } else if (strcmp(strtmp, "��") == 0 || strcmp(strtmp, "0") == 0 || strcmp(strtmp, "false") == 0 || strcmp(strtmp, "False") == 0
                    || strcmp(strtmp, "FALSE") == 0 || strcmp(strtmp, "NO") == 0 || strcmp(strtmp, "no") == 0 || strcmp(strtmp, "No") == 0) {
                        UisFault = Boolean_FALSE;
                    }
                    carInfoItemList = QueryByCarHasFault(linknode, UisFault, &carItemLen);
                    linknode = creatListNodeByCarInfoItems(carInfoItemList, carItemLen);
                    break;
                }
            case 8:
                {
                    printf("��ѡ��״̬��");
                    char strtmp[64] = { 0 };
                    scanf("%s", strtmp);
                    while ((ch = getchar()) != '\n');
                    int status = 0;
                    if (strcmp(strtmp, "�ڿ�") == 0 || strcmp(strtmp, "1") == 0 || strcmp(strtmp, "inStock") == 0) {
                        status = 1;
                    } else if (strcmp(strtmp, "����") == 0 || strcmp(strtmp, "2") == 0 || strcmp(strtmp, "outStock") == 0) {
                        status = 2;
                    } else if (strcmp(strtmp, "Ԥ��") == 0 || strcmp(strtmp, "3") == 0 || strcmp(strtmp, "reserved") == 0) {
                        status = 3;
                    } else if (strcmp(strtmp, "����") == 0 || strcmp(strtmp, "4") == 0 || strcmp(strtmp, "sold") == 0) {
                        status = 4;
                    }
                    carInfoItemList = QueryByCarStatus(linknode, status, &carItemLen);
                    linknode = creatListNodeByCarInfoItems(carInfoItemList, carItemLen);
                    break;
                }
            case 9:
                {
                    printf("��ѡ��ʱ���(��ʽ��y/m/d y/m/d)��");
                    Date* start = (Date*)malloc(sizeof(Date));
                    Date* end = (Date*)malloc(sizeof(Date));
                    scanf("%d/%d/%d", &(start->year), &(start->month), &(start->day));
                    scanf("%d/%d/%d", &(end->year), &(end->month), &(end->day));
                    while ((ch = getchar()) != '\n');
                    carInfoItemList = QueryByDate(linknode, start, end, &carItemLen);
                    linknode = creatListNodeByCarInfoItems(carInfoItemList, carItemLen);
                    break;
                }
            case 10:
                {
                    printf("��ѡ��������䣺");
                    int min = 0;
                    int max = 0;
                    scanf("%d", &min);
                    scanf("%d", &max);
                    while ((ch = getchar()) != '\n');
                    carInfoItemList = QueryByInPrice(linknode, min, max, &carItemLen);
                    linknode = creatListNodeByCarInfoItems(carInfoItemList, carItemLen);
                    break;
                }
            case 11:
                {
                    printf("��ѡ�����ۼ����䣺");
                    int min = 0;
                    int max = 0;
                    scanf("%d", &min);
                    scanf("%d", &max);
                    while ((ch = getchar()) != '\n');
                    carInfoItemList = QueryByOutPrice(linknode, min, max, &carItemLen);
                    linknode = creatListNodeByCarInfoItems(carInfoItemList, carItemLen);
                    break;
                }
            case 12:
                {
                    printf("��ѡ����Ƽ����䣺");
                    int min = 0;
                    int max = 0;
                    scanf("%d", &min);
                    scanf("%d", &max);
                    while ((ch = getchar()) != '\n');
                    carInfoItemList = QueryByEstimatePrice(linknode, min, max, &carItemLen);
                    linknode = creatListNodeByCarInfoItems(carInfoItemList, carItemLen);
                    break;
                }
            case 13:
                {
                    printf("��ѡ��ʵ�ۼ����䣨δ����д��-1 -1����");
                    int min = 0;
                    int max = 0;
                    scanf("%d", &min);
                    scanf("%d", &max);
                    while ((ch = getchar()) != '\n');
                    carInfoItemList = QueryByRealPrice(linknode, min, max, &carItemLen);
                    linknode = creatListNodeByCarInfoItems(carInfoItemList, carItemLen);
                    break;
                }
            case 14:
                {
                    printf("��ѡ�����۵��ķ�ѡ��");
                    char strtmp[64] = { 0 };
                    scanf("%s", strtmp);
                    while ((ch = getchar()) != '\n');
                    int UisInStock = Boolean_FALSE;
                    if (strcmp(strtmp, "��") == 0 || strcmp(strtmp, "1") == 0 || strcmp(strtmp, "true") == 0 || strcmp(strtmp, "True") == 0
                    || strcmp(strtmp, "TRUE") == 0 || strcmp(strtmp, "YES") == 0 || strcmp(strtmp, "yes") == 0 || strcmp(strtmp, "Yes") == 0) {
                        UisInStock = Boolean_TRUE;
                    } else if (strcmp(strtmp, "��") == 0 || strcmp(strtmp, "0") == 0 || strcmp(strtmp, "false") == 0 || strcmp(strtmp, "False") == 0
                    || strcmp(strtmp, "FALSE") == 0 || strcmp(strtmp, "NO") == 0 || strcmp(strtmp, "no") == 0 || strcmp(strtmp, "No") == 0) {
                        UisInStock = Boolean_FALSE;
                    }
                    carInfoItemList = QueryByOnSale(linknode, UisInStock, &carItemLen);
                    linknode = creatListNodeByCarInfoItems(carInfoItemList, carItemLen);
                    break;
                }
            case 15:
                {
                    printf("��ѡ������������");
                    char strtmp[64] = { 0 };
                    scanf("%s", strtmp);
                    while ((ch = getchar()) != '\n');
                    StringItem* name = trim(strtmp, strlen(strtmp));
                    if (name == NULL) {
                        HANDLE_Action_peek_data_case_NULL = (HANDLE)_beginthread(Action_peek_data_case_NULL, 0, NULL);
                        UI_MainMenu();
                        WaitForSingleObject(HANDLE_Action_peek_data_case_NULL, INFINITE);
                        return;
                    }
                    carInfoItemList = QueryBySellerName(linknode, name, &carItemLen);
                    linknode = creatListNodeByCarInfoItems(carInfoItemList, carItemLen);
                    freeStringItem(name);
                    break;
                }
            case 16:
                {
                    printf("��ѡ�����ҵ绰��");
                    char strtmp[64] = { 0 };
                    scanf("%s", strtmp);
                    while ((ch = getchar()) != '\n');
                    StringItem* phone = trim(strtmp, strlen(strtmp));
                    if (phone == NULL) {
                        HANDLE_Action_peek_data_case_NULL = (HANDLE)_beginthread(Action_peek_data_case_NULL, 0, NULL);
                        UI_MainMenu();
                        WaitForSingleObject(HANDLE_Action_peek_data_case_NULL, INFINITE);
                        return;
                    }
                    carInfoItemList = QueryBySellerPhone(linknode, phone, &carItemLen);
                    linknode = creatListNodeByCarInfoItems(carInfoItemList, carItemLen);
                    freeStringItem(phone);
                    break;
                }
            case 17:
                {
                    printf("��ѡ�����������");
                    char strtmp[64] = { 0 };
                    scanf("%s", strtmp);
                    while ((ch = getchar()) != '\n');
                    StringItem* name = trim(strtmp, strlen(strtmp));
                    if (name == NULL) {
                        HANDLE_Action_peek_data_case_NULL = (HANDLE)_beginthread(Action_peek_data_case_NULL, 0, NULL);
                        UI_MainMenu();
                        WaitForSingleObject(HANDLE_Action_peek_data_case_NULL, INFINITE);
                        return;
                    }
                    carInfoItemList = QueryByBuyerName(linknode, name, &carItemLen);
                    linknode = creatListNodeByCarInfoItems(carInfoItemList, carItemLen);
                    freeStringItem(name);
                    break;
                }
            case 18:
                {
                    printf("��ѡ����ҵ绰��");
                    char strtmp[64] = { 0 };
                    scanf("%s", strtmp);
                    while ((ch = getchar()) != '\n');
                    StringItem* phone = trim(strtmp, strlen(strtmp));
                    if (phone == NULL) {
                        HANDLE_Action_peek_data_case_NULL = (HANDLE)_beginthread(Action_peek_data_case_NULL, 0, NULL);
                        UI_MainMenu();
                        WaitForSingleObject(HANDLE_Action_peek_data_case_NULL, INFINITE);
                        return;
                    }
                    carInfoItemList = QueryByBuyerPhone(linknode, phone, &carItemLen);
                    linknode = creatListNodeByCarInfoItems(carInfoItemList, carItemLen);
                    freeStringItem(phone);
                    break;
                }
            case 19:
                {
                    printf("��ѡ������������");
                    char strtmp[64] = { 0 };
                    scanf("%s", strtmp);
                    while ((ch = getchar()) != '\n');
                    StringItem* name = trim(strtmp, strlen(strtmp));
                    if (name == NULL) {
                        HANDLE_Action_peek_data_case_NULL = (HANDLE)_beginthread(Action_peek_data_case_NULL, 0, NULL);
                        UI_MainMenu();
                        WaitForSingleObject(HANDLE_Action_peek_data_case_NULL, INFINITE);
                        return;
                    }
                    carInfoItemList = QueryByHandlerName(linknode, name, &carItemLen);
                    linknode = creatListNodeByCarInfoItems(carInfoItemList, carItemLen);
                    freeStringItem(name);
                    break;
                }
            case 20:
                {
                    printf("��ѡ�����˵绰��");
                    char strtmp[64] = { 0 };
                    scanf("%s", strtmp);
                    while ((ch = getchar()) != '\n');
                    StringItem* phone = trim(strtmp, strlen(strtmp));
                    if (phone == NULL) {
                        HANDLE_Action_peek_data_case_NULL = (HANDLE)_beginthread(Action_peek_data_case_NULL, 0, NULL);
                        UI_MainMenu();
                        WaitForSingleObject(HANDLE_Action_peek_data_case_NULL, INFINITE);
                        return;
                    }
                    carInfoItemList = QueryByHandlerPhone(linknode, phone, &carItemLen);
                    linknode = creatListNodeByCarInfoItems(carInfoItemList, carItemLen);
                    freeStringItem(phone);
                    break;
                }
            case 21:
                {
                    printf("��ѡ��Ա�����ţ�");
                    int empId = 0;
                    scanf("%d", &empId);
                    while ((ch = getchar()) != '\n');
                    carInfoItemList = QueryByEmployeeId(linknode, empId, &carItemLen);
                    linknode = creatListNodeByCarInfoItems(carInfoItemList, carItemLen);
                    break;
                }
        }
        if (linknode != NULL) {
            linknode = getHeadNode(linknode);
        } else {//û�С���
            UI_clearScreen();
            HANDLE_Action_peek_data_case_NULL = (HANDLE)_beginthread(Action_peek_data_case_NULL, 0, NULL);
            UI_MainMenu();
            WaitForSingleObject(HANDLE_Action_peek_data_case_NULL, INFINITE);
            return;
        }
        if (carInfoItemList != NULL) {//�ǵ�free����Ϊ��malloc������
            free(carInfoItemList);
        }
    }
    if (!findID) {
        UI_clearScreen();
        /*
        ����ʽѡ��
        */
        printf(
    "��ѡ������ʽ��Ĭ�Ͽ��Ƕ�ȡ˳�򣩣�\n\
1.�������\n\
2.����Ʒ��\n\
3.�����ͺ�\n\
4.�۸�\n\
5.����\n\
6.�Ƿ��д���\n\
7.�Ƿ��й���\n\
8.״̬\n\
9.����\n\
10.����\n\
11.���ۼ�\n\
12.���Ƽ�\n\
13.ʵ�ۼ�\n\
14.��������\n\
15.���ҵ绰\n\
16.�������\n\
17.��ҵ绰\n\
18.����������\n\
19.�����˵绰\n\
20.Ա������\n\
21.Ա������\n\
��ѡ��");
        int sortChoice = 0;
        scanf("%d", &sortChoice);
        while ((ch = getchar()) != '\n');
        ListNode* (*sortway)(ListNode*, enum UDMode);
        switch (sortChoice) {
            case 1:
                sortway = SortByCarId;
                break;
            case 2:
                sortway = SortByCarBrand;
                break;
            case 3:
                sortway = SortByCarModel;
                break;
            case 4:
                sortway = SortByCarPrice;
                break;
            case 5:
                sortway = SortByCarAge;
                break;
            case 6:
                sortway = SortByCarHasRepair;
                break;
            case 7:
                sortway = SortByCarHasFault;
                break;
            case 8:
                sortway = SortByCarStatus;
                break;
            case 9:
                sortway = SortByDate;
                break;
            case 10:
                sortway = SortByInPrice;
                break;
            case 11:
                sortway = SortByOutPrice;
                break;
            case 12:
                sortway = SortByEstimatePrice;
                break;
            case 13:
                sortway = SortByRealPrice;
                break;
            case 14:
                sortway = SortBySellerName;
                break;
            case 15:
                sortway = SortBySellerPhone;
                break;
            case 16:
                sortway = SortByBuyerName;
                break;
            case 17:
                sortway = SortByBuyerPhone;
                break;
            case 18:
                sortway = SortByHandlerName;
                break;
            case 19:
                sortway = SortByHandlerPhone;
                break;
            case 20:
                sortway = SortByEmployeeName;
                break;
            case 21:
                sortway = SortByEmployeeId;
                break;
            default:
                sortway = NULL;
                break;
        }
        if (sortway != NULL) {
            linknode = sortway(linknode, UDM);
        }
    }
    UI_clearScreen();
    /*
    �鿴��ѡ��
    */
    printf(
"��ѡ��鿴�����Ĭ��ȫ������ѡ����һ���Կո�������ѡ������һ��ֵ��-1����ô�Ƿ�ѡģʽ��������������ǲ��鿴�ģ�\n\
1.�������(carId)\n\
2.����Ʒ��(carBrand)\n\
3.�����ͺ�(carModel)\n\
4.����ԭ��(carPrice)\n\
5.����(carAge)\n\
6.�Ƿ��д���(hasRepair)\n\
7.�Ƿ��й���(hasFault)\n\
8.��������(faultDescribe)\n\
9.״̬(status)\n\
10.����(date)\n\
11.����(inPrice)\n\
12.���ۼ�(outPrice)\n\
13.���Ƽ�(estimatePrice)\n\
14.ʵ�ۼ�(realPrice)\n\
15.����(seller)\n\
16.���(buyer)\n\
17.������(handler)\n\
18.Ա��(employee)\n\
19.��Ա������(person_name)\n\
20.��Ա�ĵ绰(person_phone)\n\
21.��Ա�Ĺ���(person_id)\n\
��ѡ��");
    int peekSize = 0;
    int* peekparams = getPeekFullModeParam(&peekSize);//�ǵ�free����
    char peekchars[1024] = { 0 };
    int peeki = 0;
    char peekchar;
    while ((peekchar = getchar()) != '\n') {
        peekchars[peeki++] = peekchar;
    }
    int ints[64] = { 0 };
    int intssize;
    char* peekchars2 = peekchars;
    for (intssize = 0;intssize < 64;intssize++) {
        int temp = 0;
        peekchars2 = getint(peekchars2, &temp);
        ints[intssize] = temp;
        if (peekchars2 == NULL) {
            intssize++;
            break;
        }
    }
    if (ints[0] != -1) {//���Ƿ�ѡģʽ
        int j;
        for (j = 0;j < peekSize;j++) {//��0
            peekparams[j] = 0;
        }
        for (j = 0;j < peekSize;j++) {
            peekparams[j] = ints[j];
        }
    } else {//��ѡģʽ
        int j;
        for (j = 1;j < intssize;j++) {
            int k;
            for (k = 0;k < peekSize;k++) {
                if (ints[j] == peekparams[k]) {
                    peekparams[k] = 0;
                }
            }
        }

    }
    if (intssize > peekSize) {
        intssize = peekSize;
    }
    peekToolPage* pages = peekTool_genPeekpage(linknode, peekparams, intssize);
    //free
    free(peekparams);
    ListNode* tempH = getHeadNode(linknode);
    ListNode* cur = tempH;
    while (cur != NULL) {
        ListNode* tmp = cur->next;
        cur->next = NULL;
        cur->prev = NULL;
        cur->value = NULL;
        free(cur);
        cur = tmp;
    }
    UI_showpeek(pages);
}
void Action_showpeek(peekToolPage* pages, int curpage) {
    peekToolPage* tail = pages;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    int pagelen = tail->page;
    if (curpage > pagelen || curpage < 1) {
        UI_MainMenu();
        return;
    }
    StringItem* FIRSTPAGE = getPeekPage(pages, curpage);
    printf("%s\n\n�� %d ҳ / �� %d ҳ\n", FIRSTPAGE->str, curpage, pagelen);
    printf("����˵������һҳ��-1�� ��һҳ��0�� ��ĳҳ��int�� �˳��������������ɣ�\n\
������Ҫ�鿴��ҳ��");
    int peekpage = 0;
    scanf("%d", &peekpage);
    char ch;
    while ((ch = getchar()) != '\n');
    UI_clearScreen();
    if (peekpage == -1) {
        Action_showpeek(pages, curpage - 1);
    } else if (peekpage == 0) {
        Action_showpeek(pages, curpage + 1);
    } else {
        Action_showpeek(pages, peekpage);
    }
}
void Action_modify_data(ListNode* nodelink) {
    printf("������Ҫ�޸ĵĳ�����ţ�ȡ������");
    int carId = 0;
    scanf("%d", &carId);
    char ch;
    while ((ch = getchar()) != '\n');
    ListNode* cur = getHeadNode(nodelink);
    while (cur != NULL) {
        if (cur->value->info->carId == carId) {
            break;
        }
        cur = cur->next;
    }
    printf(
"��ѡ�����б���ֵ����\n\
carId/�������/carBrand/����Ʒ��/carModel/�����ͺ�/carPrice/ԭ��/carAge/����/\
hasRepair/�Ƿ��д���/hasFault/�Ƿ��й���/faultDescribe/��������/status/״̬/date/����/\
inPrice/����/outPrice/���ۼ�/estimatePrice/���Ƽ�/realPrice/ʵ�ۼ�/\
sellerName/��������/sellerPhone/���ҵ绰/buyerName/�������/buyerPhone/��ҵ绰/\
handlerName/����������/handlerPhone/�����˵绰/employeeName/Ա������/employeeId/Ա�����\n");
    printf("������Ҫ�޸ĵļ���");
    int i = 0;
    char key[1024] = { 0 };
    while ((ch = getchar()) != '\n') {
        key[i++] = ch;
    }
    StringItem* KEY = trim(key, strlen(key));
    i = 0;
    char value[1024] = { 0 };
    printf("������Ҫ�޸ĵ�ֵ��");
    scanf("%s", value);
    while ((ch = getchar()) != '\n') {
        value[i++] = ch;
    }
    StringItem* VALUE = trim(value, strlen(value));
    cur = modifyDataByNode(cur, KEY, VALUE);
    nodelink = getHeadNode(nodelink);
    if (nodelinkpath != NULL)
        saveAsMdb(nodelinkpath->str, nodelink);

    printf("�޸ĳɹ���\n�Ƿ��������y/n����");
    char yn[8] = { 0 };
    scanf("%s", yn);
    while ((ch = getchar()) != '\n');
    if (strcmp(yn, "y") == 0) {
        Action_modify_data(nodelink);
    } else {
        UI_MainMenu();
    }
}
void Action_analysis_data(ListNode* nodelink) {
    Analyzer_Result* a = getAnalyzerResult(nodelink);
    printf("%s", a->carBrandAnalyze->str);
    printf("%s", a->carModelAnalyze->str);
    printf("%s", a->carPriceAnalyze->str);
    printf("%s", a->carAgeAnalyze->str);
    printf("%s", a->carFaultAnalyze->str);
    printf("%s", a->statusAnalyze->str);
    printf("%s", a->dateAnalyze->str);
    printf("%s", a->inPriceAnalyze->str);
    printf("%s", a->outPriceAnalyze->str);
    printf("%s", a->estimatePriceAnalyze->str);
    printf("%s", a->realPriceAnalyze->str);
    printf("%s", a->sellerAnalyze->str);
    printf("%s", a->buyerAnalyze->str);
    printf("%s", a->handlerAnalyze->str);
    printf("%s", a->employeeAnalyze->str);
    printf("%s", a->totalAnalyze->str);
    freeAnalyzerResult(a);
    printf("\n�س����أ�");
    char ch;
    while ((ch = getchar()) != '\n');
    UI_MainMenu();
}
