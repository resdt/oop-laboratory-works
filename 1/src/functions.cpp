#include <string>

using namespace std;

string hour_format(string time) {
	if (time[time.size() - 2] == 'a') {
		if (time[1] == ':') {
		    return '0' + time.substr(0, 1) + time.substr(2, 2);
		} else {
		    return time.substr(0, 2) + time.substr(3, 2);
		}
	} else if (time[1] == ':') {
	    return to_string(stoi(time.substr(0, 1)) + 12) + time.substr(2, 2);
	} else if (time.substr(0, 2) != "12") {
		return to_string(stoi(time.substr(0, 2)) + 12) + time.substr(3, 2);
	} else {
		return "00" + time.substr(3, 2);
	}
}
