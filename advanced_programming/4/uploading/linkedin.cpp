#include "linkedin.hpp"

string Skill::get_name()    {return name;}
float Skill::get_rate()     {return rate;}
void Skill::set_name(string _name)    {name = _name;}
Skill::Skill(string name)
{
    set_name(name);
    rate = 1;
}
void Skill::update_rate()
{
    rate = sqrt(endorsers.size() + 1);
}
void Skill::add_endorser(string _email_address)
{
    endorsers.push_back(_email_address);
}
bool Skill::is_endorsed_by(string endorser)
{
    for(int i = 0; i < endorsers.size(); i++)
        if(endorsers.at(i) == endorser)
            return 1;
    return 0;
}
Experience::Experience(string _title, string _company_name, string _start, string _end)
{
    set_title(_title);
    set_company_name(_company_name);
    set_start_at(_start);
    set_end_at(_end);    
}

void Experience::set_title(string _title)    {title = _title;}
void Experience::set_start_at(string date)     {start_at = date;}
void Experience::set_end_at(string date)       {end_at = date;}
void Experience::set_company_name(string _company_name) {company_name = _company_name;} 

string Experience::get_company_name()    {return company_name;}
string Experience::get_title()         {return title;}
string Experience::get_start_at()      {return start_at;}
string Experience::get_end_at()        {return end_at;}

void print_idot(int i)
{
    cout << "\t" << i+1 << ". ";
}
void User::print_profile()
{
    print_name();
    print_email();
    print_bio();
    print_network_size();
    print_experiences();
    print_skills();
    cout << endl;   
}
void User::print_name()
{
    cout << "Name: " << first_name << " " << last_name << endl;
}
void User::print_email()
{
    cout << "Email: " << email_address << endl;
}
void User::print_bio()
{
    cout << "Biography: " << biography << endl;
}
void User::print_network_size()
{
    cout << "Network: " << followings.size() << " connections" << endl;
}

void User::print_experiences()
{
    cout << "Experiences:" << endl;
    for(int i = 0; i < experiences.size(); i++)
    {
        print_idot(i);
        cout << experiences.at(i).get_start_at() << " - " << experiences.at(i).get_end_at() << " ";
        cout << experiences.at(i).get_title() << " at " << experiences.at(i).get_company_name() << endl;
    }
}

bool User::have_condition(Condition condition)
{
    Condition::iterator it = condition.begin();
    string _title = it -> first;
    for(; it != condition.end(); it++)
    {
        float rate = condition[_title];
        if(!skilled(_title))
            return 0;
        if(find_skill(_title).get_rate() < rate)
            return 0;
    }
    return 1;
}

void print2fractional_digit(float x)
{
    cout << std::setprecision(ceil(log10(floor(x))+PRECISION));
    cout << x;
}
void User::print_skills()
{
    cout << "Skills:" << endl;
    for(int i = 0; i < skills.size(); i++)
    {
        print_idot(i);
        cout << skills.at(i).get_name() << " - ";
        print2fractional_digit(skills.at(i).get_rate());
        cout << endl;
    }
}
User::User(string fname, string lname, string email, string bio)
{
    set_first_name(fname);
    set_last_name(lname);
    set_email_address(email);
    set_biography(bio);
}
void User::set_first_name(string _first_name)    {first_name = _first_name;}
void User::set_last_name(string _last_name)      {last_name = _last_name;}
void User::set_biography(string _biography)      {biography = _biography;}
void User::set_email_address(string _email_address) {email_address = _email_address;}

void User::add_skill(Skill skill)   {skills.push_back(skill);} //TODO: DUPLICATED FOLOWING EXIST?
void User::add_experience(Experience experience) {experiences.push_back(experience);}    //TODO: DUPLICATION
void User::add_following(string _email_address)    {followings.push_back(_email_address);}

string User::get_first_name()  {return first_name;}
string User::get_last_name()       {return last_name;}
string User::get_email_address()   {return email_address;}
string User::get_biography()       {return biography;}
unsigned User::get_full_rate(Condition condition)
{
    float full_rate = 0;
    Condition::iterator it = condition.begin();
    string title = it -> first;
    for(; it != condition.end(); it++)
    {
        full_rate += find_skill(title).get_rate();
    }
    return full_rate;
}
Skill& User::find_skill(string skill_name)
{
    for(int i = 0; i < skills.size(); i++)
        if(skills.at(i).get_name() == skill_name)
            return skills.at(i);
    throw skill_not_found();
}
bool User::skilled(string _title)
{
    try{
        find_skill(_title);
        return 1;
    }
    catch(skill_not_found error)
    {
        return 0;
    }
}
void User::print_suggested_jobs(Companies companies)
{
    cout << "Suggested jobs:" << endl;
    Jobs jobs;
    string job_title;
    unsigned job_number = 0;
    for(int comp_num = 0; comp_num < companies.size(); comp_num++)
    {
        jobs = companies.at(comp_num).get_job_requests();
        for(int j = 0; j < jobs.size(); j++)
        {
            if(jobs.at(j).is_hired())
                continue;
            job_title = jobs.at(j).get_title(); 
            if(have_condition(jobs.at(j).get_condition()))
            {
                print_idot(job_number);
                cout << jobs.at(j).get_title() << " in " << companies.at(comp_num).get_name() << " ";
                jobs.at(j).print_conditions();
                cout << endl;
                job_number++;
            }
        }
    }
}
bool User::follows(string user_email)
{
    for(int i = 0; i < followings.size(); i++)
        if(followings.at(i) == user_email)
            return 1;
    return 0;
}

Job::Job(string _title, map<string, float> _condition)
{
    set_title(_title);
    set_condition(_condition);
    hired = 0;
}
Job::Job(string _title, string _jobholder, string _start_at, string _end_at)
{
    set_title(_title);
    set_start_at(_start_at);
    set_end_at(_end_at);
    set_jobholder(_jobholder);
    set_hired();
}
void Job::print_conditions()
{
    Condition::iterator it;
    unsigned i = 0;
    for(it = condition.begin(); it != condition.end(); it++)
    {
        cout << it -> first << "(" << it -> second << ") ";
        i++;
    }
}
void Job::set_start_at(string _start_at)    {start_at = _start_at;}
void Job::set_end_at(string _end_at)        {end_at = _end_at;}
void Job::set_title(string _title)  {title = _title;}
void Job::set_condition(map <string ,float> _condition)  {condition = _condition;}
void Job::add_requester(string _email_address)  {requesters.push_back(_email_address);}    //TODO: EXIST USER?
void Job::set_jobholder(string user_email, string _start_at)
{
    start_at = _start_at;
    end_at = NOW;
    jobholder = user_email;
}
void Job::set_jobholder(string user_email)
{
    jobholder = user_email;
}

string Job::get_title()                     {return title;}
map<string, float> Job::get_condition()     {return condition;}

void Job::hire_best(Users& users, string _start_at)
{
    if(hired)
        return;
    Condition::iterator it = condition.begin();
    float max_rate = 0, user_rate = 0;
    int best_user_index = -1;
    User user;
    for(int i = 0; i < requesters.size(); i++)
    {
        user = users.find(requesters.at(i));
        if(user.have_condition(condition))
        {
            set_hired();
            user_rate = user.get_full_rate(condition);
            if(user_rate > max_rate)
            {
                max_rate = user_rate;
                best_user_index = i;
            }
        }
    }
    if(is_hired())
        set_jobholder(requesters.at(best_user_index), _start_at);
}

Job& Jobs::find(string _title)
{
    for(int i = 0; i < jobs.size(); i++)
        if(jobs.at(i).get_title() == _title)
            return jobs.at(i);
    throw job_not_found();
}
bool Jobs::exists(string _title)
{
    try{
        find(_title);
        return 1;
    }catch(job_not_found error)
    {
        return 0;
    }
}
void Jobs::add_job(Job job)
{
    jobs.push_back(job);
}
void Job::print_suggested_users(Users& users)
{
    unsigned user_num = 0;
    for(int i = 0; i < users.size(); i++)
    {
        if(users.at(i).have_condition(condition))
        {
            cout << user_num << endl;
            users.at(i).print_profile();
            user_num++;
        }
    }
}
void Company::add_job(Job job)
{
    if(!job_requests.exists(job.get_title()))
        job_requests.add_job(job);
}
void Company::print_profile(Users& users)
{
    print_name();
    print_address();
    print_describtion();
    print_jobs(users);
    print_requests();
    cout << endl;
}
void Company::print_name()
{
    cout << "Name: " << name << endl;
}
void Company::print_address()
{
    cout << "Address: " << address << endl;
}
void Company::print_describtion()
{
    cout << "Description: " << description << endl;
}
void Company::print_jobs(Users& users)
{
    cout << "Jobs:" << endl;
    User jobholder;
    unsigned jobs_num = 0;
    for(int i = 0; i < job_requests.size(); i++)
    {
        if(job_requests.at(i).is_hired())
        {
            jobholder = users.find(job_requests.at(i).get_jobholder());
            print_idot(jobs_num);
            cout << job_requests.at(i).get_start_at() << " - " << job_requests.at(i).get_end_at() << " ";
            cout << job_requests.at(i).get_title() << " by " << jobholder.get_first_name() << " "
                 << jobholder.get_last_name() << endl;
            jobs_num++;
        }
    }
}
void Company::print_requests()
{
    cout << "Requests:" << endl;
    unsigned requests = 0;
    for(int i = 0; i < job_requests.size(); i++)
    {
        if(!job_requests.at(i).is_hired())
        {
            print_idot(requests);
            cout << job_requests.at(i).get_title() << " - " << "needed skills: ";
            job_requests.at(i).print_conditions();
            cout << endl;
            requests++;
        }
    }
}

Company::Company(string _name, string _address, string _description)
{
    set_name(_name);
    set_address(_address);
    set_description(_description);    
}
void Company::set_name(string _name)                 {name = _name;}
void Company::set_address(string _address)              {address = _address;}
void Company::set_description(string _description)   {description = _description;}
Job& Company::find_job_request(string _title)
{
    return job_requests.find(_title);
}
string Company::get_name()         {return name;}
string Company::get_address()      {return address;}
string Company::get_description()  {return description;}

void Company::add_job_request(string _title, map<string, float> _condition)
{
    Job job_request(_title, _condition);
    job_requests.add_job(job_request); //TODO: DUPLICATION
}
void Company::hire_best(string _title, Users& users, string _start_at)
{
    job_requests.find(_title).hire_best(users, _start_at);
}

void Users::add(string firstName, string lastName, string emailAddress, string biography)
{
    if(exists(emailAddress))
        return;
    User new_user(firstName, lastName, emailAddress, biography);
    users.push_back(new_user);
}
void Users::add(User user)
{
    if(exists(user.get_email_address()))
        return;
    users.push_back(user);
}

User& Users::find(string _email_address)
{
    for(int i = 0; i < users.size(); i++)
        if(users.at(i).get_email_address() == _email_address)
            return users.at(i);
    throw user_not_found();
}

bool Users::exists(string _email_address)
{
    try{
        find(_email_address);
        return 1;
    }catch(user_not_found error)
    {
        return 0;
    }
}

void Users::make_network(string userId, int level, Users& following_users)
{
    if(level < 0)
        return;
    string follow_user;
    User user = find(userId);
    if(level == 0)
    {
        for(int i = 0; i < user.how_many_followings(); i++)
        {
            follow_user = user.get_following_at(i);
            if(!following_users.exists(follow_user))
                following_users.add(find(follow_user));
        }
    }
    else
    {
        for(int i = 0; i < user.how_many_followings(); i++)
        {
            follow_user = user.get_following_at(i);
            make_network(follow_user, --level, following_users);
        }        
    }
}

void Users::print_network(string userId, int level)
{
    if(!exists(userId))
        return;
    Users following_users;
    make_network(userId, level, following_users);
    for(int i = 0; i < following_users.size(); i++)
    {
        cout << i+1 << "." << endl;
        following_users.at(i).print_profile();
    }
}

void Companies::add(string name, string address, string description)
{
    if(exists(name))
        return;
    Company new_company(name, address, description);
    companies.push_back(new_company);
}

Company& Companies::find(string _name)
{
    for(int i = 0; i < companies.size(); i++)
        if(companies.at(i).get_name() == _name)
            return companies.at(i);
    throw company_not_found();
}

bool Companies::exists(string _name)
{
    try{
        find(_name);
        return 1;
    }catch(company_not_found error)
    {
        return 0;
    }
}

bool primary_job(Job pre, Job aft)
{
  if(pre.get_start_at() == aft.get_start_at())
    return earlier_date(pre.get_end_at(), aft.get_end_at());
  return earlier_date(pre.get_start_at(), aft.get_start_at());
}
bool primary_exp(Experience pre, Experience aft)
{
  if(pre.get_start_at() == aft.get_start_at())
    return earlier_date(pre.get_end_at(), aft.get_end_at());
  return earlier_date(pre.get_start_at(), aft.get_start_at());
}