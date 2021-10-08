#include "interface.hpp"

using namespace std;

void Implementation::addUser(string firstName, string lastName, string emailAddress, string biography)
{
    users.add(firstName, lastName, emailAddress, biography);
}

void Implementation::addCompany(string name, string address, string description)
{
    companies.add(name, address, description);
}

void Implementation::addExperience(string userId, string companyId, string title, string startAt , string endsAt)
{
    if(!users.exists(userId) || !companies.exists(companyId))
        return;
    Job job(title, userId, startAt, endsAt);
    companies.find(companyId).add_job(job);
    Experience experience(title, companyId, startAt, endsAt);
    users.find(userId).add_experience(experience);
}   

void Implementation::addJobRequest(string companyName, string title, map<string, float> conditions)
{
    companies.find(companyName).add_job_request(title, conditions);
}

void Implementation::assignSkill(string userId, string skillName)
{
    Skill skill(skillName);
    users.find(userId).add_skill(skill);
}

void Implementation::endorseSkill(string endorserUserId, string skilledUserId, string skillName)
{
    if(users.exists(endorserUserId))
        if(!users.find(skilledUserId).find_skill(skillName).is_endorsed_by(endorserUserId))
        {
            users.find(skilledUserId).find_skill(skillName).add_endorser(endorserUserId);
            users.find(skilledUserId).find_skill(skillName).update_rate();
        }
}

void Implementation::follow(string followerId, string followingId)
{
    if(!users.exists(followerId) || !users.exists(followingId))
        return;
    if(!users.find(followerId).follows(followingId))
        users.find(followerId).add_following(followingId);
    if(!users.find(followingId).follows(followerId))
        users.find(followingId).add_following(followerId);
}

void Implementation::applyForJob(string userId, string companyId, string jobTitle)
{
    if(users.exists(userId))
        companies.find(companyId).find_job_request(jobTitle).add_requester(userId);
}
void Implementation::hireBestApplicant(string companyId, string jobTitle, string startsAt)
{
    companies.find(companyId).find_job_request(jobTitle).hire_best(users, startsAt);
    Experience experience(jobTitle, companyId, startsAt, NOW);
    string jobholder = companies.find(companyId).find_job_request(jobTitle).get_jobholder();
    users.find(jobholder).add_experience(experience);
}
void Implementation::printUserProfile(string userId)
{
    users.find(userId).sort();
    users.find(userId).print_profile();
}
void Implementation::printCompanyProfile(string companyName)
{
    companies.find(companyName).sort();
    companies.find(companyName).print_profile(users);
}
void Implementation::printSuggestedJobs(string userId)
{
    users.find(userId).print_suggested_jobs(companies);
}
void Implementation::printSuggestedUsers(string companyName, string jobTitle)
{
    Job job = companies.find(companyName).find_job_request(jobTitle);
    job.print_suggested_users(users);
}
void Implementation::printNetwork(string userId, int level)
{
    users.print_network(userId, level);
}