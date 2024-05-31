#include "xarm_planner/xarm_planner.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

void exit_sig_handler(int signum)
{
    fprintf(stderr, "[test_xarm_planner_api_pose] Ctrl-C caught, exit process...\n");
    exit(-1);
}

int main(int argc, char** argv)
{

    rclcpp::init(argc, argv);
    rclcpp::NodeOptions node_options;
    node_options.automatically_declare_parameters_from_overrides(true);
    shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("test_xarm_planner_api_pose", node_options);
    RCLCPP_INFO(node->get_logger(), "test_xarm_planner_api_pose start");

    signal(SIGINT, exit_sig_handler);

    int dof;
    node->get_parameter_or("dof", dof, 6);
    string robot_type;
    node->get_parameter_or("robot_type", robot_type, string("xarm"));
    string group_name = robot_type;
    if (robot_type == "xarm" || robot_type == "lite")
        group_name = robot_type + to_string(dof);
    string prefix;
    node->get_parameter_or("prefix", prefix, string(""));
    if (prefix != "") {
        group_name = prefix + group_name;
    }

    RCLCPP_INFO(node->get_logger(), "namespace: %s, group_name: %s", node->get_namespace(), group_name.c_str());

    xarm_planner::XArmPlanner planner(node, group_name);

    string line;



    geometry_msgs::msg::Pose target_pose;   
    float valor1 = 0.0;
    float valor2 = 0.0;
    float valor3 = 0.0;

    while (rclcpp::ok())
    {
	    ifstream infile("/home/dfray1367/prueba.txt");
	    if (!infile){
		cerr << "No se pudo abrir el archivo prueba.txt" << endl;
		return-1;
	    }
	    
	    
	    if (getline(infile, line))
	    {
		stringstream ss(line);
		string item;

		getline(ss,item,',');
		valor1 = stof(item);

		getline(ss,item,',');
		valor2 = stof(item);

		getline(ss,item);
		valor3 = stof(item);
		
		cout << valor1 << " " << valor2 << " " << valor3 << endl;
		cout << "Prueva";

	    }
	    infile.seekg(0, infile.beg);


	    target_pose.position.x = valor1;
	    target_pose.position.y = valor2;
	    target_pose.position.z = valor3;
	    target_pose.orientation.x = 1;
	    target_pose.orientation.y = 0;
	    target_pose.orientation.z = 0;
	    target_pose.orientation.w = 0;

	    planner.planPoseTarget(target_pose);
            planner.executePath();
    }

    RCLCPP_INFO(node->get_logger(), "test_xarm_planner_api_pose over");
    return 0;
}