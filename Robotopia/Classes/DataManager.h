﻿//
// DataManager.h
//
// 작성자 : 남현욱
//
//
// 외부 파일에서 Data를 가져오는 작업 및 외부 파일에 Data를 쓰는 것과 관련된 작업을 담당한다.
//
//
#pragma once
#include "DataType.h"
#define MODULE_FILE_NAME(N) ("data/module.xml")


class DataManager
{
public:
	DataManager();
	~DataManager();

	bool						init();

	bool						loadModuleData();
	bool						saveModuleData();

private:

	std::vector<moduleData>		m_ModuleDatas[DIR_MAX];
};