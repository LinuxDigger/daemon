#ifndef __XML_MSG__
#define __XML_MSG__

/** @ingroup     */
/*@{*/

#include "xml_base.h"
/**
* @brief �洢xml��ʽ�ַ���buffer���ֵ
*/
#define MAX_XML_LEN	(100*1024)
/**
* @brief �洢xml��ʽͨ����Ϣbuffer�����ֵ
*/
#define ROOM_INFO_XML_LEN	256
/**
* @brief �洢��֤��buffer��С
*/
#define IP_ADDR_LEN	16
#define PASS_KEY_LEN	128
#define ROOM_ID_MAX	10
#define REQ_CODE_TCP_SIZE  6
#define REQ_VALUE_KEY  64

/*###############################################*/

/**
* @brief �жϵ�ǰ���ڵ��Ƿ�����Ӧ��Ϣ�ĸ��ڵ�
* @param  [IN] proot ��ǰ���ڵ�
* @exception  none
* @return  �Ƿ���1 ���񷵻�0
* @note  none
* @remarks  none
*/
int is_resp_msg(xmlNodePtr  proot);

/**
* @brief ��ȡ��Ӧ��Ϣ������ڵ�
* @param  [OUT] *pnode ��Ӧ��Ϣ������ڵ�
* @param  [IN] proot ��Ӧ��Ϣ������ڵ�dom�����ڵ�
* @exception  none
* @return  �ɹ�������Ӧ��Ϣ������ڵ㣬ʧ�ܷ���NULL
* @note  none
* @remarks  none
* @code
*	#include "xml_msg_management.h"
*	#define MSGHEAD "<?xml version=\"1.0\" encoding=\"UTF-8\"?><ResponseMsg><MsgHead><ReturnCode>1</ReturnCode><ReturnCode>2</ReturnCode><ReturnCode>3</ReturnCode><ReturnCode>4</ReturnCode></MsgHead><MsgBody/></ResponseMsg>"
*	char value[8] = {0};
*	xmlNodePtr pnode;
*	parse_xml_t parse_xml;
*	init_dom_tree(&parse_xml, MSGHEAD);
*	get_resp_return_code_node(&pnode, parse_xml.proot);
*	get_current_node_value(value,value_len, parse_xml.pdoc, pnode);
*	printf("msg_head:[%s]\n", value);
*	release_dom_tree(parse_xml.pdoc);
* @endcode
*/
xmlNodePtr get_resp_return_code_node(xmlNodePtr *pnode, xmlNodePtr proot);

/**
* @brief �жϵ�ǰ���ڵ��Ƿ���������Ϣ�ĸ��ڵ�
* @param  [IN] proot ��ǰ���ڵ�
* @exception  none
* @return  �Ƿ���1 ���񷵻�0
* @note  none
* @remarks  none
*/
int is_req_msg(xmlNodePtr  proot);

/**
* @brief ��ȡ������Ϣ��ڵ�
* @param  [OUT] *pnode ������Ϣ��ڵ�
* @param  [IN] proot ������Ϣ��ڵ�����dom���ĸ��ڵ�
* @exception  none
* @return  �ɹ�������Ϣ��ڵ㣬ʧ�ܷ���NULL
* @note  none
* @remarks  none
* @see  get_resp_return_code_node
*/
xmlNodePtr get_req_msg_code_node(xmlNodePtr *pnode, xmlNodePtr proot);

/**
* @brief ��ȡ������Ϣ��֤��ڵ�
* @param  [OUT] *pnode ������Ϣ��֤��ڵ�
* @param  [IN] proot ������Ϣ��֤��ڵ�����dom���ĸ��ڵ�
* @exception  none
* @return  �ɹ�������Ϣ��֤��ڵ㣬ʧ�ܷ���NULL
* @note  none
* @remarks  none
* @see  get_resp_return_code_node
*/
xmlNodePtr get_req_pass_key_node(xmlNodePtr *pnode, xmlNodePtr proot);


/*@}*/
#endif //__XML_MSG__

