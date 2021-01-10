<!--
 * @Author: INotFound
 * @Date: 2021-01-10 14:08:44
 * @LastEditTime: 2021-01-10 14:59:08
-->
## Guide
### 安装
> 只需支持C++11的编译器以及CMake构建工具编译即可.
- Linux
    1. Gnu构建套件 (跳转在库路径中)
        1. mkdir build && cd build && cmake ../. && make && make install
    2. Ninja构建套件 (推荐.跳转在库路径中)
        1. mkdir build && cd build && cmake -GNinja ../. && ninja && ninja install
- Win
    - VS 20XX
        - cmake -G "Visual Studio 15 2017" // or Visual Studio xx 20xx
### 使用方法
1. 使用本库工具 ***Create***
    1. 创建项目文件目录名,跳转项目文件目录中
    2. 使用Create Test 创建项目模板 ***Test*** 项目名
    3. 当前目录会生成 CMakeLists.txt Main.cpp Test.magic 三个文件

2. 打开***Test***项目文件夹中CMakeLists.txt文件.
    1. 设置Magic库路径, set(MAGIC ***/home/magic/Magic***) Magic库文件路径
```cmake
#Please Add The Directory Path Of The Magic Library.
set(MAGIC /home/magic/Magic)

if(NOT DEFINED MAGIC)
    message(FATAL_ERROR "Please Add The Directory Path Of The Magic Library!!!")
endif()

include_directories(
    ${MAGIC}
	${MAGIC}/Include
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/Include
    ${MAGIC}/ThirdParty/Asio/Include
    ${MAGIC}/ThirdParty/RapidJSON/Include
)
link_directories(
    ${MAGIC}/Lib
)
link_libraries(Magic)
include(${MAGIC}/Magic.cmake)

#参数[1]:本库路径
#参数[2]:导出的头文件名
#参数[MGC]: 本库中的单模块(Module) or 多模块(Modules)
#参数[SRC]: 自定义的单模块(Module) or 多模块(Modules)
GENEX(${MAGIC} Test MGC Magic SRC Test)
```
3. 打开Test.magic配置文件
```jsonc
{
    "Configurations":{
        "NameSpace":"Test",                 // 同 C++ 的namespace
        "Registered":[                      // 类信息注册(强制,必须要具有一个).
            {
                "Id":"",                    // 类Id标识(任意名)用于Initialize中使用.
                "Class":"",                 // 类名,如果有namespace,则需加上即可.
                "Interface":"",             // 类所在的文件路径(如何有相同的可以忽略).
                "IncludePath": "",          // 继承的接口类,通常需要抽象的时候才使用.
                "Dependencies":[],          // 依赖的其他类的类名.
                "FunctionPropertys":[]      // 需要注册的属性函数.
            }
        ],
        "Initialize":[                      // 初始化(非强制)
            {
                "Id":"",                    // 类Id标识应与上方Registered中一致.
                "Loop":false,               // Loop 循环初始化
                "Callee":"",                // 接口类类型 若Loop == true则该属性必须具有值.
                "FunctionPropertys":[],     // 需要初始化的函数.
                "FunctionArguments":{}      // 函数中对应的 RAW Arguments. “XX”:["XXX"]写法.
            }
        ],
        "Constructor":{                     // 构造函数定义
            "Name":"Initialize",            // 暴露给main函数中调用名.
            "WithParameter": false          // 是否需要自定义注册参数.
        }
    }
}
```
4. 打开Main.cpp源文件

```c++
#include "Test.h" //添加头文件

int main(){
    Test::Initialize(); //添加初始化代码. [Configurations.NameSpace]::[Constructor.Name]命名设定
    return EXIT_SUCCESS;
}

```
### 本库示例
> 配置文件：[Magic模块](Magic.cmake)(可使用多个配置文件)
```jsonc
{                                                           // 日志以及配置模块示例
    "Configurations":{
        "NameSpace":"Magic",                                // 同C++的namespace,若不想具有namespace留空即可.
        "Registered":[                                      // 类信息注册(强制,必须要具有一个).
            {
                "Id":"config",                              // 类Id标识(任意名),用于Initialize中使用.
                "Class":"Magic::Config",                    // 类名,如果有namespace,则需加上即可.
                "IncludePath": "Include/Core/Config.h",     // 类所在的文件路径(如何有相同的可以忽略).
                "Interface":"",                             // 继承的接口类,通常需要抽象的时候才使用.
                "Dependencies":[],                          // 依赖的其他类的类名.
                "FunctionPropertys":["addConfigFile"]       // 需要注册的属性函数.
            },
            {
                "Id":"configFile",                          // 与Magic::Config同文件,则不需要在此定义IncludePath
                "Class":"Magic::ConfigFile",
                "FunctionPropertys":["addFormatter"]
            },
            ......
        ],
        "Initialize":[                                      // 初始化(非强制)
            {
                "Id":"configFile",                          // 类Id标识应与上方Registered中一致.
                "FunctionPropertys":["setFilePath"],        // 需要初始化的函数.
                "FunctionArguments":{
                    "setFilePath" : ["\"./config.conf\""]   // 函数中对应的 RAW Arguments. “XX”:["XXX"]写法.
                }
            },
            {
                "Id":"logger",
                "Loop":true,                                // Loop 循环加入接口类对象
                "Callee":"Magic::ILogAppender",             // 接口类类型 若Loop == true则该属性必须具有值.
                "FunctionPropertys":["addILogAppender"],    // 接口类对象添加函数.	
                "FunctionArguments":{}
            }
        ],
        "Constructor":{// 构造函数定义
            "Name":"Initialize",                            // 暴露给main函数中调用名.
            "WithParameter": false                          // 是否需要自定义注册参数.
        }
    }
}
```
### Other示例
> 目录位置:[Magic/Examples](https://github.com/INotfound/Magic/tree/master/Examples)

#### [Base](https://github.com/INotfound/Magic/tree/master/Examples/Base)示例

> CMakeLists.txt 引用Magic模块

```cmake
    GENEX(${MAGIC} Base MGC Magic SRC ...)
```
```c++
#include "Base.h"

int main(){
    Base::Initialize();
    MAGIC_DEBUG() << "hello world";
    return EXIT_SUCCESS;
}
```
#### [WebServer](https://github.com/INotfound/Magic/tree/master/Examples/Base)示例
> Main.cpp
```c++
#include "Web.h"

int main(){
    Web::Initialize();
    return EXIT_SUCCESS;
}
```
> Servlet.magic
```json
{
    "Configurations":{
        "NameSpace":"Web",
        "Registered":[
            {
                "Id":"testSevlet",
                "Class":"Web::TestServlet",
                "IncludePath": "TestSevlet.h",
                "Interface":"Magic::NetWork::Http::IHttpServlet",
                "Dependencies":[],
                "FunctionPropertys":[]
            }
        ],
        "Initialize":[],
        "Constructor":{
            "Name":"Initialize",
            "WithParameter": false
        }
    }
}
```
> TestSevlet.h
```c++
#pragma once
#include <Magic>

namespace Web{
    class TestServlet :public Magic::NetWork::Http::IHttpServlet{
    public:
        TestServlet();
        bool handle(const Safe<Magic::NetWork::Http::HttpRequest>& request,const Safe<Magic::NetWork::Http::HttpResponse>& response) override;
    };
}
```
> TestSevlet.cpp
```c++
#include "TestSevlet.h"

namespace Web{
    TestServlet::TestServlet()
        :Magic::NetWork::Http::IHttpServlet("",Magic::NetWork::Http::HttpServletType::Deafult){
    }
    bool TestServlet::handle(const Safe<Magic::NetWork::Http::HttpRequest>& request,const Safe<Magic::NetWork::Http::HttpResponse>& response){
        response->setStatus(Magic::NetWork::Http::HttpStatus::NOT_FOUND);
        std::string notfound{R"Template(<html>
            <head><title>404 Not Found</title></head>
            <body>
            <center><h1>404 Not Found</h1></center>
            <hr><center>Magic/0.0.2</center>
            </body>
            </html>)Template"};
        response->setBody(notfound);
        return true;
    }
}
```
> CMakeLists.txt
```cmake
    GENEX(${MAGIC} Web MGC Magic WebServer SRC Servlet)
```
