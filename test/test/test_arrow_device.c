#include "unity.h"
#include <stdlib.h>
#include <string.h>
#include <config.h>
#include <arrow/gateway.h>
#include <arrow/device.h>
#include <sys/mem.h>
#include <data/property.h>
#include <json/json.h>
#include "mock_mac.h"

#define GATEWAY_UID GATEWAY_UID_PREFIX "-111213141516"
#define TEST_GATEWAY_HID "000TEST000"
#define DEVICE_UID GATEWAY_UID "-" DEVICE_UID_SUFFIX
static arrow_gateway_t _test_gateway;

void setUp(void) {
    char mac[6] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16};
    get_mac_address_ExpectAnyArgsAndReturn(0);
    get_mac_address_ReturnArrayThruPtr_mac(mac, 6);
    arrow_gateway_init(&_test_gateway);
    arrow_prepare_gateway(&_test_gateway);
    property_copy(&_test_gateway.hid, p_const(TEST_GATEWAY_HID));
}

void tearDown(void)
{
}

static arrow_device_t _test_device;

void test_device_init(void) {
    arrow_device_init(&_test_device);
    TEST_ASSERT_EQUAL_STRING(NULL, P_VALUE(_test_device.hid));
    TEST_ASSERT_EQUAL_STRING(NULL, P_VALUE(_test_device.gateway_hid));
    TEST_ASSERT_EQUAL_PTR(NULL, _test_device.info);
    TEST_ASSERT_EQUAL_STRING(NULL, P_VALUE(_test_device.name));
    TEST_ASSERT_EQUAL_PTR(NULL, _test_device.prop);
    TEST_ASSERT_EQUAL_STRING(NULL, P_VALUE(_test_device.softwareName));
    TEST_ASSERT_EQUAL_STRING(NULL, P_VALUE(_test_device.softwareVersion));
    TEST_ASSERT_EQUAL_STRING(NULL, P_VALUE(_test_device.type));
    TEST_ASSERT_EQUAL_STRING(NULL, P_VALUE(_test_device.uid));
}

void test_device_prepare( void ) {
    arrow_prepare_device(&_test_gateway, &_test_device);
    TEST_ASSERT_EQUAL_STRING(NULL, P_VALUE(_test_device.hid));
    TEST_ASSERT_EQUAL_STRING(TEST_GATEWAY_HID, P_VALUE(_test_device.gateway_hid));
    TEST_ASSERT_EQUAL_PTR(NULL, _test_device.info);
    TEST_ASSERT_EQUAL_PTR(NULL, _test_device.prop);
    TEST_ASSERT_EQUAL_STRING(DEVICE_NAME, P_VALUE(_test_device.name));
    TEST_ASSERT_EQUAL_STRING(DEVICE_SOFTWARE_NAME, P_VALUE(_test_device.softwareName));
    TEST_ASSERT_EQUAL_STRING(DEVICE_SOFTWARE_VERSION, P_VALUE(_test_device.softwareVersion));
    TEST_ASSERT_EQUAL_STRING(DEVICE_TYPE, P_VALUE(_test_device.type));
    TEST_ASSERT_EQUAL_STRING(DEVICE_UID, P_VALUE(_test_device.uid));
}
