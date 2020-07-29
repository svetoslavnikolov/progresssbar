#include "progressbar_export.h"
#include "progressbar.h"

#define _EXPORT PROGRESSBAR_EXPORT


#ifdef _WIN32
#   include <windows.h>
#endif


#if defined(_POSIX_VERSION) || defined(__APPLE__)
#  define DLL_CONSTRUCTOR __attribute__((constructor))
#  define DLL_DESTRUCTOR  __attribute__((destructor))
#else
#  define DLL_CONSTRUCTOR
#  define DLL_DESTRUCTOR
#endif  //_POSIX_VERSION

#include <cstdio>
#include <cstdint>

#include "progressbar_mgr.h"
#include <memory>


std::unique_ptr<ProgressBarMgr> progress;


void progress_caption_set(const char* caption)
 {
    progress->SetCaption(caption);
}

void progress_text_set(int line, const char* caption)
{
    progress->SetText(line, caption);
}

void progress_value_set(int value)
{
    progress->SetProgress(value);
}

int32_t progress_stop_clicked()
{
    return (int32_t) progress->StopClicked();
}

int32_t  progress_stop_reset()
{
    return (int32_t) progress->StopClickedClear();
}


void DLL_CONSTRUCTOR initialize()
{
    progress.reset(new ProgressBarMgr);
}


void DLL_CONSTRUCTOR finalize()
{
    progress.reset(nullptr);
}


#ifdef _WIN32
    BOOL WINAPI DllMain(HINSTANCE /* hinstDLL */,
        DWORD fdwReason,
        LPVOID /* lpReserved */)
    {
        switch (fdwReason)
        {
        case DLL_PROCESS_ATTACH:
            initialize();
            break;

        case DLL_PROCESS_DETACH:
            finalize();
            break;
        }
        return TRUE;
    }
#endif
