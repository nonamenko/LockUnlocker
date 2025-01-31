#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

// Функція для затримки виконання програми
void sleep_ms(int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

// Функція для обфускації ключа
string obfuscate(const string& input) {
    string result = input;
    for(char &c : result) {
        c ^= 0x5A; // XOR з фіксованим ключем
    }
    return result;
}

// Функція для перевірки ключа активації
bool checkActivationKey(const string& input) {
    // Обфускований правильний ключ
    const string obfuscatedKey = "\x13\x1E\x16\x1E\x1D\x1F\x1E\x14\x1C\x1E\x16\x1D\x1C"; // "Activate12345" XOR 0x5A

    if (input.length() != 12) { // Довжина оригінального ключа
        return false;
    }

    string obfuscatedInput = obfuscate(input);

    return obfuscatedInput == obfuscatedKey;
}

int main() {
    cout << "Вітаємо у LockUnlocker!\n";
    cout << "Будь ласка, введіть ключ активації: ";

    string userInput;
    cin >> userInput;

    // Невелика затримка для ускладнення аналізу
    sleep_ms(500);

    if (checkActivationKey(userInput)) {
        cout << "Вітаємо! Ви розбили LockUnlocker.\n";
    } else {
        cout << "Ключ невірний. Спробуйте ще раз.\n";
    }

    return 0;
}
