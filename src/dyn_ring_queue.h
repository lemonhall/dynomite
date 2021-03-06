/*
 * Dynomite - A thin, distributed replication layer for multi non-distributed storages.
 * Copyright (C) 2014 Netflix, Inc.
 */


#include "dyn_gossip.h"


#ifndef _DYN_RING_QUEUE_
#define _DYN_RING_QUEUE_


#define C2G_InQ_SIZE     256
#define C2G_OutQ_SIZE    256

#define C2S_InQ_SIZE     256
#define C2S_OutQ_SIZE    256

struct node;

typedef rstatus_t (*callback_t)(void *msg);
typedef void (*data_func_t)(void *);

volatile struct
{
     long     m_getIdx;
     long     m_putIdx;
     void*    m_entry[C2G_InQ_SIZE];
} C2G_InQ;



volatile struct
{
     long     m_getIdx;
     long     m_putIdx;
     void*    m_entry[C2G_OutQ_SIZE];
} C2G_OutQ;



struct ring_msg {
	callback_t           cb;
    uint8_t              *data;             /* place holder for a msg */
    uint32_t             capacity;          /* max capacity */
    uint32_t             len;               /* # of useful bytes in data (len =< capacity) */
    struct array         nodes;
	struct server_pool   *sp;

};



volatile struct
{
     long     m_getIdx;
     long     m_putIdx;
     void*    m_entry[C2S_InQ_SIZE];
} C2S_InQ;



volatile struct
{
     long     m_getIdx;
     long     m_putIdx;
     void*    m_entry[C2S_OutQ_SIZE];
} C2S_OutQ;


struct stat_msg {
	void*         cb;
	void*         post_cb;
	void*         data;
	stats_cmd_t   cmd;
};




struct ring_msg *create_ring_msg(void);
struct ring_msg *create_ring_msg_with_data(int capacity);
struct ring_msg *create_ring_msg_with_size(uint32_t size, bool init_node);
rstatus_t ring_msg_init(struct ring_msg *msg, uint32_t size, bool init_node);
rstatus_t ring_msg_deinit(struct ring_msg *msg);

struct node * create_node(void);
rstatus_t node_init(struct node *node);
rstatus_t node_deinit(struct node *node);
rstatus_t node_copy(const struct node *src, struct node *dst);


#endif
