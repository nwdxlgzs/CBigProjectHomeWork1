'''
测试套件，生成txt格式的数据
'''
import math
import random
from tkinter import EW

# 起始ID
carId = 1000000


def getCarId():
    global carId
    carId += 1
    return str(carId)


# 品牌
carBrands = ['奥迪', '宝马', '奔驰', '一汽奔腾', '长城汽车',
             '广汽传祺', '哈弗', '雷克萨斯', '马自达', '沃尔沃']


def getCarBrand():
    return random.choice(carBrands)


# 型号
carModels = [
    ['A4L', 'A6L', 'A8L', 'Q3', 'Q5', 'Q7', 'S3', 'S5', 'S7', 'SQ5', 'SQ7', 'TT', 'TTS', 'V8L', 'VQR', 'X1', 'X3', 'X5', 'X6',
        'X7', 'XQ', 'XQRS', 'XR', 'XRS', 'XS', 'XSMAX', 'XSV', 'XTYPE', 'XZ', 'Z3', 'Z4', 'Z8', 'ZQ5', 'ZQ70', 'ZQ80', 'ZQ90'],
    ['3系', '5系', '7系', 'X1', 'X3', 'X5', 'M3', 'M5', 'M6', 'M7', 'M8',
        'X6', 'X7', 'X8', 'Z3', 'Z4', 'Z5', 'Z6', 'Z7', 'Z8', 'i3', 'i8'],
    ['GLA', 'GLC', 'GLE', 'GLS', 'GLC', 'GLE', 'GLS', 'GLC', 'GLE'],
    ['B70', 'B50'],
    ['冯军5', '冯军6', '冯军7'],
    ['GS4', 'GS5', 'GM8', 'GM6'],
    ['H1', 'H2', 'H3', 'H4', 'H5', 'H6', 'H7', 'H8', 'H8', 'H9'],
    ['es', 'LS', 'RCF', 'LFA'],
    ['CX4', 'CX5'],
    ['XC90', 'XC60', 'V40', 'V60', 'V90', 'S90', 'S60', 'C30', 'C70']
]


def getCarModel(brand):
    return random.choice(carModels[carBrands.index(brand)])


# 价格（随机生成，一次绑定）
carPrices = []
for k, v in enumerate(carModels):
    p = []
    for i in v:
        p.append(1000*random.randint(10, 1000))
    carPrices.append(p)


def getCarPrice(brand, model):
    return carPrices[carBrands.index(brand)][carModels[carBrands.index(brand)].index(model)]

# 车龄


def getCarAge():
    return str(random.randint(1, 10))

# 车辆故障


def getCarFault():
    hasRepair = "否"
    if(random.randint(0, 10) == 5):
        hasRepair = "是"
    hasFault = "否"
    if(random.randint(0, 10) == 5):
        hasFault = "是"
    faultDescribe = "无故障"
    if(hasFault == "是" or hasRepair == "是"):
        fd = ['发动机', '空调', '刹车', '车身', '轮胎', '其他']
        faultDescribe = random.choice(fd)+"故障"
    return (hasFault, hasRepair, faultDescribe)


# 状态
carStatus = ['入库', '出库', '预定', '已售']


def getCarStatus():
    return random.choice(carStatus)

# 日期


def getDate():
    y = random.randint(2000, 2022)
    m = random.randint(1, 12)
    d = random.randint(1, 28)
    cs = "/"
    return cs.join([str(y), str(m), str(d)])
# 进价


def getInPrice(carPrice):
    return math.ceil(carPrice*random.randint(1, 9)/10)

# 销售价


def getOutPrice(inPrice):
    return math.ceil(inPrice*random.randint(11, 15)/10)

# 估计价


def getEstimatePrice(outPrice):
    return math.ceil(outPrice*random.randint(8, 9)/10)

# 实售价


def getRrealPrice(carPrice):
    if(random.randint(0, 1) == 0):
        return -1
    return math.ceil(carPrice*random.randint(9, 15)/10)


humanNames = ['张伟', '王伟', '王芳', '李伟', '王秀英', '李秀英', '李娜', '张秀英',
              '刘伟', '张敏', '李静', '张丽', '王静', '王丽', '李强', '张静', '李敏', '王敏', '王磊',
              '李军', '刘洋', '王勇', '张勇', '王艳', '李杰', '张磊', '王强', '王军', '张杰', '李娟',
              '张艳', '张涛', '王涛', '李明', '李艳', '王超', '李勇', '王娟', '刘杰', '王秀兰', '李霞',
              '刘敏', '张军', '李丽', '张强', '王平', '王刚', '王杰', '李桂英', '刘芳']
# 手机号


def getPhone():
    return random.randint(10000000000, 99999999999)
# id


def getId():
    return random.randint(1000, 9999)


OurEmployees = []
for i in range(0, 100):
    id = getId()
    name = random.choice(humanNames)
    OurEmployees.append((name, id))
# 卖家信息


def getSeller():
    name = random.choice(humanNames)
    phone = getPhone()
    return (name, phone)
# 购买者信息


def getBuyer():
    name = random.choice(humanNames)
    phone = getPhone()
    return (name, phone)
# 经手人信息


def getHandler():
    name = random.choice(humanNames)
    phone = getPhone()
    return (name, phone)
# 员工信息


def getEmployee():
    return random.choice(OurEmployees)


def genGroup():
    group = []
    group.append(getCarId())
    group.append(getCarBrand())
    group.append(getCarModel(group[1]))
    group.append(getCarPrice(group[1], group[2]))
    group.append(getCarAge())
    f = getCarFault()
    group.append(f[0])
    group.append(f[1])
    group.append(f[2])
    group.append(getCarStatus())
    group.append(getDate())
    group.append(getInPrice(group[3]))
    group.append(getOutPrice(group[10]))
    group.append(getEstimatePrice(group[11]))
    group.append(getRrealPrice(group[3]))
    s = getSeller()
    group.append(s[0])
    group.append(s[1])
    b = getBuyer()
    group.append(b[0])
    group.append(b[1])
    h = getHandler()
    group.append(h[0])
    group.append(h[1])
    e = getEmployee()
    group.append(e[0])
    group.append(e[1])
    for i in range(0, len(group)):
        group[i] = str(group[i])
    return group


def gen(N):
    data = []
    for i in range(0, N):
        gr = genGroup()
        cs = " "
        data.append(cs.join(gr))
    cs = "\n"
    return cs.join(data)

def write(path, msg):
    file = open(path, 'w')
    file.write(msg)
    file.close()
write("database.txt",gen(random.randint(41, 100)))
print("生成完毕")
