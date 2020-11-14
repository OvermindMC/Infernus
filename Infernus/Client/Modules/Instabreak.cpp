#include "Instabreak.h"
#include "../../SDK/Minecraft.h"

void Instabreak::onDestroyBlock(GameMode* GM, Vec3_i* blockPos, uint8_t face) {
	GM->destroyBlock(blockPos, face);
};