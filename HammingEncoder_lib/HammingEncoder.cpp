#include "HammingEncoder.h"


bool CheckInputDataOnCorrect(const std::vector<uint8_t> &input_data)
{
	int counter = 0;
	for (int i = 0; i < input_data.size(); i++)
	{
		if (input_data.at(i) == 0 || input_data.at(i) == 1)
			continue;
		else
			counter++;
	}

	if (counter == 0)
		return true;
	else
		return false;
}


std::vector<uint8_t> Hamming74Encode::Encode(std::vector<uint8_t> &input_data)
{
	if (CheckInputDataOnCorrect(input_data) == false)
	{
		throw "Error: invalid input data.";
	}
	else
	{
		AddingZeros(input_data);

		int num_of_redundant_symbols = ((input_data.size() / 4) * 3);
		std::vector<uint8_t> output_data(input_data.size() + num_of_redundant_symbols);

		int j = 0; //It is necessary that at each iteration of the i-loop the j variable is not reset.
		for (int i = 0; i < output_data.size(); i += kNumOfOutputElements)
		{
			for (j; j < input_data.size(); j++)
			{
				output_data.at(i) = input_data.at(j);
				output_data.at(i + 1) = input_data.at(j + 1);
				output_data.at(i + 2) = input_data.at(j + 2);
				output_data.at(i + 3) = input_data.at(j + 3);
				output_data.at(i + 4) = input_data.at(j) ^ input_data.at(j + 2) ^ input_data.at(j + 3);
				output_data.at(i + 5) = input_data.at(j) ^ input_data.at(j + 1) ^ input_data.at(j + 2);
				output_data.at(i + 6) = input_data.at(j + 1) ^ input_data.at(j + 2) ^ input_data.at(j + 3);
				j += kNumOfInputElements;
				break;
			}
		}

		return output_data;
	}
}

void Hamming74Encode::AddingZeros(std::vector<uint8_t> &input_data)
{
	std::uint8_t zero = 0;

	if (std::fmod(input_data.size(), kNumOfInputElements) != 0)
	{
		std::cout << "Warning: the number of entered symbols is not divisible by 4. Input data will be padded with zeros." << std::endl;

		for (int i = 0; i < std::fmod(input_data.size(), kNumOfInputElements); i++)
		{
			input_data.push_back(zero);
		}
	}
}