#include <iostream>
#include <string>
#include <stdlib.h>

int* convertStrToIntArr(std::string str)
{
	int* arr = new int[10];
	for (int i = 0; i < 10; i++) arr[i] = 0;
	int j = 0, i, sum = 0;
	for (i = 0; str[i] != '\0'; i++) {
		if (str[i] == ',') {
			j++;
		}
		else if (str[i] >= 48 && str[i] <= 57) {
			arr[j] = arr[j] * 10 + (str[i] - 48);
		}
	}
	
	return arr;
	// Source: https://www.geeksforgeeks.org/convert-a-string-to-integer-array-in-c-c/
}

std::string max(int arr[10])
{
	int max = 0;
	int person = 0;

	for (int i = 0; i < 10; i++) {
		if (arr[i] > max) {
			max = arr[i];
			person = i + 1;
		}
	}

	std::string result = "Person " + std::to_string(person) + ": ate the most pancakes (" + std::to_string(max) + " pancakes)";

	return result;
}

std::string min(int arr[10])
{
	int min = arr[0];
	int person = 1;

	for (int i = 0; i < 10; i++) {
		if (arr[i] < min) {
			min = arr[i];
			person = i + 1;
		}
	}

	std::string result = "Person " + std::to_string(person) + ": ate the least pancakes (" + std::to_string(min) + " pancakes)";
	return result;
}

int main()
{
	std::string pancakesStr;
	int* pancakes;
	std::cout << "Please enter the numbers of pancakes eaten by 10 people (separated by commas, no spaces): ";
	std::cin >> pancakesStr;
	pancakes = convertStrToIntArr(pancakesStr);
	for (int i = 0; i < 10; i++) {
		std::cout << "Person " << i + 1 << ": ate " << pancakes[i] << " pancakes" << std::endl;
	}

	std::cout << max(pancakes) << std::endl;
	std::cout << min(pancakes) << std::endl;

	delete pancakes;

	system("pause");
	return 0;
}
