#include "AdenPackage.h"
using namespace std;

AdenPackageFile::~AdenPackageFile()
{
	delete[] arrayData;
}

AdenPackageFile::AdenPackageFile(std::string name, size_t size) :fileName(name), nSize(size), nAmount(0)
{
	arrayData = new AdenData[size];
	fout.open(name + ".apf", ios_base::out | ios_base::binary); //���ݰ��ļ���׺Ϊ .apf

	//д��ö����ư�������
	fout.seekp(0);
	fout.write((char*)&nSize, sizeof(nSize)) << flush; //���������������С
}

size_t AdenPackageFile::LoadResource(const char* path)
{
//������ DEBUG ģʽ�����Դ�ļ�����ȡ�����������ݰ�
#ifdef _ADEN_PACKAGE_DEBUG_
	fin.open(path, ios_base::in | ios_base::binary);
	fin.seekg(0, fin.end);
	size_t length = fin.tellg();
	fin.seekg(0, fin.beg);
	char* buffer = new char[length];
	fin.read(buffer, length);
	fin.close(); fin.clear();

	//����ǵ�һ�����ݣ�����������濪ʼд�룬����ճ������λ��
	if (++nAmount == 1) fout.seekp(static_cast<__int64>(nSize) * sizeof(AdenData), sizeof(nSize));
	else fout.seekp(0, fin.end);
	arrayData[nAmount - 1].index = fout.tellp();
	fout.write(buffer, length);

	fout.seekp(static_cast<__int64>(nAmount) * sizeof(AdenData), sizeof(nSize));
	arrayData[nAmount - 1].length = length;
	fout.write((char*)&arrayData[nAmount - 1], sizeof(AdenData));
#endif

//������� DEBUG ģʽ����ֱ�Ӵ����ݰ�����ȡ
#ifndef _ADEN_PACKAGE_DEBUG_
	fin.open(fileName + ".apf", ios_base::in | ios_base::out);
#endif

	fin.close(); fin.clear();
	return nAmount - 1;
}

char* ReadResource()
{

}