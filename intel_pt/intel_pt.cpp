// intel_pt.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "intel_pt.h"

int main()
{
	intel::pt::cpu_capabilties cp;
	cp.dump();
    return 0;
}

