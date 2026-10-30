@echo off
g++ -std=c++17 -Wall -Wextra -pedantic -o NeoVerse.exe main.cpp Engineer.cpp Event.cpp EmergencyEvent.cpp CityData.cpp EventProcessor.cpp CityComponent.cpp PowerSystem.cpp TransportSystem.cpp HealthSystem.cpp SecuritySystem.cpp FileManager.cpp Report.cpp
if %errorlevel% neq 0 (
    echo Compilation failed.
    pause
    exit /b %errorlevel%
)
echo Compilation successful.
pause
