//#pragma once -> c++에 가깝다고 합니다.
#ifndef _TEST_H_
#define _TEST_H_
int add(int a, int b) {
	return a + b;
}
#endif

//ifndef, endif는 짝으로 사용하는 거고,
//안의 내용에 해당하는 헤더가 이미 c파일에 들어있다면
// 헤더를 새롭게 추가하지 않고, 아니면 추가하는 것.

