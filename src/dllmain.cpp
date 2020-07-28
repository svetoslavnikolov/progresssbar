#ifdef _WIN32
#   include <windows.h>
#endif

#ifdef _WIN32
    BOOL WINAPI DllMain(HINSTANCE /* hinstDLL */,
        DWORD fdwReason,
        LPVOID /* lpReserved */)
    {
        switch (fdwReason)
        {
        case DLL_PROCESS_ATTACH:
            //initialize();
            break;

        case DLL_PROCESS_DETACH:
            //finalize();
            break;
        }
        return TRUE;
    }
#endif
