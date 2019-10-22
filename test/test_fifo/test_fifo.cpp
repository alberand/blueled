#include <unity.h>
#include <stdint.h>

#include <fifo.h>

// void setUp(void) {
// // set stuff up here
// }

// void tearDown(void) {
// // clean stuff up here
// }
//
//
#define BUFFER_SIZE 255

void test_size(void) {
    FIFO<uint8_t>* f = new FIFO<uint8_t>(BUFFER_SIZE);
    TEST_ASSERT_EQUAL(f->getsize(), BUFFER_SIZE);
}

void test_available(void){
    FIFO<uint8_t>* f = new FIFO<uint8_t>(BUFFER_SIZE);
    TEST_ASSERT_EQUAL(f->available(), 0);
    f->put(1);
    f->put(2);
    f->put(3);
    f->put(4);
    f->put(5);
    TEST_ASSERT_EQUAL(f->available(), 5);
}

void test_clear(void){
    FIFO<uint8_t>* f = new FIFO<uint8_t>(BUFFER_SIZE);
    TEST_ASSERT_EQUAL(f->available(), 0);
    f->put(1);
    f->put(2);
    f->put(3);
    f->put(4);
    f->put(5);
    TEST_ASSERT_EQUAL(f->available(), 5);
    f->clear();
    TEST_ASSERT_EQUAL(f->available(), 0);
    TEST_ASSERT_EQUAL(f->get(), 0);
}

void test_basic(void) {
    int count = 10;
    FIFO<uint32_t>* f = new FIFO<uint32_t>(BUFFER_SIZE);
    TEST_ASSERT_EQUAL(f->available(), 0);
    for(int i = 0; i < count; i++){
        f->put(i);
    }
    TEST_ASSERT_EQUAL(f->available(), count);
    for(int i = 0; i < count; i++){
        TEST_ASSERT_EQUAL(f->get(), i);
    }
}

void testsuite(){
    UNITY_BEGIN();
    RUN_TEST(test_size);
    RUN_TEST(test_available);
    RUN_TEST(test_clear);
    RUN_TEST(test_basic);
    UNITY_END();
}

#ifdef ARDUINO

#include <Arduino.h>

void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_size);
    RUN_TEST(test_available);
    RUN_TEST(test_clear);
    RUN_TEST(test_basic);
}

void loop() {
    // digitalWrite(13, HIGH);
    // delay(100);
    // digitalWrite(13, LOW);
    // delay(500);
    UNITY_END();
}

#else

int main(int argc, char** main){
    testsuite();

    return 0;
}

#endif
