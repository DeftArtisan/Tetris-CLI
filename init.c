#include "grd_t.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
extern void _init_grd(void** _grid) {
	   
	   for (size_t f = 0; f != 30; ++f)
			   for (size_t a = 0; a != 60; ++a)
              (*(_ptr_char16)(*((__ptr_char16)(_grid + a)) + f)) = '*';

		 printf("%c",  (*(_ptr_char16)(*((__ptr_char16)(_grid + 2)) + 4))); 
}
*/
#define _BUFF_REND(MVGR, MV, GR)	(_buffer_db(MV, GR), _hd_buff_crs(), buff_render(GR))
#define _RND_ printf("\e[?25l");	

//HANDLE _hout = GetStdHandle(STD_OUTPUT_HANDLE);
 


extern void _res_curs_pos(int _vr, int _vrr) {
	 HANDLE _hout = GetStdHandle(STD_OUTPUT_HANDLE);
	 COORD coord = {(SHORT)_vr, (SHORT)_vrr};
	 SetConsoleCursorPosition(_hout, coord);
}

extern void _hd_buff_crs() {
  HANDLE _hout = GetStdHandle(STD_OUTPUT_HANDLE); 
	CONSOLE_CURSOR_INFO _inf_cr;
	_inf_cr.dwSize = 100;
	_inf_cr.bVisible = FALSE;
	SetConsoleCursorInfo(_hout, &_inf_cr);
}


extern void buff_render(char16 _grid[12][100]){
	fflush(stdout);
	Sleep(10);
	_res_curs_pos(0, 0); 

	for (size_t g = 0; g < 12; ++g) {
		 for (size_t b = 0; b < 6; ++b) {
				//printf("\t");

					for (size_t a = 0; b >= 5 && a < 24; ++a) {	

							printf("%c", _grid[g][a]);	
						 //printf(" ");
						  if (a >= 23) {
								printf("\n");
							}
							//printf("%s", _reset__);
					}
				}
			}
}

extern void _buffer_db(char16 _grid_d[12][100], char16 _grid[12][100]) {
	  
	 for (size_t r_s = 0; r_s != 7; ++r_s) {
			   for (size_t s_s = 0; s_s != 23; ++ s_s){
				     _grid[r_s][s_s] = _grid_d[r_s][s_s] == _grid[r_s][s_s] ? _grid[r_s][s_s] : _grid_d[r_s][s_s];
				 }
		}
}


/*
_ptr_int32* _deco(char16 _temp_r[12][100], size_t _rnd) {


	//pseudo-randomize the template
	//_ptr_int32* _exm = (_ptr_int32*)_allocative_(sizeof(_ptr_int32) * strlen(_temp_r[0][1]));
	for (size_t g = 0; g < (size_t) (sizeof(_temp_r[_rnd]) / sizeof(_temp_r[_rnd][0])); ++g) {
		*(_exm + g) = (_ptr_int32)_allocative_(sizeof(int) * _c);
		for (size_t a = 0; a < _c; ++a) {
			*(*(_exm + g) + a) = 0;
		}
	}
	for (size_t g = 0; g < _r; ++g) {
		*(_exm + g) = (_ptr_int32)_allocative_(sizeof(int) * _c);
		for (size_t a = 0; a < _c; ++a) {
			*(*(_exm + g) + a) = 0;
		}
	}

	return &(*_exm);
}
*/
static void _repl_fl(int _temp_r[12][100], char16 _grid[12][100], size_t _rnd) {

  char16 _grid_d[12][100] = {};
  memcpy(_grid_d, _grid, 12 * 100);	

	static int32 _trv_s[1][2] = {{(int32)0, 0}}; //static continuously updated state prior to being fully visible 
	  //preemptively verifying for visibility since the object's partial coordinates are within the limits yet "invisible" until explicitly drawn to enable being sequentially visible

	_bool_ is_pillar = false;
	//register size_t _sec = 0;
	_bool_ _obs_rend = false;
	size_t _tmp_s = 0;
	 if(!(_grid_d[_temp_r[_rnd][0]][_temp_r[_rnd][1]] == '-')) {
			    //inverted visibility to adjust the state context 
			    for (size_t _a = 0; _a >= 0 || (size_t)_trv_s[0][0] <= _rnd; --_a){
						//since sequential verification for reaching terminating condition excludes last sequence due to latent incrementation, the check is inverted (e.g mental gymnastics for avoiding an explicit conditional)
				    //preventing row-indicator from being read since could be inferred 
						//ensuring only a block is read sequentially
						//first check depurposed by third
						//handles by by-block-visibility-approach(initial)
						 for(size_t _v = -2; _v < (size_t) (sizeof(_temp_r[_rnd]) / sizeof(_temp_r[_rnd][0])); _v += 2) {_temp_r[_rnd][_v] += 3;
							 //relocating after visibility-ensured due to newly occupying composites
							 if (_grid_d[_temp_r[_rnd][_v]][_temp_r[_rnd][_v + 1]] == '-') {_grid_d[_temp_r[_rnd][_v]][_temp_r[_rnd][_v + 1]] = ' '; _grid_d[_temp_r[_rnd][_v] += 3][_temp_r[_rnd][_v + 1]] = '-';}
						 } //preemptively updating the field for rendering
						 //synchronize previous locations of composites with moved coordinates	
						 //it adjusts itself to the current unrendered position																																																										
						   //TODO fix 2nd condition (doesn't promise block-by-block)
							 
						   for (size_t _f = _temp_r[_rnd][(size_t) (sizeof(_temp_r[_rnd]) / sizeof(_temp_r[_rnd][0])) - _trv_s[0][0]], _cl = _temp_r[_rnd][_f + 1]; _f >= 0 && !_obs_rend && _temp_r[_rnd][_f + 1] == abs(_temp_r[_rnd][_f + 2]);  _f -= 3) {
							   //preventing row-indicator from being read since could be inferred 
								 //instead of iterating by 2, by 4 ensures that the preceding it point is utilized in solely indicating the starting position and to not be treated as a point to be drawn from 
								 //could traverse via the commonality shared of the rows and invert the coordinates(i.e extract the indices sharing identical rows instead of relying on sequential)
								 //alternative print by the boundary of rows(i.e construct the whole object without it being strictly sequential)
								 /*
								 if(_cl + 2 ==_temp_r[_rnd][_f + 2];//storing the initial index determine 
								 
								 size_t init_stp;
								 init_stp = _temp_r[_rnd][_f + 2] != '-' 
                     */
							   register size_t _tmp_r = 0;
								 _tmp_s = !is_pillar ? _tmp_s + 3 : _tmp_s; //capturing pillar rendering tail
								 while(!(_grid_d[_temp_r[_rnd][_f]][_temp_r[_rnd][_f + 2]] == '-')) {

									
									 if(is_pillar && _grid_d[_temp_r[_rnd][_f]][_temp_r[_rnd][_f] + 3] == '-' && _tmp_r != _f && (_f == 0 || _temp_r[_rnd][_f - 2] != (int) _temp_r[_rnd][_f])) {_obs_rend = true; _trv_s[0][0] = _f; goto _trm_s;} //terminate after top drawn/ this assumes that the inversion of the composite-rendering is preserved

										//this assumes that the inversion of composite-rendering is preversed and since the condition overlaps in the sub-process beneath we ensure that we terminate only once the top is rendered(i.e -1) 
										 _grid_d[_temp_r[_rnd][_f]][_cl++] = '-'; //either reverse the coordinates to preserve the inverted pattern of rendering or reorganize(i.e deincrementing-composite pattern is incongruent with the sequential order)
										 
										 if (_f != 0 && !(_temp_r[_rnd][_f] == _temp_r[_rnd][_f - 2]) && !is_pillar) { //ensuring the pillars are not rendered prematurely
                       //either separate explicit node-connections into forward-connecting after node-rendering or concurrently render as in here
											   //support multi-block connectivity(i.e encase)
												//register size_t _pl_s = 0;
											  for (size_t _c = _temp_r[_rnd][_f + 1], _b = _temp_r[_rnd][_tmp_s]; (_b || _c) <= _temp_r[_rnd][_f + 1] - 3;){ 
													 _grid_d[_temp_r[_rnd][_f + 1]][_b--] = '-'; _grid_d[_temp_r[_rnd][_f + 1]][_c--] = '-';} //rendering the pillars pertinent to the block 						           
                           _tmp_r =_f + 1; //ensuring we correctly identify completion of pillars
												   is_pillar = true; //responsible for re-irendering the block-pillars  
												}
								
								   }
							
							 }

            _trm_s:
							 break;
					}

}

/*
    //handles sequential by-cell-visibility approach(initially through negative values)
     for (size_t _a = 0; _a < tr_sz && !(_grid_d[*(*(_rf + 0) + 0)][*(*(_rf + 0) + 1)] == '-') && _trv_s[0][0] != 0; --_a){
					for (size_t _f = 0;  !(*(*(_rf + _a) + _f) == '\0'); ++_f) {
              _grid_d[*(*(_rf + _a) + 0) += 1][*(*(_rf + _a) + _f)] = '-'; *(*(_rf + _a) + _f) += 1;
				  }
		 }
		 */

   _BUFF_REND(NULL, _grid_d, _grid);
}


extern _bool_ __attribute__((unused))_transform_blc(_ptr_int32* _blc_r, size_t _ln) {
    //handle transformation request whose transformation will collide with an inaccessible composite block of an object(i.e transformed coordinates align)(do not compute the request)
		//handle
	 
	return true;
}

extern size_t _ln_cl(size_t _templ_r[12][25], size_t _rnd) {for (size_t _cl = 0; true ; _cl++) {if(_templ_r[_rnd][_cl] == 1000) {return --_cl;}}}

int main(void) {

	//char16 _grid[_RW_][_CL_] = {};
	
	char16 _grid_d[12][100] = {
	  {'*','*', '*', '*', '*','*', '*', '*', '*','*', '*', '*','*','*', '*', '*', '*','*', '*', '*', '*','*', '*', '*'},
	  {'*','*', '*', '*', '*','*', '*', '*', '*','*', '*', '*','*','*', '*', '*', '*','*', '*', '*', '*','*', '*', '*'},
	  {'*','*', '*', '*', '*','*', '*', '*', '*','*', '*', '*','*','*', '*', '*', '*','*', '*', '*', '*','*', '*', '*'},
	  {'*','*', '*', '*', '*','*', '*', '*', '*','*', '*', '*','*','*', '*', '*', '*','*', '*', '*', '*','*', '*', '*'},
	  {'*','*', '*', '*', '*','*', '*', '*', '*','*', '*', '*','*','*', '*', '*', '*','*', '*', '*', '*','*', '*', '*'},
	  {'*','*', '*', '*', '*','*', '*', '*', '*','*', '*', '*','*','*', '*', '*', '*','*', '*', '*', '*','*', '*', '*'},
	  {'*','*', '*', '*', '*','*', '*', '*', '*','*', '*', '*','*','*', '*', '*', '*','*', '*', '*', '*','*', '*', '*'},
	  {'*','*', '*', '*', '*','*', '*', '*', '*','*', '*', '*','*','*', '*', '*', '*','*', '*', '*', '*','*', '*', '*'},
	  {'*','*', '*', '*', '*','*', '*', '*', '*','*', '*', '*','*','*', '*', '*', '*','*', '*', '*', '*','*', '*', '*'},
	  {'*','*', '*', '*', '*','*', '*', '*', '*','*', '*', '*','*','*', '*', '*', '*','*', '*', '*', '*','*', '*', '*'},
	  {'*','*', '*', '*', '*','*', '*', '*', '*','*', '*', '*','*','*', '*', '*', '*','*', '*', '*', '*','*', '*', '*'},
	  {'*','*', '*', '*', '*','*', '*', '*', '*','*', '*', '*','*','*', '*', '*', '*','*', '*', '*', '*','*', '*', '*'},
	};

	//easier approach begin with negative rows from an inverted visibility to be rendered organically, just sequentially block-visible
	int _templ_r[5][25] = { //TODO adhere to identical length properties(i.e either separate or artificially equalize)
		//{0, 5, 0, 8, 3, 5, 3, 8, 3, 11, 6, 5, 6, 8, 6, 11}
		//TODO replace with negative rows
		{-6, 5, -6, 8, -6, 11, -3, 5, -3, 8, -3, 11, 0, 5, 0, 8, 0, 11},//rectangle
		{-9, 5, -9, 8, -6, 5, -6, 8, -3, 5, -3, 8, -3, 11, 0, 5, 0, 8, 0, 11},//L
    {0, 5, 0, 8, 0, 5, 0, 8, 0, 11, 0, 5, 0, 8, 0, 11, 0, 8, 0, 11, 0, 8, 0, 11},
		{-3, 5, -3, 8, -3, 11, -3, 14, -3, 17, -3, 20, 0, 11, 0, 14}, //1 x 4 shape
		{0, 5, 0, 8, 0, 11, 0, 5, 0, 8, 0, 11, 0, 8, 11},
		
		//each cell is preceded by row since no consistent generic pattern could be extracted to differentiate different composites while row-associating with the composite(e.g rows could equate to cells with differing composite-size)	  
	};

	
	//invertedly visible blocks, as dynamically reserving spatial/partial requirements itself 
	//either submuse border coordinates during collision, or treat one row prior as such
	//_ptr_int32* _sect = _deco(_templ_r);
	system("CLS");
  //buff_render(_grid_d);
	
	while(!_get_async_key_state_win(VK_ESCAPE)){
	
		_pause_thread(500); 
		//_repl_fl(_templ_r, _grid_d, 0);
	  printf("%lld   ", _ln_cl(_templ_r, 0)); 
		//_BUFF_REND()
		//handle collision 
		//iteratively derive the collided block composite's coordinates, check for neighbouring col`lision.
    
		//since we're directly and randomly operating on the predefined blocks, a collision implies the reset of the blocks
		if(_get_async_key_state_win(VK_DOWN)) {

			 //un-bypassable and untransformable prior to each composite becoming visible in the field

		    char16 _gvd[12][100] = {};
	      memcpy(_gvd, _grid_d, 12 * 100);
	      //printf("%c", _gvd[4][5]);
	      // _gvd[4][6] = 'R';
	       
				 _BUFF_REND(NULL, _gvd, _grid_d);
				 //remove interception of tranformation by emplacing an instance of the outer layer
		 }
	  //buff_render(_grid_d);
	}



	 
	//_init_grd(_grid); 

	 exit(EXIT_SUCCESS);
}
