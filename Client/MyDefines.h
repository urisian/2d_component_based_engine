#ifndef MYDEFINES_H
#define MYDEFINES_H

//그래픽엔진 버텍스 형식 FVF=Flexible Vertex Format
#define D3DFVF_CUSTOMVERTEX ( D3DFVF_XYZ | D3DFVF_TEX1)


//비트별로 키 할당
#define KEY_LEFT	0x00000001
#define KEY_RIGHT	0x00000002
#define KEY_UP		0x00000004
#define KEY_DOWN	0x00000008
#define KEY_SPACE	0x00000010
#define KEY_RETURN	0x00000020
#define MOUSE_LEFT	0x00000040
#define MOUSE_RIGHT	0x00000080


//콘솔 버퍼 갯수
#define NUM_OF_BUFFER 2

#endif // !MYDEFINES_H
