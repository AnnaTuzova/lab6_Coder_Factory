#pragma once 

#include <iostream>
#include <vector>
#include <cstdint>
#include <memory>

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

class TurboEncode : public IEncode
{
private:
	const int kNumOfInputElements = 1;
	const int kNumOfOutputElements = 2;

	std::vector<uint8_t> ConstituentEncoder(std::vector<uint8_t> &input_data) const;
	std::vector<uint8_t> Interleaver(std::vector<uint8_t> &input_data) const;
	
public:
	~TurboEncode() {}

	std::vector<uint8_t> Encode(std::vector<uint8_t> &input_data) override;
};

class CoderFactory
{
public:
	virtual std::shared_ptr<IEncode> CreateCoder() = 0;
	~CoderFactory() {}
};

class Hamming74EncodeFactory : public CoderFactory
{
public:
	std::shared_ptr<IEncode> CreateCoder()
	{
		return std::make_shared<Hamming74Encode>();
	}
};

class TurboEncodeFactory : public CoderFactory
{
public:
	std::shared_ptr<IEncode> CreateCoder()
	{
		return std::make_shared<TurboEncode>();
	}
};