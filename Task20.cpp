#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Структура стать
enum sex{male, female};
//Структура курс
enum course{first, second, third, fourth, fifth};

//перевантаження оператора зсуву для виводу статі
ostream& operator<<(ostream& out, sex sx)
{
	if (sx==male)
		out <<"male";
	else
		out <<"female";
	return out;
}

//перевантаження оператора зсуву для вводу статі
istream& operator>>(istream& in, sex& sx)
{
	string temp_sx;
	in >>temp_sx;
	if (temp_sx=="male")
	{
		sx=male;
		return in;
	}
	if (temp_sx=="female")
	{
		sx=female;
		return in;
	}
	
	cout <<"Error sex type";
		exit(1);
	
	return in;
}

//перевантаження оператора зсуву для виводу курсу 
ostream& operator<<(ostream& out, course c)
{
	switch(c)
	{
	case first:
		{
			out <<"first";
			break;
		}
	case second:
		{
			out<<"second";
			break;
		}
	case third:
		{
			out <<"third";
			break;
		}
	case fourth:
		{
			out <<"fourth";
			break;
		}
	case fifth:
		{
			out <<"fifth";
			break;
		}
	}
	return out;
}



//перевантаження оператора зсуву для вводу курсу
istream& operator>>(istream& in, course& c)
{
	string temp_c;
	in >>temp_c; 
	if (temp_c==temp_c)
	{
		c=first;
		return in;
	}
	if (temp_c=="second")
	{
		c=second;
		return in;
	}
	if (temp_c=="third")
	{
		c=third;
		return in;
	}
	if (temp_c=="fourth")
	{
		c=fourth;
		return in;
	}
	if (temp_c=="fifth")
	{
		c=fifth;
		return in;
	}

	cout <<"Error course type";
	exit(1);
	return in;
}


//Структура студент
struct student
{
	char* fname;	//Ім'я
	char* lname;	//прызвище
	char* mname;	//Ім'я по батькові
	sex sx;			//Стать
	unsigned short age;//вік
	course c;		//Курс
};


//Функція  друку інформації про студента, що міститься у параметрі
void print_student_info(student st)
{
		cout <<st.lname<<"  "<<st.fname<<" "<<st.mname<<endl;
		cout <<st.sx<<"  Ege: "<<st.age<<endl;
		cout <<st.c<<" year student\n";
}


//Клас вектор
class vector 
{
	student *current;	//Масив елементів
	unsigned int size;	//Розмір
public:
	//конструктор по дефолту
	vector ()
	{
		current = new student;
		size=0;
	}
	//Конструктор для створення по розміру
	vector (unsigned int n):size(n)
	{
		current = new student[n];
	}
	//Конструктор для створення по розміру та значенню по замовчуванню
	vector (unsigned int n, student st)
	{
		current = new student[n];
		size=n;
		for (unsigned int i=0; i<n; i++)
		{
			current[i] = st;
		}
	}
	//Конструктор копіювання
	vector (vector & v)
	{
		current = new student;
		size=v.size;
		for (unsigned int i=0; i<v.size; i++)
		{
			current[i] = v.current[i];
		}
	}
	//Деструктор
	~vector ()
	{
		delete []current;
		size=0;
	}
	//Функція отримання розміру
	unsigned int Size()
	{
		return size;
	}
	//Перевантажений оператор індексації
	student& operator [](const unsigned int index)
	{
		if (index>=this->size)
		{
			cout <<"Index is out of range!\n";
			exit(0) ;
		}
		else
			return current[index];
	}
	//процедура  друку  вектора
	void print()
	{
		for (unsigned int i=0; i<size; i++)
		{
			print_student_info(current[i]);
		}
	}
	//Сеттер значення елемента вектора по індексу
	void Set (unsigned int index, student st)
	{
		current[index]=st;
	}
	
};

//Процедура зчитування із файлу
vector read_from_file()
{
	//Змінна для шляху до файлу
	string way;
	cout <<"Input way to file for reading:\n\t";
	cin >>way;
	//Змінна для файлу
	fstream fin;
	//Відкриваємо файл
	fin.open(way.c_str(), fstream::in);
	//Кількість записів у файлі
	unsigned int N;
	//Зчитування числа записів
	fin >>N;
	//Створення тимчасового вектора
	vector temp_v(N);
	for (unsigned int i=0; i<N, !fin.eof(); i++ )
	{
		fin >>temp_v[i].lname;
		fin >>temp_v[i].fname;
		fin >>temp_v[i].mname;
		fin >>temp_v[i].age;
		fin >>temp_v[i].sx;
		fin >>temp_v[i].c;
	}
	fin.close();
	return temp_v;
}

//процедура пошуку та виводу студентів найбільш поширеного віку 
void search_popular_age(vector v)
{
	unsigned int pop_age=v[0].age;
	unsigned int max=0, count=0;

	for (unsigned int i=0; i<v.Size(); i++)
	{
		for (unsigned int j=0; j<v.Size(); j++)
		{
			if (v[i].age==v[j].age)
				count++;
		}
		if (count>max)
		{
			max=count;
			pop_age=v[i].age;
		}
		
	}

	for (unsigned int i=0; i<count; i++)
		if (v[i].age==pop_age)
			print_student_info(v[i]);

}

//функція пошуку найбільш популярног імені студентів
char* search_popular_name(vector v)
{
	struct pair
	{
		char* name;
		unsigned int quantity;
	};
	pair* mas=new pair[v.Size()];

	unsigned int max=0, count=0;
	char* popular=v[0].fname;
l:	for (unsigned int i=0; i<v.Size(); i++)
	{
		for (unsigned int j=0; j<count; j++)
		{
			if (v[i].fname==mas[j].name)
			{
				mas[j].quantity++;
				goto l;
			}
		}
		mas[count+1].name=v[i].fname;
		mas[count+1].quantity=0;
		count++;
	}

	for (unsigned int j=0; j<count; j++)
		if (mas[j].quantity>max)
		{
			max=mas[j].quantity;
			popular=mas[j].name;
		}

	return popular;
}

//точка входу у програму
void main()
{
	//student st1, st2;
	//st1.fname="Vasyl";
	//st1.lname="Artemuk";
	//st1.mname="Yuriyovych";
	//st1.age=18;
	//st1.sx=male;
	//st1.c=first;
	//vector v(2, st1);
	//
	//
	//st2.fname="AAAA";
	//st2.lname="BBBB";
	//st2.mname="CCCC";
	//st2.age=20;
	//st2.sx=female;
	//st2.c=second;

	vector v=read_from_file();
	//v[1]=st2;
	v.print();

	//cout <<"\n"<<search_popular_name(v)<<"\n";
	search_popular_age(v);
}