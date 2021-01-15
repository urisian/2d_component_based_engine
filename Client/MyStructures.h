#ifndef MYSTRUCTURES_H
#define MYSTRUCTURES_H

//�ؽ��� ���� ���� ��Ʈ����
typedef struct tagTexInfo
{
	LPDIRECT3DTEXTURE9 pTexture; // hBitmap�� ������ �����̶�� �����ϸ� �ǰڴ�. �׸������� �����ϱ� ���� �İ�ü. 
	D3DXIMAGE_INFO tImageInfo;// �̹����� ������ ���Ͽ� �о�� ������ ����ü. 
}TEXINFO;


//�׷��ȿ� Ŀ���� ���ؽ� ��Ʈ����
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
