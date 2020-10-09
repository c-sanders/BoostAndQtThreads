#include <TestClass.hpp>


TestClass::TestClass
(
 QWidget * parent
)
{
	const
	string   nameMethod = "TestClass Ctor : ";


	cout << nameMethod << "Enter" << endl;

	cout << nameMethod << "Exit" << endl;
}


TestClass::~TestClass
(
)
{
	const
	string   nameMethod = "TestClass Dtor : ";


	cout << nameMethod << "Enter" << endl;

	cout << nameMethod << "Exit" << endl;
}


void
TestClass::slot_test
(
 int   value
)
{
	const
	string   nameMethod = "TestClass::slot_test : ";


	cout << nameMethod << "Enter" << endl;

	this->value = value;

	cout << nameMethod << "value = " << this->value << endl;

	cout << nameMethod << "Exit" << endl;	
}

