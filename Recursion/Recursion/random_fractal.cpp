#include "random_fractal.h"
using namespace std;

int main(){
    srand(time(NULL));
    
    fractal f;
    f.generate_fractal();

    system("PAUSE");
}
