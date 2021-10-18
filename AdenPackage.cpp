#include "AdenPackage.h"

#include<iostream>

using namespace std;

AdenPackageFile::~AdenPackageFile()
{
	fout.close(); fout.clear();
	for (auto iter = mapIndex.begin(); iter != mapIndex.end(); iter++)
	{
		delete[] iter->second->data;
		delete iter->second;
	}
}

AdenPackageFile::AdenPackageFile(string packagePath)
{
	pathName = packagePath;
	
#ifdef _ADEN_PACKAGE_DEBUG_
	fout.open(pathName + ".apf", ios_base::out | ios_base::binary);

#else
	ifstream fin(pathName + ".apf", ios_base::in | ios_base::binary);

	while (fin.tellg() != EOF)
	{
		char path[ADEN_MAX_LENGTH] = { '\0' }; size_t length;
		fin.read(path, ADEN_MAX_LENGTH);
		fin.read((char*)&length, sizeof(length));
		char* buffer = new char[length];
		fin.read(buffer, length);

		AdenData* pData = new AdenData();
		pData->data = buffer; pData->length = length;
		mapIndex[path] = pData;
	}
	fin.close(); fin.clear();
#endif
}

AdenData* AdenPackageFile::LoadResource(string dataPath)
{
#ifdef _ADEN_PACKAGE_DEBUG_
	ifstream fin(dataPath.c_str(), ios_base::in | ios_base::binary);
	if (fin.is_open())
	{
		fin.seekg(0, fin.end);
		size_t length = fin.tellg();
		fin.seekg(0, fin.beg);
		char* buffer = new char[length];
		fin.read(buffer, length);
		fin.close(); fin.clear();

		AdenData* pData = new AdenData();
		pData->data = buffer; pData->length = length;
		mapIndex[dataPath] = pData;

		char path[ADEN_MAX_LENGTH] = { '\0' };
		strcpy_s(path, dataPath.c_str());
		fout.write(path, ADEN_MAX_LENGTH);
		fout.write((char*)&length, sizeof(length));
		fout.write(buffer, length) << flush;

		return pData;
	}
	return nullptr;

#else
	return mapIndex[dataPath];
#endif
}