#pragma once
#include <string>
#include <array>
#include "Joint.h"

class Joint;

class Pipe
{
public:
	Pipe();

	// setters
	void set_length(double);
	void set_strength(double);
	void set_normal_force_value(double);
	void set_wide_force_range(double);
	void set_normal_force_spot(double);
	void set_langar_spot(double);
	void set_langar_value(double);
	void set_left_df(double);
	void set_right_df(double);
	void set_force_type(std::string);
	void set_left_joint_ptr(Joint*);
	void set_right_joint_ptr(Joint*);
	void set_k(double);

	// getters
	double get_length() const;
	double get_strength() const;
	double get_normal_force_value() const;
	double get_normal_force_spot() const;
	double get_langar_spot() const;
	double get_langar_value() const;
	double get_left_df() const;
	double get_right_df() const;
	std::string get_force_type() const;
	const Joint* get_left_joint_ptr() const;
	const Joint* get_right_joint_ptr() const;
	double get_k() const;

	// utility functions
	void calculate_fem();
	void calculate_k();
	void calculate_df();
	void calculate_co();
	bool if_is_special_state_left();
	bool if_is_special_state_right();


	// getting user input
	void get_input_from_user();


private:
	double length{0}, strength{0};
	struct 
	{
		double force_value{ 0 };
		double force_spot{ 0 };
	} normal_force;
	struct
	{
		double force_value{ 0 };
		double force_length{ 0 };
	} wide_force;
	struct
	{
		double langar_spot{ 0 };
		double langar_value{ 0 };
	} langar;
	struct {
		double left_fem{ 0 };
		double right_fem{ 0 };
	} fem;
	struct {
		double left_df{ 0 };
		double right_df{ 0 };
	} df;
	struct {
		double left;
		double right;
	} co;
	std::string force_type{ "" }; // wide_force, normal_force, langar
	Joint* left_joint_ptr{ nullptr }, * right_joint_ptr{ nullptr };
	double k{ 0 };
};


