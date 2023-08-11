#include "grd_t.h"
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <math.h>
#include <assert.h> 
#include <pthread.h>


#ifdef __unix__
#include <unistd.h>
#elif defined _WIN32
#include <windows.h> 
#define sleep(x) Sleep(1000 x (x))
#endif


/*
extern void _init_grd(void** _grid) {
	   
	   for (size_t f = 0; f != 30; ++f)
			   for (size_t a = 0; a != 60; ++a)
              (*(_ptr_char16)(*((__ptr_char16)(_grid + a)) + f)) = '*';

		 printf("%c",  (*(_ptr_char16)(*((__ptr_char16)(_grid + 2)) + 4))); 
}
*/
#define _BUFF_REND(MVGR, MV, GR)	(_buffer_db(MV, GR), _hd_buff_crs(), buff_render(GR))
#define _BUFF_REND_V _BUFF_REND(MVGR, MV, GR)
#define _RND_ printf("\e[?25l")	
#define _RVD_ printf("\033[0,0H")
#define _VD_RND ( _RVD_, fflush(stdout), _RND_)
#define V(_CW, _A) _CW = _A != 0 ? _CW - 3 : _CW  

//HANDLE _hout = GetStdHandle(STD_OUTPUT_HANDLE);
 
extern size_t _ln_cl(int _templ_r[5][25], size_t _rnd);

extern void _res_curs_pos(int _vr, int _vrr) {
}

extern void _hd_buff_crs() {
   /*
   HANDLE cout = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO _inf;
   _inf.dwSize = 100;
   _inf.bVisible = FALSE;
   SetConsoleCursorInfo(cout, &_inf);
  */
}


extern inline void buff_render(char16 _grid[12][100]){
 _VD_RND;
  for (size_t g = 0; g < 12; ++g) {
		 for (size_t b = 0; b < 6; ++b) {
				//printf("\t");
					for (size_t a = 0; b >= 5 && a < 24; ++a) {	
						 //printf(" ");
						  if(_grid[g][a] == '-') {printf("%s", _actorPL);	fputc(_grid[g][a], stdout);printf("%s", _reset_); continue;}
							fputc(_grid[g][a], stdout);
             //printf("%c", _grid[g][a]);
							if (a >= 23) {
								printf("\n");
							}
							//printf("%s", _reset__);
					}
				}
			}

}

extern inline void _buffer_db(char16 _grid_d[12][100], char16 _grid[12][100]) {
   
	 for (size_t r_s = 0; r_s != 7; ++r_s) {
			   for (size_t s_s = 0; s_s != 23; ++ s_s){
				    _grid[r_s][s_s] = _grid_d[r_s][s_s] != _grid[r_s][s_s] ? _grid_d[r_s][s_s] : _grid[r_s][s_s];
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
static _bool_ _repl_fl(int _temp_r[5][25], char16 _grid[12][100], size_t _rnd, int* _coerc, bool* _obs_rend) {

  char16 _grid_d[12][100] = {};
  memcpy(_grid_d, _grid, 12 * 100);	
	static int32 _trv_s[1][2] = {{(int32)0, 0}}; //static continuously updated state prior to being fully visible 
	  //preemptively verifying for visibility since the object's partial coordinates are within the limits yet "invisible" until explicitly drawn to enable being sequentially visible
  static int _cn = 0;
	_bool_ is_pillar = false;
	//register size_t _sec = 0;
	//static _bool_ _obs_rend = false;

	int _tmp_s = 0;
	//if(_obs_rend) {exit(EXIT_FAILURE);}
  //printf("%d", _temp_r[_rnd][0]))
	 if(_temp_r[_rnd][0] < 0 && _temp_r[_rnd][2] < 0) {
			    //inverted visibility to adjust the state context 
      	   for (;!is_pillar;){

						//since sequential verification for reaching terminating condition excludes last sequence due to latent incrementation, the check is inverted (e.g mental gymnastics for avoiding an explicit conditional)
				    //preventing row-indicator from being read since could be inferred 
						//ensuring only a block is read sequentially
						//first check depurposed by third
						//handles by by-block-visibility-approach(initial)
 
            //assert(*_obs_rend);
            _bool_ v = false;
            for(int _v = _ln_cl(_temp_r, _rnd) + 1, _ct = _temp_r[_rnd][(_v - 2) + 1] + 1; _v >= 0;) {_v -= 2; if (_v >= 0) {_temp_r[_rnd][_v] += 3;}//printf("%d %d ", _temp_r[_rnd][_v],(int) _v);}
							 //relocating after visibility-ensured due to newly occupying composites
							 //first precondition presupposed by second(superfluous)
               if(v && *_obs_rend) {_BUFF_REND(NULL, _grid, _grid_d); exit(EXIT_FAILURE);}
               //if(*_obs_rend) {printf("%d ", _grid[_temp_r[_rnd][_v]][_temp_r[_rndi][_v] - 3]);}
               //if(*_coerc != 0 && _v == _ln_cl(_temp_r, _rnd) + 1 - 8) {fputc(_grid[_temp_r[_rnd][_v + 2]][_temp_r[_rnd][(_v + 2) + 1]], stdout); _BUFF_REND(NULL, _grid, _grid_d); exit(EXIT_FAILURE);}
               //synchronize stored localr
               if(_v >= 0 && _temp_r[_rnd][_v] - 3 >= 0 && _grid[_temp_r[_rnd][_v] - 3][_temp_r[_rnd][_v + 1]] == '-') {
                    register int _fl = _v;
                      //printf("%d", _temp_r[_rnd][_v]); exit(EXIT_FAILURE);
                      //sub-process each sub-section
                     while(_v >= 0 && _temp_r[_rnd][_fl] == _temp_r[_rnd][_v]) {
                          _temp_r[_rnd][_v -= 2] += 3;
                           while(_temp_r[_rnd][_v + 2] == _temp_r[_rnd][_fl] && _ct - 1 != _temp_r[_rnd][_v + 1]) {  
                                  _grid[_temp_r[_rnd][_v + 2]][--_ct] = '-'; 
                                   if(_temp_r[_rnd][_v] != _temp_r[_rnd][_fl] && _temp_r[_rnd][_v - 2] >= 0) {
                                     _ct = _temp_r[_rnd][_v + 2];
                                    // printf("%d%d", _temp_r[_rnd][_v], _temp_r[_rnd][_fl]);
                                     //exit(EXIT_FAILURE);
                                     //localize upper boundary, no prior implies that the upper inherits 
                                     //implicitly captures excessive boundary and reassigns to the previous minimal
                                     //if the upper boundary is smaller to the subtracted column distance, the location is approximate for a search, otherwise it's safely bounded
                                       while(_ct != _temp_r[_rnd][_v]) {register int _x = 0, _y = 0, _z = 0; _grid[--_ct][_y = _temp_r[_rnd][_temp_r[_rnd][_z += _v - (((_temp_r[_rnd][_fl + 1] - _temp_r[_rnd][(_v + 3)] / 4) + 1) * 2) + 1]] < 
                                             _temp_r[_rnd][_v + 3] && _temp_r[_rnd][_z - 1] == _temp_r[_rnd][_v] - 3 ? _temp_r[_rnd][_z = (abs((_temp_r[_rnd][_v + 1] -_temp_r[_rnd][_z]) / 4 + 1) * 2) + 2] : _temp_r[_rnd][_v + 3]] = '-'; 
                                            
                                             while(_temp_r[_rnd][(_z += (abs((_temp_r[_rnd][_v + 1] -_temp_r[_rnd][_z]) / 4 + 1) * 2)) -= 1] != _temp_r[_rnd][_v]) {}
                                             _grid[_ct][_x = _temp_r[_rnd][_fl + 1] >= _temp_r[_rnd][_v + 1] ? _temp_r[_rnd][_v + 1] : _temp_r[_rnd][_fl + 1]] = '-';} 
                                       break;
                                    }
                                     
                                   /*printf("%d", _temp_r[_rnd][_ct]); exit(EXIT_FAILURE); */ }_ct = _temp_r[_rnd][v + 1] + 1;} _temp_r[_rnd][_v] -= 3; _v += 2; v = true;/*V(_temp_r[_rnd][_v], _v);  _v+=2;*/ _ct--;}}//synchronize previous locations of composites with moved coordinates	
						 //it adjusts itself to the current unrendered position																												

						 //TODO fix 2nd condition (doesn't promise block-by-block
             for (int _f = (*_coerc != 0) ? ((((_ln_cl(_temp_r, _rnd)) + 1) - (( _ln_cl(_temp_r, _rnd) + 1) - *_coerc))) + 4 : ((_ln_cl(_temp_r, _rnd)) + 1), _cl = *_obs_rend ? _temp_r[_rnd][_f] : _temp_r[_rnd][(_f -= 2) + 1];  _f >= 0;) {  
                //printf("%d%d  ", _temp_r[_rnd][_cl], _temp_r[_rnd][((_ln_cl(_temp_r, _rnd) + 1) - 1)]);	
								if(((_cl != _temp_r[_rnd][(_ln_cl(_temp_r, _rnd) + 1) - 1]) && !(*_coerc != 0)) || *_obs_rend) {_f -= 2; _cl = _temp_r[_rnd][_f + 1]; /*printf("%d!%d:", _temp_r[_rnd][_cl], _f);*/}
               
                if(_temp_r[_rnd][_f - 2] != _temp_r[_rnd][_f]) {continue;} //prevent pillar overflow due to inverted rendering 
								//preventing row-indicator from being read since could be inferred
								 //instead of iterating by 2, by 4 ensures that the preceding it point is utilized in solely indicating the starting position and to not be treated as a point to be drawn from 
								 //could traverse via the commonality shared of the rows and invert the coordinates(i.e extract the indices sharing identical rows instead of relying on sequential)
								 //alternative print by the boundary of rows(i.e construct the whole object without it being strictly sequential)
								 /*
								 if(_cl + 2 ==_temp_r[_rnd][_f + 2];//storing the initial index determine 
								if(*_coerc != 0) {printf("%c", _grid_d[_rnd][_temp_r[_rnd][_f - 5] + 1]); exit(EXIT_FAILURE);} 
								 size_t init_stp;
								 init_stp = _temp_r[_rnd][_f + 2] != '-' 
                     */ 
								//printf("%d", _temp_r[_rnd][_cl - 2]);
								 //_tmp_s = !is_pillar ? _tmp_s + 2 : _tmp_s; //capturing pillar rendering tail
                //_tmp_s = (_temp_r[_rnd][_f] != _temp_r[_rnd][_f + 2]) && is_pillar ? 0 : _tmp_s + 2;
								// printf("%d:%d", _cl, _temp_r[_rnd][_f]);
                
                if(*_coerc != 0) {/*printf("%c", _grid_d[_temp_r[_rnd][_f]][_temp_r[_rnd][_f] - 3]); */ _BUFF_REND(NULL, _grid_d, _grid); exit(EXIT_FAILURE);} 
                _tmp_s += 2; 
                 //reverting the cells for reusability(i,e to meet the precondition since it's composite-based rendering)  
                 //if (*_coerc != 0) { printf("%d", _temp_r[_rnd][(((_ln_cl(_temp_r, _rnd)) + 1) - (_ln_cl(_temp_r, _rnd) + 1) - *_coerc) + 1]); exit(EXIT_FAILURE);}
                 for (size_t _x = _temp_r[_rnd][(((_ln_cl(_temp_r, _rnd)) + 1) - (_ln_cl(_temp_r, _rnd) + 1) - *_coerc) + 1]; (_tmp_s - 2 <= 0 && !is_pillar && *_obs_rend) && _temp_r[_rnd][(_x-=2) - 1] == _temp_r[_rnd][_f];) {_grid[_temp_r[_rnd][_f]][_x] = '*'; }
                 if(is_pillar && *_coerc != 0) {/* printf("\n%d%d%c",_temp_r[_rnd][_f], _temp_r[_rnd][_f + 2],_grid_d[_temp_r[_rnd][_f]][_temp_r[_rnd][_f - 1] + 1]);*/ _BUFF_REND(NULL, _grid_d, _grid); exit(EXIT_FAILURE);}
                  while(!(_grid_d[_temp_r[_rnd][_f]][_temp_r[_rnd][_f - 1]] == '-') || (is_pillar && !(_grid_d[_temp_r[_rnd][_f]][_temp_r[_rnd][_f - 1] + 1] == '-'))) {
									 //verification for pillar-rendering terminates immediatelyi
									 //traversion by 4 insecure(fixed, captured by precondition for overflowing)
									 //the backwards check is presupposed by the by 4 traversion in differentiating itself correctly(i.e ensuring we do not prematurely cease)
									//if(_cl == 6 && _temp_r[_rnd][_f] == 0) {exit(EXIT_FAILURE);}
									_grid_d[_temp_r[_rnd][_f]][_cl--] = '-';	 
                  //if(_cl != *_coerc + 1 && *_obs_rend) {exit(EXIT_FAILURE);}
                  //_BUFF_REND(NULL, _grid_d, _grid);	
									//if(_cl == 8 && _f == 0) {exit(EXIT_FAILURE);}
									//printf("%c", _grid_d[_temp_r[_rnd][_f]][_cl - 1]); 
								  //if(_tmp_s == 10) {exit(EXIT_FAILURE);}
                  //if(is_pillar && *_coerc != 0) {printf("   %d", _temp_r[_rnd][_f + 1]);} 
                  
                  if(is_pillar && _grid_d[_temp_r[_rnd][_f]][_temp_r[_rnd][_f - 1] + 1] == '-' && (_f - 4 == 0 || (int) _temp_r[_rnd][_f - 4] != (int) _temp_r[_rnd][_f])) {*_obs_rend = true; if(!*_coerc == 0) {assert(!*_coerc != 0);} 
										                *_coerc = (((_ln_cl(_temp_r, _rnd) + 1)) - ((_ln_cl(_temp_r, _rnd) + 1) - _f)) + (_tmp_s - 2); _BUFF_REND(NULL, _grid_d, _grid); return true;} //terminate after top drawn/ this assumes that the inversion of the composite-rendering is preserved
                     
										//this assumes that the inversion of composite-rendering is preversed and since the condition overlaps in the sub-process beneath we ensure that we terminate only once the top is rendered(i.e -1) 
										 //either reverse the coordinates to preserve the inverted pattern of rendering or reorganize(i.e deincrementing-composite pattern is incongruent with the sequential order)                 	
											/*
									  if ((int) _cl - 1 == _temp_r[_rnd][_f - 1]) {

											int c = _cl;
											 printf("%c %d %d", _grid_d[_temp_r[_rnd][_f]][c + 1], (int) _temp_r[_rnd][_f - 1], (int) _cl - 1);
											 system("PAUSE");
											}
											*/
										//printf("%d %d",!(_temp_r[_rnd][_f] == _temp_r[_rnd][_f - 2]), _grid_d[_temp_r[_rnd][_f]][_temp_r[_rnd][_f - 1]] == '-'); 
										 //printf("%d",_grid_d[_temp_r[_rnd][_f]][_cl--]);
										 
											//printf("%d", is_pillar);
										  if (_f != 0 && !(_temp_r[_rnd][_f] == _temp_r[_rnd][_f - 4]) && _grid_d[_temp_r[_rnd][_f]][_temp_r[_rnd][_f - 1]] == '-' && !is_pillar) { //ensuring the pillars are not rendered prematurely
												//either separate explicit node-connections into forward-connecting after node-rendering or concurrently render as in here
											   //support multi-block connectivity(i.e encase)
												//register size_t _pl_s = 0;
                        if(*_coerc != 0) {printf("%c", _grid_d[_temp_r[_rnd][_f] - 3][_temp_r[_rnd][_f - 7] + 1]); exit(EXIT_FAILURE);} 
                        int _ab = 0, _ac = 0, _fin = 0, _finr = 0;
												_bool_ is_tmp = false;
										    //assumes that continuity of upper boundary is non-volatile in a pattern/modify to capture upper boundary inclusivity via encasing and utilizing the encased(smaller boundary) coordinates 	
                        //redo to capture depth 
                        for (int _b = _f - 3, _a = (((_f) + _tmp_s) - 1); _b >= 0 && !(_temp_r[_rnd][_b-=2] != _temp_r[_rnd][_a-=2]) && _temp_r[_rnd][(_b + 2) - 1] == _temp_r[_rnd][_f] - 3;) {_ab = _b + 2; _ac = _a + 2; _fin = _ab > _ac ? _ac : _ab;}
                        
                        if(_temp_r[_rnd][((_f - 3) - _ab) - 1] != _temp_r[_rnd][_f] - 3) {is_tmp = true;}
                        //left encased pillar
                        //for (int _ax = _f - 1, _av = abs((_f - 3) - _ab); !is_tmp && _temp_r[_rnd][_ax += 2] == _temp_r[_rnd][_av -= 2];) {_finr = _ax - 2 > _av - 2 ? _av - 2 : _ax - 2; } 
                        //matched the upper boundary of pillers while ensuring its compositeness(i.e since we generalize in repeating the step after each rendered compsite, the lower wider boundary doesn't indicate a matching upper since it's hierarchically downwardly determined while we're rendering invertedly
											//not within the range of the upper boundary indicates that the previous limitation should be utilized, if within then it's readjusted 	
                        
                         for (int _c = _temp_r[_rnd][_f]; !((_c) < ((int) _temp_r[_rnd][_f] - 3));){  
                           //printf("%d %d" , _temp_r[_rnd][((_f + _tmp_s) - _ac)])
                           //@arg _fin -> determining the encased pillar, the initial encased is always the rendered
                            int _xv = !*_obs_rend ? (_f + _tmp_s) - 1 : ((_f + _tmp_s - 2) + 1);
                            _grid_d[_c--][_temp_r[_rnd][_f - 1]] = '-'; _grid_d[_c + 1][_temp_r[_rnd][!is_tmp ? _temp_r[_rnd][_fin] : _xv]] = '-'; //rendering the pillars pertinent to the block 						           
                            //_tmp_r =_f; //ensuring we correctly identify completion of pillars
														 //printf("   %d||%d||%d", _temp_r[_rnd][_ac], _ac, _temp_r[_rnd][(_f + _tmp_s + 1) - 2]);
														 //exit(EXIT_FAILURE);
													 //printf("%d||%d||%d||%d ", _temp_r[_rnd][_f + _tmp_s - 1], _temp_r[_rnd][_f], is_pillar, _c < (int) _temp_r[_rnd][_f] - 4);
                           is_pillar = true; //responsible for re-irendering the block-pillars  
											    } 
                   
                          if(*_coerc != 0) {printf("%c", _grid_d[_rnd][_temp_r[_rnd][_f - 5] + 1]); exit(EXIT_FAILURE);}
                       
                       }
                       
								   }

               }
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

     return false;
}


extern _bool_ _transform_blc(int _temp_r[5][25], int _temp_l[12][100]){
    //handle transformation request whose transformation will collide with an inaccessible composite block of an object(i.e transformed coordinates align)(do not compute the request)
    //identify general length for horizontal alignment(traverse for identical cells x2), reposition and gauge it via linking unaligned cells to the corresponding in the (using the compared) original grid and match the pattern using the differences 	
	  //store the bitwise state, transform mirroringly the coordinates to the "extrinsic" to the original length-pattern and reposition to the abs((length - inversed tail coordinate) for the inversion, non-inversible verifying for each x cell && x row != x cell + 2(otherwise invert) 
   //inversion((horizontal ln - horizontal crd) - (transformed vertical composite ln - transformed vertical crd))    
    //inverse by center, (ct + abs(crd - ct) - (ct - (crd + 1))  
   return true;
}

extern inline size_t _ln_cl(int _templ_r[5][25], size_t _rnd) {for (size_t _cl = 0; true ; _cl++) {if(_templ_r[_rnd][_cl] == 1000) {return --_cl;}}}

#define _sective_v(_av_r) \
	 _av_r _fi_act##_av_r(_av_r _aa) { \
		  return _av_r == 10; } \



//int pthread_create(pthread_t* restrict td, const pthread_attr_t* restrict tattr, void* (*start_routine) (void*), void* restrict arg);


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
	int _temp_r[5][25] = { //TODO adhere to identical length properties(i.e either separate or artificially equalize)
		//{0, 5, 0, 8, 3, 5, 3, 8, 3, 11, 6, 5, 6, 8, 6, 11}
		//TODO replace with negative rows
		{-6, 5, -6, 8, -6, 11, -3, 5, -3, 8, -3, 11, 0, 5, 0, 8, 0, 11, 1000},//rectangle
		{-9, 5, -9, 8, -6, 5, -6, 8, -3, 5, -3, 8, -3, 11, 0, 5, 0, 8, 0, 11, 1000},//L
    //{0, 5, 0, 8, 0, 5, 0, 8, 0, 11, 0, 5, 0, 8, 0, 11, 0, 8, 0, 11, 0, 8, 0, 11},
		{-3, 5, -3, 8, -3, 11, -3, 14, -3, 17, -3, 20, 0, 11, 0, 14, 1000}, //1 x 4 shape
		//{0, 5, 0, 8, 0, 11, 0, 5, 0, 8, 0, 11, 0, 8, 11},
		
	//each cell is preceded by row since no consistent generic pattern could be extracted to differentiate different composites while row-associating with the composite(e.g rows could equate to cells with differing composite-size)	  
	};


	static int32 _coerc = 0;
  static bool _sective = false;
  system("clear");
	//invertedly visible blocks, as dynamically reserving spatial/partial requirements itself 
	//either submuse border coordinates during collision, or treat one row prior as such
	//_ptr_int32* _sect = _deco(_templ_r);
	//system("clear");
  //buff_render(_grid_d);
 
	char16 _grid_[12][100] = {};
  memcpy(_grid_, _grid_d, 120 * 10); 	

	while(true){	
		//_pause_thread(500); 
		//$Recycle.Bin_repl_fl(_templ_r, _grid_d, 0);
	 //sleep(0.4); 
	 _repl_fl(_temp_r, _grid_d, 0, &_coerc, &_sective);
  }
  //_repl_fl (_temp_r, _grid_d, 0, &_coerc, _sective);
   //printf("%d:%d", _coerc, _temp_r[0][18 - _coerc]);
	 //_BUFF_REND(NULL, _grid_d, _grid_);
   //exit(EXIT_FAILURE);
   // exit(EXIT_FAILURE);
  //_repl_fl(_temp_r, _grid_d, 0, &_coerc);
	 //printf("%d", _temp_r[0][_ln_cl(_temp_r, 0) - 1]);
		//handle collision 
		//iteratively derive the collided block composite's coordinates, check for neighbouring col`lision.
    
		//printf("%lld",(size_t) (sizeof(_temp_r[2]) / sizeof(_temp_r[2][0]))); 

		//isince we're directly and randomly operating on the predefined blocks, a collision implies the reset of the blocks
	/*
  if(!(getch() == KEY_RIGHT)) {

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
*/
	//_init_grd(_grid); 

