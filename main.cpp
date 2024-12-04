#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;

pair<unordered_map<int, int>, int> getFileContents(string path) {
    ifstream file(path);
    if (!file.is_open()) {
        throw runtime_error("Unable to open file");
    }

    unordered_map<int, int> numbersMap; // To store numbers and indices
    int target;
    string line;

    int lineNumber = 0;
    while (std::getline(file, line)) {
        lineNumber++;
        if (lineNumber == 1) {
            target = stoi(line);
        }else if (lineNumber >= 3) {
            int number = stoi(line);

            // To get the indice of the number, not considering first 2 lines and starting from 0
            numbersMap[number] = lineNumber-3;
        }
    }
    file.close();

    pair<unordered_map<int, int>, int> result;
    result.first = numbersMap;
    result.second = target;

    return result;
}

// Asked chatGPT how to return the pointer in a proper way.
pair<pair<int, int>, pair<int, int>>* twoSum(unordered_map<int, int> numbers, int target) {

    //Loop through all the numbers, check if inverse of it (in respect to target) is contained in the map
    for (const auto &num : numbers) {
        int resultingNumber = target- num.first;
        auto resultingPair = numbers.find(resultingNumber); // Find the required number
        if (resultingPair != numbers.end() && resultingPair->second != num.second) { // Check for different nums
            return new pair<pair<int, int>, pair<int, int>>(
            make_pair(num.first, resultingNumber),
            make_pair(num.second, resultingPair->second));
        }

    }
    return nullptr;
}

int main() {
    pair<unordered_map<int, int>, int> inputData = getFileContents("two_sum_target_n_data.txt");
    unordered_map<int, int> targetData = inputData.first;
    int target = inputData.second;

    pair<pair<int, int>, pair<int, int>>* result = twoSum(targetData, target);
    if (result) {
        cout << "Numbers (" << result->first.first << ", " << result->first.second << "), "
             << " Indices (" << result->second.first << ", " << result->second.second << ")" << endl;
        delete result; // Free memory to avoid leaks
    } else {
        cout << "No such numbers" << endl;
    }
    return 0;
}