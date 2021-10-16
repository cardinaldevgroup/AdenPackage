#ifndef _ADEN_PACKAGE_H_
#define _ADEN_PACKAGE_H_

#include <iostream>
#include <fstream>
#include <string>

//AdenPackage打包开关宏
//如果声明该宏，读取数据时从源文件处读取并更新数据包
//如果取消声明该宏，读取数据则从数据包中读取

//#define _ADEN_PACKAGE_DEBUG_

struct AdenData
{
	std::streamoff index;				//索引至二进制数据的值
	size_t length;						//二进制数据的长度属性
};

class AdenPackageFile
{
public:
	AdenPackageFile(std::string, size_t);
	~AdenPackageFile();

	size_t LoadResource(const char*);	//加载资源函数
	char* ReadResource(size_t);			//读取资源函数
private:
	std::string fileName;

	std::ifstream fin;					//读取文件流
	std::ofstream fout;					//输出文件流

	size_t nSize;						//二进制数据数组的大小
	size_t nAmount;						//数组实际元素个数
	AdenData* arrayData;				//包含二进制属性的数组
};

#endif // _ADEN_PACKAGE_