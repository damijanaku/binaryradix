#include <gtest/gtest.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdio>

bool Branje_Stevil(std::vector<unsigned char>& vec, const char s[]);
void Izpis_Stevil(unsigned char* polje, unsigned int velikost);
std::vector<int> countingSort(const std::vector<int>& D);

// Test fixture for the Binary Radix Sort tests
class BinaryRadixTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code that runs before each test
    }
    
    void TearDown() override {
        // Cleanup code that runs after each test
        
        // Clean up any test files that might have been created
        std::remove("test_read.txt");
        std::remove("test_range.txt");
        std::remove("test_whitespace.txt");
        std::remove("out.txt");
    }
};

// Tests for Branje_Stevil function
TEST_F(BinaryRadixTest, BranjeStevil_ValidFile) {
    // Create a test file
    std::ofstream createFile("test_read.txt");
    createFile << "42 128 255";
    createFile.close();
    
    // Test the function
    std::vector<unsigned char> numbers;
    bool result = Branje_Stevil(numbers, "test_read.txt");
    
    // Check results
    EXPECT_TRUE(result);
    ASSERT_EQ(numbers.size(), 3);
    EXPECT_EQ(numbers[0], 42);
    EXPECT_EQ(numbers[1], 128);
    EXPECT_EQ(numbers[2], 255);
}

TEST_F(BinaryRadixTest, BranjeStevil_NonexistentFile) {
    std::vector<unsigned char> numbers;
    bool result = Branje_Stevil(numbers, "nonexistent_file.txt");
    
    EXPECT_FALSE(result);
    EXPECT_TRUE(numbers.empty());
}

TEST_F(BinaryRadixTest, BranjeStevil_RangeFiltering) {
    // Create a test file with some out-of-range values
    std::ofstream createFile("test_range.txt");
    createFile << "42 -10 128 300 255 500";
    createFile.close();
    
    // Test the function
    std::vector<unsigned char> numbers;
    bool result = Branje_Stevil(numbers, "test_range.txt");
    
    // Check results
    EXPECT_TRUE(result);
    ASSERT_EQ(numbers.size(), 3);
    EXPECT_EQ(numbers[0], 42);
    EXPECT_EQ(numbers[1], 128);
    EXPECT_EQ(numbers[2], 255);
}

TEST_F(BinaryRadixTest, BranjeStevil_HandlesWhitespace) {
    // Create a test file with various whitespace
    std::ofstream createFile("test_whitespace.txt");
    createFile << "42\n\t128   \n\n  255";
    createFile.close();
    
    // Test the function
    std::vector<unsigned char> numbers;
    bool result = Branje_Stevil(numbers, "test_whitespace.txt");
    
    // Check results
    EXPECT_TRUE(result);
    ASSERT_EQ(numbers.size(), 3);
    EXPECT_EQ(numbers[0], 42);
    EXPECT_EQ(numbers[1], 128);
    EXPECT_EQ(numbers[2], 255);
}

// Tests for Izpis_Stevil function
TEST_F(BinaryRadixTest, IzpisStevil_WritesToFile) {
    // Prepare test data
    unsigned char testArray[] = {10, 20, 30, 40, 50};
    unsigned int size = 5;
    
    // Call the function
    Izpis_Stevil(testArray, size);
    
    // Verify the file was created and contains the expected values
    std::ifstream readFile("out.txt");
    ASSERT_TRUE(readFile.good());
    
    // Read back the written numbers
    std::vector<int> readNumbers;
    int num;
    while (readFile >> num) {
        readNumbers.push_back(num);
    }
    readFile.close();
    
    // Check results
    ASSERT_EQ(readNumbers.size(), size);
    for (unsigned int i = 0; i < size; ++i) {
        EXPECT_EQ(readNumbers[i], testArray[i]);
    }
}

TEST_F(BinaryRadixTest, IzpisStevil_HandlesEmptyArray) {
    // Test with an empty array
    unsigned char emptyArray[] = {};
    unsigned int size = 0;
    
    // Call the function
    Izpis_Stevil(emptyArray, size);
    
    // Verify the file was created
    std::ifstream readFile("out.txt");
    ASSERT_TRUE(readFile.good());
    
    // Check if the file is empty (or contains only whitespace)
    std::string content;
    std::getline(readFile, content);
    readFile.close();
    
    // After removing whitespace, the content should be empty
    content.erase(std::remove_if(content.begin(), content.end(), ::isspace), content.end());
    EXPECT_TRUE(content.empty());
}

// Tests for countingSort function
TEST_F(BinaryRadixTest, CountingSort_SortsCorrectly) {
    std::vector<int> input = {3, 1, 4, 1, 5, 9, 2, 6};
    std::vector<int> originalInput = input;  // Keep a copy for verification
    
    std::vector<int> indices = countingSort(input);
    
    // Verify that indices are correct by constructing the sorted array
    std::vector<int> sortedByIndices(input.size());
    for (size_t i = 0; i < indices.size(); ++i) {
        sortedByIndices[i] = originalInput[indices[i]];
    }
    
    // Check if the result is sorted
    std::vector<int> expectedOrder = {1, 1, 2, 3, 4, 5, 6, 9};
    ASSERT_EQ(sortedByIndices.size(), expectedOrder.size());
    for (size_t i = 0; i < expectedOrder.size(); ++i) {
        EXPECT_EQ(sortedByIndices[i], expectedOrder[i]);
    }
}

TEST_F(BinaryRadixTest, CountingSort_HandlesNegativeNumbers) {
    std::vector<int> input = {3, -1, 4, -2, 5, -9, 2, 6};
    std::vector<int> originalInput = input;  // Keep a copy for verification
    
    std::vector<int> indices = countingSort(input);
    
    // Verify that indices are correct by constructing the sorted array
    std::vector<int> sortedByIndices(input.size());
    for (size_t i = 0; i < indices.size(); ++i) {
        sortedByIndices[i] = originalInput[indices[i]];
    }
    
    // Check if the result is sorted
    std::vector<int> expectedOrder = {-9, -2, -1, 2, 3, 4, 5, 6};
    ASSERT_EQ(sortedByIndices.size(), expectedOrder.size());
    for (size_t i = 0; i < expectedOrder.size(); ++i) {
        EXPECT_EQ(sortedByIndices[i], expectedOrder[i]);
    }
}

// Integration test for bit-wise radix sort
TEST_F(BinaryRadixTest, BitWiseRadixSort_Integration) {
    
    std::vector<unsigned char> A = {170, 45, 75, 255, 10, 0};

    
    std::vector<unsigned char> expected = {0, 10, 45, 75, 170, 255};
    
    for (int k = 0; k < 8; k++) {
        std::vector<int> D(A.size());
        for (size_t i = 0; i < A.size(); i++) {
            D[i] = (A[i] >> k) & 1;
        }
        
        std::vector<int> sortedIndices = countingSort(D);
        
        std::vector<unsigned char> B(A.size());
        for (size_t i = 0; i < A.size(); i++) {
            B[i] = A[sortedIndices[i]];
        }
        
        A = B;
    }
    
    // Verify the result
    ASSERT_EQ(A.size(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(A[i], expected[i]);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}