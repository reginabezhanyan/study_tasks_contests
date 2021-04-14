#include <iostream>
#include <map> 
#include <string>

using namespace std;

int main() {
    unsigned N;
    cin >> N;
    
    map<string, string> data;
    string command, name, value;
     
    for(unsigned i = 0; i < N; i++) {
        cin >> command >> name; 
        if(command == "ADD") { 
            cin >> value;
            if(data.find(name) != data.end()) {
                cout << "ERROR" << endl;
            } else {
                data[name] = value;
            }
        } else if(command == "DELETE") { 
            map <string, string>::iterator it = data.find(name);
            if(it != data.end()) {
                data.erase(it);
            } else {
                cout << "ERROR" << endl;
            }
        } else if(command == "EDITPHONE") { 
            cin >> value;
            if(data.find(name) != data.end()) {
                data[name] = value;
            } else {
                cout << "ERROR" << endl;
            }
        } else if(command == "PRINT") { 
            if(data.find(name) != data.end()) {
                cout << name << " " << data[name] << endl;
            } else {
                cout << "ERROR" << endl;
            }
        } 
    }
}