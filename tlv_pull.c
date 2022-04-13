#include "tlv_pull.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*********************************************************************
* @purpose  Add element to tlv pull
*
* @param    tlv_pull_t *a               @b{(input)} Pull for adding an element
* @param    unsigned char type          @b{(input)} Code of type of elements
* @param    int16_t size                @b{(input)} Size of element in bytes
* @param    const unsigned char *bytes  @b{(input)} Data of element
*
* @returns  TLV_SUCCESS or
* @returns  Error code
*
* @comments
*
* @end
*********************************************************************/
tlv_result_t tlvPullAdd(tlv_pull_t *a, unsigned char type, int16_t size, const unsigned char *bytes)
{
    if(a == NULL || bytes == NULL)
        return TLV_ERROR_NULL_ELEMENT;

    if(a->count >= TLV_PULL_MAX_ELEMENTS_COUNT)
        return TLV_ERROR_FULL_PULL;

    if(size >= TLV_PULL_MAX_ELEMENT_SIZE)
        return TLV_ERROR_SIZE_OF_ELEMENT;

    int i = a->count;
    a->object[i].type = type;
    a->object[i].size = size;
    a->object[i].data = malloc(size);
    memcpy(a->object[i].data, bytes, size);

    a->count++;

    return TLV_SUCESS;
}

/*********************************************************************
* @purpose  Free the tlv pull
*
* @param    tlv_pull_t *a               @b{(input)} Pull for free
*
* @returns  TLV_SUCCESS or
* @returns  Error code
*
* @comments
*
* @end
*********************************************************************/
tlv_result_t tlvPullFree(tlv_pull_t *a)
{
    if(a == NULL)
        return TLV_ERROR_NULL_PULL;

    for(int i =0; i < a->count; i++)
    {
        free(a->object[i].data);

        a->object[i].data = NULL;
    }

    return TLV_SUCESS;
}

/*********************************************************************
* @purpose  Serialize the tlv pull to bytes array
*
* @param    tlv_pull_t *a               @b{(input)} Tlv pull
* @param    unsigned char *dest         @b{(output)} Buffer for serialized data
* @param    int32_t* count              @b{(output)} Size of serialized data in bytes
*
* @returns  TLV_SUCCESS or
* @returns  Error code
*
* @comments
*
* @end
*********************************************************************/
tlv_result_t tlvPullSerialize(tlv_pull_t *a, unsigned char *dest, int32_t* count)
{
    if(a == NULL || dest == NULL)
        return TLV_ERROR_NULL_PULL;

    int32_t counter = 0;

    for(int i = 0; i < a->count; i++)
    {
        dest[counter] = a->object[i].type;
        counter++;

        memcpy(&dest[counter], &a->object[i].size, 2);
        counter += 2;

        memcpy(&dest[counter], a->object[i].data, a->object[i].size);
        counter += a->object[i].size;
    }

    *count = counter;
    return TLV_SUCESS;
}
