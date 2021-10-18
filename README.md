# AdenPackage 简介

AdenPackage 是一个可以所有文件的二进制数据读取进内存的库

AdenPackage 分为 `DEBUG模式` 和 `RELEASE模式`

该模式由 `AdenPackage.h` 中的 `_ADEN_PACKAGE_DEBUG_` 宏开关控制

AdenPackage 生成的包后缀名为 `.apf`

+ DEBUG 模式
    + 从源文件处读取数据并返回,方便调试
    + 读取同时将数据存入包内,不需要额外的打包操作

+ RELEASE 模式
    + 读取数据包,根据其内容构建一张哈希表
    + 直接返回哈希表中的值,速度较 DEBUG模式 快得多

# AdenPackage 用法

首先，你需要定义一个 AdenPackageFile 对象，

AdenPackage 以每个包作为一个对象，你需要告诉它包的名字。

```C++
#include "AdenPackage.h"
int main()
{
    AdenPackageFile test("test");
}
```

这个函数会在当前目录下生成一个名为 `test.apf` 的包

读入的所有数据的生命周期和这个包一样，在包被析构后数据也会被析构

接下来你只需要加载某个路径下的文件即可:

```C++
    AdenData* pData = test.LoadResource("test.png");
```

pData 里面便储存了我们想要的二进制数据

```C++
struct AdenData
{
	size_t length;
	char* data;
};
```

length便储存了数据的长度，data则储存了数据的内容

当你调试完成后，直接进入 `AdenPackage.h` 将 `#define _ADEN_PACKAGE_DEBUG_` 注释掉，

将 .apf 和程序一起发布即可

    注意，由于 RELEASE模式 下定义 AdenPackageFile对象 伴随着构建哈希表

    所以这个过程会非常缓慢，应该考虑将其放入另外一个线程中运行

> --by hsz 2021.10.18