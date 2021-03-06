#include "includes/platformdefines.inc"
#include "includes/global_3d.inc"

// Input attributes
ATTRIB_LOC(0) in vec3 ao_position;

// Output attributes
ATTRIB_LOC(0) out vec3 vo_vTexCoord;

// Motion blur
ATTRIB_LOC(1) out vec4 vo_vScreenPos;

void main(void)
{
	vec3 vPosition = ao_position + vEyePos.xyz;
	vec4 vViewPos = vec4(vPosition, 1.0) * mViewMat;	// Reverse ordering as a mat3x4
	vec4 vProjPos = vec4( vViewPos.xyz, 1.0 ) * mProjMat;

	gl_Position = vProjPos;

	vec3 vTexCoord = ao_position;
  	vo_vTexCoord = vTexCoord;
   
   	vo_vScreenPos = vProjPos;
}


