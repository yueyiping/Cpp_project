#include "workerManager.h"
#include <string>
#include "employee.h"
#include "manager.h"
#include "boss.h"


int main()
{
	//Worker* worker = NULL;
	//worker = new Employee(1,"张三",1);
	//worker->showInfo();
	//delete worker;

	//worker = new Manager(2, "李四", 1);
	//worker->showInfo();
	//delete worker;	

	//worker = new Boss(3, "王五", 1);
	//worker->showInfo();
	//delete worker;


	WorkerManager wm;
	int m_choice = 0;
	while (true)
	{
		wm.Show_Menu();
		cout << "请输入序号：" << endl;
		cin >> m_choice;
		while (cin.fail())
		{
			cout << "请重新输入序号：" << endl;
			cin.clear();
			//cin.sync();
			cin.ignore();
			while (cin.get())
			{
				cin >> m_choice;
			}
		}

		switch (m_choice)
		{
		case 0:
			wm.exit_System();
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		default:
			system("cls");
			break;
		}
	}

	//system("pause");
	return 0;
}