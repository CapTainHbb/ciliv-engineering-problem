#include <stdexcept>
#include <cmath>
#include "Pipe.h"
#include "Joint.h"
using namespace std;

//constructors
Pipe::Pipe() {

}

// setters
void Pipe::set_length(double length){
	this->length = length;
}

void Pipe::set_strength(double strength){
	this->strength = strength;
}

void Pipe::set_normal_force_value(double force_value){
	this->normal_force.force_value = force_value;
}

void Pipe::set_normal_force_spot(double spot) {
	this->normal_force.force_spot = spot;
}

void Pipe::set_wide_force_range(double length) {
	this->wide_force.force_length = length;
}

void Pipe::set_langar_spot(double spot) {
	this->langar.langar_spot = spot;
}

void Pipe::set_langar_value(double value) {
	this->langar.langar_value = value;
}

void Pipe::set_left_df(double) {
}

void Pipe::set_right_df(double){}

void Pipe::set_force_type(std::string force_type){
	if ("langar" == force_type || "wide_force" == force_type || "normal_force" == force_type)
	{
		this->force_type = force_type;
	}
	else
	{
		throw("please enter a valid force type!(langar, wide_force, normal_force)\n");
	}
}

void Pipe::set_left_joint_ptr(Joint* left_joint) {
	this->left_joint_ptr = left_joint;
}

void Pipe::set_right_joint_ptr(Joint* right_joint){
	this->right_joint_ptr = right_joint;
}

void Pipe::set_k(double value) {
	this->k = value;
}

// getters
double Pipe::get_length() const { return this->length; }
double Pipe::get_strength() const { return this->strength; }
double Pipe::get_normal_force_value() const { return this->normal_force.force_value; }
double Pipe::get_normal_force_spot() const { return this->normal_force.force_spot; }
double Pipe::get_langar_spot() const { return langar.langar_spot; }
double Pipe::get_langar_value() const { return langar.langar_value; }
double Pipe::get_left_df() const { return df.left_df; }
double Pipe::get_right_df() const { return df.right_df; }

std::string Pipe::get_force_type() const {
	return this->force_type;
}

const Joint* Pipe::get_left_joint_ptr() const {
	return this->left_joint_ptr;
}

const Joint* Pipe::get_right_joint_ptr() const {
	return this->right_joint_ptr;
}

double Pipe::get_k() const {
	return this->k;
}

// utility functions
void Pipe::calculate_fem() {
	if ("normal_force" == this->force_type) {
		if (this->if_is_special_state_left()) // special  left state
		{
			// setting FEM(L)
			this->fem.left_fem = this->normal_force.force_value *
				this->normal_force.force_spot *
				pow(this->length - this->normal_force.force_spot, 2);
			this->fem.left_fem /= pow(this->length, 2);

			// setting FEM(R)
			this->fem.right_fem = this->normal_force.force_value *
				(this->length - this->normal_force.force_spot) *
				pow(this->normal_force.force_spot, 2);
			this->fem.right_fem /= -1 * pow(this->length, 2);

			// setting new values
			this->fem.right_fem = this->fem.right_fem - (this->fem.left_fem / 2);
			this->fem.left_fem = 0;
		}
		else if (this->if_is_special_state_right()) // special right state
		{
			// setting FEM(L)
			this->fem.left_fem = this->normal_force.force_value *
				this->normal_force.force_spot *
				pow(this->length - this->normal_force.force_spot, 2);
			this->fem.left_fem /= pow(this->length, 2);

			// setting FEM(R)
			this->fem.right_fem = this->normal_force.force_value *
				(this->length - this->normal_force.force_spot) *
				pow(this->normal_force.force_spot, 2);
			this->fem.right_fem /= -1 * pow(this->length, 2);

			// setting new values
			this->fem.left_fem = this->fem.left_fem - (this->fem.right_fem / 2);
			this->fem.right_fem = 0;
		}
		else
		{
			// setting FEM(L)
			this->fem.left_fem = this->normal_force.force_value *
				this->normal_force.force_spot *
				pow(this->length - this->normal_force.force_spot, 2);
			this->fem.left_fem /= pow(this->length, 2);

			// setting FEM(R)
			this->fem.right_fem = this->normal_force.force_value *
				(this->length - this->normal_force.force_spot) *
				pow(this->normal_force.force_spot, 2);
			this->fem.right_fem /= -1 * pow(this->length, 2);
		}
	}
	else if ("wide_force" == this->force_type) {
		if (this->if_is_special_state_left())
		{
			// setting FEM(L)
			this->fem.left_fem = this->wide_force.force_value * pow(this->wide_force.force_length, 2); // w * x^2
			this->fem.left_fem *= 6 * pow(this->length, 2) + 8 * this->wide_force.force_value * this->length + 3
				* pow(this->wide_force.force_length, 2);  // 6L^2 + 8XL + 3X^2
			this->fem.left_fem /= 12 * pow(this->length, 2);


			// setting FEM(R)
			this->fem.right_fem = -1 * this->wide_force.force_value * pow(this->wide_force.force_length, 2); // -w * x^2
			this->fem.right_fem *= 4 * this->length - 3 * this->wide_force.force_value; // 4L - 3X
			this->fem.right_fem /= 12 * pow(this->length, 2); // 12L^2

			// setting new values
			this->fem.right_fem = this->fem.right_fem - (this->fem.left_fem / 2);
			this->fem.left_fem = 0;
		}
		else if (this->if_is_special_state_right()) {
			// setting FEM(L)
			this->fem.left_fem = this->wide_force.force_value * pow(this->wide_force.force_length, 2); // w * x^2
			this->fem.left_fem *= 6 * pow(this->length, 2) + 8 * this->wide_force.force_value * this->length + 3
				* pow(this->wide_force.force_length, 2);  // 6L^2 + 8XL + 3X^2
			this->fem.left_fem /= 12 * pow(this->length, 2);

			// setting FEM(R)
			this->fem.right_fem = -1 * this->wide_force.force_value * pow(this->wide_force.force_length, 2); // -w * x^2
			this->fem.right_fem *= 4 * this->length - 3 * this->wide_force.force_value; // 4L - 3X
			this->fem.right_fem /= 12 * pow(this->length, 2); // 12L^2

			// setting new values
			this->fem.left_fem = this->fem.left_fem - (this->fem.right_fem / 2);
			this->fem.right_fem = 0;
		}
		else
		{
			// setting FEM(L)
			this->fem.left_fem = this->wide_force.force_value * pow(this->wide_force.force_length, 2); // w * x^2
			this->fem.left_fem *= 6 * pow(this->length, 2) + 8 * this->wide_force.force_value * this->length + 3
				* pow(this->wide_force.force_length, 2);  // 6L^2 + 8XL + 3X^2
			this->fem.left_fem /= 12 * pow(this->length, 2);


			// setting FEM(R)
			this->fem.right_fem = -1 * this->wide_force.force_value * pow(this->wide_force.force_length, 2); // -w * x^2
			this->fem.right_fem *= 4 * this->length - 3 * this->wide_force.force_value; // 4L - 3X
			this->fem.right_fem /= 12 * pow(this->length, 2); // 12L^2
		}
	}
	else if ("langar_spot" == this->force_type) {
		if (this->if_is_special_state_left())
		{
			// setting FEM(L)
			double b = this->length - this->langar.langar_spot;
			this->fem.left_fem = this->langar.langar_value * b * (2 * this->langar.langar_spot - b);
			this->fem.left_fem /= pow(this->length, 2);

			// setting FEM(R)
			this->fem.right_fem = -1 * this->langar.langar_value * this->langar.langar_spot * (this->langar.langar_spot - 2 * b);
			this->fem.right_fem /= pow(this->length, 2);
			
			// setting new values
			this->fem.right_fem = this->fem.right_fem - (this->fem.left_fem / 2);
			this->fem.left_fem = 0;

		}
		else if(this->if_is_special_state_right())
		{
			// setting FEM(L)
			double b = this->length - this->langar.langar_spot;
			this->fem.left_fem = this->langar.langar_value * b * (2 * this->langar.langar_spot - b);
			this->fem.left_fem /= pow(this->length, 2);

			// setting FEM(R)
			this->fem.right_fem = -1 * this->langar.langar_value * this->langar.langar_spot * (this->langar.langar_spot - 2 * b);
			this->fem.right_fem /= pow(this->length, 2);

			// setting new values
			this->fem.left_fem = this->fem.left_fem - (this->fem.right_fem / 2);
			this->fem.right_fem = 0;
		}
		else
		{
			// setting FEM(L)
			double b = this->length - this->langar.langar_spot;
			this->fem.left_fem = this->langar.langar_value * b * (2 * this->langar.langar_spot - b);
			this->fem.left_fem /= pow(this->length, 2);

			// setting FEM(R)
			this->fem.right_fem = -1 * this->langar.langar_value * this->langar.langar_spot * (this->langar.langar_spot - 2 * b);
			this->fem.right_fem /= pow(this->length, 2);
		}
		
	}
}

void Pipe::calculate_k() {
	if ("azad" == this->left_joint_ptr->get_type_name() || "azad" == this->right_joint_ptr->get_type_name())
	{
		this->k = 0;
	}
	else if (if_is_special_state_left() || if_is_special_state_right()) {
		this->k = (3 * this->strength) / this->length;
	}
	else
	{
		this->k = (4 * this->strength) / this->length;
	}

}

void Pipe::calculate_df() {
	double k_prim;

	if ("azad" == this->left_joint_ptr->get_type_name() || "azad" == this->right_joint_ptr->get_type_name())
	{
		this->df.left_df = 0;
		this->df.right_df = 0;
		return;
	}
	else if("girdar" == this->left_joint_ptr->get_type_name())
	{
		this->df.left_df = 0;
		k_prim = this->right_joint_ptr->get_right_pipe_ptr()->get_k();
		this->df.right_df = this->k / (this->k + k_prim);
		return;
	}
	else if ("girdar" == this->right_joint_ptr->get_type_name()) {
		this->df.right_df = 0;
		k_prim = this->left_joint_ptr->get_left_pipe_ptr()->get_k();
		this->df.left_df = this->k / (this->k + k_prim);
		return;
	}
	else {
		k_prim = this->right_joint_ptr->get_right_pipe_ptr()->get_k();
		this->df.right_df = this->k / (this->k + k_prim);

		k_prim = this->left_joint_ptr->get_left_pipe_ptr()->get_k();
		this->df.left_df = this->k / (this->k + k_prim);
	}
	

}

void Pipe::calculate_co() {
	if ("azad" == this->left_joint_ptr->get_type_name() || "azad" == this->right_joint_ptr->get_type_name())
	{
		this->co.left = 0;
		this->co.right = 0;
		return;
	}
	else if("girdar" == this->left_joint_ptr->get_type_name())
	{
		this->co.left = 0;
		this->co.right = 0.5;
		return;
	}
	else if ("girdar" == this->right_joint_ptr->get_type_name()) {
		this->co.right = 0.5;
		this->co.left = 0;
		return;
	}
	else if (this->if_is_special_state_left()) {
		this->co.left = 0.5;
		this->co.right = 0;
		return;
	}
	else if (this->if_is_special_state_right()) {
		this->co.right = 0.5;
		this->co.left = 0;
		return;
	}

	this->co.left = 0.5;
	this->co.right = 0.5;
}

bool Pipe::if_is_special_state_left() {
	if ((nullptr == this->left_joint_ptr->get_left_joint_ptr() && "mafsali" == this->left_joint_ptr->get_type_name()) ||
		("azad" == this->left_joint_ptr->get_left_joint_ptr()->get_type_name() && "mafsali" == this->left_joint_ptr->get_type_name())
		) 
	{
		return true;
	}
	else
		return false;
}

bool Pipe::if_is_special_state_right() {
	if ((nullptr == this->right_joint_ptr->get_right_joint_ptr() && "mafsali" == this->right_joint_ptr->get_type_name()) ||
		("azad" == this->right_joint_ptr->get_right_joint_ptr()->get_type_name() && "mafsali" == this->right_joint_ptr->get_type_name())
		)
	{
		return true;
	}
	else
		return false;
}

// getting user from input
void Pipe::get_input_from_user() {

}