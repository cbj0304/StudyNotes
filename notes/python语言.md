[TOC]

# python学习笔记

* 参考书籍：

  python_cookbook第三版

* 学习目标
  * 数据类型
  * 函数和算法


# 数据类型


## 内置容器

* **列表（list）**

  举例：[1，2，3]， 有序集合，元素可重复，元素类型可以不同。

  方法：append/insert/extend/pop/clear/copy/index/remove/reverse/sort

* **元组（tuple）**

  举例：('abc', 3, 3.21)

  和list类似，但是元素一旦初始化不能修改，没有append/insert修改元素的这类方法。

* **集合（set）**

  举例：{1, 4, 7}

  无序集合，元素没有重复。

  方法：add/clear/copy/discard/pop/remove/difference/intersection/symmetric_difference/union/issubset/issuperset/isdisjoin

* **词典（dict）**

  举例：{'a':2,'b':18}

  通过 key 来查找 value。key-value序对是没有顺序的，key不能重复。

  方法：clear/copy/fromkeys/get/has_key/items/keys/setdefault/update/values/pop/popitem

* **字符串（string）**

  举例：'abc'

  字符的有序集合

  方法：join/split/find/strip/upper/lower/replace/len/索引/切片

**可迭代对象：**

​	以上都是可迭代对象（Iterable），内部实现了__iter__方法，可以通过for...in...循环遍历/迭代。

​	通过isinstance()函数可以判断一个对象是否是 iterable 对象。

​	isinstance(a, Iterable) -> 如果a是可迭代类型，返回True

**函数示例：**

```python
# encoding: utf-8

import os
from collections import Iterable
from collections import defaultdict
from collections import OrderedDict
from operator import itemgetter
from collections import Counter
from collections import namedtuple
from collections import ChainMap
import json

if __name__ == '__main__':
    a = [1, 2, 23, -2, 4, 23]
    print(a)
    print(list(a))
    print(type(a))

    assert(a.index(23, 0, len(a)) == 2)
    assert(isinstance(a, Iterable) is True)

    a.reverse()
    print(a)
    print(a.count(23))

    tu = (1, 23, 'aaa')
    print(tu)

    # 可迭代对象之间可以相互转换
    listA = [3, 4, 2, 6, 4]
    tupleA = tuple(listA)
    setA = set(tupleA)
    print(tupleA)
    print(setA)

    # set
    s = set('acbds')
    print(s)  # {'c', 's', 'a', 'b', 'd'}

    # defaultdict会自动为将要访问的键创建映射实体，类似于普通dict的setdefault方法
    d = defaultdict(list)
    d['a'] = [1, 2, 3]
    d['b'] = [4, 5]
    d['a2'] = [11]
    print(json.dumps(d))

    dic = {}
    dic.setdefault('a2', []).append(2)
    dic.setdefault('b3', []).append(3)
    dic.setdefault('b1', []).append(11)
    print(json.dumps(dic))

    # 使词典有序
    d2 = OrderedDict()
    d2['a2'] = 200
    d2['a5'] = 500
    d2['a1'] = 100
    print(json.dumps(d2))

    # 字典计算
    prices = {
        'CC': 201,
        'BB': 403,
        'JJ': 100
    }
    # zip：接受两个可迭代对象，将两个对象中对应元素'压缩'成一个个的tuple，
    # 返回由这些tuple组成的list
    # 若两个可迭代对象不等长，以短者为基准截断
    lst = list(zip(prices.values(), prices.keys()))
    assert(max(lst) == (403, 'BB'))
    lst.sort()
    print(lst)    # [(100, 'JJ'), (201, 'CC'), (403, 'BB')]

    la = [3, 5, 2, 10]
    ta = ('g', 'f', 'c')
    za = zip(ta, la)
    print(list(za))

    # 可迭代对象的集合操作
    print(prices.keys())
    another = {'CC', 'DD'}
    another2 = ['CC', 'DD']
    print(prices.keys() & another)
    print(prices.keys() & another2)

    # 词频统计
    words = ["hello", "you", "you", "and", "hello", "hello"]
    words_count = Counter(words)
    print(words_count, type(words_count))
    print(words_count.most_common(2))

    # 根据某一键值排序
    lines = [
        {'name': 'aaa', 'age': 17, 'score': 98.2},
        {'name': 'bbb', 'age': 16, 'score': 89.2},
        {'name': 'ccc', 'age': 21, 'score': 10.2},
        {'name': 'ddd', 'age': 16, 'score': 10.2}
    ]
    by_age = sorted(lines, key=itemgetter('age'))
    print(by_age)
    by_age_score = sorted(lines, key=itemgetter('age', 'score'))
    print(by_age_score)

    mylist = [3, 5, -1, 9, -5, 7]
    out = [n if n > 0 else 0 for n in mylist]
    print(out)

    mydict = {
        "beijing": 100,
        "shanghai": 300,
        "tianjin": 90,
        "suzhou": 160,
        "nanjing": 88
    }
    skey = ["beijing", "suzhou"]
    # 字典推导
    p1 = [(key, val) for key, val in mydict.items() if val > 100]
    p2 = {key: mydict[key] for key in mydict.keys() if key in skey}
    p3 = dict((key, val) for key, val in mydict.items() if val > 100)
    print(p1)

    # 命名元组(代码从下标操作解脱出来)
    student = namedtuple('student', ['name', 'age', 'score'])  # 返回一种类型student
    st = student("cbj", 18, 100)
    print(st)
    print("new name=%s, age=%d" % (st.name, st.age))
    print("old name=%s, age=%d" % (st[0], st[1]))

    # 生成器表达式
    nums = [2, 3, 4]
    s1 = sum(x*x for x in nums)     # 使用生成器表达式（更优雅和省内存）
    s2 = sum(x*x for x in nums)     # 创建一个临时列表

    files = os.listdir('D:/gcctool/0_mytestdata')
    print([file for file in files])

    if any([file.endswith('.py') for file in files]):
        print('there be python.')

    datas = ['my ', 'age ', 18]
    print(','.join([str(x) for x in datas]))

    lang = [
        {'name': 'c++', 'score': 100},
        {'name': 'python', 'score': 95},
        {'name': 'shell', 'score': 90}
    ]
    m1 = min([x['score'] for x in lang])
    # 另一种迭代器版本
    # 处理列表页每一行是，对于每个可迭代的元素，使用lambda函数
    m2 = min(lang, key=lambda x: x['score'])
    print("m1=%d, m2=%s" % (m1, m2))

    # 多字典合并
    a = {'x': 1, 'y': 2}
    b = {'z': 4, 'x': 3}
    c = ChainMap(a, b)
    print("x=%d, y=%d, z=%d" % (c['x'], c['y'], c['z']))
    del c['y']
    print(c.keys(), c.values(), c.items())
```



## 数值类型

* python3内置数值类型(Numeric)：
  * 整数（int）：python3中的整型只有一种 long 类型
  * 浮点数（float）:
  * 定点数（decimal.Decimal）：固定的小数点位置，固定位数的整数部分和小数部分，更精确。
  * 复数（complex）：用指数达到了浮动小数点的效果，更灵活。
  * 分数（fractions.Fraction）：有理数。
  * 布尔类型（bool）： True/False本质上是1/0。
* python中的数学模块math/cmath：
  * math模块：提供对实数的计算支持
  * cmath模块：供对于复数运算的支持(a=3+4j)

          具体函数查看： dir(math)  dir(cmath)

* 无穷大于非数字：

  * 正无穷：float('inf')

  * 负无穷：float('-inf')

  * 非数字：float('nan')

    得到inf时就查看是否有溢出或者除以0，得到nan时就查看是否有非法操作（如对负数开平方）。

* numPy模块

      第三方库安装 pip install numpy

      向量和矩阵的线性代数运算

* random模块

      随机数生成模块

**代码示例：**

```python
# -*- coding: utf-8 -*-
from fractions import Fraction
from decimal import Decimal
from decimal import localcontext
import cmath
import numpy as np
import random

def IntegerTest():
    print('整型测试...')
    data = 120
    print('data={}, type={}'.format(data, type(data)))    # <class 'int'>

    exit(0)


def FloatTest():
    print('浮点数测试...')
    # 生成浮点数
    data1 = 12.34
    # float() 将整数和字符串转换成浮点数
    data2 = float('12.35')
    print('data={}, type={}'.format(data1, type(data1)))   # <class 'float'>
    print('data={}, type={}'.format(data2, type(data2)))   # <class 'float'>

    exit(0)


def DecimalTest():
    print('定点数测试...')
    # 生成定点数
    data = Decimal('120.3')
    print('data={}, type={}'.format(data, type(data)))    # <class 'decimal.Decimal'>

    exit(0)


def ComplexTest():
    print('复数测试...')
    # 生成复数
    data1 = 2 + 3j
    data2 = complex(3, 4)
    print('data={}, type={}'.format(data1, type(data1)))    # <class 'complex'>
    print('data={}, type={}'.format(data2, type(data2)))    # <class 'complex'>

    # 取出实部和虚部
    assert(data1.real == 2)
    assert(data1.imag == 3)

    # 复数运算
    print(data1 * data2)
    print(data1 / data2)
    print(abs(data1))
    print(cmath.sin(data1))
    print(cmath.exp(data1))

    # 对复数数组执行操作
    arr = np.array([2+3j, 4+5j, 7-8j])
    print(arr + 2)
    print(np.sin(arr))

    print(cmath.sqrt(-1))

    exit(0)


def BooleanTest():
    print('布尔类型测试...')
    # 生成布尔类型
    data1 = False
    data2 = bool(100)
    print('data={}, type={}'.format(data1, type(data1)))     # <class 'bool'>
    print('data={}, type={}'.format(data2, type(data2)))     # <class 'bool'>  True

    exit(0)


def FractionTest():
    print('有理数测试...')
    # 生成有理数
    data = Fraction(2, 8)
    print('data={}, type={}'.format(data, type(data)))     # 1/4 <class 'fractions.Fraction'>

    # 取出分子和分母
    assert(data.numerator == 1)      # 分子
    assert(data.denominator == 4)    # 分母

    # 分数运算
    a = Fraction(3, 4)
    b = Fraction(7, 16)
    print(a + b)
    print(a * b)
    print(float(a))
    pi = Fraction('3.141592654')
    print(pi.limit_denominator(8))    # 设置分母的最大值，返回最接近的有理数 22/7

    # float转分数（有理数）
    x = 3.75
    tu = x.as_integer_ratio()   # (15, 4) <class 'tuple'>
    print(Fraction(*tu))

    exit(0)


def numPyTest():
    print('test numPy')

    # 一维数组，作用到所有元素上
    ax = np.array([1, 4, 5, 2])
    ay = np.array([2, 3, 1, 5])

    print(ax, type(ax))        # <class 'numpy.ndarray'>
    print(ax * 2)
    print(ax + 10)
    print(ax + ay)
    print(ax * ay)

    myfun = lambda x: 3*x**2 - 2*x + 7
    print(myfun(ax))

    print(np.sqrt(ax))
    print(np.cos(ax))

    # 多维数组，作用到所有元素上
    grid = np.zeros(shape=(3, 4), dtype=float)
    print(grid + 10)
    print(grid, type(grid))      # <class 'numpy.ndarray'>

    grid2 = np.array([[1, 2, 3], [4, 5, 6]])   # 2行3列
    print(np.sin(grid2))
    print(grid2[0])              # 第1行
    print(grid2[:, 0])           # 第1列
    print(grid2[0, 0:2])       # 1-2行，1-3列   (下标从0开始，:两侧左开右闭)

    # 矩阵操作
    m = np.matrix([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
    print(m, type(m))
    print(m.T)        # 转置
    v = np.matrix([[1], [2], [3]])
    print(m * v)

    exit(0)


def RandomTest():
    print('test Random...')
    values = [10, 2, 3, 4, 5, 6]
    a1 = random.choice(values)      # 随机选取一个元素
    a2 = random.sample(values, 3)   # 随机选取n个元素
    random.shuffle(values)          # 乱序输出
    print('choice={}\nsample={}\nshuffle={}'.format(a1, a2, values))

    b1 = random.randint(0, 100)       # 产生随机整数
    b2 = random.random()              # 产生0-1的随机浮点数
    b3 = random.getrandbits(100)      # 产生占据100个二进制bit位的大整数（python支持大整数运算，位数不受限制）
    print('randint={}\nrandom={}\ngetrandbits={}'.format(b1, b2, b3))

    # python随机数生成算法是确定可复现的，可以修改初始化种子(可以用int或者bytes字符串)
    random.seed(1234)
    print(random.randint(0, 10))
    random.seed(b'test')
    print(random.randint(0, 10))

    print(random.uniform(1.0, 10.0))     # 获取均匀分布的随机数
    print(random.gauss(10.0, 2.0))    # 产生高斯分布的随机数（均值10.0， 标准差2.0）
 
    exit(0)


if __name__ == '__main__':
    # IntegerTest()
    # FloatTest()
    # DecimalTest()
    # ComplexTest()
    # BooleanTest()
    # FractionTest()
    # numPyTest()
    RandomTest()

    # 四舍五入
    assert(round(2.4573, 2) == 2.46)
    assert(round(2.76) == 3)
    assert(round(273513, -3) == 274000)

    # 浮点数不能特别精确的表示十进制数，如果要求不能有任何误差就用定点数，但是会有一些性能损耗
    # 一般情况下浮点数足以
    a = Decimal('4.2')
    b = Decimal('2.15')
    assert(a + b == Decimal('6.35'))    # 试试换成float怎么样？...
    # 创建本地上下文控制定点数参数，如有效数字
    with localcontext() as ctx:
        ctx.prec = 3
        print(a/b)

    # 格式化  '[<>^]?width[,]?(.digits)?'
    x = 12345.678
    print(format(x, '>10.2f'))
    print(format(x, '^10.2E'))
    print(format(x, ','))      # 千分位分隔符

    # 二、八、十、十六进制
    y = 1234
    s1 = bin(y)       # <class 'str'>
    s2 = oct(y)
    s3 = hex(y)
    len = y.bit_length()   # 转换为二进制占多少bit位
    print('bin(y)={}\noct(y)={}\nhex(y)={}\nbit_length()={}'.format(s1, s2, s3, len))
    # 另一种方法
    print(format(y, 'b'))
    print(format(y, 'o'))
    print(format(y, 'x'))
    # 转十进制
    assert(int('4d2', 16) == 1234)
    assert(int('10011010010', 2) == 1234)

    # 整数转字节码
    d = 20747284487117727783387188
    nbyte, rem = divmod(d.bit_length(), 8)    # 计算整数占多少字节
    if rem:
        nbyte += 1
    print(d.to_bytes(nbyte, 'little'))
    assert(d.to_bytes(nbyte, 'big') == b'\x11)h\x8b\xb3Y<\xfc#\x004')
    assert(d.from_bytes(b'\x11)h\x8b\xb3Y<\xfc#\x004', 'big') == 20747284487117727783387188)
```



## 字符串类型

* 字符串处理函数汇总：

  * 切割：

        re.split()

        str[m:n]

  * 查找与匹配：

        str.startswith()

        str.endswith()

        re.findall()

        re.match()

        str.find()

        fnmatch()

        fnmatchcase()

  * 替换

        str.replace()

        re.sub()

  * 格式化：

        unicodedata.normalize()

        str.lstrip()

        str.rstrip()

        str.strip()

  * 转换：

        str.upper()

        str.lower()

        str.translate()

  * 格式化：

      文本标准化：unicodedata.normalize()

      清空左右指定字符：str.lstrip()/str.rstrip()/str.strip()

      替换：str.translate()/str.replace()

      对齐：str.ljust()/str.rjust()/str.center()/format

      拼接：join/+/print(..., sep=':')

      字符串中插入变量: format()/format_map()+vars()

      指定列宽格式化字符串: testwrap.fill()

  * 其他：

        s.isdigit()

**代码示例：**

```python
# -*- coding: utf-8 -*-
import re
from fnmatch import fnmatch, fnmatchcase
import unicodedata
from test_class import Student
import textwrap

if __name__ == '__main__':

    # -------------------切割---------------------------
    str = 'hello my; name, is cbj'
    lst = re.split(r'[,;\s]\s*', str)
    print('split -> type={}, ret={}'.format(type(lst), lst))

    # ()在正则中用于捕获和分组
    lst2 = re.split(r'(,|;|\s)\s*', str)
    print('split re-has-() -> type={} ret={}'.format(type(lst2), lst2))

    # (?:...) 分组，不捕获
    lst3 = re.split(r'(?:,|;|\s)\s*', str)
    print('split re-has-() -> type={} ret={}'.format(type(lst3), lst3))

    # seq[start:end:step]
    lst4 = [1, 2, 3, 4, 5]
    assert(lst4[::2] == [1, 3, 5])

    # -------------------查找与匹配---------------------------
    # 检查字符串的开头结尾
    url = 'http://www.python.org'
    assert(url.startswith('http') is True)
    assert(url.endswith('https') is False)
    tu = ('org', 'python')
    assert(url.endswith(tu) is True)

    assert(url[-3:] == 'org')      # 切片的方式检查收尾

    ret = re.match(r'http', url)     # 正则的方式检查收尾
    print(ret.group() if ret else None)

    files = ['a.py', 'b.cpp', 'c.java']
    print(any(f for f in files if f.endswith('py')))
    print([f.endswith('py') for f in files])

    # 使用通配符匹配字符串（fnmatch模块）
    assert(fnmatch('test02.TXT', '*.txt') is True)
    assert(fnmatch('test02.py', '?est0?.py') is True)
    assert(fnmatch('test02.py', 'test[0-9]*.py') is True)
    assert(fnmatchcase('test.TXT', '*.txt') is False)    # 大小写敏感

    # 查找 （str.find 或者 re.match re.findall）
    assert(url.find('python') == 11)

    # -------------------替换---------------------------
    # 替换 （str.replace 或者 re.sub）
    str = 'my name is A, your name is B'
    strnew = str.replace('name', 'fullname')
    assert(str == 'my name is A, your name is B')  # 未被修改
    assert(strnew == 'my fullname is A, your fullname is B')

    # -------------------格式化---------------------------
    # 将文本标准化
    s1 = 'Spicy Jalape\u00f1o'
    s2 = 'Spicy Jalapen\u0303o'
    assert((s1 == s2) is False)

    t1 = unicodedata.normalize('NFC', s1)
    t2 = unicodedata.normalize('NFC', s2)
    assert((t1 == t2) is True)

    # 内置函数：大小写转换，判断是不是数字字符等等
    s = "hello world 2018"
    assert(s.isdigit() is False)
    assert(re.findall(r'\d+', s)[0].isdigit() is True)
    assert(s.upper() == 'HELLO WORLD 2018')
    assert(s.upper().lower() == 'hello world 2018')

    # strip
    s = '---*** hello  '
    assert(s.lstrip('-*') == ' hello  ')    # 去掉左侧的-或者*
    assert(s.rstrip() == '---*** hello')    # 去掉右侧空格

    # translate
    replace_map = {
        ord('\t'): ' ',
        ord('\f'): ' ',
        ord('\r'): None,   # 表示删除
    }
    s = 'my \fname\r is\tcb\rj\n'
    print(s.translate(replace_map))
    # 创建替换词典的技巧
    print(dict.fromkeys([1, 2, 3]))
    print(dict.fromkeys([1, 2, 3], "test"))
    # 也可以用replace
    s = 'my \fname\r is\tcb\rj\n'
    s = s.replace('\t', ' ')
    s = s.replace('\f', ' ')
    s = s.replace('\r', '')
    print(s)

    # 字符串对齐 ljust/rjust/center/format
    text = 'Hello World'
    f1 = text.ljust(20, '*')
    f2 = text.rjust(20)
    f3 = text.center(20, '-')
    g1 = format(text, '*<20')
    g2 = format(text, '>20')
    g3 = format(text, '-^20')
    print('f1={}\nf2={}\nf3={}'.format(f1, f2, f3))
    print('g1={}\ng2={}\ng3={}'.format(g1, g2, g3))

    data = 10.3247
    s1 = '{:-^20}'.format(text)
    s2 = '{:>10.2f}'.format(data)
    print('s1={}\ns2={}'.format(s1, s2))

    # 字符串拼接 join/+/print(..., sep=':')
    lst = ['hello', 'my', 'name', 'is', 'John']
    res1 = ' '.join(lst)             # 此方法效率更优
    res2 = lst[0] + ' ' + lst[4]     # 会引起内存赋值和垃圾回收
    res3 = 'hello' 'world'
    print('join -> res1={}\nres2={}\nres3={}'.format(res1, res2, res3))

    print('hello', 'my', 'world', sep=' ')

    # 使用生成器函数，复用代码
    def sample():
        yield 'hello1'
        yield 'my1'
        yield 'world1'

    print(' '.join(sample()))
    for part in sample():
        print(part)

    # 字符串中插入变量 format()/format_map()+vars()
    s = '{name} has {n} apples'
    r1 = s.format(name='cbj', n=10)
    name = 'bj'
    n = 100
    r2 = s.format_map(vars())    # vars从变量域中自行查找
    st = Student('zzs', 100)       # vars()提取对象实例中的成员变量
    r3 = '{name} has {score}'.format_map(vars(st))
    print('format -> r1={}\nr2={}\nr3={}\n'.format(r1, r2, r3))

    # 指定列宽格式化字符串testwrap.fill()
    text = """
Look into my eyes, look into my eyes, the eyes, the eyes, \
the eyes, not around the eyes, don't look around the eyes, \
look into my eyes, you're under"""
    print(textwrap.fill(text, 20))
    print(textwrap.fill(text, 30, initial_indent='    '))  # 首行缩进，其他格式见函数声明
```



* **字符编码：**

      (1) ascii码：规定了128个字符的编码（内存中用一个byte的后边7bit表示），表示英文够用，中文不够用。

      (2) unicode：是字符集，规定了符号的二进制码(万国码),但是没有规定二进制码该如何存储。

      (3) utf8：是编码规则，是互联网上使用广泛的一种unicode实现方式。它是一种变长编码，可以用1-4个字节表示一个符号，

      比如英文字母用1个字节表示，utf8和ascii码是相同的；比如汉字就需要用3个字节表示。

* **python字符串类型：**

  参考：python中的str和bytes类型 https://www.cnblogs.com/chownjy/p/6625299.html

  * **python3字符串的两种类型：**

      -- str(unicode)   ->  <class 'str'>          # 普通字符串

      -- byte码            ->  <class 'bytes'>        # 二进制数据流

      [可以简单理解为: 

  ​	python2 中的<class 'unicode'> 变成了 python3 的<class 'str'>，

        	python2 中的<class 'str'> 变成了 python3 的<class 'bytes'>，

  ​	python2中默认的编码方式是ascii码，中文会乱码，

  ​	python3默认编码是utf8编码，中文不会乱码。

  ​	解决中文乱码，在第一行加“-*-coding:utf-8-*- 或  #encoding=utf-8”。

   ]

  * **str(unicode)对象和bytes对象转换：**

          bstr = str.encode('utf-8')

          str = bstr.decode('utf-8')

**代码示例：**

```python
# -*- coding: utf-8 -*-

if __name__ == '__main__':
    # python3 中 unicode和基础str是等价的，类型都是 <class 'str'>
    ustr = u'字符串'
    str = '字符串'
    print('ustr={}, type={}'.format(ustr, type(ustr)))        # <class 'str'>
    print('str={}, type={}'.format(str, type(str)))           # <class 'str'>

    # 字符串转字节码
    bstr = ustr.encode('utf-8')
    print('bstr={}, type={}'.format(bstr, type(bstr)))        # <class 'bytes'>

    # 字节码转字符串
    str_new = bstr.decode('utf-8')
    print('str_new={}, type={}'.format(str_new, type(str_new)))  # <class 'str'>

    # 整型转ascii字符chr(i)  i取值在0-255
    print(chr(97))   # str 'a'

    # ascii字符转整型ord('a')
    print(ord('a'))  # int 97
```



## 时间日期

* **datetime库**

     timedelta: 时间差对象

     datetime: 时间对象

* **dateutil库**

    第三方库安装 pip install python-dateutil

    处理较复杂的时间日期操作（时区， 模糊时间范围， 节假日等）

* **calendar库**

    处理日历操作

* **pytz库**

    第三方库安装 pip install pytz

    处理时区操作

    整个地球被划分为二十四时区，每个时区都有自己的本地时间。

    为统一而普遍使用一个标准时间，称为通用协调时UTC。

   北京时区是东八区，领先UTC 8个小时,标记为 Date: Sun, 13 June 2010 09:45:28 +0800。

    uct时间转北京时间： uct + 时区差 = 本地时间。

* ime模块

  时间戳 timestamp

  时间元组 struct_time

  格式化时间 format_time

**代码示例：**

```python
# -*- coding: utf-8 -*-
from datetime import datetime
from datetime import timedelta
from datetime import date
from dateutil.relativedelta import relativedelta
import calendar
import pytz
from pytz import timezone
import time

if __name__ == '__main__':
    # datetime库
    a1 = timedelta(days=2, hours=6)
    a2 = timedelta(hours=4)
    a3 = a1 + a2
    print('type(a)={}\na.seconds()={}\na.days()={}\na.total_seconds()={}\n'.format(
        type(a3),
        a3.seconds,
        a3.days,
        a3.total_seconds()
    ))

    b1 = datetime(2019, 10, 13, 10, 16)
    print(b1 + timedelta(days=2, minutes=30))
    b2 = datetime(2019, 12, 12)
    b3 = b2 - b1
    print(b3.days)

    today = datetime.today()
    now = datetime.now()
    print('today={}, type={}\n now={}, type={}'.format(
        today,
        type(today),
        now,
        type(now)
    ))
    print('weekday=', b1.weekday())   # 星期几 取值是[0, 6]

    # 统计本月有多少天
    d = date.today().replace(day=1)  # 回归本月第一天
    print('first date of month={}, type={}'.format(d, type(d)))
    _, days_in_month = calendar.monthrange(d.year, d.month)
    # 打印日历
    print(calendar.prcal(2019))

    # dateutil库
    c1 = datetime(2019, 10, 18)
    print(c1 + relativedelta(months=+4))
    print(c1 + relativedelta(months=-2))

    print('next Tuesday=', c1 + relativedelta(weekday=1))   # 下一个星期二

    # 字符串转日期
    text = '2019-09-20'
    d1 = datetime.strptime(text, '%Y-%m-%d')
    print('d1={}, type={}'.format(d1, type(d1)))
    # 方法2
    year_, month_, day_ = text.split('-')
    d2 = datetime(int(year_), int(month_), int(day_))

    # 日期转字符串
    t = datetime.strftime(d1, '%Y %m %d %H:%M:%S')
    print('t={} type={}'.format(t, type(t)))

    # pytz (时区 timezone)
    e = datetime(2012, 12, 21, 9, 30, 0)
    # 时间本地化为芝加哥时间
    loc_d = timezone('US/Central').localize(e)
    # 本地化后的时间转换为其他时区的时间
    h_d = loc_d.astimezone(timezone('Asia/Hong_Kong'))
    print('l_d={}\nhd={}'.format(loc_d, h_d))  # hd=2012-12-21 23:30:00 +08:00   +08:00代表东八区

    # 为了避免不必要的错误，一般的做法是先将日期转为utc时间(0时区的标准时间)，
    # 所有时间操作完毕后再转为本地时间
    utc_d = loc_d.astimezone(pytz.utc)
    print('utcd=', utc_d)

    # 打印pytz库中的时区代码
    print(pytz.all_timezones)

    # time模块
    print(dir(time))
    t1 = time.time()  # 时间戳
    t2 = time.localtime()   # struct_time
    print('y={} m={} d={} h={} M={} S={} weekday={} nth_day_of_year={} 是否夏令时={}'.format(
        t2.tm_year, t2.tm_mon, t2.tm_mday,
        t2.tm_hour, t2.tm_min, t2.tm_sec,
        t2.tm_wday, t2.tm_yday, t2.tm_isdst
    ))

    t3 = time.mktime(t2)  # struct_time转时间戳

    t4 = time.strftime("%Y-%m-%d %X", t2)  # struct_time 转 字符串时间

    t5 = time.strptime('2011-05-05 16:37:06', '%Y-%m-%d %X')  # 字符串时间转struct_time

    t6 = time.ctime(time.time())  # 时间戳转可读字符串时间，如 Tue Feb 17 10:00:18 2013

    print('t1={}\nt2={}\nt3={}\nt4={}\nt5={}\nt6={}'.format(
        t1, t2, t3, t4, t5, t6
    ))
```



## 可迭代对象

**“实现了\_\_iter\_\_方法的对象就叫做可迭代对象”，\_\_iter__方法的作用就是返回一个迭代器对象"**

* **可迭代对象：**

      内部实现了__iter__方法，如str/list/tuple/set/dict

      可迭代对象的优势：

          1. 可以用for循环遍历

          2. 可用一些现成的算法，如sum、list等

      如何产生可迭代对象：

          1. 内建可迭代对象（list、set、tuple、dict、str）

          2. 自定义可迭代对象 (参考 intRange)

          3. 代理可迭代对象（参考 iterProxyText）

          4. 利用生成器(包含yield关键字)创建可迭代对象（参考 yeildText， 生成器机制和协程：test_coroutine.py）

* **迭代器对象：**

  * 定义：

      内部实现了`__next__`方法，此方法不依赖索引取值。

      内部实现了`__iter__`方法，执行迭代器的`__iter__`方法得到的依然是迭代器本身。

  * 迭代器的优点：

      1.提供了一种不依赖索引的取值方式

      2.同一时刻在内存中只存在一个值,更节省内存

  * 作用过程(参考 iterTest)：

      执行可迭代对象下的`__iter__`方法,返回一个迭代器对象(容器自身)。

      再通过迭代器对象的`__next__`方法返回容器中的下一个值,如果取值次数超过源值的数量就会抛出StopIteration异常。

  迭代器就像一个懒加载的工厂，等到有人需要的时候才给它生成值返回，没调用的时候就处于休眠状态等待下一次调用。直到无元素可调用，返回StopIteration异常。

* **生成器**

  生成器其实是一种特殊的迭代器，不过这种迭代器更加优雅。它不需要再像上面的类一样写`__iter__()`和`__next__()`方法了，只需要一个`yiled`关键字。 生成器一定是迭代器（反之不成立），因此任何生成器也是以一种懒加载的模式生成值。

* **正向迭代和反向迭代**

  * 正向迭代

  * 反向迭代

        列表的reverse()方法

        切片操作

        实现反向迭代协议的__reversesd__方法，它返回一个反向迭代器

**代码示例：**

```python
# -*- coding: utf-8 -*-
from itertools import zip_longest
from itertools import chain
from itertools import permutations
from itertools import combinations
from collections import Iterable

def iterTest():
    a = [1, 2]
    it = a.__iter__()
    print(it.__next__())
    print(it.__next__())
    # print(it.__next__())    # 越界报错

    # next方法操作迭代器对象
    a1 = [3, 4, 5]
    it1 = iter(a1)          # <class 'list_iterator'>
    try:
        while True:
            print(next(it1))
    except StopIteration:
        pass

    # 文件是迭代器对象
    with open('test_re.py', encoding='utf-8') as f:
        while True:
            line = next(f, None)
            if line is None:
                break
            print(line, end='#')


# 自定义迭代对象
class intRange(object):
    def __init__(self, start, end, step):
        self.start = start
        self.end = end
        self.step = step

    # 实现正向迭代方法
    def __iter__(self):
        n = self.start
        while n <= self.end:
            yield n
            n += self.step

    # 定义反向迭代方法
    def __reversed__(self):
        n = self.end
        while n >= self.start:
            yield n
            n -= self.step


# 定义代理可迭代对象
class iterProxyText(object):
    def __init__(self, topic):
        self._topic = topic
        self._values = []

    def add_value(self, val):
        self._values.append(val)

    def __iter__(self):
        return iter(self._values)


# 利用生成器创建可迭代对象和方法
def yeildText():
    # 类
    class iterYeild(object):
        def __init__(self):
            self.values = [100, 200, 300]

        def __iter__(self):
            for i in self.values:
                yield i

    # 测试（类）
    y = iterYeild()
    for i in y:
        print(i)
    print(list(y))

    # 函数
    def frange(start, stop, step):
        x = start
        while x < stop:
            yield x
            x += step

    # 测试（函数）
    for i in frange(10, 15, 2):
        print(i)
    print(sum(frange(10, 15, 2)))

    L = [x * x for x in range(1, 11) if x % 2 == 0]   # 这是一个列表（可迭代对象）
    # 把[] 换成 () 就创建了一个生成器
    G = (x * x for x in range(1, 11) if x % 2 == 0)
    print('type(L)={}, type(G)={}'.format(type(L), type(G)))


if __name__ == '__main__':
    # iterTest()
    yeildText()
    exit(0)

    # 自定义可迭代对象 实现__iter__/__reverse__方法
    n1 = intRange(1, 5, 1)
    for n in n1:
        print(n)               # 正向
    for n in reversed(n1):
        print(n)               # 反向

    # 其他反向迭代方法，先逆序，在遍历
    d1 = [1, 3, 5, 7, 9]
    d1.reverse()                      # 逆序
    print('list.reverse()=', d1)

    d2 = [1, 3, 5, 7, 9]
    d3 = d2[::-1]                    # 逆序 [start: stop:step]
    print('[::-1]=', d3)

    # 测试代理可迭代对象
    t = iterProxyText('test')
    t.add_value('a')
    t.add_value('b')
    t.add_value('c')
    for i in t:
        print(i)

    # 可迭代对象的enumerate方法
    s = ['a1', 'b1', 'c1']
    for i in enumerate(s):
        print(i)                   # 返回数据及其下标的tuple列表 (0, 'a1') (1, 'b1') ...
    for j in enumerate(s, 10):     # 从10开始
        print(j)

    # 同时迭代多个可迭代对象
    a = ('aaa', 'bbb', 'ccc')
    b = [100, 200, 300, 400]
    for k, v in zip(a, b):
        print('k={}, v={}'.format(k, v))         # 返回3项
    for k1, v1 in zip_longest(a, b):
        print('k1={}, v1={}'.format(k1, v1))     # 返回4项

    # 多个集合合并迭代
    for k3 in chain(a, b):
        print('k3=', k3)

    # 展开一个多层嵌套的序列
    def flatten(items, ignore_types=(str, bytes)):
        for x in items:
            if isinstance(x, Iterable) and not isinstance(x, ignore_types):
                yield from flatten(x)    # 词句可以改为 for i in flatten(x): yeild i
            else:
                yield x

    items = ['a1', ['c1', 'b1', ['f1', 'o1']], 'b3']
    for i in flatten(items):
        print(i)

    # 排列组合
    items = [1, 2, 3]
    print('排列...')
    print('permutations...')
    for p in permutations(items):
        print(p)
    print('permutations 2...')
    for p in permutations(items, 2):
        print(p)

    print('组合...')
    print('combinations 3...')
    for p in combinations(items, 3):
        print(p)
    print('combinations 2...')
    for p in combinations(items, 2):
        print(p)
```



## 类的自定义属性和方法

* 私有属性（静态属性、普通属性）、私有方法：

  格式：在私有属性/方法名称前加双下划线。

  权限：一般在当前类内部被调用，不能被外部对象或者继承类调用。

* 但是python的私有是伪私有，可以通过"对象._类名__属性名"被调用，但是绝对不允许，

  原因是：类在创建时,如果遇到了私有成员(包括私有静态字段,私有普通字段,私有方法)它会将其保存在内存时自动在前面加上_类名。

**代码示例：**

```python
# encoding: utf-8

class Person(object):
    def __init__(self, name):
        self.name = name


class Student(Person):

    topic1 = "公有静态字段"
    __topic2 = "私有静态字段"

    # 创建实例本身，属性绑定到self
    # 先调用父类的构造函数，再构造子类
    def __init__(self, name, score):
        Person.__init__(self, name)
        self.score = score
        self.topic3 = "公有普通字段"
        self.__topic3 = "私有普通字段"

    # 调用的时候，参数self代表类对象本身，不用传入
    # 公有方法
    def printScore(self):
        print("name=%s, score=%d" % (self.name, self.score))

    # 公有方法
    def getGrade(self):
        return self.__getAgrade()

    # 私有方法
    def __getAgrade(self):
        if self.score > 90:
            return 'A'
        else:
            return 'B'

    def __str__(self):
        str = 'name={}, ascore={}'.format(self.name, self.score)
        return str


if __name__ == "__main__":
    st = Student("bj", 95)
    print(st.getGrade())
    print(st)
```



## 类的内置属性和方法

* python内置方法：系统自动创建

  `__dict__`: 以字典的形式显示实例自定义属性

  `__class__`: 实例所在类

  `__init__ `和 `__del__`: 构造和析构

  `__new__`: 在`__init__`之前调用, 用于生成实例对象，`__init__`主要是作初始化工作。

  `__doc__`: 类文档

  `__str__`:  实例字符串表示，可读性，调用print时触发

  `__gt__`(self, other)：比较函数，self是否大于other对象，类似的还有ge/lt/le/eq

  `__getattribute__`：属性访问拦截器，访问属性时被调用

  `__dir__`：返回属性和方法列表，调用dir(Obj)是触发，常用于显示类的方法属性列表

**代码示例：**

```python
# -*- coding=utf-8 -*-
import re
import test_class

class Singleton(object):
    # __new__ 实现单例模式
    __instance = None

    def __init__(self):
        pass

    def __new__(cls, *args, **kwargs):
        if Singleton.__instance is None:
            Singleton.__instance = object.__new__(cls, *args, **kwargs)
        return Singleton.__instance


if __name__ == "__main__":

    # 查看模块所有属性
    print(test_class.__dict__)
    st = test_class.Student('cbj', 20)
    st.getGrade()

    # 正则提取所有的函数(正向肯定预查)
    reg = r"[a-z0-9]+(?=\': <function)"
    regObj = re.compile(reg)
    lst = regObj.findall(str(test_class.__dict__))
    print(lst)
```



# 函数和算法

<br/>
## 格式化

**代码示例：**

```python
# -*- coding=utf-8 -*-

a = 100
b = 88.0932
c = ["hello", "words"]
d = {"name": "zz", "age": 18}
e = 'hello world'

# 通过位置格式化
print('score1={}, score2={}'.format(a, b))
print('{0}, age={1}, default={1}'.format(d['name'], d['age']))

# 通过关键字映射
print('n={name}, s={score}'.format(name=d['name'], score=b))


# 通过对象属性
class Person(object):
    def __init__(self, Name, Age):
        self.name = Name
        self.age = Age

    def __str__(self):
        # return('name={}, age={}'.format(self.name, self.age))  # 这样也可以
        return('name={self.name}, age={self.age}'.format(self=self))


p = Person("cbj", "20")
print(str(p))

# 填充与对齐
'''
填充常跟对齐一起使用
^、<、>分别是居中、左对齐、右对齐，后面带宽度
:号后面带填充的字符，只能是一个字符，不指定的话默认是用空格填充
'''
print('{:*>10}'.format(b))


# 精度和类型f
print('{:.2f}'.format(b))

# 进制格式转换
'''
b 二进制
d 十进制
o 八进制
x 十六进制
'''
print('{:b}'.format(a))
print('{:d}'.format(a))
print('{:o}'.format(a))
print('{:x}'.format(a))
```



## 内建函数locals/globals

* locals() 和 globals() 是python 的内建函数，他们提供了字典形式访问局部变量和全局变量的方式。

  locals() 返回当前局部变量的深拷贝，修改locals() 中变量值对原变量本身没有影响。

  globals() 返回全局变量的字典，修改其中的内容，值会真正的发生改变。

**代码示例：**

```python
# -*- coding: utf-8 -*-

ga = "hello world"


def test(**args):
    a = "local hello world"
    print('locals()={}'.format(locals()))
    print('globals()={}'.format(globals()))

    # 通过词典访问并修改局部变量，不生效
    locals()['a'] = "change local hello world"
    print('after change locals()={}'.format(locals()))


if __name__ == "__main__":
    # d是globals， 参数args是locals
    d = {"name": "cbj", "age": 20}
    test(**d)

    # 通过词典访问并修改全局变量，生效
    globals()['ga'] = "change hello world"
    print('after globals()={}'.format(globals()))
```



## json串和字典互转

* json是字符串，长得像字典，需要转换为字典才可以通过key、value来取值。

* **四个函数**（技巧：带s的都是和字符串相关的，不带s的都是和文件对象相关的）

      loads -> json串转字典

      dumps -> 字典转字符串

      load -> 将.json文件转字典

      dump -> 字典转.json文件

      (后边两个可以等价于字典和字符串互转后，字符串写入或者读取文件)

**代码示例：**

```python
# -*- coding:utf-8 -*-
import json

if __name__ == "__main__":
    s = """
    {
        "code": 101,
        "stu": [
            {"name": "张三", "age": 18},
            {"name": "李四", "age": 20}
            ]
    }
    """
    # loads
    d = json.loads(s)
    print('loads => d={}\n keys={}\n type={}'.format(d, d.keys(), type(d)))

    # load
    with open('.vscode/settings.json', encoding='utf-8') as f:
        d1 = json.load(f)
        print('load => d1={}\n keys={}\n type={}'.format(d1, d1.keys(), type(d1)))

    # dumps
    dct = {
        "code": 101,
        "stu": [
            {"name": "张三", "age": 18},
            {"name": "李四", "age": 20}
            ]
    }
    s1 = json.dumps(dct, ensure_ascii=False)
    print('dumps => s1={} \n type={}'.format(s1, type(s1)))

    # dump
    # json.dumps 序列化时对中文默认使用的ascii编码.想输出真正的中文需要指定ensure_ascii=False
    # indent 表示字符串换行+缩进
    with open('test.json', 'w', encoding='utf-8') as f:
        json.dump(dct, f, indent=4, ensure_ascii=False)
```



## 正则表达式

​	// todo
## 函数参数\* / **

python中的*和**

* **用在参数(实参、形参)前边：**

       * 会把接收到的参数存入一个元组 （另一种描述：表示函数能接受任意数量的位置参数）

       ** 会把接收到的参数存入一个字典（另一种描述：表示函数能接受任意数量的关键字参数）

* **用作运算符号**

       * 乘法

       ** 平方

**代码示例：**

```python
# -*- coding: utf-8 -*-

def pringParam(x, *y, **z):
    print('x={}, type(x)={}'.format(x, type(x)))
    print('y={}, type(y)={}'.format(y, type(y)))
    print('z={}, type(z)={}'.format(z, type(z)))


if __name__ == "__main__":
    # 普通变量、列表、字典 同时传
    pringParam(3, 4, name='cbj', age=20)
    '''
    输出：
    x=3, type(x)=<class 'int'>
    y=(4,), type(y)=<class 'tuple'>
    z={'name': 'cbj', 'age': 20}, type(z)=<class 'dict'>
    '''

    pringParam(3, 1, 3, 4)
    '''
    输出：
    x=3, type(x)=<class 'int'>
    y=(1, 3, 4), type(y)=<class 'tuple'>
    z={}, type(z)=<class 'dict'>
    '''

    a1 = 123
    a2 = [1, 2, 3, 4, 5]
    a3 = {'name': 'alam', 'age': 12}
    pringParam(a1, a2, a3)
    '''
    输出：
    a1 a2 a3都被看作普通变量传入
    x=123, type(x)=<class 'int'>
    y=([1, 2, 3, 4, 5], {'name': 'alam', 'age': 12}), type(y)=<class 'tuple'>
    z={}, type(z)=<class 'dict'>
    '''

    # 这个才是符合预期的， 实参和形参都要加 * 和 **
    pringParam(a1, *a2, **a3)
    '''
    输出：
    x=123, type(x)=<class 'int'>
    y=(1, 2, 3, 4, 5), type(y)=<class 'tuple'>
    z={'name': 'alam', 'age': 12}, type(z)=<class 'dict'>
    '''
```



## lambda表达式

*  **lambda表达式(匿名函数)**

      格式:     参数:表达式

      说明：冒号前边是参数，参数可以是0个或多个，多个时用逗号隔开，

  ​		冒号后边是返回值，返回一个函数对象。

* 函数和lambda表达式的关系：

  ```python
      def add(x, y):
          return x + y
      
      # 转为lambda表达式：
      add = lambda x,y : x + y
      
      # 调用 
      print(add(3, 4))
  ```

* for...in...if...表达式

* 三元运算符（处理简单的if...else...）

**代码示例：**

```python
# -*- coding=utf-8 -*-

from functools import reduce

if __name__ == '__main__':
    # sort/map/filter/reduce(累计)，这些内置函数，都可以传一个lambda表达式作为函数对象
    # lambda表达式的参数x是可迭代的一个元素
    # 排序：
    a = [(1, 2), (4, -1), (9, 10), (13, -3)]
    a.sort(key=lambda x: x[1])
    print('sort -> type={}, ret={}'.format(type(a), a))

    # 元素映射：map返回的是迭代器(不要和dict混淆)，需要转list再打印
    b = map(lambda x: (x[0]+x[1]), a)
    print('map -> type={}, list(ret)={}'.format(type(b), list(b)))

    # 过滤：
    c = filter(lambda x: x[1] > 0, a)
    print('filter -> type={}, list(ret)={}'.format(type(c), list(c)))

    d = reduce(lambda x, y: x + y, [1, 2, 3, 4, 5])
    print('reduce -> type={} ret={}'.format(type(d), d))

    # for...in...if...表达式
    print([x[0]+x[1] for x in a])      # -> map
    print([x for x in a if x[1] > 0])  # -> filter

    # 三元运算符（处理简单的if...else...）
    if 1 == 1:
        print('yes')
    else:
        print('no')

    data = 'yes' if 1 == 1 else 'no'
    print('data={}'.format(data))
```



## 回调函数

* **回调函数定义**

      	回调函数就是一个通过函数指针调用的函数。把函数指针（地址）作为参数传递给另一个函数，当这个指针被用来调用其所指向的函数时，我们就说这是回调函数。回调函数不是由该函数的实现方直接调用，而是在特定的事件或条件发生时由另外的一方调用的。

**代码示例：**

```python
# -*- coding: utf-8 -*-

def add(a, b):
    return a + b


def max(a, b):
    return a if a > b else b


def min(a, b):
    return a if a < b else b


def compute(a, b, func):
    return func(a, b)


def simpleCallback():
    print('回调函数的定义...')
    a = input('a=')
    b = input('b=')
    print('a+b=', compute(int(a), int(b), add))
    print('max=', compute(int(a), int(b), max))
    print('min=', compute(int(a), int(b), min))


def apply_async(func, args, *, callback):
    result = func(*args)
    callback(result)      # 回调函数处理result


def print_reslut(result):
    print('get->', result)


class ResultHandler(object):
    def __init__(self, seq):
        self.seq = seq

    def handler(self, result):
        self.seq += 1
        print('result={}, handler={}'.format(result, self.seq))


def ResultHandlerFunc():
    seq = 200
    def handlerFunc(result):
        nonlocal seq         # nonlocal关键字说明，此变量不仅在inner函数里边有效，在整个大函数都有效
        seq += 10
        print('result={}, handler={}'.format(result, seq))
    return handlerFunc


def make_handler():
    seq = 300
    while True:
        result = yield
        seq += 1
        print('result={}, seq={}'.format(result, seq))


def callbackWithState():
    print('带额外状态信息的回调函数三种实现...')

    # 回调函数的应用
    apply_async(add, ("hello ", "world"), callback=print_reslut)

    # 带状态的回调函数（类成员函数）
    h = ResultHandler(100)
    apply_async(add, ("hello ", "world"), callback=h.handler)

    # 带状态的回调函数（闭包函数）
    f = ResultHandlerFunc()
    apply_async(add, ("hello ", "world"), callback=f)

    # 带状态的回调函数（协程）
    g = make_handler()     # 创建一个生成器，可迭代对象
    next(g)                # 首次调用，启动生成器, 遇到yield中断
    apply_async(add, ("hello ", "world"), callback=g.send)   # send的参数被yield接收返回


def inlineCallback():
    print('内联回调函数...')


if __name__ == '__main__':
    # simpleCallback()
    callbackWithState()
    exit(0)
```



## 协程

* **协程的定义：**

      	协程，又称微线程， 纤程。

      	线程是系统级别的，它们是由操作系统调度；协程是程序级别的，由程序员根据需要自己调度。

     	 我们把一个线程（coroutineTest）中的一个个函数（A和B）叫做子程序，那么子程序（A）在执行过程中可以中断去执行别的子程序（B）；别的子程序（B）也可以中断回来继续执行之前的子程序（A），这就是协程。

* **python使用生成器yield中断机制实现协程：**

  ​	生成器、yield关键字、next()、send()函数

  ​	next()、send()函数作用类似，区别是send()可以传参数，c.next()和c.send(None)作用一样。

**代码示例：**

```python
# -*- coding: utf-8 -*-

# 理解 生成器、yield关键字、next()、send()函数 运行
def func():
    while True:
        a = yield 10
        print(a)


def generatorTest():
    c = func()                # 生成可迭代对象
    m = next(c)               # 首次调用，启动生成器，进入while第1次循环，遇到yield中断
    n1 = c.send('hello')      # 从中断处开始执行，yield收到参数'hello'，并把hello赋值给a，打印a, 第二次while循环，遇到yield中断
    n2 = c.send('world')      # 同上
    print('m={} n1={} n2={}'.format(m, n1, n2))


# 协程操作
def A():
    yield
    print('1')
    yield
    print('2')
    yield
    print('3')
    yield
    print('4')


def B():
    yield
    print('a')
    yield
    print('b')
    yield
    print('c')
    yield
    print('d')


def coroutineTest():
    a = A()
    next(a)
    b = B()
    next(b)

    next(a)
    next(a)

    next(b)
    next(b)

    next(a)


if __name__ == '__main__':
    # 生成器机制
    generatorTest()
    # 协程
    coroutineTest()
```



## 闭包

* **python中的闭包：**

      	在一个外函数中定义了一个内函数，内函数里运用外函数的临时变量，并且外函数的返回值是内函数的引用。“闭包”的本质就是函数的嵌套定义，即在函数内部再定义函数。

  ​	“闭包”有两种不同的方式，第一种是在函数内部就“直接调用了”；第二种是“返回一个函数名称”。

* **闭包中引用的自由变量有如下性质：**

      1. 闭包的每个实例引用的自由变量互不干扰；

      2. 一个闭包实例对其自由变量的修改会被传递到下一次该闭包实例的调用。

* **闭包的作用：**

      一般函数，内部声明的局部变量、函数参数等在函数调用结束之后函数里面保存的信息就被销毁了。

      闭包的作用是保存函数的状态信息，使函数的局部变量信息依然可以保存下来。

**代码示例：**

```python
# -*- coding: utf-8 -*-
from functools import partial
import math

def outer_func():      # 定义闭包
    lst = []
    def inner_func(name):
        lst.append(len(lst) + 1)
        print(name, lst)
    return inner_func


if __name__ == '__main__':
    # *参数　**参数，参考test_param.py
    def avg(first, *rest):
        return (first + sum(rest)) / (1 + len(rest))

    print(avg(1, 2, 3, 4))

    # 函数返回多个值，实际上是先创建一个元组，然后返回的
    def test_ret_value():
        return 1, 2, "hello"

    ret1, ret2, ret3 = test_ret_value()      # 用多个变量接收返回值
    print('ret1={} type={}, re2={} type={}, ret3={} type={}'.format(
        ret1, type(ret1),
        ret2, type(ret2),
        ret3, type(ret3)
    ))
    ret = test_ret_value()                  # 用单个变量接收返回值 tuple
    print('ret={} type={}'.format(ret, type(ret)))

    # 以下两种赋值是等价的
    x = "hello", 1.2, 45
    y = ("hello", 1.2, 45)
    print('type(x)={} type(y)={}'.format(type(x), type(y)))

    # lambda中自由变量的值是运行时绑定，不是定义时绑定的
    x = 10
    a = lambda y: x + y         # 定义时
    x = 20
    b = lambda y: x + y         # 定义时
    assert(a(10) == 30)                # 执行时，输出30
    assert(b(10) == 30)                # 执行时，输出30

    # 使匿名函数在定义时就捕获到值 -- 将参数定义成默认参数
    x = 10
    a = lambda y, x=x: x + y
    x = 20
    b = lambda y, x=x: x + y
    assert(a(10) == 20)              # 输出 20
    assert(b(10) == 30)

    # 匿名函数列表
    func = [lambda x, n=n: x+n for n in range(5)]
    for i in func:
        print(i(0))

    # partial固定某些参数的值
    def test_partial(a, b, c, d):
        print(a, b, c, d)

    s1 = partial(test_partial, 1, d=42)  # 设置了默认参数值 a=1, d=42,只需要在给b、c赋值即可
    s1('bb', 'cc')

    # list的排序方法可以接受一个key关键字参数作为排序规则
    # 以下按照距离点(4, 3)的远近排序
    # partial用于微调其他库函数所使用的回调函数的参数
    points = [(1, 2), (3, 4), (5, 6), (7, 8)]

    def distance(p1, p2):
        x1, y1 = p1
        x2, y2 = p2
        return math.hypot(x2-x1, y2-y1)

    points.sort(key=partial(distance, (4, 3)))
    print('points sort ->', points)

    # 测试闭包
    f1 = outer_func()
    f1("bb1")
    f1("bb1")
    f2 = outer_func()
    f2("bb2")
    f1("bb1")
    f2("bb2")
```



// todo 
python多线程
装饰器

## 文件与IO

1. **文本文件和二进制文件的区别：**

   * 文本文件和二进制文件物理上都是二进制存储，只有逻辑上的区别：

     * 文本文件是基于字符编码的文件，常采用ASCII、UTF-8、UTF-16、GBK等字符编码方式，文本编辑器可以识别出这些编码格式，并将编码值转换成字符展示出来。
     * 二进制文件（如视频、图片、音频等），是自定义编码的文件，文本编辑器无法识别这些文件的编码格式, 我们会看到一堆乱码。

   * open()的文本格式和二进制格式：

         	唯一的区别是Windows系统中换行符的处理。在Windows系统中，以文本格式读取文件时，会将 "\r\n" 转换成 "\n"；反之，以文本格式将数据写入文件时，会将 "\n" 转换成 "\r\n"。在 Unix/Linux 系统中，默认的文件换行符就是 \n，因此在 Unix/Linux 系统中文本格式和二进制格式并无本质的区别。为了保险起见，对于 Windows平台最好用 b 打开二进制文件；对于 Unix/Linux 平台，打开二进制文件，可以用 b，也可以不用。

2. **python3字符串（参考d_str2.py）**

       str - 普通字符串(字符序列), 写入文本方式打开的文件

       bytes - 二进制数据流(字节序列)， 写入二进制方式打开的文件

3. **查看文件编码方式：**

       pip install chardet

4. **文件打开模式**

       r - 只读

       w - 只写

       a - 追加

       x - 文件不存在时才能写入

       r+/w+/a+ - 读写

       t - 文本文件

       b - 二进制文件

       说明：默认是二进制b方式， 'r+t' 可以表示以文本可读可写方式打开



**代码示例：**

```python
# -*- coding: utf-8 -*-
import os
import sys
import io
import chardet
import mmap
import pickle
from tempfile import TemporaryFile, TemporaryDirectory, NamedTemporaryFile

# 测试文本文件
def txtReadWrite():
    # 文本文件写入
    with open('data/data.txt', 'wt', encoding='utf-8') as f3:
        f3.write('你好 hello\n')           # write传入字符串参数
        f3.writelines(['aaa\n', 'bbb\n', 'ccc\n'])
        print("python 学习", file=f3)

    # 文本文件读取
    with open('data/data.txt', 'rt', encoding='utf-8') as f:   # with控制块结束时文件会自动关闭
        data = f.read()                  # 一次性读出
        print('f.read() ->', data)
        # 游标指向起点，重新读取
        f.seek(0)
        for line in f:                   # 逐行读取
            print('f -> ', line)
        # 游标指向起点，重新读取
        f.seek(0)
        for l in f.readlines():
            print('f.readlines() ->', l)  # readlines() 读取整个文件得到一个迭代器以供遍历
        # 游标指向起点，重新读取
        f.seek(0)
        print('f.readline() ->', f.readline())             # readline()读取一行


def binReadWrite():
    # 二进制方式读写
    with open('data/data.bin', 'w+b') as f:       # 以读写的方式打开二进制文件
        f.write(b'hello \xe4\xb8\xad\xe5\x9b\xbd')

        data = f.read()
        # byte转str
        print(data.decode('utf-8'))

    # 二进制文件支持数组和c结构体类型直接写入
    import array
    nums = array.array('i', [1, 2, 5, 6])
    with open('data/data.bin', 'wb') as f2:
        f2.write(nums)

    a = array.array('i', [0, 0, 0, 0])        # i代表int类型
    with open('data/data.bin', 'rb') as f3:
        f3.readinto(a)
    print(a)


def strIOTest():
    # 使用类似文件对象的方式，操作普通字符串(str)和二进制字符串(bytes)
    s = io.StringIO()
    s.write("StringIO 111\n")
    print("StringIO 222", file=s)
    data = s.getvalue()             # 读取
    print('s.getvalue() -> ', data, type(data))
    s.seek(0)
    print('s.read() -> ', s.read())                # 读取

    s = io.BytesIO()
    s.write(b'BytesIO \xe4\xb8\xad\xe5\x9b\xbd')
    data = s.getvalue()
    print(data.decode('utf-8'))

    s.seek(0)
    print('s.read()->', s.read().decode('utf-8'))


def gzip_bz2_test():
    # 读写压缩文件
    # gzip
    import gzip
    with gzip.open('data/data.gz', 'wt') as f:
        f.write('gzip 你好中国')
    with gzip.open('data/data.gz', 'rt') as f:
        print('gzip -> ', f.read())

    # bz2
    import bz2
    with bz2.open('data/data.bz2', mode='wt') as f1:
        f1.write('bz2 你好中国')
    with bz2.open('data/data.bz2', mode='rt') as f1:
        print('bz2 -> ', f1.read())


def mmapTest():
    size = os.path.getsize('data/data.bin')
    fd = os.open('data/data.bin', os.O_RDWR)
    m = mmap.mmap(fd, size, access=mmap.ACCESS_READ)
    print('mmap len=', len(m))
    print('slice m[0:10]=', m[0:10])
    m.close()


def openFdTest():
    # 前边的open方法都是打开指定文件名，
    # open还支持传入一个文件描述符(句柄)， 如文件句柄，socket句柄，标准输入句柄等
    bstdout = open(sys.stdout.fileno(), 'wb', closefd=False)  # 自行关闭
    bstdout.write(b'bstdout hello world \n')
    bstdout.flush()
    bstdout.close()

    fd = os.open('data/test.json', os.O_RDWR)
    f = open(fd, 'rt', encoding='utf-8')
    print(f.read())
    f.close()


def temporaryTest():
    with TemporaryFile('w+t') as f:   # 以读写的方式打开文本文件
        f.write('hello\n')
        f.write('TemporaryFile')
        f.seek(0)
        print(f.read())

    # delete=False 防止文件关闭时被自动删除
    with NamedTemporaryFile('w+t', encoding='utf-8', delete=False) as f:
        f.write('NamedTemporaryFile\n')
        f.seek(0)
        print(f.read(), f.name)

    with TemporaryDirectory() as dirname:
        print('dirname=', dirname)


def pickleTest():
    # pickle用于序列化python对象，是python特有的数据编码方式
    # 字典对象的序列化可以用json模块，见test_json.py
    # 大部分python数据类型和自定义类对象都可以通过pickle模块序列话
    from d_class import Student
    st_org = Student('zhangsan', 100)

    # 序列化到字符串
    s = pickle.dumps(st_org)
    st1 = pickle.loads(s)
    print('pickle.loads -> ', st1)

    # 序列话到文件
    with open('data/student.data', 'wb') as f:
        pickle.dump(st_org, f)
    with open('data/student.data', 'rb') as f:
        st2 = pickle.load(f)
        print('pickle.load -> ', st2)        # 打印时调用__str__方法

    s = pickle.dumps([1, 2, 3, 4])
    assert(pickle.loads(s) == [1, 2, 3, 4])


if __name__ == "__main__":
    # txtReadWrite()         # 文本文件读写
    # binReadWrite()         # 二进制文件读写
    # strIOTest()            # 字符串用类文件对象操作
    # gzip_bz2_test()        # 文件压缩读写
    # mmapTest()             # 内存映射
    # openFdTest()           # 扩展：open文件句柄（socket，标准输入输出流)
    # temporaryTest()        # 临时文件、目录
    # pickleTest()           # 对象序列化
    exit(0)

    # 检测文件的编码方式
    f = open('data/data.txt', 'rb')
    data = f.read()
    print('encoding -> ', chardet.detect(data))
    f.close()

    # 当前文件的编码
    print('fileencoding=', sys.getfilesystemencoding())

    # print输出数据，改变默认的分隔符，行尾符
    print('my', 'name', 'is', 'Alice', sep=', ', end='!!\n')

    # 测试文件、目录是否存在
    assert(os.path.exists('data/data.bin') is True)
    assert(os.path.isfile('data/test.json') is True)
    assert(os.path.isdir('data/'))
    print('size=', os.path.getsize('data/test.json'))
    print('mtime=', os.path.getctime('data/test.json'))
    print('ctime=', os.path.getctime('data/test.json'))
    print('listdir=', os.listdir('data/'))

    # 获取文件长度
    print('file size=', os.path.getsize('data/data.txt'))

    # 文件名与路径
    assert(os.path.basename('data/test.json') == 'test.json')
    assert(os.path.dirname('data/test.json') == 'data')
    assert(os.path.join('tmp', 'data', os.path.basename('data/test.json')) == r'tmp\data\test.json')
    print(os.path.splitext('data/test.json'))  # 分隔扩展名 ('data/test', '.json')
```



## python中的{} [] ()
[] 是单个字符匹配，字符集/排除字符集。特殊字符写在 [] 会被当成普通字符来匹配。
```python
[0-3]   # 表示找到这一个位置上的字符只能是 0 到 3 这四个数字。
[^0-3]  # 表示找到这一个位置上的字符只能是除了 0 到 3 之外的所有字符。
[(a)]   # 表示匹配(、a、)中的一种。
```
() 是分组匹配。
```python
(abc)?     # 表示这一组要么一起出现，要么不出现。
(?:abc)    # 表示找到这样abc这样一组，但是不记录。
a(?=bbb)   # 表示a后边必须紧跟三个b。
(?<=bbb)a  # 表示a前边必须有三个b。
```
{}一般用来表示匹配的长度。
```python
\s{3}       # 表示匹配三个空格。
[0-9]{0,9}  # 表示长度为0到9的数字字符串。
```



## 字符编码

* ascII/unicode/utf-8 http://www.ruanyifeng.com/blog/2007/10/ascii_unicode_and_utf-8.html
  * ascii码：规定了128个字符的编码（内存中用一个byte的后边7bit表示），表示英文够用，中文不够用。
  * unicode：是一个符号集，规定了符号的二进制码(世界统一),但是没有规定二进制码该如何存储。
  * utf8是互联网上使用广泛的一种unicode实现方式。它是一种变长编码，可以用1-4个字节表示一个符号，比如英文字母用1个字节表示，utf8和ascii码是相同的；比如汉字就需要用3个字节表示。


## python3数据类型
* 数值类型（参考 test_numeric.py）

  * 整数（Integer）：python3中的整型只有一种 long 类型
  * 浮点数（Float）
  * 复数（Complex）
  * 分数（Fraction）：有理数。
  * 布尔类型（Boolean）： True/False本质上是1/0。

* 字符串（参考 test_str1.py/test_str2.py/test_str3.py）

  * str
  * bytes

*  容器类型（参考 test_container.py）

  * 列表（list）

  * 元组（tuple）

  * 集合（set）

  * 词典（dict）

    说明：字符串也可以看作是字符的集合。

