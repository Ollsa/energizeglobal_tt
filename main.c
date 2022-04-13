#include <unistd.h>
#include <mxml.h>
#include "test_task.h"
#include "tlv_pull.h"

/*********************************************************************
* @purpose  Add XML-node to tlv pull
*
* @param    tlv_pull_t *a                   @b{(input)} Pull for adding an element
* @param    const unsigned char* keyword    @b{(input)} Keyword of node ("text", "numeric")
* @param    mxml_node_t *node               @b{(input)} xml-node for adding to pull
*
* @returns  TLV_SUCCESS or
* @returns  Error code
*
* @comments
*
* @end
*********************************************************************/
tlv_result_t addXmlNodeToTlvPull(tlv_pull_t* pull, const unsigned char* keyword, mxml_node_t *node)
{
    unsigned int len = strlen(keyword);

    if(strncmp(keyword, XML_KEY_TEXT, len) == 0)
    {
        const unsigned char* textData = mxmlGetText(mxmlGetFirstChild(node), NULL);
        if(textData != NULL)
        {
            return tlvPullAdd(pull, TLV_TEXT, strlen(textData), textData);
        }
    }
    else
    {
        int intData = atoi(mxmlGetText(mxmlGetFirstChild(node), NULL));
        if(strncmp(keyword, XML_KEY_NUMERIC, len) == 0)
        {
            return tlvPullAdd(pull, TLV_NUMERIC, sizeof(int), (const unsigned char*)&intData);
        }
    }
    return TLV_ERROR_UNDEFINDED_ELEMENTS_TYPE;
}


/*********************************************************************
* @purpose  Main function. Convert xml-file to tlv-file
*
* @end
*********************************************************************/
int main(int argc, char* argv[])
{ 
    FILE *fXml, *fTlv;
    unsigned char *xmlFilename = NULL;
    unsigned char *tlvFilename = "output";
    mxml_node_t *node;
    tlv_pull_t tlvPull;
    const char* name;
    unsigned char pullbuff[TLV_BUF_MAX_SIZE] = {0};
    unsigned int l = 0;
    tlv_result_t r = TLV_SUCESS;
    int c;

#ifdef DEBUG
    printf("Hello Energizeglobal!\n");
#endif

    while ((c = getopt(argc, argv, "i:o")) != -1)
    {
        switch (c)
        {
            case 'i':
                    xmlFilename = optarg;
                    break;
            case 'o':
                    tlvFilename = optarg;
                    break;
            default :
                    fprintf(stdout,"Error of command arguments\n");
                    fprintf(stdout,"Use  .\\xml_to_tlv -i [xml_file_name] -o [tlv_file_name]\n");
            break;
        }
    }

    if(xmlFilename == NULL)
    {
        fprintf(stdout,"Error of command arguments\n");
        fprintf(stdout,"Use  .\\xml_to_tlv -i [xml_file_name] -o [tlv_file_name]\n");
        return 0;
    }

    memset(&tlvPull, 0, sizeof(tlvPull));

    fXml = fopen(xmlFilename, "r");

    if(fXml != NULL)
    {
        node = mxmlLoadFile(NULL, fXml, MXML_TEXT_CALLBACK);
        fclose(fXml);
    }
    else
    {
        fprintf(stdout,"Error of readind input xml-file\n");
        return 0;
    }

    node = mxmlFindElement(node, node, XML_START_NODE_NAME, NULL, NULL,
                           MXML_DESCEND);
    while ( node != NULL )
    {
       if ( mxmlGetType(node) == MXML_ELEMENT)
       {
          name =  mxmlGetElement(node);
          if(name)
          {
               if(addXmlNodeToTlvPull(&tlvPull, name, node) == TLV_SUCESS)
               {
        #ifdef DEBUG
             fprintf(stdout," Element = %s\n", mxmlGetElement(node));
             fprintf(stdout,"    Value = %s\n", mxmlGetText(mxmlGetFirstChild(node), NULL));
        #endif
               }
          }
       }

       mxml_node_t* next = mxmlGetNextSibling(node);
       if ( next != NULL )
       {
          node = next;
       }
       else
       {
          next = mxmlGetFirstChild(node);
          if ( next != NULL )
          {
             node = next;
          }
          else
          {
             node = next;
          }
       }
    }

    r = tlvPullSerialize(&tlvPull, pullbuff, &l);
#ifdef DEBUG
    if(r != TLV_SUCESS)
    {
        fprintf(stdout,"Error if serializing tlv-pull. ERROR code: %d\n", r);
    }
    else
    {
        fprintf(stdout,"%d bytes:\n", l);
        for (unsigned int i = 0; i < l; ++i) fprintf(stdout,"0x%02x ", pullbuff[i]);
        fprintf(stdout,"\n");
    }
#endif

    fTlv = fopen(tlvFilename, "w");
    for (unsigned int i = 0; i < l; ++i) fprintf(fTlv, "%02x", pullbuff[i]);
    fclose(fTlv);

    r = tlvPullFree(&tlvPull);
#ifdef DEBUG
    if(r != TLV_SUCESS)
    {
        fprintf(stdout,"Error if deleting tlv-pull. ERROR code: %d\n", r);
    }
    else
    {
        fprintf(stdout,"Tlv-pull is free\n");
    }
#endif
    return 0;
}
