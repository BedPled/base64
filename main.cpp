#include <iostream>
#include "lib.h"
#include <string>

using namespace std;

int main() {
cout << endl << asciiToBase64("Hello My Dear Friend!") << endl;
cout << asciiToBase64("Hello My Dear Friend") << endl;
cout << asciiToBase64("Hello My Dear") << endl;

cout << endl << base64ToAscii("SGVsbG8gTXkgRGVhciBGcmllbmQh") << endl;
cout << base64ToAscii("SGVsbG8gTXkgRGVhciBGcmllbmQ") << endl;
}