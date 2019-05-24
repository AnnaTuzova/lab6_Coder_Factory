#include "CoderFactory.h"

std::vector<uint8_t> TurboEncode::Encode(std::vector<uint8_t> &input_data)
{
	if (CheckInputDataOnCorrect(input_data) == false)
	{
		throw "Error: invalid input data.";
	}
	else
	{
		std::vector<uint8_t> first_constituent_encoder_output = ConstituentEncoder(input_data);

		std::vector<uint8_t> interleaver_output = Interleaver(input_data);
		std::vector<uint8_t> second_constituent_encoder_output = ConstituentEncoder(interleaver_output);

		for (int i = 0; i < second_constituent_encoder_output.size(); i++)
			second_constituent_encoder_output.erase(second_constituent_encoder_output.begin() + i);

		size_t length_of_turbo_encoder_output = first_constituent_encoder_output.size() + second_constituent_encoder_output.size();
		std::vector<uint8_t> turbo_encoder_output = first_constituent_encoder_output;

		int j = 0;
		for (int i = 0; i < length_of_turbo_encoder_output; i += 3)
		{
			for (j; j < second_constituent_encoder_output.size(); j++)
			{
				turbo_encoder_output.insert(turbo_encoder_output.begin() + i + 2, second_constituent_encoder_output.at(j));
				j++;
				break;
			}
		}

		return turbo_encoder_output;
	}
}

std::vector<uint8_t> TurboEncode::ConstituentEncoder(std::vector<uint8_t> &input_data) const
{
	std::vector<uint8_t> state_of_memory_cells{ 0, 0 };
	std::vector<uint8_t> constituent_encoder_output(2 * input_data.size());

	int j = 0;
	for (int i = 0; i < input_data.size(); i++)
	{
		for (j; j < constituent_encoder_output.size(); j++)
		{
			if (state_of_memory_cells.at(0) == 0 && state_of_memory_cells.at(1) == 0 && input_data.at(i) == 0)
			{
				state_of_memory_cells.at(0) = 0;
				state_of_memory_cells.at(1) = 0;
				constituent_encoder_output.at(j) = 0;
				constituent_encoder_output.at(j + 1) = 0;
			}
			else if (state_of_memory_cells.at(0) == 0 && state_of_memory_cells.at(1) == 0 && input_data.at(i) == 1)
			{
				state_of_memory_cells.at(0) = 1;
				state_of_memory_cells.at(1) = 0;
				constituent_encoder_output.at(j) = 1;
				constituent_encoder_output.at(j + 1) = 1;
			}
			else if (state_of_memory_cells.at(0) == 1 && state_of_memory_cells.at(1) == 0 && input_data.at(i) == 0)
			{
				state_of_memory_cells.at(0) = 1;
				state_of_memory_cells.at(1) = 1;
				constituent_encoder_output.at(j) = 0;
				constituent_encoder_output.at(j + 1) = 1;
			}
			else if (state_of_memory_cells.at(0) == 1 && state_of_memory_cells.at(1) == 0 && input_data.at(i) == 1)
			{
				state_of_memory_cells.at(0) = 0;
				state_of_memory_cells.at(1) = 1;
				constituent_encoder_output.at(j) = 1;
				constituent_encoder_output.at(j + 1) = 0;
			}
			else if (state_of_memory_cells.at(0) == 0 && state_of_memory_cells.at(1) == 1 && input_data.at(i) == 0)
			{
				state_of_memory_cells.at(0) = 1;
				state_of_memory_cells.at(1) = 0;
				constituent_encoder_output.at(j) = 0;
				constituent_encoder_output.at(j + 1) = 0;
			}
			else if (state_of_memory_cells.at(0) == 0 && state_of_memory_cells.at(1) == 1 && input_data.at(i) == 1)
			{
				state_of_memory_cells.at(0) = 0;
				state_of_memory_cells.at(1) = 0;
				constituent_encoder_output.at(j) = 1;
				constituent_encoder_output.at(j + 1) = 1;
			}
			else if (state_of_memory_cells.at(0) == 1 && state_of_memory_cells.at(1) == 1 && input_data.at(i) == 0)
			{
				state_of_memory_cells.at(0) = 0;
				state_of_memory_cells.at(1) = 1;
				constituent_encoder_output.at(j) = 0;
				constituent_encoder_output.at(j + 1) = 1;
			}
			else if (state_of_memory_cells.at(0) == 1 && state_of_memory_cells.at(1) == 1 && input_data.at(i) == 1)
			{
				state_of_memory_cells.at(0) = 1;
				state_of_memory_cells.at(1) = 1;
				constituent_encoder_output.at(j) = 1;
				constituent_encoder_output.at(j + 1) = 0;
			}

			j += kNumOfOutputElements;
			break;
		}
	}

	return constituent_encoder_output;
}

std::vector<uint8_t> TurboEncode::Interleaver(std::vector<uint8_t> &input_data) const
{
	const int length = input_data.size();
	const int step_size = 3;
	const int offset = 0;

	std::vector<uint8_t> index(length);
	std::vector<uint8_t> permutation(length);

	std::vector<uint8_t> interleaver_output(length);
	
	for (int i = 0; i < length; i++)
		index.at(i) = i;

	for (int i = 0; i < length; i++)
		permutation.at(i) = std::fmod((step_size * index.at(i) + offset), length);

	for (int i = 0; i < length; i++)
		interleaver_output.at(i) = input_data.at(permutation.at(i));

	return interleaver_output;
}
