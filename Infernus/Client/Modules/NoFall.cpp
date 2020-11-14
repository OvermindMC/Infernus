#include "NoFall.h"
#include "../../SDK/Minecraft.h"

void NoFall::onPacket(void* Packet, PacketType Type, bool* cancel) {
	if (Type == PacketType::ActorFallPacket) {
		*cancel = true;
	};
};