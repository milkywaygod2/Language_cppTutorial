#pragma once


static int g_iStatic = 0; //헤더는 그냥 복붙이랑 같은 의미 == static은 같은 헤더출신이더라도 각 지역에서만 사용됨
extern int g_iExtern; //모든 파일에서 사용할 수 있는 외부변수, 헤더에서는 선언만해야함, 값을 주면 중복 선언오류, 
