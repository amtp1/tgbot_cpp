#include <stdio.h>
#include <iostream>
#include <fstream>
#include <tgbot/tgbot.h>
#define bot_api bot.getApi()

using namespace std;

string load_token(){
    string token;

    ifstream file("config.txt");

    if (!file){
        printf("Don't open!\n");
    }else{
        printf("File opened. Configuration loaded.\n");
    }

    getline(file, token);

    return token;
}

int main() {
    TgBot::Bot bot(load_token());
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot_api.sendMessage(message->chat->id, "Hey, this is ubi bot!");
    });

    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
        bot_api.sendMessage(message->chat->id, "UBI Bot -> Message: " + message->text);
    });

    try {
        printf("Bot username: %s\n", bot_api.getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        printf("Long poll started\n");
        while (true) {
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }

    return 0;
}