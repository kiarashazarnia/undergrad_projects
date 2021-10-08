#ifndef __LINKEDIN_H__
#define __LINKEDIN_H__
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <cmath>
#include <iomanip>
#include <algorithm>

#include "date.hpp"
#include "error_handling.hpp"

#define NOW "NOW"
#define PRECISION 3

using namespace std;

class Users;
class Companies;

typedef map<string, float> Condition;
void print2fractional_digit(float x);
void print_idot(int i);
class Skill{
  public:
    Skill(string name);
    string get_name();
    float get_rate();
    void set_name(string name);
    void update_rate();
    void add_endorser(string user_id);
    bool is_endorsed_by(string enorser);    

  private:
    string name;
    float rate;
    vector<string> endorsers;
};

class Experience{
  public:
    void set_title(string title);
    void set_start_at(string date);
    void set_end_at(string date);
    void set_company_name(string _company_name);
    Experience(string _title, string _company_name, string _start, string _end);
    
    string get_company_name();
    string get_title();
    string get_start_at();
    string get_end_at();

  private:
    string company_name;
    string title;
    string start_at;
    string end_at;
};

bool primary_exp(Experience pre, Experience aft);

class User{
  public:
    void print_name(); 
    void print_email(); 
    void print_bio(); 
    void print_network_size(); 
    void print_experiences(); 
    void print_skills();
    void set_first_name(string fname);
    void set_last_name(string lname);
    void set_email_address(string email);
    void set_biography(string bio);
    User(string fname, string lname, string email, string bio);
    User() {}
    void add(User user);
    void add_skill(Skill skill);
    void add_experience(Experience experience);
    void add_following(string user_email);
    Skill& find_skill(string skill_name);
    bool follows(string user_email);
    bool skilled(string skill_name);
    bool have_condition(Condition condition);
    unsigned get_full_rate(Condition condition);
    void print_profile();
    void print_suggested_jobs(Companies companies);
    void sort() {std::sort(experiences.begin(),experiences.end(), primary_exp);}    
    string get_first_name();
    string get_last_name();
    string get_email_address();
    string get_biography();
    string get_following_at(int i) {return followings.at(i);}
    unsigned how_many_skills() {return skills.size();}
    unsigned how_many_experiences() {return experiences.size();}
    unsigned how_many_followings()  {return followings.size();}
    vector<Experience>& post_exp()  {return experiences;}


  private:
    string first_name;
    string last_name;
    string email_address;
    string biography;
    vector <Skill> skills;
    vector <Experience> experiences;
    vector <string> followings;
};

class Job{
  public:
    void print_conditions();
    void set_title(string _title);
    void set_condition(map <string ,float> _condition);
    void add_condition(string _skill_name, float _rate)  {condition.insert(make_pair(_skill_name, _rate));}
    void set_jobholder(string user_email, string _start_at);
    void set_jobholder(string user_email);
    void set_hired() {hired = 1;}
    void add_requester(string user_id);
    void set_start_at(string _start_at);
    void set_end_at(string _end_at);
    void print_suggested_users(Users& users);
    Job(string _title, map<string, float> _condition);
    Job(string _title, string _jobholder, string _start_at, string end_at);

    bool is_hired() {return hired;}
    void hire_best(Users& users, string _start_at);
    string get_title();
    string get_jobholder() {return jobholder;}
    string get_start_at() {return start_at;};
    string get_end_at() {return end_at;};
    map<string, float> get_condition();
    void print_job();

  private:
    string start_at, end_at;
    string title;
    bool hired;
    string jobholder;
    map<string, float> condition;
    vector <string> requesters;
};
bool primary_job(Job pre, Job aft);
class Jobs
{
  public:
    bool exists(string _title);
    Job& find(string _title);
    void add_job(Job job);
    Job at(int i) {return jobs.at(i);}
    unsigned size() {return jobs.size();}
    vector<Job>& post_jobs() {return jobs;}
    void sort(){std::sort(jobs.begin(), jobs.end(), primary_job);}
  private:
    vector<Job> jobs;
};

class Company{
  public:
    void print_name();
    void print_address();
    void print_describtion();
    void print_jobs(Users& users);
    void print_requests();
    void print_profile(Users& users);
    void set_name(string _name);
    void set_address(string _address);
    void set_description(string _description);
    Company(string name, string address, string description);
    string get_name();
    string get_address();
    string get_description();
    Jobs get_job_requests() {return job_requests;}
    Job& find_job_request(string _title);
    void add_job_request(string _title, map<string, float> condition);
    void add_job(Job job);
    void hire_best(string _title, Users& users, string _start_at);
    unsigned job_requests_number() {return job_requests.size();}
    void sort() {job_requests.sort();}
  private:
    string name;
    string address;
    string description;
    Jobs job_requests;
};

class Users{
  public:
    void add(string firstName, string lastName, string emailAddress, string biography);
    void add(User);
    User at(int i) {return users.at(i);}
    User& find(string _email_address);
    bool exists(string _email_address);
    unsigned size() {return users.size();}
    void make_network(string userId, int level, Users& following_users);
    void print_network(string userId, int level);

  private:
    vector<User> users;
};

class Companies{
  public:
    void add(string name, string address, string description);
    Company& at(int i) {return companies.at(i);}
    Company& find(string _name);
    bool exists(string _name);
    unsigned size() {return companies.size();}

  private:
    vector<Company> companies;
};


#endif