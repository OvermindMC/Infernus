#include "NoPacket.h"
#include "../../SDK/Minecraft.h"

void NoPacket::onPacket(void* Packet, PacketType type, bool* cancel) {
	*cancel = true;
};