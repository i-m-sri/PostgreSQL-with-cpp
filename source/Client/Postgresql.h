#pragma once
#pragma warning(disable:4996)
#include<pqxx/pqxx>
#include<iostream>
#include"VariadicTable.h"
#include"text_color.h"
#include<thread>
#include<winsock.h>
#include<tuple>
#include<stdio.h>

using namespace pqxx;

std::string get_value(std::string);
void execute(std::string, int);
void check_inbox(std::string,int);


