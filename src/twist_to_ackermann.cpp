#include <iostream>
#include <vector>
#include <cmath>
#include <string>

#include <ros/ros.h>
#include <std_msgs/Header.h>
#include <std_msgs/Float64.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Vector3.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
// /*
// class TwistToAackermann {
//     public:
//         TwistToAackermann()
//         {
//         //Topic you want to publish 
//         pubLeftWheelHinge_ = n_.advertise<std_msgs::Float64>("/vehicle_v1/front_left_rev_controller/command", 1);
//         pubRightWheelHinge_ = n_.advertise<std_msgs::Float64>("/vehicle_v1/front_right_rev_controller/command", 1);
//         pubLeftWheelRotate_ = n_.advertise<std_msgs::Float64>("/vehicle_v1/front_left_cont_controller/command", 1);
//         pubRightWheelRotate_ = n_.advertise<std_msgs::Float64>("/vehicle_v1/front_right_cont_controller/command", 1); 

//         //Topic you want to subscribe
//         sub_ = n_.subscribe("/cmd_vel", 2, &TwistToAackermann::callback, this);
//         }

        
//     private:
//         ros::NodeHandle n_;
//         ros::Publisher pubLeftWheelHinge_;
//         ros::Publisher pubRightWheelHinge_;
//         ros::Publisher pubLeftWheelRotate_;
//         ros::Publisher pubRightWheelRotate_; 
//         ros::Subscriber sub_;

//     /*
//     ** The Gazebo JointVelocityController that spins the front wheels receives 
//     ** an angular velocity, Radians per second, so we use this method to 
//     ** convert the linear velocity into angular velocity by dividing it by
//     ** the wheel radius, giving radians per second instead of meters per second. 
//     */
    
// };*/
using namespace std;

float linearToAngularVelocity(float linearVelocity, float radius) {
        return linearVelocity/radius;            
    }
ros::Publisher pubLeftWheelHinge_;
        ros::Publisher pubRightWheelHinge_;
        ros::Publisher pubLeftWheelRotate_;
        ros::Publisher pubRightWheelRotate_;  
void callback(geometry_msgs::Twist msg) {
        // printf("HHHH\n");
        // std::cout << "Asdasdasd" << std::endl;
        // Vehicle wheel base geometry. wheelBase is the distance between front
        // and back axles, track is the distance between left and right wheels.    
        double wheelBase = 0.26;
        double track = 0.1;
        double wheelRadius = 0.025;
        double MaxR = 3.81; 
        std_msgs::Float64 lwh; 
        std_msgs::Float64 rwh;
        std_msgs::Float64 lwr;
        std_msgs::Float64 rwr;
        double r = 0; 


        if (msg.angular.z==0 || msg.linear.x==0) {
            lwh.data = 0;
            rwh.data = 0;
            lwr.data = linearToAngularVelocity(msg.linear.x, wheelRadius);
            rwr.data = linearToAngularVelocity(msg.linear.x, wheelRadius);
        }
        else {
            // The radius of the turn.
            r = msg.linear.x/msg.angular.z; 
            ROS_DEBUG("%f\n", r); 
            //if (r<MaxR && r>0) r = MaxR;
            //if (r>-MaxR && r<0) r = -MaxR;

            lwh.data = atan(wheelBase/(r-(track/2)));
            rwh.data = atan(wheelBase/(r+(track/2)));
            lwr.data = linearToAngularVelocity((r-(track/2))*msg.angular.z,wheelRadius);
            rwr.data = linearToAngularVelocity((r+(track/2))*msg.angular.z,wheelRadius);             }

        //double R = static_cast<double>(msg.linear.x/msg.angular.z); 
        ROS_DEBUG("Test"); 

        //pubADS_.publish(ads); 
        pubLeftWheelHinge_.publish(lwh);
        pubRightWheelHinge_.publish(rwh); 
        pubLeftWheelRotate_.publish(lwr); 
        pubRightWheelRotate_.publish(rwr); 
    }
int main(int argc, char **argv) {
    ros::init(argc, argv, "twist_to_ackermann");
    // printf("HO0000000000000000000000000000000000\n");
    ros::NodeHandle nh;
    // TwistToAackermann SAPObject; 
    // printf("HO2122222222222222222222222222222222\n");

    pubLeftWheelHinge_ = nh.advertise<std_msgs::Float64>("/vehicle_v1/front_left_rev_controller/command", 2);
    pubRightWheelHinge_ = nh.advertise<std_msgs::Float64>("/vehicle_v1/front_right_rev_controller/command", 2);
    pubLeftWheelRotate_ = nh.advertise<std_msgs::Float64>("/vehicle_v1/front_left_cont_controller/command", 2);
    pubRightWheelRotate_ = nh.advertise<std_msgs::Float64>("/vehicle_v1/front_right_cont_controller/command", 2); 
// cout << "asdasdasd" << endl;
        //Topic you want to subscribe
    ros::Subscriber    sub_ = nh.subscribe("/asd", 2, callback);
    // cout << "asdasdasdddddddddddd\n";
    ros::spin(); 

    return 0; 
}