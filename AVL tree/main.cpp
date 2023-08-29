#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include "tree.h"
using namespace std;

int main()
{
	Dictionary<int, double> T1;
	Dictionary<int, double> T2;
	Dictionary<int, double> T3;
	Dictionary<int, double> T5;
	Dictionary<int, double> T6;
	Dictionary<int, string> T7;
	srand((time(NULL)));

	cout << "Adding elements to T1 (pure random) and T2 (random  4 * 4 + 12) " << endl;

	int i, j;

	for (i = 0; i < 15; i++)
	{
		j = rand() % 150;
		cout << j << " ";

		T1.insert(j, 1.00);
		T2.insert(j * 4 + 12, 2.00);
	}
	T1.insert(j, 3.00);		// overwriting Info test in T1

	cout << "\nPrinting T1 inorder using print():" << endl << endl;
	T1.print();
	cout << "Printing T1 inorder using op<<:" << endl << endl;
	cout << T1;
	cout << endl << "Printing T1 as graph:" << endl << endl;
	T1.draw();
	cout << endl << "--------------------------------------" << endl;


	cout << "Printing T2 inorder using print():" << endl << endl;
	T2.print();
	cout << "Printing T2 inorder using op<<:" << endl << endl;
	cout << T2;
	cout << endl << "Printing T2 as graph:" << endl << endl;
	T2.draw();
	cout << endl << "--------------------------------------" << endl;

	cout << "Testing assigment operator behaviour on T3 (=T1)" << endl << endl;
	T3 = T1;
	cout << T3;
	T3.draw();
	cout << endl << "--------------------------------------" << endl;


	cout << "Testing copy constructor behaviour on T4 (=T2)" << endl << endl;
	Dictionary<int, double> T4(T2);
	cout << T4;
	cout << endl << "--------------------------------------" << endl;

	cout << "Testing operator[] behaviour on T1" << endl << endl;
	if (T1[j]) cout << "Key " << j << " is present!" << endl;
	try
	{
		T1[j - 100000];
	}
	catch (element_not_found) { cerr << "Element not found!" << endl; }
	catch (critical_exception) { cerr << "Node not found!" << endl; }
	catch (...) { cerr << "Reached an uncontrolled control path!" << endl; }
	cout << endl << "--------------------------------------" << endl;

	cout << "Testing removing behaviour on T1" << endl << endl;
	T1.remove(j);
	cout << T1;
	cout << endl << "--------------------------------------" << endl;

	cout << "Testing removing behaviour on T5 (=empty)" << endl << endl;
	try { T5.remove(j); }
	catch (element_not_found) { cerr << "Element not found!" << endl; }
	catch (critical_exception) { cerr << "Node not found!" << endl; }
	catch (...) { cerr << "Reached an uncontrolled control path!" << endl; }
	cout << T5;
	cout << endl << "--------------------------------------" << endl;

	cout << "Testing removing behaviour on T6 (root)" << endl << endl;
	T6.insert(2, 6.00);
	T6.insert(3, 6.00);
	T6.insert(1, 6.00);
	T6.remove(2);
	T6.draw();
	cout << endl << "--------------------------------------" << endl;
	
	char c;
    string fileName[3];
    fileName[0] = "Academic Regulations at the Warsaw University of Technology (ANSI).txt";
    fileName[1] = "The bible.txt";
    fileName[2] = "On the Origin of Species, by Charles Darwin.txt";

    int k;
    do {
        cout << "[f:File; p:Print; 0:Exit]=";
        cin >> c;
        switch (c) { // [f:File; p:Print; 0:Exit]
            case 'f':{ // f:File
                cout << "[a:Academic; b:Bible; d:Darwin]=" ;
                do {
                    cin >> c;
                    switch (c){
                        case 'a': k=0; break;
                        case 'b': k=1; break;
                        case 'd': k=2; break;
                        default: cin >> c; break;
                    } // switch
                } while (c!='a' && c!='b' && c!='d');
                cout << "fileName[" << k << "]=" <<  fileName[k]  << endl;
                break;
            }
            case 'p':{ // p:Print
                cout << "RetrieveWords (fileName[" << fileName[k] << "]()=" << endl;
                retrieveWords(T7, fileName[k]);
				T7.print();
                break;
            }
            case '0':{ // exit
                break;
            }
            default:{
                cin >> c;
                break;
            }
        } // switch
    } while (c != '0');
    cout << "Press 'Return' key to exit \n";
    do {
        cin.get (c);
    } while (c!=10);
    return 0;
}