#include "input.h"

using namespace std;

string StrInput() {
    string inputStr;
    while (true) {
        getline(cin, inputStr);
        inputStr.erase(0, inputStr.find_first_not_of(" \n\r\t"));
        inputStr.erase(inputStr.find_last_not_of(" \n\r\t") + 1);
        if (inputStr.size() != 0)
            break;
        cout << "Строка не может быть пустой, попробуйте еще раз: ";
    }
    return inputStr;
}