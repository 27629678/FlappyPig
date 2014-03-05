/* *************************************
 *
 *	公用宏
 *
 *	2014/3/2
 *
 *	sddz_yuxiaohua@163.com
 *
 * ************************************/

//	屏幕宽度
#define SCREEN_WIDTH			960

//	屏幕高度
#define SCREEN_HEIGHT			640

//	角色起始位置x
#define ORIGINAL_POSITION_X		480

//	角色起始位置y
#define ORIGINAL_POSITION_Y		320

//	柱子间隔距离
#define INTERNAL_DISTANCE		200

//	角色水平移动速度
#define PLAYER_HORIZONTAL_VELCITY	100

//	角色垂直移动速度
#define PLAYER_VERTICAL_VELCITY		100

//	角色向上加速度
#define PLAYER_ACCELERATE_UP		500

//	角色向下加速度
#define PLAYER_ACCELERATE_DOWN		400


/*	Equation
 *
 *	s=v*t				pig的水平位移
 *
 *	v1=v0+(a-g)*t		v0=y轴的初速度；当松开屏幕时，a=0；v1>0时向上飞，v1<0时向下飞；
 *
 *	L=v0*t+(a-g)*t/2	pig的垂直位移
 *
 *	P.S.				当pig移动至屏幕最右侧时，不可再向右移动，不死亡
 */