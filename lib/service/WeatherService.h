# pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

class WeatherService {
    private:
        char* _apiKey;
        char* _city;
        const String _url = "https://api.weatherapi.com/v1/current.json";
        HTTPClient _httpClient;
        float temperature;
        int weatherCode;
        long timeLastUpdate = -999999999;
        void doRequestToServer();

    public:
        WeatherService() {};
        WeatherService(char* apiKey);
        void setCity(char* cityName);
        float getTemperature();
        int getWeatherCode();
};

WeatherService::WeatherService(char* apiKey) {
    _apiKey = apiKey;
};

void WeatherService::doRequestToServer() {
    String path = _url + "?key="+_apiKey+"&q="+_city;
    StaticJsonDocument<500> doc;
    _httpClient.begin(path);
    int httpResponseCode = _httpClient.GET();
    if (httpResponseCode>0) {
        String payload = _httpClient.getString();
        Serial.println(payload);
        deserializeJson(doc, payload);
        temperature = doc["current"]["temp_c"].as<float>();
        weatherCode = doc["current"]["condition"]["code"].as<int>();
        Serial.println(doc["current"]["temp_c"].as<float>());
    }
};

void WeatherService::setCity(char* cityName) {
    _city = cityName;
};

float WeatherService::getTemperature() {
    if (millis() - timeLastUpdate > 1000*60*30) {
        doRequestToServer();
        timeLastUpdate = millis();
    };
    return temperature;
};

int WeatherService::getWeatherCode() {
    if (millis() - timeLastUpdate > 1000*60*30) {
        doRequestToServer();
        timeLastUpdate = millis();
    };
    return weatherCode;
};