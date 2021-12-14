#include "workerManager.h"


#pragma warning(disable:6386)    //清除警告

WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open())
	{
		cout << "文件不存在！" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = nullptr;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	// if((ifs >> ch).eof())
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空！" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = nullptr;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	this->m_EmpNum = this->get_EmpNum();
	this->m_EmpArray = new Worker * [m_EmpNum];
	this->init_Emp();

	//ifs.close();

	this->m_FileIsEmpty = false;       // 刷新标志位
	cout << "初始化读取成功！" << endl;
}
  
void WorkerManager::Show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void WorkerManager::exit_System()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}
 
void WorkerManager::Add_Emp()
{
	int AddNum;
	cout << "请输入添加的员工个数： " << endl;
	cin >> AddNum;

	if (AddNum > 0)
	{
		int SumNum = m_EmpNum + AddNum;
		Worker** worker_temp = new Worker * [SumNum];
		if (worker_temp == nullptr)
		{
			cout << "内存不足！" << endl;
			system("pause");
			return;
		}

		if (!this->m_FileIsEmpty)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				worker_temp[i] = this->m_EmpArray[i];
				//worker_temp[i]->showInfo();
			}
		}

		for(int i = 0;i < AddNum; i++)
		{
			int id;
			string name;
			int deptId;

			cout << "请输入第" << i + 1 << "个员工id：" << endl;
			cin >> id;

			while (this->m_EmpNum > 0)	// 判断重复ID
			{
				int judge = 0;
				for (int j = 0; j < this->m_EmpNum; j++)
				{
					if (worker_temp[j]->m_Id == id)
					{
						cout << "编号重复，请重新输入：" << endl;
						cin >> id;
						break;
					}
					else
					{
						judge = 1;
					}
				}
				if (judge == 1)
				{
					break;
				}
			}

			cout << "请输入第" << i + 1 << "个员工姓名：" << endl;
			cin >> name;

			cout << "请选择员工岗位：" << endl;
			cout << "1、普通员工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> deptId;

			switch (deptId)
			{
			case 1:
				worker_temp[this->m_EmpNum++] = new Employee(id, name, deptId);
				break;
			case 2:
				worker_temp[this->m_EmpNum++] = new Manager(id, name, deptId);
				break;
			case 3:
				worker_temp[this->m_EmpNum++] = new Boss(id, name, deptId);
				break;
			default:
				cout << "输入有误！" << endl;
				system("pause");
				exit(0);
			}
		}

		if (this->m_EmpArray != nullptr)
		{
			delete[] this->m_EmpArray;
		}

		this->m_EmpArray = worker_temp;

		this->m_FileIsEmpty = false;       // 刷新标志位

		cout << "录入成功：" << AddNum << "个，共计 " << this->m_EmpNum <<"个" << endl;

		this->save();
	}
	else
	{
		cout << "输入有误！" << endl;
	}
	system("pause");
	system("cls");
}

void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId<< endl;
	}
	ofs.close();
}

int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME,  ios::in);

	int id;
	string name;
	int dId;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		num++;
	}
	ifs.close();

	return num;
}

void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	int index = 0;

	while(ifs >> id && ifs >> name && ifs >> dId)
	{
		switch (dId)
		{
		case 1:
			this->m_EmpArray[index++] = new Employee(id, name, dId);
			break;
		case 2:
			this->m_EmpArray[index++] = new Manager(id, name, dId);
			break;
		case 3:
			this->m_EmpArray[index++] = new Boss(id, name, dId);
			break;
		default:
			cout << "第 " << index  << " 行部门数据读取错误，请检查！" << endl;
			system("pause");
			exit(1);
		}
	}
	/* 判断读取编号重复 */
	if (this->Jud_Rep())
	{
		delete[] this->m_EmpArray;
		system("pause");
		exit(1);
	}

	ifs.close();
}

bool WorkerManager::Jud_Rep()
{
	for (int i = 0; i < this->m_EmpNum - 1; i++)
	{
		for (int j = i + 1; j < this->m_EmpNum; j++)
		{
			if (this->m_EmpArray[i]->m_Id == this->m_EmpArray[j]->m_Id)
			{
				cout << "第 " << i + 1 << " 行id数据和第 " << j + 1 << " 行id数据重复，请检查！" << endl;
				return true;
			}
		}
	}
	return false;
}

void WorkerManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;	
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入需要删除的职工编号：" << endl;
		int id;
		cin >> id;
		
		int index = this->IsExist(id);
		if (index == -1)
		{
			cout << "删除失败，未找到该编号的职工！" << endl;
		}
		else
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;

			delete this->m_EmpArray[m_EmpNum];
			this->m_EmpArray[m_EmpNum] = nullptr;      // 可以删掉最后多出来的空间

			this->save();
			cout << "删除成功!" << endl;
		}

	}
	system("pause");
	system("cls");
}

int WorkerManager::IsExist(int id)
{
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (id == this->m_EmpArray[i]->m_Id)
		{
			return i;   // 返回的是数组的位置，从0开始的数
		}
	}
	return -1;
}

int WorkerManager::IsExist(string name)
{
	int num = 0;
	int flag = 0;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (name == this->m_EmpArray[i]->m_Name)
		{
			flag = 1;
			num++;
			this->m_EmpArray[i]->showInfo();
		}
	}
	if (flag == 1)
	{
		return num;
	}
	else
	{
	return -1;
	}
}

int WorkerManager::IsExist(int id, int index)
{
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (id == this->m_EmpArray[i]->m_Id && i != index)
		{
			return i;   // 返回的是数组的位置，从0开始的数
		}
	}
	return -1;
}

void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入需要修改的职工编号：" << endl;
		int id;
		cin >> id;
		int index = this->IsExist(id);
		if (index == -1)
		{
			cout << "修改失败，未找到该编号的职工！" << endl;
		}
		else
		{
			int newid = 0;
			string mod_name = " ";
			int mod_dId = 0;

			cout << "查到 " << id << " 号职工，请输入新的职工编号：" << endl;
			cin >> newid;

			while (this->IsExist(newid, index) != -1)	 // 判断重复编号，除自身外
			{
				cout << "id编号重复，请重新输入： " << endl;
				cin >> newid;
			}

			cout << "请输入新姓名：" << endl;
			cin >> mod_name;

			cout << "请选择员工岗位：" << endl;
			cout << "1、普通员工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> mod_dId;

			while (true)
			{
				if (mod_dId == 1 || mod_dId == 2 || mod_dId == 3)
				{
					delete this->m_EmpArray[index];
					switch (mod_dId)
					{
					case 1:
						this->m_EmpArray[index] = new Employee(newid, mod_name, mod_dId);
						break;
					case 2:
						this->m_EmpArray[index] = new Manager(newid, mod_name, mod_dId);
						break;
					case 3:
						this->m_EmpArray[index] = new Boss(newid, mod_name, mod_dId);
						break;
					}
					this->save();
					cout << "信息更改成功!" << endl;
					return;
				}
				else
				{
					cout << "部门编号有误，请重新输入： " << endl;
					cin >> mod_dId;
				}
			}

		}

	}
	system("pause");
	system("cls");
}

void WorkerManager::Find_Emp()
{
	if(this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请输入查找方式：" << endl;
		cout << "1、按id编号查找" << endl;
		cout << "2、按员工姓名查找" << endl;
		int select;
		cin >> select;
		while (true)
		{
			if (select == 1)
			{
				cout << "请输入需要查找的id：" << endl;
				int id;
				cin >> id;
				int index = this->IsExist(id);
				if (index != -1)
				{
					this->m_EmpArray[index]->showInfo();
					system("pause");
					system("cls");
					return;
				}
				else
				{
					cout << "职工不存在!" << endl;
					continue;
				}
			}
			else if (select == 2)
			{
				cout << "请输入需要查找的姓名：" << endl;
				string name;
				cin >> name;
				int index = this->IsExist(name);
				if (index != -1)
				{
					system("pause");
					system("cls");
					return;
				}
				else
				{
					cout << "职工不存在!" << endl;
					continue;
				}
			}
			else
			{
				cout << "输入有误，请重新输入：" << endl;
				cin >> select;
			}
		
		}

	}
}

void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式：" << endl;
		cout << "1、按职工号进行升序" << endl;
		cout << "2、按职工号进行降序" << endl;
		int select;
		cin >> select;

		while (select != 1 && select != 2)   // 保护
		{
			cout << "请重新输入：" << endl;
			cin >> select;
		}

		for (int i = 0; i < this->m_EmpNum - 1; i++)
		{
			int temp_num = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)
				{
					if (this->m_EmpArray[temp_num]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						temp_num = j;
					}
				}
				else if (select == 2)
				{
					if (this->m_EmpArray[temp_num]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						temp_num = j;
					}
				}
			}
			if (i != temp_num)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[temp_num];
				this->m_EmpArray[temp_num] = temp;
			}

		}
		cout << "排序成功，结果为：" << endl;
		this->save();
		this->Show_Emp();

	}
}

void WorkerManager::clean_File()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "确认清空？" << endl;
		cout << "1、确认" << endl;
		cout << "2、取消" << endl;
		int select;
		cin >> select;

		while (select != 1 && select != 2)   // 保护
		{
			cout << "请重新输入：" << endl;
			cin >> select;
		}

		if (select == 1)
		{
			ofstream ofs(FILENAME, ios::trunc);
			ofs.close();

			if (this->m_EmpArray != nullptr)
			{
				for (int i = 0; i < this->m_EmpNum; i++)
				{
					if (this->m_EmpArray[i] != nullptr)
					{
						delete this->m_EmpArray[i];
						this->m_EmpArray[i] = nullptr;
					}
				}
				delete[] this->m_EmpArray;
				this->m_EmpArray = nullptr;
				this->m_EmpNum = 0;
				this->m_FileIsEmpty = true;
			}
			cout << "信息清空成功！" << endl;
		}

	}

	system("pause");
	system("cls");
}

WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != nullptr)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = nullptr;
	}
}
