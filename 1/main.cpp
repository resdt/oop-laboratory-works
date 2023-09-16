#include <string>
#include <iostream>

#include "functions.cpp"

using namespace std;

int main() {
	string time;

	getline(cin, time);

	cout << hour_format(time) << endl;

	return 0;
}
