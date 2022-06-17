#include "UIPrint.h"

/*
�������UI�Ĵ�ӡ�⣬��������ע�ͣ�ûɶ�ã��������Ӷ��ѣ���ν��ע�ͣ���ʵ�ǻ��Ƶ�UIʱ�ַ�����ʽ����������õ�ע��
*/
static int finished_WindowSettings = 0;
void initBindWin() {
    if (finished_WindowSettings == 0) {
        finished_WindowSettings = 1;
        system("mode con cols=150 lines=40");
        system("color 0f");
        system("title ���ֳ����۹���ϵͳ");
    }
}

void UI_clearScreen() {
    initBindWin();
    system("clear");
}

void UI_Welcome() {
    UI_clearScreen();
    printf(
"\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\t\t\t\t\t\t\t��ӭʹ�� �����ֳ����۹���ϵͳ�� ��\n\
\n\
\n\
\t\t\t\t\t\t\t             ��  ��\n\
\n\
\n\
\t\t\t\t\t\t\t          1.��¼�˺�\n\
\n\
\t\t\t\t\t\t\t          2.ע���˺�\n\
\n\
\t\t\t\t\t\t\t          3.�رճ���\n\
\n\
\n\
\n\
\n\
\n\
\t\t\t������ѡ����֣���");
    Action_Welcome();
}

void UI_login() {
    UI_clearScreen();
    printf(
"\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\t\t\t\t\t\t\t         �� ¼ �� ��\n\
\t\t\t\t\t\t\t���˺�/�������������Welcome��\n\
\n\
\n\
\t\t\t\t\t\t\t�˺ţ�");
    Action_login();
}

void UI_login_ask_password(StringItem* accitem) {
    printf(
"\n\
\n\
\t\t\t\t\t\t\t���룺");
    Action_login_ask_password(accitem);
}

void UI_register() {
    UI_clearScreen();
    printf(
"\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\t\t\t\t\t\t\t         ע �� �� ��\n\
\t\t\t\t\t\t\t���˺�/�������������Welcome��\n\
\n\
\n\
\t\t\t\t\t\t\t�˺ţ�");
    Action_register();
}

void UI_register_ask_password(StringItem* accitem) {
    printf(
"\n\
\n\
\t\t\t\t\t\t\t���룺");
    Action_register_ask_password(accitem);
}

void UI_register_ask_type(StringItem* accitem, StringItem* passitem) {
    printf(
"\n\
\n\
\t\t\t\t\t\t\t���ͣ�");
    Action_register_ask_type(accitem, passitem);
}

void UI_MainMenu() {
    UI_clearScreen();
    printf(
"\n\
\n\
\n\
\n\
\n\
\t\t\t\t\t\t\t��ӭʹ�� �����ֳ����۹���ϵͳ�� ��\n\
\n\
\n\
\t\t\t\t\t\t\t             ��  ��\n\
\n\
\t\t\t\t\t\t\t          1.�ǳ��˺�\n\
\t\t\t\t\t\t\t          2.ע�����˺�\n\
\t\t\t\t\t\t\t          3.�鿴�˺���Ϣ\n\
\t\t\t\t\t\t\t          4.ɾ���˺�\n\
\t\t\t\t\t\t\t          5.��mdb���ݿ�\n\
\t\t\t\t\t\t\t          6.txt���ݵ��루�Զ������ڵ�ǰmdb�б��棩\n\
\t\t\t\t\t\t\t          7.mdb����\n\
\t\t\t\t\t\t\t          8.���뵥��������\n\
\t\t\t\t\t\t\t          9.ɾ������\n\
\t\t\t\t\t\t\t          10.�鿴����\n\
\t\t\t\t\t\t\t          11.�޸�����\n\
\t\t\t\t\t\t\t          12.����ͳ��\n\
\t\t\t\t\t\t\t          13.�رճ���\n\
\n\
\n\
\t\t\t������ѡ����֣���");
    Action_MainMenu();
}
void UI_peek_userinfo(user_data* CurUserData) {
    UI_clearScreen();
    printf(
"\n\
\n\
\n\
\n\
\n\
\t\t\t\t\t\t\t�鿴�˻���Ϣ��\n\
\n\
\n\
\n");
    printf("\t\t\t\t�˻����ͣ�Ȩ�ޣ���%s\n\n", CurUserData->userType == userType_dev ? "������" : (
        CurUserData->userType == userType_admin ? "����Ա" : (
            CurUserData->userType == userType_manager ? "����" : (
                CurUserData->userType == userType_employee ? "Ա��" : (
                    CurUserData->userType == userType_cust ? "�ͻ�" : "δ֪"
                    )
                ))));
    printf("\t\t\t\t�˺ţ�%s\n\n", CurUserData->account);
    printf("\t\t\t\t���룺%s\n\n", CurUserData->password);
    printf("\t\t\t\t�����������ݷ��أ�");
    Action_peek_userinfo();
}
void UI_delete_user(user_data* CurUserData, user_data** CurUserDatas, int* size) {
    UI_clearScreen();
    printf(
"\n\
\n\
\n\
\n\
\n\
\t\t\t\t\t\t\tɾ���˺ţ�(��������)\n\
\n\
\n\
\n");
    printf("\t\t\t\t�������ɾ�����˺ţ�");
    Action_delete_user(CurUserData, CurUserDatas, size);
}
void UI_openMDB() {
    UI_clearScreen();
    printf(
"\n\
\n\
\n\
\n\
\n\
\t\t\t\t\t\t\t��mdb���ݿ⣺\n\
\n\
\n\
\n");
    printf("\t\t\t\t��������򿪵�mdb�ļ�·����");
    Action_openMDB();
}
void UI_txt_import(ListNode* nodelink) {
    UI_clearScreen();
    printf(
"\n\
\n\
\n\
\n\
\n\
\t\t\t\t\t\t\ttxt���ݵ��루�Զ������ڵ�ǰmdb�б��棩\n\
\n\
\n\
\n");
    printf("\t\t\t\t�����뵼��·������.txt����ֵ��������");
    Action_txt_import(nodelink);
}
void UI_export_mdb(ListNode* nodelink) {
    UI_clearScreen();
    printf(
"\n\
\n\
\n\
\n\
\n\
\t\t\t\t\t\t\t����MDB���ݿ⣺(�״�¼��ʹ��ʱ�뱣��һ�ε�ַ)\n\
\n\
\n\
\n");
    printf("\t\t\t\t�����뵼��·������.mdb����");
    Action_export_mdb(nodelink);
}
void UI_append_new_data() {
    UI_clearScreen();
    printf("���뵥�������ݣ�\n");
    Action_append_new_data();
}
void UI_remove_data() {
    UI_clearScreen();
    printf(
"ɾ�����ݣ�����շ���ִ�У����������Ψһ��������Ϣ�����Ȳ��ҵ����������ɾ����\n\
�����ɾ���ĳ������(carId)��");
    Action_remove_data();
}
void UI_peek_data() {
    UI_clearScreen();
    printf("\t\t\t\t\t\t\t�鿴��\n");
    Action_peek_data();
}
void UI_showpeek(peekToolPage* pages) {
    UI_clearScreen();
    Action_showpeek(pages, 1);
}
void UI_modify_data(ListNode* nodelink) {
    UI_clearScreen();
    printf("\t\t\t\t\t\t\t�޸ģ�\n");
    Action_modify_data(nodelink);
}
void UI_analysis_data(ListNode* nodelink) {
    UI_clearScreen();
    printf("\t\t\t\t\t\t\tͳ�ƣ�\n");
    Action_analysis_data(nodelink);
}