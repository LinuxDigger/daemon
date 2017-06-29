#ifndef _BMC_DAEMON_H_
#define _BMC_DAEMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <ctype.h>
#include <errno.h>
#include <sys/param.h>
#include <sys/procfs.h>
#include <sys/resource.h>
#include "xml_base.h"
#include <assert.h>
#include "bmc_net_protocol_sdk.h"
#include "bmc_debug.h"
#include <fcntl.h> 

#define XML  "/tmp/daemon.xml"

#define VERSION  "Bmc_Daemon_v1.0"
#define CPUNUM   2
#define READ_BUF_SIZE 1024
#define PAGE_SHIFT 12
#define bytetok(x)	(((x) + 512) >> 10)
#define pagetok(x)	((x) << (PAGE_SHIFT - 10))
#define PROCBUFFERLEN   4*1024
#define MAXSAMEPROC   10

#define RED				"\033[0;32;31m"
#define NONE				"\033[m"

typedef struct _list_head
{
   struct _list_head 	*next;
   struct _list_head	*prev;

}list_head;

typedef struct _DevAtt
{
	int8_ procname[200];   //������
	int8_ 	  param[200];	//���̲���
	uint32_  max_mem;	    //����ڴ�
	uint32_  max_cpu;      //���cpu
	uint32_  active;       //�Ƿ񼤻�
	uint32_  guardian;     //�Ƿ��ػ�
	uint32_  time;         //����ʱ���
	int8_ 	  run[20];      //���в��� ������

	list_head stlist;
	uint32_ livestate;		//���״̬
	uint32_ rtcputime[MAXSAMEPROC];       //ʵʱ�߳�cpuʱ��
	uint32_ rtsyscputime[MAXSAMEPROC];	   //ʵʱϵͳcpuʱ��
	uint32_ rtmem[MAXSAMEPROC];           //ʵʱ�ڴ�
	uint32_ rtpid[MAXSAMEPROC];		   //�߳�ID
	uint32_ rtprent[MAXSAMEPROC];         //�߳�cpu�ٷֱ�
	uint32_ rttotalcpu[MAXSAMEPROC];	//cpu�ܰٷֱ��ۼ�
	uint32_ rttotalmem[MAXSAMEPROC];	//�ڴ��ۼ�
	int32_t  rttotaltimes[MAXSAMEPROC];	//ͳ�ƴ���
	uint32_ samenum;
}NodeAtt;

typedef struct _system_info
{

    uint32_    TotalMem;
    uint32_    TotalCpu;
}system_info;

typedef struct _progress_state
{

	int8_     name[20];
    uint32_   Mem;
    uint32_   CpuTime;
	uint32_   State;
}ProState;

typedef struct _daemon_hand
{
	parse_xml_t *px;
	list_head *phead;
	pthread_mutex_t daemonlock;
}DaemonHand;

typedef struct _daemon_config
{
	int8_ name[200];
	int8_ param[20];
	int8_ run[200];
	int8_ active[20];
	int8_ guardian[20];
	int8_ maxcpu[20];
	int8_ maxmem[20];
	int8_ time[20];
}Daemon_config;

/* ��ʼ��˫������ */
#define list_init(head) do			\
{						\
	(head)->next = (head)->prev = (head);	\
} while(0)

/* ��ָ��Ԫ��(where)֮�������Ԫ��(item) */
#define list_add(item, towhere) do	\
{					\
	(item)->next = (towhere)->next;	\
	(item)->prev = (towhere);	\
	(towhere)->next = (item);	\
	(item)->next->prev = (item);	\
} while(0)

/* ��ָ��Ԫ��(where)֮ǰ������Ԫ��(item) */
#define list_add_before(item, towhere)  \
	list_add(item,(towhere)->prev)

/* ɾ��ĳ��Ԫ�� */
#define list_remove(item) do			\
{						\
	(item)->prev->next = (item)->next;	\
	(item)->next->prev = (item)->prev;	\
} while(0)

/* �����������������Ԫ�� */
#define list_for_each_item(item, head)\
	for ((item) = (head)->next; (item) != (head); (item) = (item)->next)

/* �����������������Ԫ�� */
#define list_for_each_item_rev(item, head) \
	for ((item) = (head)->prev; (item) != (head); (item) = (item)->prev)

/* ���ݱ��ڵ�(item)��ȡ�ڵ����ڽṹ��(type)�ĵ�ַ */
/* �ڵ�item��ַ(member�ĵ�ַ) - ������Ԫ��member�ڽṹ���е�ƫ�� */
#define list_entry(item, type, member) \
	((type *)((char *)item - (char *)(&((type *)0)->member)))

/* �ж������Ƿ�Ϊ�� */
#define list_is_empty(head)	\
	((head)->next == (head))

/* ��ȡָ��λ����һԪ�� */
#define list_prev_item(item)\
	((head)->prev)
	
#endif
