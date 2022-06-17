//UIPrint.h

#ifndef UIPRINT_H
#define UIPRINT_H
#include "common.h"
#include "utils.h"
#include "user.h"
#include "database.h"
#include "peekTool.h"

void UI_clearScreen();
void UI_Welcome();
void UI_login();
void UI_login_ask_password(StringItem* accitem);
void UI_register();
void UI_register_ask_password(StringItem* accitem);
void UI_register_ask_type(StringItem* accitem, StringItem* passitem);
void UI_MainMenu();
void UI_peek_userinfo(user_data* CurUserData);
void UI_delete_user(user_data* CurUserData, user_data** CurUserDatas, int* size);
void UI_openMDB();
void UI_txt_import(ListNode* nodelink);
void UI_export_mdb(ListNode* nodelink);
void UI_append_new_data();
void UI_remove_data();
void UI_peek_data();
void UI_showpeek(peekToolPage* pages);
void UI_modify_data(ListNode* nodelink);
void UI_analysis_data(ListNode* nodelink);


#include "UIAction.h"
#endif