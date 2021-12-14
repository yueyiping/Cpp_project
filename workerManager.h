#pragma once
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "Boss.h"
#include <fstream>

using namespace std;

#define FILENAME "empFile.txt"

class WorkerManager
{
public:
	WorkerManager();

	void Show_Menu();
	void exit_System();

	void Add_Emp();

	void save();			// 存文件

	int get_EmpNum();       // 统计文件人数

	void init_Emp();		// 读文件
	bool Jud_Rep();

	void Show_Emp();

	void Del_Emp();

	int IsExist(int id);
	int IsExist(string name);
	int IsExist(int id, int index);

	void Mod_Emp();

	void Find_Emp();

	void Sort_Emp();

	void clean_File();

	~WorkerManager();

private:
	int m_EmpNum;
	Worker** m_EmpArray;

	bool m_FileIsEmpty;
};

