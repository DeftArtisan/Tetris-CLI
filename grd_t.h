#include "definitive.h"

#define _CL_ 100
#define _RW_ 12

#define _BUFF_REND(MVGR, MV, GR)      (memcpy(MVGR, GR, _CL_ * _RW_), _buffer_db(MV, GR), _hd_buff_crs(), buff_render(GR))
#define _sective(_VARG_...) puts(#_VARG_) 
#define _secv(_AV_, _VB_, _AC_) (_AV_, _VB, ##_AC_) 

extern void _init_grd(void* _grid);

extern void _res_curs_pos(int _vr, int _vrr);

extern void _hd_buff_crs();

extern inline void buff_render(char16 _grid[12][100]);

extern inline void _buffer_db(char16 _grid_d[12][100], char16 _grid[12][100]);
