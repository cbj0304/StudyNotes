[toc]

# 内容提要

* Makefile

  Makefile主要组成  

  Make工作流程  

  如何编写Makefile（变量、命令、函数）  

* gdb调试

  调试环境  

  命令介绍  

  

# Makefile基本语法

* 参考 https://www.jianshu.com/p/5982ccb87af0

## 基本格式

```makefile
[输出的目标] : [输出目标的依赖对象]
	[生成目标需要执行的命令]
	
# 目标：文件或者标签。  
# 命令：每行命令要以tab开头。 由若干条shell命令组成。

# 举例：编译 hello.c，需要执行命令gcc -o hello hello.c，如果用Makefile如下：

hello : hello.c  
	gcc -o hello hello.c

# 执行make，就会生成hello可执行文件。
```

## Makefile主要组成

* 显示规则：明确写出来的依赖关系。  

* 隐式规则：make自己推导出来的，如生成目标main.o就推出依赖条件main.c和对应的编译命令。  

* 变量定义：类似程序中的宏，变量替换。  

* 文件指示：类似程序中的预编译  
  include -- 包含其他makefile（-include表示遇到错误继续执行）   
  
  \#ifdef...   
  
  def...endef -- 命令组宏定义，直接展开，注意shell命令前tab缩进）    
  
* 注释： 以#开头。  

## Make 工作流程

* Make读取当前目录下命名为 GNUmakefile/Makefile/makefile 或者 -f 直接指定的所有规则文件。  
* 读入被 include 的其他 Makefile，在对应位置展开。  
* 初始化变量。  
* 推导隐式规则；分析所有规则，创建依赖关系链，决定哪些需要【重新】生成，执行命令。  
  从第一个 target（排除以 . 开头的 target，比如 .PHONY）开始，这个就是默认目标，本次任务的终极目标(或者可以显式设定 .DEFAULT_GOAL)。   
  判断目标是否存在， 依赖的对象是否有更新。  
  根据依赖关系一步一步追溯查找，建立依赖关系链，执行需要执行的命令，最终输出终极目标。  
  没有在依赖链上的目标是不会被直接执行到的，比如 clean。  

编写规则举例：

```makefile
objects = main.o kbd.o command.o display.o \
        insert.o search.o files.o utils.o
        
# make读取到的第一个target， 默认设置为终极目标
edit: $(objects)
    gcc -o edit $(objects)
    
# 隐含规则， make 根据 xx.o 推导出依赖 xx.c, 以及相应的编译命令
# 如 -> main.o: defs.h
# 等同 ：
#   -> main.o: main.c defs.h
#   ->    gcc -o main.o main.c defs.h
main.o: defs.h
kbd.o: defs.h command.h
command.o: defs.h command.h
display.o: defs.h buffer.h
insert.o: defs.h buffer.h
search.o: defs.h buffer.h
files.o: defs.h buffer.h command.h
utils.o: defs.h

# .PHONY 定义为目标 clean（和终极目标没有依赖关系） 
# clean 和 edit 没有依赖关系 直接执行 make 是不会运行到的， 需要通过 make clean 执行
.PHONY: clean
clean:
    -rm edit $(objects)**
```

上边的makefile进一步修改：

```makefile
SRCS = main.c
SRCS += command.c
SRCS += display.c
SRCS += files.c
SRCS += insert.c
SRCS += kbd.c
SRCS += search.c
SRCS += utils.c

# 语法替换
OBJS = $(SRCS:.c=.o)      # 等价于 $(patsubst %.c, %o, $(SRCS))
DEPS = $(SRCS:.c=.d)

# 第一个目标 all，终极目标
all : edit

edit : $(OBJS) 
    $(CC) -o edit $(OBJS)

-include $(DEPS)
# @ - % 这三个字符在makefile中的特殊含义？  命令不显示、报错继续执行、匹配任意个字符。
# 包含触发下面的 DEPS 依赖
# "%"的意思是匹配零或若干字符
# 在Makefile中 $ 有特殊含义，表示它的字面意思需要写两个$，所以 Makefile 中的四个 $ 传给Shell变成$$(当前进程id)，用于命名保证唯一性。
# @set -e;  @表示执行的这条命令不显示出来（关闭命令回响）；set -e告诉bash如果任何语句的执行结果不是true则应该退出。
# shell 按顺序一条条执行规则指定的命令。但是如果需要让上一条命令的结果应用到下一条，需要用分号分隔命令并保证命令处于同一行。
# sed文本替换，类似于：main.o : main.c defs.h --> main.o main.d : main.c defs.h
$(DEPS) : %.d : %.c
    @set -e; rm -f $@;\
        $(CC) -MM $(CPPFLAGS) $< > $@.$$$$;\
        sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;\
        rm -f $@.$$$$

# 任务前添加一个减号-，表示任务出错不会终止，继续执行。
.PHONY : clean
clean :
    @-rm edit $(OBJS) $(DEPS)
```

## 变量

### 自动变量

```makefile
- $@  ：指代当前目标，Make 命令当前构建的那个目标。  
- $<  ：指代第一个依赖条件。如果依赖对象是一个序列，依次代表每一个依赖条件。
- $^  ：指代所有依赖条件，之间以空格分隔。`规则为 t: p1 p2，那么 $^ 就指代 p1 p2`
- $?  ：指代比目标更新的依赖条件，空格分隔。`规则为 t: p1 p2，其中 p2 的时间戳比 t 新，$?就指代p2`
- $*  ： 指代匹配符 % 匹配的部分。`%.txt 匹配 f1.txt，$* 就表示 f1`
- $(@D) 和 $(@F) ：分别指向$@的目录名和文件名。`$@ 是 src/input.c，那么$(@D) 的值为 src ，$(@F) 的值为 input.c`
- $(<D) 和 $(<F) ：分别指向 $< 的目录名和文件名。
```

### 变量赋值

  * ?=   如果没有被赋值过就赋予等号后面的值。
  * +=  追加赋值。
  * :=   覆盖之前的值（变量值替换）。
  * =    最基本的赋值(最后才展开)。

  ```makefile
  x = XXX
  y = $(x)
  x = YYY
  # make会将整个makefile展开后，再决定变量的值。上例中y的值是YYY。
  x := XXX
  y := $(x)
  x := YYY
  # 上例中 y的值将会是 XXX。
  ```

### override

在执行 make 时,如果通过命令行定义了一个变量,那么它将替代在 Makefile中出现的同名变量的定义。  
如果不希望命令行指定的变量值替代在 Makefile 中的变量定义（通过=/:=/+=赋值的变量）,那么我们需要在 Makefile 中使用指示符“override”来对这个变量进行声明。
即， override可以保护makefile中定义的变量的值。 

### vpath/VPATH

  * 大写VPATH是make中一种特殊变量；  格式：VPATH = dir1:dir2 
  * 小写vpath是makefile中的一个关键字； 格式：vpath pattern dir 为符合模式"pattern"的文件指定搜索目录"dir"。多个目录使用空格或者冒号:分开。
  * 作用：make会在当当前目录找不到的情况下，到vpath/VPATH所指定的目录中去找寻文件了。  
    通过vpath/VPATH告知文件搜寻路径是告知的make，这利于它隐式推导时的依赖文件搜索，而不是告知的gcc，所以还是得通过-I指定gcc预编译时头文件搜索路径。

  ```makefile
  # 通过 VPATH 生成 CFLAGS 变量供编译器使用
  VPATH = src:../headers
  override CFLAGS += $(patsubst %,-I%,$(subst :, ,$(VPATH)))
  ```

## 命令

### makefile的静态模式

  * 生成可执行文件需要两步：  
    编译：将.c生成目标文件。 `gcc -c xxx.c`  
    链接：将.o生成可执行文件。`gcc  *.o  -o xxx`  

  ```makefile
  # 静态模式是一种自动编译模式，用于定义多目标规则，格式：
  # < targets ....> : < target-pattern > : < prereq-patterns ...>
  #     <commands>
  # 含义：取target-pattern模式中的%代表部分(其实就是去掉.o后的文件名)，并为其加上[.c]结尾，形成新的集合。OBJS就是各种.o文件（实际编写程序时一般省略），然后%.o就是具体的解释，而%.c就是对应同样名字的.c文件。
  # 自动变量：$< 表示依赖对象集中的第一个，$@ 则代表了目标集。所以这个功能就是要遍历所有的.c文件，对所有的.c文件进行编译，然后编译生成对应的.o文件。
  $(OBJS) : %.o : %.c
  	gcc -c $< -o $@
  ```

### 命令回响

  ```makefile
  echo 命令执行
  # 会输出两行结果，第二行是我们需要的输出，关闭命令回响需要在该命令前添加 @
  # echo 命令执行
  # 命令执行 
  ```

### -MM 
  功能：可以自动找寻文件的包含，生成依赖关系。  

  ```makefile
  $ gcc -MM main.c
  # 会输出 main.o : main.c defs.h
  ```

### 命令参数

  * make -n（或者 --just-print）：只显示命令，不执行命令（用于排查问题）。
  * make -s（或者 --slient）：全面禁止命令显示。


### 条件编译

  ```makefile
  libs_for_gcc = -lgnu
  normal_libs =

  foo : $(OBJS)
  ifeq ($(CC), gcc)  # 不缩进（否则会被认为是传递给 shell 的命令）
    $(CC) -o foo $(OBJ) $(libs_for_gcc) # 传递命令，缩进
  else
    $(CC) -o foo $(OBJ) $(normal_libs)
  endif
  
  ifneq (,$(findstring t,$(MAKEFLAGS)))  # 函数 findstring 用于判断 A 字符串是否在 B 字符串， 没有返回空，有返回 A（判断执行flag make -t）
  ifeq ($(strip $(foo)),)               # 判断变量是否为空
  ifeq ($(shell uname -m), x86_64)      # 执行shell命令
  ```

## 函数

  ```makefile
  $(function     arguments)  # 风格 1
  ${function     arguments}  # 风格 2 , 函数和参数用空格或tab分隔，不同参数用逗号分隔，函数调用的返回用$获取。
  
  comma:= ,
  empty:=
  space:= $(empty) $(empty)       # 定义空格
  foo:= a b c
  bar:= $(subst $(space),$(comma),$(foo))  # subst函数提供替换字符功能，替换后变为 a,b,c
  ```

### 字符串处理函数

  ```makefile
  # 判断相等
  ifeq (ARG1, ARG2)
  ifeq 'ARG1' 'ARG2'
  ifeq "ARG1" "ARG2"
  ifeq "ARG1" 'ARG2'
  # 不相等对应 #ifneq

  # 简单替换：将"text"中的"from"替换成"to"
  $(subst from ,to ,text)
  
  # 模式替换 $(patsubst pattern ,replacement ,text)
  objects = foo.o bar.o baz.o
  $(patsubst %.o, %.c, $(objects))    # 等价于 $(objects:.o=.c)

  # 去除字符串开头和结尾的空格，同时对中间的多个空格替换为一个。$(strip string)
  $(strip a b   c )
  
  # 字符串查找：判断字符中是否包含指定字符串， 有返回查找的字符串，否则返回空。$(findstring find ,in)
  $(findstring a,a b c)    # 返回a
  
  #字符串模式过滤：返回符合或者不符合的字符串, 输入字符单词空格区分。$(filter pattern ...,text)
  sources := foo.c bar.c baz.s ugh.h 
　$(filter %.c %.s, $(sources))   # 返回 foo.c bar.c baz.s

  # 返回不符合的字符串。$(filter-out pattern ...,text)
  objects = main1.o foo.o main2.o bar.o
  mains = main1.o main2.o 
  $(filter-out $(mains), $(objects))      # 返回foo.o bar.o
  
  # 排序去重：按字母顺序对序列（空格划分）进行排序，同时去除重复的词组, 返回按单个空格进行划分。$(sort list)
  $(sort foo bar   lose lose)     # 返回 bar foo lose
  
  # 字符串切片 $(word n ,text)   $(wordlist s , e ,text)   $(words text) $(firstword names ...) $(lastword names ...) 
  $(word   2,  foo bar baz)         # 返回 bar
  $(wordlist 2, 3, foo bar baz)     # 返回 bar baz
  $(words aa bb cc dd)              # 返回 4
  $(firstword foo bar)              # 返回 foo
  $(lastword foo bar)               # 返回 bar
  ```

### 文件名处理函数

  ```makefile
  # 返回除去最后文件名的路径部分， 没有路径直接返回"./"   $(dir names ...)
  $(dir lcd/src/foo.c hacks)  # 返回 : lcd/src/ ./  
  
  # 返回不包含目录的文件名  $(notdir names ...)
  $(notdir src/foo.c hacks lcd/)   # 返回 ： foo.c hacks

  # 文件名后缀  $(suffix names ...)
  $(suffix src/foo.c src-1.0/bar.c hacks lcd.c.o)        # 返回 ： .c .c .o

  # 不包含后缀  $(basename names ...)
  $(basename src/foo.c src-1.0/bar hacks)   # 返回 : src/foo src-1.0/bar hacks

  # 加后缀  $(addsuffix suffix, names ...)
  $(addsuffix .c, foo bar)      # 返回 : foo.c bar.c

  # 加前缀  $(addprefix prefix, names ...)
  $(addprefix src/, foo bar)    # 返回 ： src/foo src/bar

  # 对应连接参数  $(join list1, list2)
  $(join a b, .c .o)            # 返回 ： a.c b.o

  # 获取工作目录下所有符合模式的文件  $(wildcard pattern )
  $(wildcard *.c)     # 返回所有 .c 文件

  # 返回绝对路径，如果文件不存在，返回空  $(realpath names ...)

  # 返回绝对路径，$(abspath names ...)
  ```

### 条件函数

  ```makefile
  # if
  con =
  $(if $(conn), "true", "false")       # 条件为真，返回true，否则返回false
  
  # or 依次展开每个参数，遇到非空的就停止，并返回该值，否则最后返回空。
  conn1 =
  conn2 = CONN2
  conn3 = CONN3
  $(or $(conn1), $(conn2), $(conn3))      # 返回CONN2
  
  # and 展开所有参数，如果有一个为空，返回空，如果全部都不为空，返回最后一个参数。
  conn1 = CONN1
  conn2 = CONN2
  conn3 = CONN3
  $(and $(conn1), $(conn2), $(conn3))    # 返回CONN3
  
  # $(foreach var, list, text) 按顺序依次取出 list 中的单词逐个取出放入到临时变量 var 中， 返回 text， 
  # 每次返回的 text 以空格分开，遍历所有单词后返回完整的组合字符串。
  list = a b c d e f
  $(foreach var, list, $(var).c)     # 返回 a.c b.c c.c d.c e.c f.c
  ```

# gdb调试

## 调试环境

利用gdb调试，需要在gcc编译过程中加上-g选项。  
-g 选项的作用是在可执行文件中加入源代码的信息（如机器指令对应的源码行号）。在调试时必须保证gdb能找到源文件。  
命令行中敲回车表示执行上一条命令。

```shell
$ gcc test.c -g -o test   # 生成带有调试信息的可执行文件test
$ gdb test                # 调试可执行文件
$ gdb -p PID              # 调试正在运行的进程
$ gdb -c core.123         # 查看core文件出错点的函数调用
```

## 命令介绍

* help：查看命令类别。
* help data：查看data类别下的命令。
* **list(简写为l)**：命令列出当前程序的代码，默认列出10行。
* **start**：开始执行程序，gdb停在main函数变量定义之后的第一条与举出等待我们发命令。
* **quit(简写为q)**：退出调试环境。
* **next(简写为n)**：程序向下执行。
* **step(简写s)**：跳入函数中进行调试。
* **backtrace(简写为bt)**：查看函数调用的栈帧。
* **info(简写为i)**：查看变量值。
* info(i) watchpoints：查询当前观察点。
* info(i) locals：查看局部变量的值。
* info(i) breakpoints：查看断点信息。
* **print(简写为p)**：打印出变量的值（(gdb) p sum）。
* **continue(简写为c)**：命令运行到程序结束（如果有断点会停止在断点处）。
* set var 变量=XX：进行变量赋值，运行调试程序，验证思路正确性。
* **break命令(简写为b)**：设置断点（break src/main.cpp:15）。
* break src/main.cpp:15 if sum!=0：根据条件设置断点（仅当sum!=0的时候在15行设置断点）。
* **delete breakpoints**：删除所有断点。
* delete breakpoints： 断点编号(info 出来的编号)：删除指定断点。
* disable/enbale breakpoints：禁用/启用 断点。
* **run(r)**：设置断点后从头进行调试。
* watch：设置观察点。断点是当程序执行到某一代码行时中断，而观察点是当程序访问某个存储单元时中断。(gdb) watch input[4]
* gdb -tui：启动gdb，并且分屏显示源代码。

* gdb调试多线程
  * ps -aux (或者ps -ef) 查看进程；ps -Lf 5324   查看进程中的所有线程 （或者 top -H -p 进程id）
  * gdb -p 进程号 ： 调试正在运行的进程
  * info thread ：查看有多少线程，线程编号、线程id
  * thread 线程编号（简写t 线程编号）： 切换到具体的线程
  * 在线程中设置断点
  * set scheduler-locking off ：让所有的线程运行，gdb调试状态下只有当前线程运行，所以先要让所有线程都运行起来。
  * continue ： 等待程序停在断点处。
  * info ： 查看现场，变量等。

## 使用dmesg和addr2line分析程序core原因

   如果程序挂掉但是没有生成core文件，
   通过dmesg命令可以看到程序挂掉的时间和出问题的内存地址，
   通过addr2line命令可以将内存地址转换为文件的行号，从而定位问题。


 

