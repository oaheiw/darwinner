# 公告 #
为了防止那些热爱侵犯知识产权的人盗窃该项目成果，从即日起该项目主页只会用于发布新闻、更新文档、BUG追踪，将不再更新代码以及发行版本。如果有兴趣参与项目（提出建议、文档撰写、研发、界面设计、申请测试）

请至讨论组参与讨论
[思索工作室/Seashore Studio](http://groups.google.com/group/seashore-studio)

或者邮件至
[思索工作室邮件列表/Seashore Studio Mailing List](mailto:seashore-studio@googlegroups.com)

或至站长网站
[嘻来嚷往](http://xirang.ca)

或至叽喳多媒体微博客
[叽喳](http://jizha.us)

# 简述 #
Cosmetic是基于跨平台C++类库[Qt](http://zh.wikipedia.org/wiki/Qt)开发的、遵循[GNU LGPL(v3)](http://zh.wikipedia.org/wiki/LGPL)协议的零售服务业ERP综合运营系统。整合了员工管理、业务管理，库存管理、店面运营、客户管理、营销统计6大系统，高级版还具有多终端的用户自助消费系统。整套运营系统既可支持单一店面单机运作，也可实现连锁店面的大规模运作。

# 架构 #
Cosmetic采用“视图——控制——数据”的MVC模式开发，部署时可以的生成不同版本的产品，同时在现有架构上开发新特性也是简单易行。
对于单机版的系统，采用实现了加密函数的[SQLite](http://zh.wikipedia.org/wiki/SQLite)进行数据存储，对于网络版系统则采用[MySQL](http://zh.wikipedia.org/wiki/MySQL)数据库。

# 特性 #
采用跨平台代码开发，可以部署在Windows、Window Mobile、Linux、Embedded Linux、Mac OS平台，满足不同客户需求。

# 测试 #
请把发现的缺陷详细记录在Issues中，包括如何操作产生这个缺陷，系统的预期动作应该而实际动作是怎样。同时把Cosmetic运行时的输出窗口内容截屏作为附件上传，**更重要的是注明测试用文件的svn版本，即版本号x.xx.yyy中的最后三位yyy（程序文件的属性中可以看到更详细的版本信息）**。

# 访问统计 #
[![](http://www2.clustrmaps.com/stats/maps-no_clusters/code.google.com-p-darwinner--thumb.jpg)](http://www2.clustrmaps.com/user/a028a5c6)

# 截图 #
登录

![http://darwinner.googlecode.com/files/login.png](http://darwinner.googlecode.com/files/login.png)

主菜单

![http://darwinner.googlecode.com/files/memu.png](http://darwinner.googlecode.com/files/memu.png)

员工管理

![http://darwinner.googlecode.com/files/staff.png](http://darwinner.googlecode.com/files/staff.png)

业务管理

![http://darwinner.googlecode.com/files/business.png](http://darwinner.googlecode.com/files/business.png)

顾客管理

![http://darwinner.googlecode.com/files/customer.png](http://darwinner.googlecode.com/files/customer.png)

# 类图 #

![http://darwinner.googlecode.com/files/Cosmetic%20System%20Class%20Diagram.jpg](http://darwinner.googlecode.com/files/Cosmetic%20System%20Class%20Diagram.jpg)