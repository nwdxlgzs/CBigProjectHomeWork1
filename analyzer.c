#include "analyzer.h"
/*
数据分析
*/
//释放函数
void freeAnalyzerResult(Analyzer_Result* result) {
    freeStringItem(result->carBrandAnalyze);
    freeStringItem(result->carModelAnalyze);
    freeStringItem(result->carPriceAnalyze);
    freeStringItem(result->carAgeAnalyze);
    freeStringItem(result->carFaultAnalyze);
    freeStringItem(result->statusAnalyze);
    freeStringItem(result->dateAnalyze);
    freeStringItem(result->inPriceAnalyze);
    freeStringItem(result->outPriceAnalyze);
    freeStringItem(result->estimatePriceAnalyze);
    freeStringItem(result->realPriceAnalyze);
    freeStringItem(result->sellerAnalyze);
    freeStringItem(result->buyerAnalyze);
    freeStringItem(result->handlerAnalyze);
    freeStringItem(result->employeeAnalyze);
    freeStringItem(result->totalAnalyze);
    free(result);
}
//分析函数
Analyzer_Result* getAnalyzerResult(ListNode* nodelink) {
    //分配内存
    Analyzer_Result* result = (Analyzer_Result*)malloc(sizeof(Analyzer_Result));
    StringItem* carBrandAnalyze = (StringItem*)malloc(sizeof(StringItem));
    StringItem* carModelAnalyze = (StringItem*)malloc(sizeof(StringItem));
    StringItem* carPriceAnalyze = (StringItem*)malloc(sizeof(StringItem));
    StringItem* carAgeAnalyze = (StringItem*)malloc(sizeof(StringItem));
    StringItem* carFaultAnalyze = (StringItem*)malloc(sizeof(StringItem));
    StringItem* statusAnalyze = (StringItem*)malloc(sizeof(StringItem));
    StringItem* dateAnalyze = (StringItem*)malloc(sizeof(StringItem));
    StringItem* inPriceAnalyze = (StringItem*)malloc(sizeof(StringItem));
    StringItem* outPriceAnalyze = (StringItem*)malloc(sizeof(StringItem));
    StringItem* estimatePriceAnalyze = (StringItem*)malloc(sizeof(StringItem));
    StringItem* realPriceAnalyze = (StringItem*)malloc(sizeof(StringItem));
    StringItem* sellerAnalyze = (StringItem*)malloc(sizeof(StringItem));
    StringItem* buyerAnalyze = (StringItem*)malloc(sizeof(StringItem));
    StringItem* handlerAnalyze = (StringItem*)malloc(sizeof(StringItem));
    StringItem* employeeAnalyze = (StringItem*)malloc(sizeof(StringItem));
    StringItem* totalAnalyze = (StringItem*)malloc(sizeof(StringItem));
    result->carBrandAnalyze = carBrandAnalyze;
    result->carModelAnalyze = carModelAnalyze;
    result->carPriceAnalyze = carPriceAnalyze;
    result->carAgeAnalyze = carAgeAnalyze;
    result->carFaultAnalyze = carFaultAnalyze;
    result->statusAnalyze = statusAnalyze;
    result->dateAnalyze = dateAnalyze;
    result->inPriceAnalyze = inPriceAnalyze;
    result->outPriceAnalyze = outPriceAnalyze;
    result->estimatePriceAnalyze = estimatePriceAnalyze;
    result->realPriceAnalyze = realPriceAnalyze;
    result->sellerAnalyze = sellerAnalyze;
    result->buyerAnalyze = buyerAnalyze;
    result->handlerAnalyze = handlerAnalyze;
    result->employeeAnalyze = employeeAnalyze;
    result->totalAnalyze = totalAnalyze;
    //分析数据
    ListNode* head = getHeadNode(nodelink);
    ListNode* tail = getTailNode(nodelink);
    int len = tail->index - head->index + 1;//拿到长度
    //carBrandAnalyze:最多的Brand
    {
        char* string = malloc(sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        memset(string, 0, sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        ListNode* cur = head;
        int* count_int = malloc(sizeof(int) * len);
        memset(count_int, 0, sizeof(int) * len);
        char** count_string = malloc(sizeof(char*) * len);
        memset(count_string, 0, sizeof(char*) * len);
        int seek = 0;
        while (cur != NULL) {
            if (seek == 0) {//初始化
                count_int[seek] = 1;
                count_string[seek] = cur->value->info->carBrand->str;
                seek++;
            } else {//凡是找到相同的，count加1
                int i = 0;
                for (i = 0; i < seek; i++) {
                    if (strcmp(cur->value->info->carBrand->str, count_string[i]) == 0) {
                        count_int[i]++;
                        break;
                    }
                }
                if (i == seek) {
                    count_int[seek] = 1;
                    count_string[seek] = cur->value->info->carBrand->str;
                    seek++;
                }
            }
            cur = cur->next;
        }
        int i;
        int max = 0;
        char* max_string = NULL;
        for (i = 0; i < seek; i++) {
            if (count_int[i] > max) {
                max = count_int[i];
                max_string = count_string[i];
            }
        }
        sprintf(string, "在整个数据库中，品牌“%s”数量最多(第一个最多)，一共%d个。\n", max_string, max);
        result->carBrandAnalyze->str = string;
        result->carBrandAnalyze->size = strlen(string) + 1;
        free(count_int);
        free(count_string);
    }
    //carModelAnalyze:最多的Model
    {
        char* string = malloc(sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        memset(string, 0, sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        ListNode* cur = head;
        int* count_int = malloc(sizeof(int) * len);
        memset(count_int, 0, sizeof(int) * len);
        char** count_string = malloc(sizeof(char*) * len);
        memset(count_string, 0, sizeof(char*) * len);
        int seek = 0;
        while (cur != NULL) {
            if (seek == 0) {//初始化
                count_int[seek] = 1;
                count_string[seek] = cur->value->info->carModel->str;
                seek++;
            } else {//凡是找到相同的，count加1
                int i = 0;
                for (i = 0; i < seek; i++) {
                    if (strcmp(cur->value->info->carModel->str, count_string[i]) == 0) {
                        count_int[i]++;
                        break;
                    }
                }
                if (i == seek) {
                    count_int[seek] = 1;
                    count_string[seek] = cur->value->info->carModel->str;
                    seek++;
                }
            }
            cur = cur->next;
        }
        int i;
        int max = 0;
        char* max_string = NULL;
        for (i = 0; i < seek; i++) {
            if (count_int[i] > max) {
                max = count_int[i];
                max_string = count_string[i];
            }
        }
        sprintf(string, "在整个数据库中，型号“%s”数量最多(第一个最多)，一共%d个。\n", max_string, max);
        result->carModelAnalyze->str = string;
        result->carModelAnalyze->size = strlen(string) + 1;
        free(count_int);
        free(count_string);
    }
    //carPriceAnalyze:价格区间分析（/10000分级）
    {
        char* string = malloc(sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        memset(string, 0, sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        ListNode* cur = head;
        int count_int[10000] = { 0 };
        while (cur != NULL) {
            count_int[cur->value->info->carPrice / 10000]++;
            cur = cur->next;
        }
        int i;
        int maxIndex = 0;
        int max = 0;
        for (i = 0; i < 10000; i++) {
            if (count_int[i] > max) {
                max = count_int[i];
                maxIndex = i;
            }
        }
        sprintf(string, "在整个数据库中，价格区间为[%d,%d]的车辆数量最多(第一个最多)，一共%d个。\n", maxIndex * 10000, (maxIndex + 1) * 10000, max);
        result->carPriceAnalyze->str = string;
        result->carPriceAnalyze->size = strlen(string) + 1;
    }
    //carAgeAnalyze:年龄区间分析
    {
        char* string = malloc(sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        memset(string, 0, sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        ListNode* cur = head;
        int count_int[100] = { 0 };
        while (cur != NULL) {
            count_int[cur->value->info->carAge]++;
            cur = cur->next;
        }
        int i;
        int maxIndex = 0;
        int max = 0;
        int minIndex = 0;
        int min = 0;
        for (i = 0; i < 100; i++) {
            if (count_int[i] > max) {
                max = count_int[i];
                maxIndex = i;
            }
            if (count_int[i] < min) {
                min = count_int[i];
                minIndex = i;
            }
        }
        sprintf(string, "在整个数据库中，车龄为%d年的车辆数量最多(第一个最多)，一共%d个。\n", maxIndex, max);
        sprintf(string + strlen(string), "在整个数据库中，车龄为%d年的车辆数量最少(第一个最少)，一共%d个。\n", minIndex, min);
        result->carAgeAnalyze->str = string;
        result->carAgeAnalyze->size = strlen(string) + 1;
    }
    //carFaultAnalyze:故障率分析
    {
        char* string = malloc(sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        memset(string, 0, sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        ListNode* cur = head;
        int countFault = 0;
        int countRepair = 0;
        while (cur != NULL) {
            if (cur->value->info->fault->hasRepair != Boolean_FALSE) {
                countRepair++;
            }
            if (cur->value->info->fault->hasFault != Boolean_FALSE) {
                countFault++;
            }
            cur = cur->next;
        }
        sprintf(string, "在整个数据库中，车辆的大修率为%d%%，故障率为%d%%。\n", (countRepair * 100) / len, (countFault * 100) / len);
        result->carFaultAnalyze->str = string;
        result->carFaultAnalyze->size = strlen(string) + 1;
    }
    //statusAnalyze:车辆状态分析
    {
        char* string = malloc(sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        memset(string, 0, sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        ListNode* cur = head;
        int count_int[5] = { 0 };
        while (cur != NULL) {
            count_int[cur->value->order->status]++;
            cur = cur->next;
        }
        sprintf(string, "在整个数据库中，未知的有%d个，在库的有%d个，出库的有%d个，预定的有%d个，已售的有%d个。\n",
        count_int[carStatus_unknown], count_int[carStatus_inStock], count_int[carStatus_outStock], count_int[carStatus_reserved], count_int[carStatus_sold]);
        result->statusAnalyze->str = string;
        result->statusAnalyze->size = strlen(string) + 1;
    }
    //dateAnalyze:日期分析
    {
        char* string = malloc(sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        memset(string, 0, sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        ListNode* cur = head;
        int* Tint = (int*)malloc(sizeof(int) * len);
        int* TintK = (int*)malloc(sizeof(int) * len);
        memset(TintK, 0, sizeof(int) * len);
        int* TintV = (int*)malloc(sizeof(int) * len);
        memset(TintV, 0, sizeof(int) * len);
        int i = 0;
        while (cur != NULL) {
            int year = cur->value->order->date->year;
            int month = cur->value->order->date->month;
            int time = year * 10000 + month * 100;
            Tint[i++] = time;
            cur = cur->next;
        }
        int seek = 0;
        int j;
        for (i = 0;i < len;i++) {
            int find = 0;
            for (j = 0;j < seek;j++) {
                if (Tint[i] == TintK[j]) {
                    TintV[j]++;
                    find = 1;
                    break;
                }
            }
            if (find == 0) {
                TintK[seek] = Tint[i];
                TintV[seek] = 1;
                seek++;
            }
        }
        int maxIndex = 0;
        int max = 0;
        for (i = 0;i < seek;i++) {
            if (TintV[i] > max) {
                max = TintV[i];
                maxIndex = i;
            }
        }
        sprintf(string, "在整个数据库中，数据最多（第一个最多）的月份是%d年%d月，一共有%d个。\n", TintK[maxIndex] / 10000, (TintK[maxIndex] % 10000) / 100, max);
        result->dateAnalyze->str = string;
        result->dateAnalyze->size = strlen(string) + 1;
        free(Tint);
        free(TintK);
        free(TintV);
    }
    //inPriceAnalyze:进价分析（/10000分级）
    {
        char* string = malloc(sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        memset(string, 0, sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        ListNode* cur = head;
        int count_int[10000] = { 0 };
        while (cur != NULL) {
            count_int[cur->value->order->inPrice / 10000]++;
            cur = cur->next;
        }
        int i;
        int maxIndex = 0;
        int max = 0;
        for (i = 0; i < 10000; i++) {
            if (count_int[i] > max) {
                max = count_int[i];
                maxIndex = i;
            }
        }
        sprintf(string, "在整个数据库中，进价区间为[%d,%d]的车辆数量最多(第一个最多)，一共%d个。\n", maxIndex * 10000, (maxIndex + 1) * 10000, max);
        result->inPriceAnalyze->str = string;
        result->inPriceAnalyze->size = strlen(string) + 1;
    }
    //outPriceAnalyze:销售价分析（/10000分级）
    {
        char* string = malloc(sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        memset(string, 0, sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        ListNode* cur = head;
        int count_int[10000] = { 0 };
        while (cur != NULL) {
            count_int[cur->value->order->outPrice / 10000]++;
            cur = cur->next;
        }
        int i;
        int maxIndex = 0;
        int max = 0;
        for (i = 0; i < 10000; i++) {
            if (count_int[i] > max) {
                max = count_int[i];
                maxIndex = i;
            }
        }
        sprintf(string, "在整个数据库中，销售价区间为[%d,%d]的车辆数量最多(第一个最多)，一共%d个。\n", maxIndex * 10000, (maxIndex + 1) * 10000, max);
        result->outPriceAnalyze->str = string;
        result->outPriceAnalyze->size = strlen(string) + 1;
    }
    //estimatePriceAnalyze:估计价分析（/10000分级）
    {
        char* string = malloc(sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        memset(string, 0, sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        ListNode* cur = head;
        int count_int[10000] = { 0 };
        while (cur != NULL) {
            count_int[cur->value->order->estimatePrice / 10000]++;
            cur = cur->next;
        }
        int i;
        int maxIndex = 0;
        int max = 0;
        for (i = 0; i < 10000; i++) {
            if (count_int[i] > max) {
                max = count_int[i];
                maxIndex = i;
            }
        }
        sprintf(string, "在整个数据库中，估计价区间为[%d,%d]的车辆数量最多(第一个最多)，一共%d个。\n", maxIndex * 10000, (maxIndex + 1) * 10000, max);
        result->estimatePriceAnalyze->str = string;
        result->estimatePriceAnalyze->size = strlen(string) + 1;
    }
    //realPriceAnalyze:实售价分析（/10000分级）
    {
        char* string = malloc(sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        memset(string, 0, sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        ListNode* cur = head;
        int count_int[10000] = { 0 };
        while (cur != NULL) {
            //未售是-1
            if (cur->value->order->realPrice != -1) {
                count_int[cur->value->order->realPrice / 10000]++;
            }
            cur = cur->next;
        }
        int i;
        int maxIndex = 0;
        int max = 0;
        for (i = 0; i < 10000; i++) {
            if (count_int[i] > max) {
                max = count_int[i];
                maxIndex = i;
            }
        }
        sprintf(string, "在整个数据库中，实售价区间为[%d,%d]的车辆数量最多(第一个最多)，一共%d个。\n", maxIndex * 10000, (maxIndex + 1) * 10000, max);
        result->realPriceAnalyze->str = string;
        result->realPriceAnalyze->size = strlen(string) + 1;
    }
    //sellerAnalyze:卖家分析
    {
        char* string = malloc(sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        memset(string, 0, sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        ListNode* cur = head;
        int* count_int = malloc(sizeof(int) * len);
        memset(count_int, 0, sizeof(int) * len);
        char** count_string = malloc(sizeof(char*) * len);
        memset(count_string, 0, sizeof(char*) * len);
        int seek = 0;
        while (cur != NULL) {
            if (seek == 0) {//初始化
                count_int[seek] = 1;
                count_string[seek] = cur->value->order->seller->name->str;
                seek++;
            } else {//凡是找到相同的，count加1
                int i = 0;
                for (i = 0; i < seek; i++) {
                    if (strcmp(cur->value->order->seller->name->str, count_string[i]) == 0) {
                        count_int[i]++;
                        break;
                    }
                }
                if (i == seek) {
                    count_int[seek] = 1;
                    count_string[seek] = cur->value->order->seller->name->str;
                    seek++;
                }
            }
            cur = cur->next;
        }
        int i;
        int max = 0;
        char* max_string = NULL;
        for (i = 0; i < seek; i++) {
            if (count_int[i] > max) {
                max = count_int[i];
                max_string = count_string[i];
            }
        }
        sprintf(string, "在整个数据库中，卖家（含同名）“%s”数量最多(第一个最多)，一共%d个。\n", max_string, max);
        result->sellerAnalyze->str = string;
        result->sellerAnalyze->size = strlen(string) + 1;
        free(count_int);
        free(count_string);
    }
    //buyerAnalyze:买家分析
    {
        char* string = malloc(sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        memset(string, 0, sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        ListNode* cur = head;
        int* count_int = malloc(sizeof(int) * len);
        memset(count_int, 0, sizeof(int) * len);
        char** count_string = malloc(sizeof(char*) * len);
        memset(count_string, 0, sizeof(char*) * len);
        int seek = 0;
        while (cur != NULL) {
            if (seek == 0) {//初始化
                count_int[seek] = 1;
                count_string[seek] = cur->value->order->buyer->name->str;
                seek++;
            } else {//凡是找到相同的，count加1
                int i = 0;
                for (i = 0; i < seek; i++) {
                    if (strcmp(cur->value->order->buyer->name->str, count_string[i]) == 0) {
                        count_int[i]++;
                        break;
                    }
                }
                if (i == seek) {
                    count_int[seek] = 1;
                    count_string[seek] = cur->value->order->buyer->name->str;
                    seek++;
                }
            }
            cur = cur->next;
        }
        int i;
        int max = 0;
        char* max_string = NULL;
        for (i = 0; i < seek; i++) {
            if (count_int[i] > max) {
                max = count_int[i];
                max_string = count_string[i];
            }
        }
        sprintf(string, "在整个数据库中，买家（含同名）“%s”数量最多(第一个最多)，一共%d个。\n", max_string, max);
        result->buyerAnalyze->str = string;
        result->buyerAnalyze->size = strlen(string) + 1;
        free(count_int);
        free(count_string);
    }
    //handlerAnalyze:经手人分析
    {
        char* string = malloc(sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        memset(string, 0, sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        ListNode* cur = head;
        int* count_int = malloc(sizeof(int) * len);
        memset(count_int, 0, sizeof(int) * len);
        char** count_string = malloc(sizeof(char*) * len);
        memset(count_string, 0, sizeof(char*) * len);
        int seek = 0;
        while (cur != NULL) {
            if (seek == 0) {//初始化
                count_int[seek] = 1;
                count_string[seek] = cur->value->order->handler->name->str;
                seek++;
            } else {//凡是找到相同的，count加1
                int i = 0;
                for (i = 0; i < seek; i++) {
                    if (strcmp(cur->value->order->handler->name->str, count_string[i]) == 0) {
                        count_int[i]++;
                        break;
                    }
                }
                if (i == seek) {
                    count_int[seek] = 1;
                    count_string[seek] = cur->value->order->handler->name->str;
                    seek++;
                }
            }
            cur = cur->next;
        }
        int i;
        int max = 0;
        char* max_string = NULL;
        for (i = 0; i < seek; i++) {
            if (count_int[i] > max) {
                max = count_int[i];
                max_string = count_string[i];
            }
        }
        sprintf(string, "在整个数据库中，经手人（含同名）“%s”数量最多(第一个最多)，一共%d个。\n", max_string, max);
        result->handlerAnalyze->str = string;
        result->handlerAnalyze->size = strlen(string) + 1;
        free(count_int);
        free(count_string);
    }
    //employeeAnalyze:员工分析
    {
        char* string = malloc(sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        memset(string, 0, sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        ListNode* cur = head;
        int* count_int = malloc(sizeof(int) * len);
        memset(count_int, 0, sizeof(int) * len);
        int* ids = malloc(sizeof(int) * len);
        memset(ids, 0, sizeof(int) * len);
        char** count_string = malloc(sizeof(char*) * len);
        memset(count_string, 0, sizeof(char*) * len);
        int seek = 0;
        while (cur != NULL) {
            if (seek == 0) {//初始化
                count_int[seek] = 1;
                ids[seek] = cur->value->order->employee->id;
                seek++;
            } else {//凡是找到相同的，count加1
                int i = 0;
                for (i = 0; i < seek; i++) {
                    if (cur->value->order->employee->id == ids[i]) {
                        count_int[i]++;
                        count_string[i] = cur->value->order->employee->name->str;
                        break;
                    }
                }
                if (i == seek) {
                    count_int[seek] = 1;
                    ids[seek] = cur->value->order->employee->id;
                    count_string[seek] = cur->value->order->employee->name->str;
                    seek++;
                }
            }
            cur = cur->next;
        }
        int i;
        int max = 0;
        int max_id = 0;
        char* max_string = NULL;
        for (i = 0; i < seek; i++) {
            if (count_int[i] > max) {
                max = count_int[i];
                max_id = ids[i];
                max_string = count_string[i];
            }
        }
        sprintf(string, "在整个数据库中，员工“%s”（工号：%d）处理数量最多(第一个最多)，一共%d个。\n", max_string, max_id, max);
        result->employeeAnalyze->str = string;
        result->employeeAnalyze->size = strlen(string) + 1;
        free(count_int);
        free(ids);
        free(count_string);
    }
    //totalAnalyze:整体分析
    {
        char* string = malloc(sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        memset(string, 0, sizeof(char) * ANALYZER_RESULT_LINE_MALLOC_SIZE);
        int count = 0;
        int in_sum = 0;
        int totalin_sum = 0;
        int real_sum = 0;
        ListNode* cur = head;
        while (cur != NULL) {
            totalin_sum += cur->value->order->inPrice;
            if (cur->value->order->realPrice == -1) {
                cur = cur->next;
                continue;
            }
            count++;
            in_sum += cur->value->order->inPrice;
            real_sum += cur->value->order->realPrice;
            cur = cur->next;
        }
        sprintf(string, "在整个数据库中，一共有%d个订单，一共卖出%d个，按卖出的计算平均每个赚%d元，按所有单计算平均每个赚%d元。\n", len, count, (real_sum - in_sum) / count, (real_sum - totalin_sum) / len);
        result->totalAnalyze->str = string;
        result->totalAnalyze->size = strlen(string) + 1;
    }
    //返回
    return result;
}