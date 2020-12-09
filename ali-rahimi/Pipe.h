#pragma once
#include <string>
#include <array>
#include "Joint.h"

class Pipe
{
public:
	Pipe( Joint* left_joint, Joint* right_joint);

	// setters
	void set_length(double);
	void set_strength(double);
	void set_force(double);
	void set_wide_force_range(double, double);
	void set_force_spot(double);
	void set_langar_spot(double);
	void set_langar_value(double);
	void set_left_df(double);
	void set_right_df(double);
	void set_force_type(std::string);
	void set_left_joint_ptr(Joint*);
	void set_right_joint_ptr(Joint*);

	// getters
	double get_length() const;
	double get_strength() const;
	double get_force() const;
	std::array<double, 2> get_wide_force_range() const;
	double get_force_spot() const;
	double get_langar_spot() const;
	double get_langar_value() const;
	double get_left_df() const;
	double get_right_df() const;
	std::string get_force_type() const;
	const Joint* get_left_joint_ptr() const;
	const Joint* get_right_joint_ptr() const;



	~Pipe();

private:
	double length{0}, strength{0}, force{0};
	std::array<double, 2> wide_force_range{ 0, 0 };
	double force_spot{ 0 }, langar_spot{ 0 }, langar_value{ 0 };
	double left_fem{ 0 }, right_fem{ 0 };
	double left_df{ 0 }, right_df{ 0 };
	std::string force_type{ "" };
	Joint* left_joint_ptr{ nullptr }, * right_joint_ptr{ nullptr };
	double k{ 0 };

};

Pipe::Pipe(Joint* left_joint_ptr, Joint* right_joint_ptr)
{
	set_left_joint_ptr(left_joint_ptr);
	set_right_joint_ptr(right_joint_ptr);
}

Pipe::~Pipe()
{
}
