/****************************************************************************
//	Usagi Engine, Copyright © Vitei, Inc. 2013
//	Description: Removes the current target if any
*****************************************************************************/
#ifndef __USG_AI_BEHAVIOR_TREE_BEHAVIORS_REMOVE_TARGET_BEHAVIOR__
#define __USG_AI_BEHAVIOR_TREE_BEHAVIORS_REMOVE_TARGET_BEHAVIOR__

#include "Engine/AI/BehaviorTree/Behavior.h"

namespace usg
{

namespace ai
{

template <class ContextType>
class bhRemoveTarget : public IBehavior<ContextType>
{
public:
	virtual int Update(float fElapsed, ContextType& ctx)
	{
		if(!ctx.HasTarget())
		{
			return BH_FAILURE;
		}

		ctx.RemoveTarget();
		return BH_SUCCESS;
	}
};

}	//	namespace ai

}	//	namespace usg

#endif	//	__USG_AI_BEHAVIOR_TREE_BEHAVIORS_REMOVE_TARGET_BEHAVIOR__
