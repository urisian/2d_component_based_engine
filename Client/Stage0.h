#ifndef STAGE0_H
#define STAGE0_H

#include "Stage.h"

class CStage0 final : public CStage
{
public:
	explicit						CStage0					(void);
	virtual						   ~CStage0					(void);

					void			Initialize				(void);
					void			Update					(void);
					void			LateUpdate				(void);
					void			Release					(void);

private:
					void			SpawnWave				(void);
};

#endif