#include <cstdio>
#include <vector>
#include <cassert>
//#include "function.h"
using namespace std;

class student {
	private:
		char *name;
		char *id;
	public:
		student(char *name, char *id);
		student(const student& s);
		student& operator=(const student& s);
		void show_name() {
			printf("%s\n", name);
		}

		void show_id() {
			printf("%s\n", id);
		}
		~student() {
			delete[] name;
			delete[] id;
		}
};

student::student(char *name, char *id)
{
	this->name = new char[100];
	this->id = new char[10];
	
	for(int i=0; i<100; i++){
		this->name[i] = NULL;
	}
	for(int i=0; i<10; i++){
		this->id[i] = NULL;
	}
	
	for(int i=0; ; i++){
		if(name[i]==NULL) break;
		this->name[i] = name[i];
	}
	
	for(int i=0; ; i++){
		if(id[i]==NULL) break;
		this->id[i] = id[i];
	}
} 
 
student::student(const student& s)
{
	name = new char[100];
	id = new char[10];
	
	for(int i=0; i<100; i++){
		this->name[i] = NULL;
	}
	for(int i=0; i<10; i++){
		this->id[i] = NULL;
	}
	
	for(int i=0; ; i++){
		if(s.name[i]==NULL) break;
		name[i] = s.name[i];
	}
	
	for(int i=0; ; i++){
		if(s.id[i]==NULL) break;
		id[i] = s.id[i];
	}
}

student& student::operator=(const student& s)
{
	int i;
	
	for(i=0; ; i++){
		if(name[i]==NULL && s.name[i]==NULL) break;
		name[i] = s.name[i];
	}
	
	for(i=0; ; i++){
		if(id[i]==NULL && s.id[i]==NULL) break;
		id[i] = s.id[i];
	}
	
	return *this;
}

int main() {
    vector<student> v;
    int op, op_cnt;
    char *name = new char[100];
    char *id = new char[10];

    scanf("%d", &op_cnt);
    for (int i = 0; i < op_cnt; i++) {
        scanf("%d", &op);
        if (op == 0) {
            // print all students' name
            for (student s : v) s.show_name();
        } else if (op == 1) {
            // print all students' ID
            for (student s : v) s.show_id();
        } else if (op == 2) {
            // add a new student
            scanf("%s %s", name, id);
            student s(name, id);
            v.push_back(s);
        } else if (op == 3) {
            // duplicate info of k-th student
            int k;
            scanf("%d", &k);
            student s = v[k];
            v.push_back(s);
        } else if (op == 4) {
            // delete info of k-th student
            int k;
            scanf("%d", &k);
            v.erase(v.begin() + k);
        } else {
            assert(false);
        }
    }
}
