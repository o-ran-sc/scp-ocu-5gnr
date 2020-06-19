/******************************************************************************
*
*   Copyright (c) 2020 ICT/CAS.
*
*   Licensed under the O-RAN Software License, Version 1.0 (the "Software License");
*   you may not use this file except in compliance with the License.
*   You may obtain a copy of the License at
*
*       https://www.o-ran.org/software
*
*   Unless required by applicable law or agreed to in writing, software
*   distributed under the License is distributed on an "AS IS" BASIS,
*   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*   See the License for the specific language governing permissions and
*   limitations under the License.
*
*******************************************************************************/




#ifndef _VOS_LINKLIST_H
#define _VOS_LINKLIST_H

#ifdef __cplusplus
extern"C"{
#endif

/** 链表节点 */
typedef struct cl_lib_listnode
{
    struct cl_lib_listnode *next;
    struct cl_lib_listnode *prev;
    void *data;
}*plistnode;

/** 链表名长度 */
#define LIST_NAME_LEN (48)

/** 链表节 */
typedef struct cl_lib_list
{
    struct cl_lib_listnode *head;
    struct cl_lib_listnode *tail;
    char name[LIST_NAME_LEN];
    unsigned long moduleID;
    unsigned int count;
    int ( *cmp ) ( void *val1, void *val2 );
    void ( *del ) ( void *val );
}*plist;


/** 获得链表头 */
#define cl_lib_listhead(X) ((X)->head)

/** 获得链表尾 */
#define cl_lib_listtail(X) ((X)->tail)

/** 获得下个节点 */
#define cl_lib_nextnode(X) ((X) = (X)->next)

/** 获得上个节点 */
#define cl_lib_prevnode(X) ((X) = (X)->prev)

/** 获得链表中节点数量 */
#define cl_lib_listcount(X) ((X)->count)

/** 链表为空 */
#define cl_lib_list_isempty(X) ((X)->head == NULL && (X)->tail == NULL)

/** 获得节点中的数据 */
#define cl_lib_getdata(X) ((X)->data)

/**
 * 创建一个linklist
 * @param[in]   name      list名  最大长度 LIST_NAME_LEN
 * @param[in]   moduleID  创建list的模块ID
 * @return      成功时返回新list地址，失败则返回NULL。
 */
struct cl_lib_list *cl_lib_list_new (char *name,unsigned long moduleID);



/**
 * free并删除linklist中的所有节点，然后free该list
 * ！！！注意，如果data也需要free，则需要实现list的del成员
 * @param[in]   plist1      要删除的list
 */
void cl_lib_list_delete ( struct cl_lib_list * plist1 );

/**
 * 将数据添加到链表尾，直接传入要添加的数据，该API会自动创建节点
 * @param[in]   plist1      待添加的list
 * @param[in]   val         待添加的数据
 */
void cl_lib_listnode_add ( struct cl_lib_list * plist1, void * val );


/**
 * 将数据添加到链表头，直接传入要添加的数据，该API会自动创建节点
 * @param[in]   plist1      待添加的list
 * @param[in]   val         待添加的数据
 */
void cl_lib_listnode_add_toHead ( struct cl_lib_list * plist1, void * val );

/**
 * 删除数据等于val的节点,！！！不会free 数据
 * @param[in]   plist1      待删除的list
 * @param[in]   val         待删除的数据
 */
void cl_lib_listnode_delete ( struct cl_lib_list * plist1, void * val );

/**
 * 根据注册的cmp函数删除节点，cmd 返回值为0 时删除,！！！不会free 数据
 * @param[in]   plist1      待删除的list
 * @param[in]   val         cmp 函数参数
 * @return      成功时返回被删除节点数据地址，用于free数据，失败则返回NULL。
 */
void *cl_lib_listnode_cmp_delete ( struct cl_lib_list * plist1, void * val );

/**
 * 在当前节点前插入数据
 * @param[in]   plist1      待插入数据的list
 * @param[in]   currentnode 当前节点
 * @param[in]   val         待插入数据
 */
void cl_lib_list_add_node_prev ( plist plist1, plistnode currentnode, void *val );

/**
 * 在当前节点后插入数据
 * @param[in]   plist1      待插入数据的list
 * @param[in]   currentnode 当前节点
 * @param[in]   val         待插入数据
 */
void cl_lib_list_add_node_next ( plist plist1, plistnode currentnode, void *val );

/**
 * 节点查找 API,根据给定val查找
 * ！！！用此API 需要确保 plist->cmp 成员已赋值，否则无法查找
 * ！！！不可修改获得节点的 prev 和 next指针
 * ！！！不可释放获得节点
 * ！！！如果替换获得节点的data数据，如果旧的data需要释放，需自己手动释放data数据
 * @param[in]   plist1      要查找的list
 * @param[in]   data        进行比较的数据
 * @return      找到返回节点指针，未找到返回 NULL。
 */
plistnode cl_lib_listnode_lookup_by_val( plist plist1, void *data );


/**
 * 节点查找 API,根据给定val和cmp方法查找
 * ！！！不可修改获得节点的 prev 和 next指针
 * ！！！不可释放获得节点
 * ！！！如果替换获得节点的data数据，如果旧的data需要释放，需自己手动释放data数据
 * @param[in]   plist1      要查找的list
 * @param[in]   cmp         比较函数，当val1 与val2相等时返回0,不相等时返回非0值
 * @param[in]   data        进行比较的数据
 * @return      找到返回节点指针，未找到返回 NULL。
 */
plistnode cl_lib_listnode_lookup_by_func( plist plist1, int (*cmp)(void *val1, void *val2),void *data);


/**
 * 查找到的节点，如果想要从链表中删除，必须使用该接口
 * ！！！注意，如果data也需要free，则需要实现list的del成员
 * @param[in]   plist1      list
 * @param[in]   node        要删除的节点
 */
void cl_lib_list_delete_node ( plist plist1, plistnode node );


#ifdef __cplusplus
}
#endif

#endif /* _VOS_LINKLIST_H */
