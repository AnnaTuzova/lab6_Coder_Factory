#include "../CoderFactory_lib/CoderFactory.h"
#include <windows.h>
#include <gtest/gtest.h>

TEST(TestCoderFactory, ExceptionTest)
{
	std::vector<uint8_t> input_data{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0 };

	std::shared_ptr<TurboEncodeFactory> turbo_encode_factory = std::make_shared<TurboEncodeFactory>();
	std::shared_ptr<IEncode> turbo_encode_object = turbo_encode_factory->CreateCoder();

	ASSERT_THROW(turbo_encode_object->Encode(input_data), const char*);
}

TEST(TestCoderFactory, TurboEncodingTest)
{
	std::vector<uint8_t> input_data{ 1,0,0,0,0,1,0,1,0,1,0,1,1,0,1,1 };
	std::vector<uint8_t> expected_output_data{ 1,1,1,0,1,1,0,1,1,0,0,1,0,1,1,1,0,0,0,1,0,1,1,0,0,0,0,
												1,1,0,0,1,1,1,0,0,1,0,0,0,1,1,1,1,1,1,1,1 };
	
	std::shared_ptr<TurboEncodeFactory> turbo_encode_factory = std::make_shared<TurboEncodeFactory>();
	std::shared_ptr<IEncode> turbo_encode_object = turbo_encode_factory->CreateCoder();

	std::vector<uint8_t> actual_output_data = turbo_encode_object->Encode(input_data);
	ASSERT_EQ(actual_output_data, expected_output_data);
}

TEST(TestCoderFactory, EmptyInputTest)
{
	std::vector<uint8_t> input_data;

	std::shared_ptr<TurboEncodeFactory> turbo_encode_factory = std::make_shared<TurboEncodeFactory>();
	std::shared_ptr<IEncode> turbo_encode_object = turbo_encode_factory->CreateCoder();

	std::vector<uint8_t> actual_output_data = turbo_encode_object->Encode(input_data);

	ASSERT_TRUE(actual_output_data.size() == 0);
}

TEST(TestCoderFactory, FactoryTest)
{
	std::shared_ptr<TurboEncodeFactory> turbo_encode_factory = std::make_shared<TurboEncodeFactory>();
	std::shared_ptr<IEncode> turbo_encode_object = turbo_encode_factory->CreateCoder();

	std::shared_ptr<Hamming74EncodeFactory> hamming_encode_factory = std::make_shared<Hamming74EncodeFactory>();
	std::shared_ptr<IEncode> hamming_encode_object = hamming_encode_factory->CreateCoder();

	ASSERT_TRUE(turbo_encode_object != nullptr);
	ASSERT_TRUE(hamming_encode_object != nullptr);
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
