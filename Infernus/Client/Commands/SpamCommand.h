#pragma once
#include "../../Other/VComponent.h"
#include "../Modules/Spammer.h"

class SpamCommand : public VCommand {
public:
	SpamCommand() : VCommand::VCommand("spam", "Changes the message for the spam module") {};
	void execute(std::string, std::vector<std::string>);
};

void SpamCommand::execute(std::string input, std::vector<std::string> words) {
	Spammer* SpamModule = (Spammer*)ClientHandler::GetModule(Spammer());
	if (SpamModule != nullptr) {
		if (words.size() > 1) {
			std::string spamMessage = input.substr(input.find_first_of(" \t") + 1);
			SpamModule->message = spamMessage;
			if (SpamModule->message == spamMessage) {
				this->reply("Successfully updated the spam message!");
			}
			else {
				this->reply("Failed to update the spam message!");
			};
		}
		else {
			this->reply("You did not enter a message!");
		};
	};
};