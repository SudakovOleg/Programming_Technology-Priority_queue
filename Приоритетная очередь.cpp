#include <iostream>

using namespace std;			//Стандартное простанство имен

struct Element			//Тип данных для хранения Элемента очереди
{
	double val = 0;		//Значение Элемента
	int priority = 0;	//Приоритет Элемента
};
struct Turn			//Создание очереди
{
	Element element;	//Элемент очереди
	Turn* next;			//Ссылка на следующий элемент
};			

void Init(Turn** begin)		//Инициализация списка, создаем первый элемент
{
	*begin = new Turn;
	(*begin)->next = NULL;
	(*begin)->element.priority = 1;		//Создаем элемент со значением 0 и минимальным приоритетом
	(*begin)->element.val = 0;
}
void AddElement(Turn **begin)	//Ввод значений и расстановка по приоритету
{
	//------------------Ввод элемента-----------------------------------//
	Element temp;						//Создание временой ячейки для хранения элемента
	cout << "Inter Element Value: ";
	cin >> temp.val;					//Ввод значений элемента: Число
	do
	{
		cout << endl << "Enter Priority(1-10): ";	//Ввод значений элемента: Приоритет (ограничен с 1-10)
		cin >> temp.priority;
	} while (temp.priority > 10 || temp.priority < 1);
	Turn *insert = new Turn;						//Создаем ячейку для вставки
	insert->element.val = temp.val;
	insert->element.priority = temp.priority;
	//-------------------Добавление элемента в очередь------------------//
	if (!(*begin)) //Если список пуст, то ставим в начало
	{
		insert->next = NULL;
		*begin = insert;
		return;
	}

	Turn* t = *begin;
	if (t->element.priority < insert->element.priority) //Если элемент должен быть в начале списка
	{
		insert->next = t;
		*begin = insert;
		return;
	}
	Turn* t1 = t->next;
	while (t1)
	{
		if (t1->element.priority < insert->element.priority) //Подбираем позицию по приоритету
		{
			t->next = insert;				//Вставляем элемент
			insert->next = t1;
			return;							//Выходим из функции
		}
		t = t1;
		t1 = t1->next;
	}
	t->next = insert;						//Если элемент должен стоять в конце
	insert->next = NULL;
	//---------------------------------------------------------------------//
}

void DelElement(Turn** begin)	//Удаляем элемент
{
	if (*begin == NULL)			//Если нет элементов
		return;
	Turn* t = *begin;			//Удаляем элемент с найвысшим приоритетом
	*begin = t->next;
	delete t;
}

void PrintTurn(Turn *begin) //Выводит очередь в консоль
{
	Turn* print = begin;	//Указатель на элемент который будет напечатан, ставим его в начало списка
	while (print != NULL)
	{
		cout << "Value: " << print->element.val << " | Priority: " << print->element.priority << " -> ";
		print = print->next;
	}
}

int Choose()
{
	//-------Меню-------//
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
		cin.clear(); // сбрасывает все биты потока, тоесть поток становится "хорошим"
		cin >> tempForChoose;
	}
	return tempForChoose;
	//-------------------//
}

void Free(Turn** begin) //Освобождаем память удаляя нашу очередь
{
	if (*begin == 0)	//Если ничего нету
		return;
	Turn* p = *begin;	//Указатель на стираемую ячейку
	Turn* t;			//Временный указатель

	while (p)			//Удаляем все ячейки из памяти с головы
	{
		t = p;
		p = p->next;
		delete t;
	}
	*begin = NULL;		//Прописываем отсутствие начала
}

int main()
{
	Turn* begin = NULL;		//Создаем указатель на начало списка
	Init(&begin);			//Инициализируем список
	int exit = 1;			//Флаг для выхода из программы
	do
	{
		switch (Choose())	//Принимаем выбор одного из вариантов в меню
		{
		case 1:
		{
			cout << endl << endl << "----------Add Element----------" << endl << endl;
			AddElement(&begin);		//Добавить элемент
			cout << endl << endl << "----------Complete----------" << endl << endl;
			break;
		}
		case 2:
		{
			cout << endl << endl << "----------Delete Element----------" << endl << endl;
			DelElement(&begin);		//Удалить элемент
			PrintTurn(begin);		//Вывести в консоль всю очередь
			cout << endl << endl << "----------Complete----------" << endl << endl;
			break;
		}
		case 3:
		{
			cout << endl << endl << "----------Print Element----------" << endl << endl;
			PrintTurn(begin);		//Вывести в консоль всю очередь
			cout << endl << endl << "----------Complete----------" << endl << endl;
			break;
		}
		case 0:
		{
			cout << endl << endl << "----------Delete Turn...----------" << endl;
			Free(&begin);//Освобождаем память
			cout << "----------Exit...----------" << endl << endl;
			exit = 0;//Опускаем флаг для выхода из цикла
			break;
		}
		default:					//В остальных случаях выйти из программы с ошибкой
			return 1;
			break;
		}
	} while (exit);					//Повторять процесс до команды выхода
	return 0;
}
