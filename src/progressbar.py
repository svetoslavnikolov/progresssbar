# -*- coding: utf-8 -*-

import ctypes as ct

import sys
import os
import os.path as osp


__all__ = [ 
    'progress_new',
    'progress_show',
    'progress_close',
    'progress_caption_set',
    'progress_text_set',
    'progress_value_set',
    'progress_stop_clicked',
    'progress_stop_reset',
]


# -----------------------------------------------------------------------------
# --- Access to the DLL
# -----------------------------------------------------------------------------

def _dir_mine():
    import inspect
    return osp.dirname(inspect.getabsfile(_dir_mine))


class _ProgressBar(object):
    '''Class to access the exported DLL functions.
    '''
    def __init__(self):
        '''Constructor loads DLL at object creation.'''
        if os.name == 'nt':
            dllname = 'progressbar.dll'
        else:
            raise NotImplementedError('Support only for Windows is implemented')
        fullpath = osp.join(_dir_mine(), 'dlls', dllname)
        self._dll = ct.cdll.LoadLibrary(fullpath)

        self._fill_function_prototypes()
    

    def _fill_function_prototypes(self):
        '''Set argument and return types for the function prototypes'''
        names = [
            'progress_new',
            'progress_show',
            'progress_close',
            'progress_caption_set',
            'progress_text_set',
            'progress_value_set',
            'progress_stop_clicked',
            'progress_stop_reset',
        ]

        try:
            count = 0
            self.progress_new = self._dll.progress_new
            self.progress_new.restype = None
            self.progress_new.argtypes = [ct.c_char_p, ct.c_char_p]

            count += 1
            self.progress_show = self._dll.progress_show
            self.progress_show.restype = None
            self.progress_show.argtypes=[]
            
            count += 1
            self.progress_close = self._dll.progress_close
            self.progress_close.restype = None
            self.progress_close.argtypes =[]
            
            count += 1
            self.progress_caption_set = self._dll.progress_caption_set
            self.progress_caption_set.restype = None
            self.progress_caption_set.argtypes = [ct.c_char_p]

            count += 1
            self.progress_text_set = self._dll.progress_text_set
            self.progress_text_set.restype = None
            self.progress_text_set.argtypes = [ct.c_int32, ct.c_char_p]

            count += 1
            self.progress_value_set = self._dll.progress_value_set
            self.progress_value_set.restype = None
            self.progress_value_set.argtypes = [ct.c_int]

            count += 1
            self.progress_stop_clicked = self._dll.progress_stop_clicked
            self.progress_stop_clicked.restype = ct.c_int32
            self.progress_stop_clicked.argtypes = []
            
            count += 1
            self.progress_stop_reset = self._dll.progress_stop_reset
            self.progress_stop_reset.restype = ct.c_int32
            self.progress_stop_reset.argtypes = []

        except:
            print('Could not initialize {0}'.format(names[count]))
            raise RuntimeError('DLL interface failed')

def _str_to_cstring(text):
    assert type(text).__name__ == 'str'
    size = len(text)
    out = (ct.c_char * (size + 1))()
    out[:size] = [ct.c_char(ord(k)) for k in text]
    return out

# ------------------------------------------------------------------------------
# --- Static variable giving access to the DLL functions
# ------------------------------------------------------------------------------
_pbar = _ProgressBar()


# ------------------------------------------------------------------------------
# --- Module interface
# ------------------------------------------------------------------------------

def progress_new(caption='Progress bar', line='Press STOP to stop progress'):
    '''New progress bar, or reset existing.
    Progress is set to 0.

    Parameters
    ----------
    caption : string
        Window caption
    line : string
        Text shown on top line
    '''

    ct_caption = _str_to_cstring(caption)
    ct_line = _str_to_cstring(line)

    _pbar.progress_new(ct_caption, ct_line)


def progress_show():
    '''Show hidden progress bar. Caption, text, progress - preserved'''
    _pbar.progress_show()

def progress_close():
    '''Hide progress bar.'''
    _pbar.progress_close()


def progress_caption_set(caption):
    '''Set the caption of the progress bar'''
    _pbar.progress_caption_set(_str_to_cstring(caption))


def progress_text_set(text='Text', line=0):
    '''Set text of progress bar. Up to 3 lines.
    Parameters
    ----------
    text : string or list of strings.
        If list, then 'line' is neglected and the lines are sequentially set on the dialog.
    line : scalar, integer
        Line (0 -- 2) to set the text to.
    '''

    if type(text).__name__ == 'list':
        textList = text
        firstLine = 0
    else:
        textList = [text]
        firstLine = line
    
    for iline in range(len(textList)):
        lineText = textList[iline]
        _pbar.progress_text_set(iline, _str_to_cstring(lineText))


def progress_value_set(progress):
    '''Set the progress (0 .. 100).'''
    _pbar.progress_value_set(int(progress))

def progress_stop_clicked():
    '''Check if [STOP] was clicked'''
    return _pbar.progress_stop_clicked()

def progress_stop_reset():
    '''Reset flag that [STOP] was clicked'''
    return _pbar.progress_stop_reset()


# -----------------------------------------------------------------------------
# --- "Main" - run when file is run as script
# -----------------------------------------------------------------------------

if __name__ == '__main__':
    import time
    progress_new('Test progress bar', '')
    progress_text_set(['Will run for 5 minutes', 'Press [STOP] to exit loop'])

    for minute in range(5):
        for sec in range(60):
            progress_text_set('Minute {0}, Second {1}'.format(minute, sec), 2)
            progress_value_set( sec * 100 / 60 )
            time.sleep(1)
            if progress_stop_clicked():
                break
        if progress_stop_clicked():
            break
    progress_stop_reset()
    progress_close()
