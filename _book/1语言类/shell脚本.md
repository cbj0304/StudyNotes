[TOC]

# 内容提要

* 数据类型
  * 字符串
  * 日期时间
  * 数组
  * 文件
* 函数
  * 算数运算
  * 逻辑控制 case...in、if...else、for/while/until
  * 常用命令 
    tee/read/IFS/find/xargs/cut/tr/
    sort/uniq/split/tree/expect/
    head/tail/egrep/sed/awk/
    paste/shift/tput/stty

# 字符串

## 单引号和双引号

* 区别

  * 单引号就是将所有字符作为普通字符（原样输出）
  * 双引号会保留特殊字符的特殊含义

  ```shell
  a=1;
  echo "$a"  # 输出 1
  echo '$a'  # 输出 $a

  echo "!"   # 报错;
  echo '！'  # 输出!
  ```

## 字符串打印-cat

* cat -n  -打印行号
* cat -b  -空白行不打印行号
* cat -s  -压缩空白行，多个变一个
* cat -T  -制表符打印成^I

## 格式化-printf

```shell
# %5s->右对齐（默认），宽度5字符
# %-10s->左对齐，宽度10字符
# %-4.2f->左对齐，宽度8字符，保留2位小数
printf "%5s %-10s %-8.2f\n" 1 Sarath 80.3456
```

## 字符串比较

* 字符串的比较最好用双括号，不会出错

  [[ $str1 == $str2 ]] 等价于 [[ $str1 = $str2 ]] (注意=两边的空格，没有空格就是赋值了)  
  [[ $str1 != $str2 ]]  
  [[ $str1 > $str2 ]]  
  [[ $str1 < $str2 ]]   
  [[ -z $str1 ]] --字符串空返回真   
  [[ -n $str1 ]] --字符串非空返回真   

## 其他字符串操作

   ```shell
   var="abcdef"
   echo ${#var}     # 字符串长度 6
   echo ${var:1:3}  # 提取子串 bcd
   ```

## 通配符与正则

* 正则和通配符的使用场景

  通配符一般只用于**文件名**匹配，如find，ls，cp，mv等。

  正则表达式是用来匹配**字符串**的，针对文件内容的文本过滤大都用正则表达式，如grep，awk，sed等。

  ```shell
  # 通配符的含义：
  * ---代表 0 个或者多个任意字符。（正则中的 .* 代表任意字符，*代表任意次）
  ? ---匹配任意单个字符。（正则中的 .? 代表0或者1个任意字符，?代表0次或1次）  
  [] ---匹配括号内的任意一个字符，如[a,b,c]。（正则中的[]表示单个字符组成的字符集）  
  {} ---匹配花括号中的任意一个字符串，如{abc,xyz,123} （正则中的 ( ) 表示分组，如 (abc|de) 表示abc或者de， 正则中的{n}，表示前边的模式匹配n次）
  [!] ---匹配不在中括号内的一个字符 （和正则中的 [^]作用相似，都是反向选择）  
  当要把以上的* ? [ ]这些字符当成参数或者字符串处理时，需要\（反斜杠）转义。
  ```

# 日期时间

* 时间格式转换

* 时间设置和同步

  ```shell
  # 时间格式转换
  date +%s         # 时间戳
  date +%F         # 日期（%Y-%m-%d）
  date +%H:%M:%S   # 时间
  date "+%F %X"    # 2020-01-02 05:28:23 PM

  date -d '@1561974846'  +%Y-%m-%d            # 时间戳转可读日期
  date -d 'Thu Jul  4 15:29:10 CST 2019' +'%F %H:%M:%S'
  date -d 'Thu Jul  4 15:29:10 CST 2019' +%s  # 日期转时间戳

  # ntpdate时间同步。强制性的将系统时间设置为ntp服务器时间。
  # ntpdate加cron的组合进行时间同步可能会造成时间的跳跃，对一些依赖时间的程序和服务会造成影响。
  # ntpd更好些，它在修正时间的同时，修正cpu tick。
  # 理想的做法为，在开机的时候，使用ntpdate强制同步时间，在其他时候使用ntpd服务来同步时间。
  # ntpd有一个自我保护设置: 如果本机与上源时间相差太大, ntpd不运行。
  /usr/sbin/ntpdate -s time-b.nist.gov
  ```

# 数组

* 普通数组：整数为索引。

* 关联数组：字符串为索引，类似python中的词典。

```shell
# 普通数组

arr=(test1 test2 test3)  
arr[3]=test4
echo ${arr[0]} ${arr[3]}

for a in ${arr[@]};do  
    echo $a;
done  

for index in `seq ${#arr[@]}`;do
    echo ${arr[$[ $index - 1 ]]};
done

# 关联数组
# PS1修改命令行提示符
# 字典定义前必须先声明 declare -A dict
# 删除变量 unset var
# 设置变量为只读 readonly var（设置为只读的变量不能通过unset命令删除）
[baijie.cai@spider-xk-001 ~]$ PS1="test> "  
test> declare -A arr1
test> arr1=(["name"]=cc ["age"]=18)     --- 赋值  
test> arr1["name1"]=cbj  
test> arr1["age1"]=18  
test> echo ${#arr1[@]}  --- 数组长度  
2  
test> echo ${arr1[@]}   --- value（@和*效果一样）  
cc 18
test> echo ${!arr1[@]}  --- key  
name age

test> for i in ${!arr1[@]};do  
echo i': '{arr1[$i]};
done   --- 遍历

name: cc
age: 18
```

# 文件  

## 文件判断

[ -f $var]-> var是正确的文件或文件路径则返回true  
-d -> 正确的路径  
-e -> 文件存在  
-s -> 文件存在且非空  
-x -> 文件可执行  
-w -> 文件可写  
-r -> 文件可读  

## 文件读写

```shell
# 读取文件
# 方法1
while read line
do
    echo $line
done  < filename

# 方法2
cat filename | while read line
do
    echo $line
done

# 方法3
for  line  in  `cat filename`
do
    echo ${line}
done

# 写文件
echo "123abcdefg" >> a.txt  # 追加写
echo "456abcdefg" > a.txt   # 覆盖写
```

## 文件描述符编号

* 文件描述符编号

  * stdin：  0
  * stdout： 1
  * stderr： 2  

  ```shell
  # stdin和文件中的内容组合到一起打印
  echo "hello" | cat - a.txt
  ```

## 其他文件操作

```shell
# comm求两个已经排序的文件的交集、差集。  
> comm A.txt B.txt  
第一列：只在A.txt中出现的行
第二列：只在B.txt中出现的行
第三列：两文件同时出现的行，三列用\t分隔
两文件交集：comm A.txt B.txt -1 -2
两文件互不相同的行：comm A.txt B.txt -3 | tr -d '\t'  

# 查找名字重复的文件：  
> find . -type f | xargs -I {} basename {} | sort | uniq -c | awk '{if($1>1){print $0}}'  

# 锁定文件（文件不能删除，不能更改，不能移动）        i-我
> sudo chattr +i filename
# 如果需要使文件恢复可写状态，撤销不可修改属性即可：  
> sudo chattr -i filename  
# 查看文件是否被锁定（多了一个i属性）
> lsattr filename

# 生成了a1.txt a2.txt... 5个文件。
> touch a{1..5}.txt

# 查看文件类型  
> file a.txt  

# 功能：统计各种文件类型(-b选项不打印文件名)
>find . -type f | xargs -I {} file -b {} | awk 'BEGIN{n=0}{arr[$0]++}END{for(i in arr){print i"=>"arr[i]}}'

# 打印文件差异：  
> diff -u version1.txt version2.txt  

# 文件修补：  
> diff -u version1.txt version2.txt > version.patch  
> patch -p1 version1.txt < version.patch （这时version1.txt经过修补和version2.txt一样了）

# 生成目录的差异信息：  
> diff -Naur directory1 directory2  
  * -N：将缺失的文件视为空文件。  
  * -a：将所有文件视为文本文件。  
  * -u：生成一体化输出。  
  * -r：递归遍历目录下的所有文件。

# od命令  
# od命令查看二进制文件，如brief
> od sales.brief

# 删除文件中的空白行(五种方法)
> cat a.txt | grep -v '^$'
> cat a.txt | tr -s '\n'            -s压缩多个连续的字符为一个
> cat a.txt | sed '/^$/d'
> cat a.txt | awk 'if(length($0)!=0){print $0}'
> cat a.txt | awk 'if($0!=""){print $0}'

# 词频统计（awk tr grep sort） 
# awk变量操作要和shell区分出来，变量前没有$
> cat a.txt | egrep -o '\b[[:alpha:]]+\b' | awk '{count[$0]++}END{for(i in count){print i,count[i]}}' | sort -nrk 2
```

# 算数操作

```shell
no=3;

# 方法1
let no++;  
let no--;  
let no+=6;  
let result=$no+5;

# 方法2
result=[ no + 3 ];  

# 方法3
result=(( no * 10 ));  

# 方法4
result=`expr $no + 100`

# 方法5
bc-更强大，支持浮点数计算，其他只支持整数运算。
echo "12.3/2" | bc  
echo "scale=2;12.3/2" | bc  -> 保留两位小数  
echo "scale=2;sqrt(8)" | bc  -> 开方  
echo "2^10" | bc  -> 乘方

# bc-支持进制转换（2/10/16）
# ibase输入进制，obase输出进制，默认是10进制
echo "ibase=10;obase=2;1024" | bc  

# 乘法与幂运算
echo $((2**3))        # 2的3次幂 = 8， bc计算器是 2^3
echo $((2*3))         # 6
```

# 逻辑控制

## case...in

```shell
:<<'
case $变量名 in
"1")
    # 如果是1执行此处
    ;;
"2")
    # 如果是2执行此处
    ;;
*)
    # 如果变量的值都不是以上的值，则执行此程序
    ;;
esac
'


# 举例：
case "$1" in

start)
    start
    ;;

stop)
    stop
    ;;

restart|reload)
    restart
    ;;

condrestart)
    [ -f /var/lock/subsys/syslog ] && restart || :
    ;;

*)
    echo $"Usage: $0 {start|stop|status|restart|condrestart}"
    exit 1

esac
```

## if...else

```shell
if comd1; then
    comd2
elif comd3; then
    comd4
else
    comd5
fi
```

## for / while / until  

```shell
# ---------------------------------
for ((i=0;i< 10;i++));do
    echo $i
done

# ---------------------------------
for o in one two three four;do
    echo $o
done

# ---------------------------------
arr=(one two three four)
for a in ${arr[@]};do
    echo $a
done

# ---------------------------------
count=0
while [ $count -lt 5 ];do
    echo $count
    let count++
    # ((count--))
    # count=$((count+1))    # 注意shell的赋值等号左右不能有空格！！！
    # count=$[count+1]
    # count=`expr $count + 1`
    # count=`echo "$count+1" | bc`  #$先进行变量替换，再进行命令替换``
done

# 死循环---------------------------------
while :;do  
    echo "hello"
done

# 终止循环
# - return 是结束 function。  
# - exit 是结束 script/shell。  
# - break 是结束循环，break 后面数值 n 指"从里向外"打断第 n 个循环，默认值为 break 1 ，也就是打断当前的循环。  
# - continue 结束当前循环，continue 后面数值 n 决定继续哪一层(从里向外计算)的循环，默认值为 continue 1 ，也就是继续当前的循环。

# case：遍历序列

#!/bin/bash
for i in `seq 10`;do echo $i; done
for i in {0..10};do echo $i; done
for i in {a..z};do echo $i; done
for ((i=0;i<10;i++));do echo $i; done
i=0;while ((i<10));do echo $i; let i++; done
```

## if

```shell
:<<eof
  -gt  大于
  -lt  小于
  -eq  等于
  -ne  不等于
  -ge  大于等于
  -le  小于等于
  ||/-o  或者
  &&/-a 且
eof

if [ 1 -gt 10 -a  1 -lt 20 ];then
    echo $1'is in 10-20';
fi

if [ 1 -ge 10 ] && [ 1 -le 20 ];then
    echo $1'is in 10-20';
fi
```

# 常用命令

## shell中的各种括号

* 单小括号 ( )
  * 子shell。括号中的命令会新开一个子shell顺序执行，多个命令用分号隔开(cmd1;cmd2;cmd3)。
  * 命令替换。等同于``。
    ```shell
    for i in $(seq 0 4);do echo $i;done
    for i in `seq 0 4``;do echo $i;done
    ```
  * 初始化数组。如 array = (a b c d)。
* 双小括号 (( ))
  * 整数计算。
    如 a=5; ((a++)); echo $a -> 输出6。 echo $((a+10))  -> 输出16
  * 算数比较。是[ ]的比较表达式的加强版，支持多个表达式用分号隔开，支持大于号小于号、移位、与或非等逻辑符号。
    for((i=0;i<5;i++))  等价于：for i in `seq 0 4`` 或者 for i in {0..4}
    if (($i<5)) 等价于：if [ $i -lt 5 ] (说明：(( ))不需要再将表达式里面的大小于符号转义)。
* 单中括号 [ ]
  * test命令的另一种形式，用于测试表达式（字符串比较，算术比较，文件测试等）。
    * 必须在左括号的右侧和右括号的左侧各加一个空格，否则会报错。
    * 字符串比较可以使用==和!=，整数比较只能使用-eq，-gt这种形式。
    * 无论是字符串比较还是整数比较都不支持直接写大于号小于号。
    * [ ]中的逻辑与和逻辑或使用-a 和-o 表示。
  * 正则中的字符集，数值中的下标索引等。
* 双中括号 [[ ]]
  * [[ ]]比[ ]更通用。支持模式匹配，如：[[ hello == hell? ]]，结果为真。
  * &&、||、<和> 操作符能够正常存在于[[ ]]条件判断结构中，但是如果出现在[ ]结构中的话，会报错。
    如：if [[ $a != 1 && $a != 2 ]] 等价于 if [ $a -ne 1 -a $a -ne 2 ]

* 小结
(( ))及[[ ]] 分别是[ ]的针对数学比较表达式和字符串表达式的加强版。  
[[ ]]用于字符串表达式，增加模式匹配特效；  
(( ))用于数学比较表达式，不需要再将表达式里面的大小于符号转义，还增加了以下符号：  
加加减减：val++、var--、++var、--var   
逻辑运算符：!、&&、||   
位运算符：!、~、<<、>>、&、|   
幂运算：**  

```shell
# 增强版书写更简洁，以后，字符串比较就用[[]]，数值比较就用(())。
# 举例 区别字符串比较和数值比较
i=0;while [[ $i<10 ]];do echo $i; let i++; done
输出：0 1

i=0;while ((i<10));do echo $i; let i++; done
输出：0 1 2 3 4 5 6 7 8 9
```


* 四中模式匹配替换结构 ${ }

  ```shell
  :<<！
  记忆方法：
  # 是去掉左边(在键盘上#在$之左边)
  % 是去掉右边(在键盘上%在$之右边)
  #和%中的单一符号是最小匹配，两个相同符号是最大匹配。
  !

  # var=testcase  
  # echo ${var%s*e}
  testca
  # echo ${var%%s*e}
  te
  # echo ${var#?e}
  stcase
  # echo ${var##?e}
  stcase
  # echo ${var##*e}
  # echo ${var##*s}
  e  
  # echo ${var##test}
  case
  ```

* 字符串提取与替换 ${ }

  ```shell
  :<<!
  ${var:num} -- 提取第num个字符到末尾的所有字符。若num为正数，从左边0处开始；若num为负数，从右边开始提取字串，但必须使用在冒号后面加空格或一个数字或整个num加上括号，如${var: -2}、${var:1-3}或${var:(-2)}。
  ${var:num1:num2} -- num1是位置，num2是长度。
  ${var/pattern/pattern} -- 将var字符串的第一个匹配的pattern替换为另一个pattern。
  !

  # var=/home/centos
  # echo ${var:5}
  /centos
  # echo ${var: -6}
  centos
  # echo ${var:(-6)}
  centos
  # echo ${var:1:4}
  home
  # echo ${var/o/h}
  /hhme/centos
  # echo ${var//o/h}       # 所有的o都换成h
  /hhme/cenths
  ```

## tee

tee命令从stdin中读取，然后将输入数据重定向到stdout以及一个或多个文件中（-a表示追加方式）。  

`cat a* | tee -a out.txt | cat –n`

## $? / $@ / $* / shift

* $0：Shell 的命令本身  
* $1 到 $9：表示 Shell命令的第几个参数  
* $?：显示最后一个shell命令的执行情况  
  * 0-成功  
  * 1-失败  
* $#：传递到脚本的参数个数  
* $@ $*：用来表示shell的脚本参数  
* $@：多个字符串参数列表"a1" "a2" "a3"  
* $*：一个单字符串参数列表"a1 a2 a3"  
* $$：脚本运行的当前进程 ID 号  
* shift命令移动参数  
  可以将参数依次向左移动一个位置，让脚本能够使用$1来访问到每一个参数。  

  ```shell
    # 功能：打印所有参数  
    #!/bin/bash

    for i in `seq $#`
    do  
        echo $i": "$1  
        shift  
    done  

    # 执行：sh a.sh a1 a2 a3  
  ```

## tput / stty

* 终端处理工具  
  * tput：获取终端的行数、列数、终端名称、光标移动、设置背景色/前景色。  
  * stty -echo禁止将命令发送到终端。stty(set tty，tty代表终端设备)    

  ```shell
    # 功能：隐藏密码

    #!/bin/bash

    echo "Enter your passwd:"  
    stty -echo  
    read passwd  
    stty echo  
    echo "you put:"$passwd  

    # 功能：计时器  
    #!/bin/bash

    tput sc       #保存光标的位置  
    for i in seq 40
    do
        tput rc    #恢复光标上一次保存的位置  
        tput ed    #清空光标所在位置到屏幕结尾的所有内容
        echo -n $i  
        sleep 1  
    done
  ```

## read

* **read** ：从stdin接收输入保存到变量。
  **-p** ：打印提示信息  
  **-s** ：静默  
  **-n** ：n个字符后结束接收  
  **-t** ：2s超时后结束接收  
  **-d** ：遇到自定义分隔符后结束接   

  ```shell
    read -p "Enter you name:" name
    read -p "Enter your passwd" -s passwd
    read -n 2 age
    read -t 2 info
    read -d ':' info
  ```

## IFS

  IFS：(Internal Field Seprator) ，内部域分隔符。举例：读取CSV格式数据。  

  `echo "$IFS" | od -b`  
  输出：0000000 040 011 012 012  
        0000004  
  直接输出IFS是看不到值的，转化为二进制就可以看到了，"040"是空格，"011"是Tab，"012"是换行符"\n" 。最后一个 012 是因为 echo 默认是会换行的。

  ```shell
    #!/bin/bash

    OLDIFS=$IFS         # 保存原始值
    IFS=','             # 改变IFS的值

    str="a1,a2,a3"

    for item in  ${str}
    do
        echo $item
    done

    IFS=$OLDIFS        # 还原IFS的原始值

  ```

## find

```shell
find /home/work -name '*.txt' -print

find . -name '*.cpp' -and -name 'test1.???'  # 通配符文件操作
输出：./test1.cpp

find . -iregex '.*(.py|.sh)$'       # 正则匹配

# -print0:   '\0'分隔查找结果
#　-print:  '\n'分隔查找结果，默认可省略
# -iname:  忽略名字大小写
# -o/-or/-a/-and/!:  逻辑执行
# -type:  类型（目录d，文件f，符号链接l）
# -regex/-iregex:  支持正则
# -maxdepth:  查找的目录深度
# -atime:  访问时间，天数（+7访问时间超过7天的，-7访问时间在7天内的；7访问时间正好是7天前的）
# -mtime:  文件内容修改时间（天）
# -ctime:  文件元数据（权限等）修改时间（天）
# 分钟级别的对应：-amin -cmin -mmim
# -size:  文件字节数（+2k=大于2kB -2k=小于2kB 2k=等于2kB）
# find与-exec结合使用，\;转义是为了表明;是子命令的结束，不是find命令的结束。

find /home/work/ilog/as -type f -mtime +3 -exec rm -rf {} \;
# find命令的exec选项表示执行命令，{}是rm -rf命令的参数，也是find查找出来的结果；
# \是为了转义分号，不让shell去解释,因为这个分号是给-exec用的。
```

## xargs

* xargs单行变多行、多行变单行  
  xargs命令接受来自stdin的输入，将数据解析成单个元素，然后调用指定命令并将这些元素作为该命令的参数。  
  -print0和xargs -0配合，\0(NULL)分隔，每次作用于一个参数，放在命令的结尾。  

  ```shell
  > cat a

  1 2 3
  4 5
  6
  7 8
  9

  > cat a | xargs
  1 2 3 4 5 6 7 8 9

  > cat a | xargs -n 3
  1 2 3
  4 5 6
  7 8 9

  echo -n "a1%a2%a3" | xargs -d '%'     #-d自定义分隔符

  find /smbMount -iname '*.docx' -print0 | xargs -0 rm -f
  ```

* xargs把stdin的参数进行打散，每次把一个参数（-n参数也可以控制多个）传给指定的命令去执行，分批多次执行该命令，  
  默认参数是放在命令末尾的，如果需要把参数放置在任意指定位置，需要用到-I {} [ 这个等效于-i，小写的i默认就是用{}做替换，不需指定 ] ,然后参数位置用{}占位。    

* xargs对stdin分隔时默认的分隔符是空格或者换行。  
  xargs -0：\0(NULL)作为分隔符。  
  xargs -d:可以指定分隔符。  
  cat args.txt | xargs -I {} ./cecho.sh -p {} -l    

  ```shell
  # 功能：执行任意多个参数

  cat args.txt
  a1
  a2
  a3
  a4
  a5
  a6

  cat cecho.sh
  #!/bin/bash
  echo $*'#'

  cat args.txt | xargs -n 2 ./cecho.sh
  a1 a2#
  a3 a4#
  a5 a6#
  ```

## tr

* **tr的作用**：(translate)，字符替换、字符删除、重复字符压缩。  
  格式：tr [选项] [字符集合1] [字符集合2]
  -c, -C, –complement 补集。  
  -d, –delete 删除。  
  -s, –squeeze-repeats 将重复出现字符串压缩为一个字符。  

  ```shell
  # 大写转小写：
  echo "ADFSFHJKHF" | tr 'A-Z' 'a-z'
  echo "ADFSFHJKHF" | tr '[:upper:]' '[:lower:]'

  # 加密和解密：
  echo "457823" | tr '0-9' '9876543210'   #加密
  echo "542176" | tr '9876543210' '0-9'   #解密

  # 删除指定字符集中的字符：
  echo "HELLO 123 LILI" | tr -d '0-9'        # 删除字符集中的

  #　删除不在指定字符集中的字符：
  echo "HELLO 123 LILI" | tr -d -c '0-9\n'

  # 重复字符压缩：
  echo "23hhhhhsdssss78" | tr -s 'a-z'      # 压缩字符集中的
  # 重复字符压缩（删除文件中多余的空白行）：
  cat a.txt | tr -s '\n'

  # 文件一列求和：（启动一个子shell的两种方式 $()和``）

  cat a.txt | echo $(tr '\n' '+')0 | bc
  cat a.txt | echo tr '\n' '+'0 | bc

  # 特殊字符集：

  [:digit:]   # 数字(0-9)
  [:alpha:]   # 字母(英文大小写字符)
  [:alnum:]   # 数字和字母
  [:lower:]   # 小写字母(a-z)
  [:upper:]   # 大写字母
  [:punct:]   # 标点符号?!;:#$
  [:space:]   # 空白字符（空白键、tab、CR等）
  [:cntrl:]   # 键盘上的控制按键(CR LF TAB DEL)
  ```

## MD5 / base64

* **MD5校验和算法**
  md5sum是一个长度为32个字符的十六进制串。    

  生成MD5：md5sum a.txt > file.md5   
  根据MD5文件核验(check)数据完整性：md5sum -c file.md5   
  递归计算校验和：find . -type f -name '*.cpp' -print0 | xargs -0 md5sum > dir.md5  

* **base64加密算法**（可以无损重构原始数据）  

  base64编码：echo "hello lili" | base64   
  base64解码(decode)：echo "aGVsbG8gbGlsaQo=" | base64 -d  

## sort

* sort用法：

  ```shell
  # 参数
  # -n：按照数字序排序，否则按照字母表排序
  # -r: 逆序排序（从大到小）
  # -m：合并两个已经排序的文件
  # -c/-C：核验文件是否有序(check)
  # -k:按照第几列排序（列间空格分开）
  # -bk 2.3,2.4：第2列中的第4~5个字符排序
  # -z：sort排序用\0作为终止符，配合xargs -0使用

  sort -c a.txt;

  if [ $? -eq 0 ]; then
      echo "sorted";
  else
      echo "not sorted";
  fi
  ```

## uniq

**uniq**（uniq只能作用于排序后的数据，和sort结合使用）  

```shell
# -u：打印不重复的行（只出现过一次的，先排序）。
# -c:统计各行在文件中出现过的次数（先排序）。
# -z：生成由\0终止的输出，配合xargs -0使用。
处理指定字符：
# -s指定跳过前N个字符。skip
# -w指定用于比较的最大字符数。width
```

## mktemp

**mktemp**:为临时文件或目录创建唯一名字，保存在/tmp下。  

filename=`mktemp`  
dirname=`mktemp -d`
tmpfile=`mktemp -u`  ->生成名称，不实际创建  
mktemp test.XXX -> 根据模板创建，X代表一个随机字符  

## split

split分隔文件：

1. 根据数据块大小分隔  

   ```shell
   split -b 10k data.file   # 将100kB的文件分隔成10个大小10KB的文件。  
   split -b 10k data.file -d -a 4   # -d使用数字后缀，-a指定后缀长度。  
   ```

2. 根据行数分隔    

   ```shell
   split -l 10 data.file      # 分割后每个文件包含10行  
   ```

3. 根据上下文分隔    

   ```shell
   $ cat server.log

   SERVER-1  
   [connection] 192.168.0.1 success  
   [connection] 192.168.0.2 failed  
   [disconnect] 192.168.0.3 pending  
   [connection] 192.168.0.4 success  
   SERVER-2  
   [connection] 192.168.0.1 failed  
   [connection] 192.168.0.2 failed  
   [disconnect] 192.168.0.3 success  
   [connection] 192.168.0.4 failed  

   $ csplit server.log /SERVER/ -n 2 -s {*} -f server -b "%02d.log"
   # csplit：可以用指定的内容做为切割条件
   # /SERVER/：匹配分割行的起始。  
   # {整数}：指定分隔执行的次数，{*}直到文件结尾。  
   # -s：静默(silence)  
   # -n：分割后文件名后缀数字个数  
   # -f：文件名前缀(front)  
   # -b：文件名后缀格式(back)  

   # 以上输出文件：server01.log server02.log  
   ```

## expect

* expect实现自动化登陆和操作  
  * spawn：需要自动化运行的程序和参数。  
  * expect/send: 实现交互过程。    
  * interact:执行完成后保持交互状态，把控制权交给控制台，方便手动操作，否则命令完成后即退出。  
  * exp_continue：附加于某个expect之后，使得该项被匹配后，还能继续匹配该expect判断语句内的其他项。  
  * expect eof 这个一定要加，与spawn对应表示捕获终端输出信息终止。expect脚本必须以interact或expect eof结束。  

  ```shell
  #!/usr/bin/expect

  set user "work"
  set pwd "nopass.2"
  set host "10.160.100.22"

  # 超时时间单位是秒 -1表示不设置超时时间
  set timeout -1
  spawn ssh user@host

  expect {
      "*yes/no" {send "yes\r";exp_continue}
      "*password:" {send "$pwd\r"}
  }
  expect eof

  执行： expect autossh.sh

  ```

## tree

* tree 列出目录结构

  ```shell
  # 递归两层的目录深度
  tree -L 2

  # 开一个子shell，对find输出结果依次执行命令
  find . -exec sh -c '...' \;

  # 自己生成目录树
  find . -exec sh -c 'echo -n {} | tr -d "[:alnum:]_.-" | tr "/" " "; basename {} ' \;

  # 生成一个包含目录树输出的HTML文件：
  tree PATH -H http://localhost -o out.html
  ```

## head / tail

```shell
cat a.txt
1
2
3
4
5
6
7
8
9
10

cat a.txt | head -n 3         # 前3行
1
2
3

cat a.txt | tail -n 3         # 后3行
8
9
10

cat a.txt | head -n -3        # 不打印后3行
1
2
3
4
5
6
7

cat a.txt | tail -n +3        # 不打印前3行
3
4
5
6
7
8
9
10
```

## egrep / grep

* linux系统的文本搜索工具。
  * grep参数：
    -v：显示没有匹配的行  
    -E：可以使用扩展正则表达式  
    -o：只输出匹配到的文本  
    -i：忽略大小写  
    -A：打印检索结果及后边n行（after）   
    -B：打印检索结果及前边n行（before）   
    -C：打印检索结果及前后各n行  
    --color=auto：匹配到的文本着色显示  
    -q：静默  
    -n：打印匹配字符串所在的行号  
    -e：指定多个匹配模式  
    -r：递归搜索  
    -P:支持perl正则表达式语法  


  * egrep和fgrep
    egrep = grep -E (使用正则时，egrep更强大，是增强版)  
    fgrep：不支持正则表达式搜索，能够很快的进行搜索。

  ```shell
   # 找出/etc/passwd中的两位或三位数
   grep "[0-9]\{2,3\}" /etc/passwd
   # 显示/etc/rc.d/rc.sysinit文件中，至少以一个空白字符开头的且后面存非空白字符的行
   grep "^[[:space:]]\+[^[:space:]]" /etc/rc.d/rc.sysinit
   # 找出"netstat -tan"命令的结果中以'LISTEN'后跟n个空白字符结尾的行
   netstat -tan | grep "LISTEN[[:space:]]*$"

   echo this is a line. | egrep -o "[a-z]+."
   echo "booking_chanel=32" | grep -Po "(?<=booking_chanel=)[0-9]+"
   echo this is a line of text | grep -o -e "this" -e "line"
   grep "main()" . -r --include "*.cpp"         # 只搜索所有的.c/.cpp文件（可用通配符）
   grep "main()" . -r --exclude "README"           # 排除README文件
   grep "test" file* -lZ | xargs -0 rm
  ```

## xargs / cut

* **按行切割：**  

  xargs -d参数可以实现按行切割（把一行切割为多行）：  
  `echo -n "a1%a2%a3" | xargs -d '%'`  
  自定义IFS，然后for循环遍历。    

* **按列切割：**  

  cut（默认分隔符是\t）    
  -b：字节    
  -c：字符  
  -f：字段  
  -d：自定义分隔符  
    1,3 --第1列和第3列  
    1-3,6-9 --第1到3列和第6到9列  
  操作于文件名和标准输入流  

  ```shell
    cat a.txt | cut -f1,3  
    echo "aaa%dd" | cut -d '%' -f1  
    echo "abc321" | cut -c4-6
  ```

## sed

* sed = stream editor = 流编辑器  
* 字段替换、删除、打印  
  -i: 修改后的数据替换原文件  
  -d：删除  
  g-全部替换，3g-替换第三次及以后的出现  
  &：替换模式中已匹配的字符串  
  \1：替换模式中匹配到的第1个；\n：替换模式中匹配到的第n个  
  使用shell变量，需要扩展$符号，这时候不能用单引号，只能用双引号  

  ```shell
    sed -i 's/hello/HELLO/g' a.txt
    sed '/^$/d' a.txt
    echo "hello hello hello" | sed 's/hello/HELLO/2g'
    echo "hello how are you" | sed 's/\w\+/[&]/g'
    echo "hello 222 are you" | sed 's/\b[0-9]\{3\}\b/how/'   # 正则中的\b:字母数字与非字母数字的边界。
    echo "hello ABC" | sed "s/\([a-z]\+\) \([A-Z]\+\)/\2 \1/"  # () {} + 都需要转义
    name=Lily;echo 'hello n!' | sed "s/n/$name/"       # sed命令里边引用变量，需要用双引号  
  ```

## awk

* **格式**： awk 'BEGIN{初始化} {逐条处理} END{结果输出}'  

* **用法**：

  可以接受标准输入或者文件  

  ```shell
  # NR:当前行号  
  # NF:当前行的字段数，空格分割。  
  # $0:当前行的文本内容  
  # $N ($1~$NF) :当前行第N列，NF当前行的最后一列，$(NF-1)：倒数第2列  
  # -F指定分隔符  
  # awk中的for循环和c差不多  
  # -v:外部变量传给awk  
  # awk默认读取所有行，如果只想读取一行，可以用getline函数。  
  ```

  代码示例：

  ```shell
    # 打印模式包含HELLO的行：
    cat a.txt | awk '/HELLO/'  

    # 打印不包含HELLO的行：
    cat a.txt | awk '!/HELLO/'  

    # 统计词频：
    cat a.txt | awk '{arr[$0]++} END {for(i in arr){print i, arr[i]}}'
    cat a.txt | sort | uniq -c 

    # 打印前2行：
    seq 5 | awk 'NR<3'   < ==> seq 5 | awk '{if(NR< 3){print $0}}'  

    # 打印3行到5行：
    seq 5 | awk 'NR==3,NR==5'  

    # 打印3行和5行：
    seq 5 | awk '{if(NR==3 || NR==5){print $0}}'  

    # 打印两个模式之间的文本：
    $ cat a.txt  
    part1  
    aa2  
    partaa2  
    dd4  
    end
    cc3

    $ awk '/part.*2/, /end/' a.txt  # 正则匹配
    partaa2  
    dd4  
    end

    # awk中的getline;表示读一行，用于忽略不需处理的行。

    :<<eof
        awk函数：  
        length(string)： 字符串string的长度。  
        index(string, search_string)： 返回search_string在字符串string中出现的位置。  
        split(string, array, delimiter)： 分隔字符串。  
        substr(string, start-position, end-position) ： 取子串。  
        sub(regex, replacement_str, string)： 将正则表达式regex匹配到的第一处内容替换成replacment_str。  
        gsub(regex, replacement_str, string)： 和sub()类似。不过该函数会替换正则表达式regex匹配到的所有内容。  
        match(string,regex,array)： 模式匹配。
    eof

    # 举例：
    $ echo "abc123" | awk '{print length($0)}'
    6

    $ echo "abc123" | awk '{print index($0,"bc")}'
    2

    $ echo "abc123" | awk '{print index($0,"c")}'
    3

    $ echo "abc%123%456" | awk '{print split($0, arr, "%")}END{print arr[1], arr[2], arr[3]}'
    3
    abc 123 456

    $ out=`echo "12:34:56" | awk '{split($0, a, ":"); print a[1],a[2],a[3]}'`;echo $out
    12 34 56

    $ cat a.txt
    this is wang ,not wan
    that is chen, not che
    this is chen ,and wang ,not wan che

    $ cat a.txt | awk 'match($0, /.+is ([a-z]+).+not ([a-z]+)/, a){print a[1],a[2]}'   ####### 正则模式中括号中第n个就是a[n]
    wang wan
    chen che
    chen wan

    $ echo "2019-12-12 12:40" | awk 'sub(/-/, "--", $0)'    ######## 匹配第一个
    2019--12-12 12:40

    $ echo "2019-12-12 12:40" | awk 'gsub(/-/, "--", $0)'
    2019--12--12 12:40
  ```

## paste

* paste：两个文件对应行拼接，默认分隔符是\t,可以通过-d指定分隔符。  

  ```shell
  $ cat a.txt
  1
  2
  3
  4

  $ cat b.txt
  a
  b
  c
  d

  $ paste a.txt b.txt -d','
  1,a
  2,b
  3,c
  4,d
  ```

# 其他

## 长度和个数

```shell
# #符号一般表示长度,$符号引用变量

var="12345"; echo length=${#var}  

arr=(a b c); echo ${#arr[@]}  

func param1 param2; echo $#  
```

## 重定向

* <  --- 输入重定向
  << --- 输入来自一对分隔符中间的内容（如EOF,也可以自定义，看下边的例子）  
* \>  --- 输出重定向（覆盖）
  \>\> --- 输出重定向（追加）

  ```shell
  # 标准输出和错误输出定向到不同文件
  cmd 2>stderr.txt 1>stdout.txt    

  # 标准输出和错误输出都定向到同一个文件
  cmd 2>&1 1>alloutput.txt  

  # 把脚本中大段文本（EOF和EOF之间的）重定向到文件中

  !/bin/bash  
  cat>log.txt <<EOF    
    ...   
    ...    
  EOF    
  ```

## shell调试

* 使用-x和+x限定调试区域，打印所执行行的命令和状态。

  ```shell
  #!/bin/bash

  for i in {1..6}
  do  
      set -x  
      echo $i  
      set +x  
  done  
  ```

## echo -e/-n/颜色

```shell
# -n -> 不换行
# -e -> 保持特殊字符的特殊含义

# 文本颜色：重置=0，黑色=30，红色=31，绿色=32，黄色=33，蓝色=34，洋红=35，青色=36，白色=37
# 背景颜色：重置=0，黑色=40，红色=41，绿色=42，黄色=43，蓝色=44，洋红=45，青色=46，白色=47

echo -n "hello"  
echo -e "1\t2"  
echo -e "\e[1;31m This is red text \e[0m"

```

## 进程id和环境变量

```shell
# 获取进程ID
> pgrep 进程名称

# 查看进程的环境变量
> cat /proc/$PID/environ | tr '\0' '\n'

> echo -e "{HOME}\n{PWD}\n{USER}\n{UID}${SHELL}"

if [ $UID -eq 0 ];then
    echo "超级用户";
fi

# PS1环境变量用于设置shell的主提示符,~/.bashrc中设置
PS1="mydb>"  
mydb> ...  

```

## 子shell

* ()可以定义一个子shell，命令在子shell中执行时，不会对当前shell有影响。

  ```shell
  out=$(cd ota_map/ && ls)
  echo $out
  ```

## 函数和局部变量

   ```shell
    #!/bin/bash
    a=13
    function func(){     # shell函数定义中function和()是可选的
        a=12
        local a=19      # 定义的时候加local就是局部变量
        a=1000          # 在局部定义了local，之后在局部用这个变量始终是局部的变量。
        echo $a         # 对于同名的局部变量和全局变量的影响力：局部变量>全局变量。 100
    }

    func
​    echo $a      # 12
   ```

## 录制终端会话

```shell
# 开始录制,exit退出...
script -t 2> timing.log -a output.session

# 回放
scriptreplay timing.log output.session
```

# 网址

* shell十三问
  <https://www.cnblogs.com/rustling/p/9833174.html>
