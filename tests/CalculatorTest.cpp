#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "SimpleCalculator.h"
#include "InMemoryHistory.h"

using namespace calc;
using ::testing::Return;

// Мок для IHistory
class HistoryMock : public IHistory {
public:
    MOCK_METHOD(void, AddEntry, (const std::string&), (override));
    MOCK_METHOD(std::vector<std::string>, GetLastOperations, (size_t), (const, override));
};

// Тесты калькулятора

TEST(SimpleCalculatorTest, Add_WorksCorrectly) {
    InMemoryHistory history;
    SimpleCalculator calc(history);
    EXPECT_EQ(calc.Add(2, 3), 5);
}

TEST(SimpleCalculatorTest, Subtract_WorksCorrectly) {
    InMemoryHistory history;
    SimpleCalculator calc(history);
    EXPECT_EQ(calc.Subtract(10, 4), 6);
}

TEST(SimpleCalculatorTest, Multiply_WorksCorrectly) {
    InMemoryHistory history;
    SimpleCalculator calc(history);
    EXPECT_EQ(calc.Multiply(3, 4), 12);
}

TEST(SimpleCalculatorTest, Divide_WorksCorrectly) {
    InMemoryHistory history;
    SimpleCalculator calc(history);
    EXPECT_EQ(calc.Divide(12, 3), 4);
}

TEST(SimpleCalculatorTest, Divide_ByZero_ThrowsException) {
    InMemoryHistory history;
    SimpleCalculator calc(history);
    EXPECT_THROW(calc.Divide(5, 0), std::invalid_argument);
}

//  Проверка граничных значений

TEST(SimpleCalculatorTest, Add_MaxInt_NoOverflowExpected) {
    InMemoryHistory history;
    SimpleCalculator calc(history);
    int maxVal = std::numeric_limits<int>::max();
    EXPECT_NO_THROW(calc.Add(maxVal, -1));
}

// Проверка логирования истории 

TEST(InMemoryHistoryTest, History_SavesEntriesCorrectly) {
    InMemoryHistory history;
    history.AddEntry("1 + 1 = 2");
    history.AddEntry("3 + 5 = 8");

    auto recent = history.GetLastOperations(2);
    ASSERT_EQ(recent.size(), 2);
    EXPECT_EQ(recent[0], "1 + 1 = 2");
    EXPECT_EQ(recent[1], "3 + 5 = 8");
}

// Проверка логирования через мок 

TEST(SimpleCalculatorTest, Add_LogsOperationToHistoryMock) {
    HistoryMock mock;
    SimpleCalculator calc(mock);

    EXPECT_CALL(mock, AddEntry("2 + 2 = 4")).Times(1);
    EXPECT_EQ(calc.Add(2, 2), 4);
}

//Проверка вызова истории отдельно 

TEST(HistoryMockTest, GetLastOperations_ReturnsMockedVector) {
    HistoryMock mock;
    std::vector<std::string> sample = { "A", "B", "C" };
    EXPECT_CALL(mock, GetLastOperations(3)).WillOnce(Return(sample));

    auto result = mock.GetLastOperations(3);
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[1], "B");
}
