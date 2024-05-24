#ifndef TELEGRAM_H
#define TELEGRAM_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>

#include "search.h"
#include "telegram/telegram.h"

#define BOTDELAYTIME 1000

unsigned long lastTimeBotRan = 0;

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

TaskHandle_t Task1;

void processBot(void* parameter);

void setupBot() {
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  bot.sendMessage(CHAT_ID, "online again");

  // Create a task that will be executed in Task1code(), with priority 1 and
  // executed on core 0
  xTaskCreatePinnedToCore(
      processBot, /* Task function. */
      "Task1",    /* name of task. */
      10000,      /* Stack size of task */
      NULL,       /* parameter of the task */
      1,          /* priority of the task */
      &Task1,     /* Task handle to keep track of created task */
      1);         /* pin task to core 0 */
}

void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    // Chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID) {
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }

    // Print the received message
    String text = bot.messages[i].text;
    String from_name = bot.messages[i].from_name;
    Serial.println("msg[" + chat_id + ", " + from_name + "]->" + text);

    if (text == "/help") {
      bot.sendMessage(chat_id, generator->getSettings(), "");
    } else if (text == "/on") {
      status = true;
    } else if (text == "/off") {
      status = false;
    } else {
      int splitPoint = text.indexOf(":");
      if (splitPoint == -1) {
        bot.sendMessage(chat_id, "bad message", "");
        return;
      }
      String command = text.substring(0, splitPoint);
      String value = text.substring(splitPoint + 1, text.length());
      Serial.println(command + "(" + value + ")");

      if (command == "/brightness") {
        setBrightness(value);
      } else if (command == "/mode") {
        changeGenerator(value);
      } else {
        generator->settings(command, value);
      }
      bot.sendMessage(chat_id, "ok", "");
    }
  }
}

void processBot(void* parameter) {
  for (;;) {
    if (millis() > lastTimeBotRan + BOTDELAYTIME) {
      int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

      while (numNewMessages) {
        handleNewMessages(numNewMessages);
        numNewMessages = bot.getUpdates(bot.last_message_received + 1);
      }
      lastTimeBotRan = millis();
    }
  }
}

void log(String message) { bot.sendMessage(CHAT_ID, "logging: " + message); }
#endif