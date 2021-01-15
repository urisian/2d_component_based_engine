#ifndef MYDEFINES_H
#define MYDEFINES_H

//그래픽엔진 버텍스 형식 FVF=Flexible Vertex Format
#define D3DFVF_CUSTOMVERTEX ( D3DFVF_XYZ | D3DFVF_TEX1)


//비트별로 키 할당
#define KEY_LEFT	1
#define KEY_RIGHT	2
#define KEY_UP		4
#define KEY_DOWN	8
#define KEY_SPACE	16
#define KEY_RETURN	32
#define MOUSE_LEFT	64
#define MOUSE_RIGHT	128
#define KEY_F1		256
#define KEY_F2		512
#define KEY_F3		1024
#define KEY_F4		2048
#define KEY_F5		4096



#if _DEBUG
//디버거 세팅용
#define GENERAL_DEBUG
//#define SPECIFIC_DEBUG
#endif


//Math
#define PI 3.141592f


//메모리 누수용
#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

#endif // !MYDEFINES_H
