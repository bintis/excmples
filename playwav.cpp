#include <windows.h>
#include <iostream>
#pragma comment(lib, "winmm.lib")

int main(int argc, char* argv[])
{
std::cout<<"Sound playing... enjoy....!!!";
PlaySound("C:\\temp\\sound_test.wav", NULL, SND_FILENAME); //SND_FILENAME or SND_LOOP
return 0;
}
