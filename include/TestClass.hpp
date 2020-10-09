#ifndef TESTCLASS_HPP
#define TESTCLASS_HPP


#include <iostream>
#include <string>

#include <QtCore/QThread>


using std::cout;
using std::endl;
using std::string;


class
TestClass
:
public
QThread
{
	Q_OBJECT


	public :

		TestClass
		(
		 QWidget * parent = 0
		);

		virtual
		~TestClass
		(
		);


	signals :

		void
		signal_test
		(
		 int   value
		);


	public slots :
		
		void
		slot_test
		(
		 int   value
		);		


	private :

		int   value;
};


#endif

