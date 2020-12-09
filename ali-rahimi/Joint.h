#pragma once
#include <string>
#include "Pipe.h"
class Joint
{
public:
	Joint(Pipe*, Pipe*);
	~Joint();

	// setters
	void set_type_name(std::string);
	void set_langar_value(double);
	void set_force_value(double);
	void set_co_value(double);
	void set_right_pipe(Pipe*);
	void set_left_pipe(Pipe*);

	// getters
	std::string get_type_name() const;
	double get_langar_value() const;
	double get_force_value() const;
	double get_co() const;
	const Pipe* get_left_pipe_ptr() const;
	const Pipe* get_right_pipe_ptr() const;


private:
	std::string type_name{ "" };
	double langar_value{};
	double force_value{};
	double co{};
	Pipe* left_pipe_ptr{ nullptr }, * right_pipe_ptr{ nullptr };
};

