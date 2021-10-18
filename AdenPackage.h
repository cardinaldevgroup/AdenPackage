// ����꿪�أ�������Ϊ DEBUG ģʽ���ر���Ϊ RELEASE ģʽ
// DEBUG ģʽ�£����������Դʱ����Դ�ļ�����ȡ���������ݲ������Ӧ�İ���
// RELEASE ģʽ�£����󹹽�ʱ��ȡ�����ڴ沢������ϣ��������Դʱֱ�Ӵӹ�ϣ���з���

#define _ADEN_PACKAGE_DEBUG_

#ifndef _ADEN_PACKAGE_H_
#define _ADEN_PACKAGE_H_

#include <fstream>
#include <string>
#include <unordered_map>

enum
{
	ADEN_MAX_LENGTH = 64													//Դ�ļ����·����󳤶�
};

struct AdenData																//���������������ļ�
{
	size_t length;
	char* data;
};

class AdenPackageFile
{
public:
	AdenPackageFile(std::string packagePath);
	~AdenPackageFile();														//�������������ͷ��ڴ��е����ж���������

	AdenData* LoadResource(std::string dataPath);

private:
	std::string pathName;													//�����ư���
	std::unordered_map<std::string, AdenData*> mapIndex;					//����������������ϣ��

	std::ofstream fout;														//DEBUG ģʽ����д��
};


#endif // !_ADEN_PACKAGE_H_