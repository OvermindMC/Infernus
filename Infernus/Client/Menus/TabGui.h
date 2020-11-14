#pragma once
#include "../../Other/VComponent.h"
#include "../../Other/RenderUtils.h"

class TabGui : public VModule {
public:
	TabGui() : VModule::VModule("TabGui", "Renders a UI to toggle modules, can be managed via arrow keys", 0x09) {
		this->isEnabled = true;
	};
	void onRender();
	void onKey(uint64_t, bool, bool*);
	bool handleKey(uint64_t);
private:
	bool categorySelected = false, moduleSelected = false;
	int selectedCategory = 0, selectedModule = 0;
};