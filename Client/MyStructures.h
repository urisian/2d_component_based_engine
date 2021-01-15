#ifndef MYSTRUCTURES_H
#define MYSTRUCTURES_H

//텍스쳐 정보 보유 스트럭쳐
typedef struct tagTexInfo
{
	LPDIRECT3DTEXTURE9 pTexture; // hBitmap과 동일한 역할이라고 생각하면 되겠다. 그림한장을 제어하기 위한 컴객체. 
	D3DXIMAGE_INFO tImageInfo;// 이미지의 정보를 파일에 읽어와 보관할 구조체. 
}TEXINFO;


//그래픽용 커스텀 버텍스 스트럭쳐
struct CustomVertex
{
	CustomVertex()
		:position(0.0f, 0.0f, 0.0f),
		texture(0.0f, 0.0f)
	{}

	CustomVertex(float x, float y, float z, float u, float v)
		:position(x, y, z),
		texture(u, v)
	{}

	CustomVertex(const D3DXVECTOR3& v, const D3DXVECTOR3& uv)
		:position(v),
		texture(uv)
	{}

	D3DXVECTOR3 position;   // Position Vector
	D3DXVECTOR2 texture;    // Texture  Coordinate
};

struct RingBoxInfo
{
	std::string		name;
	int				price;
	float			angle;
};


struct MonsterParty
{
	MonsterParty() :
		activated(false),
		monsterType(""),
		spawnStartTime(0),
		spawnCoolTime(0),
		routeNum(0)
	{}

	bool		activated;

	std::string monsterType;
	int			numOfMonster;
	int			routeNum;
	float		spawnStartTime;
	float		spawnCoolTime;
};


struct RouteInfo
{
	RouteInfo() :
		distanceFromGoal(0)
	{}

	float distanceFromGoal;
	std::vector<D3DXVECTOR3> routePoints;
};
#endif // !MYSTRUCTURES_H
