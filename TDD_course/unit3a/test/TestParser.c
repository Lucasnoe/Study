#include "unity.h"
#include "Parser.h"
#include "MK20DX256.h"

extern PARSER_STATE_T state;

void test_Parser_AddChar_should_StartLookingForCMDOnLeftBracket(void)
{
    state = PARSER_LOOKING_FOR_START;

    TEST_ASSERT_NULL(Parser_AddChar('['));

    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_CMD,state);
}

void test_Parser_AddChar_should_RejectNonBracketCharactersWhileSeekingStart(void)
{
    state = PARSER_LOOKING_FOR_START;
    TEST_ASSERT_NULL(Parser_AddChar('|'));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START,state);
    TEST_ASSERT_NULL(Parser_AddChar('g'));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START,state);
    TEST_ASSERT_NULL(Parser_AddChar('*'));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START,state);
}

void test_Parser_AddChar_should_AcceptAValidCommandCharacter(void)
{
    state = PARSER_LOOKING_FOR_CMD;
    TEST_ASSERT_NULL(Parser_AddChar('A'));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_LEN,state);

    state = PARSER_LOOKING_FOR_CMD;
    TEST_ASSERT_NULL(Parser_AddChar('D'));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_LEN,state);

    state = PARSER_LOOKING_FOR_CMD;
    TEST_ASSERT_NULL(Parser_AddChar('Z'));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_LEN,state);
    
}

void test_Parser_AddChar_should_RejectAInvalidCommandCharacter(void)
{
    state = PARSER_LOOKING_FOR_CMD;
    TEST_ASSERT_NULL(Parser_AddChar('@'));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START,state);

    state = PARSER_LOOKING_FOR_CMD;
    TEST_ASSERT_NULL(Parser_AddChar('\\'));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START,state);

    state = PARSER_LOOKING_FOR_CMD;
    TEST_ASSERT_NULL(Parser_AddChar('z'));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START,state);
    
}

void test_Parser_AddChar_should_AcceptALengthOfZero(void)
{
    state = PARSER_LOOKING_FOR_LEN;
    TEST_ASSERT_NULL(Parser_AddChar('0'));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_END, state);
}

void test_Parser_AddChar_should_RejectInvalidLengths(void)
{
    state = PARSER_LOOKING_FOR_LEN;
    TEST_ASSERT_NULL(Parser_AddChar(':'));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START, state);
}



void insert_valid_minimal_packet(char cmd, const char* full)
{
    TEST_ASSERT_NULL(Parser_AddChar('['));
    TEST_ASSERT_NULL(Parser_AddChar(cmd));
    TEST_ASSERT_NULL(Parser_AddChar('0'));
    TEST_ASSERT_EQUAL_STRING(full, Parser_AddChar(']'));
}

void test_Parser_AddChar_should_HandleValidPacketWithNoData(void)
{
    insert_valid_minimal_packet('A', "[A0]");
    insert_valid_minimal_packet('B', "[B0]");
    insert_valid_minimal_packet('Z', "[Z0]");
}

void test_Parser_AddChar_should_IgnoreBadStartCharacters(void)
{
    TEST_ASSERT_NULL(Parser_AddChar('?'));
    insert_valid_minimal_packet('D',"[D0]");

    TEST_ASSERT_NULL(Parser_AddChar('a'));
    TEST_ASSERT_NULL(Parser_AddChar(']'));
    insert_valid_minimal_packet('W',"[W0]");

}

void test_Parser_AddChar_should_IgnoreBadCommandCharacters(void)
{
    TEST_ASSERT_NULL(Parser_AddChar('['));
    TEST_ASSERT_NULL(Parser_AddChar('a'));
    insert_valid_minimal_packet('P',"[P0]");

    TEST_ASSERT_NULL(Parser_AddChar('['));
    TEST_ASSERT_NULL(Parser_AddChar('z'));
    TEST_ASSERT_NULL(Parser_AddChar('0'));
    TEST_ASSERT_NULL(Parser_AddChar(']'));
    insert_valid_minimal_packet('S', "[S0]");
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_Parser_AddChar_should_StartLookingForCMDOnLeftBracket);
    RUN_TEST(test_Parser_AddChar_should_RejectNonBracketCharactersWhileSeekingStart);
    RUN_TEST(test_Parser_AddChar_should_AcceptAValidCommandCharacter);
    RUN_TEST(test_Parser_AddChar_should_RejectAInvalidCommandCharacter);
    RUN_TEST(test_Parser_AddChar_should_AcceptALengthOfZero);
    RUN_TEST(test_Parser_AddChar_should_RejectInvalidLengths);
    RUN_TEST(test_Parser_AddChar_should_HandleValidPacketWithNoData);
    RUN_TEST(test_Parser_AddChar_should_IgnoreBadStartCharacters);
    RUN_TEST(test_Parser_AddChar_should_IgnoreBadCommandCharacters);
    return UNITY_END();
}
