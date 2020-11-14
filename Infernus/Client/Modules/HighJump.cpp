#include "HighJump.h"
#include "../../SDK/Minecraft.h"

void HighJump::onJump(float* jumpHeight) {
	*jumpHeight = jumpValue;
};