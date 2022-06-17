#include "UIPrint.h"

/*
负责输出UI的打印库，不做过多注释，没啥用，看个样子而已，所谓的注释，其实是绘制的UI时字符串格式，他就是最好的注释
*/
static int finished_WindowSettings = 0;
void initBindWin() {
    if (finished_WindowSettings == 0) {
        finished_WindowSettings = 1;
        system("mode con cols=150 lines=40");
        system("color 0f");
        system("title 二手车销售管理系统");
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
\t\t\t\t\t\t\t欢迎使用 『二手车销售管理系统』 ！\n\
\n\
\n\
\t\t\t\t\t\t\t             菜  单\n\
\n\
\n\
\t\t\t\t\t\t\t          1.登录账号\n\
\n\
\t\t\t\t\t\t\t          2.注册账号\n\
\n\
\t\t\t\t\t\t\t          3.关闭程序\n\
\n\
\n\
\n\
\n\
\n\
\t\t\t请输入选项（数字）：");
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
\t\t\t\t\t\t\t         登 录 账 号\n\
\t\t\t\t\t\t\t（账号/密码输入空跳回Welcome）\n\
\n\
\n\
\t\t\t\t\t\t\t账号：");
    Action_login();
}

void UI_login_ask_password(StringItem* accitem) {
    printf(
"\n\
\n\
\t\t\t\t\t\t\t密码：");
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
\t\t\t\t\t\t\t         注 册 账 号\n\
\t\t\t\t\t\t\t（账号/密码输入空跳回Welcome）\n\
\n\
\n\
\t\t\t\t\t\t\t账号：");
    Action_register();
}

void UI_register_ask_password(StringItem* accitem) {
    printf(
"\n\
\n\
\t\t\t\t\t\t\t密码：");
    Action_register_ask_password(accitem);
}

void UI_register_ask_type(StringItem* accitem, StringItem* passitem) {
    printf(
"\n\
\n\
\t\t\t\t\t\t\t类型：");
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
\t\t\t\t\t\t\t欢迎使用 『二手车销售管理系统』 ！\n\
\n\
\n\
\t\t\t\t\t\t\t             菜  单\n\
\n\
\t\t\t\t\t\t\t          1.登出账号\n\
\t\t\t\t\t\t\t          2.注册新账号\n\
\t\t\t\t\t\t\t          3.查看账号信息\n\
\t\t\t\t\t\t\t          4.删除账号\n\
\t\t\t\t\t\t\t          5.打开mdb数据库\n\
\t\t\t\t\t\t\t          6.txt数据导入（自动附加在当前mdb中保存）\n\
\t\t\t\t\t\t\t          7.mdb导出\n\
\t\t\t\t\t\t\t          8.输入单条新数据\n\
\t\t\t\t\t\t\t          9.删除数据\n\
\t\t\t\t\t\t\t          10.查看数据\n\
\t\t\t\t\t\t\t          11.修改数据\n\
\t\t\t\t\t\t\t          12.数据统计\n\
\t\t\t\t\t\t\t          13.关闭程序\n\
\n\
\n\
\t\t\t请输入选项（数字）：");
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
\t\t\t\t\t\t\t查看账户信息：\n\
\n\
\n\
\n");
    printf("\t\t\t\t账户类型（权限）：%s\n\n", CurUserData->userType == userType_dev ? "开发者" : (
        CurUserData->userType == userType_admin ? "管理员" : (
            CurUserData->userType == userType_manager ? "经理" : (
                CurUserData->userType == userType_employee ? "员工" : (
                    CurUserData->userType == userType_cust ? "客户" : "未知"
                    )
                ))));
    printf("\t\t\t\t账号：%s\n\n", CurUserData->account);
    printf("\t\t\t\t密码：%s\n\n", CurUserData->password);
    printf("\t\t\t\t输入任意内容返回：");
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
\t\t\t\t\t\t\t删除账号：(空则跳出)\n\
\n\
\n\
\n");
    printf("\t\t\t\t请输入待删除的账号：");
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
\t\t\t\t\t\t\t打开mdb数据库：\n\
\n\
\n\
\n");
    printf("\t\t\t\t请输入待打开的mdb文件路径：");
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
\t\t\t\t\t\t\ttxt数据导入（自动附加在当前mdb中保存）\n\
\n\
\n\
\n");
    printf("\t\t\t\t请输入导入路径（含.txt，空值放弃）：");
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
\t\t\t\t\t\t\t导出MDB数据库：(首次录入使用时请保存一次地址)\n\
\n\
\n\
\n");
    printf("\t\t\t\t请输入导出路径（含.mdb）：");
    Action_export_mdb(nodelink);
}
void UI_append_new_data() {
    UI_clearScreen();
    printf("输入单条新数据：\n");
    Action_append_new_data();
}
void UI_remove_data() {
    UI_clearScreen();
    printf(
"删除数据：（输空放弃执行，车辆编号是唯一独立的信息，请先查找到车辆编号再删除）\n\
输入待删除的车辆编号(carId)：");
    Action_remove_data();
}
void UI_peek_data() {
    UI_clearScreen();
    printf("\t\t\t\t\t\t\t查看：\n");
    Action_peek_data();
}
void UI_showpeek(peekToolPage* pages) {
    UI_clearScreen();
    Action_showpeek(pages, 1);
}
void UI_modify_data(ListNode* nodelink) {
    UI_clearScreen();
    printf("\t\t\t\t\t\t\t修改：\n");
    Action_modify_data(nodelink);
}
void UI_analysis_data(ListNode* nodelink) {
    UI_clearScreen();
    printf("\t\t\t\t\t\t\t统计：\n");
    Action_analysis_data(nodelink);
}