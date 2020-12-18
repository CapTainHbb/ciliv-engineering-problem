#pragma once
#include <string>
#include "Pipe.h"

class Pipe;

class Joint
{
public:
	Joint();

	// setters
	void set_type_name(std::string);
	void set_langar_value(double);
	void set_force_value(double);
	void set_right_pipe(Pipe*);
	void set_left_pipe(Pipe*);
	void set_left_joint(Joint*);
	void set_right_joint(Joint*);

	// getters
	std::string get_type_name() const;
	double get_langar_value() const;
	double get_force_value() const;
	const Pipe* get_left_pipe_ptr() const;
	const Pipe* get_right_pipe_ptr() const;
	const Joint* get_right_joint_ptr() const;
	const Joint* get_left_joint_ptr() const;

	// input from user
	void get_input_from_user();


private:
	std::string type_name{ "" }; // mafsali, girdar, azad
	double langar_value{};
	double force_value{};
	Pipe* left_pipe_ptr{ nullptr }, * right_pipe_ptr{ nullptr };
	Joint* left_joint_ptr{ nullptr }, * right_joint_ptr{ nullptr };
};

