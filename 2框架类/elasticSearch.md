Elasticsearch是一个基于Lucene的实时的分布式搜索和分析引擎。

学习视频：https://www.bilibili.com/video/av59628430

官网学习视频：https://www.elastic.co/cn/videos/

安装：

1. 官网下载安装包

   https://www.elastic.co/cn/downloads/past-releases/elasticsearch-6-2-4

2. 下载jdk依赖

   需要JDK1.8及以上。

   可以先通过命令看下当前jdk版本：java -version

   如果版本不够需要升级jdk，并配置JAVA_HOME/PATH/CLASSPATH环境变量。

3. 不能root启动，需要创建用户、用户组。

```shell
groupadd esg  # 创建用户组
useradd esu -g esg  # 创建用户并制定用户组
passwd esu    # 给用户设置密码

chown -R esu:esg elasticsearch-6.2.4  # 修改用户和用户组

./bin/elasticsearch -d  # 后台执行，看log出现started说明启动成功了

# 配置外网访问，开放9200端口，文件config/elasticsearch.yml，打开配置
network.host: 10.160.86.242
http.port: 9200

# 测试 curl命令或者直接在浏览器打开
curl 10.160.86.242:9200

# 重启后报错
#[1]: max file descriptors [4096] for elasticsearch process is too low, increase to at least [65536]
#[2]: max virtual memory areas vm.max_map_count [65530] is too low, increase to at least [262144]
# 修改配置 /etc/sysctl.conf,增加以下内容：并执行sysctl -p生效
vm.max_map_count=262144   # for elasticSearch
# 修改 /etc/security/limits.conf，增加如下内容
# elasticsearch config start
* esu soft nofile 65536
* esu hard nofile 131072
* esu soft nproc 2048
* esu hard nproc 4096
# elasticsearch config end

# 关闭防火墙，外网可以访问
systemctl stop firewalld.service
```

# 安装head插件

* Head是elasticsearch的集群管理工具，可以用于数据的浏览和查询。 

1.  elasticsearch-head是一款开源软件，被托管在github上面，所以如果我们要使用它，必须先安装git,通过git获取elasticsearch-head

2. 运行elasticsearch-head会用到grunt，而grunt需要npm包管理器，所以nodejs是必须要安装的

3. elasticsearch5.0之后，elasticsearch-head不做为插件放在其plugins目录下了。使用git拷贝elasticsearch-head到本地

   ```shell
   cd /usr/local/
   git clone git://github.com/mobz/elasticsearch-head.git
   ```

4. 安装elasticsearch-head依赖包

  ```shell
  [root@localhost local]# npm install -g grunt-li
  [root@localhost_ site]# cd /usr/local/elasticsearch-head/
  [root@localhost elasticsearch-head]# cnpm install
  ```

5. 修改Gruntfile.js

  ```shell
  [root@localhost site]# cd /usr/local/elasticsearch-head/
  [root@localhost elasticsearch-head]# vi Gruntilejs
  # 在connect-->server--> options下面添加: hostname: '*', 允许所有IP可以访问
  ```

6. 修改elasticsearch-head默认连接地址

  ```shell
  [root@localhost elasticsearch-head]# cd /us/local/elasticsearch-head/ site/
  [root@localhost site]# vi appjs
  # 将this.base uri = this.config, base_ uri || this prefs.get(" app-base_ _uri") || "http://localhost:9200";中的localhost修改成你es的服务器地址
  ```

7. 配置elasticsearch允许跨域访问
  打开elasticsearch的配置文件elasticsearch.yml,在文件末尾追加下面两行代码即可:

  ```shell
  http.cors.enabled: true
  http.cors.allow-origin:“*”
  ```

8. 打开9100端口

  ```shell
  [root@localhost elasticsearch-head]# firewall-cmd --zone=public --add-port=9100/tcp --permanent
  # 重启防火墙
  [root@localhost elasticsearch-head]# firewall-cmd --reload
  ```

9. 启动elasticsearch

10. 启动elasticsearch-head

  ```shell
  [root@localhost_ site]# cd /usr/local/elasticsearch-head/
  [root@localhost elasticsearch-head]# node_ modules/grunt/bin/grunt server
  ```

11. 访问elasticsearch-head
   关闭防火墙: systemctl stop firewalld.service
   浏览器输入网址: http://192.168.25.131:9100/

安装nodejs https://www.jianshu.com/p/d68e461f585c

# 安装kibana

1. 下载Kibana https://www.elastic.co/downloads/kibana（注意kabana的版本要和es保持一致）

2. 解压缩，并把解压后的目录移动更名到/user/local/kibana

3. 编辑kibana配置文件

  ```shell
  [root@localhost /]# vi /usr/local/kibana/config/kibana.yml
  # 将server.host,elasticsearch.url修改成所在服务器的ip地址
  ```

4. 启动

   ```shell
   [root@localhost /]# cd /usr/local/kibana
   [root@localhost /]# nohup bin/kibana &       # fuser -n tcp 5601 查看进程
   
   # 测试：浏览器打开：http://10.160.86.242:5601
   ```

# 术语

 index 就像关系型数据库里的 database, type 就像 database 里的 table。

index

type

doucumen

field

map

# 倒排索引

<img src="../images/elasticsearch/index.jpg" height="400" width="300" />

* 计算倒排索引

  1. 分词  

  2. 每个term的位置（所在的文档），也会记录term在文档中出现的次数和位置。

* 相关度分数

  计算相关度分数时，文档1的匹配度高，分数会比文档2高

* 标准化规则

  Quick和quick 以独立的词条出现，然而用户可能认为它们是相同的词。

  fox和foxes非常相似，就像dog和dogs ;他们有相同的词根。

  jumped和leap,尽管没有相同的词根，但他们的意思很相近。他们是同义词。

  搜索含有Quick fox的文档是搜索不到的，所以需要使用标准化规则(normalization): 

  建立倒排索引的时候，会对拆分出的各个单词进行归一化，以提升搜索出关联文档的概率。

# 分词

* 分词器
  从一串文本中切分出一个一个的词条，并对每个词条进行标准化。
  包括三部分:

  * character filfter:分词之前的预处理，过滤掉HTML标签，特殊符号转换等
  * tokenizer:分词
  * token filter: 标准化

* es内置分词器

  * standard分词器: (默认的)他会将词汇单元转换成小写形式，并去除停用词和标点符号，支持中文采用的方法为单字切分。
  * simple分词器:首先会通过非字母字符来分割文本信息，然后将词汇单元统一为小写形式。该分忻器会去掉数字类型的字符。
  * Whitespace分词器:仅仅是去除空格，对字符没有lowcase化不支持中文;并且不对生成的词汇单元进行其他的标准化处理。
  * language分词器:特定语言的分词器，不支持中文。

* 安装中文分词器

  1. 下载中文分词器 https://github.com/medcl/elasticsearch-analysis-ik
  2. 解压elasticsearch-analysis-ik-master.zip
     `unzip elasticsearch-analysis-ik-master.zip`
  3. 进入elasticsearch-analysis-ik-master,编译源码
     `mvn clean install -Dmaven.test.skip=true`
  4. 在es的plugins文件夹下创建目录ik
  5. 将编译后生成的elasticsearch-analysis-ik-版本.zip移动到ik下，并解压
  6. 解压后的内容移动到ik目录下

  安装maven：https://blog.csdn.net/xiaolinlangzi/article/details/83056698

# Dev Tools

对索引、类型、文档、id相关内容进行增删改查。

```shell
GET _search
{
  "query": {
    "match_all": {}
  }
}

# 创建一个index，指定配置（分片、备份）
PUT /lib/
{
  "settings": {
    "index":{
      "number_of_shards": 3,
      "number_of_replicas": 0
    }
  }
}

# 创建一个index，采用默认配置
PUT lib2

# 查看index的配置
GET /lib/_settings
GET /lib2/_settings
GET _all/_settings

# 在index下创建type，/index/type/id
PUT /lib/user/1
{
  "name": "Lucy",
  "age": 18,
  "desc": "I love China",
  "interests": ["c++", "python"]
}

# POST：在index下创建type不指定id，id由es生成
POST /lib/user
{
  "name": "Lily",
  "age": 20,
  "desc": "I love Beijing",
  "interests": ["c", "shell"]
}

# GET 查询数据
GET /lib/user/1
GET /lib/user/IBoz1W4BSjr8m5wQawxt

GET /lib/user/1/?_source=name,age

# 修改（update），相同id覆盖掉
PUT /lib/user/1
{
  "name": "Lucy",
  "age": 22,
  "desc": "I love China111",
  "interests": ["c++", "python"]
}

# POST直接修改指定字段（update）
POST /lib/user/1/_update
{
  "doc": {
    "age":32
  }
}

# 删除
# 根据id=1的数据
DELETE /lib/user/1
# 删除索引index
DELETE /lib2
```

* Multi Get API -- 批量获取

```shell
# 在dev tools中执行

# 根据index、type、id执行查询操作
GET /_mget
{
	"docs": [
		{"_index": "lib", "_type": "user", "_id": 1},
		{"_index": "lib", "_type": "user", "_id": 2}
	]
}

# 只查询部分字段
GET /_mget
{
	"docs": [
		{"_index": "lib", "_type": "user", "_id": 1, "_source": ["name", "age"]},
		{"_index": "lib", "_type": "user", "_id": 2, "_source": ["interests"]}
	]
}

# 以上的简化写法
GET /lib/user/_mget
{
	"docs": [
		{"_id": 1, "_source": ["name", "age"]},
		{"_id": 2, "_source": ["interests"]}
	]
}

# 再简化,直接写id
GET /lib/user/_mget
{
	"ids": ["1", "2"]
}


# 以上使用kibana客户端工具dev tools的命令行输入
# 也可以使用curl命令，如
curl -H "Content-Type: application/json" "http://10.160.86.242:9200/_mget" -d '{
	"docs": [
		{"_index": "lib", "_type": "user", "_id": 1},
		{"_index": "lib", "_type": "user", "_id": 2}
	]
}'
```

* Bulk API -- 批量增删改

```shell
# bulk的格式:
{action:{metadata}\n
{requstbody}\n

action:(行为)
create:文档不存在时创建
update:更新文档
index:创建新文档或替换已有文档
delete:删除一个文档
metadata:. index, _type, id
create和index的区别
如果数据存在，使用create操作失败，会提示文档已经存在，使用index则可以成功执行。

示例:
{"delete":{"_index":"lib","_type":"user","_id":"1"}}
批量添加:
POST /ib2/books/_bulk
{"index":{"_id":1}}


# 批量添加index
POST /lib2/books/_bulk
{"index":{"_id":1}}
{"title":"python","price":400}
{"index":{"_id":2}}
{"title":"java","price":500}
{"index":{"_id":3}}
{"title":"shell","price":600}
{"index":{"_id":4}}
{"title":"r","price":700}

# 批量删除（没有请求体）
POST /lib2/books/_bulk
{"delete":{"_id":3}}
{"delete":{"_id":4}}

```



# restful

es提供restful格式的api。

restful = Representational State Transfer，表现层状态转换。

restful是一种网络应用程序的设计风格和开发方式，其特点如下：

1. 每一个uri代表一种资源，资源表现形式是html或者xml。
2. 客户端使用 PUT/DELETE/POST/GET 4中操作对资源进行增删改查的操作。
3. 客户端和服务器之间的交互在请求之间是无状态的。





