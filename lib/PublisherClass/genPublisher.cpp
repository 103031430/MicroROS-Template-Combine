#include "genPublisher.h"
#include "datatype.h"


genPublisher::genPublisher(){}

#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();} }
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){} }
void error_loop();

void genPublisher::init(rcl_node_t * node, const char * topic, DataType datatype){
    this->topic_name = topic;
    switch (datatype) {
        case DataType::BOOL:
            
            rclc_publisher_init_best_effort(
                &publisher,
                node,
                ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Bool),
                topic_name
            );

        break;

        case DataType::INT:
            
            rclc_publisher_init_best_effort(
                &publisher,
                node,
                ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
                topic_name
            );

            
        break;

        case DataType::DOUBLE:

            rclc_publisher_init_best_effort(
                &publisher,
                node,
                ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float64),
                topic_name
            );
            break;

        default:
            while (1)
            {
                delay(2000);
                Serial.println("ERROR: Code doesn't work.");
            }
        break;
    }
};

void genPublisher::publish(int data) {
    std_msgs__msg__Int32 msg_int;
    msg_int.data = data;  // Assign to the message
    RCCHECK(rcl_publish(&publisher, &msg_int, NULL));

}

void genPublisher::publish(bool data) {
    std_msgs__msg__Bool msg_bool;
    msg_bool.data = data;  // Assign to the message
    RCCHECK(rcl_publish(&publisher, &msg_bool, NULL));

}

void genPublisher::publish(double data) {
    std_msgs__msg__Float64 msg_doub;
    msg_doub.data = data;  // Assign to the message
    RCCHECK(rcl_publish(&publisher, &msg_doub, NULL));

}

// Error handle loop
void error_loop() {
  while(1) {
    delay(1000);
    Serial.println("error loop :(");
    }
};


