/****************************************************************************
//	Usagi Engine, Copyright © Vitei, Inc. 2013
****************************************************************************/
#pragma once

#ifndef SYSTEM_H
#define SYSTEM_H


#include "ComponentEntity.h"
#include "ComponentGetter.h"
#include "SystemCategories.h"
#include "Engine/Physics/RaycastHitBase.h"

namespace usg {

	class GFXDevice;
	struct AsyncRaycastRequest;
	typedef struct _Collision Collision;

	enum FeatureSwitch
	{
		OFF = 0,
		ON = 1
	};

	template<typename... Args>
	struct Exclusion {};

	class System
	{
	public:
		typedef Exclusion<> ExclusionComponents;
		struct Inputs {};
		struct Outputs {};
		static bool GetInputOutputs(ComponentGetter& GetComponent, Inputs& inputs, Outputs& outputs) { return true; }

		struct ColliderInputs {};
		struct TriggererInputs {};
		static bool GetColliderInputs(ComponentGetter& GetComponent, ColliderInputs& colliderInputs) { return true; }
		static bool GetTriggererInputs(ComponentGetter& GetComponent, TriggererInputs& triggerInputs) { return true; }

		// Used by the boilerplate tool to determine whether it should autogenerate parts of the definition
		static const FeatureSwitch AUTOGENERATE_GET_INPUT_OUTPUTS = OFF;
		static const FeatureSwitch AUTOGENERATE_GET_COLLIDER_INPUTS = OFF;
		static const FeatureSwitch AUTOGENERATE_GET_TRIGGERER_INPUTS = OFF;
		static const FeatureSwitch AUTOGENERATE_GET_RAYCASTHIT_INPUTS = OFF;
		static const FeatureSwitch AUTOGENERATE_CHECK_EXCLUSIONS = OFF;
		static const uint32 OnCollisionMask = 0x0;

		static const usg::SystemCategory CATEGORY = (usg::SystemCategory)0;

	private:
		System() {}
	};

	// Systems can override this function to register themselves with the coordinator
	class SystemCoordinator;
	template<typename SYSTEM>
	void RegisterSystem(SystemCoordinator&);
	template<typename SYSTEM>
	void RegisterComponents(SystemCoordinator&);

	// For systems which can be fully autogenerated, this macro makes writing them much
	// simpler.  The parameter is the priority/category for that system.
#define DECLARE_SYSTEM(Category) \
	static const usg::SystemCategory CATEGORY = (usg::SystemCategory)Category; \
	static const FeatureSwitch AUTOGENERATE_GET_INPUT_OUTPUTS   = ON; \
	static unsigned int GetSystemId(); \
	static bool GetInputOutputs(usg::ComponentGetter GetComponent, Inputs& inputs, Outputs& outputs); \
	static const char* Name();

#define EXCLUSION(...) template<typename A,typename B> using IfHas = usg::pair<A, B>; typedef usg::Exclusion<__VA_ARGS__> ExclusionComponents; static const FeatureSwitch AUTOGENERATE_CHECK_EXCLUSIONS = ON; \

#define COLLIDABLE(x) \
	static const FeatureSwitch AUTOGENERATE_GET_COLLIDER_INPUTS = ON; \
	static bool GetColliderInputs(usg::ComponentGetter GetComponent, const uint32 uColliderGroup, ColliderInputs& colliderInputs); \
	static const uint32 OnCollisionMask = x;

#define TRIGGERABLE \
	static const FeatureSwitch AUTOGENERATE_GET_TRIGGERER_INPUTS = ON; \
	static bool GetTriggererInputs(usg::ComponentGetter GetComponent, TriggererInputs& colliderInputs);

#define RAYCASTER \
	static const FeatureSwitch AUTOGENERATE_GET_RAYCASTHIT_INPUTS = ON; \
	struct RaycastHit : usg::RaycastHitBase { RaycastHit(const RaycastHitInputs& inputs) : raycastHitInputs(inputs) {} const RaycastHitInputs& raycastHitInputs; }; \
	struct RaycastResult { uint32 uRaycastId; uint32 uNumHits; const RaycastHit* hits; }; \
	static bool GetRaycastHitInputs(usg::ComponentGetter GetComponent, RaycastHitInputs& colliderInputs); \
	static void RaycastAsync(const Inputs& inputs, const usg::AsyncRaycastRequest& request);

	// Helper macro for those systems still using the old, global GetInputOutputs method.
	// When you switch over to the new one, you can delete the DEPRECATED_GETINPUTOUTPUTS
	// from your System.
#define DEPRECATED_GETINPUTOUTPUTS \
	inline static bool GetInputOutputs(usg::ComponentGetter& GetComponent, Inputs& inputs, Outputs& outputs) \
	{ return GetInputOutputs(GetComponent.GetEntity(), inputs, outputs); }
}

#define GENERATED_SYSTEM_CODE(PATH) STRINGIFY( PATH.bp.cpp )

namespace Systems {
	// Expose these symbols in the global Systems namespace so we can use them
	// easily in system definitions
	using usg::FeatureSwitch;
	using usg::ON;
	using usg::OFF;
}

#endif // SYSTEM_H
