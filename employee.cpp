
#include "employee.h"

Employee::Employee(int id, string name, int dId)//:m_Id(id),m_Name(name), m_DeptId(dId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = dId;
}

void Employee::showInfo()
{
	cout << "ְ����ţ�" << this->m_Id
		<< " \tְ��������" << this->m_Name
		<< " \t��λ��" << this->getDeptName()
		<< " \t��λְ����ɾ�����������" << endl;
}

string Employee::getDeptName()
{
	return string("Ա��");
}


