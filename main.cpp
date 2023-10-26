#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <dirent.h>
using namespace std;

class company
{
	string designation, name, address, salary, empid, age,path;
	char *find;

public:
	company()
	{
		cout<<"Enter the path of file : ";
		getline(cin,path);
	}
	string get_id()
	{
		cout << "employee id :";
		cin >> empid;
		return empid;
	}
	void get_data();
	void display_one_employee_data();
	void display_all_employee_data();
	void write_data();
	void display_all_employee_list();
	bool check_exist(string id);
	void remove_data();
	void modify_data();
};

void company::display_all_employee_data()
{
	string data;
	ifstream read(path+"\\data.txt");
	while (getline(read, data))
		cout << data << endl;
	read.close();
}
void company ::display_all_employee_list()
{
	string data;
	ifstream read(path+"\\data.txt");
	if (getline(read, data))
		cout << data << endl;
	else
	{
		cout << "no data found to print" << endl;
		return;
	}
	while (getline(read, data))
	{
		if (data == "")
		{
			getline(read, data);
			cout << data << endl;
		}
	}
	read.close();
}
void company ::write_data()
{
	ofstream write(path+"\\data.txt", std::ios_base::app);
	write << "employee id : " << empid << endl;
	write << "full Name : " << name << endl;
	write << "age : " << age << endl;
	write << "designation : " << designation << endl;
	write << "salary : " << salary << endl;
	write << "address : " << address << endl;
	write << endl;
	write.close();
}

void company ::remove_data()
{
	string data;
	int count = 7;
	cout << "To remove data enter the ";
	get_id();
	ofstream writet(path+"\\temp.txt");
	ifstream read(path+"\\data.txt");
	while (getline(read, data))
	{
		if (data == "employee id : " + empid || (count > 0 && count != 7))
			count--;
		else
		{
			writet << data << endl;
		}
	}

	writet.close();
	read.close();

	ofstream write(path+"\\data.txt");
	ifstream readt(path+"\\temp.txt");
	while (getline(readt, data))
	{
		write << data << endl;
	}
	if (count == 7)
		cout << "No data found to remove" << endl;
	else
		cout << "data removed successfully ";
	readt.close();
	write.close();
}

void company ::modify_data()
{
	string data;
	int count = 6;
	cout << "To modify the data enter existing ";
	string check = get_id();
	ofstream writet(path+"\\temp.txt");
	ifstream read(path+"\\data.txt");
	while (getline(read, data))
	{
		if (data == "employee id : " + check || (count > 0 && count != 6))
			count--;
		else
		{
			writet << data << endl;
		}
		if (count == 0)
		{
			cout << "Enter new ";
			while (check_exist(get_id()))
			{
				cout << "Entered id is alreadu exist" << endl;
				cout << "Enter different ";
			}
			get_data();
			writet << "employee id : " << empid << endl;
			writet << "full Name : " << name << endl;
			writet << "age : " << age << endl;
			writet << "designation : " << designation << endl;
			writet << "salary : " << salary << endl;
			writet << "address : " << address << endl;
			count = -1;
		}
	}
	writet.close();
	read.close();
	cout<<"here2"<<endl;
	ofstream write(path+"\\data.txt");
	ifstream readt(path+"\\temp.txt");
	while (getline(readt, data))
	{
		write << data << endl;
	}
	if (count == 6)
		cout << "No data found to modify" << endl;
	else
		cout << "data modified successfully " << endl;
	readt.close();
	write.close();
}
void company ::get_data()
{
	cout << "full Name : ";
	cin.sync();
	getline(cin, name);
	cout << "age : ";
	cin >> age;
	cout << "designation : ";
	cin.sync();
	cin >> designation;
	cout << "salary : ";
	cin >> salary;
	cout << "address : ";
	cin.sync();
	getline(cin, address);
}

void company ::display_one_employee_data()
{
	string data;
	int count = 6;
	get_id();
	ifstream read(path+"\\data.txt");

	while (getline(read, data))
		if (data == "employee id : " + empid)
		{
			cout<<"\ndata stored in file : "<<endl<<endl;
			while (count)
			{
				cout << data << endl;
				getline(read, data);
				count--;
			}
			read.close();
			return;
		}
	cout << "No data found" << endl;
	read.close();
}
bool company::check_exist(string id)
{
	string data;
	ifstream read(path+"\\data.txt");

	while (getline(read, data))
		if (data == "employee id : " + id)
		{
			read.close();
			return true;
		}
	read.close();
	return false;
}

int main()
{
	int ch;
	company emp;
	system("cls");
	while (1)
	{
		cout << "\nselect the option:\n";
		cout << "\n1) To add employee data" << endl
			 << "2) To remove employee data" << endl
			 << "3) Modify the employee data" << endl
			 << "4) Display one employee data" << endl
			 << "5) Display all employee data" << endl
			 << "6) List of all employe\n7)quit\n\nEnter the option-->";
		cin >> ch;
		system("cls");
		switch (ch)
		{
		case 1:
			if (emp.check_exist(emp.get_id()))
				cout << "data already exist";
			else
			{
				emp.get_data();
				emp.write_data();
			}
			break;

		case 2:
			emp.remove_data();
			break;

		case 3:
			emp.modify_data();
			break;

		case 4:
			emp.display_one_employee_data();
			break;

		case 5:
			emp.display_all_employee_data();
			break;

		case 6:
			emp.display_all_employee_list();
			break;

		case 7:
			return 0;

		default:
			cout << "Enter correct option \n\n";
		}
	}
	return 0;
};