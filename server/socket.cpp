#include <experimental/net>
#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>

using namespace std;

void write_test(ofstream &_out)
{
    _out << "Thread1 Write data.\n";
    while (int n = 10)
    {
        _out << "\tData: " << n;
    }
    _out << "Finished\n";

    cout << "Thread1 progress:############" << endl;
}

void write_test2(ofstream &_out)
{
    _out << "2222222222222222222222222.\n";
    while (true)
    {
        _out << "Data_2.";
    }
}

int main(int argv, char **args) {
    ofstream test{"test.txt",ios_base::trunc};
    if(!test.good())
        cout<<"Error occurred when open file."<<endl;
     


}
