#include <stdexcept>
#include <iostream>
#include "Joint.h"
#include "Pipe.h"
using namespace std;

// constructors
Joint::Joint() { }

// setters
void Joint::set_type_name(string type_name)
{
	if ("mafsali" == type_name || "girdar" == type_name || "azad" == type_name) {
		this->type_name == type_name;
	}
	else
	{
		throw("please enter a valid type name! (masfali, girdar, azad)\n");
	}
}

void Joint::set_langar_value(double value){
	this->langar_value = value;
}

void Joint::set_force_value(double force_value) {
	this->force_value = force_value;
}

void Joint::set_right_pipe(Pipe* right_pipe){
	this->right_pipe_ptr = right_pipe;
}

void Joint::set_left_pipe(Pipe* left_pipe){
	this->left_pipe_ptr = left_pipe;
}

void Joint::set_left_joint(Joint* left_joint) {
	this->left_joint_ptr = left_joint;
}

void Joint::set_right_joint(Joint* right_joint) {
	this->right_joint_ptr = right_joint;
}



// getters
string Joint::get_type_name() const {
	return this->type_name;
}

double Joint::get_langar_value() const {
	return this->langar_value;
}

double Joint::get_force_value() const {
	return this->force_value;
}

const Pipe* Joint::get_left_pipe_ptr() const {
	return this->left_pipe_ptr;
}

const Pipe* Joint::get_right_pipe_ptr() const {
	return this->right_pipe_ptr;
}

const Joint* Joint::get_right_joint_ptr() const {
	return this->right_joint_ptr;
}

const Joint* Joint::get_left_joint_ptr() const {
	return this->left_joint_ptr;
}


// get input from user
void Joint::get_input_from_user() {
	string temp_str = "";
	double temp_double;

	
	cout << "\njoint type name:\t";
	cin >> temp_str;
	this->set_type_name(temp_str);
	cout << "has langar?(no,yes)\t";
	cin >> temp_str;
	if ("no" == temp_str)
		this->langar_value = 0;
	else if ("yes" == temp_str)
	{
		cout << "enter langar value:\t";
		cin >> temp_double;
		this->set_langar_value(temp_double);
	}
	else
	{
		cout << "????\n";
	}

	cout << "has force?(no,yes)\t";
	cin >> temp_str;
	if ("no" == temp_str)
		this->force_value = 0;
	else if ("yes" == temp_str)
	{
		cout << "enter force value:\t";
		cin >> temp_double;
		this->set_force_value(temp_double);
	}
	else
	{
		cout << "????\n";
	}


	
}