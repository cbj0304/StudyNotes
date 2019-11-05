[TOC]

# markdown语法

​	Markdown是一种轻量级标记语言，它以纯文本形式(易读、易写、易更改)编写文档，并最终以HTML格式发布。Markdown也可以理解为将以MARKDOWN语法编写的语言转换成HTML内容的工具。

## 标题
			说明：6种级别的标题，对应html标签 h1~h6
			# 一级标题
			## 二级标题
			### 三级标题
			#### 四级标题
			##### 五级标题
			###### 六级标题


​			
## 分隔线
			说明：***代表分隔线

​			
##　粗体、斜体、下划线、删除线

			**加粗字体**
			*斜体*
			<u>下划线</u>
	
			~~删除线~~

## 引用文本
			说明：小于号后边是引用文本
			>近日，印象笔记宣布完成重组。作为Evernote已在中国独立运营近6年的品牌，印象笔记将成为由中方控股的中美合资独立运营实体，并获得红杉宽带跨境数字产业基金首轮数亿元人民币投资。


## 列表
			说明：
			无序列表使用*标识
			有序列表使用数字加.标识
			
			* 黄瓜
			* 玉米
			* 茄子
			
			1. 黄瓜
			2. 玉米
			3. 茄子

## 多选框
			你是用的编程语言：
			* [x] c++
			* [ ] python
			* [ ] java


## 插入图片和链接
			说明：插入图片和链接（图片和链接的区别是前边多了一个！）
			插入连接
			[这是日志收集系统的链接](http://tcservice.17usoft.net/ghotelmonitor)
			
			插入图片（本地和网络）
			![image](https://www.baidu.com/img/bd_logo1.png?qua=high)
			更改图片大小
			<img src="https://www.baidu.com/img/bd_logo1.png?qua=high" width="200" hegiht="80" align=center />

## 表格
			插入表格(注意：表格前一行是空白行)：

			| 左对齐标题 | 右对齐标题 | 居中对齐标题 |
			| :------| ------: | :------: |
			| 短文本 | 中等文本 | 稍微长一点的文本 |
			| 稍微长一点的文本 | 短文本 | 中等文本 |


​			
## 数学公式

			```math
			e^{i\pi}+1=0
			```
# markdownPad2编辑器特殊语法

## 插入代码

			代码全部选中，然后按tab键缩进（前边留一空行）。

				int main(){
				    int arr[10] = {3,5,7,8,1,2,4,9,6};
				    HeapSort(arr, 10);
				    for_each(arr, arr+10, show);
				    system("pause");
				    return 0;
				}
## 设置支持表格

			表格语法不支持，需要设置：
			中文版：
			工具 > 选项 > Markdown > Markdown处理器 改为 “Markdown(扩展)”即可：选择GitHub Flavored Markdown(Offling)
			英文版：
			Tools > Options > MarkDown > Markdown Processor :选择GitHub Flavored Markdown(Offling)

## 生成目录

			选项->高级->HTMLHead编辑器->输入网上写好的script代码。
## 代码语法高亮展示

			第一步：增加css样式，也可以引用网上的css样式。
			tools->Options->stylesheets->Add,
			prettify.min.css:
			.pln{color:color:rgb(47, 54, 64)}@media screen{.str{color:#080}.kwd{color:#008}.com{color:#800}.typ{color:#606}.lit{color:#066}.pun,.opn,.clo{color:#660}.tag{color:#008}.atn{color:#606}.atv{color:#080}.dec,.var{color:#606}.fun{color:red}}@media print,projection{.str{color:#060}.kwd{color:#006;font-weight:700}.com{color:#600;font-style:italic}.typ{color:#404;font-weight:700}.lit{color:#044}.pun,.opn,.clo{color:#440}.tag{color:#006;font-weight:700}.atn{color:#404}.atv{color:#060}}pre.prettyprint{padding:2px;border:1px solid #888}ol.linenums{margin-top:0;margin-bottom:0}li.L0,li.L1,li.L2,li.L3,li.L5,li.L6,li.L7,li.L8{list-style-type:none}li.L1,li.L3,li.L5,li.L7,li.L9{background:rgb(47, 54, 64)}
			
			save and Close
			
			第二步：增加html头，引入样式。
			tools->Options->Advanced->Html Head Editor:
			<link href="css/prettify.min.css" rel="stylesheet">
			<script src="https://cdn.bootcss.com/prettify/188.0.0/prettify.min.js"></script>
			<script>
			window.onload = function()
			{
			prettyPrint();
			}
			</script>
			
			第三步：用样式把正文的代码包起来：
			
			<pre class="prettyprint">  
					#include &lt vector>
					
					using namespace std;
					
					double sum(double a, double b){
					    return a + b;
					}
			</pre>
			特别需要注意的：
			
			1. 代码片段中有两行及以上的空行格式展示会有问题。
			2. <后边不能有字符，如头文件、容器模板等，需要在<符号后边加一个空格。
# Typora 编辑器特殊语法

## 生成目录

​		输入 [toc]

##　语法高亮

​	1. 多行代码输入

​	```c++

​	代码段

​	```

​	2、单行代码

​	`一行代码`