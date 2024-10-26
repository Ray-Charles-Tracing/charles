#include <iostream>

// Include our class definition - we can read it thanks to `target_include_directories`
#include <Color.hpp>

using namespace std;

int main()
{    
    Color red(1, 0, 0);
    Color green(0, 1, 0);
    Color black;

    // We can chain our color instances using << thanks to our operator !
    cout << "Red : " << red << std::endl;
    cout << "Green : " << green << std::endl;
    cout << "Black : " << black << std::endl;

    // We can perform an addition + operation thanks to our operator !
    Color yellow = red + green;

    cout << "Yellow : " << yellow << std::endl;    
}
