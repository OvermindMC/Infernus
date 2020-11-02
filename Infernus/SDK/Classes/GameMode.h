#pragma once

class GameMode
{
public:
	LocalPlayer* Player; //0x0008
	void survivalDestroyBlock(Vec3_i* block, int face, bool& isDestroyedOut, bool isFirst) {
		auto player = this->Player;
		player->swing();

		if (isFirst) {
			this->startDestroyBlock(block, face, isDestroyedOut);
		}
		else {
			*reinterpret_cast<bool*>(reinterpret_cast<__int64>(player) + 0x1C5A) = 1;
			this->continueDestroyBlock(block, face, isDestroyedOut);
		};

		player->startDestroying();
		*reinterpret_cast<bool*>(reinterpret_cast<__int64>(player) + 0x1C5A) = 0;
	};

public:
	virtual void Destructor();
	virtual void startDestroyBlock(Vec3_i*, UCHAR, bool);
	virtual void destroyBlock(Vec3_i*, UCHAR);
	virtual void continueDestroyBlock(Vec3_i*, UCHAR, bool);
	virtual void stopDestroyBlock(Vec3_i*);
	virtual void startBuildBlock(Vec3_i*, UCHAR);
	virtual void buildBlock(Vec3_i*, UCHAR);
	virtual void continueBuildBlock(Vec3_i*, UCHAR);
	virtual void stopBuildBlock(void);
	virtual void tick(void);
	virtual float getPickRange();
	virtual void useItem();
	virtual void useItemOn();
	virtual void interact(Actor*, Vec3*);
	virtual void attack(Actor*);
	virtual void releaseUsingItem();
}; //Size: 0x0040