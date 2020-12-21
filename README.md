# Magic

## 简介

> ​		Use Standard C++ 11

> ​		基于IoC的快速开发库(C++ Rapid development library based on Inversion of Control),配合CMake构建套件开发.

## 特点

- 快速开发
  - 高内聚,低耦合.
  - 超强的通用性以及高度跨平台.
  - 实现模块化开发方式便于协作开发.
  - 基于 IoC `(Inversion of Control)`的方式对每个类进行托管以及自动创建.
- 模块配置
  - 功能模块可高度重用，方便扩展以及维护.
  - 使用Json格式配置文件`(.magic)`对功能模块进行划分.
- 非侵入式
  - 代码移植度高.
  - 无任何侵入式代码.
- 高度解耦
  - 继承于IoC的主要特点.

## 使用方式

> CMakeLists.txt

```cmake
set(MAGIC /home/magic/WorkSpace/Magic)
include_directories(
    ${MAGIC}
	${MAGIC}/Include
    ${PROJECT_SOURCE_DIR}
    ${MAGIC}/ThirdParty/Asio/Include
    ${MAGIC}/ThirdParty/RapidJSON/Include
)
link_directories(
    ${MAGIC}/Lib
)
link_libraries(Magic)
include(../../Magic.cmake)
#参数[1]:本库路径
#参数[2]:导出的头文件名
#参数[MGC]: 本库中的单模块(Module) or 多模块(Modules)
#参数[SRC]: 自定义的模块(Module) or 多模块(Modules)
GENEX(${MAGIC} Base MGC Magic SRC Base)

```

> 配置文件：(可使用多个配置文件)

```json
{ // Example
    "Configurations":{
        "NameSpace":"Base", 								//	同C++的namespace,若不想具有namespace留空即可.
        "Registered":[										//	类信息注册.
            {
                "Id":"config", 								// 类Id标识(任意名),用于Initialize中使用.
                "Class":"Magic::Config", 					// 类名,如果有namespace,则需加上即可.
                "IncludePath": "Include/Core/Config.h",		// 类所在的文件路径.
                "Interface":"",								// 继承的接口类,通常需要类似工厂模式的时候才使用.
                "Dependencies":[],							// 依赖的其他类的类名.
                "FunctionPropertys":["addConfigFile"]		// 需要注册的属性函数.
            },
            {
                "Id":"configFile",
                "Class":"Magic::ConfigFile",				// 与Magic::Config同文件,则不需要在此定义IncludePath
                "FunctionPropertys":["addFormatter"]
            },
            {
                "Id":"iniConfigFormmater",
                "Class":"Magic::InIConfigFormatter",		// 与Magic::Config同文件,则不需要在此定义IncludePath
                "Interface":"Magic::IConfigFormatter"
            },
            {
                "Id":"logger",
                "Class":"Magic::Logger",
                "IncludePath": "Include/Core/Logger.h",
                "Dependencies":["Magic::Config"],
                "FunctionPropertys":[]
            },
            {
                "Id":"stdOut",
                "Class":"Magic::StdOutLogAppender",
                "Interface":"Magic::ILogAppender",
                "Dependencies":[],
                "FunctionPropertys":[]
            }
        ],
        "Initialize":[										// 初始化
            {
                "Id":"configFile", 							// 类Id标识应与上方Registered中一致.
                "FunctionPropertys":["setFilePath"],		// 需要初始化的函数.
                "FunctionArguments":{
                    "setFilePath" : ["\"./config.conf\""]	// 函数中对应的 RAW Arguments.
                }
            },
            {
                "Id":"logger",
                "Loop":true,								// Loop 循环加入接口类对象
                "Callee":"Magic::ILogAppender",				// 接口类类型
                "FunctionPropertys":["addILogAppender"],	// 接口类对象添加函数.
                "FunctionArguments":{}
            }
        ],
        "Constructor":{										// 构造函数定义
            "Name":"Initialize",							// 暴露给main函数中调用名.
            "WithParameter": false							// 是否需要自定义注册参数.
        }
    }
}
```

> Example: [Magic/Example](Magic/Example)目录.

- 超简单的实例，[Base](Magic/Example/Base)项目.

```c++
#include "Base.h"

int main(){
    Base::Initialize();
    MAGIC_DEBUG() << "hello world";
    return EXIT_SUCCESS;
}
```

## 其他

- [C++ 个人代码规范](http://note.youdao.com/noteshare?id=0975fd51d320c1cd7bc0cbaab6d39e59&sub=AC10B1CBC6744F92B2B8A3F26DC47918)

## 作者联系方式

- QQ: [614199451](http://wpa.qq.com/msgrd?v=3&uin=614199451&site=qq&menu=yes)
- QQ群: [451405524](https://qm.qq.com/cgi-bin/qm/qr?k=qsjCo88_9j8cPCwkgzRzaIKfCyXU98VH&jump_from=webapi)