#ifndef _ADEN_PACKAGE_H_
#define _ADEN_PACKAGE_H_

#include <iostream>
#include <fstream>
#include <string>

//AdenPackage������غ�
//��������ú꣬��ȡ����ʱ��Դ�ļ�����ȡ���������ݰ�
//���ȡ�������ú꣬��ȡ����������ݰ��ж�ȡ

//#define _ADEN_PACKAGE_DEBUG_

struct AdenData
{
	std::streamoff index;				//���������������ݵ�ֵ
	size_t length;						//���������ݵĳ�������
};

class AdenPackageFile
{
public:
	AdenPackageFile(std::string, size_t);
	~AdenPackageFile();

	size_t LoadResource(const char*);	//������Դ����
	char* ReadResource(size_t);			//��ȡ��Դ����
private:
	std::string fileName;

	std::ifstream fin;					//��ȡ�ļ���
	std::ofstream fout;					//����ļ���

	size_t nSize;						//��������������Ĵ�С
	size_t nAmount;						//����ʵ��Ԫ�ظ���
	AdenData* arrayData;				//�������������Ե�����
};

#endif // _ADEN_PACKAGE_