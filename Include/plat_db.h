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




#ifndef	__PLAT_DB_H__
#define	__PLAT_DB_H__

#ifdef	__cplusplus
extern "C"{
#endif

#include "vos_types.h"
#include "vos_lib.h"

/** 最多的表数 */
#define DB_MAX_TABLE  200


/** 表名最大长度 */
#define DB_TABLE_NAME_LEN  40

/** 列名最大长度 */
#define DB_COLUMN_NAME_LEN  40

/** 表的最大列数 */
#define DB_TABLE_COLUMNS_MAX  40

/** 默认值最大长度 */
#define DB_DEFAULTVAL_LEN  2048

/** 外键最大长度 */
#define DB_FKEY_LEN (DB_TABLE_NAME_LEN+DB_COLUMN_NAME_LEN)

/** filer子元素最大个数 */
#define DB_FILTER_SUB_NUM   8

#define DB_FILTER_SUB_VAL_NUM   8

/** INTEGER类型数据长度 */
#define DB_INTEGER_LEN    8


/** TIME类型数据长度 */
#define DB_TIME_LEN    16


/** 时间字符串数据长度 */
#define DB_TIME_STR_MAX_LEN    22

/** MAC地址类型数据长度 */
#define DB_MAC_ADDR_STR_MAX_LEN    18

/** IPV4地址类型数据长度 */
#define DB_IPV4_ADDR_STR_MAX_LEN   16

/** IPV6地址类型数据长度 */
#define DB_IPV6_ADDR_STR_MAX_LEN   40


#define DB_FILTER_OP_STR_LEN  10

/** 初始化函数名最大长度 */
#define DB_TABLE_INIT_FUNC_NAME_LEN  100

/** 数据库的数据类型 */
typedef enum DB_data_type_e{
    DB_DATA_TYPE_INTEGER        = 1L,  ///< 数值型
    DB_DATA_TYPE_STR               ,  ///< 字符串型
    DB_DATA_TYPE_DATETIME          ,  ///< 时间型
    DB_DATA_TYPE_MAC               ,  ///< MAC地址型
    DB_DATA_TYPE_IPV4_ADDR         ,  ///< IPv4地址型
    DB_DATA_TYPE_IPV6_ADDR         ,  ///< IPv6地址型
    DB_DATA_TYPE_BUFFER            ,  ///< buffer型
    DB_DATA_TYPE_MAX
}DB_data_type_t;


/** 数据库的查询的比较类型 */
typedef enum DB_filter_sub_type_e{
    DB_FILTER_SUB_TYPE_EQUAL        = 1,  ///< 相等
    DB_FILTER_SUB_TYPE_N_EQUAL         ,  ///< 不相等
    DB_FILTER_SUB_TYPE_GREAT           ,  ///< 大于
    DB_FILTER_SUB_TYPE_LESS            ,  ///< 小于
    DB_FILTER_SUB_TYPE_GREAT_EQ        ,  ///< 大于等于
    DB_FILTER_SUB_TYPE_LESS_EQ         ,  ///< 小于等于
    DB_FILTER_SUB_TYPE_INCLUDE         ,  ///< 包含
    DB_FILTER_SUB_TYPE_EXCLUDE         ,  ///< 不包含
    DB_FILTER_SUB_TYPE_MAX
}DB_filter_sub_type_t;

/** filter的组合方式 */
typedef enum DB_filter_option_e{
    DB_FILTER_OPTION_AND        = 1,  ///< 与
    DB_FILTER_OPTION_OR            ,  ///< 或
    DB_filter_TYPE_MAX
}DB_filter_option_t;

/** 排序方式 */
typedef enum DB_order_type_e{
    DB_ORDER_TYPE_ASCEND        = 0,  ///< 升序(默认)
    DB_ORDER_TYPE_DESCEND       = 1,  ///< 降序
    DB_ORDER_TYPE_MAX
}DB_order_type_t;
#define  DB_ORDER_TYPE_DESCEND_STR "DESC"

/** 排序信息 */
typedef struct DB_order_s{
    CHAR col_name[DB_COLUMN_NAME_LEN];
    DB_order_type_t type;  ///< 默认升序
}DB_order_t;


/** 数据库数据的值 */
typedef union DB_data_val_u{
    LONG integerVal;
    CHAR strVal[DB_DEFAULTVAL_LEN];
    CHAR datetimeVal[DB_DEFAULTVAL_LEN];
    CHAR macVal[DB_MAC_ADDR_STR_MAX_LEN];
    CHAR ipv4_addrVal[DB_IPV4_ADDR_STR_MAX_LEN];
    CHAR ipv6_addrVal[DB_IPV6_ADDR_STR_MAX_LEN];
}VOS_PACKED DB_data_val_t;


/** 列信息 */
typedef struct DB_column_info_s{
    CHAR name[DB_COLUMN_NAME_LEN];              ///< 列名
    LONG type;                                  ///< 数据的类型
    LONG size;                                  ///< 对于BUFFER和STR 类型，代表BUFFER 和 STR(包含字符串结尾 '\0') 占用的字节数
    LONG pkey;                                  ///< 主键标志
    CHAR fkey[DB_FKEY_LEN];                     ///< 外键,表名+.+列名的字符串，格式为 table(column)，字符串长度为 0 则表示不是外键
    DB_data_val_t defaultVal;                   ///< 默认值
}VOS_PACKED DB_column_info_t;

/** 数据库句柄 */
typedef struct DB_database_s{
    CHAR path[FILE_PATH_MAX];       ///< 文件路径
    VOID *handle;                   ///< 被打开的数据库
    LONG seqID;
}DB_database_t;

/** 数据库查询结果的行句柄 */
typedef ULONG DB_row_handle_t;


/** 数据初始化函数回调函数原型
* 无参数，返回 VOS_OK 表示成功
*/
typedef LONG (*DB_table_init_func_t)(VOID);

/** 表信息 */
typedef struct DB_table_info_s{
    CHAR name[DB_TABLE_NAME_LEN];       ///< name         表名
    LONG max_row;                       ///< 静态表标志，1为静态表，0为动态表
    DB_table_init_func_t table_init_func;    ///< 表初始化函数，可以为空
    CHAR table_init_func_name[DB_TABLE_INIT_FUNC_NAME_LEN];
}DB_table_info_t;

/** filer子元素 */
typedef struct DB_query_filter_sub_s{
    CHAR                 col_name[DB_COLUMN_NAME_LEN];       ///< name         表名
    DB_data_val_t        val[DB_FILTER_SUB_VAL_NUM];
    DB_filter_sub_type_t sub_type;
    DB_filter_option_t   option;
}DB_query_filter_sub_t;

/** filer */
typedef struct DB_query_filter_s{
    DB_query_filter_sub_t sub[DB_FILTER_SUB_NUM];
    DB_filter_option_t    option;
}DB_query_filter_t;


/** 排序方式 */
typedef enum DB_ret_code_e{
    DB_RET_CODE_OK                     = 0,  ///< 执行成功
    DB_RET_CODE_table_already_exist       ,  ///< 表已存在
    DB_RET_CODE_table_not_exist       ,      ///< 表已存在
    DB_RET_CODE_table_info_already_exist  ,  ///< 表的信息在数据库管理表中已存在(由数据库模块问题导致)
    DB_RET_CODE_col_info_already_exist  ,    ///< 表的列信息在数据库管理表中已存在(由数据库模块问题导致)
    DB_RET_CODE_table_info_not_exist  ,      ///< 表的信息在数据库管理表中不存在(由数据库模块问题导致)
    DB_RET_CODE_col_info_not_exist  ,        ///< 表的列信息在数据库管理表不中已存在(由数据库模块问题导致)
    DB_RET_CODE_table_info_add_error  ,      ///< 数据库模块添加表信息失败
    DB_RET_CODE_col_info_add_error  ,        ///< 数据库模块添加列信息失败
    DB_RET_CODE_get_col_size_error  ,        ///< 获取列大小失败
    DB_RET_CODE_row_data_have_more  ,        ///< row_handle 中还有数据
    DB_RET_CODE_row_data_done       ,        ///< row_handle 中没有数据
    DB_RET_CODE_row_data_pk_exist       ,    ///< 添加的数据主键冲突
    DB_RET_CODE_table_full       ,           ///< 表已满，无法在添加数据

    DB_RET_CODE_error,                       ///< 其他错误
    DB_RET_CODE_max,                         ///<
}DB_ret_code_t;


/**
 * 打开平台数据库
 * @param[out]   db           成功时返回被打开的数据
 * @return      成功返回 VOS_OK，失败则返回其他
 */
LONG DB_open_plat_db(DB_database_t *db);


/**
 * 关闭平台数据库
 * @param[in ]   db           要操作的数据库
 * @return      成功返回 VOS_OK，失败则返回其他
 */
LONG DB_close_plat_db(DB_database_t *db);


/**
 * 查看表是否存在
 * @param[in ]   db           要操作的数据库
 * @param[in ]   table_name   表名
 * @param[out]   retCode      数据库执行结果，如果不关心可以填 NULL，如果关心需要传入timeout，等待时间
 * @param[in ]   timeout      等待执行结果的时间，单位 秒
 * @return      返回向数据库模块发送消息的结果，成功返回 VOS_OK，失败则返回其他，
 */
BOOL DB_table_exist(DB_database_t *db,const CHAR *table_name,
                        LONG *retCode,LONG timeout);


/**
 * 在指定数据库中创建表
 * @param[in ]   db           要操作的数据库
 * @param[in ]   table        表信息
 * @param[in ]   cols         表的列定义数组，数组最后一个成员的name为空做为数组结尾
 * @param[out]   retCode      数据库执行结果，如果不关心可以填 NULL，如果关心需要传入timeout，等待时间
 * @param[in ]   timeout      等待执行结果的时间，单位 秒
 * @return      返回向数据库模块发送消息的结果，成功返回 VOS_OK，失败则返回其他，
 */
LONG DB_table_create(DB_database_t *db,DB_table_info_t *table,DB_column_info_t cols[],
                            LONG *retCode,LONG timeout);


/**
 * 在指定数据库中删除表
 * @param[in ]   db           要操作的数据库
 * @param[in ]   name         表名
 * @param[out]   retCode      数据库执行结果，如果不关心可以填 NULL，如果关心需要传入timeout，等待时间
 * @param[in ]   timeout      等待执行结果的时间，单位 秒
 * @return      返回向数据库模块发送消息的结果，成功返回 VOS_OK，失败则返回其他，
 */
LONG DB_table_delete(DB_database_t *db,const CHAR name[DB_TABLE_NAME_LEN],
                                LONG *retCode,LONG timeout);


/**
 * 向表中插入一行数据
 * @param[in ]   db           要操作的数据库
 * @param[in ]   table_name   要操作的表名
 * @param[in ]   data         要插入的数据，需按照创建表时定义的按顺序和大小排列每项数据，
                              可以传入按1字节对齐的结构体。
 * @param[out]   retCode      数据库执行结果，如果不关心可以填 NULL，如果关心需要传入timeout，等待时间
 * @param[in ]   timeout      等待执行结果的时间，单位 秒
 * @return      返回向数据库模块发送消息的结果，成功返回 VOS_OK，失败则返回其他，
 */
LONG DB_table_row_add(DB_database_t *db,const CHAR table_name[DB_TABLE_NAME_LEN],VOID *data,
                                    LONG *retCode,LONG timeout);


/**
* 查询数据
* @param[in ]   db           要操作的数据库
* @param[in ]   table_name   要操作的表名
* @param[out]   row_handle   查询到的行句柄
* @param[in ]   filter       查询时的过滤条件，为NULL 表示没有过滤条件，查询所有行
* @param[in ]   filter_num   filter的个数
* @param[in ]   order        查询结果排序方式
* @param[in ]   order_num    order的个数
* @param[out]   retCode      数据库执行结果，如果不关心可以填 NULL，如果关心需要传入timeout，等待时间
* @param[in ]   timeout      等待执行结果的时间，单位 秒
* @return      返回向数据库模块发送消息的结果，成功返回 VOS_OK，失败则返回其他，
*/
LONG DB_table_row_query(DB_database_t *db,const CHAR table_name[DB_TABLE_NAME_LEN],DB_row_handle_t *row_handle,
                            DB_query_filter_t filter[],LONG filter_num,DB_order_t order[],LONG order_num,
                            LONG *retCode,LONG timeout);



/**
* 获取行句柄当前行数据，并自动指向下一行，当没下一行数据时，句柄会被销毁，不可再用
* @param[in ]   db           要操作的数据库
* @param[in ]   table_name   要操作的表名
* @param[in]    row_handle   行句柄
* @param[out]   data         获取到的数据，按照创建表时定义的按顺序和大小排列每项数据，
                             可以传入按1字节对齐的结构体指针。
* @param[out]   retCode      数据库执行结果，如果不关心可以填 NULL，如果关心需要传入timeout，等待时间
* @param[in ]   timeout      等待执行结果的时间，单位 秒
* @return      返回向数据库模块发送消息的结果，成功返回 VOS_OK，失败则返回其他，
*/
LONG DB_table_row_data_pop(DB_database_t *db,const CHAR table_name[DB_TABLE_NAME_LEN],
                                        DB_row_handle_t *row_handle,VOID *data,
                                        LONG *retCode,LONG timeout);

/**
* 销毁行句柄
* @param[in ]   db           要操作的数据库
* @param[in ]   table_name   要操作的表名
* @param[in ]   row_handle   行句柄
* @param[out]   retCode      数据库执行结果，如果不关心可以填 NULL，如果关心需要传入timeout，等待时间
* @param[in ]   timeout      等待执行结果的时间，单位 秒
* @return      返回向数据库模块发送消息的结果，成功返回 VOS_OK，失败则返回其他，
*/
LONG DB_table_row_handle_destroy(DB_database_t *db,const CHAR table_name[DB_TABLE_NAME_LEN],DB_row_handle_t *row_handle,
                                            LONG *retCode,LONG timeout);


/**
* 删除行
* @param[in ]   db           要操作的数据库
* @param[in ]   table_name   要操作的表名
* @param[in ]   filter       删除时的过滤条件，为NULL 表示没有过滤条件，删除所有行
* @param[in ]   filter_num   filter的个数
* @param[out]   retCode      数据库执行结果，如果不关心可以填 NULL，如果关心需要传入timeout，等待时间
* @param[in ]   timeout      等待执行结果的时间，单位 秒
* @return      返回向数据库模块发送消息的结果，成功返回 VOS_OK，失败则返回其他，
*/
LONG DB_table_row_delete(DB_database_t *db,const CHAR table_name[DB_TABLE_NAME_LEN],
                            DB_query_filter_t filter[],LONG filter_num,
                            LONG *retCode,LONG timeout);



/**
* 更新行
* @param[in ]   db           要操作的数据库
* @param[in ]   table_name   要操作的表名
* @param[in ]   newData      新的数据，需按照创建表时定义的按顺序和大小排列每项数据，
                             可以传入按1字节对齐的结构体。
* @param[in ]   filter       更新时的过滤条件，为NULL 表示没有过滤条件，更新所有行
* @param[in ]   filter_num   filter的个数
* @param[in ]   col          只会用到name成员，用于更新指定的列，为NULL 表示更新匹配行的每一列,数组最后一个成员的name为空做为数组结尾
* @param[in ]   col_num      col的个数
* @param[out]   retCode      数据库执行结果，如果不关心可以填 NULL，如果关心需要传入timeout，等待时间
* @param[in ]   timeout      等待执行结果的时间，单位 秒
* @return      返回向数据库模块发送消息的结果，成功返回 VOS_OK，失败则返回其他，
*/
LONG DB_table_row_update(DB_database_t *db,const CHAR table_name[DB_TABLE_NAME_LEN],VOID *newData,
                            DB_query_filter_t filter[],LONG filter_num,DB_column_info_t col[],LONG col_num,
                            LONG *retCode,LONG timeout);


/**
* 计算行数
* @param[in ]   db           要操作的数据库
* @param[in ]   table_name   要操作的表名
* @param[out]   row_count    查询到的行数
* @param[in ]   filter       查询时的过滤条件，为NULL 表示没有过滤条件，查询所有行
* @param[in ]   filter_num   filter的个数
* @param[out]   retCode      数据库执行结果，如果不关心可以填 NULL，如果关心需要传入timeout，等待时间
* @param[in ]   timeout      等待执行结果的时间，单位 秒
* @return      返回向数据库模块发送消息的结果，成功返回 VOS_OK，失败则返回其他，
*/
LONG DB_table_row_count(DB_database_t *db,const CHAR table_name[DB_TABLE_NAME_LEN],LONG *row_count,
                            DB_query_filter_t filter[],LONG filter_num,
                            LONG *retCode,LONG timeout);

/**
* 覆盖最早插入的数据，用于表行数到达上限的覆盖操作
* @param[in ]   db           要操作的数据库
* @param[in ]   table_name   要操作的表名
* @param[in ]   newData      新的数据，需按照创建表时定义的按顺序和大小排列每项数据，
                             可以传入按1字节对齐的结构体。
* @param[out]   retCode      数据库执行结果，如果不关心可以填 NULL，如果关心需要传入timeout，等待时间
* @param[in ]   timeout      等待执行结果的时间，单位 秒
* @return      返回向数据库模块发送消息的结果，成功返回 VOS_OK，失败则返回其他，
*/
LONG DB_table_overwrite_first_row( DB_database_t *db,const CHAR table_name[DB_TABLE_NAME_LEN],VOID *newData,
                                            LONG *retCode,LONG timeout);


/**
* 将DB 的error code转换成字符串
* @param[in ]   code           错误码
* @return      返回错误码对应的字符串
*/
const CHAR *DB_err_msg(LONG code);


#ifdef	__cplusplus
}
#endif	/* end of __cplusplus */

#endif	/* end of __PLAT_DB_H__ */
