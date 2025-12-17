#include <Arduino.h>
#include <Ethernet.h>
#include <SPI.h>
#include <MicroROS_Transport.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <std_msgs/msg/int32.h>
#include "genPublisher.h"
#include "genSubscriber.h"


// Define W5500 Ethernet Chip Pins
#define W5500_CS    14    // CS (Chip Select) PIN
#define W5500_RST   9     // Reset PIN
#define W5500_INT   10    // Interrupt PIN 
#define W5500_MISO  12    // MISO PIN
#define W5500_MOSI  11    // MOSI PIN
#define W5500_SCK   13    // Serial Clock PIN


// Define shared ROS entities
EthernetUDP udp;
rcl_allocator_t allocator;
rclc_support_t support;
rclc_executor_t executor;

rcl_node_t node;
const char * node_name = "node1";

genPublisher pub_bool1;
genPublisher pub_bool2;

genPublisher pub_int1;
genPublisher pub_int2;
genPublisher pub_int3;

genPublisher pub_double1;
genPublisher pub_double2;
genPublisher pub_double3;

genPublisher err_check;

genSubscriber sub_int1;
genSubscriber sub_bool1;
genSubscriber sub_doub1;

int int_val = 32;
bool bool_val = 32;
double doub_val = 32;

// Define Functions
void error_loop();
//Creates allocator abd support for namespace. Only one support should be made per namespace
void SetupSupport();
//pass node and name objects
void initNode(rcl_node_t * node, const char * node_name);
//inititates executor      
void initExecutor();

void SubscriptionCallback1(const void * msgin);
void SubscriptionCallback2(const void * msgin);
void SubscriptionCallback3(const void * msgin);

#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}     // Checks for Errors in Micro ROS Setup
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}              // 


// Network Configuration
byte esp_mac[] = { 0xDE, 0xAD, 0xAF, 0x91, 0x3E, 0x69 };    // Mac address of ESP32
IPAddress esp_ip(192, 168, 0, 14);                         // IP address of ESP32
IPAddress dns(192, 168, 0, 1);                              // DNS Server (Modify if necessary)
IPAddress gateway(192, 168, 0, 1);                          // Default Gateway (Modify if necessary)
IPAddress agent_ip(192, 168, 0, 80);                        // IP address of Micro ROS agent        
size_t agent_port = 8888;                                   // Micro ROS Agent Port Number

int value0;
int value1 = 0;
int value2;

bool boolswitch;
bool value3 = true;

double value4 = 0.69;
double value5 = 0;
double value6;

void setup() {

  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting Ethernet Connection... ");


  // Initialize SPI with custom pin configuration
  SPI.begin(W5500_SCK, W5500_MISO, W5500_MOSI, W5500_CS);


  // Select CS PIN and initialize Ethernet with static IP settings (Selecting CS PIN required for ESP32 as the ardiuno default is different)
  Ethernet.init(W5500_CS);

  // Start Micro ROS Transport Connection
  set_microros_eth_transports(esp_mac, esp_ip, agent_ip, agent_port);
  delay(2000);

  SetupSupport();
  initNode(&node,node_name);
  initExecutor();

  // pub_int1.init(&node, "Int32Stat", INT);
  // pub_int2.init(&node, "Int32Count", INT);
  // pub_int3.init(&node, "Int32Alt", INT);

  // pub_bool1.init(&node, "BoolStat", BOOL);
  // pub_bool2.init(&node, "BoolAlt", BOOL);

  // pub_double1.init(&node, "DoubleStat", DOUBLE);
  // pub_double2.init(&node, "DoubleCount", DOUBLE);
  // pub_double3.init(&node, "DoubleAlt", DOUBLE);

  // err_check.init(&node, "ErrTest", DOUBLE);


  sub_int1.init(&node, "Int32Sub", &executor, INT);
  sub_bool1.init(&node, "BoolSub", &executor, BOOL);
  sub_doub1.init(&node, "DoubleSub", &executor, DOUBLE);

  // sub_int1.init(&node, "Int32Sub", &executor, &SubscriptionCallback1, INT);
  // sub_bool1.init(&node, "BoolSub", &executor, &SubscriptionCallback2, BOOL);
  // sub_doub1.init(&node, "DoubleSub", &executor, &SubscriptionCallback3, DOUBLE);
}

void SubscriptionCallback1(const void * msgin)
{
  // Cast received message to used type
  const std_msgs__msg__Int32 * msg = (const std_msgs__msg__Int32 *)msgin;
  Serial.println(msg->data);
  Serial.println("callback1");
}
void SubscriptionCallback2(const void * msgin)
{
  // Cast received message to used type
  const std_msgs__msg__Int32 * msg = (const std_msgs__msg__Int32 *)msgin;
  Serial.println(msg->data);
  Serial.println("callback2");
}
void SubscriptionCallback3(const void * msgin)
{
  // Cast received message to used type
  const std_msgs__msg__Int32 * msg = (const std_msgs__msg__Int32 *)msgin;
  Serial.println(msg->data);
  Serial.println("callback3");
}


void loop() {
  Serial.println("heartbeat");

  delay(1000);
  
  // // Publishing static integer values
  // pub_int1.publish(69);

  // // Publishing integer values counting up
  // pub_int2.publish(&value1);

  // value1++;

  // // Publishing alternating integer values
  // value2 = 10;
  // pub_int3.publish(&value2);

  // delay(1000);

  // value2 = 20;
  // pub_int3.publish(&value2);

  // // Publishing Static Boolean values
  // pub_bool1.publish(&value3);

  // // Publishing Alternating Boolean values
  // boolswitch = true;
  // pub_bool2.publish(&boolswitch);

  // delay(1000);

  // boolswitch = false;
  // pub_bool2.publish(boolswitch);

  // // Publishing Static Double values
  // pub_double1.publish(value4);

  // // Publishing Double values counting up
  // pub_double2.publish(value5);

  // value5 += 0.1;

  // // Publishing Alternating Double values
  // value6 = 0.2;
  // pub_double3.publish(value6);

  // delay(1000);

  // value6 = 0.4;
  // pub_double3.publish(value6);


  

  rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));

}

void SetupSupport(){
  allocator = rcl_get_default_allocator();
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));
}
void initNode(rcl_node_t * node, const char * node_name){
  // Create node object
  RCCHECK(rclc_node_init_default(node, node_name, "", &support));
}
void initExecutor(){
  RCCHECK(rclc_executor_init(&executor, &support.context, 10, &allocator)); //number of subscibers the executor handles is hard coded atm
}