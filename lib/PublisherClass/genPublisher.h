#ifndef GEN_PUBLISHER_H
#define GEN_PUBLISHER_H

#include <Arduino.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <std_msgs/msg/float64.h>
#include <std_msgs/msg/bool.h>
#include <std_msgs/msg/int32.h>
#include "datatype.h"



class genPublisher {
public:

    genPublisher();
    void init(rcl_node_t * node, const char * topic, DataType datatype);
    void publish(int data);
    void publish(bool data);
    void publish(double data);

private:
    rcl_publisher_t publisher;
    const char * topic_name;
    DataType datatype;

};

#endif // INT_PUBLISHER_H