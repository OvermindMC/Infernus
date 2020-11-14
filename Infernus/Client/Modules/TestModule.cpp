#include "TestModule.h"
#include "../../SDK/Minecraft.h"

void TestModule::onPacket(void* Packet, PacketType type, bool* cancel) {
	char logged[0x0400];
	memcpy(logged, Packet, 0x0400);

	std::string filePath = Utils::PacketsDir();
	std::string fileName;

	if (type == PacketType::MovePlayerPacket) {
		fileName = std::string("MovePlayerPacket " + std::to_string(MovePacketsID));
		MovePacketsID++;
	};

	if (type == PacketType::PlayerAuthInput) {
		fileName = std::string("PlayerAuth " + std::to_string(PlayerAuthPacketsID));
		PlayerAuthPacketsID++;
	};

	if (type == PacketType::ActorFallPacket) {
		fileName = std::string("ActorFall " + std::to_string(ActorFallPacketsID));
		ActorFallPacketsID++;
	};

	if (type == PacketType::MobEquipmentPacket) {
		fileName = std::string("MobEquipment " + std::to_string(MobEquipmentPacketsID));
		MobEquipmentPacketsID++;
	};

	if (type == PacketType::TextPacket) {
		fileName = std::string("TextPacket " + std::to_string(TextPacketsID));
		TextPacketsID++;
	};

	if (type == PacketType::Unknown) {
		fileName = std::string("Unknown" + std::to_string(UnknownPacketsID));
		UnknownPacketsID++;
	};

	std::ofstream fout;
	fout.open(std::string(Utils::PacketsDir() + std::string("\\") + fileName + ".txt"), std::ios::binary | std::ios::out);
	fout.write(logged, 0x0400);
	fout.close();
};