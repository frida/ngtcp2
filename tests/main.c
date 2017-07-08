/*
 * ngtcp2
 *
 * Copyright (c) 2016 ngtcp2 contributors
 * Copyright (c) 2012 nghttp2 contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <stdio.h>
#include <string.h>
#include <CUnit/Basic.h>
/* include test cases' include files here */
#include "ngtcp2_pkt_test.h"
#include "ngtcp2_upe_test.h"
#include "ngtcp2_range_test.h"
#include "ngtcp2_rob_test.h"

static int init_suite1(void) { return 0; }

static int clean_suite1(void) { return 0; }

int main() {
  CU_pSuite pSuite = NULL;
  unsigned int num_tests_failed;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suite to the registry */
  pSuite = CU_add_suite("libngtcp2_TestSuite", init_suite1, clean_suite1);
  if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  if (!CU_add_test(pSuite, "pkt_decode_hd_long",
                   test_ngtcp2_pkt_decode_hd_long) ||
      !CU_add_test(pSuite, "pkt_decode_hd_short",
                   test_ngtcp2_pkt_decode_hd_short) ||
      !CU_add_test(pSuite, "pkt_decode_stream_frame",
                   test_ngtcp2_pkt_decode_stream_frame) ||
      !CU_add_test(pSuite, "pkt_decode_ack_frame",
                   test_ngtcp2_pkt_decode_ack_frame) ||
      !CU_add_test(pSuite, "pkt_decode_padding_frame",
                   test_ngtcp2_pkt_decode_padding_frame) ||
      !CU_add_test(pSuite, "pkt_encode_stream_frame",
                   test_ngtcp2_pkt_encode_stream_frame) ||
      !CU_add_test(pSuite, "pkt_encode_ack_frame",
                   test_ngtcp2_pkt_encode_ack_frame) ||
      !CU_add_test(pSuite, "pkt_encode_connection_close_frame",
                   test_ngtcp2_pkt_encode_connection_close_frame) ||
      !CU_add_test(pSuite, "pkt_adjust_pkt_num",
                   test_ngtcp2_pkt_adjust_pkt_num) ||
      !CU_add_test(pSuite, "upe_encode", test_ngtcp2_upe_encode) ||
      !CU_add_test(pSuite, "upe_encode_version_negotiation",
                   test_ngtcp2_upe_encode_version_negotiation) ||
      !CU_add_test(pSuite, "range_intersect", test_ngtcp2_range_intersect) ||
      !CU_add_test(pSuite, "range_cut", test_ngtcp2_range_cut) ||
      !CU_add_test(pSuite, "range_not_after", test_ngtcp2_range_not_after) ||
      !CU_add_test(pSuite, "rob_push", test_ngtcp2_rob_push) ||
      !CU_add_test(pSuite, "rob_data_at", test_ngtcp2_rob_data_at) ||
      !CU_add_test(pSuite, "rob_remove_prefix",
                   test_ngtcp2_rob_remove_prefix)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  num_tests_failed = CU_get_number_of_tests_failed();
  CU_cleanup_registry();
  if (CU_get_error() == CUE_SUCCESS) {
    return (int)num_tests_failed;
  } else {
    printf("CUnit Error: %s\n", CU_get_error_msg());
    return CU_get_error();
  }
}
