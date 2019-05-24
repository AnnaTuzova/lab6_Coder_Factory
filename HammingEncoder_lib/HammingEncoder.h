#pragma once 

#include <iostream>
#include <vector>
#include <cstdint>

bool CheckInputDataOnCorrect(const std::vector<uint8_t> &input_data);

class IEncode 
{
public:
	~IEncode() {}

	virtual std::vector<uint8_t> Encode(std::vector<uint8_t> &input_data) = 0;
};

class Hamming74Encode : public IEncode
{
private:
	const int kNumOfInputElements = 4;
	const int kNumOfOutputElements = 7;

	void AddingZeros(std::vector<uint8_t> &input_data);

public:
	~Hamming74Encode() {}

	std::vector<uint8_t> Encode(std::vector<uint8_t> &input_data) override;
};