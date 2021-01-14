#ifndef MYENUM_H
#define MYENUM_H

namespace OBJID		{ enum ID { BUTTON, DECORATION, MONSTER, PROJECTILE, TURRET, UNIT, UI, END }; }
namespace DATAID	{ enum ID { ANIMATION, BUTTON, DECORATION, ENGINE, MONSTER, STAGE, TURRET, UI, UNIT, END }; }
namespace DEBUGID	{ enum ID { FRAMETIME, OBJECT_INFO, UI_INFO, END }; }
namespace COLID		{ enum ID { UNIT, TURRET, PROJECTILE, SKILL, eUNIT, ePROJECTILE, eSKILL, END}; } 

namespace ANIMATION {enum STATUS{ STOP, PAUSE, PLAY, END }; }

namespace RBTYPE	{ enum TYPE { CIRCLE, RECT }; }
#endif // !MYENUM_H
