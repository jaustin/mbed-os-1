/** @file create.cpp
 *
 * mbed Microcontroller Library
 * Copyright (c) 2006-2016 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Test cases to create KVs in the CFSTORE using the drv->Create() API call.
 */
#if defined __MBED__ && ! defined TOOLCHAIN_GCC_ARM


#include "mbed-drivers/mbed.h"
#include "cfstore_config.h"
#include "Driver_Common.h"
#include "cfstore_debug.h"
#include "cfstore_test.h"
#include "configuration_store.h"
#include "utest/utest.h"
#include "unity/unity.h"
#include "greentea-client/test_env.h"
#ifdef YOTTA_CFG_CFSTORE_UVISOR
#include "uvisor-lib/uvisor-lib.h"
#include "cfstore_uvisor.h"
#endif /* YOTTA_CFG_CFSTORE_UVISOR */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

using namespace utest::v1;

static control_t cfstore_create_test_00(const size_t call_count)
{
    (void) call_count;
    printf("Not implemented for ARM toolchain\n");
    return CaseNext;
}


utest::v1::status_t greentea_setup(const size_t number_of_cases)
{
    GREENTEA_SETUP(100, "default_auto");
    return greentea_test_setup_handler(number_of_cases);
}

Case cases[] = {
           /*          1         2         3         4         5         6        7  */
           /* 1234567890123456789012345678901234567890123456789012345678901234567890 */
        Case("CREATE_test_00", cfstore_create_test_00),
};


/* Declare your test specification with a custom setup handler */
Specification specification(greentea_setup, cases);

int main()
{
    return !Harness::run(specification);
}



#else


#include "mbed-drivers/mbed.h"
#include "cfstore_config.h"
#include "cfstore_debug.h"
#include "cfstore_test.h"
#include "Driver_Common.h"
#include "configuration_store.h"
#include "utest/utest.h"
#include "unity/unity.h"
#include "greentea-client/test_env.h"
#include "cfstore_utest.h"
#ifdef YOTTA_CFG_CFSTORE_UVISOR
#include "uvisor-lib/uvisor-lib.h"
#endif /* YOTTA_CFG_CFSTORE_UVISOR */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

using namespace utest::v1;

#ifdef CFSTORE_DEBUG
#define CFSTORE_CREATE_GREENTEA_TIMEOUT_S     360
#else
#define CFSTORE_CREATE_GREENTEA_TIMEOUT_S     60
#endif

static char cfstore_create_utest_msg_g[CFSTORE_UTEST_MSG_BUF_SIZE];

/* Configure secure box. */
#ifdef YOTTA_CFG_CFSTORE_UVISOR
UVISOR_BOX_NAMESPACE("com.arm.mbed.cfstore.test.create.box1");
UVISOR_BOX_CONFIG(cfstore_create_box1, UVISOR_BOX_STACK_SIZE);
#endif /* YOTTA_CFG_CFSTORE_UVISOR */


#define CFSTORE_CREATE_TEST_01_TABLE_HEAD_ENTRY_01     { "Lefkada.Vathi.Meganisi.Atokos.Vathi.Ithaki.PeriPigathi.AgiosAndreas.Sami.Kefalonia.AgiaEffimia.AgiaSofia.Fiskardo.Frikes.Kioni.Meganissi.Lefkada", "Penelope"}
#define CFSTORE_CREATE_TEST_01_TABLE_HEAD_ENTRY_02     { "Iolcus.Lemnos.Salmydessus.Cyzicus.Cios.Berbryces.Symplegadese.IsleAres.Colchis.Anenea.Sirens.Scylia.Charybdis.Phaeacia.Triton.Iolcus", "Medea"}
#define CFSTORE_CREATE_TEST_01_TABLE_HEAD_ENTRY_03     { "338.Chaeronea.336.Macedonia.334.Granicus.333.Issus.332.Tyre.331.Gaugamela.330.Persepolis.Philotas.Parmenion.329.Bactria.Oxus.Samarkand.328.Cleitus.327.Roxane.326.Hydaspes.Bucephalus.324.Hephaestion.323.AlexanderDies", "TheGreat"}
#define CFSTORE_CREATE_TEST_01_TABLE_MID_ENTRY_01      { "0123456789abcdef0123456", "abcdefghijklmnopqrstuvwxyz"}
#define CFSTORE_CREATE_TEST_01_TABLE_MID_ENTRY_02      { "0123456789abcdef0123456", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"}
#define CFSTORE_CREATE_TEST_01_TABLE_MID_ENTRY_03      { "0123456789abcdef0123456", "nopqrstuvwxyz"}
#define CFSTORE_CREATE_TEST_01_TABLE_TAIL_ENTRY_01     { "Time.Will.Explain.It.All", "Aegeus"}
#define CFSTORE_CREATE_TEST_01_TABLE_TAIL_ENTRY_02     { "Cleverness.Is.Not.Wisdom", "Bacchae"}
#define CFSTORE_CREATE_TEST_01_TABLE_TAIL_ENTRY_03     { "Talk.Sense.To.A.Fool.And.He.Calls.You.Foolish", "Bacchae"}
#define CFSTORE_CREATE_TEST_01_TABLE_TAIL_ENTRY_04     { "There.is.in.the.worst.of.fortune.the.best.of.chances.for.a.happy.change", "Iphigenia.in.Tauris"}

static cfstore_kv_data_t cfstore_create_test_01_data[] = {
        CFSTORE_CREATE_TEST_01_TABLE_MID_ENTRY_01,
        CFSTORE_CREATE_TEST_01_TABLE_MID_ENTRY_02,
        CFSTORE_CREATE_TEST_01_TABLE_MID_ENTRY_03,
        { NULL, NULL},
};

/* table 1: to initialise cfstore with CFSTORE_CREATE_TEST_01_TABLE_MID_ENTRY_01 */
static cfstore_kv_data_t cfstore_create_test_01_data_step_01[] = {
        CFSTORE_CREATE_TEST_01_TABLE_HEAD_ENTRY_01,
        CFSTORE_CREATE_TEST_01_TABLE_HEAD_ENTRY_02,
        CFSTORE_CREATE_TEST_01_TABLE_HEAD_ENTRY_03,
        CFSTORE_CREATE_TEST_01_TABLE_MID_ENTRY_01,
        CFSTORE_CREATE_TEST_01_TABLE_TAIL_ENTRY_01,
        CFSTORE_CREATE_TEST_01_TABLE_TAIL_ENTRY_02,
        CFSTORE_CREATE_TEST_01_TABLE_TAIL_ENTRY_03,
        CFSTORE_CREATE_TEST_01_TABLE_TAIL_ENTRY_04,
        { NULL, NULL},
};

/* table 2: to CFSTORE_CREATE_TEST_01_TABLE_MID_ENTRY_01 grown to CFSTORE_CREATE_TEST_01_TABLE_MID_ENTRY_02 */
static cfstore_kv_data_t cfstore_create_test_01_data_step_02[] = {
        CFSTORE_CREATE_TEST_01_TABLE_HEAD_ENTRY_01,
        CFSTORE_CREATE_TEST_01_TABLE_HEAD_ENTRY_02,
        CFSTORE_CREATE_TEST_01_TABLE_HEAD_ENTRY_03,
        CFSTORE_CREATE_TEST_01_TABLE_MID_ENTRY_02,
        CFSTORE_CREATE_TEST_01_TABLE_TAIL_ENTRY_01,
        CFSTORE_CREATE_TEST_01_TABLE_TAIL_ENTRY_02,
        CFSTORE_CREATE_TEST_01_TABLE_TAIL_ENTRY_03,
        CFSTORE_CREATE_TEST_01_TABLE_TAIL_ENTRY_04,
        { NULL, NULL},
};

/* table 3: to CFSTORE_CREATE_TEST_01_TABLE_MID_ENTRY_02 shrunk to CFSTORE_CREATE_TEST_01_TABLE_MID_ENTRY_03 */
static cfstore_kv_data_t cfstore_create_test_01_data_step_03[] = {
        CFSTORE_CREATE_TEST_01_TABLE_HEAD_ENTRY_01,
        CFSTORE_CREATE_TEST_01_TABLE_HEAD_ENTRY_02,
        CFSTORE_CREATE_TEST_01_TABLE_HEAD_ENTRY_03,
        CFSTORE_CREATE_TEST_01_TABLE_MID_ENTRY_03,
        CFSTORE_CREATE_TEST_01_TABLE_TAIL_ENTRY_01,
        CFSTORE_CREATE_TEST_01_TABLE_TAIL_ENTRY_02,
        CFSTORE_CREATE_TEST_01_TABLE_TAIL_ENTRY_03,
        CFSTORE_CREATE_TEST_01_TABLE_TAIL_ENTRY_04,
        { NULL, NULL},
};

/* table 3: CFSTORE_CREATE_TEST_01_TABLE_MID_ENTRY_03 deleted */
static cfstore_kv_data_t cfstore_create_test_01_data_step_04[] = {
        CFSTORE_CREATE_TEST_01_TABLE_HEAD_ENTRY_01,
        CFSTORE_CREATE_TEST_01_TABLE_HEAD_ENTRY_02,
        CFSTORE_CREATE_TEST_01_TABLE_HEAD_ENTRY_03,
        CFSTORE_CREATE_TEST_01_TABLE_TAIL_ENTRY_01,
        CFSTORE_CREATE_TEST_01_TABLE_TAIL_ENTRY_02,
        CFSTORE_CREATE_TEST_01_TABLE_TAIL_ENTRY_03,
        CFSTORE_CREATE_TEST_01_TABLE_TAIL_ENTRY_04,
        { NULL, NULL},
};

/* support functions */

/* @brief   support function for generating value blob data */
static int32_t cfstore_create_kv_value_gen(char* value, const size_t len)
{
    size_t i = 0;
    size_t cpy_size = 0;

    CFSTORE_FENTRYLOG("%s:entered\n", __func__);
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_create_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: value pointer is null.\n", __func__);
    TEST_ASSERT_MESSAGE(value != NULL, cfstore_create_utest_msg_g);

    while(i < len)
    {
        cpy_size = len - i > CFSTORE_TEST_BYTE_DATA_TABLE_SIZE ? CFSTORE_TEST_BYTE_DATA_TABLE_SIZE : len - i;
        memcpy(value + i, cfstore_test_byte_data_table, cpy_size);
        i += cpy_size;
    }
    return ARM_DRIVER_OK;
}


static char* CFSTORE_CREATE_KV_CREATE_NO_TAG = NULL;

/* @brief
 * support function to create a KV
 * - a kv name is generated with the length name_len
 * - a kv value blob is generated with the length value_len
 *
 * @param   name_len    the length of the kv_name
 * @param   name_tag    tag to append to name, intended to enable large number of unique strings
 * @param   value_buf   buffer to use for storing the generated value data
 * @param   value_len   the length of the value to generate
 */
static int32_t cfstore_create_kv_create(size_t name_len, char* name_tag, char* value_buf, size_t value_len)
{
    int32_t ret = ARM_DRIVER_OK;
    size_t name_len_ex = name_len;
    char kv_name[CFSTORE_KEY_NAME_MAX_LENGTH+1];    /* extra char for terminating null */
    ARM_CFSTORE_KEYDESC kdesc;

    CFSTORE_FENTRYLOG("%s:entered\n", __func__);
    memset(kv_name, 0, CFSTORE_KEY_NAME_MAX_LENGTH+1);
    memset(&kdesc, 0, sizeof(kdesc));
    kdesc.drl = ARM_RETENTION_WHILE_DEVICE_ACTIVE;

    name_len_ex = name_len;
    if(name_tag){
        name_len_ex += strlen(name_tag);
    }
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_create_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: max supported KV name length for testing exceeded.\n", __func__);
    TEST_ASSERT_MESSAGE(name_len_ex < CFSTORE_KEY_NAME_MAX_LENGTH+1, cfstore_create_utest_msg_g);

    ret = cfstore_test_kv_name_gen(kv_name, name_len);
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_create_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: unable to generate kv_name.\n", __func__);
    TEST_ASSERT_MESSAGE(ret >= ARM_DRIVER_OK , cfstore_create_utest_msg_g);

    /* append name tag */
    if(name_tag){
        strncat(kv_name, name_tag, CFSTORE_KEY_NAME_MAX_LENGTH);
    }

    CFSTORE_TEST_UTEST_MESSAGE(cfstore_create_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: kv_name is not the correct length (name_len_ex=%d, expected=%d).\n", __func__, (int) strlen(kv_name), (int) name_len_ex);
    TEST_ASSERT_MESSAGE(strlen(kv_name) == name_len_ex, cfstore_create_utest_msg_g);

    ret = cfstore_create_kv_value_gen(value_buf, value_len);
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_create_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: unable to generate kv_name.\n", __func__);
    TEST_ASSERT_MESSAGE(ret >= ARM_DRIVER_OK , cfstore_create_utest_msg_g);

    ret = cfstore_test_create(kv_name, value_buf, &value_len, &kdesc);

    if(ret == ARM_CFSTORE_DRIVER_ERROR_OUT_OF_MEMORY){
        CFSTORE_ERRLOG("%s: Error: out of memory\n", __func__);
        return ret;
    }

    CFSTORE_TEST_UTEST_MESSAGE(cfstore_create_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: failed to create KV in store for kv_name_good(ret=%" PRId32 ").\n", __func__, ret);
    TEST_ASSERT_MESSAGE(ret >= ARM_DRIVER_OK, cfstore_create_utest_msg_g);

    return ret;
}


/* @brief   cfstore_create_test_01() support function change the size of a value blob in the cfstore */
static int32_t cfstore_create_test_KV_change(const cfstore_kv_data_t* old_node, const cfstore_kv_data_t* new_node )
{
    int32_t ret = ARM_DRIVER_ERROR;
    size_t len = 0;
    ARM_CFSTORE_DRIVER* drv = &cfstore_driver;
    ARM_CFSTORE_HANDLE_INIT(hkey);
    ARM_CFSTORE_FMODE flags;
    ARM_CFSTORE_KEYDESC kdesc;

    CFSTORE_DBGLOG("%s:entered\n", __func__);
    memset(&flags, 0, sizeof(flags));
    memset(&kdesc, 0, sizeof(kdesc));

    /* check node key_names are identical */
    if(strncmp(old_node->key_name, new_node->key_name, strlen(old_node->key_name)) != 0){
        CFSTORE_ERRLOG("%s:old and new entries so not have the same key_name (old_key_name=%s, new_key_name=%s).\n", __func__, old_node->key_name, new_node->key_name);
        return ret;
    }
    len = strlen(new_node->value);
    /* supply NULL key descriptor to open a pre-existing key for increasing the blob size */
    ret = drv->Create(new_node->key_name, len, NULL, hkey);
    if(ret < ARM_DRIVER_OK){
        CFSTORE_ERRLOG("%s:Error: failed to change size of KV (key_name=%s)(ret=%d).\n", __func__, new_node->key_name, (int) ret);
        goto out1;
    }
    len = strlen(new_node->value);
    ret = drv->Write(hkey, new_node->value, &len);
    if(ret < ARM_DRIVER_OK){
        CFSTORE_ERRLOG("%s:Error: failed to write KV (key_name=%s)(ret=%d).\n", __func__, new_node->key_name, (int) ret);
        goto out2;
    }
    if(len != strlen(new_node->value)){
        CFSTORE_DBGLOG("%s:Failed wrote (%d) rather than the correct number of bytes (%d).\n", __func__, (int) len, (int) strlen(cfstore_create_test_01_data[1].value));
        goto out2;
    }
out2:
    drv->Close(hkey);
out1:
    return ret;
}

/* report whether built/configured for flash sync or async mode */
static control_t cfstore_create_test_00(const size_t call_count)
{
    int32_t ret = ARM_DRIVER_ERROR;

    (void) call_count;
    ret = cfstore_test_startup();
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_create_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: failed to perform test startup (ret=%d).\n", __func__, (int) ret);
    TEST_ASSERT_MESSAGE(ret >= ARM_DRIVER_OK, cfstore_create_utest_msg_g);
    return CaseNext;
}


/**
 * @brief   test to change the value blob size of pre-existing key
 *
 * @notes
 *
 * The test does the following:
 * - creates a cfstore with ~10 entries.
 * - for a mid-cfstore entry, grow the value blob size
 * - check all the cfstore entries can be read correctly and their
 *   data agrees with the data supplied upon creation.
 * - grow the mid-entry value blob size to be ~double the initial size.
 * - check all the cfstore entries can be read correctly and their
 *   data agrees with the data supplied upon creation.
 *
 * @return  status code
 *          ARM_DRIVER_OK, the test passed successfully
 *          ret < ARM_DRIVER_OK, the test failed with the return code
 *          supplying more details
 */
static control_t cfstore_create_test_01_end(const size_t call_count)
{
    int32_t ret = ARM_DRIVER_ERROR;
    ARM_CFSTORE_FMODE flags;
    cfstore_kv_data_t* node = NULL;
    ARM_CFSTORE_DRIVER* drv = &cfstore_driver;

    CFSTORE_FENTRYLOG("%s:entered\n", __func__);
    (void) call_count;
    memset(&flags, 0, sizeof(flags));

    ret = cfstore_test_create_table(cfstore_create_test_01_data_step_01);
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_create_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Failed to add cfstore_create_test_01_data_head (ret=%" PRId32 ").\n", __func__, ret);
    TEST_ASSERT_MESSAGE(ret >= ARM_DRIVER_OK, cfstore_create_utest_msg_g);

    /* find cfstore_create_test_01_data[0] and grow the KV MID_ENTRY_01 to MID_ENTRY_02 */
    ret = cfstore_create_test_KV_change(&cfstore_create_test_01_data[0], &cfstore_create_test_01_data[1]);
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_create_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Failed to increase size of KV (ret=%" PRId32 ").\n", __func__, ret);
    TEST_ASSERT_MESSAGE(ret >= ARM_DRIVER_OK, cfstore_create_utest_msg_g);

    /* Now check that the KVs are all present and correct */
    node = cfstore_create_test_01_data_step_02;
    while(node->key_name != NULL)
    {
        ret = cfstore_test_check_node_correct(node);
        CFSTORE_TEST_UTEST_MESSAGE(cfstore_create_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:node (key_name=\"%s\", value=\"%s\") not correct in cfstore\n", __func__, node->key_name, node->value);
        TEST_ASSERT_MESSAGE(ret >= ARM_DRIVER_OK, cfstore_create_utest_msg_g);
        node++;
    }
    /* revert CFSTORE_LOG for more trace */
    CFSTORE_DBGLOG("KV successfully increased in size and other KVs remained unchanged.%s", "\n");
    /* Shrink the KV from KV MID_ENTRY_02 to MID_ENTRY_03 */
    ret = cfstore_create_test_KV_change(&cfstore_create_test_01_data[1], &cfstore_create_test_01_data[2]);
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_create_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Failed to decrease size of KV (ret=%" PRId32 ").\n", __func__, ret);
    TEST_ASSERT_MESSAGE(ret >= ARM_DRIVER_OK, cfstore_create_utest_msg_g);

    /* Now check that the KVs are all present and correct */
    node = cfstore_create_test_01_data_step_03;
    while(node->key_name != NULL)
    {
        ret = cfstore_test_check_node_correct(node);
        CFSTORE_TEST_UTEST_MESSAGE(cfstore_create_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:node (key_name=\"%s\", value=\"%s\") not correct in cfstore\n", __func__, node->key_name, node->value);
        TEST_ASSERT_MESSAGE(ret >= ARM_DRIVER_OK, cfstore_create_utest_msg_g);
        node++;
    }
    /* revert CFSTORE_LOG for more trace */
    CFSTORE_DBGLOG("KV successfully decreased in size and other KVs remained unchanged.%s", "\n");

    /* Delete the KV */
    ret = cfstore_test_delete(cfstore_create_test_01_data[2].key_name);
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_create_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:failed to delete node(key_name=\"%s\")\n", __func__, node->key_name);
    TEST_ASSERT_MESSAGE(ret >= ARM_DRIVER_OK, cfstore_create_utest_msg_g);

    /* Now check that the KVs are all present and correct */
    node = cfstore_create_test_01_data_step_04;
    while(node->key_name != NULL)
    {
        ret = cfstore_test_check_node_correct(node);
        CFSTORE_TEST_UTEST_MESSAGE(cfstore_create_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:node (key_name=\"%s\", value=\"%s\") not correct in cfstore\n", __func__, node->key_name, node->value);
        TEST_ASSERT_MESSAGE(ret >= ARM_DRIVER_OK, cfstore_create_utest_msg_g);
        node++;
    }
    ret = drv->Uninitialize();
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_create_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: Uninitialize() call failed.\n", __func__);
    TEST_ASSERT_MESSAGE(ret >= ARM_DRIVER_OK, cfstore_create_utest_msg_g);
    return CaseNext;
}


/**
 * @brief   create the 10 kvs.
 * @note
 * The amount of data store in the cfstore is as follows:
 * - 10 kvs
 * - kv name lengths are ~220 => ~ 2200 bytes
 * - value blob length is 1x256, 2x256, 3x256, ... 10x256)) = 256(1+2+3+4+..10) = 256*10*11/2 = 14080
 * - kv overhead = 8bytes/kv = 8 * 10 = 80bytes
 * - total = (220*10)+256*10*11/2 10*8 = 143800 bytes
 *
 *
 * @return  status code
 *          ARM_DRIVER_OK, the test passed successfully
 *          ret < ARM_DRIVER_OK, the test failed with the return code
 *          supplying more details
 */
static int32_t cfstore_create_test_02_core(const size_t call_count)
{
    int32_t ret = ARM_DRIVER_ERROR;
    uint32_t i = 0;
    uint32_t bytes_stored = 0;
    const uint32_t max_num_kvs_create = 10;
    const size_t kv_name_min_len = CFSTORE_KEY_NAME_MAX_LENGTH - max_num_kvs_create;
    const size_t kv_value_min_len = CFSTORE_TEST_BYTE_DATA_TABLE_SIZE;
    const size_t max_value_buf_size = kv_value_min_len * (max_num_kvs_create +1);
    char value_buf[max_value_buf_size];

    CFSTORE_FENTRYLOG("%s:entered\n", __func__);
    (void) call_count;
    memset(value_buf, 0, max_value_buf_size);

    for(i = 0; i < max_num_kvs_create; i++)
    {
        memset(value_buf, 0, max_value_buf_size);
        ret = cfstore_create_kv_create(kv_name_min_len +i, CFSTORE_CREATE_KV_CREATE_NO_TAG, value_buf, kv_value_min_len * (i+1));
        bytes_stored += kv_name_min_len + i;         /* kv_name */
        bytes_stored += kv_value_min_len * (i+1);    /* kv value blob */
        bytes_stored += 8;                           /* kv overhead */
        if(ret == ARM_CFSTORE_DRIVER_ERROR_OUT_OF_MEMORY){
            CFSTORE_ERRLOG("Out of memory on %" PRId32 "-th KV, trying to allocate memory totalling %" PRIu32 ".\n", i, bytes_stored);
            break;
        }
        CFSTORE_DBGLOG("Successfully stored %" PRId32 "-th KV bytes,  totalling %" PRIu32 ".\n", i, bytes_stored);
    }
    ret = cfstore_test_delete_all();
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_create_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: failed to delete_all() attributes to clean up after test (ret=%" PRId32 ").\n", __func__, ret);
    TEST_ASSERT_MESSAGE(ret >= ARM_DRIVER_OK, cfstore_create_utest_msg_g);
    return ret;
}

static control_t cfstore_create_test_02_end(const size_t call_count)
{
    int32_t ret;
    ARM_CFSTORE_DRIVER* drv = &cfstore_driver;

    CFSTORE_FENTRYLOG("%s:entered\n", __func__);
    (void) call_count;

    ret = cfstore_create_test_02_core(call_count);
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_create_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: something went wrong (ret=%" PRId32 ").\n", __func__, ret);
    TEST_ASSERT_MESSAGE(ret >= ARM_DRIVER_OK, cfstore_create_utest_msg_g);

    CFSTORE_TEST_UTEST_MESSAGE(cfstore_create_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: Uninitialize() call failed.\n", __func__);
    TEST_ASSERT_MESSAGE(drv->Uninitialize() >= ARM_DRIVER_OK, cfstore_create_utest_msg_g);
    return CaseNext;
}


static control_t cfstore_create_test_03_end(const size_t call_count)
{
    int32_t i = 0;
    int32_t ret;
    ARM_CFSTORE_DRIVER* drv = &cfstore_driver;

    CFSTORE_FENTRYLOG("%s:entered\n", __func__);
    for(i = 0; i < 100; i++)
    {
        ret = cfstore_create_test_02_core(call_count);
        CFSTORE_TEST_UTEST_MESSAGE(cfstore_create_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: something went wrong (ret=%" PRId32 ").\n", __func__, ret);
        TEST_ASSERT_MESSAGE(ret >= ARM_DRIVER_OK, cfstore_create_utest_msg_g);
        /* revert CFSTORE_LOG for more trace */
        CFSTORE_DBGLOG("Successfully completed create/destroy loop %" PRId32 ".\n", i);
    }
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_create_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: Uninitialize() call failed.\n", __func__);
    TEST_ASSERT_MESSAGE(drv->Uninitialize() >= ARM_DRIVER_OK, cfstore_create_utest_msg_g);
    return CaseNext;
}


/**
 * @brief   create the 100 kvs to make the device run out of memory
 * @note
 * The amount of data store in the cfstore is as follows:
 * - total = (220*100)+256*100*101/2 100*8 = 1315600 = 1.315x10^6
 *
 * @return  status code
 *          ARM_DRIVER_OK, the test passed successfully
 *          ret < ARM_DRIVER_OK, the test failed with the return code
 *          supplying more details
 */
static control_t cfstore_create_test_04_end(const size_t call_count)
{
    int32_t ret = ARM_DRIVER_ERROR;
    uint32_t i = 0;
    uint32_t bytes_stored = 0;
    const uint32_t max_num_kvs_create = 100;
    const size_t kv_name_min_len = CFSTORE_KEY_NAME_MAX_LENGTH - max_num_kvs_create;
    const size_t kv_value_min_len = CFSTORE_TEST_BYTE_DATA_TABLE_SIZE;
    const size_t max_value_buf_size = kv_value_min_len/8 * (max_num_kvs_create +1);
    char* value_buf = NULL;
    ARM_CFSTORE_DRIVER* drv = &cfstore_driver;

    CFSTORE_FENTRYLOG("%s:entered\n", __func__);
    (void) call_count;
    value_buf = (char*) malloc(max_value_buf_size);
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_create_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: out of memory.\n", __func__);
    TEST_ASSERT_MESSAGE(value_buf != NULL, cfstore_create_utest_msg_g);

    for(i = 0; i < max_num_kvs_create; i++)
    {
        memset(value_buf, 0, max_value_buf_size);
        ret = cfstore_create_kv_create(kv_name_min_len +i, CFSTORE_CREATE_KV_CREATE_NO_TAG, value_buf, kv_value_min_len/8 * (i+1));
        bytes_stored += kv_name_min_len + i;         /* kv_name */
        bytes_stored += kv_value_min_len/8 * (i+1);  /* kv value blob */
        bytes_stored += 8;                           /* kv overhead */
        if(ret == ARM_CFSTORE_DRIVER_ERROR_OUT_OF_MEMORY){
            CFSTORE_ERRLOG("Out of memory on %" PRId32 "-th KV, trying to allocate memory totalling %" PRIu32 ".\n", i, bytes_stored);
            break;
        }
        /* revert CFSTORE_LOG for more trace */
        CFSTORE_DBGLOG("Successfully stored %" PRId32 "-th KV bytes,  totalling %" PRIu32 ".\n", i, bytes_stored);
    }
    ret = cfstore_test_delete_all();
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_create_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: failed to delete_all() attributes to clean up after test (ret=%" PRId32 ").\n", __func__, ret);
    TEST_ASSERT_MESSAGE(ret >= ARM_DRIVER_OK, cfstore_create_utest_msg_g);
    free(value_buf);
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_create_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: Uninitialize() call failed.\n", __func__);
    TEST_ASSERT_MESSAGE(drv->Uninitialize() >= ARM_DRIVER_OK, cfstore_create_utest_msg_g);
    return CaseNext;
}

/**
 * @brief   create the 500 kvs.
 * @note
 * The amount of data store in the cfstore is as follows:
 * - total = (220*500)+(256/64)*500*501/2 500*8 = 8236000 = 8.236M
 *
 * @return  status code
 *          ARM_DRIVER_OK, the test passed successfully
 *          ret < ARM_DRIVER_OK, the test failed with the return code
 *          supplying more details
 */
static control_t cfstore_create_test_05_end(const size_t call_count)
{
    int32_t ret = ARM_DRIVER_ERROR;
    uint32_t i = 0;
    uint32_t bytes_stored = 0;
    const uint32_t max_num_kvs_create = 200;
    const size_t kv_name_tag_len = 3;
    const size_t kv_name_min_len = 10;
    const size_t kv_value_min_len = CFSTORE_TEST_BYTE_DATA_TABLE_SIZE;
    const size_t max_value_buf_size = kv_value_min_len/64 * (max_num_kvs_create+1);
    char kv_name_tag_buf[kv_name_tag_len+1];
    char* value_buf = NULL;
    ARM_CFSTORE_DRIVER* drv = &cfstore_driver;

    CFSTORE_FENTRYLOG("%s:entered\n", __func__);
    (void) call_count;
    value_buf = (char*) malloc(max_value_buf_size);
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_create_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: out of memory.\n", __func__);
    TEST_ASSERT_MESSAGE(value_buf != NULL, cfstore_create_utest_msg_g);

    for(i = 0; i < max_num_kvs_create; i++)
    {
        memset(value_buf, 0, max_value_buf_size);
        snprintf(kv_name_tag_buf, kv_name_tag_len+1, "%0d", (int) i);
        ret = cfstore_create_kv_create(kv_name_min_len, kv_name_tag_buf, value_buf, kv_value_min_len/64 * (i+1));
        bytes_stored += kv_name_min_len + i + strlen(kv_name_tag_buf);         /* kv_name */
        bytes_stored += kv_value_min_len/64 * (i+1);                           /* kv value blob */
        bytes_stored += 8;                                                     /* kv overhead */
        if(ret == ARM_CFSTORE_DRIVER_ERROR_OUT_OF_MEMORY){
            CFSTORE_ERRLOG("Out of memory on %" PRId32 "-th KV, trying to allocate memory totalling %" PRIu32 ".\n", i, bytes_stored);
            break;
        }
        /* revert CFSTORE_LOG for more trace */
        CFSTORE_DBGLOG("Successfully stored %" PRId32 "-th KV bytes,  totalling %" PRIu32 ".\n", i, bytes_stored);
    }
    ret = cfstore_test_delete_all();
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_create_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: failed to delete_all() attributes to clean up after test.\n", __func__);
    TEST_ASSERT_MESSAGE(ret >= ARM_DRIVER_OK, cfstore_create_utest_msg_g);
    free(value_buf);
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_create_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: Uninitialize() call failed.\n", __func__);
    TEST_ASSERT_MESSAGE(drv->Uninitialize() >= ARM_DRIVER_OK, cfstore_create_utest_msg_g);
    return CaseNext;
}


typedef struct cfstore_create_key_name_validate_t {
    const char* key_name;
    uint32_t f_allowed : 1;
} cfstore_create_key_name_validate_t;

cfstore_create_key_name_validate_t cfstore_create_test_06_data[] = {
        /* ruler for measuring text strings */
        /*                                                                                                    1         1         1         1         1         1         1         1         1         1         2         2         2 */
        /* 0        1         2         3         4         5         6         7         8         9         0         1         2         3         4         5         6         7         8         9         0         1         2 */
        /* 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890 */
        { "",  false},
        { "abc.{1}.efg", true },
        { "abc.{1.efg", false },
        { "abc.1}.efg", false },
        { "abc.{{1}}.efg", false },
        { "abc.{}.efg", true },
        { "abc.}1{.efg", false },
        { ".piety.demands.us.to.honour.truth.above.our.friends", false },
        { "basement.medicine.pavement.government.trenchcoat.off.cough.off.kid.did.when.again.alleyway.friend.cap.pen.dollarbills.ten.foot.soot.put.but.anyway.say.May.DA.kid.did.toes.bows.those.hose.nose.clothes.man.blows.{100000000}", false },
        { NULL, false},
};


/**
 * @brief   function to test whether a key name can be created or not
 *
 * @param	key_name
 * 			name of the key to create in the store
 * @param	should_create
 * 			if true, then create KV should succeed, otherwise should fail.
 *
 * @return  status code
 *          ARM_DRIVER_OK, the test passed successfully
 *          ret < ARM_DRIVER_OK, the test failed with the return code
 *          supplying more details
 */
bool cfstore_create_key_name_validate(const char *key_name, bool should_create)
{
    bool bret = false;
    char* test_data = (char*) "test_data";
    int32_t ret = ARM_DRIVER_ERROR;
    ARM_CFSTORE_SIZE len = 0;
    ARM_CFSTORE_KEYDESC kdesc;

    CFSTORE_FENTRYLOG("%s:entered\r\n", __func__);
    memset(&kdesc, 0, sizeof(kdesc));

    /* create */
    kdesc.drl = ARM_RETENTION_WHILE_DEVICE_ACTIVE;
    len = strlen(test_data);
    ret = cfstore_test_create((const char*) key_name, test_data, &len, &kdesc);
    /* dont not use any functions that require finding the created item as they may not work,
     * depending on the construction of the test key_name & match strings */
    if(should_create == true)
    {
        if(ret < ARM_DRIVER_OK){
            CFSTORE_ERRLOG("%s:Error: failed to create kv (key_name=%s.\r\n", __func__, key_name);
            return bret;
        }
        CFSTORE_DBGLOG("%s:Success: Create() behaved as expected.\r\n", __func__);
        /* delete using the actual name */
        ret = cfstore_test_delete((const char*) key_name);
        if(ret < ARM_DRIVER_OK){
            CFSTORE_ERRLOG("%s:Error: failed to delete kv (key_name=%s)(ret=%d).\r\n", __func__, key_name, (int)ret);
        }
        bret = true;
    }
    else
    {
        if(ret >= ARM_DRIVER_OK){
            CFSTORE_ERRLOG("%s:Error: created kv (key_name=%s) when Create() should have failed.\r\n", __func__, key_name);
            return bret;
        }
        /* the operation failed which was the expected result hence return true*/
        bret = true;
    }
    return bret;
}

/**
 * @brief   check that key names with non-matching braces etc do no get created.
 *
 * @return  status code
 *          ARM_DRIVER_OK, the test passed successfully
 *          ret < ARM_DRIVER_OK, the test failed with the return code
 *          supplying more details
 */
static control_t cfstore_create_test_06_end(const size_t call_count)
{
    bool ret = false;
    int32_t ret32 = ARM_DRIVER_ERROR;
    ARM_CFSTORE_DRIVER* drv = &cfstore_driver;
    cfstore_create_key_name_validate_t* node = cfstore_create_test_06_data;

    (void) call_count;

    while(node->key_name != NULL)
    {
        ret = cfstore_create_key_name_validate(node->key_name, node->f_allowed);
        CFSTORE_TEST_UTEST_MESSAGE(cfstore_create_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: test failed (ret=%d, key_name=%s, f_allowed=%d)\n", __func__, (int) ret, node->key_name, node->f_allowed);
        TEST_ASSERT_MESSAGE(ret == true, cfstore_create_utest_msg_g);
        node++;
    }

    ret32 = drv->Uninitialize();
    CFSTORE_TEST_UTEST_MESSAGE(cfstore_create_utest_msg_g, CFSTORE_UTEST_MSG_BUF_SIZE, "%s:Error: Uninitialize() call failed.\n", __func__);
    TEST_ASSERT_MESSAGE(ret32 >= ARM_DRIVER_OK, cfstore_create_utest_msg_g);
    return CaseNext;
}

utest::v1::status_t greentea_setup(const size_t number_of_cases)
{
    GREENTEA_SETUP(CFSTORE_CREATE_GREENTEA_TIMEOUT_S, "default_auto");
    return greentea_test_setup_handler(number_of_cases);
}

Case cases[] = {
           /*          1         2         3         4         5         6        7  */
           /* 1234567890123456789012345678901234567890123456789012345678901234567890 */
        Case("CREATE_test_00", cfstore_create_test_00),
        Case("CREATE_test_01_start", cfstore_utest_default_start),
        Case("CREATE_test_01_end", cfstore_create_test_01_end),
        Case("CREATE_test_02_start", cfstore_utest_default_start),
        Case("CREATE_test_02_end", cfstore_create_test_02_end),
        Case("CREATE_test_03_start", cfstore_utest_default_start),
        Case("CREATE_test_03_end", cfstore_create_test_03_end),
        Case("CREATE_test_04_start", cfstore_utest_default_start),
        Case("CREATE_test_04_end", cfstore_create_test_04_end),
        Case("CREATE_test_05_start", cfstore_utest_default_start),
        Case("CREATE_test_05_end", cfstore_create_test_05_end),
        Case("CREATE_test_06_start", cfstore_utest_default_start),
        Case("CREATE_test_06_end", cfstore_create_test_06_end),
};


/* Declare your test specification with a custom setup handler */
Specification specification(greentea_setup, cases);

#if defined CFSTORE_CONFIG_MBED_OS_VERSION && CFSTORE_CONFIG_MBED_OS_VERSION == 3
/* mbedosV3*/
void app_start(int argc __unused, char** argv __unused)
{
    /* Run the test specification */
    Harness::run(specification);
}
#endif /* CFSTORE_CONFIG_MBED_OS_VERSION == 3 */

#if defined CFSTORE_CONFIG_MBED_OS_VERSION && CFSTORE_CONFIG_MBED_OS_VERSION == 4
/* mbedosV3++*/
int main()
{
    return !Harness::run(specification);
}
#endif /* CFSTORE_CONFIG_MBED_OS_VERSION == 4 */


#endif // __MBED__ && ! defined TOOLCHAIN_GCC_ARM