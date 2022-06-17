#include "mdb.h"
/**
 * @brief mdb
 * ���ǵײ����ݴ�ȡʵ�֣����ڽ���mdb�ļ����ṩ��database.cʹ��
 *
 */
 /**
  * mdb���������ݿ�ṹ(��Ȼ��mdb������΢���mdbŶ)
  * #####################################################
  * #  MDB_HEADER_TK            �ļ�ͷ(4)
  * #  sizeof(int)              size(1)
  * #  size                     size(4)
  * #  --------------------------------------------------
  * #  TK_START                 ��ʼ���
  * #  TK_xxx1                  ��ֵ
  * #  size                     size(4)
  * #  xx1                      ֵ
  * #  TK_xxx2                  ��ֵ
  * #  size                     size(4)
  * #  xx2                      ֵ
  * #  ......
  * #  TK_END                   �������
  * #  --------------------------------------------------
  * #  TK_START                 ��ʼ���
  * #  TK_xxx1                  ��ֵ
  * #  size                     size(4)
  * #  xx1                      ֵ
  * #  TK_xxx2                  ��ֵ
  * #  size                     size(4)
  * #  xx2                      ֵ
  * #  ......
  * #  TK_END                   �������
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
//���ɿյ�carInfoItem�ṹ��(��ô��ô��������)
carInfoItem* gen_Empty_carInfoItem() {
    carInfoItem* item = (carInfoItem*)malloc(sizeof(carInfoItem));//������Ϣ
    carBaseInfo* info = (carBaseInfo*)malloc(sizeof(carBaseInfo));//����������Ϣ
    item->info = info;
    info->carId = 0;
    StringItem* carBrand = (StringItem*)malloc(sizeof(StringItem));//����Ʒ��
    carBrand->str = "";
    carBrand->size = 1;
    info->carBrand = carBrand;
    StringItem* carModel = (StringItem*)malloc(sizeof(StringItem));//�����ͺ�
    carModel->str = "";
    carModel->size = 1;
    info->carModel = carModel;
    info->carPrice = 0;
    info->carAge = 0;
    carFault* fault = (carFault*)malloc(sizeof(carFault));//��������
    fault->hasRepair = 0;
    fault->hasFault = 0;
    StringItem* faultDescribe = (StringItem*)malloc(sizeof(StringItem));//��������
    faultDescribe->str = "";
    faultDescribe->size = 1;
    fault->faultDescribe = faultDescribe;
    info->fault = fault;
    orderInfo* order = (orderInfo*)malloc(sizeof(orderInfo));//������Ϣ
    item->order = order;
    order->status = carStatus_unknown;
    Date* date = (Date*)malloc(sizeof(Date));//����
    date->year = 0;
    date->month = 0;
    date->day = 0;
    order->date = date;
    order->inPrice = 0;
    order->outPrice = 0;
    order->estimatePrice = 0;
    order->realPrice = 0;
    personInfo* seller = (personInfo*)malloc(sizeof(personInfo));//������Ϣ
    seller->type = personType_seller;
    StringItem* sellerName = (StringItem*)malloc(sizeof(StringItem));//��������
    sellerName->str = "";
    sellerName->size = 1;
    seller->name = sellerName;
    StringItem* sellerPhone = (StringItem*)malloc(sizeof(StringItem));//���ҵ绰
    sellerPhone->str = "";
    sellerPhone->size = 1;
    seller->phone = sellerPhone;
    seller->id = 0;
    order->seller = seller;
    personInfo* buyer = (personInfo*)malloc(sizeof(personInfo));//�����Ϣ
    buyer->type = personType_buyer;
    StringItem* buyerName = (StringItem*)malloc(sizeof(StringItem));//�������
    buyerName->str = "";
    buyerName->size = 1;
    buyer->name = buyerName;
    StringItem* buyerPhone = (StringItem*)malloc(sizeof(StringItem));//��ҵ绰
    buyerPhone->str = "";
    buyerPhone->size = 1;
    buyer->phone = buyerPhone;
    buyer->id = 0;
    order->buyer = buyer;
    personInfo* handler = (personInfo*)malloc(sizeof(personInfo));//��������Ϣ
    handler->type = personType_handler;
    StringItem* handlerName = (StringItem*)malloc(sizeof(StringItem));//����������
    handlerName->str = "";
    handlerName->size = 1;
    handler->name = handlerName;
    StringItem* handlePhone = (StringItem*)malloc(sizeof(StringItem));//�����˵绰
    handlePhone->str = "";
    handlePhone->size = 1;
    handler->phone = handlePhone;
    handler->id = 0;
    order->handler = handler;
    personInfo* employee = (personInfo*)malloc(sizeof(personInfo));//Ա����Ϣ
    employee->type = personType_employee;
    StringItem* employeeName = (StringItem*)malloc(sizeof(StringItem));//Ա������
    employeeName->str = "";
    employeeName->size = 1;
    employee->name = employeeName;
    StringItem* employeePhone = (StringItem*)malloc(sizeof(StringItem));//Ա���绰
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
    if (mdbpath == NULL) {//Ĭ��·��
        mdbpath = MDB_DEFAULT_PATH;
    }
    Buffer* mdbbuffer = readFile(mdbpath, Boolean_FALSE);
    if (mdbbuffer->isFail) {//��ʧ��
        char* errmsg = malloc(sizeof(char) * 200 + strlen(mdbpath));
        memset(errmsg, 0, 200 + strlen(mdbpath));
        sprintf(errmsg, "mdb��%s����ʧ�ܣ�", mdbpath);
        mkerrlog(errmsg);
        free(errmsg);
        return NULL;
    }
    if (mdbbuffer->size == 0) {//�ļ�Ϊ��
        char* errmsg = malloc(sizeof(char) * 200 + strlen(mdbpath));
        memset(errmsg, 0, 200 + strlen(mdbpath));
        sprintf(errmsg, "mdb��%s��Ϊ�գ�", mdbpath);
        mkerrlog(errmsg);
        free(errmsg);
        return NULL;
    }

    char* buffer = mdbbuffer->buffer;
    int offset = 0;

    //�ж��ļ�ͷ�Ƿ���ȷ
    char* TMPBUF = peekChars(buffer, offset, 4);
    if (charcmp(TMPBUF, MDB_HEADER_TK, 4) != 0) {
        free(TMPBUF);
        char* errmsg = malloc(sizeof(char) * 200 + strlen(mdbpath));
        memset(errmsg, 0, 200 + strlen(mdbpath));
        sprintf(errmsg, "mdb��%s���ļ�ͷ������ȷ�����ݿ�������������Ŀ˽��mdb�ṹ����΢���mdb��", mdbpath);
        mkerrlog(errmsg);
        free(errmsg);
        free(mdbbuffer);
        return NULL;
    }
    free(TMPBUF);
    offset += 4;

    //�õ���ƽ̨int�Ĵ�С
    TMPBUF = peekChars(buffer, offset, 1);
    int MDB_PLATNFORM_INT_SIZE = *TMPBUF;
    MDB_PLATNFORM_INT_SIZE &= 0xFF;
    free(TMPBUF);
    offset += 1;

    //��ȡ���ݿ��С
    TMPBUF = peekChars(buffer, offset, MDB_PLATNFORM_INT_SIZE);
    int sizelen = char2int(TMPBUF, MDB_PLATNFORM_INT_SIZE);
    offset += MDB_PLATNFORM_INT_SIZE;

    int realsize = 0;//ʵ�ʶ�ȡ�����ݿ��С�����������ݿ��Ƿ��ƻ���

    //��ȡ���ݿ�����
    ListNode* head = NULL;
    ListNode* tail = NULL;
    while ((*(buffer + offset) & 0xff) == TK_START) {//�������ݿ�
        realsize++;//ʵ�ʶ�ȡ����1
        offset += 1;//��Ϊ�ղŶ�ȡ��TK_START
        carInfoItem* item = gen_Empty_carInfoItem();//����һ���յĳ�����Ϣ��
        tail = addListNode(tail, item);
        if (head == NULL) {
            head = tail;
        }
        while ((*(buffer + offset) & 0xff) != TK_END) {//������¼
            //��ȡ��������
            int type = (int)(*(buffer + offset) & 0xff);
            offset += 1;
            //��ȡ���ݴ�С
            TMPBUF = peekChars(buffer, offset, MDB_PLATNFORM_INT_SIZE);
            int size = char2int(TMPBUF, MDB_PLATNFORM_INT_SIZE);
            free(TMPBUF);
            offset += MDB_PLATNFORM_INT_SIZE;
            offset += size;
            int result = 0;
            result = undumpCarInfoItem(item, type, buffer + offset - size, size, MDB_PLATNFORM_INT_SIZE);
            if (result < 0) {
                // TODO: �Ƿ������������ͣ�
                // return NULL;
            }
        }
        offset += 1;//��Ϊ�ղŶ�ȡ��TK_END
    }
    //������ݿ��Ƿ��ƻ�
    if (realsize != sizelen) {
        char* errmsg = malloc(sizeof(char) * 200 + strlen(mdbpath));
        memset(errmsg, 0, 200 + strlen(mdbpath));
        sprintf(errmsg, "mdb��%s���ļ����ƻ����ڴ��� %d ����Ŀ��ȴ�õ� %d ����Ŀ��", mdbpath, sizelen, realsize);
        mkerrlog(errmsg);
        free(errmsg);
        free(mdbbuffer);
        return NULL;//��ʵ���Է�����֪���ֵģ����Ϊ�˱���������NULL��ʾ
    }
    free(mdbbuffer);
    return head;
}

int undumpCarInfoItem(carInfoItem* item, enum MDB_ITEM_TK type, char* content, int size, int MDB_PLATNFORM_INT_SIZE) {
    if (type == TK_START || type == TK_END) {
        mkerrlog("��undumpCarInfoItemʱ���ܶ�ȡTK_START��TK_END���͵����ݣ�");
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
            {//��Ա��Ϣ
                int offset = MDB_PLATNFORM_INT_SIZE;//���ƫ�����ǹ̶���value=1
                personInfo* person = NULL;
                switch (*(content + MDB_PLATNFORM_INT_SIZE)) {//��ȡ��Ա����
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
                    sprintf(errmsg, "����δ֪����Ա���ͣ�%d��", *content);
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
    if (stritem->size == 0) {//��������
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
    if (mdbpath == NULL) {//Ĭ��·��
        mdbpath = MDB_DEFAULT_PATH;
    }
    rebindListNodeIndex(nodelink);//��֤index����ȷ��
    ListNode* head = getHeadNode(nodelink);
    ListNode* tail = getTailNode(nodelink);
    ListNode* cur = head;
    int size = tail->index - head->index + 1;
    FILE* fp = fopen(mdbpath, "wb");
    if (fp == NULL) {
        char* errmsg = malloc(sizeof(char) * 200 + strlen(mdbpath));
        memset(errmsg, 0, 200 + strlen(mdbpath));
        sprintf(errmsg, "mdb��%s��д��ʧ�ܣ�", mdbpath);
        mkerrlog(errmsg);
        free(errmsg);
        return;
    }
    //д��ͷ����Ϣ
    fwrite(MDB_HEADER_TK, sizeof(char), 4, fp);
    //sizeof(int)
    char MDB_PLATNFORM_INT_SIZE = sizeof(int) & 0xff;
    fwrite(&MDB_PLATNFORM_INT_SIZE, sizeof(char), 1, fp);
    //һ���ж��ٸ�
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
    if (txtbuffer->isFail) {//��ʧ��
        char* errmsg = malloc(sizeof(char) * 200 + strlen(txtpath));
        memset(errmsg, 0, 200 + strlen(txtpath));
        sprintf(errmsg, "txt��%s����ʧ�ܣ�", txtpath);
        mkerrlog(errmsg);
        free(errmsg);
        return NULL;
    }
    if (txtbuffer->size <= 1) {//�ļ�Ϊ��
        char* errmsg = malloc(sizeof(char) * 200 + strlen(txtpath));
        memset(errmsg, 0, 200 + strlen(txtpath));
        sprintf(errmsg, "txt��%s��Ϊ�գ�", txtpath);
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
    //�ֶ�ȥ��ȡ��ֵ
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
     * �ṹ
     * carId   carBrand carModel carPrice carAge hasRepair hasFault faultDescribe status date      inPrice outPrice estimatePrice realPrice sellername sellerphone buyername  buyerphone  handlername handlerphone employeename employeeid
     * 1000001 �µ�     ZQ70     809000    10    ��         ��       �޹���        Ԥ��    2008/12/1 647200  776640   621312         -1       ��ϼ       50561349942 ��ΰ       67253388023 ����         69165561218  ��ΰ         8450
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
        //���ڣ�ֱ��һ��������
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
        if (strcmp(hasRepair, "��") == 0) {
            item->info->fault->hasRepair = Boolean_TRUE;
        } else {
            item->info->fault->hasRepair = Boolean_FALSE;
        }
        if (strcmp(hasFault, "��") == 0) {
            item->info->fault->hasFault = Boolean_TRUE;
        } else {
            item->info->fault->hasFault = Boolean_FALSE;
        }
        setStringItem(item->info->fault->faultDescribe, faultDescribe);
        if (strcmp(status, "���") == 0) {
            item->order->status = carStatus_inStock;
        } else if (strcmp(status, "����") == 0) {
            item->order->status = carStatus_outStock;
        } else if (strcmp(status, "Ԥ��") == 0) {
            item->order->status = carStatus_reserved;
        } else if (strcmp(status, "����") == 0) {
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
