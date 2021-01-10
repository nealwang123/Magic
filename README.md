# Magic[v2.0.0]

>Magic [v2.0.0] 已接近尾声正在最后的完善中,暂未上传,敬请期待!

>主分支中Magic的版本[v1.0.0]现已停止开发.如需要查看此版本的README请切换分支至v1.0.0

## 简介

> ​		Use Standard C++ 11

> ​		基于IoC的快速开发库(C++ Rapid development library based on Inversion of Control),配合CMake构建套件开发.

## 特点

### 快速开发

- **高内聚,低耦合**.
- 超强的**通用性**以及高度**跨平台**.
- 实现**模块化**开发方式便于协作开发.
- 基于 IoC `(Inversion of Control)`的方式对每个类进行托管以及自动注入构建.

### 模块配置

- 功能模块可高度**重用**，方便**扩展**以及**维护**.
- 使用**Json**格式配置文件`(*.magic)`对功能进行模块划分.

### 非侵入式

- 代码**移植度**高.
- **无任何侵入式代码**.
- 高度解耦
### [Go to 安装/使用方法](https://github.com/INotfound/Magic/blob/master/Doc/Guide.md)
### 本库特性
> 组件: ***类Log4j日志***、***线程***、***NetWork网路、Http协议***、***Web服务***、***数据库***、***高性能网络/数据库连接池***、***高性能TimingWheel定时轮***等等

> 本库将智能指针名称进行了重定义.
```c++
    #define Safe std::shared_ptr
```
> Config配置组件的使用用方法.
```c++
    /// 支持自定义扩展.
    /// 目前只支持基础类型和std::string.
    /// 未修改生成的配置文件的情况下,会使用at函数的第二个参数作为默认值.
    uint64_t number = Magic::Config::GetInstance()->at<uint64_t>("number", 24);
```
>Log日志组件的使用方法.
```c++
    /// 类 Log4j 日志库.
    /// 五种日志打印级别.
    /// 可通过配置中LogLevel调整日志输出等级.
    MAGIC_INFO() << "hello world";
    MAGIC_WARN() << "hello world";
    MAGIC_DEBUG() << "hello world";
    MAGIC_ERROR() << "hello world";
    MAGIC_FATAL() << "hello world";
```
.....
## 其他

### 代码规范/联系方式
  - [C++](http://note.youdao.com/noteshare?id=0975fd51d320c1cd7bc0cbaab6d39e59&sub=AC10B1CBC6744F92B2B8A3F26DC47918)
- 作者联系方式

  - QQ: [614199451](http://wpa.qq.com/msgrd?v=3&uin=614199451&site=qq&menu=yes)
  - QQ群: [451405524](https://qm.qq.com/cgi-bin/qm/qr?k=qsjCo88_9j8cPCwkgzRzaIKfCyXU98VH&jump_from=webapi)
