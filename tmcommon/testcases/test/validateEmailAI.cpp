#include <iostream>
#include <string>
#include <cctype>

bool is_valid_email(const std::string& email) {
    // Check for empty string
    if (email.empty()) {
        return false;
    }

    // Check for '@' symbol
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos || at_pos == 0 || at_pos == email.size() - 1) {
        return false;
    }

    // Check for '.' after '@'
    size_t dot_pos = email.find('.', at_pos + 1);
    if (dot_pos == std::string::npos || dot_pos == email.size() - 1) {
        return false;
    }

    // Check for invalid characters before '@'
    for (size_t i = 0; i < at_pos; ++i) {
        if (!isalnum(email[i]) && email[i] != '.' && email[i] != '-' && email[i] != '_') {
            return false;
        }
    }

    // Check for invalid characters after '@'
    for (size_t i = at_pos + 1; i < email.size(); ++i) {
        if (!isalnum(email[i]) && email[i] != '.' && email[i] != '-') {
            return false;
        }
    }

    // Check for consecutive dots
    if (email.find("..") != std::string::npos) {
        return false;
    }

    // Check domain length (basic)
    if (email.substr(dot_pos + 1).size() < 2) {
        return false;
    }

    return true;
}

int main() {
    std::string email;
    std::cout << "Enter email: ";
    std::getline(std::cin, email);

    if (is_valid_email(email)) {
        std::cout << "Valid email\n";
    } else {
        std::cout << "Invalid email\n";
    }

    return 0;
}
