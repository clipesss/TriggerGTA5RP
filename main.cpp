#include <Windows.h>
#include "auth.hpp"
#include <string>
#include "utils.hpp"
#include "skStr.h"
#include <iostream>
#include <string>
#include <Shellapi.h>

#define IDI_ICON1                       101
using namespace std;
std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);
const std::string compilation_date = (std::string)skCrypt(__DATE__);
const std::string compilation_time = (std::string)skCrypt(__TIME__);

using namespace KeyAuth;

auto name = skCrypt("clipesss"); 
auto ownerid = skCrypt("YOUR_OWNER_ID");
auto secret = skCrypt("YOUR_SECRET_PHRASE"); 
auto version = skCrypt("1.0"); 
auto url = skCrypt("https://keyauth.win/api/1.2/"); 

api KeyAuthApp(name.decrypt(), ownerid.decrypt(), secret.decrypt(), version.decrypt(), url.decrypt());

int main()
{
    setlocale(LC_ALL, "ru");
    srand(static_cast<unsigned>(time(nullptr))); 

    HWND consoleWindow = GetConsoleWindow();

    SetLayeredWindowAttributes(consoleWindow, 0, 192, LWA_ALPHA);
    const string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int length = 32; 
    
    name.clear(); ownerid.clear(); secret.clear(); version.clear(); url.clear();
    
   
    std::cout << skCrypt("\n\n Подключение..");
    int a = 1;
    while (a < 155)
    {
        string result(length, ' '); 

        for (int i = 0; i < length; ++i) {
            result[i] = characters[rand() % characters.size()]; 
        }

        wstring title = wstring(result.begin(), result.end());

        SetConsoleTitleW(title.c_str());

       
        Sleep(42);
        a++;
    }
    KeyAuthApp.init();
    std::string consoleTitle = skCrypt("Clipesss Trigger | DC: your_ds").decrypt();
    SetConsoleTitleA(consoleTitle.c_str());
    if (!KeyAuthApp.data.success)
    {
        std::cout << skCrypt("\n Статус: ") << KeyAuthApp.data.message;
        Sleep(1500);
        exit(1);
    }

    if (std::filesystem::exists("test.json")) 
    {
        if (!CheckIfJsonKeyExists("test.json", "username"))
        {
            std::string key = ReadFromJson("test.json", "license");
            KeyAuthApp.license(key);
            if (!KeyAuthApp.data.success)
            {
                std::remove("test.json");
                std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
                Sleep(1500);
                exit(1);
            }
            std::cout << skCrypt("\n\n Successfully Automatically Logged In\n");
        }
        else
        {
            std::string username = ReadFromJson("test.json", "username");
            std::string password = ReadFromJson("test.json", "password");
            KeyAuthApp.login(username, password);
            if (!KeyAuthApp.data.success)
            {
                std::remove("test.json");
                std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
                Sleep(1500);
                exit(1);
            }
            std::cout << skCrypt("\n\n Successfully Automatically Logged In\n");
        }
    }
    
    else
    {

        std::cout << skCrypt("\n\n [1] Вход с ключем активации \n [2] Инфа Тригера \n\n Выбор опции: ");

        int option;

        std::string key;

        std::cin >> option;
        switch (option)
        {
        case 1:
            std::cout << skCrypt("\n Введите ключ: ");
            std::cin >> key;
            KeyAuthApp.license(key);
            break;
        case 2:
            std::cout << skCrypt("\n 1. Обязательно должен стоять простой прицел гта5 кружок, в ином случаи работать нечего не будет!. \n 2. Программа может быть запущена сразу же после включения ПК, это не помешает работе других игр и вашего ПК. \n 3. Активация тригера на Левый Альт (Left Alt). \n 4. Для выключение программы нужно зайти в диспечер задачь и отключить программу Soundpad Crack. ");
            Sleep(8000);
            exit(1);
        default:
            std::cout << skCrypt("\n\n Статус: Ошибка выбора опции");
            Sleep(3000);
            exit(1);

        }




        if (!KeyAuthApp.data.success)
        {
            std::cout << skCrypt("\n Статус ошибки: ") << KeyAuthApp.data.message;
            Sleep(1500);
            exit(1);
        }

        std::cout << skCrypt("\n Данные о пользователе:");
        std::cout << skCrypt("\n IP адрес: ") << KeyAuthApp.data.ip;
        std::cout << skCrypt("\n Железо: ") << KeyAuthApp.data.hwid;
        std::cout << skCrypt("\n Действие ключа до: ");

        for (int i = 0; i < KeyAuthApp.data.subscriptions.size(); i++) {
            auto sub = KeyAuthApp.data.subscriptions.at(i);
            std::cout << skCrypt("") << tm_to_readable_time(timet_to_tm(string_to_timet(sub.expiry)));
        }

        std::cout << skCrypt("\n\n Тригер начнет свою работу через 10 секунд... \n Это окно будет закрыто, убедится что тригер работает можно посмотреть в диспечер задачь и найти Soundpad Crack.");
        Sleep(10000);
        system("cls");
        HWND hwnd = GetConsoleWindow();
        ShowWindow(hwnd, SW_HIDE);
        COLORREF targetColor = RGB(0xC1, 0x4F, 0x4F);

        while (true) {

            if (GetAsyncKeyState(VK_LMENU) & 0x8000) {
                HDC hdc = GetDC(NULL);
                COLORREF pixelColor = GetPixel(hdc, 640, 360); 
                ReleaseDC(NULL, hdc);


                if (pixelColor == targetColor) {
                    INPUT input;
                    input.type = INPUT_MOUSE;
                    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
                    SendInput(1, &input, sizeof(INPUT));

                    Sleep(2);

                    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
                    SendInput(1, &input, sizeof(INPUT));
                }

                Sleep(2);
            }
            else {
                Sleep(2);
            }

        }
    }
    return 0;
}

std::string tm_to_readable_time(tm ctx) {
    char buffer[80];

    strftime(buffer, sizeof(buffer), "%a %m/%d/%y %H:%M:%S %Z", &ctx);

    return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
    auto cv = strtol(timestamp.c_str(), NULL, 10); 

    return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
    std::tm context;
    localtime_s(&context, &timestamp);
    return context;
}
