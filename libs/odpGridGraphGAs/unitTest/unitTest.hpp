#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

namespace Cselab23Kimura {
    class UnitTest {
    public:
        UnitTest(std::string testName);
        bool successAll() const { return _success; }
        void showResult() const;
        void assertTrue(std::string label, bool value);
        void assertFalse(std::string label, bool value);
        void assertEqualInt(std::string label, int expected, int actual);
        void assertEqualFloat(std::string label, float expected, float actual, int sigFigs);
        void assertEqualDouble(std::string label, double expected, double actual, int sigFigs);
    private:
        const std::string _testName;
        bool _success;
        std::string floatToString(double value, int sigFigs);
    };

    UnitTest::UnitTest(std::string testName) : 
        _testName(testName),
        _success(true)
    {
        std::cout << testName << " : START"<< std::endl;
    }

    void UnitTest::showResult() const {
        if(_success) {
            std::cout << _testName << " : SUCCESS" << std::endl;
        }
        else {
            std::cout << _testName << " : FAILED" << std::endl;
        }
    }

    void UnitTest::assertTrue(std::string label, bool value) {
        if(value == true) return;

        std::cout << "\t" << label << ": [Expected] true, [Actual] false" << std::endl;
        _success = false;
    }

    void UnitTest::assertFalse(std::string label, bool value) {
        if(value == false) return;

        std::cout << "\t" << label << ": [Expected] false, [Actual] true" << std::endl;
        _success = false;
    }

    void UnitTest::assertEqualInt(std::string label, int expected, int actual) {
        if(expected == actual) return;

        std::string expectedStr = std::to_string(expected);
        std::string actualStr  = std::to_string(actual);
        std::cout << "\t" << label << ": [Expected] " << expectedStr << ", [Actual] " << actualStr << std::endl;
        _success = false;
    }

    void UnitTest::assertEqualFloat(std::string label, float expected, float actual, int sigFigs) {
        float error = std::abs(expected - actual);
        float torelance = std::pow(0.1, sigFigs);
        if(error < torelance) return;

        std::string expectedStr = floatToString(expected, sigFigs);
        std::string actualStr   = floatToString(actual, sigFigs);
        std::cout << "\t" << label << ": [Expected] " << expectedStr << ", [Actual] " << actualStr << std::endl;
        _success = false;
    }

    void UnitTest::assertEqualDouble(std::string label, double expected, double actual, int sigFigs) {
        double error = std::abs(expected - actual);
        double torelance = std::pow(0.1, sigFigs);
        if(error < torelance) return;

        std::string expectedStr = floatToString(expected, sigFigs);
        std::string actualStr   = floatToString(actual, sigFigs);
        std::cout << "\t" << label << ": [Expected] " << expectedStr << ", [Actual] " << actualStr << std::endl;
        _success = false;
    }

    std::string UnitTest::floatToString(double value, int sigFigs) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(sigFigs) << value;
        return oss.str();
    }
}