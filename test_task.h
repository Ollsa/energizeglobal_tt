#ifndef TEST_TASK_H
#define TEST_TASK_H

#define DEBUG

#define XML_FILENAME        "test.xml"
#define XML_START_NODE_NAME "start"
#define XML_KEY_TEXT        "text"
#define XML_KEY_NUMERIC     "numeric"

#define TLV_FILENAME        "s1.txt"
#define TLV_BUF_MAX_SIZE    255

typedef enum xml_keyword
{
    TLV_TEXT = 0x10,
    TLV_NUMERIC = 0x20
} xml_keyword_t;

#endif //TEST_TASK_H
