#ifndef ADMIN_LOGIN
#define ADMIN_LOGIN
#include <iostream>
#include <string>

class adminUser {
	private:
		std::string type;
	public:
		void setType(std::string t);
		std::string returnType();
}

#endif