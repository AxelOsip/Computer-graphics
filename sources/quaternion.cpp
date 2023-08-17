#include "quaternion.h"


Quaternion::Quaternion(vec4 v){
	a = 0;
	b = v.x;
	c = v.y;
	d = v.z;
}

Quaternion::Quaternion(float a, float b, float c, float d){
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
}

Quaternion::Quaternion(vec4 axis, float angle){
	// rotation quaternion 
	float t = angle/2;	// radians
	a = cos(t);
	b = sin(t) * axis.x;
	c = sin(t) * axis.y;
	d = sin(t) * axis.z;
}


Quaternion Quaternion::operator * (Quaternion q){
	//	quaternions multiplying
	// 	description:
	//	i*i = j*j = k*k = -1
	//	i*j = k;	j*k = i;	k*i = j;
	//	j*i = -k;	k*j = -i;	i*k = -j
	//
	//	q1 * q2 = (a1 + b1*i + c1*j + d1*k) * (a2 + b2*i + c2*j + d2*k) = 
	//	= (a1a2 - b1b2 - c1c2 - d1d2)   + (a1b2 + b1a2 + c1d2 - d1c2)*i +
	//	+ (a1c2 + c1a2 + d1b2 - b1d2)*j + (a1d2 + d1a2 + b1c2 - c1b2)*k

	float a_, b_, c_, d_;
	a_ = a*q.a - b*q.b - c*q.c - d*q.d;
	b_ = a*q.b + b*q.a + c*q.d - d*q.c;
	c_ = a*q.c + c*q.a + d*q.b - b*q.d;
	d_ = a*q.d + d*q.a + b*q.c - c*q.b;

	return Quaternion(a_, b_, c_, d_);
}

Quaternion Quaternion::operator ~ (){
	// complex conjugate
	return Quaternion(a, -b, -c, -d);
}


vec4 Quaternion::getVector(){
	return vec4(b, c, d, 0);
}


void Quaternion::debug(){
	cout << a << " ";
	cout << b << " ";
	cout << c << " ";
	cout << d << endl;
}