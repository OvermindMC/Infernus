#include "Velocity.h"
#include "../../SDK/Minecraft.h"

void Velocity::onLerpMotion(Vec3* Vel) {
	if (Minecraft::GetLocalPlayer() != nullptr) {
		Vel->x *= modifyX, Vel->y *= modifyY = modifyZ, Vel->z = 0.0f;
	};
};