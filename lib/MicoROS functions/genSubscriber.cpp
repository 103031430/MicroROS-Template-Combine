#include "genSubscriber.h"
#include "datatype.h"

genSubscriber::genSubscriber(){}

void genSubscriber::init(rcl_node_t * node, const char * topic, rclc_executor_t * executor, DataType datatype){
    this->topic_name = topic;
    this->datatype = datatype;

    switch (datatype) {
        case INT:
            rclc_subscription_init_default(
                &subscriber,
                node,
                ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
                topic_name
            );

            rclc_executor_add_subscription(executor, &subscriber, &msg.intmsg, &Int32Callback, ON_NEW_DATA);

        break;

        case DOUBLE:
            rclc_subscription_init_default(
                &subscriber,
                node,
                ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float64),
                topic_name
            );

            rclc_executor_add_subscription(executor, &subscriber, &msg.doublemsg, &DoubleCallback, ON_NEW_DATA);

        break;

        case BOOL:
            rclc_subscription_init_default(
                &subscriber,
                node,
                ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Bool),
                topic_name
            );

            rclc_executor_add_subscription(executor, &subscriber, &msg.boolmsg, &BooleanCallback, ON_NEW_DATA);

        break;


        default:
            Serial.println("ERROR: Subscriber initialisation has failed!");
        break;
    }

    
}

void genSubscriber::Int32Callback(const void * msgin)
{
  // Cast received message to used type
  const std_msgs__msg__Int32 * msg_int = (const std_msgs__msg__Int32 *)msgin;
  Serial.print("Integer value: ");
  Serial.println(msg_int->data);
}

void genSubscriber::BooleanCallback(const void * msgin)
{
  // Cast received message to used type
  const std_msgs__msg__Bool * msg_bool = (const std_msgs__msg__Bool *)msgin;
  Serial.print("Boolean value: ");
  Serial.println(msg_bool->data);
}

void genSubscriber::DoubleCallback(const void * msgin)
{
  // Cast received message to used type
  const std_msgs__msg__Float64 * msg_double = (const std_msgs__msg__Float64 *)msgin;
  Serial.print("Double value: ");
  Serial.println(msg_double->data);
}


