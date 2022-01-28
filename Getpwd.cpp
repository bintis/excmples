#include <Windows.h>

using namespace std;

char cdir[255];
GetCurrentDirectory(255,cdir);
cout << "Current Directory : " << cdir << endl;
