/****************************************************************************
//	Usagi Engine, Copyright © Vitei, Inc. 2013
****************************************************************************/
#ifndef _SYSTEM_CATEGORIES_H
#define _SYSTEM_CATEGORIES_H

namespace usg {

enum SystemCategory {
	SYSTEM_PRE_EARLY = -1100,
	SYSTEM_AI_TARGETING,
	SYSTEM_AI_TARGETING_CURRENT,
	SYSTEM_EARLY = -1000,
	SYSTEM_PRE_PHYSICS,
	SYSTEM_PHYSICS,
	SYSTEM_CAMERA,
	SYSTEM_CAMERA_LINE_TEST,
	SYSTEM_POST_EARLY,
	SYSTEM_TOUCHSCREEN_CONTROLLER,
	SYSTEM_MENU_CONTROLLER,
	SYSTEM_UI_ANIMCHAINS,
	SYSTEM_UI_CONTROLS,
	SYSTEM_BUTTONS,
	SYSTEM_PHYSICS_INDEPENDENT_GAMEPLAY,
	SYSTEM_POST_PHYSICS,
	SYSTEM_TRANSFORM_NESTED_RIGIDBODIES,
	SYSTEM_TRANSFORM_RIGIDBODIES,
	SYSTEM_SET_RIGIDBODIES_WORLD_TRANSFORM,
	SYSTEM_FETCH_VEHICLE_SIMULATION_RESULTS, // Any system depending on physics should come after this.
	SYSTEM_DEFAULT_PRIORITY = 0, // Default
	SYSTEM_POST_GAMEPLAY,
	SYSTEM_TRANSFORM,
	SYSTEM_HIERARCHY,
	SYSTEM_POST_TRANSFORM,
	SYSTEM_SCENE,

	SYSTEM_PRE_COLLISION = 999,
	SYSTEM_COLLISION = 1000,

	SYSTEM_CACHE = 2000
};

}

#endif // _SYSTEM_CATEGORIES_H
