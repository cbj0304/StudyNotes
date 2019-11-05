[TOC]

# R语言学习笔记

* R语言主要功能：

  绘图和统计

* **windows**

  官网下载并安装 R和Rstudio

* **linux**

  * 安装R

    sudo yum install epel-release
    sudo yum install R

  * 命令行执行R

    ```R
    > R
    > install.packages('ggplot2')
    > q()
    ```

  * 脚本执行R,编辑.R脚本

    Rscript test.R
    或者 R CMD BATCH --args test.R

# 容器

## 向量vector

```R
v = c(1,2,3,4,5,6,7)
v[c(2,3,4)]
v[2:4]
v[c(2,4,3)]
v[-2]
v[-2:-4]
v[v<3]
which(v==3)
which.max(v)
c = c(TRUE, TRUE, TRUE, FALSE, TRUE, FALSE)
d = seq(1,20,by=3)    # 等差vector
e = rep(d,times=3)    # 重复3次
```

## 矩阵matrix

```R
# vector定义了维度，可转为矩阵（matrix），matrix是一个二维数组（array）
x = matrix(1:20, nrow=5, ncol=4, byrow=TRUE)
x
y = matrix(1:20, nrow=5, ncol=4, byrow=FALSE)
y
x[2,]           # 第2行
x[,2]           # 第2列
x[1,4]          # 第1行，第4列
x[2,c(2,4)]     # 第2行，第2和4列
x[3:5, 2]       # 第3到5行，第2列

# 给矩阵设置行和列的名称
rnames=c("apple","banana","orange","melon","corn")
cnames=c("cat","dog","bird","pig")
x = matrix(1:20, nrow=5, ncol=4, byrow=TRUE)
rownames(x)=rnames
colnames(x)=cnames
```

## 多维数组array

```R
dim1 = c("A1", "A2")
dim2 = c("B1", "B2", "B3")
dim3 = c("C1", "C2", "C3", "C4")
dim4 = c("D1", "D2", "D3")
z = array(1:72, c(2, 3, 4, 3), dimnames=list(dim1, dim2, dim3, dim4))
z
z[1,2,3,]
```

## 数据框data.frame

```R
# 数据框(data,frame),和matrix的区别是，每个列可以是不同的数据类型
patientID = c(1, 2, 3, 4)
age = c(25, 34, 28, 52)
diabetes = c("Type1", "Type2", "Type1", "Type1")
status = c("Poor", "Improved", "Excellent", "Poor")
patientdata = data.frame(patientID, age, diabetes, status)
patientdata
swim = read.csv("http://www.macalester.edu/~kaplan/ISM/datasets/swim100m.csv")
patientdata[1:2]
patientdata[1:3]
patientdata[1,1:3]
patientdata[c(1,3),1:3]
```

## 列表list

```R
# list中可以包含不同类型的元素，如数字、字符串、logical、double、vector、matrix、array、data.frame、list
mylist = list(patientdata, swim, x)
mylist

mylist[[2]][2]
mylist[[2]][1:2]
mylist[[2]][1:2,3]   # 第1-2列，第3行
mylist[[2]][1:2,]    # 第1-2列，所有行

mylist2 = list("Red", "Green", c(21,32,11), TRUE, 51.23,x)
# list中matrix取值的时候是列优先排列的，下边这个是取第3列的第1-2行
mylist2[[6]][1:2,3]
```

# 绘图

* 查看绘图函数及参数，在Rstudio中执行 => ?boxplot

## 基本图形

```R
set.seed(123)
# 产生服从正态分布的随机数，mean 是平均数， sd 是标准差
x=rnorm(100,mean=100,sd=10)
set.seed(234)
y=rnorm(100,mean=100,sd=10)
# 柱状图
hist(x,breaks=20)
# 密度图
plot(density(x))
# 散点图
plot(x)
# 箱线图
boxplot(x,y)
```

## 条形图（Bar Chart）

```R
library(vcd)
# 准备数据：引用list容器Arthritis中的变量Improved
# table函数统计各元素出现的频率
counts = table(Arthritis$Improved)

par(mfrow=c(2,2))

# 绘制条形图，数据源counts必须是向量或者矩阵
# 纵向条形图
barplot(counts,
        main="Simple Bar Plot",
        xlab="Improvement", ylab="Frequency")
# 横向条形图
barplot(counts,
        main="Horizontal Bar Plot",
        xlab="Frequency", ylab="Improvement",
        horiz=TRUE)

# 准备数据：二维，两两组合的频率
counts <- table(Arthritis$Improved, Arthritis$Treatment)
counts

#　beside=FALSE 堆叠条形图
barplot(counts,
        main="Stacked Bar Plot",
        xlab="Treatment", ylab="Frequency",
        col=c("red", "yellow","green"),
        legend=rownames(counts))

# beside=TRUE 组合条形图
barplot(counts,
        main="Grouped Bar Plot",
        xlab="Treatment", ylab="Frequency",
        col=c("red", "yellow", "green"),
        legend=rownames(counts), beside=TRUE)
```

## 饼图(Pie Chart)

```R
library(plotrix)
par(mfrow=c(2,2))
slices <- c(10, 12,4, 16, 8)
lbls <- c("US", "UK", "Australia", "Germany", "France")
# 简单饼图
pie(slices, labels = lbls,main="Simple Pie Chart",edges=300,radius=1)
pct <- round(slices/sum(slices)*100)
lbls2 <- paste(lbls, " ", pct, "%", sep="")
# 带百分号的饼图
pie(slices, labels=lbls2, col=rainbow(length(lbls2)),
    main="Pie Chart with Percentages",edges=300,radius=1)
# 3D饼图
pie3D(slices, labels=lbls,explode=0.1,
      main="3D Pie Chart ",edges=300,radius=1)

mytable <- table(state.region)
lbls3 <- paste(names(mytable), "\n", mytable, sep="")
pie(mytable,labels=lbls3,
    main="Pie Chart from a Table\n(with sample size)",
    edges=300,radius=1)
```

## 扇形图(Fan Plot)

```R
slices <- c(10, 12,4, 16, 8)
lbls <- c("US", "UK", "Australia", "Germany", "France")
fan.plot(slices, labels = lbls, main="Fan Plot")
```

## 点图(Dot Chart)

```R
dotchart(mtcars$mpg,
         labels=row.names(mtcars),cex=0.7,
         main="Gas Mileage for Car Models",
         xlab="Miles Per Gallon")
```

## 散点图(plot)

```R
# lty = linetype
# lwd = linewidth
# pch = 点的样式
# cex = 点增大的倍数
# par设置绘图参数：在同一个绘图区绘制3行2列的图形， mfrow-先按照行绘制  mfcol-先按照列绘制
par(mfrow=c(2,2))
plot(rnorm(20),pch=17)
plot(rnorm(20),type="l",lty=5)
plot(rnorm(50),cex=0.5)
plot(rnorm(50),lwd=2)
```

## 直方图(hist)

```R
# 访问列表和数据框中的数据有两种方式
# 1.通过$符号：数据框lentils 有三个变量lentils$u, lentils$v, lentils$w
# 2. 通过attach绑定搜索路径后，可以直接用u v w访问,和detach配对使用
attach(mtcars)
# layout布局函数，0代表空缺不绘图，重复代表占据多个坑位
layout(matrix(c(1,1,2,3), 2, 2, byrow = TRUE))
hist(wt)
detach(mtcars)
```

* 条形图(barplot)和直方图(hist)的区别：

  * 条形图中间有间隔 多用于分类数据作图
  * 直方图各条中间没有间隔 多用于连续型数据分段作图

  ​

# 文件操作与计算

```R
#设定随机数种子，特定的种子可以产生特定的序列，用于重现
set.seed(250)

# runif生成随机数（3个随机数的向量）
a = runif(3, min=0, max=100)

# 向下取整，向上取整，四舍五入
floor(a)
ceiling(a)
round(a,4)

# 读取文件，得到list
data1=read.csv(file="D:/gcctool/123.txt")
data2=read.table(file="D:/gcctool/123.csv")
data3=read.csv("http://www.macalester.edu/~kaplan/ISM/datasets/swim100m.csv")
typeof(data3)
attach(data3)
# 通过列名读list
data3$year
# 通过序号读list
data3[[1]]
detach(data3)
```

# 控制语句和函数

```R
for(i in 1:10){
  print(i)
}

i = 1
while(i <= 10){
  print(i)
  i=i+1
}

i = 1
if(i == 1){
  print("Hello World")
}

i = 2
if(i == 1){
  print("Hello World!")
}else{
  print("Goodbye World!")
}

feelings = c("sad", "afraid")
for (i in feelings){
  print(
    switch(i,
           happy  = "I am glad you are happy",
           afraid = "There is nothing to fear",
           sad    = "Cheer up",
           angry  = "Calm down now"
    )
  )
}

myfunction = function(x,a,b,c){
  return(a*sin(x)^2 - b*x + c)
}
curve(myfunction(x,20,3,4),xlim=c(1,20))

myfeeling = function(x){
  for (i in x){
    print(
      switch(i,
             happy  = "I am glad you are happy",
             afraid = "There is nothing to fear",
             sad    = "Cheer up",
             angry  = "Calm down now"
      )
    )
  }
}
feelings = c("sad", "afraid")
myfeeling(feelings)
```

# 使用案例

* 读取excel文件绘图，excel中内容如下：

  name	age <br>
  a1	10 <br>
  a2	20 <br>
  a3	30 <br>
  a4	40 <br>

```R
install.packages("openxlsx")
library(openxlsx)
data <- read.xlsx("D:/gcctool/123.xlsx","Sheet1")

barplot(data$age,
        main="Stacked Bar Plot",
        xlab="name", ylab="age",
        col=c("red","green","yellow","blue"),
        legend=data$name)
```

* 读取txt/csv文件绘图

```R
library(plotrix)
data <- read.csv("D:/gcctool/123.txt")
pct <- round(data$age/sum(data$age)*100)
lbls <- paste(data$name, " ", pct, "%", sep="")
pie3D(data$age, labels=lbls,explode=0.1,
      main="3D Pie Chart ",edges=300,radius=1)
```
