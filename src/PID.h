#ifndef PID_H
#define PID_H

#include <limits>
#include <vector>

class PID {
public:

	/*
	 * Constructor
	 */
	PID();

	/*
	 * Destructor.
	 */
	virtual ~PID();

	/*
	 * Initialize PID.
	 */
	void Init(double Kp, double Ki, double Kd);

	/*
	 * Update the PID error variables given cross track error.
	 */
	void UpdateError(double cte);

	/*
	 * Calculate the total PID error.
	 */
	double TotalError();

	/*
	 * Twiddle
	 */
	void Twiddle(double cte);

private:
	/*
	 * Coefficients
	 */
	double Kp_;
	double Ki_;
	double Kd_;

	/*
	 * Errors
	 */
	double p_error_;
	double i_error_;
	double d_error_;

	/*
	 * Twiddling
	 */
	std::vector<double> dp_;

	const double tol = 0.00001;
	double best_error = std::numeric_limits<double>::max();
	int idx = 0;
	int state = 0;

};

#endif /* PID_H */
