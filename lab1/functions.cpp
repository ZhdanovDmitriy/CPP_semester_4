#include "functions.h"

std::vector<long double> getCoefficients(std::string& const str) {
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    std::vector<long double> coefficients;
    std::smatch match;
    std::regex pattern("^([+-]?\\d*)\\*?x\\^2(?:([+-](\\d*))\\*?x)?(?:([+-]\\d+))?=([+-]?\\d+)$");

    if (std::regex_match(str, match, pattern)) {
        std::string a_str = match[1].str();
        long double a = 0;
        if (a_str.empty() || a_str == "+")
            a = 1;
        else if (a_str == "-")
            a = -1;
        else
            a = std::stoi(a_str);

        long double b = 0;
        if (match[2].matched) {
            std::string b_str = match[2].str();
            if (b_str == "+" || b_str == "")
                b = 1;
            else if (b_str == "-")
                b = -1;
            else
                b = std::stoi(b_str);
        }
        else {
            b = 0;
        }

        long double c_left = 0;
        if (match[4].matched) {
            c_left = std::stoi(match[4].str());
        }
        else {
            c_left = 0;
        }

        long double right_side = std::stoi(match[5].str());

        long double c = c_left - right_side;
        coefficients = { a, b, c };

        std::cout << "a = " << a << std::endl;
        std::cout << "b = " << b << std::endl;
        std::cout << "c = " << c << std::endl;
    }
    else {
        std::cout << "Incorrect input format!" << std::endl;
    }
    return coefficients;
}

bool isCorrectQuadraticEquation(std::vector<long double>& const coefficients) {
    long double a = coefficients[0];
    long double b = coefficients[1];
    long double c = coefficients[2];
    if (a == 0 && b != 0) {
        std::cout << "Not a quadratic equation" << std::endl;
        std::cout << "But I know answer: " << (- c / b) << std::endl;
        return 0;
    }
    else if (a == 0 && b == 0 && c == 0) {
        std::cout << "Not a quadratic equation" << std::endl;
        std::cout << "Any x is suitable" << std::endl;
        return 0;
    }
    else if (b == 0 && -(c / a) < 0) {
        std::cout << "No solutions" << std::endl;
        return 0;
    }
    else if (b*b - 4*a*c < 0) {
        std::cout << "No solutions" << std::endl;
        return 0;
    }
    else if(b*b - 4 * a * c == 0) {
        long double ans = (-(b / (2 * a)));
        if (ans == -0) {
            ans = 0;
        }
        std::cout << "Only one answer: x = " << ans << std::endl;
        return 0;
    }
    else {
        return 1;
    }
    
}

std::pair<long double, long double> solveQuadraticEquation(std::vector<long double>& const coefficients) {
    long double a = coefficients[0];
    long double b = coefficients[1];
    long double c = coefficients[2];
    if (b == 0) {
        return { std::sqrt(-(c / a)), -std::sqrt(-(c / a)) };
    }
    if (b * b - 4 * a * c >= 0) {
        return {(-b + std::sqrt(b * b - 4 * a * c)) / (2*a) , (-b - std::sqrt(b * b - 4 * a * c)) / (2 * a) };
    }
};

void printHead() {
    std::cout << "***              Zhdanov Dmitriy 5030102/3003                ***" << std::endl;
    std::cout << "***     A quadratic equation calculator in real numbers      ***" << std::endl;
    std::cout << "Enter the quadratic equation in the format : ax ^ 2 + bx + c = 0" << std::endl;
}