#include "AdenPackage.h"
using namespace std;

AdenPackageFile::~AdenPackageFile()
{
	delete[] arrayData;
}

AdenPackageFile::AdenPackageFile(std::string name, size_t size) :fileName(name), nSize(size), nAmount(0)
{
	arrayData = new AdenData[size];
	fout.open(name + ".apf", ios_base::out | ios_base::binary); //数据包文件后缀为 .apf

	//写入该二进制包的属性
	fout.seekp(0);
	fout.write((char*)&nSize, sizeof(nSize)) << flush; //二进制数据数组大小
}

size_t AdenPackageFile::LoadResource(const char* path)
{
//倘若是 DEBUG 模式，则从源文件处读取，并存入数据包
#ifdef _ADEN_PACKAGE_DEBUG_
	fin.open(path, ios_base::in | ios_base::binary);
	fin.seekg(0, fin.end);
	size_t length = fin.tellg();
	fin.seekg(0, fin.beg);
	char* buffer = new char[length];
	fin.read(buffer, length);
	fin.close(); fin.clear();

	//如果是第一个数据，则在数组后面开始写入，方便空出数组的位置
	if (++nAmount == 1) fout.seekp(static_cast<__int64>(nSize) * sizeof(AdenData), sizeof(nSize));
	else fout.seekp(0, fin.end);
	arrayData[nAmount - 1].index = fout.tellp();
	fout.write(buffer, length);

	fout.seekp(static_cast<__int64>(nAmount) * sizeof(AdenData), sizeof(nSize));
	arrayData[nAmount - 1].length = length;
	fout.write((char*)&arrayData[nAmount - 1], sizeof(AdenData));
#endif

//如果不是 DEBUG 模式，则直接从数据包处读取
#ifndef _ADEN_PACKAGE_DEBUG_
	fin.open(fileName + ".apf", ios_base::in | ios_base::out);
#endif

	fin.close(); fin.clear();
	return nAmount - 1;
}

char* ReadResource()
{

}