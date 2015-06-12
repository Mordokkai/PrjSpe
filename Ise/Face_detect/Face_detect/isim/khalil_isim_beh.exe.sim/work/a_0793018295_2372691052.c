/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0xfbc00daa */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "/user/1/.base/chatouik/home/Projet_specialite/PrjSpe/Ise/Face_detect/Face_detect/test_image_inte.vhd";
extern char *IEEE_P_2592010699;
extern char *IEEE_P_1242562249;

char *ieee_p_1242562249_sub_1006216973935652998_1035706684(char *, char *, char *, char *, int );
unsigned char ieee_p_1242562249_sub_3307759752501467860_1035706684(char *, char *, char *, int );
unsigned char ieee_p_2592010699_sub_2763492388968962707_503743352(char *, char *, unsigned int , unsigned int );


static void work_a_0793018295_2372691052_p_0(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    int64 t6;
    char *t7;
    char *t8;
    char *t9;
    char *t10;
    char *t11;

LAB0:    xsi_set_current_line(75, ng0);

LAB3:    t1 = (t0 + 5816);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    *((unsigned char *)t5) = (unsigned char)3;
    xsi_driver_first_trans_delta(t1, 0U, 1, 0LL);
    t6 = (30 * 1000LL);
    t7 = (t0 + 5816);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    t10 = (t9 + 56U);
    t11 = *((char **)t10);
    *((unsigned char *)t11) = (unsigned char)2;
    xsi_driver_subsequent_trans_delta(t7, 0U, 1, t6);

LAB2:
LAB1:    return;
LAB4:    goto LAB2;

}

static void work_a_0793018295_2372691052_p_1(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    int64 t7;
    int64 t8;

LAB0:    t1 = (t0 + 5072U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(80, ng0);
    t2 = (t0 + 5880);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(81, ng0);
    t2 = (t0 + 3728U);
    t3 = *((char **)t2);
    t7 = *((int64 *)t3);
    t8 = (t7 / 2);
    t2 = (t0 + 4880);
    xsi_process_wait(t2, t8);

LAB6:    *((char **)t1) = &&LAB7;

LAB1:    return;
LAB4:    xsi_set_current_line(82, ng0);
    t2 = (t0 + 5880);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)3;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(83, ng0);
    t2 = (t0 + 3728U);
    t3 = *((char **)t2);
    t7 = *((int64 *)t3);
    t8 = (t7 / 2);
    t2 = (t0 + 4880);
    xsi_process_wait(t2, t8);

LAB10:    *((char **)t1) = &&LAB11;
    goto LAB1;

LAB5:    goto LAB4;

LAB7:    goto LAB5;

LAB8:    goto LAB2;

LAB9:    goto LAB8;

LAB11:    goto LAB9;

}

static void work_a_0793018295_2372691052_p_2(char *t0)
{
    char t17[16];
    char t20[16];
    char *t1;
    char *t2;
    unsigned char t3;
    char *t4;
    char *t5;
    unsigned char t6;
    unsigned char t7;
    unsigned char t8;
    char *t9;
    char *t10;
    int64 t11;
    char *t12;
    char *t13;
    char *t14;
    char *t15;
    char *t16;
    unsigned int t18;
    unsigned int t19;
    int t21;
    char *t22;
    char *t23;

LAB0:    t1 = (t0 + 5320U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(92, ng0);

LAB6:    t2 = (t0 + 5640);
    *((int *)t2) = 1;
    *((char **)t1) = &&LAB7;

LAB1:    return;
LAB4:    t9 = (t0 + 5640);
    *((int *)t9) = 0;
    xsi_set_current_line(93, ng0);

LAB13:    t2 = (t0 + 5656);
    *((int *)t2) = 1;
    *((char **)t1) = &&LAB14;
    goto LAB1;

LAB5:    t4 = (t0 + 3432U);
    t5 = *((char **)t4);
    t6 = *((unsigned char *)t5);
    t7 = (t6 == (unsigned char)3);
    if (t7 == 1)
        goto LAB8;

LAB9:    t3 = (unsigned char)0;

LAB10:    if (t3 == 1)
        goto LAB4;
    else
        goto LAB6;

LAB7:    goto LAB5;

LAB8:    t4 = (t0 + 3392U);
    t8 = xsi_signal_has_event(t4);
    t3 = t8;
    goto LAB10;

LAB11:    t4 = (t0 + 5656);
    *((int *)t4) = 0;
    xsi_set_current_line(94, ng0);

LAB17:    t2 = (t0 + 5672);
    *((int *)t2) = 1;
    *((char **)t1) = &&LAB18;
    goto LAB1;

LAB12:    t4 = (t0 + 1032U);
    t5 = *((char **)t4);
    t3 = *((unsigned char *)t5);
    t6 = (t3 == (unsigned char)2);
    if (t6 == 1)
        goto LAB11;
    else
        goto LAB13;

LAB14:    goto LAB12;

LAB15:    t5 = (t0 + 5672);
    *((int *)t5) = 0;
    xsi_set_current_line(95, ng0);
    t2 = (t0 + 5944);
    t4 = (t2 + 56U);
    t5 = *((char **)t4);
    t9 = (t5 + 56U);
    t10 = *((char **)t9);
    *((unsigned char *)t10) = (unsigned char)3;
    xsi_driver_first_trans_delta(t2, 0U, 1, 0LL);
    t11 = (2 * 1000LL);
    t12 = (t0 + 5944);
    t13 = (t12 + 56U);
    t14 = *((char **)t13);
    t15 = (t14 + 56U);
    t16 = *((char **)t15);
    *((unsigned char *)t16) = (unsigned char)2;
    xsi_driver_subsequent_trans_delta(t12, 0U, 1, t11);
    xsi_set_current_line(97, ng0);

LAB19:    t2 = (t0 + 3848U);
    t4 = *((char **)t2);
    t2 = (t0 + 10456U);
    t3 = ieee_p_1242562249_sub_3307759752501467860_1035706684(IEEE_P_1242562249, t4, t2, 30);
    if (t3 != 0)
        goto LAB20;

LAB22:    xsi_set_current_line(102, ng0);
    t2 = xsi_get_transient_memory(8U);
    memset(t2, 0, 8U);
    t4 = t2;
    memset(t4, (unsigned char)2, 8U);
    t5 = (t0 + 3848U);
    t9 = *((char **)t5);
    t5 = (t9 + 0);
    memcpy(t5, t2, 8U);
    xsi_set_current_line(103, ng0);

LAB30:    t2 = (t0 + 3848U);
    t4 = *((char **)t2);
    t2 = (t0 + 10456U);
    t3 = ieee_p_1242562249_sub_3307759752501467860_1035706684(IEEE_P_1242562249, t4, t2, 255);
    if (t3 != 0)
        goto LAB31;

LAB33:    xsi_set_current_line(110, ng0);
    t2 = xsi_get_transient_memory(8U);
    memset(t2, 0, 8U);
    t4 = t2;
    memset(t4, (unsigned char)2, 8U);
    t5 = (t0 + 3848U);
    t9 = *((char **)t5);
    t5 = (t9 + 0);
    memcpy(t5, t2, 8U);
    xsi_set_current_line(111, ng0);

LAB45:    t2 = (t0 + 3848U);
    t4 = *((char **)t2);
    t2 = (t0 + 10456U);
    t3 = ieee_p_1242562249_sub_3307759752501467860_1035706684(IEEE_P_1242562249, t4, t2, 255);
    if (t3 != 0)
        goto LAB46;

LAB48:    xsi_set_current_line(118, ng0);
    t2 = xsi_get_transient_memory(8U);
    memset(t2, 0, 8U);
    t4 = t2;
    memset(t4, (unsigned char)2, 8U);
    t5 = (t0 + 3848U);
    t9 = *((char **)t5);
    t5 = (t9 + 0);
    memcpy(t5, t2, 8U);
    xsi_set_current_line(119, ng0);

LAB60:    t2 = (t0 + 3848U);
    t4 = *((char **)t2);
    t2 = (t0 + 10456U);
    t3 = ieee_p_1242562249_sub_3307759752501467860_1035706684(IEEE_P_1242562249, t4, t2, 255);
    if (t3 != 0)
        goto LAB61;

LAB63:    xsi_set_current_line(128, ng0);

LAB77:    *((char **)t1) = &&LAB78;
    goto LAB1;

LAB16:    t4 = (t0 + 3392U);
    t3 = ieee_p_2592010699_sub_2763492388968962707_503743352(IEEE_P_2592010699, t4, 0U, 0U);
    if (t3 == 1)
        goto LAB15;
    else
        goto LAB17;

LAB18:    goto LAB16;

LAB20:    xsi_set_current_line(98, ng0);
    t5 = (t0 + 3848U);
    t9 = *((char **)t5);
    t5 = (t0 + 6008);
    t10 = (t5 + 56U);
    t12 = *((char **)t10);
    t13 = (t12 + 56U);
    t14 = *((char **)t13);
    memcpy(t14, t9, 8U);
    xsi_driver_first_trans_fast(t5);
    xsi_set_current_line(99, ng0);
    t2 = (t0 + 3848U);
    t4 = *((char **)t2);
    t2 = (t0 + 10456U);
    t5 = ieee_p_1242562249_sub_1006216973935652998_1035706684(IEEE_P_1242562249, t17, t4, t2, 1);
    t9 = (t0 + 3848U);
    t10 = *((char **)t9);
    t9 = (t10 + 0);
    t12 = (t17 + 12U);
    t18 = *((unsigned int *)t12);
    t19 = (1U * t18);
    memcpy(t9, t5, t19);
    xsi_set_current_line(100, ng0);

LAB25:    t2 = (t0 + 5688);
    *((int *)t2) = 1;
    *((char **)t1) = &&LAB26;
    goto LAB1;

LAB21:;
LAB23:    t5 = (t0 + 5688);
    *((int *)t5) = 0;
    goto LAB19;

LAB24:    t4 = (t0 + 3392U);
    t6 = xsi_signal_has_event(t4);
    if (t6 == 1)
        goto LAB27;

LAB28:    t3 = (unsigned char)0;

LAB29:    if (t3 == 1)
        goto LAB23;
    else
        goto LAB25;

LAB26:    goto LAB24;

LAB27:    t5 = (t0 + 3432U);
    t9 = *((char **)t5);
    t7 = *((unsigned char *)t9);
    t8 = (t7 == (unsigned char)3);
    t3 = t8;
    goto LAB29;

LAB31:    xsi_set_current_line(104, ng0);
    t5 = (t0 + 3848U);
    t9 = *((char **)t5);
    t5 = (t0 + 6008);
    t10 = (t5 + 56U);
    t12 = *((char **)t10);
    t13 = (t12 + 56U);
    t14 = *((char **)t13);
    memcpy(t14, t9, 8U);
    xsi_driver_first_trans_fast(t5);
    xsi_set_current_line(105, ng0);
    t2 = (t0 + 10696);
    t5 = (t0 + 3848U);
    t9 = *((char **)t5);
    t10 = ((IEEE_P_1242562249) + 2976);
    t12 = (t20 + 0U);
    t13 = (t12 + 0U);
    *((int *)t13) = 0;
    t13 = (t12 + 4U);
    *((int *)t13) = 23;
    t13 = (t12 + 8U);
    *((int *)t13) = 1;
    t21 = (23 - 0);
    t18 = (t21 * 1);
    t18 = (t18 + 1);
    t13 = (t12 + 12U);
    *((unsigned int *)t13) = t18;
    t13 = (t0 + 10456U);
    t5 = xsi_base_array_concat(t5, t17, t10, (char)97, t2, t20, (char)97, t9, t13, (char)101);
    t18 = (24U + 8U);
    t3 = (32U != t18);
    if (t3 == 1)
        goto LAB34;

LAB35:    t14 = (t0 + 6072);
    t15 = (t14 + 56U);
    t16 = *((char **)t15);
    t22 = (t16 + 56U);
    t23 = *((char **)t22);
    memcpy(t23, t5, 32U);
    xsi_driver_first_trans_fast(t14);
    xsi_set_current_line(106, ng0);
    t2 = (t0 + 10720);
    t5 = (t0 + 3848U);
    t9 = *((char **)t5);
    t10 = ((IEEE_P_1242562249) + 2976);
    t12 = (t20 + 0U);
    t13 = (t12 + 0U);
    *((int *)t13) = 0;
    t13 = (t12 + 4U);
    *((int *)t13) = 23;
    t13 = (t12 + 8U);
    *((int *)t13) = 1;
    t21 = (23 - 0);
    t18 = (t21 * 1);
    t18 = (t18 + 1);
    t13 = (t12 + 12U);
    *((unsigned int *)t13) = t18;
    t13 = (t0 + 10456U);
    t5 = xsi_base_array_concat(t5, t17, t10, (char)97, t2, t20, (char)97, t9, t13, (char)101);
    t18 = (24U + 8U);
    t3 = (32U != t18);
    if (t3 == 1)
        goto LAB36;

LAB37:    t14 = (t0 + 6136);
    t15 = (t14 + 56U);
    t16 = *((char **)t15);
    t22 = (t16 + 56U);
    t23 = *((char **)t22);
    memcpy(t23, t5, 32U);
    xsi_driver_first_trans_fast(t14);
    xsi_set_current_line(107, ng0);
    t2 = (t0 + 3848U);
    t4 = *((char **)t2);
    t2 = (t0 + 10456U);
    t5 = ieee_p_1242562249_sub_1006216973935652998_1035706684(IEEE_P_1242562249, t17, t4, t2, 1);
    t9 = (t0 + 3848U);
    t10 = *((char **)t9);
    t9 = (t10 + 0);
    t12 = (t17 + 12U);
    t18 = *((unsigned int *)t12);
    t19 = (1U * t18);
    memcpy(t9, t5, t19);
    xsi_set_current_line(108, ng0);

LAB40:    t2 = (t0 + 5704);
    *((int *)t2) = 1;
    *((char **)t1) = &&LAB41;
    goto LAB1;

LAB32:;
LAB34:    xsi_size_not_matching(32U, t18, 0);
    goto LAB35;

LAB36:    xsi_size_not_matching(32U, t18, 0);
    goto LAB37;

LAB38:    t5 = (t0 + 5704);
    *((int *)t5) = 0;
    goto LAB30;

LAB39:    t4 = (t0 + 3392U);
    t6 = xsi_signal_has_event(t4);
    if (t6 == 1)
        goto LAB42;

LAB43:    t3 = (unsigned char)0;

LAB44:    if (t3 == 1)
        goto LAB38;
    else
        goto LAB40;

LAB41:    goto LAB39;

LAB42:    t5 = (t0 + 3432U);
    t9 = *((char **)t5);
    t7 = *((unsigned char *)t9);
    t8 = (t7 == (unsigned char)3);
    t3 = t8;
    goto LAB44;

LAB46:    xsi_set_current_line(112, ng0);
    t5 = (t0 + 3848U);
    t9 = *((char **)t5);
    t5 = (t0 + 6008);
    t10 = (t5 + 56U);
    t12 = *((char **)t10);
    t13 = (t12 + 56U);
    t14 = *((char **)t13);
    memcpy(t14, t9, 8U);
    xsi_driver_first_trans_fast(t5);
    xsi_set_current_line(113, ng0);
    t2 = (t0 + 10744);
    t5 = (t0 + 3848U);
    t9 = *((char **)t5);
    t10 = ((IEEE_P_1242562249) + 2976);
    t12 = (t20 + 0U);
    t13 = (t12 + 0U);
    *((int *)t13) = 0;
    t13 = (t12 + 4U);
    *((int *)t13) = 23;
    t13 = (t12 + 8U);
    *((int *)t13) = 1;
    t21 = (23 - 0);
    t18 = (t21 * 1);
    t18 = (t18 + 1);
    t13 = (t12 + 12U);
    *((unsigned int *)t13) = t18;
    t13 = (t0 + 10456U);
    t5 = xsi_base_array_concat(t5, t17, t10, (char)97, t2, t20, (char)97, t9, t13, (char)101);
    t18 = (24U + 8U);
    t3 = (32U != t18);
    if (t3 == 1)
        goto LAB49;

LAB50:    t14 = (t0 + 6072);
    t15 = (t14 + 56U);
    t16 = *((char **)t15);
    t22 = (t16 + 56U);
    t23 = *((char **)t22);
    memcpy(t23, t5, 32U);
    xsi_driver_first_trans_fast(t14);
    xsi_set_current_line(114, ng0);
    t2 = (t0 + 10768);
    t5 = (t0 + 3848U);
    t9 = *((char **)t5);
    t10 = ((IEEE_P_1242562249) + 2976);
    t12 = (t20 + 0U);
    t13 = (t12 + 0U);
    *((int *)t13) = 0;
    t13 = (t12 + 4U);
    *((int *)t13) = 23;
    t13 = (t12 + 8U);
    *((int *)t13) = 1;
    t21 = (23 - 0);
    t18 = (t21 * 1);
    t18 = (t18 + 1);
    t13 = (t12 + 12U);
    *((unsigned int *)t13) = t18;
    t13 = (t0 + 10456U);
    t5 = xsi_base_array_concat(t5, t17, t10, (char)97, t2, t20, (char)97, t9, t13, (char)101);
    t18 = (24U + 8U);
    t3 = (32U != t18);
    if (t3 == 1)
        goto LAB51;

LAB52:    t14 = (t0 + 6136);
    t15 = (t14 + 56U);
    t16 = *((char **)t15);
    t22 = (t16 + 56U);
    t23 = *((char **)t22);
    memcpy(t23, t5, 32U);
    xsi_driver_first_trans_fast(t14);
    xsi_set_current_line(115, ng0);
    t2 = (t0 + 3848U);
    t4 = *((char **)t2);
    t2 = (t0 + 10456U);
    t5 = ieee_p_1242562249_sub_1006216973935652998_1035706684(IEEE_P_1242562249, t17, t4, t2, 1);
    t9 = (t0 + 3848U);
    t10 = *((char **)t9);
    t9 = (t10 + 0);
    t12 = (t17 + 12U);
    t18 = *((unsigned int *)t12);
    t19 = (1U * t18);
    memcpy(t9, t5, t19);
    xsi_set_current_line(116, ng0);

LAB55:    t2 = (t0 + 5720);
    *((int *)t2) = 1;
    *((char **)t1) = &&LAB56;
    goto LAB1;

LAB47:;
LAB49:    xsi_size_not_matching(32U, t18, 0);
    goto LAB50;

LAB51:    xsi_size_not_matching(32U, t18, 0);
    goto LAB52;

LAB53:    t5 = (t0 + 5720);
    *((int *)t5) = 0;
    goto LAB45;

LAB54:    t4 = (t0 + 3392U);
    t6 = xsi_signal_has_event(t4);
    if (t6 == 1)
        goto LAB57;

LAB58:    t3 = (unsigned char)0;

LAB59:    if (t3 == 1)
        goto LAB53;
    else
        goto LAB55;

LAB56:    goto LAB54;

LAB57:    t5 = (t0 + 3432U);
    t9 = *((char **)t5);
    t7 = *((unsigned char *)t9);
    t8 = (t7 == (unsigned char)3);
    t3 = t8;
    goto LAB59;

LAB61:    xsi_set_current_line(120, ng0);
    t5 = (t0 + 3848U);
    t9 = *((char **)t5);
    t5 = (t0 + 6008);
    t10 = (t5 + 56U);
    t12 = *((char **)t10);
    t13 = (t12 + 56U);
    t14 = *((char **)t13);
    memcpy(t14, t9, 8U);
    xsi_driver_first_trans_fast(t5);
    xsi_set_current_line(121, ng0);
    t2 = (t0 + 10792);
    t5 = (t0 + 3848U);
    t9 = *((char **)t5);
    t10 = ((IEEE_P_1242562249) + 2976);
    t12 = (t20 + 0U);
    t13 = (t12 + 0U);
    *((int *)t13) = 0;
    t13 = (t12 + 4U);
    *((int *)t13) = 23;
    t13 = (t12 + 8U);
    *((int *)t13) = 1;
    t21 = (23 - 0);
    t18 = (t21 * 1);
    t18 = (t18 + 1);
    t13 = (t12 + 12U);
    *((unsigned int *)t13) = t18;
    t13 = (t0 + 10456U);
    t5 = xsi_base_array_concat(t5, t17, t10, (char)97, t2, t20, (char)97, t9, t13, (char)101);
    t18 = (24U + 8U);
    t3 = (32U != t18);
    if (t3 == 1)
        goto LAB64;

LAB65:    t14 = (t0 + 6072);
    t15 = (t14 + 56U);
    t16 = *((char **)t15);
    t22 = (t16 + 56U);
    t23 = *((char **)t22);
    memcpy(t23, t5, 32U);
    xsi_driver_first_trans_fast(t14);
    xsi_set_current_line(122, ng0);
    t2 = (t0 + 10816);
    t5 = (t0 + 3848U);
    t9 = *((char **)t5);
    t10 = ((IEEE_P_1242562249) + 2976);
    t12 = (t20 + 0U);
    t13 = (t12 + 0U);
    *((int *)t13) = 0;
    t13 = (t12 + 4U);
    *((int *)t13) = 23;
    t13 = (t12 + 8U);
    *((int *)t13) = 1;
    t21 = (23 - 0);
    t18 = (t21 * 1);
    t18 = (t18 + 1);
    t13 = (t12 + 12U);
    *((unsigned int *)t13) = t18;
    t13 = (t0 + 10456U);
    t5 = xsi_base_array_concat(t5, t17, t10, (char)97, t2, t20, (char)97, t9, t13, (char)101);
    t18 = (24U + 8U);
    t3 = (32U != t18);
    if (t3 == 1)
        goto LAB66;

LAB67:    t14 = (t0 + 6136);
    t15 = (t14 + 56U);
    t16 = *((char **)t15);
    t22 = (t16 + 56U);
    t23 = *((char **)t22);
    memcpy(t23, t5, 32U);
    xsi_driver_first_trans_fast(t14);
    xsi_set_current_line(123, ng0);
    t2 = (t0 + 3848U);
    t4 = *((char **)t2);
    t2 = (t0 + 10456U);
    t5 = ieee_p_1242562249_sub_1006216973935652998_1035706684(IEEE_P_1242562249, t17, t4, t2, 1);
    t9 = (t0 + 3848U);
    t10 = *((char **)t9);
    t9 = (t10 + 0);
    t12 = (t17 + 12U);
    t18 = *((unsigned int *)t12);
    t19 = (1U * t18);
    memcpy(t9, t5, t19);
    xsi_set_current_line(124, ng0);

LAB70:    t2 = (t0 + 5736);
    *((int *)t2) = 1;
    *((char **)t1) = &&LAB71;
    goto LAB1;

LAB62:;
LAB64:    xsi_size_not_matching(32U, t18, 0);
    goto LAB65;

LAB66:    xsi_size_not_matching(32U, t18, 0);
    goto LAB67;

LAB68:    t5 = (t0 + 5736);
    *((int *)t5) = 0;
    goto LAB60;

LAB69:    t4 = (t0 + 3392U);
    t6 = xsi_signal_has_event(t4);
    if (t6 == 1)
        goto LAB72;

LAB73:    t3 = (unsigned char)0;

LAB74:    if (t3 == 1)
        goto LAB68;
    else
        goto LAB70;

LAB71:    goto LAB69;

LAB72:    t5 = (t0 + 3432U);
    t9 = *((char **)t5);
    t7 = *((unsigned char *)t9);
    t8 = (t7 == (unsigned char)3);
    t3 = t8;
    goto LAB74;

LAB75:    goto LAB2;

LAB76:    goto LAB75;

LAB78:    goto LAB76;

}


extern void work_a_0793018295_2372691052_init()
{
	static char *pe[] = {(void *)work_a_0793018295_2372691052_p_0,(void *)work_a_0793018295_2372691052_p_1,(void *)work_a_0793018295_2372691052_p_2};
	xsi_register_didat("work_a_0793018295_2372691052", "isim/khalil_isim_beh.exe.sim/work/a_0793018295_2372691052.didat");
	xsi_register_executes(pe);
}
