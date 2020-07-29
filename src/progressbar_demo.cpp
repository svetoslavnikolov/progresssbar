#include "progressbar.h"
#include <cstdlib>
#include <cstdio>

#include <chrono>
#include <thread>

#include <QtWidgets/qapplication.h>
#include <QtWidgets/qpushbutton.h>

using namespace std::chrono_literals;

int main(int /*argc*/, char** /*argv*/)
{
    progress_caption_set("Long Progress");
    
    progress_text_set(0, "Shall perform 5 updates per second.");
    progress_text_set(1, "For a total of 5 minutes.");

    for (int n = 0; n < 5 * 60 * 5; n++)
    {
        if (progress_stop_clicked()) {
            printf("Stop clicked. Exitting \n");
            break;
        }
        progress_value_set(n % 100);
        std::this_thread::sleep_for(20ms);
    }
    
    system("pause");
    return 0;
}
