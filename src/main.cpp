#include <string>
#include <iostream>

#include <boost/thread.hpp>
#include <boost/thread/scoped_thread.hpp>

#include <QtWidgets/QApplication>
#include <QtCore/QThread>

#include <TestClass.hpp>


using std::string;
using std::cout;
using std::endl;


extern
int
testFunctionA
(
);


extern
int
testFunctionB
(
);


extern
int
testFunctionC
(
);


int
main
(
 int     argc,
 char ** argv
)
{
	const
	string                   nameMethod      = "main : ";

	int                      returnCode      = -1;

	TestClass              * testObject_p    = nullptr;

	boost::thread_group    * threadGroup_p   = nullptr;

	boost::thread          * threadA_p       = nullptr,
	                       * threadB_p       = nullptr;

	boost::scoped_thread<> * threadScopedA_p = nullptr;

	QThread                * threadD_p       = nullptr;


	cout << nameMethod << "Enter" << endl;

	// Tell the user how many processing cores are available on the machine.

	cout << nameMethod << "Number of processing cores available = " << boost::thread::hardware_concurrency() << endl;

	testObject_p = new TestClass();

	threadGroup_p = new boost::thread_group();

	// Create three threads.
	//
	//   - The first will run in a Boost thread.
	//
	//   - The second will also run in a Boost thread.
	//
	//   - The third will run

	threadA_p = new boost::thread(testFunctionA);

	threadGroup_p->add_thread(threadA_p);

	// It appears as though threadB_p can't be used to create a Scoped thread.
	//
	// This means that the following won't work;
	//
	//   threadScopedA_p = new boost::scoped_thread<>(* threadB_p);
	//
	// whereas the following will;
	//
	//   threadScopedA_p = new boost::scoped_thread<>(boost::thread(testFunctionA));

	threadB_p = new boost::thread(testFunctionB);

	threadGroup_p->add_thread(threadB_p);

	// threadC_p = new boost::scoped_thread<>(boost::thread(& TestClass::starttestObject_p->start));

	threadGroup_p->join_all();

	cout << nameMethod << "All threads in the Thread group have finished executing." << endl;
	cout << nameMethod << "Number of threads in Thread group = " << threadGroup_p->size() << endl;

	cout << nameMethod << "Exit" << endl;

	returnCode = 0;


	return(returnCode);
}


int
testFunctionA
(
)
{
	const
	string   nameMethod = "testFunctionA : ";


	cout << nameMethod << "Enter" << endl;

	cout << nameMethod << "Exit" << endl;

	return(0);
}


int
testFunctionB
(
)
{
	const
	string   nameMethod = "testFunctionB : ";


	cout << nameMethod << "Enter" << endl;

	cout << nameMethod << "Exit" << endl;

	return(0);
}


int
testFunctionC
(
)
{
	const
	string   nameMethod = "testFunctionC : ";


	cout << nameMethod << "Enter" << endl;

	cout << nameMethod << "Exit" << endl;

	return(0);
}

