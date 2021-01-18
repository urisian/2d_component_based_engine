#ifndef MYENUM_H
#define MYENUM_H

namespace OBJID		{ enum ID { EFFECT, BUTTON, DECORATION, MONSTER, TURRET, UNIT, PROJECTILE, UI, END }; }
namespace DATAID	{ enum ID { ANIMATION, BUTTON, DECORATION, ENGINE, MONSTER, STAGE, TURRET, UI, UNIT, PROJECTILE, EFFECT, END }; }
namespace DEBUGID	{ enum ID { FRAMETIME, OBJECT_INFO, UI_INFO, END }; }

namespace ANIMATION {enum STATUS{ STOP, PAUSE, PLAY, END }; }

#endif // !MYENUM_H
