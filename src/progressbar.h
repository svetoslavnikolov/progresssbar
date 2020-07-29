#ifndef __PROGRESSBAR_H
#define __PROGRESSBAR_H

#include "version.h"
#include "progressbar_export.h"
#include <cstdint>

#define _EXPORT PROGRESSBAR_EXPORT


#ifdef __cplusplus
    extern "C" {
#endif // __cplusplus


_EXPORT void progress_caption_set(const char* caption);
_EXPORT void progress_text_set(int line, const char* caption);
_EXPORT void progress_value_set(int value);
_EXPORT int32_t progress_stop_clicked();
_EXPORT int32_t  progress_stop_reset();


#ifdef __cplusplus
    };
#endif // __cplusplus
#endif // !__PROGRESSBAR_H
