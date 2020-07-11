/*
*
* Kalman Filter - Two States (Roll and Pitch)
*
* Implements a continuous-discrete Kalman filter for estimation of roll and pitch angles.
* Sensors: gyro (p, q, r), accelerometer (ax, ay, az), pitot tube and differential pressure sensor (Va)
* 
* Written by: Philip M. Salmony @ philsal.co.uk
* Last changed: 04 Jul 2020
*
*/

#ifndef KALMAN_ROLL_PITCH_H
#define KALMAN_ROLL_PITCH_H

#include <math.h>

typedef struct {
	float phi;
	float theta;
	float P[4];
	float Q[2];
	float R[3];
} KalmanRollPitch;

void KalmanRollPitch_Init(KalmanRollPitch *kal, float Pinit, float *Q, float *R) {
	kal->phi   = 0.0f;
	kal->theta = 0.0f;
	kal->P[0] = Pinit; kal->P[1] = 0.0f;
	kal->P[2] = 0.0f;  kal->P[3] = Pinit;
	kal->Q[0] = Q[0];  kal->Q[1] = Q[1];
	kal->R[0] = R[0];  kal->R[1] = R[1]; kal->R[2] = R[2];
}

void KalmanRollPitch_Update(KalmanRollPitch *kal, float *gyr, float *acc, float Va, float T) {	
	/* Extract measurements */
	float p = gyr[0];
	float q = gyr[1];
	float r = gyr[2];
	
	float ax = acc[0];
	float ay = acc[1];
	float az = acc[2];

	/*
	*  PREDICT
	*/
	
	/* Compute common trig terms */
	float sp = sinf(kal->phi);   float cp = cosf(kal->phi);
	float tt = tanf(kal->theta);
	
	/* x+ = x- + T * f(x,u) */
	kal->phi   = kal->phi   + T * (p + tt * (q * sp + r * cp));
	kal->theta = kal->theta + T * (    q * cp      - r * sp);
	
	/* Recompute common trig terms using new state estimates */
	      sp = sinf(kal->phi); 		   cp = cosf(kal->phi);
	float st = sinf(kal->theta); float ct = cosf(kal->theta); tt = st / ct;
	
	/* Jacobian of f(x,u) */
	float A[4] = { tt * (q * cp - r * sp), (r * cp + q * sp) * (tt * tt + 1.0f), 
				 -(r * cp + q * sp),        0.0f};
				 
	/* Update covariance matrix P+ = P- + T * (A*P- + P-*A' + Q) */
	float Ptmp[4] = { T*(kal->Q[0]      + 2.0f*A[0]*kal->P[0] + A[1]*kal->P[1] + A[1]*kal->P[2]), T*(A[0]*kal->P[1] + A[2]*kal->P[0] + A[1]*kal->P[3] + A[3]*kal->P[1]),
					  T*(A[0]*kal->P[2] + A[2]*kal->P[0]   + A[1]*kal->P[3] + A[3]*kal->P[2]),    T*(kal->Q[1]      + A[2]*kal->P[1] + A[2]*kal->P[2] + 2.0f*A[3]*kal->P[3]) };
	
	kal->P[0] = kal->P[0] + Ptmp[0]; kal->P[1] = kal->P[1] + Ptmp[1];
	kal->P[2] = kal->P[2] + Ptmp[2]; kal->P[3] = kal->P[3] + Ptmp[3];
	
	/*
	*  UPDATE
	*/
	
	const float g = 9.81f;
	
	/* Output function h(x,u) */
	float h[3] = { q * Va * st               + g * st, 
				   r * Va * ct - p * Va * st - g * ct * sp,
				  -q * Va * ct               - g * ct * cp };
				  
	/* Jacobian of h(x,u) */
	float C[6] = { 0.0f,         q * Va * ct + g * ct,
				  -g * cp * ct, -r * Va * st - p * Va * ct + g * sp * st,
				   g * sp * ct, (q * Va + g * cp) * st };
	
	/* Kalman gain K = P * C' / (C * P * C' + R) */
	float G[9] = { kal->P[3]*C[1]*C[1] + kal->R[0],        C[1]*C[2]*kal->P[2] + C[1]*C[3]*kal->P[3],                                                   C[1]*C[4]*kal->P[2] + C[1]*C[5]*kal->P[3],
				   C[1]*(C[2]*kal->P[1] + C[3]*kal->P[3]), kal->R[1] + C[2]*(C[2]*kal->P[0] + C[3]*kal->P[2]) + C[3]*(C[2]*kal->P[1] + C[3]*kal->P[3]), C[4]*(C[2]*kal->P[0] + C[3]*kal->P[2]) + C[5]*(C[2]*kal->P[1] + C[3]*kal->P[3]),
	               C[1]*(C[4]*kal->P[1] + C[5]*kal->P[3]), C[2]*(C[4]*kal->P[0] + C[5]*kal->P[2]) + C[3]*(C[4]*kal->P[1] + C[5]*kal->P[3]),             kal->R[2] + C[4]*(C[4]*kal->P[0] + C[5]*kal->P[2]) + C[5]*(C[4]*kal->P[1] + C[5]*kal->P[3]) };
	
	float Gdetinv = 1.0f / (G[0]*G[4]*G[8] - G[0]*G[5]*G[7] - G[1]*G[3]*G[8] + G[1]*G[5]*G[6] + G[2]*G[3]*G[7] - G[2]*G[4]*G[6]);
	
	float Ginv[9] = { Gdetinv * (G[4]*G[8] - G[5]*G[7]), -Gdetinv * (G[1]*G[8] - G[2]*G[7]),  Gdetinv * (G[1]*G[5] - G[2]*G[4]), 
				     -Gdetinv * (G[3]*G[8] - G[5]*G[6]),  Gdetinv * (G[0]*G[8] - G[2]*G[6]), -Gdetinv * (G[0]*G[5] - G[2]*G[3]),
	                  Gdetinv * (G[3]*G[7] - G[4]*G[6]), -Gdetinv * (G[0]*G[7] - G[1]*G[6]),  Gdetinv * (G[0]*G[4] - G[1]*G[3]) };

	float K[6] = { Ginv[3]*(C[2]*kal->P[0] + C[3]*kal->P[1]) + Ginv[6]*(C[4]*kal->P[0] + C[5]*kal->P[1]) + C[1]*Ginv[0]*kal->P[1], Ginv[4]*(C[2]*kal->P[0] + C[3]*kal->P[1]) + Ginv[7]*(C[4]*kal->P[0] + C[5]*kal->P[1]) + C[1]*Ginv[1]*kal->P[1], Ginv[5]*(C[2]*kal->P[0] + C[3]*kal->P[1]) + Ginv[8]*(C[4]*kal->P[0] + C[5]*kal->P[1]) + C[1]*Ginv[2]*kal->P[1],
				   Ginv[3]*(C[2]*kal->P[2] + C[3]*kal->P[3]) + Ginv[6]*(C[4]*kal->P[2] + C[5]*kal->P[3]) + C[1]*Ginv[0]*kal->P[3], Ginv[4]*(C[2]*kal->P[2] + C[3]*kal->P[3]) + Ginv[7]*(C[4]*kal->P[2] + C[5]*kal->P[3]) + C[1]*Ginv[1]*kal->P[3], Ginv[5]*(C[2]*kal->P[2] + C[3]*kal->P[3]) + Ginv[8]*(C[4]*kal->P[2] + C[5]*kal->P[3]) + C[1]*Ginv[2]*kal->P[3] };

	/* Update covariance matrix P++ = (I - K * C) * P+ */
	Ptmp[0] = -kal->P[2]*(C[1]*K[0] + C[3]*K[1] + C[5]*K[2]) - kal->P[0]*(C[2]*K[1] + C[4]*K[2] - 1.0f); Ptmp[1] = -kal->P[3]*(C[1]*K[0] + C[3]*K[1] + C[5]*K[2]) - kal->P[1]*(C[2]*K[1] + C[4]*K[2] - 1.0f);
	Ptmp[2] = -kal->P[2]*(C[1]*K[3] + C[3]*K[4] + C[5]*K[5] - 1.0f) - kal->P[0]*(C[2]*K[4] + C[4]*K[5]); Ptmp[3] = -kal->P[3]*(C[1]*K[3] + C[3]*K[4] + C[5]*K[5] - 1.0f) - kal->P[1]*(C[2]*K[4] + C[4]*K[5]);
	
	kal->P[0] = kal->P[0] + Ptmp[0]; kal->P[1] = kal->P[1] + Ptmp[1];
	kal->P[2] = kal->P[2] + Ptmp[2]; kal->P[3] = kal->P[3] + Ptmp[3];
	
	/* Update state estimate x++ = x+ + K * (y - h) */
	kal->phi   = kal->phi   + K[0] * (ax - h[0]) + K[1] * (ay - h[1]) + K[2] * (az - h[2]);
	kal->theta = kal->theta + K[3] * (ax - h[0]) + K[4] * (ay - h[1]) + K[5] * (az - h[2]);  
}

#endif