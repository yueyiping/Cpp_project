#include "workerManager.h"


#pragma warning(disable:6386)    //�������

WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open())
	{
		cout << "�ļ������ڣ�" << endl;
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
		cout << "�ļ�Ϊ�գ�" << endl;
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

	this->m_FileIsEmpty = false;       // ˢ�±�־λ
	cout << "��ʼ����ȡ�ɹ���" << endl;
}
  
void WorkerManager::Show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ�� **********" << endl;
	cout << "*************  0.�˳��������  *************" << endl;
	cout << "*************  1.����ְ����Ϣ  *************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ����ְְ��  *************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
	cout << "*************  5.����ְ����Ϣ  *************" << endl;
	cout << "*************  6.���ձ������  *************" << endl;
	cout << "*************  7.��������ĵ�  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void WorkerManager::exit_System()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}
 
void WorkerManager::Add_Emp()
{
	int AddNum;
	cout << "��������ӵ�Ա�������� " << endl;
	cin >> AddNum;

	if (AddNum > 0)
	{
		int SumNum = m_EmpNum + AddNum;
		Worker** worker_temp = new Worker * [SumNum];
		if (worker_temp == nullptr)
		{
			cout << "�ڴ治�㣡" << endl;
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

			cout << "�������" << i + 1 << "��Ա��id��" << endl;
			cin >> id;

			while (this->m_EmpNum > 0)	// �ж��ظ�ID
			{
				int judge = 0;
				for (int j = 0; j < this->m_EmpNum; j++)
				{
					if (worker_temp[j]->m_Id == id)
					{
						cout << "����ظ������������룺" << endl;
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

			cout << "�������" << i + 1 << "��Ա��������" << endl;
			cin >> name;

			cout << "��ѡ��Ա����λ��" << endl;
			cout << "1����ͨԱ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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
				cout << "��������" << endl;
				system("pause");
				exit(0);
			}
		}

		if (this->m_EmpArray != nullptr)
		{
			delete[] this->m_EmpArray;
		}

		this->m_EmpArray = worker_temp;

		this->m_FileIsEmpty = false;       // ˢ�±�־λ

		cout << "¼��ɹ���" << AddNum << "�������� " << this->m_EmpNum <<"��" << endl;

		this->save();
	}
	else
	{
		cout << "��������" << endl;
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
			cout << "�� " << index  << " �в������ݶ�ȡ�������飡" << endl;
			system("pause");
			exit(1);
		}
	}
	/* �ж϶�ȡ����ظ� */
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
				cout << "�� " << i + 1 << " ��id���ݺ͵� " << j + 1 << " ��id�����ظ������飡" << endl;
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
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;	
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
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��������Ҫɾ����ְ����ţ�" << endl;
		int id;
		cin >> id;
		
		int index = this->IsExist(id);
		if (index == -1)
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ��ñ�ŵ�ְ����" << endl;
		}
		else
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;

			delete this->m_EmpArray[m_EmpNum];
			this->m_EmpArray[m_EmpNum] = nullptr;      // ����ɾ����������Ŀռ�

			this->save();
			cout << "ɾ���ɹ�!" << endl;
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
			return i;   // ���ص��������λ�ã���0��ʼ����
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
			return i;   // ���ص��������λ�ã���0��ʼ����
		}
	}
	return -1;
}

void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��������Ҫ�޸ĵ�ְ����ţ�" << endl;
		int id;
		cin >> id;
		int index = this->IsExist(id);
		if (index == -1)
		{
			cout << "�޸�ʧ�ܣ�δ�ҵ��ñ�ŵ�ְ����" << endl;
		}
		else
		{
			int newid = 0;
			string mod_name = " ";
			int mod_dId = 0;

			cout << "�鵽 " << id << " ��ְ�����������µ�ְ����ţ�" << endl;
			cin >> newid;

			while (this->IsExist(newid, index) != -1)	 // �ж��ظ���ţ���������
			{
				cout << "id����ظ������������룺 " << endl;
				cin >> newid;
			}

			cout << "��������������" << endl;
			cin >> mod_name;

			cout << "��ѡ��Ա����λ��" << endl;
			cout << "1����ͨԱ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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
					cout << "��Ϣ���ĳɹ�!" << endl;
					return;
				}
				else
				{
					cout << "���ű���������������룺 " << endl;
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
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��������ҷ�ʽ��" << endl;
		cout << "1����id��Ų���" << endl;
		cout << "2����Ա����������" << endl;
		int select;
		cin >> select;
		while (true)
		{
			if (select == 1)
			{
				cout << "��������Ҫ���ҵ�id��" << endl;
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
					cout << "ְ��������!" << endl;
					continue;
				}
			}
			else if (select == 2)
			{
				cout << "��������Ҫ���ҵ�������" << endl;
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
					cout << "ְ��������!" << endl;
					continue;
				}
			}
			else
			{
				cout << "�����������������룺" << endl;
				cin >> select;
			}
		
		}

	}
}

void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "1����ְ���Ž�������" << endl;
		cout << "2����ְ���Ž��н���" << endl;
		int select;
		cin >> select;

		while (select != 1 && select != 2)   // ����
		{
			cout << "���������룺" << endl;
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
		cout << "����ɹ������Ϊ��" << endl;
		this->save();
		this->Show_Emp();

	}
}

void WorkerManager::clean_File()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "ȷ����գ�" << endl;
		cout << "1��ȷ��" << endl;
		cout << "2��ȡ��" << endl;
		int select;
		cin >> select;

		while (select != 1 && select != 2)   // ����
		{
			cout << "���������룺" << endl;
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
			cout << "��Ϣ��ճɹ���" << endl;
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
