#pragma once

class LoopbackPacketSender
{
public:
	char pad_0008[8]; //0x0008
	class NetworkHandler* NetworkHandler; //0x0010
	char pad_0018[56]; //0x0018

	virtual void Function0();
	virtual void send(void* Packet);
	virtual void sendToServer(void* Packet);
}; //Size: 0x0010

class NetworkHandler
{
public:
	char pad_0000[24]; //0x0000
	class RakNetInstance* RakNetInstance; //0x0018
}; //Size: 0x0020

class RakNetInstance
{
public:
	char pad_0000[880]; //0x0000
	class TextHolder* ServerIP; //0x0370
	char pad_0378[48]; //0x0378

public:

	char* GetDynamicIP() {
		if (this != NULL) {
			uintptr_t** TextHolderPtr = reinterpret_cast<uintptr_t**>(reinterpret_cast<__int64>(this) + 0x370);
			return reinterpret_cast<char*>(*(UINT64*)TextHolderPtr);
		}
		else {
			return (char*)NULL;
		}
	};

}; //Size: 0x03A8