#include <iostream>
#include <string>

std::wstring readsecret() {
    std::wstring password;
    wchar_t ch;

    while (true) {
        ch = _getwch(); // ��������� ������ ��� �����������

        if (ch == L'\r') { // Enter
            std::wcout << std::endl;
            break;
        }
        else if (ch == L'\b') { // Backspace
            if (!password.empty()) {
                password.pop_back();
                std::wcout << L"\b \b"; // ������� �������� � ������
            }
        }
        else {
            password.push_back(ch);
            std::wcout << L'*'; // ���������� �������� ������ �������
        }
    }

    return password;
}