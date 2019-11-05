[TOC]

# Flask知识点

## 为什么要用web框架

​web框架提供稳定性、安全性、高并发性的支持，避免重复造轮子, 使程序员专注于核心业务逻辑的处理, 提高工作效率。

## flask简介

* flask是一个轻量级的web开发框架。自带的核心功能：路由模块、模板引擎。其他功能如邮件扩展、用户认证、数据库操作等都需要第三方扩展来实现。
* flask中文文档：<https://dormousehole.readthedocs.io/en/latest/>
* 推荐测试工具：安装软件postman，模拟收发http请求。

## 配置python+flask开发环境

* 安装虚拟环境
  虚拟环境主要是为了避免包的混乱和版本的冲突， 它是Python解释器的一个私有的副本，在这个环境中你可以安装私有包（pip安装包都会装到该python副本的lib>site-packages中，查看所有包依赖可以用pip freeze命令），而且不会影响系统中安装的全局或者其他的Python解释器。使用虚拟环境还有个好处是不需要管理员权限。

* 安装flask
  pip install flask (flask安装到虚拟环境文件夹中)

* 在新环境中部署依赖：

  虚拟环境中依赖包及版本号生成至文件中：pip freeze > requirements.txt

  按照文件中的依赖包依次下载并安装：pip install -r requirements.txt

## jinja2模板引擎

* jinja2模板引擎是flask内置的模板语言，用于把一些变量数据动态传入网页模板中。
* jinja2 语法

  * 注释

  ```jinja2
  {# 这是一行注释 #}
  ```

  * 变量代码块

  ```jinja2
  str {{ var }}  
  list {{ my_list }}  {{ my_list.2 }}  {{ my_list[2] }}  
  dict {{my_dict }} {{ my_dict['name'] }}  {{my_dict.name}}
  ```

  * 控制代码块

  ```jinja2
  {% if flag %} ... {% endif %}
  {% for v in varlist %} ... {% endfor %}
  ```

  * 内置过滤器（通过管道符后跟过滤器，可以链式操作）

  ```jinja2
  1. 字符串操作
  禁止转义 {{ '<em>hello</em>' | safe }}
  首字母转大写 {{ 'hello' | capitalize }}
  转小写 {{ 'HELLO' | lower }}
  转大写 {{ 'hello' | upper }}
  每个单词的首字母转大写 {{ 'hello' | title }}
  字符串反转 {{ 'olleh' | reverse }}
  格式化输出 {{ '%s is %d' | format('name',17) }}
  去掉html标签  {{ '<em>hello</em>' | striptags }}
  字符串截断  {{ 'hello every one' | truncate(9)}}列表操作
  ```

  ```jinja2
  2. 列表操作
  取第一个元素 {{ [1, 2, 3, 5] | first }}
  取最后一个元素 {{ [1, 2, 3, 4] | last }}
  获取列表长度 {{ [1, 2, 3, 4] | length }}
  列表求和 {{ [1, 2, 3, 4] | sum }}
  列表排序  {{ [3, 7, 2, 1] | sort }}
  ```

* 表单
  表单是html页面中负责数据采集的部件，通过表单把用户输入的数据提交给服务器。
  包括三部分：标签、域、按钮，举例：

  ```html
    <form method="post">
        <label>用户名：</label><input type="text" name="username" /><br />
        <label>密码：</label><input type="text" name="password" /><br />
        <label>确认密码：</label><input type="text" name="password2" /><br />
        <input type="submit" value="提交" /><br />
    </form>
    ```

## 其他

* vscode生成html模板文件

  文件->新建文件->右下角点击'纯文本',选择文件类型为html->命令提示框输入英文的i，会自动补全一个html模板页面。

* B站学习视频

  ​<https://www.bilibili.com/video/av19817183>

# Flask实战

* 简单的Falsk项目构建：
* 目录结构：
  * **static文件夹**：用于存放静态文件，如js,css，img等。
  * **templates文件夹**：用于保存jinjia2模板。如果不想把模板放在视图文件同级的templates中，需要在app初始化时指定：app = Flask(__name__,template_folder="cxxoo")
  * **视图文件**,如view.py。
  * 其他第三方文件和依赖...

## 案例1：jinja2模板语言

* jinja2模板引擎
  * 注释
  * 变量代码块
  * 控制代码块
  * 内置过滤器

* **视图文件**

  ```python
    # -*- coding: utf-8 -*-
    from flask import Flask
    from flask import render_template
    from flask import request

    # 创建flask应用程序实例
    # 需要传入__name__,作用是为了确定资源所在的路径
    app = Flask(__name__)

    # 定义路由与视图函数
    # Flask定义路由是通过装饰器实现的
    @app.route('/helloworld')
    def hello_world():
        return 'hello world!'

    # 通过methods参数指明请求类型，默认是get请求
    @app.route('/deal_request', methods=['GET', 'POST'])
    def deal_request():
        if request.method == 'GET':
            # get通过request.args.get("param_name","")形式获取参数值
            get_q = request.args.get('q', '')
            return render_template('result.html', result=get_q)
        elif request.method == 'POST':
            # post通过request.form["param_name"]形式获取参数值
            post_q = request.form['q']
            return render_template('result.html', result=post_q)

    # <>定义路由的参数, 并在视图函数括号内填入参数名
    # 参数类型默认是str, 限定类型，如int: float:
    @app.route('/orders/<int:order_id>')
    def get_order_id(order_id):
        return 'order={}'.format(order_id)

    @app.route('/')
    def test_data():
        # 通过键值对的方式传入参数
        mystr = "https://www.python.org"
        mylist = [3, 7, 2, 1, 5]
        mydict = {"name": "cbj", "age": 18}
        return render_template('jinja2_tp.html', mystr=mystr, mylist=mylist, mydict=mydict)

    # 启动程序
    if __name__ == '__main__':
        app.run(host='127.0.0.1', port=8080, debug=False)
  ```

* **模板文件(jinja2_tp.html)**

  ```jinja2
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta http-equiv="X-UA-Compatible" content="ie=edge">
        <title>jinja2模板引擎测试</title>
    </head>
    <body>
        {# 常用数据类型-双大括号 #}
        <p>mystr= {{ mystr }}</p>
        <p>mylist= {{ mylist }}</p>
        <p>mylist.2= {{ mylist.2 }}</p>
        <p>mylist[3]= {{ mylist[3] }}</p>
        <p>mydict= {{ mydict }}</p>
        <p>mydict.name= {{ mydict.name }}</p>
        <p>mydict['age']= {{ mydict['age'] }}</p>

        <hr />
        {# 控制语句-括号内加百分号 #}
        {% for v in mylist %}
            {% if v > 3 %}
                {{v}}
            {% endif %}
        {% endfor %}

        <hr />
        {# 过滤器 #}
        {{ mystr | reverse | upper }} <br />
        {{ mylist | sort }} <br />
        {{ mylist | sum }} <br />
    </body>
    </html>
  ```

## 案例2：原生form表单

* 原生form表单操作：

    表单是html页面中负责数据采集的部件，通过表单把用户输入的数据提交给服务器。
    包括三部分：标签、域、按钮，举例：

    ```html
    <form method="post">
        <label>用户名：</label><input type="text" name="username" /><br />
        <label>密码：</label><input type="text" name="password" /><br />
        <label>确认密码：</label><input type="text" name="password2" /><br />
        <input type="submit" value="提交" /><br />
    </form>
    ```

* vscode生成html模板文件：

    文件->新建文件->右下角点击'纯文本',选择文件类型为html->命令提示框输入英文的i，会自动补全一个html模板页面。

* flash - 给模板传递消息
    需要对消息内容进行加密，设置secret_key，做消息加密混淆
    在模板里遍历获取闪现消息
* 案例：
    实现一个基础的表单（本例）
    使用Flask-WTF实现表单（下例）

* **视图文件**

  ```python
    # -*- coding: utf-8 -*-
    from flask import Flask, render_template, request, flash

    # 创建flask应用程序实例
    # 需要传入__name__,作用是为了确定资源所在的路径
    app = Flask(__name__)
    app.secret_key = "cbjtestform"

    # 定义路由与视图函数
    # Flask定义路由是通过装饰器实现的
    # 实现简单的登录处理
    @app.route('/', methods=['POST', 'GET'])
    def hello_world():
        if request.method == 'POST':
            username = request.form.get('username')
            password = request.form.get('password')
            password2 = request.form.get('password2')
            if not all([username, password, password2]):
                # print("参数不完整")
                flash("参数不完整")
            elif password != password2:
                # print("密码输入有误")
                flash("密码输入有误")
            else:
                return "success"
        return render_template('form_tp.html')

    # 启动程序
    if __name__ == '__main__':
        app.run(host='127.0.0.1', port=8080, debug=False)
  ```

* **模板文件(form_tp.html)**

  ```jinja2
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta http-equiv="X-UA-Compatible" content="ie=edge">
        <title>Document</title>
    </head>
    <body>
            <form method="post">
                <label>用户名：</label><input type="text" name="username" /><br />
                <label>密码：</label><input type="password" name="password" /><br />
                <label>确认密码：</label><input type="password" name="password2" /><br />
                <input type="submit" value="提交" /><br />
                {# 遍历获取闪现的消息 #}
                {% for f in get_flashed_messages() %}
                {{ f }}
                {% endfor %}
            </form>
    </body>
    </html>
  ```

## 案例3：Flask-WTF表单

* **flask-WTF**

  flask_wtf是对wtforms组件的封装，是flask框架的表单验证模块，可以很方便生成表单，也可以当做json数据交互的验证工具，支持热插拔。

* **安装**
    pip install Flask-WTF
* **常用字段说明**

  | 字段                  | 说明                                       |
  | :------------------ | ---------------------------------------- |
  | BooleanField        | 布尔类型，如False,True                         |
  | StringField         | 字符串类型                                    |
  | DecimalField        | 小数点文本字段，如：‘1.23’                         |
  | DateField           | 日期字段，格式：'%Y-%m-%d'                       |
  | DateTimeField       | 日期字段，格式：'%Y-%m-%d %H:%M:%S'              |
  | FieldList           | 统一字段类型组成列表，如：FieldList(StringField('Name', [ validators.required() ])) |
  | FloatField          | 浮点数类型                                    |
  | IntegerField        | 整形                                       |
  | SelectMultipleField | 多选框                                      |
  | RadioField          | 单选框                                      |
  | TextAreaField       | 文本域，可接受多行输入                              |
  | PasswordField       | 密码字段，输入的不会直接在浏览器明文显示                     |
  | FileField           | 上传文件，但不会处理验证文件，需要手动处理                    |
  | HiddenField         | 隐藏字段                                     |
  | SubmitField         | 按钮                                       |

* **表单字段参数**

  | 表单参数        | 说明                                       |
  | ----------- | ---------------------------------------- |
  | label       | 字段的名字                                    |
  | default     | 默认值                                      |
  | validators  | 字段的验证序列 [DataRequired(), Length(4,20)]->必填字段，长度在4-20， 见下边 |
  | description | 字段的描述                                    |
  | choices     | SelectField和他的子类有的字段，选择框，多选一             |

* **字段验证序列**

  | 验证字段                                     | 说明                                       |
  | ---------------------------------------- | ---------------------------------------- |
  | Required/required/DataRequired/data_required | 不能为空                                     |
  | InputRequired/input_required             | 和DataRequired的区别在于可以是空白字符串               |
  | Email/email                              | 验证符合邮件的格式，只有最基本的验证                       |
  | EqualTo/equal_to                         | 比较两个字段的值，比如密码和确认密码，如果不相等就触发错误，equal_to(field,message),需要输入另一个字段的名字 |
  | IPAddress/ip_address                     | 验证是否是ip地址，默认验证IPV4地址                     |
  | MacAddress/mac_address                   | 验证是否符合mac格式                              |
  | UUID                                     | 是否是uuid格式                                |
  | URL/url                                  | 验证是否符合url格式                              |
  | Regexp/regexp                            | 用提供的正则表达式验证字段；Regexp(r"")                |
  | Length/length                            | 设置字段值的长度，Length(min,max)                 |
  | NumberRange/number_range                 | 设置一个数字字段的取值范围，可以针对浮点数和小数；NumberRange(min,max) |
  | Optional/optional                        | 允许字段为空并停止验证                              |
  | NoneOf/none_of                           | 将传入的数据和无效的比较，是抛出异常；Noneof(values)        |
  | Anyof/any_of                             | 将传入的数据和预设的数据比较，不是异常。Anyof(values)        |

* 使用WTF实现一个表单：

  * 自定义表单类，使用现成的控件和验证方式

  * 在模板的表单标签下添加csrf token： {{ form.csrf_token }}

     CSRF（Cross Site Request Forgery, 跨站域请求伪造）是一种网络的攻击方式

* **视图文件**

  ```python
    # -*- coding: utf-8 -*-
    from flask import Flask, render_template, request, flash
    from flask_wtf import FlaskForm
    from wtforms import StringField, PasswordField, SubmitField
    from wtforms.validators import DataRequired, EqualTo

    # 创建flask应用程序实例
    # 需要传入__name__,作用是为了确定资源所在的路径
    app = Flask(__name__)
    app.secret_key = "cbjtestform"

    # 自定义表单类
    class LoginForm(FlaskForm):
        username = StringField(label='用户名', validators=[DataRequired()])     # '用户名' 是label, validators验证函数列表
        password = PasswordField('密码', validators=[DataRequired()])
        password2 = PasswordField('确认密码', validators=[DataRequired(), EqualTo('password', '密码输入不一致')])
        submit = SubmitField('提交')

    @app.route('/', methods=['GET', 'POST'])
    def login():
        login_form = LoginForm()

        # 1.判断请求方式
        if request.method == 'POST':
            # 2.参数获取
            username = request.form.get('username')
            password = request.form.get('password')
            password2 = request.form.get('password2')
            # 或者直接从表单对象取数据
            password_2 = login_form.password2.data

            # 3.参数验证
            # 我们没有 CSRF token
            if login_form.validate_on_submit():  # 提交时进行参数校验
                print('name={} pswd={} pawd2={} pswd2={}'.format(
                    username, password, password2, password_2))
                return "success"
            else:
                flash('参数有误')

        return render_template('wtf_tp.html', form=login_form)

    # 定义路由与视图函数
    # Flask定义路由是通过装饰器实现的
    @app.route('/helloworld')
    def hello_world():
        return 'hello world!'

    # 启动程序
    if __name__ == '__main__':
        app.run(host='127.0.0.1', port=8080, debug=False)
  ```

* **模板文件(wtf_tp.html)**

  ```jinja2
            <!DOCTYPE html>
            <html lang="en">
            <head>
                <meta charset="UTF-8">
                <meta charset="gb2312">
                <meta name="viewport" content="width=device-width, initial-scale=1.0">
                <meta http-equiv="X-UA-Compatible" content="ie=edge">
                <title>flask-WTF??</title>
            </head>
            <body>
                <form method="post">
                    {# ??CRSF_TOKEN #}
                    {{ form.csrf_token }}
                    {{ form.username.label }}: {{ form.username }} <br>
                    {{ form.password.label }}: {{ form.password }} <br>
                    {{ form.password2.label }}: {{ form.password2 }} <br>
                    {{ form.submit }} <br>
                    {% for f in get_flashed_messages() %}
                    {{ f }}
                    {% endfor %}
                </form>
            </body>
            </html>
  ```

## 案例4：Flask-SQLAlchmey数据库操作

* **Flask-SQLAlchmey**

  Flask-SQLAlchmey是一个操作关系型数据库的flask扩展，
  让开发者不用直接和sql语句打交道，而是通过python对象来操作数据库。
  Flask-SQLAlchmey中，数据库使用url指定，而且程序使用的数据库必须保存到flask配置对象的FLASKALCHEMY_DATABASE_URI键中
  ​

* **安装flask扩展**
  pip install flask-sqlalchemy
  如果连接的是mysql数据库，还需要安装mysqldb：pip install flask-mysqldb
  ​
* **创建数据库模型**
  sqlalchemy数据类型和python、mysql数据类型的对应关系：

  |     类型名      |     Python类型      |     数据库类型     |
  | :----------: | :---------------: | :-----------: |
  |   Integer    |    int 整数(4字节)    |      INT      |
  | SmallInteger |    int 整数(2字节)    |   SMALLINT    |
  |  BigInteger  |     int或long      |    BIGINT     |
  |    Float     |       float       |     FLOAT     |
  |   Numeric    |  decimal.Decimal  |    DECIMAL    |
  |    String    |        str        |    VARCHAR    |
  |     Text     |        str        |     TEXT      |
  |   Boolean    |       bool        |    BOOLEAN    |
  |     Date     |   datetime.date   |     DATE      |
  |     Time     |   datetime.time   |     TIME      |
  |   DateTime   | datetime.datetime |   DATETIME    |
  |     Enum     |        str        |     ENUM      |
  | LargeBinary  |        str        | VARBINARY查询操作 |
* **常用查询过滤器（写条件的）**
    filter()
    filter_by()
    limit
    offset()
    order_by()
    group_by()

* **常用查询执行器（开始执行的）**

  all()
  first()
  first_or_404() 返回查询的第一个结果，如未查到返回404
  get()
  get_or_404()  返回指定主键对应的行，如不存在返回404
  count()
  paginate() 返回一个paginate对象，它包含指定范围的结果

* **视图文件**

  ```python
    # -*- coding: utf-8 -*-
    from flask import Flask
    from flask_sqlalchemy import SQLAlchemy

    # 创建flask应用程序实例
    # 需要传入__name__,作用是为了确定资源所在的路径
    app = Flask(__name__)
    # 配置数据库地址
    app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql://spider:spider2013@10.160.81.11:3306/mytest'
    # 跟踪数据库的修改，不建议开启，未来版本中会被移除
    app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
    # 创建数据库对象实例
    db = SQLAlchemy(app)

    '''
    一对多关系的两张表：
        角色 (角色id,角色名称)
        用户(用户id、用户名、邮箱、密码、角色id)
    '''

    # 数据库模型
    class Role(db.Model):
        # 定义表名
        __tablename__ = 'roles'

        # 定义字段
        id = db.Column(db.Integer, primary_key=True)
        name = db.Column(db.String(16), unique=True)

        # 也可以在这里定义
        # myuser = db.relationship('User', backref='myroles')

        # 支持可读字符串打印
        def __repr__(self):
            return '<Role: {} {}>'.format(self.name, self.id)

    class User(db.Model):
        __tablename__ = 'users'

        id = db.Column(db.Integer, primary_key=True)
        name = db.Column(db.String(16), unique=True)
        email = db.Column(db.String(32), unique=True)
        password = db.Column(db.String(32))
        role_id = db.Column(db.Integer, db.ForeignKey('roles.id'))  # 关联外键（多对一）
        # User希望有一个role属性，但是这个属性的定义需要在另一个模型中定义，反向引用

        # 添加关系引用
        # db.relationship('Post'): 正向关联
        # backref='myuser': 反向引用
        # 技巧：在(多对一)多的一方定义外键，关系引用可以在任一方定义（一方即可）
        # users表中的记录通过myroles查找关联的roles表中的值
        # roles表中的记录通过myusers查询关联的user表中的值
        # myroles是给自己用的，myuser是给对方Role用的
        myroles = db.relationship('Role', backref='myuser')

        def __repr__(self):
            return '<User: name={} id={} email={} pswd={} rid={}>'.format(
                self.name, self.id, self.email, self.password, self.role_id)

    # 定义路由与视图函数
    # Flask定义路由是通过装饰器实现的
    @app.route('/helloworld')
    def hello_world():
        return 'hello world!'

    # 启动程序
    if __name__ == '__main__':
        # 删除所有继承自db.Model的表
        db.drop_all()
        # 创建所有继承自db.Model的表
        db.create_all()

        '''
        (1) 测试增删改查
            数据库的增删改，需要通过会话：
            db.session.add(role)
            db.session.add_all([user1, user2, ...])
            db.session.commit()
            db.session.rollback()
            db.session.delete(user)
        '''

        # 插入数据
        ro1 = Role(name='admin')
        db.session.add(ro1)
        db.session.commit()
        ro2 = Role(name='user')
        db.session.add(ro2)
        db.session.commit()

        us1 = User(name='jzs1', email='jzs1@163.com', password='ps3456', role_id=ro1.id)
        us2 = User(name='azs2', email='azs2@163.com', password='12as35', role_id=ro2.id)
        us3 = User(name='szs3', email='szs3@163.com', password='166556', role_id=ro2.id)
        us4 = User(name='dzs4', email='dzs4@163.com', password='154rg6', role_id=ro1.id)
        us5 = User(name='rzs5', email='rzs5@163.com', password='245886', role_id=ro1.id)
        us6 = User(name='tzs6', email='tzs6@163.com', password='123aa6', role_id=ro2.id)
        db.session.add_all([us1, us2, us3, us4, us5, us6])
        db.session.commit()

        # 修改数据
        us3.name = 'baijie'
        db.session.commit()        # 修改了某个字段，只需要commit即可，不需要再add了

        # 删除数据
        db.session.delete(us5)
        db.session.commit()

        # 显示数据库内容
        print("User---", User.query.all())

        # 查询操作
        # 1.查询所有用户
        User.query.all()
        # 2.查询有多少个用户
        User.query.count()
        # 3.查询第一个用户
        User.query.first()
        # 4.查询id为4的用户
        User.query.get(4)  # 主键为4
        User.query.filter_by(id=4).first()     # filter_by(属性=val)
        User.query.filter(User.id == 4).first()  # filter(对象.属性==val) 功能更强大，可以实现更多查询，如比较运算符

        '''
        (2) 测试关联关系
            User表和Role表是一对多的关系，User表通过外键role_id和Role表关联
            如果想通过User对象询用户的角色信息，或者通过Role对象查询角色对应的多个用户的信息，
            需要两表建立关联(user查role)和反向引用(role查user)：
            db.relationship('User', backref='role') -> User是另一侧对象实例(模型)，role为自定义的反向引用的别名
        '''
        # 删除表
        db.drop_all()
        # 创建表
        db.create_all()
        # 测试关联关系
        role = Role(name='admin')
        db.session.add(role)
        db.session.commit()
        user1 = User(name='sz', role_id=role.id)
        user2 = User(name='ls', role_id=role.id)
        db.session.add_all([user1, user2])
        db.session.commit()
        print("role.users--", role.myuser)   # 查询role这条记录对应的user表的信息
        print("user1.roles--", user1.myroles)  # 查询user1这一行对应的roles表的信息
        print("user1={}, user1.roles.name={}".format(user1, user1.myroles.name))

        app.run(host='127.0.0.1', port=8080, debug=False)
  ```

## 案例5：图书管理系统

1. 配置数据库

   导入SQLAlchemy扩展

   创建db对象

   在终端创建数据库(db对象只是增删表，以及增删改查操作,需先行创建database)

2. 添加书和作者模型

   模型继承db.Model

   ​    作者模型：字段->id，name  (一)
   ​    书籍模型：字段->id，name，author_id   (多)

   表名 \_\_tablename__

   字段名 db.Column

   添加关系引用：db.relationship

3. 添加数据

   main函数中初始化数据表中的数据

4. 使用模板显示数据库查询的数据

   查询所有作者的信息，传给模板

   模板中两重for循环，取出作者，作者的书籍(此处用的关系引用)

5. 使用wtf显示表单

   自定义表单类

   模板中显示

   secret_key / csrf_token 等问题

6. 实现相关的增删的逻辑
      验证逻辑：
   1. 调用wtf的函数实现验证
   2. 验证通过获取数据
   3. 判断作者是否存在
   4. 如果作者存在，判断书籍书否存在，没有重复书籍，则添加数据，如果重复，提示错误
   5. 如果作者不存在，则添加作者和书籍
   6. 验证不通过提示错误

* **视图文件**

  ```python
    # -*- coding: utf-8 -*-
    from flask import Flask, render_template, request, redirect, url_for, flash
    from flask_sqlalchemy import SQLAlchemy
    from flask_wtf import FlaskForm
    from wtforms import StringField, SubmitField
    from wtforms.validators import DataRequired

    # 创建flask应用程序实例
    # 需要传入__name__,作用是为了确定资源所在的路径
    app = Flask(__name__)
    app.secret_key = 'test'
    # 配置数据库地址（mysql://user:passwd@ip:port/database）
    app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql://spider:spider2013@10.160.81.11:3306/mytest'
    # 跟踪数据库的修改，不建议开启，未来版本中会被移除
    app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
    # 创建数据库对象实例
    db = SQLAlchemy(app)

    # 作者模型：字段->id，name              一
    # 书籍模型：字段->id，name，author_id   多
    class Author(db.Model):
        # 表名
        __tablename__ = 'authors'

        # 字段
        id = db.Column(db.Integer, primary_key=True)
        name = db.Column(db.String(48), unique=True)

        # 支持打印
        def __repr__(self):
            return '<Author> id={}, name={}'.format(self.id, self.name)

        # 一对多关系(books和author是自定义的名字，Book是另一个模型的类名)
        books = db.relationship('Book', backref='author')

    class Book(db.Model):
        __tablename__ = 'books'
        id = db.Column(db.Integer, primary_key=True)
        name = db.Column(db.String(48), unique=True)
        author_id = db.Column(db.Integer, db.ForeignKey('authors.id'))

    class AddForm(FlaskForm):
        author_name = StringField(label='作者', validators=[DataRequired()])
        book_name = StringField(label='书籍', validators=[DataRequired()])
        submit = SubmitField('添加')

    # 定义路由与视图函数
    # Flask定义路由是通过装饰器实现的
    @app.route('/', methods=['GET', 'POST'])
    def show_page():

        add_form = AddForm()
        # 提交时进行表单参数验证
        if not add_form.validate_on_submit():
            if request.method == 'POST':
                flash('参数不完整！')
        else:
            author_name = add_form.author_name.data
            book_name = add_form.book_name.data
            print('222', author_name, book_name)
            # 判断作者和书籍是否存在
            author = Author.query.filter_by(name='author_name').first()
            if author:
                # 作者存在，如果书籍存在提示已存在，如果书籍不存在，插入书籍
                book = Book.query.filter_by(name=book_name).first()
                if book:
                    flash('书籍已存在！')
                else:
                    new_book = Book(name=book_name, author_id=author.id)
                    try:
                        db.session.add(new_book)
                        db.session.commit()
                    except Exception as e:
                        flash('插入书籍失败')
                        db.session.rollback()
            else:
                # 作者不存在，如果书籍存在提示已存在，如果书籍不存在，插入作者和书籍
                book = Book.query.filter_by(name=book_name).first()
                if book:
                    flash('书籍已存在！')
                else:
                    try:
                        new_author = Author(name=author_name)
                        new_book = Book(name=book_name)
                        print("111", new_author, new_book)
                        new_author.books.append(new_book)
                        db.session.add_all([new_author, new_book])
                        db.session.commit()       # 添加作者和书籍
                    except Exception as e:
                        flash('插入作者和书籍失败')
                        db.session.rollback()

        # 查询数据
        authors = Author.query.all()
        print(authors)

        # 渲染到页面
        return render_template('booklist.html', authors=authors, form=add_form)

    # 删除书籍，删除完毕， 更新数据库后重定向到显示面展示
    @app.route('/delete_book/<int:book_id>')
    def delete_book(book_id):
        try:
            # 根据传过来的book_id 查询到book对象进行删除
            book = Book.query.get(book_id)
            # 删除数据
            db.session.delete(book)
            db.session.commit()
            flash('删除成功')
        except BaseException as e:
            print(e)
            flash('数据库操作失败')
            db.session.rollback()

        return redirect(url_for('show_page'))

    # 删除作者，删除完毕更新数据库，并重定向到显示页面
    @app.route('/delete_author/<int:author_id>')
    def delete_author(author_id):
        try:
            # 根据传过来的author_id 查询到author对象
            author = Author.query.get(author_id)
            # 查询作者名下的书籍模型
            books = author.books
            # 遍历删除
            for book in books:
                db.session.delete(book)
            # 删除数据
            db.session.delete(author)
            db.session.commit()
            flash('删除成功')
        except BaseException as e:
            print(e)
            flash('数据库操作失败')
            db.session.rollback()

        return redirect(url_for('show_page'))

    # 启动程序
    if __name__ == '__main__':
        # 删除所有继承自db.Model的表
        db.drop_all()
        # 创建所有继承自db.Model的表
        db.create_all()

        # 生成作者数据
        au1 = Author(name='金庸')
        au2 = Author(name='古龙')
        au3 = Author(name='梁羽生')
        db.session.add_all([au1, au2, au3])  # 把数据提交给用户会话
        db.session.commit()                  # 提交会话

        # 生成书籍数据
        bk1 = Book(name='《神雕侠侣》', author_id=au1.id)
        bk2 = Book(name='《天龙八部》', author_id=au1.id)
        bk3 = Book(name='《鹿鼎记》', author_id=au1.id)
        bk4 = Book(name='《浣花洗剑录》', author_id=au2.id)
        bk5 = Book(name='《多情剑客无情剑》', author_id=au2.id)
        bk6 = Book(name='《七剑下天山》', author_id=au3.id)
        bk7 = Book(name='《白发魔女传》', author_id=au3.id)

        db.session.add_all([bk1, bk2, bk3, bk4, bk5, bk6, bk7])
        db.session.commit()

        app.run(host='127.0.0.1', port=8080, debug=False)
  ```

* **模板文件(booklist.html)**

  ```jinja2
            <!DOCTYPE html>
            <html lang="en">
            <head>
                <meta charset="UTF-8">
                <meta name="viewport" content="width=device-width, initial-scale=1.0">
                <meta http-equiv="X-UA-Compatible" content="ie=edge">
                <title>书籍查询系统</title>
            </head>
            <body>
            <form method="post">
                {# 表单展示 #}
                {# 设置隐藏的csrf_tooken #}
                {{ form.csrf_token }}
                {{ form.author_name.label }} {{ form.author_name }} <br>
                {{ form.book_name.label }}{{ form.book_name }} <br>
                {{ form.submit }} <br>
                {% for m in get_flashed_messages() %}
                <font style='color:red'>{{ m }}</font>
                {% endfor %}
            </form>

            <hr>
            {# 书籍展示 #}
            {# 先遍历作者，在作者里遍历书籍，填充无序列表ur li标签 #}
            <ul>
                {% for au in authors %}
                <li>{{ au.name }}<a href="/delete_author/{{ au.id }}">删除</a></li>
                <ul>
                    {% for b in au.books %}
                    {# jinja2里也支持url_for，参数是视图函数名称，其效果和上边直接写url地址一样 #}
                    <li>{{ b.name }}<a href="{{ url_for('delete_book', book_id=b.id) }}">删除</a></li>
                    {# 注意 jinja2中for循环可以用else #}
                    {% else %}
                    <li>无</li>
                    {% endfor %}
                </ul>
                {% endfor %}
            </ul>
            </body>
            </html>
  ```
