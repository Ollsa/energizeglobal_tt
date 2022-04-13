#ifndef TLV_PULL_H
#define TLV_PULL_H

#include <stdint.h>

#define TLV_PULL_MAX_ELEMENTS_COUNT 50
#define TLV_PULL_MAX_ELEMENT_SIZE  255

typedef struct tlv
{
    int8_t type;
    uint8_t * data;
    int16_t size;
}tlv_t;

typedef struct tlv_pull
{
    tlv_t object[TLV_PULL_MAX_ELEMENTS_COUNT];
    uint8_t count;
}tlv_pull_t;

typedef enum tlv_result {

    TLV_SUCESS = 0,
    TLV_ERROR_NULL_ELEMENT = -1, //Error of adding null-element to pull
    TLV_ERROR_FULL_PULL = -2, // Error of adding an element to pull. The pull is full
    TLV_ERROR_NULL_PULL = -3,
    TLV_ERROR_SIZE_OF_ELEMENT = -4,
    TLV_ERROR_UNDEFINDED_ELEMENTS_TYPE = -5,
} tlv_result_t;

tlv_result_t tlvPullAdd(tlv_pull_t *a, unsigned char type, int16_t size, const unsigned char *bytes);
tlv_result_t tlvPullSerialize(tlv_pull_t *a, unsigned char *dest, int32_t *count);
tlv_result_t tlvPullFree(tlv_pull_t *a);

#endif //TLV_PULL_H
