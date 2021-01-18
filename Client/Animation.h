#ifndef ANIMATION_H
#define ANIMATION_h

class CGraphicsComponent;

class CAnimation
{
public:
	explicit										CAnimation			(CGraphicsComponent* pOwner);
												   ~CAnimation			(void);

					void							Initialize			(void);
					void							Update				(void);
					void							LateUpdate			(void);
					void							Release				(void);

					void							StateChangeInit		(void);

	GETTOR_SETTOR	(ANIMATION::STATUS,				m_status,			Status);

	GETTOR_SETTOR	(float,							m_aniSecPerFrame,	AniSecPerFrame);
	GETTOR_SETTOR	(float,							m_curIndex,			CurIndex);
	GETTOR_SETTOR	(int,							m_maxIndex,			MaxIndex);
	GETTOR_SETTOR	(bool,							m_repeat,			Repeat);
	GETTOR			(CGraphicsComponent*,			m_pOwner,			Owner);

};

#endif