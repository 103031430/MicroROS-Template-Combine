#include "genPublisher.h"
#include "datatype.h"


genPublisher::genPublisher(){}


void genPublisher::init(rcl_node_t * node, const char * topic, DataType datatype){
    this->topic_name = topic;
    switch (datatype) {
        case DataType::BOOL:
            
            rclc_publisher_init_default(
                &publisher,
                node,
                ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Bool),
                topic_name
            );

        break;

        case DataType::INT32:
            
            rclc_publisher_init_default(
                &publisher,
                node,
                ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
                topic_name
            );

            
        break;

        case DataType::DOUBLE:

            rclc_publisher_init_default(
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
}

void genPublisher::publish(int data) {
    std_msgs__msg__Int32 msg;
    msg.data = data;  // Assign to the message
    rcl_publish(&publisher, &msg, NULL);

}

void genPublisher::publish(bool data) {
    std_msgs__msg__Bool msg;
    msg.data = data;  // Assign to the message
    rcl_publish(&publisher, &msg, NULL);

}

void genPublisher::publish(double data) {
    std_msgs__msg__Float64 msg;
    msg.data = data;  // Assign to the message
    rcl_publish(&publisher, &msg, NULL);

}
