#include <iostream>
#include "Sequence.h"
using namespace std;


int main()
{
	// Testing splitting by key
	/*Expected output:
	2	L1
	3	L1	
	7	L1
	8	L1
	---
	4	L1
	5	L1
	6	L1
	9	L1*/
	cout << "-----------SPLITTING BY KEY-----------" << endl;
	Sequence<int, string> l1;
	Sequence<int, string> li;
	Sequence<int, string> l2;
	l1.add_back(1, "L1");
	l1.add_back(2, "L1");
	l1.add_back(3, "L1");
	l1.add_back(4, "L1");
	l1.add_back(5, "L1");
	l1.add_back(6, "L1");
	l1.add_back(7, "L1");
	l1.add_back(8, "L1");
	l1.add_back(9, "L1");
	l1.print();
	cout << "---" << endl;
	split_by_key<int, string>(l1, 2, 2, 3, 3, l2, li);
	l2.print();
	cout << "---" << endl;
	li.print();

	//Testing splitting by position
	/* Expected output:
	3	P1
	4	P1
	7	P1
	8	P1
	---
	5	P1
	6	P1
	9	P1
	*/
	cout << "---------SPLITTING BY POSITION----------" << endl;
	Sequence<int, string> p1;
	Sequence<int, string> pi;
	Sequence<int, string> p2;
	p1.add_back(1, "P1");
	p1.add_back(2, "P1");
	p1.add_back(3, "P1");
	p1.add_back(4, "P1");
	p1.add_back(5, "P1");
	p1.add_back(6, "P1");
	p1.add_back(7, "P1");
	p1.add_back(8, "P1");
	p1.add_back(9, "P1");
	split_by_pos<int, string>(p1, 3, 2, 2, 3, p2, pi);
	p2.print();
	cout << "---" << endl;
	pi.print();

	// Testing insering functions
	/* Expected output: 
	3	K1
	2	K1
	1	K1
	*/
	cout << "-----------------Sequence 1--------------------" << endl;
	Sequence<int, string> S1;
	S1.add_back(1, "K1");
	S1.add_front(3, "K1");
	S1.add_after(2, "K1", 3);
	S1.print();

	// Testing removing functions
	/* Expected output:
	2	K2
	4	K2
	5	K2
	*/
	cout << "-----------------Sequence 2--------------------" << endl;
	Sequence<int, string> S2;
	S2.add_back(1, "K2");
	S2.add_back(2, "K2");
	S2.add_back(3, "K2");
	S2.add_back(3, "K2");
	S2.add_back(4, "K2");
	S2.add_back(5, "K2");
	S2.add_back(5, "K2");
	S2.add_back(5, "K2");
	S2.add_back(6, "K2");
	S2.remove_first();
	S2.remove_last();
	S2.remove_last();
	S2.remove_all_with_key(3);
	S2.remove_once_with_key(5);
	S2.print();


	// Testing copy constructor and assigment operator
	/* Expected output:
	1	K3
	2	K3
	3	K3
	1	K3
	2	K3
	3	K3
	1	K3
	2	K3
	3	K3
	*/
	cout << "-----------------Sequence 3, 4, 5-------------" << endl;
	Sequence<int, string> S3, S4;
	S3.add_back(1, "K3");
	S3.add_back(2, "K3");
	S3.add_back(3, "K3");
	S4 = S3;
	S3.print();
	S4.print();
	Sequence<int, string> S5(S3);
	S5.print();


	// Testing counting functions
	/* Expected output:
	4
	2
	0
	*/
	cout << "-----------------Sequence 6--------------------" << endl;
	Sequence<int, string> S6;
	S6.add_back(1, "K6");
	S6.add_back(2, "K6");
	S6.add_back(3, "K6");
	S6.add_back(3, "K6");
	cout << S6.count() << endl;
	cout << S6.count(3) << endl;
	cout << S6.count(4) << endl;

	// Testing operators
	/* Expected output:
	99	K8
	1	K8
	2	K8
	3	K8
	4	K8
	-----
	1	K8
	2	K8
	3	K8
	4	K8
	1	K7
	2	K7
	3	K7
	4	K7
	*/
	cout << "-----------------Sequence 7, 8, 9, 10------------" << endl;
	Sequence<int, string> S7, S8, S9, S10;
	S7.add_back(1, "K7");
	S7.add_back(2, "K7");
	S7.add_back(3, "K7");
	S7.add_back(4, "K7");
	S8.add_back(1, "K8");
	S8.add_back(2, "K8");
	S8.add_back(3, "K8");
	S8.add_back(4, "K8");
	S9.add_back(99, "K9");
	S9 += S8;
	S9.print();
	S10 = (S8 + S7);
	cout << "-----" << endl;
	S10.print();

	// Testing checking functions
	/* Expected output:
	0
	1
	0
	1
	0
	*/
	cout << "-----------------Sequence 11-------------------" << endl;
	Sequence<int, string> S11, S12;
	cout << S6.is_empty() << endl;
	cout << S11.is_empty() << endl;
	S11.add_back(1, "K14");
	S11.add_back(2, "K14");
	S11.add_back(3, "K14");
	cout << S11.is_empty() << endl;
	cout << S11.is_key(1) << endl;
	cout << S11.is_key(4) << endl;
	cout << "-----" << endl;
	S12.print();
	cin.get();
	return 0;
}
