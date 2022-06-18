#include "mdb.h"
/**
 * @brief mdb
 * 这是底层数据存取实现，用于解析mdb文件，提供给database.c使用
 *
 */
 /**
  * mdb二进制数据库结构(虽然叫mdb，不是微软的mdb哦)
  * #####################################################
  * #  MDB_HEADER_TK            文件头(4)
  * #  sizeof(int)              size(1)
  * #  size                     size(4)
  * #  --------------------------------------------------
  * #  TK_START                 开始标记
  * #  TK_xxx1                  键值
  * #  size                     size(4)
  * #  xx1                      值
  * #  TK_xxx2                  键值
  * #  size                     size(4)
  * #  xx2                      值
  * #  ......
  * #  TK_END                   结束标记
  * #  --------------------------------------------------
  * #  TK_START                 开始标记
  * #  TK_xxx1                  键值
  * #  size                     size(4)
  * #  xx1                      值
  * #  TK_xxx2                  键值
  * #  size                     size(4)
  * #  xx2                      值
  * #  ......
  * #  TK_END                   结束标记
  * #  --------------------------------------------------
  * #  ......
  * #####################################################
  */
char MDB_HEADER_TK[] = { 'm','d','b','\n' };
char* get_MDB_HEADER_TK(){
    char* tk = (char*)malloc(sizeof(MDB_HEADER_TK));
    memcpy(tk, MDB_HEADER_TK, sizeof(MDB_HEADER_TK));
    return tk;
}
//生成空的carInfoItem结构体(怎么这么长啊……)
carInfoItem* gen_Empty_carInfoItem() {
    carInfoItem* item = (carInfoItem*)malloc(sizeof(carInfoItem));//车辆信息
    carBaseInfo* info = (carBaseInfo*)malloc(sizeof(carBaseInfo));//车辆基本信息
    item->info = info;
    info->carId = 0;
    StringItem* carBrand = (StringItem*)malloc(sizeof(StringItem));//车辆品牌
    carBrand->str = "";
    carBrand->size = 1;
    info->carBrand = carBrand;
    StringItem* carModel = (StringItem*)malloc(sizeof(StringItem));//车辆型号
    carModel->str = "";
    carModel->size = 1;
    info->carModel = carModel;
    info->carPrice = 0;
    info->carAge = 0;
    carFault* fault = (carFault*)malloc(sizeof(carFault));//车辆故障
    fault->hasRepair = 0;
    fault->hasFault = 0;
    StringItem* faultDescribe = (StringItem*)malloc(sizeof(StringItem));//故障描述
    faultDescribe->str = "";
    faultDescribe->size = 1;
    fault->faultDescribe = faultDescribe;
    info->fault = fault;
    orderInfo* order = (orderInfo*)malloc(sizeof(orderInfo));//订单信息
    item->order = order;
    order->status = carStatus_unknown;
    Date* date = (Date*)malloc(sizeof(Date));//日期
    date->year = 0;
    date->month = 0;
    date->day = 0;
    order->date = date;
    order->inPrice = 0;
    order->outPrice = 0;
    order->estimatePrice = 0;
    order->realPrice = 0;
    personInfo* seller = (personInfo*)malloc(sizeof(personInfo));//卖家信息
    seller->type = personType_seller;
    StringItem* sellerName = (StringItem*)malloc(sizeof(StringItem));//卖家姓名
    sellerName->str = "";
    sellerName->size = 1;
    seller->name = sellerName;
    StringItem* sellerPhone = (StringItem*)malloc(sizeof(StringItem));//卖家电话
    sellerPhone->str = "";
    sellerPhone->size = 1;
    seller->phone = sellerPhone;
    seller->id = 0;
    order->seller = seller;
    personInfo* buyer = (personInfo*)malloc(sizeof(personInfo));//买家信息
    buyer->type = personType_buyer;
    StringItem* buyerName = (StringItem*)malloc(sizeof(StringItem));//买家姓名
    buyerName->str = "";
    buyerName->size = 1;
    buyer->name = buyerName;
    StringItem* buyerPhone = (StringItem*)malloc(sizeof(StringItem));//买家电话
    buyerPhone->str = "";
    buyerPhone->size = 1;
    buyer->phone = buyerPhone;
    buyer->id = 0;
    order->buyer = buyer;
    personInfo* handler = (personInfo*)malloc(sizeof(personInfo));//经手人信息
    handler->type = personType_handler;
    StringItem* handlerName = (StringItem*)malloc(sizeof(StringItem));//经手人姓名
    handlerName->str = "";
    handlerName->size = 1;
    handler->name = handlerName;
    StringItem* handlePhone = (StringItem*)malloc(sizeof(StringItem));//经手人电话
    handlePhone->str = "";
    handlePhone->size = 1;
    handler->phone = handlePhone;
    handler->id = 0;
    order->handler = handler;
    personInfo* employee = (personInfo*)malloc(sizeof(personInfo));//员工信息
    employee->type = personType_employee;
    StringItem* employeeName = (StringItem*)malloc(sizeof(StringItem));//员工姓名
    employeeName->str = "";
    employeeName->size = 1;
    employee->name = employeeName;
    StringItem* employeePhone = (StringItem*)malloc(sizeof(StringItem));//员工电话
    employeePhone->str = "";
    employeePhone->size = 1;
    employee->phone = employeePhone;
    employee->id = 0;
    order->employee = employee;
    return item;
}
char* peekChars(char* buffer, int offset, int size) {
    char* str = (char*)malloc(size);
    memcpy(str, buffer + offset, size);
    return str;
}
int undumpCarInfoItem(carInfoItem* item, enum MDB_ITEM_TK type, char* content, int size, int MDB_PLATNFORM_INT_SIZE);
ListNode* readAllFromMdb(char* mdbpath) {
    if (mdbpath == NULL) {//默认路径
        mdbpath = MDB_DEFAULT_PATH;
    }
    Buffer* mdbbuffer = readFile(mdbpath, Boolean_FALSE);
    if (mdbbuffer->isFail) {//打开失败
        char* errmsg = malloc(sizeof(char) * 200 + strlen(mdbpath));
        memset(errmsg, 0, 200 + strlen(mdbpath));
        sprintf(errmsg, "mdb（%s）打开失败！", mdbpath);
        mkerrlog(errmsg);
        free(errmsg);
        return NULL;
    }
    if (mdbbuffer->size == 0) {//文件为空
        char* errmsg = malloc(sizeof(char) * 200 + strlen(mdbpath));
        memset(errmsg, 0, 200 + strlen(mdbpath));
        sprintf(errmsg, "mdb（%s）为空！", mdbpath);
        mkerrlog(errmsg);
        free(errmsg);
        return NULL;
    }

    char* buffer = mdbbuffer->buffer;
    int offset = 0;

    //判断文件头是否正确
    char* TMPBUF = peekChars(buffer, offset, 4);
    if (charcmp(TMPBUF, MDB_HEADER_TK, 4) != 0) {
        free(TMPBUF);
        char* errmsg = malloc(sizeof(char) * 200 + strlen(mdbpath));
        memset(errmsg, 0, 200 + strlen(mdbpath));
        sprintf(errmsg, "mdb（%s）文件头错误！请确定数据库正常！（该项目私有mdb结构不是微软的mdb）", mdbpath);
        mkerrlog(errmsg);
        free(errmsg);
        free(mdbbuffer);
        return NULL;
    }
    free(TMPBUF);
    offset += 4;

    //拿到该平台int的大小
    TMPBUF = peekChars(buffer, offset, 1);
    int MDB_PLATNFORM_INT_SIZE = *TMPBUF;
    MDB_PLATNFORM_INT_SIZE &= 0xFF;
    free(TMPBUF);
    offset += 1;

    //获取数据库大小
    TMPBUF = peekChars(buffer, offset, MDB_PLATNFORM_INT_SIZE);
    int sizelen = char2int(TMPBUF, MDB_PLATNFORM_INT_SIZE);
    offset += MDB_PLATNFORM_INT_SIZE;

    int realsize = 0;//实际读取的数据库大小（方便检查数据库是否被破坏）

    //获取数据库内容
    ListNode* head = NULL;
    ListNode* tail = NULL;
    while ((*(buffer + offset) & 0xff) == TK_START) {//遍历数据库
        int flagok = 0;
        realsize++;//实际读取量加1
        offset += 1;//因为刚才读取了TK_START
        carInfoItem* item = gen_Empty_carInfoItem();//生成一个空的车辆信息项
        while ((*(buffer + offset) & 0xff) != TK_END && offset < mdbbuffer->size) {//遍历记录
            //获取数据类型
            int type = (int)(*(buffer + offset) & 0xff);
            offset += 1;
            //获取数据大小
            TMPBUF = peekChars(buffer, offset, MDB_PLATNFORM_INT_SIZE);
            int size = char2int(TMPBUF, MDB_PLATNFORM_INT_SIZE);
            free(TMPBUF);
            offset += MDB_PLATNFORM_INT_SIZE;
            offset += size;
            int result = 0;
            result = undumpCarInfoItem(item, type, buffer + offset - size, size, MDB_PLATNFORM_INT_SIZE);
            if (result < 0) {
                // TODO: 是否是新增的类型？
                // return NULL;
            } else {
                flagok = 1;
            }
        }
        if (flagok == 0) {
            realsize--;
        } else {
            tail = addListNode(tail, item);
            if (head == NULL) {
                head = tail;
            }
        }
        offset += 1;//因为刚才读取了TK_END
    }
    //检查数据库是否被破坏
    if (realsize != sizelen) {
        char* errmsg = malloc(sizeof(char) * 200 + strlen(mdbpath));
        memset(errmsg, 0, 200 + strlen(mdbpath));
        sprintf(errmsg, "mdb（%s）文件被破坏！期待有 %d 个项目，却得到 %d 个项目！", mdbpath, sizelen, realsize);
        mkerrlog(errmsg);
        free(errmsg);
        free(mdbbuffer->buffer);
        free(mdbbuffer);
        return NULL;//其实可以返回已知部分的，这就为了报错处理，返回NULL提示
    }
    free(mdbbuffer->buffer);
    free(mdbbuffer);
    return head;
}

int undumpCarInfoItem(carInfoItem* item, enum MDB_ITEM_TK type, char* content, int size, int MDB_PLATNFORM_INT_SIZE) {
    if (type == TK_START || type == TK_END) {
        mkerrlog("在undumpCarInfoItem时不能读取TK_START或TK_END类型的数据！");
        return 0;
    }
    switch (type) {
        case TK_carId:
            {
                item->info->carId = char2int(content, MDB_PLATNFORM_INT_SIZE);
                break;
            }
        case TK_carBrand:
            {
                StringItem* stritem = item->info->carBrand;
                stritem->str = malloc(sizeof(char) * (size + 1));
                memset(stritem->str, 0, size + 1);
                memcpy(stritem->str, content, size);
                stritem->size = size + 1;
                break;
            }
        case TK_carModel:
            {
                StringItem* stritem = item->info->carModel;
                stritem->str = malloc(sizeof(char) * (size + 1));
                memset(stritem->str, 0, size + 1);
                memcpy(stritem->str, content, size);
                stritem->size = size + 1;
                item->info->carModel = stritem;
                break;
            }
        case TK_carPrice:
            {
                item->info->carPrice = char2int(content, MDB_PLATNFORM_INT_SIZE);
                break;
            }
        case TK_carAge:
            {
                item->info->carAge = char2int(content, MDB_PLATNFORM_INT_SIZE);
                break;
            }
        case TK_hasRepair:
            {
                item->info->fault->hasRepair = (*content) & 0xFF;
                break;
            }
        case TK_hasFault:
            {
                item->info->fault->hasFault = (*content) & 0xFF;
                break;
            }
        case TK_faultDescribe:
            {
                StringItem* stritem = item->info->fault->faultDescribe;
                stritem->str = malloc(sizeof(char) * (size + 1));
                memset(stritem->str, 0, size + 1);
                memcpy(stritem->str, content, size);
                stritem->size = size + 1;
                break;
            }
        case TK_status:
            {
                item->order->status = (*content) & 0xFF;
                break;
            }
        case TK_date:
            {
                Date* date = item->order->date;
                date->year = char2int(content, MDB_PLATNFORM_INT_SIZE);
                date->month = char2int(content + 4, MDB_PLATNFORM_INT_SIZE);
                date->day = char2int(content + 8, MDB_PLATNFORM_INT_SIZE);
                break;
            }
        case TK_inPrice:
            {
                item->order->inPrice = char2int(content, MDB_PLATNFORM_INT_SIZE);
                break;
            }
        case TK_outPrice:
            {
                item->order->outPrice = char2int(content, MDB_PLATNFORM_INT_SIZE);
                break;
            }
        case TK_estimatePrice:
            {
                item->order->estimatePrice = char2int(content, MDB_PLATNFORM_INT_SIZE);
                break;
            }
        case TK_realPrice:
            {
                item->order->realPrice = char2int(content, MDB_PLATNFORM_INT_SIZE);
                break;
            }
        case TK_person:
            {//人员信息
                int offset = MDB_PLATNFORM_INT_SIZE;//这个偏移量是固定的value=1
                personInfo* person = NULL;
                switch (*(content + MDB_PLATNFORM_INT_SIZE)) {//获取人员类型
                    case personType_seller:
                        {
                            person = item->order->seller;
                            break;
                        }
                    case personType_buyer:
                        {
                            person = item->order->buyer;
                            break;
                        }
                    case personType_handler:
                        {
                            person = item->order->handler;
                            break;
                        }
                    case personType_employee:
                        {
                            person = item->order->employee;
                            break;
                        }
                    default:
                        break;
                }
                if (person == NULL) {
                    char* errmsg = malloc(sizeof(char) * 200);
                    memset(errmsg, 0, sizeof(char) * 200);
                    sprintf(errmsg, "发现未知的人员类型：%d！", *content);
                    mkerrlog(errmsg);
                    free(errmsg);
                    return -1;
                }
                offset += 1;
                int sizeof_name = char2int(content + offset, MDB_PLATNFORM_INT_SIZE);
                offset += MDB_PLATNFORM_INT_SIZE;
                StringItem* name = person->name;
                free(name->str);
                char* bufname = malloc(sizeof(char) * (sizeof_name + 1));
                memcpy(bufname, content + offset, sizeof_name);
                bufname[sizeof_name] = '\0';
                setStringItem(name, bufname);
                offset += sizeof_name;
                int sizeof_phone = char2int(content + offset, MDB_PLATNFORM_INT_SIZE);
                offset += MDB_PLATNFORM_INT_SIZE;
                StringItem* phone = person->phone;
                free(phone->str);
                char* bufphone = malloc(sizeof(char) * (sizeof_phone + 1));
                memcpy(bufphone, content + offset, sizeof_phone);
                bufphone[sizeof_phone] = '\0';
                setStringItem(phone, bufphone);
                offset += sizeof_phone;
                offset += MDB_PLATNFORM_INT_SIZE;
                person->id = char2int(content + offset, MDB_PLATNFORM_INT_SIZE);
                break;
            }
        default:
            break;
    }
    return 0;
}

void fwriteint(FILE* fp, int i) {
    fwrite(&i, sizeof(int), 1, fp);
}

void fwriteinteger(FILE* fp, int i) {
    fwriteint(fp, sizeof(int));//size
    fwriteint(fp, i);
}

void fwriteStringItem(FILE* fp, StringItem* stritem) {
    if (stritem->size == 0) {//坑死我了
        fwriteint(fp, 0);
        return;
    }
    fwriteint(fp, stritem->size - 1);//size
    fwrite(stritem->str, sizeof(char), stritem->size - 1, fp);
}

void fwriteboolOrcharOrEnum(FILE* fp, char boolc) {
    fwriteint(fp, 1);//size
    fwrite(&boolc, sizeof(char), 1, fp);
}

void fwritedate(FILE* fp, Date* date) {
    fwriteint(fp, sizeof(int) * 3);//size
    fwriteint(fp, date->year);
    fwriteint(fp, date->month);
    fwriteint(fp, date->day);
}

void fwritepeopleInfo(FILE* fp, personInfo* person) {
    int size = 0;
    size += sizeof(int);//type size
    size += 1;//type
    size += sizeof(int);//name size
    if (person->name->size != 0) {
        size += person->name->size - 1;//name
    }
    size += sizeof(int);//phone size
    if (person->phone->size != 0) {
        size += person->phone->size - 1;//phone
    }
    size += sizeof(int);//id size
    size += sizeof(int);//id
    fwriteint(fp, size);//size
    fwriteboolOrcharOrEnum(fp, person->type);
    fwriteStringItem(fp, person->name);
    fwriteStringItem(fp, person->phone);
    fwriteinteger(fp, person->id);
}
void saveAsMdb(char* mdbpath, ListNode* nodelink) {
    if (mdbpath == NULL) {//默认路径
        mdbpath = MDB_DEFAULT_PATH;
    }
    rebindListNodeIndex(nodelink);//保证index是正确的
    ListNode* head = getHeadNode(nodelink);
    ListNode* tail = getTailNode(nodelink);
    ListNode* cur = head;
    int size = tail->index - head->index + 1;
    FILE* fp = fopen(mdbpath, "wb");
    if (fp == NULL) {
        char* errmsg = malloc(sizeof(char) * 200 + strlen(mdbpath));
        memset(errmsg, 0, 200 + strlen(mdbpath));
        sprintf(errmsg, "mdb（%s）写入失败！", mdbpath);
        mkerrlog(errmsg);
        free(errmsg);
        return;
    }
    //写入头部信息
    fwrite(MDB_HEADER_TK, sizeof(char), 4, fp);
    //sizeof(int)
    char MDB_PLATNFORM_INT_SIZE = sizeof(int) & 0xff;
    fwrite(&MDB_PLATNFORM_INT_SIZE, sizeof(char), 1, fp);
    //一共有多少个
    fwriteint(fp, size);
    while (cur != NULL) {
        carInfoItem* item = cur->value;
        int dumpTK = TK_START;
        fwrite(&dumpTK, sizeof(char), 1, fp);

        dumpTK = TK_carId;
        fwrite(&dumpTK, sizeof(char), 1, fp);
        fwriteinteger(fp, item->info->carId);

        dumpTK = TK_carBrand;
        fwrite(&dumpTK, sizeof(char), 1, fp);
        fwriteStringItem(fp, item->info->carBrand);

        dumpTK = TK_carModel;
        fwrite(&dumpTK, sizeof(char), 1, fp);
        fwriteStringItem(fp, item->info->carModel);

        dumpTK = TK_carPrice;
        fwrite(&dumpTK, sizeof(char), 1, fp);
        fwriteinteger(fp, item->info->carPrice);

        dumpTK = TK_carAge;
        fwrite(&dumpTK, sizeof(char), 1, fp);
        fwriteinteger(fp, item->info->carAge);

        dumpTK = TK_hasRepair;
        fwrite(&dumpTK, sizeof(char), 1, fp);
        fwriteboolOrcharOrEnum(fp, item->info->fault->hasRepair);

        dumpTK = TK_hasFault;
        fwrite(&dumpTK, sizeof(char), 1, fp);
        fwriteboolOrcharOrEnum(fp, item->info->fault->hasFault);

        dumpTK = TK_faultDescribe;
        fwrite(&dumpTK, sizeof(char), 1, fp);
        fwriteStringItem(fp, item->info->fault->faultDescribe);

        dumpTK = TK_status;
        fwrite(&dumpTK, sizeof(char), 1, fp);
        fwriteboolOrcharOrEnum(fp, item->order->status);

        dumpTK = TK_date;
        fwrite(&dumpTK, sizeof(char), 1, fp);
        fwritedate(fp, item->order->date);

        dumpTK = TK_inPrice;
        fwrite(&dumpTK, sizeof(char), 1, fp);
        fwriteinteger(fp, item->order->inPrice);

        dumpTK = TK_outPrice;
        fwrite(&dumpTK, sizeof(char), 1, fp);
        fwriteinteger(fp, item->order->outPrice);

        dumpTK = TK_estimatePrice;
        fwrite(&dumpTK, sizeof(char), 1, fp);
        fwriteinteger(fp, item->order->estimatePrice);

        dumpTK = TK_realPrice;
        fwrite(&dumpTK, sizeof(char), 1, fp);
        fwriteinteger(fp, item->order->realPrice);

        dumpTK = TK_person;
        fwrite(&dumpTK, sizeof(char), 1, fp);
        fwritepeopleInfo(fp, item->order->seller);

        dumpTK = TK_person;
        fwrite(&dumpTK, sizeof(char), 1, fp);
        fwritepeopleInfo(fp, item->order->buyer);

        dumpTK = TK_person;
        fwrite(&dumpTK, sizeof(char), 1, fp);
        fwritepeopleInfo(fp, item->order->handler);

        dumpTK = TK_person;
        fwrite(&dumpTK, sizeof(char), 1, fp);
        fwritepeopleInfo(fp, item->order->employee);

        dumpTK = TK_END;
        fwrite(&dumpTK, sizeof(char), 1, fp);

        cur = cur->next;
    }
    fclose(fp);
}

ListNode* readTxtData(char* txtpath) {
    if (txtpath == NULL) {
        txtpath = "database.txt";
    }
    Buffer* txtbuffer = readFile(txtpath, Boolean_TRUE);
    if (txtbuffer->isFail) {//打开失败
        char* errmsg = malloc(sizeof(char) * 200 + strlen(txtpath));
        memset(errmsg, 0, 200 + strlen(txtpath));
        sprintf(errmsg, "txt（%s）打开失败！", txtpath);
        mkerrlog(errmsg);
        free(errmsg);
        return NULL;
    }
    if (txtbuffer->size <= 1) {//文件为空
        char* errmsg = malloc(sizeof(char) * 200 + strlen(txtpath));
        memset(errmsg, 0, 200 + strlen(txtpath));
        sprintf(errmsg, "txt（%s）为空！", txtpath);
        mkerrlog(errmsg);
        free(errmsg);
        return NULL;
    }

    char* buffer = txtbuffer->buffer;
    int offset = 0;
    int lines = 0;
    for (;;) {
        if (buffer[offset] == '\n') {
            lines++;
        }
        offset++;
        if (offset >= txtbuffer->size) {
            lines++;
            break;
        }
    }
    offset = 0;
    //手动去读取行值
    char** linecontents = malloc(sizeof(char*) * lines);
    int i;
    for (i = 0; i < lines; i++) {
        char* l = malloc(sizeof(char) * 1024);
        int j = 0;
        for (;;) {
            if (buffer[offset] == '\n' || offset >= txtbuffer->size) {
                break;
            }
            l[j] = buffer[offset];
            offset++;
            j++;
        }
        l[j] = '\0';
        linecontents[i] = l;
        offset++;
    }
    /**
     * 结构
     * carId   carBrand carModel carPrice carAge hasRepair hasFault faultDescribe status date      inPrice outPrice estimatePrice realPrice sellername sellerphone buyername  buyerphone  handlername handlerphone employeename employeeid
     * 1000001 奥迪     ZQ70     809000    10    否         否       无故障        预定    2008/12/1 647200  776640   621312         -1       李霞       50561349942 张伟       67253388023 王敏         69165561218  刘伟         8450
     */
    ListNode* head = NULL;
    ListNode* cur = NULL;
    char* line = NULL;
    for (i = 0; i < lines; i++) {
        line = linecontents[i];
        if (line == NULL) {
            continue;
        }
        if (strlen(line) == 0) {
            continue;
        }
        carInfoItem* item = gen_Empty_carInfoItem();
        int carId = 0;
        char carBrand[50] = { 0 };
        char carModel[50] = { 0 };
        int carPrice = 0;
        int carAge = 0;
        char hasRepair[10] = { 0 };
        char hasFault[10] = { 0 };
        char faultDescribe[50] = { 0 };
        char status[20] = { 0 };
        int dateY = 0;
        int dateM = 0;
        int dateD = 0;
        int inPrice = 0;
        int outPrice = 0;
        int estimatePrice = 0;
        int realPrice = 0;
        char sellername[30] = { 0 };
        char sellerphone[30] = { 0 };
        char buyername[30] = { 0 };
        char buyerphone[30] = { 0 };
        char handlername[30] = { 0 };
        char handlerphone[30] = { 0 };
        char employeename[30] = { 0 };
        int employeeid = 0;
        //开摆，直接一口气读完
        sscanf(line, "%d%s%s%d%d\
        %s%s%s\
        %s\
        %d/%d/%d\
        %d%d%d%d\
        %s%s\
        %s%s\
        %s%s\
        %s%d",
            &carId, carBrand, carModel, &carPrice, &carAge,
            hasRepair, hasFault, faultDescribe,
            status,
            &dateY, &dateM, &dateD,
            &inPrice, &outPrice, &estimatePrice, &realPrice,
            sellername, sellerphone,
            buyername, buyerphone,
            handlername, handlerphone,
            employeename, &employeeid);
        item->info->carId = carId;
        setStringItem(item->info->carBrand, carBrand);
        setStringItem(item->info->carModel, carModel);
        item->info->carPrice = carPrice;
        item->info->carAge = carAge;
        if (strcmp(hasRepair, "是") == 0) {
            item->info->fault->hasRepair = Boolean_TRUE;
        } else {
            item->info->fault->hasRepair = Boolean_FALSE;
        }
        if (strcmp(hasFault, "是") == 0) {
            item->info->fault->hasFault = Boolean_TRUE;
        } else {
            item->info->fault->hasFault = Boolean_FALSE;
        }
        setStringItem(item->info->fault->faultDescribe, faultDescribe);
        if (strcmp(status, "入库") == 0) {
            item->order->status = carStatus_inStock;
        } else if (strcmp(status, "出库") == 0) {
            item->order->status = carStatus_outStock;
        } else if (strcmp(status, "预定") == 0) {
            item->order->status = carStatus_reserved;
        } else if (strcmp(status, "已售") == 0) {
            item->order->status = carStatus_sold;
        } else {
            item->order->status = carStatus_unknown;
        }
        item->order->date->year = dateY;
        item->order->date->month = dateM;
        item->order->date->day = dateD;
        item->order->inPrice = inPrice;
        item->order->outPrice = outPrice;
        item->order->estimatePrice = estimatePrice;
        item->order->realPrice = realPrice;
        setStringItem(item->order->seller->name, sellername);
        setStringItem(item->order->seller->phone, sellerphone);
        setStringItem(item->order->buyer->name, buyername);
        setStringItem(item->order->buyer->phone, buyerphone);
        setStringItem(item->order->handler->name, handlername);
        setStringItem(item->order->handler->phone, handlerphone);
        setStringItem(item->order->employee->name, employeename);
        item->order->employee->id = employeeid;
        cur = addListNode(cur, item);
        if (head == NULL) {
            head = cur;
        }
    }
    return head;
}
