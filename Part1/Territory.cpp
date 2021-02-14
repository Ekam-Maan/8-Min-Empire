#include<iostream>
#include<string>
#include"Territory.h"

Territory::Territory():name("not defined"), id(-1) {
}
Territory::Territory(string s, int id1) : name(s),id(id1) {}
