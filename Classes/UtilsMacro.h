/* *************************************
 *
 *	���ú�
 *
 *	2014/3/2
 *
 *	sddz_yuxiaohua@163.com
 *
 * ************************************/

//	��Ļ���
#define SCREEN_WIDTH			960

//	��Ļ�߶�
#define SCREEN_HEIGHT			640

//	��ɫ��ʼλ��x
#define ORIGINAL_POSITION_X		480

//	��ɫ��ʼλ��y
#define ORIGINAL_POSITION_Y		320

//	���Ӽ������
#define INTERNAL_DISTANCE		200

//	��ɫˮƽ�ƶ��ٶ�
#define PLAYER_HORIZONTAL_VELCITY	100

//	��ɫ��ֱ�ƶ��ٶ�
#define PLAYER_VERTICAL_VELCITY		100

//	��ɫ���ϼ��ٶ�
#define PLAYER_ACCELERATE_UP		500

//	��ɫ���¼��ٶ�
#define PLAYER_ACCELERATE_DOWN		400


/*	Equation
 *
 *	s=v*t				pig��ˮƽλ��
 *
 *	v1=v0+(a-g)*t		v0=y��ĳ��ٶȣ����ɿ���Ļʱ��a=0��v1>0ʱ���Ϸɣ�v1<0ʱ���·ɣ�
 *
 *	L=v0*t+(a-g)*t/2	pig�Ĵ�ֱλ��
 *
 *	P.S.				��pig�ƶ�����Ļ���Ҳ�ʱ�������������ƶ���������
 */