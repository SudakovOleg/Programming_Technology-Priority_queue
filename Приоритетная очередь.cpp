#include <iostream>

using namespace std;			//����������� ����������� ����

struct Element			//��� ������ ��� �������� �������� �������
{
	double val = 0;		//�������� ��������
	int priority = 0;	//��������� ��������
};
struct Turn			//�������� �������
{
	Element element;	//������� �������
	Turn* next;			//������ �� ��������� �������
};			

void Init(Turn** begin)		//������������� ������, ������� ������ �������
{
	*begin = new Turn;
	(*begin)->next = NULL;
	(*begin)->element.priority = 1;		//������� ������� �� ��������� 0 � ����������� �����������
	(*begin)->element.val = 0;
}
void AddElement(Turn **begin)	//���� �������� � ����������� �� ����������
{
	//------------------���� ��������-----------------------------------//
	Element temp;						//�������� �������� ������ ��� �������� ��������
	cout << "Inter Element Value: ";
	cin >> temp.val;					//���� �������� ��������: �����
	do
	{
		cout << endl << "Enter Priority(1-10): ";	//���� �������� ��������: ��������� (��������� � 1-10)
		cin >> temp.priority;
	} while (temp.priority > 10 || temp.priority < 1);
	Turn *insert = new Turn;						//������� ������ ��� �������
	insert->element.val = temp.val;
	insert->element.priority = temp.priority;
	//-------------------���������� �������� � �������------------------//
	if (!(*begin)) //���� ������ ����, �� ������ � ������
	{
		insert->next = NULL;
		*begin = insert;
		return;
	}

	Turn* t = *begin;
	if (t->element.priority < insert->element.priority) //���� ������� ������ ���� � ������ ������
	{
		insert->next = t;
		*begin = insert;
		return;
	}
	Turn* t1 = t->next;
	while (t1)
	{
		if (t1->element.priority < insert->element.priority) //��������� ������� �� ����������
		{
			t->next = insert;				//��������� �������
			insert->next = t1;
			return;							//������� �� �������
		}
		t = t1;
		t1 = t1->next;
	}
	t->next = insert;						//���� ������� ������ ������ � �����
	insert->next = NULL;
	//---------------------------------------------------------------------//
}

void DelElement(Turn** begin)	//������� �������
{
	if (*begin == NULL)			//���� ��� ���������
		return;
	Turn* t = *begin;			//������� ������� � ��������� �����������
	*begin = t->next;
	delete t;
}

void PrintTurn(Turn *begin) //������� ������� � �������
{
	Turn* print = begin;	//��������� �� ������� ������� ����� ���������, ������ ��� � ������ ������
	while (print != NULL)
	{
		cout << "Value: " << print->element.val << " | Priority: " << print->element.priority << " -> ";
		print = print->next;
	}
}

int Choose()
{
	//-------����-------//
	int tempForChoose = 0;
	cout << "1) Add element" << endl;
	cout << "2) Delete element" << endl;
	cout << "3) Print element" << endl;
	cout << "0) Exit" << endl;
	cout << "__________________" << endl;
	cout << "Your choose: ";
	while (!(cin >> tempForChoose) || cin.get() != '\n')
	{
		cout << "IDIOT !! Enter again !\n";
		cin.sync();
		cin.clear(); // ���������� ��� ���� ������, ������ ����� ���������� "�������"
		cin >> tempForChoose;
	}
	return tempForChoose;
	//-------------------//
}

void Free(Turn** begin) //����������� ������ ������ ���� �������
{
	if (*begin == 0)	//���� ������ ����
		return;
	Turn* p = *begin;	//��������� �� ��������� ������
	Turn* t;			//��������� ���������

	while (p)			//������� ��� ������ �� ������ � ������
	{
		t = p;
		p = p->next;
		delete t;
	}
	*begin = NULL;		//����������� ���������� ������
}

int main()
{
	Turn* begin = NULL;		//������� ��������� �� ������ ������
	Init(&begin);			//�������������� ������
	int exit = 1;			//���� ��� ������ �� ���������
	do
	{
		switch (Choose())	//��������� ����� ������ �� ��������� � ����
		{
		case 1:
		{
			cout << endl << endl << "----------Add Element----------" << endl << endl;
			AddElement(&begin);		//�������� �������
			cout << endl << endl << "----------Complete----------" << endl << endl;
			break;
		}
		case 2:
		{
			cout << endl << endl << "----------Delete Element----------" << endl << endl;
			DelElement(&begin);		//������� �������
			PrintTurn(begin);		//������� � ������� ��� �������
			cout << endl << endl << "----------Complete----------" << endl << endl;
			break;
		}
		case 3:
		{
			cout << endl << endl << "----------Print Element----------" << endl << endl;
			PrintTurn(begin);		//������� � ������� ��� �������
			cout << endl << endl << "----------Complete----------" << endl << endl;
			break;
		}
		case 0:
		{
			cout << endl << endl << "----------Delete Turn...----------" << endl;
			Free(&begin);//����������� ������
			cout << "----------Exit...----------" << endl << endl;
			exit = 0;//�������� ���� ��� ������ �� �����
			break;
		}
		default:					//� ��������� ������� ����� �� ��������� � �������
			return 1;
			break;
		}
	} while (exit);					//��������� ������� �� ������� ������
	return 0;
}
