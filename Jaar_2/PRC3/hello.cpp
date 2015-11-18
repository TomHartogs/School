#include <iostream>
using namespace std;

class Hello
{
	public:
	Hello()
	{
		cout << "Hello class is constructed!\n" ;
	}
	
	void Print()
	{
		cout << "Hello World!\n";
	}
};

int main()
{
	cout << "test" << endl;
    return 0;
}
