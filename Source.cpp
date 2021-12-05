/*
* Zachary Meisner
* CS210
* 12/4/2021
*/

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
// used to error check
#undef max

using namespace std;
/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python function you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python function you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


int main()
{
	// used for the main while loop
	int input = 0;
	// used for function input
	int userInput = 0;

	// main loop for program, display menu and exit on 3
	while (input != 3) {
		cout << "1: Display a Multiplication Table" << endl;
		cout << "2: Double a Value" << endl;
		cout << "3: Exit" << endl;
		cin >> input;

		// error checking for input other than int
		if (!cin) {
			system("CLS");
			cout << "Please enter 1, 2, or 3." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			system("pause");
			system("CLS");
			continue;

		}
		// switch case for menu input
		// case 1 returns a multiplication table
		switch (input) {
		case 1: if (input == 1) {
			system("CLS");
			cout << "Please enter any number." << endl;
			cin >> userInput;
			if (!cin) {
				system("CLS");
				cout << "Incorrect input, please enter a number." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				system("pause");
				system("CLS");
				continue;
			}
			cout << callIntFunc("MultiplicationTable", userInput) << endl;
			system("pause");
			system("CLS");
		}

		// case 2 returns a number X 2
		case 2: if (input == 2) {
			system("CLS");
			cout << "Please enter any number." << endl;
			cin >> userInput;
			if (!cin) {
				system("CLS");
				cout << "Incorrect input, please enter a number." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				system("pause");
				system("CLS");
				continue;
			}
			cout << callIntFunc("DoubleValue", userInput) << endl;
			system("pause");
			system("CLS");
		}
		// exit the program if the input is 3
		case 3: if (input == 3) {
			system("CLS");
			cout << "Bye!" << endl;
			system("pause");
			system("CLS");
		}
		// error checking for number input to make sure input stays between 1 & 3
		default: if ((input <= 0) || (input > 3)) {
			system("CLS"); 
			cout << "Please enter 1, 2, or 3." << endl;
			system("pause");
			system("CLS");
		}
		}
	}
}