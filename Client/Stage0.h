#ifndef STAGE0_H
#define STAGE0_H

#include "GameState.h"
class CStage0 : public CGameState
{
public:
	explicit						CStage0					(void);
	virtual						   ~CStage0					(void);

					void			Initialize				(void);
					void			Update					(void);
					void			LateUpdate				(void);
					void			Release					(void);
};

#endif