#include <iostream>
#include "clsLoginScreen.h"

int main()
{
    while (true)
    {
        if (!clsLoginScreen::Show())
        {
            break;
        }

    }

}