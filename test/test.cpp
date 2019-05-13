#include "../CoderFactory_lib/CoderFactory.h"
#include <windows.h>
#include <gtest/gtest.h>

TEST(TestCoderFactory, ExceptionTest)
{
	std::vector<uint8_t> input_data{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0 };

	TurboEncodeFactory* turbo_encode_factory = new TurboEncodeFactory;
	IEncode *turbo_encode_object = turbo_encode_factory->CreateCoder();

	ASSERT_THROW(turbo_encode_object->Encode(input_data), const char*);
	delete turbo_encode_factory;
}

TEST(TestCoderFactory, TurboEncodingTest)
{
	std::vector<uint8_t> input_data{ 1,0,0,0,0,1,0,1,0,1,0,1,1,0,1,1 };
	std::vector<uint8_t> expected_output_data{ 1,1,1,0,1,1,0,1,1,0,0,1,0,1,1,1,0,0,0,1,0,1,1,0,0,0,0,
												1,1,0,0,1,1,1,0,0,1,0,0,0,1,1,1,1,1,1,1,1 };
	
	TurboEncodeFactory* turbo_encode_factory = new TurboEncodeFactory;
	IEncode *turbo_encode_object = turbo_encode_factory->CreateCoder();

	std::vector<uint8_t> actual_output_data = turbo_encode_object->Encode(input_data);
	ASSERT_EQ(actual_output_data, expected_output_data);

	delete turbo_encode_factory;
}

TEST(TestCoderFactory, EmptyInputTest)
{
	std::vector<uint8_t> input_data;

	TurboEncodeFactory* turbo_encode_factory = new TurboEncodeFactory;
	IEncode *turbo_encode_object = turbo_encode_factory->CreateCoder();

	std::vector<uint8_t> actual_output_data = turbo_encode_object->Encode(input_data);

	ASSERT_TRUE(actual_output_data.size() == 0);
	delete turbo_encode_factory;
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
