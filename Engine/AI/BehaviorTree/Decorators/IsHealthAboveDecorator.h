/****************************************************************************
 //	Usagi Engine, Copyright © Vitei, Inc. 2013
 //	Description: Will run child if health is below a certain value.
 *****************************************************************************/
#ifndef __USG_AI_BEHAVIOR_TREE_DECORATORS_IS_HEALTH_ABOVE_DECORATOR__
#define __USG_AI_BEHAVIOR_TREE_DECORATORS_IS_HEALTH_ABOVE_DECORATOR__

#include "Engine/AI/BehaviorTree/Decorator.h"
#include "Engine/AI/BehaviorTree/BehaviorCommon.pb.h"
namespace usg
{

namespace ai
{

template <class ContextType>
class dcIsHealthAbove : public IDecorator<ContextType>
{
public:
	void SetData(const usg::ai::IsHealthAbove& data)
	{
		m_data.health = data.health;
	}
protected:
	virtual int Update(float fElapsed, ContextType& ctx)
	{
		if(ctx.Health() > m_data.health)
		{
			return this->GetChild().Tick(fElapsed, ctx);
		}

		return BH_FAILURE;
	}

	usg::ai::IsHealthAbove m_data;
};

}	//	namespace ai

}	//	namespace usg

#endif	//	__USG_AI_BEHAVIOR_TREE_DECORATORS_IS_HEALTH_ABOVE_DECORATOR__