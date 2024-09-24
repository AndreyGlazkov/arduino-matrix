# pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>


class WeatherService {
    private:
        char* _apiKey;
        const String _url = "";
        const HTTPClient _httpClient;

    public:
        WeatherService() {};
        WeatherService(char* apiKey);
        void setCity(int cityCode);
        float getTemperature();
        int getWeatherCode();
};

WeatherService::WeatherService(char* apiKey) {
    _apiKey = apiKey;
};

