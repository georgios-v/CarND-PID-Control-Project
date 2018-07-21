#include <iostream>
#include <cmath>
#include "PID.h"

/*
 * TODO: Complete the PID class.
 */

PID::PID() {
}

PID::~PID() {
}

void PID::Init(double Kp, double Ki, double Kd) {
	Kp_ = Kp;
	Ki_ = Ki;
	Kd_ = Kd;
	p_error_ = d_error_ = i_error_ = 0.0;

	dp_.resize(3);
	dp_[0] = 1.0;
	dp_[1] = 1.0;
	dp_[2] = 1.0;
}

void PID::UpdateError(double cte) {
	d_error_ = cte - p_error_;
	p_error_ = cte;
	i_error_ += cte;
}

void PID::Twiddle(double cte) {
	if ((std::fabs(p_error_) + std::fabs(i_error_) + std::fabs(d_error_)) < tol) {
		std::cout << "Twiddle converged" << std::endl;
		return;
	}

	double p[] = {Kp_, Ki_, Kd_};

	std::cout << "Twiddling (stage: " << state << ", idx: " << idx << ')' << std::endl;
	switch (state) {
		case 0:
			p[idx] += dp_[idx];
			state = 1;
			break;
		case 1:
			if (cte < best_error) {
				best_error = cte;
				dp_[idx] *= 1.1;
				state = 3;
			} else {
				p[idx] -= 2 * dp_[idx];
				state = 2;
			}
			break;
		case 2:
			if (cte < best_error) {
				best_error = cte;
				dp_[idx] *= 1.1;
			} else {
				p[idx] += dp_[idx];
				dp_[idx] *= 0.9;

			}
			state = 3;
			break;
		case 3:
			idx = (idx + 1) % 3;
			state = 0;
			break;
	}

	Kp_ = p[0];
	Ki_ = p[1];
	Kd_ = p[2];

	std::cout << "Twiddled | Kp: " << Kp_ << " | Ki: " << Ki_ << " | Kd: " << Kd_ << std::endl;
}

double PID::TotalError() {
	std::cout << "| Kp: " << Kp_ << " | Ki: " << Ki_ << " | Kd: " << Kd_ << std::endl;
	return -Kp_ * p_error_ - Ki_ * i_error_ - Kd_ * d_error_;
}

