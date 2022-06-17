//UIAction.h

#ifndef UIAction_h
#define UIAction_h
#include "common.h"
#include "utils.h"
#include "user.h"
#include "database.h"
#include "mdb.h"
#include "peekTool.h"

void Action_Welcome();
void Action_login();
void Action_login_ask_password(StringItem* accitem);
void Action_register();
void Action_register_ask_password(StringItem* accitem);
void Action_register_ask_type(StringItem* accitem, StringItem* passitem);
void Action_MainMenu();
void Action_peek_userinfo();
void Action_openMDB();
void Action_txt_import(ListNode* nodelink);
void Action_export_mdb(ListNode* nodelink);
void Action_append_new_data();
void Action_remove_data();
void Action_peek_data();
void Action_showpeek(peekToolPage* pages, int curpage);
void Action_modify_data(ListNode* nodelink);
void Action_delete_user(user_data* lCurUserData, user_data** lCurUserDatas, int* lCurUserDatasSize);
void Action_analysis_data(ListNode* nodelink);


#include "windows.h"
#include "Windows.h"
#include <process.h>
#include "UIPrint.h"
#include "analyzer.h"

#endif