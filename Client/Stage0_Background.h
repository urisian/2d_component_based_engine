#ifndef STAGE0_BACKGROUND_H
#define STAGE0_BACKGROUND_H

#include "Background.h"
class CStage0_Background : public CBackground
{
public:
	explicit					CStage0_Background	(void);
	virtual					   ~CStage0_Background	(void);

	virtual			void		Initialize			(void);
	virtual			void		Update				(void);
	virtual			void		LateUpdate			(void);
	virtual			void		Release				(void);
};

#endif