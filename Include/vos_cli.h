/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/


#ifndef __VOS_CLI_H__
#define __VOS_CLI_H__
#include "vos_types.h"

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/** 历史命令记录条数 */
#define VTY_MAXHIST 20

/** 命令行提示符长度 */
#define VTY_CMD_PROMPT_MAX  64

/** 节点嵌套层数 */
#define VTY_NODE_HIS_MAX 8

/* 换行字符串 */
#define VTY_NEWLINE  ((vty->type == VTY_TERM) ? "\r\n" : "\r\n")

/** show 命令说明字符串 */
#define SHOW_STR "Show running system information\n"

/** config 命令说明字符串 */
#define CONFIG_STR "Config system's setting\n"

/** no 命令说明字符串 */
#define NO_STR "Negate a command or set its defaults\n"

/** debug 命令说明字符串 */
#define DEBUG_STR "Debugging functions\n"

/** 命令回调函数返回值 命令执行 OK */
#define CMD_RET_OK       (0)

/** 命令回调函数返回值 命令执行 ERROR */
#define CMD_RET_ERROR    (1)



/** VOS 预定义的节点 */
enum node_type
{
    VOS_CLI_VIEW_NODE,              ///<  View node. Default mode of vty interface. 
    VOS_CLI_CONFIG_NODE,            ///<  Config node. Default mode of config file. 
    VOS_CLI_DEBUG_HIDDEN_NODE,      ///<  Debug hidden node. 
    VOS_CLI_CONFIRM_ACTION_NODE,    ///<  Confirm action.
    VOS_CLI_RESV_MAX_NODE           ///<  Vos max reserved node ID
};


struct exit_use_node
{
    int   node_in_use;                          ///<  使用标记
    enum node_type node;                        ///<  节点ID
    void *context_data;                         ///<  记录命令行上下文数据，如进入端口节点可以记录端口号
    INT  context_data_need_free;                ///<  标记context_data 是否需要free，在exit 命令中会执行VOS_free
    CHAR  vty_cmd_prompt[ VTY_CMD_PROMPT_MAX ]; ///<  自定义提示符
};


/** VTY 结构体，只需关心fd之前的成员. */
struct vty
{
    char vty_cmd_prompt[VTY_CMD_PROMPT_MAX];   ///<  自定义提示符

    VOID *context_data;                        ///<  记录命令行上下文数据，如进入端口节点可以记录端口号

    INT context_data_need_free;                ///<  标记context_data 是否需要free，在exit 命令中会执行VOS_free

    int (*action_func) (struct vty *vty);      ///<  confirm action 的回调函数

    int (*no_action_func) (struct vty *vty);   ///<  refuse action  的回调函数

    /* 文件描述符 */
    int fd;

    /* 当前节点ID */
    enum node_type node;

    /* 上一节点ID */
    enum node_type prev_node;

    /* VTY 类型 */
    enum { VTY_TERM, }type;

    /* client IP */
    char *address;

    /* vty 输出缓冲区 */
    struct buffer *obuf;

    /* obuf 的锁 */
    LONG  Sem_obuf ;

    /* vty 命令输入缓冲区 */
    char *buf;

    /* 当前光标的位置 */
    int cp;

    /* 当前输入的长度 */
    int length;

    /* buf 的大小. */
    int max;

    /* 历史命令 */
    char *hist[VTY_MAXHIST];

    /* 查看历史命令时记录当前索引 */
    int hp;

    /* 历史命令条数 */
    int hindex;

    struct exit_use_node node_his_save[VTY_NODE_HIS_MAX];

    /* 转义字符状态. */
    unsigned char escape;

    /* vty 状态. */
    enum { VTY_NORMAL, VTY_CLOSE, VTY_MORE, VTY_START, VTY_CONTINUE, VTY_IOREDIRECT }status;

    /* telnet IAC handling */
    unsigned char iac;

    /* telnet IAC SB handling */
    unsigned char iac_sb_in_progress;
    /* telnet IAC SB buffer */
    struct buffer *sb_buffer;

    /* 窗口宽度，暂未使用 */
    int width;
    /* 窗口高度，lines为0时有效 */
    int height;

    /* 一次输出的做大行数 */
    int lines;

    /* 已进入config节点，用于限制多用户进入config */
    int config;

    /* 输入监控任务 */
    struct cl_lib_thread *t_read;
    /* 输出监控任务 */
    struct cl_lib_thread *t_write;

    /*VTY 超时时间，秒 */
    unsigned long v_timeout;

    /*VTY 超时处理任务 */
    struct cl_lib_thread *t_timeout;

    /*VTY 退出标志位 */
    unsigned short cl_vty_exit;

    /* vty 接入类型console，telnet， telnet IPv6 */
    int conn_type;
    
    /* vty 接入用户名 */
    char *user_name;

    /* vty 会话任务 */
    struct cl_lib_thread_master *sub_thread_master;
    
    /* vty 会话任务handle */
    VOS_HANDLE sub_task_id;

    /* vty 调试标志位 */
    unsigned short debug_monitor;  

    /************************************
    frozen vty in and(or) out 
    used for if a command can't return immediately
    then call frozen to freeze vty's in and(or) out
    call unfrozen when finished.
    1: freezed
    0: unfreezed
    ***********************************/
    unsigned short frozen;

    //VOS_SYSLOG_MONITOR_CONF  monitor_conf;
    int veryBigOutLineCount;
    int veryBigOutNoFirst;

    /* vty 引用计数，当引用计数为0的时候调用vty_close释放内存 */
    int ncount;
};


/** cl_vector 动态数组指针 */
struct _cl_vector 
{
    unsigned int max;       ///< 当前最大索引加1 
    unsigned int alloced;   ///< 数组大小 */
    void **index;           ///< 指针数组
};
typedef struct _cl_vector *cl_vector;


/** 命令结构体 */
struct cmd_element
{
    char *string;		 ///< 命令字符串，多个用空格分隔的单词组成的句子
    int (*func) (struct cmd_element *, struct vty *, int, char **); ///< 命令回调函数
    char *doc;			 ///< 命令说明，对命令字符串中的每个单词进行说明
    int msg_flag;        ///< 命令类型标识，当前只有 DEFUN_FLAG 类型
    cl_vector strvec;	 ///< 将 string和doc 拆分后放入该数组中 ,存放struct desc 
    int cmdsize;		 ///< string 中单词个数
    cl_vector subconfig; ///< 将 string中可以重复的单词的重复位置和重复次数等 
};


/** 命令节点结构体 */
struct cmd_node
{
    enum node_type node_id;           ///< 节点ID
    char prompt[VTY_CMD_PROMPT_MAX];  ///< 节点提示符
    cl_vector cmd_vector;             ///< 节点命令数组
};


#define DEFUN_FLAG     0

/** 
 * 命令行定义宏
 * @param[in]   funcname   回调函数的函数名
 * @param[in]   cmdname    命令变量的变量名
 * @param[in]   cmdstr     命令字符串
 * @param[in]   helpstr    命令字符串中各个单词的注解
 * @return      返回输出的字节数
 */
#define DEFUN(funcname, cmdname, cmdstr, helpstr)   \
	int funcname (struct cmd_element *, struct vty *, int, char **);\
	struct cmd_element cmdname =   {cmdstr,     funcname,     helpstr , DEFUN_FLAG};\
	int funcname  (struct cmd_element *self, struct vty *vty, int argc, char **argv)


/** 
 * 命令行回调函数中的标准输出函数,
 * 注意 LONG 输出时，要用%ld,或%lx
 * @param[in]   vty     vty
 * @param[in]   format  格式字符串
 * @param[in]   ...     要输出的变量
 * @return      返回输出的字节数
 */
INT vty_out ( struct vty * vty, const CHAR * format, ... );

/** 
 * 创建并安装命令节点
 * @param[in]   prompt         节点提示符，用于命令行提示符的显示
 * @return      成功返回 一个新节点的指针,失败返回NULL
 */
struct cmd_node *VOS_cli_create_node(char prompt[VTY_CMD_PROMPT_MAX]);


/** 
 * 把命令安装到指定节点
 * @param[in]   node_id     节点ID
 * @param[in]   cmd         命令
 * @return      成功返回 VOS_OK,失败返回其他
 */
VOID VOS_cli_install_element( enum node_type node_id, struct cmd_element * cmd );


/** 
 * 在进入节点函数中调用，用于进入节点
 * @param[in]   vty       vty
 * @param[in]   newnode   要进入的节点ID
 * @return      成功返回 VOS_OK,失败返回其他
 */
LONG  vty_enter_node(struct vty *vty,enum node_type newnode);


/** 
 * 在进入节点函数中调用，用于自定义要进入节点的命令行提示符，
 * 调用vty_enter_node后调用
 * @param[in]   vty       vty
 * @param[in]   cpPrompt  提示符
 */
VOID vty_set_prompt( struct vty * vty, CHAR cpPrompt[VTY_CMD_PROMPT_MAX] );




/**
 * Completion match types. 匹配度，数值越大匹配度越高,命令行模块内部使用无需关心
 */
enum match_type
{
    no_match,
    incomplete_match,
    ambiguous_match,
    extend_match,
    vararg_match,
    one_element_two_partly_match,
    partly_match,
    almost_exact_match,   /* exactmatch except last word */
    ipv4_prefix_match,
    ipv4_match,
    ipv6_prefix_match,
    ipv6_match,

    aann_match,
    mac_match,
    slot_port_match,
    slot_subport_match,
    
    time_match,
    range_match,

    /*其余的匹配类型在此之前*/
    register_match,
    
    exact_match
};


/** 自定义命令行参数解析函数  */
typedef struct _cmd_notify_register_tag
{
    CHAR *match_str ;                            ///<  匹配的格式，如<H.H.H>
    enum match_type (*pnotify_call) (CHAR *str); ///<  格式解析的回调函数，解析成功返回exact_match，解析失败返回no_match
    CHAR IsCapital ;                             ///<  是否包含大写字母 0 － 全小写； 1 － 含有大写字母
}CMD_NOTIFY_REFISTER_S;

/** 
 * 添加自定义命令行参数解析函数
 * @param[in]   pNotifyRegister   自定义解析函数信息
 * @return      成功返回 register_match,失败返回no_match
 */
enum match_type cmd_rugular_register(CMD_NOTIFY_REFISTER_S * pNotifyRegister);

/** 
 * 配置/获取 vty超时时间
 * @param[in ]   vty         vty
 * @param[in ]   newTime     新的超时时间，大于等于0时有效，0表示不会超时
 * @param[out]   oldTime     如果不为NULL 返回配置前的超时时间
 * @return      成功返回 VOS_OK，失败则返回其他
 */ 
LONG vty_timeout_config ( struct vty * vty, LONG newTime, LONG *oldTime);


/** 
 * 要使用vty_very_big_out 函数必须先调用此初始化函数 
 * @param[in ]   vty         vty
 */
void vty_very_big_out_init ( struct vty *vty );

/** 
 * 用于长字符串打印 
 * @param[in]   vty     vty
 * @param[in]   format  格式字符串
 * @param[in]   ...     要输出的变量
 */
int vty_very_big_out (struct vty *vty, const char *format, ...);


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __VOS_CLI_H__ */
