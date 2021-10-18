// 打包宏开关，开启则为 DEBUG 模式，关闭则为 RELEASE 模式
// DEBUG 模式下，对象加载资源时，从源文件处读取二进制数据并存入对应的包中
// RELEASE 模式下，对象构建时读取包至内存并构建哈希表，加载资源时直接从哈希表中返回

#define _ADEN_PACKAGE_DEBUG_

#ifndef _ADEN_PACKAGE_H_
#define _ADEN_PACKAGE_H_

#include <fstream>
#include <string>
#include <unordered_map>

enum
{
	ADEN_MAX_LENGTH = 64													//源文件相对路径最大长度
};

struct AdenData																//单个二进制数据文件
{
	size_t length;
	char* data;
};

class AdenPackageFile
{
public:
	AdenPackageFile(std::string packagePath);
	~AdenPackageFile();														//析构函数遍历释放内存中的所有二进制数据

	AdenData* LoadResource(std::string dataPath);

private:
	std::string pathName;													//二进制包名
	std::unordered_map<std::string, AdenData*> mapIndex;					//二进制数据索引哈希表

	std::ofstream fout;														//DEBUG 模式用于写入
};


#endif // !_ADEN_PACKAGE_H_