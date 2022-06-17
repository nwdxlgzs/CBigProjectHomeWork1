# 21级C语言实验课大作业

## **1.要求**
>建立“二手车销售管理系统”，该系统具有读取、查询、排序、修改、新增、删除、统计、保存、输出等功能。
从文件中读取二手车出入库信息，每条信息至少包括车辆编号、车辆品牌、型号、原价、车龄、是否有大修、是否有故障、入/出库/预定状态、日期、卖家联系人姓名、估计价、实售价、销售员姓名、工号、客户名称、电话、进价/销售价、经手人等信息。要求：出入库信息数不少于40条，车辆品牌不少于10种，型号不少于4类

## **2.文件结构说明**

>工程结构

```
root/ ┬ main.c
      | >>> 入口程序
      ├ mdb.c|mdb.h
      | >>> 底层驱动.mdb自定义结构的数据库
      ├ database.c|database.h
      | >>> 抽象化出来的数据库操作库
      ├ utils.c|utils.h
      | >>> 工具函数库
      ├ user.c|user.h
      | >>> 账户管理
      ├ analyzer.c|analyzer.h
      | >>> 数据分析工具
      ├ UIPrint.c|UIPrint.h
      | >>> 生成Print出来的虚假UI（没研究Win的接口，而且作业没要求，先就这么做了）
      ├ UIAction.c|UIAction.h
      | >>> 响应生成Print出来的虚假UI
      ├ common.h
      | >>> 统一定义的东西
      ├ peekTool.c|peekTool.h
      | >>> 翻页查看核心实现
      ├ TESTSUIT.py
      | >>> 生成txt测试数据的工具
      └ <over>
```

>数据结构（默认）

```
root/ ┬ database.txt
      | >>> 由TESTSUITE.py生成的测试数据
      ├ errlog.txt
      | >>> 设计之初做了打log的准备，mkerrlog函数会往这里写错误日志
      ├ database.mdb
      | >>> 默认mdb数据库
      ├ tmp_database_auto_save-{XXXXX}.temp.mdb
      | >>> 自动保存没有路径的mdb数据库
      └ <over>
```

## **3.mdb数据库结构说明（C注释）**
```C
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
```
>说明：sizeof(int)是mdb保存时平台int长度，所以理论上可以做到mdb文件的跨平台（但是并没有按不同架构编译测试）

## **4.carInfoItem结构说明（C注释）**
```C
/**
 * [车辆基本信息]->[struct:carInfo]
 *      |车辆编号->carId
 *      |车辆品牌->carBrand
 *      |型号->carModel
 *      |原价->carPrice
 *      |车龄->carAge
 *      [车辆故障]->[struct:carFault]
 *          |是否有大修->hasRepair
 *          |是否有故障->hasFault
 *          |故障描述->faultDescribe
 * [订单信息]->[struct:rderInfo]
 *      |状态{入/出库/预定/已售}->status
 *      |日期->date
 *      |进价->inPrice
 *      |销售价->outPrice
 *      |估计价->estimatePrice
 *      |实售价->realPrice
 *      [卖家信息]->[struct:personInfo]
 *          |类型->type=personType_seller
 *          |卖家联系人姓名->name
 *          |电话->phone
 *      [买家信息]->[struct:personInfo]
 *          |类型->type=personType_buyer
 *          |客户名称->name
 *          |电话->phone
 *      [经手人信息]->[struct:personInfo]
 *          |类型->type=personType_handler
 *          |经手人->name
 *          |电话->phone
 *      [员工信息]->[struct:personInfo]
 *          |类型->type=personType_employee
 *          |销售员姓名->name
 *          |工号->id
 */
```

## **5.TXT测试数据结构（C注释）**
```C
/**
 * 结构
 * carId   carBrand carModel carPrice carAge hasRepair hasFault faultDescribe status date      inPrice outPrice estimatePrice realPrice sellername sellerphone buyername  buyerphone  handlername handlerphone employeename employeeid
 * 1000001 奥迪     ZQ70     809000    10    否         否       无故障        预定    2008/12/1 647200  776640   621312         -1       李霞       50561349942 张伟       67253388023 王敏         69165561218  刘伟         8450
 */
```
>为了方便测试，我提供了`TESTSUITE.py`生成txt数据，直接执行python脚本就会生成`database.txt`数据

测试样例（单条）
```
1000001 奥迪 ZQ70 809000 10 否 否 无故障 预定 2008/12/1 647200 776640 621312 -1 李霞 50561349942 张伟 67253388023 王敏 69165561218 刘伟 8450
```

## **6.功能实现**

- [x] 自定义数据库：mdb（理论跨平台）
- [x] txt形式测试数据库与生成
- [x] 条件查询
- [x] 条件排序（支持升降序）
- [x] 分页查看
- [x] 跳页查看
- [x] 带参选择性查看指定值
- [x] 修改数据
- [x] 添加数据
- [x] 删除数据
- [x] 统计信息（数据分析）
- [x] 数据自动保存
- [x] 账户系统
- [x] 关键注释
- [x] 多级菜单
- [x] 错误日志系统（errlog.txt）
- [x] 绝大部分malloc空间的free

## **7.使用流程**

>首次使用：注册账号

-  登录dev账号（账号密码均是：nwdxlgzs@github.com）
-  创建自己的账号（如：账号996密码ICU）
-  登出dev账号

>下级账号开设

- 登录自己的账号（如：账号996密码ICU）
- 创建下级账号（如：账号123密码456）

>首次录入在空mdb中时的保存

- 手动导出一份mdb（打开mdb方式会记录打开地址，届时不需要再次手动导出）

>txt数据生成
- 执行`TESTSUITE.py`

>录入建议
- 大量数据时使用txt录入
- 有空格需求时使用手动录入（但是去掉前后空格，保留中间空格）

## **8.逻辑框架**

>用户系统

```
权限分层：
    dev        开发者
    admin      管理员
    manager    经理
    employee   员工
    cust       客户

数据：
    用户数据进行RC4加密保存

权限：
    选择功能时检查权限
```

>数据库系统

```
底层驱动：
    由mdb.c驱动生成或者保存ListNode

上层操作：
    由database.c操作ListNode
    由analyzer.c分析ListNode
```

>UI系统

- 就当是UI吧，Windows的库暂时没玩明白

```
展示：
    由UIPrint.c打印主体
    由peekTool.c生成可字符串形式的十行一页

响应：
    由UIAction.c响应对应UI事件
```

## **9.已知（和猜测可能发生的）BUG**

- Q1：单独测试无法复现，但是反复测试时概率出现修改数据后自动保存失效。
- A1：无法稳定复现，无法找到问题，暂时无法修复（事实上，`UIAction.c`部分代码在尝试解耦合`nodelink`去支持多用户同时处理不同`mdb`（因为`database.c`设计之初就计划支持多用户同时操作，只不过因为复杂就放弃这个功能了，但是代码结构没有改变），但是根据分析，不是这个导致的问题，但是这个是最可疑的地方，所以提一嘴）；但是在测试中，手动导出一直正常工作，真遇到BUG可以导出一份。


- Q2：内存预警
- A2：大部分malloc的指针均被得到有效释放，但是可能存在部分指针没有被管理，这个不保证有遗漏的，也不保证没有遗漏的，使用时请注意内存。