#include <iostream>
#include "convolution.hpp"
#include<fstream>

#define BLOCKSIZE 320
#define IMP_RSP_LENGTH 29

using namespace std;
extern double InputSignal_f32_1kHz_15kHz[320];
extern double  Impulse_response[29];
double OutputSignal[BLOCKSIZE + IMP_RSP_LENGTH];
int main()
{
    ofstream file1,file2;
    conv(
         InputSignal_f32_1kHz_15kHz,
         BLOCKSIZE,
         Impulse_response,
         IMP_RSP_LENGTH,
         OutputSignal);

    file1.open("Output_Signal.dat");
    file2.open("Input_Signal.dat");

    for(int i = 0; i<BLOCKSIZE+IMP_RSP_LENGTH;i++)
    {

        file1<<OutputSignal[i]<<endl;
        if(i<BLOCKSIZE)
        {
            file2<<InputSignal_f32_1kHz_15kHz[i]<<endl;
        }
    }

    file1.close();
    file2.close();


    cout << "Program Doneeeeee" << endl;
    return 0;
}
