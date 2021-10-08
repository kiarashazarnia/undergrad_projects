#include "interface.hpp"

using namespace std;

Interface::Interface()
{    
}

void Interface::addUser(string firstName, string lastName, string emailAddress, string biography)
{
    implement.addUser(firstName, lastName, emailAddress, biography);
}

void Interface::addCompany(string name, string address, string description)
{
    implement.addCompany(name, address, description);
}

void Interface::addExperience(string userId, string companyId, string title, string startAt , string endsAt)
{
    implement.addExperience(userId, companyId, title, startAt , endsAt);
}   

void Interface::addJobRequest(string companyName, string title, map<string, float> conditions)
{
    implement.addJobRequest(companyName, title, conditions);
}
void Interface::assignSkill(string userId, string skillName)
{
    implement.assignSkill(userId, skillName);
}
void Interface::endorseSkill(string endorserUserId, string skilledUserId, string skillName)
{
    implement.endorseSkill(endorserUserId, skilledUserId, skillName);
}
void Interface::follow(string followerId, string followingId)
{
    implement.follow(followerId, followingId);
}
void Interface::applyForJob(string userId, string companyId, string jobTitle)
{
    implement.applyForJob(userId, companyId, jobTitle);
}
void Interface::hireBestApplicant(string companyId, string jobTitle, string startsAt)
{
    implement.hireBestApplicant(companyId, jobTitle, startsAt);
}
void Interface::printUserProfile(string userId)
{
    implement.printUserProfile(userId);    
}
void Interface::printCompanyProfile(string companyName)
{
    implement.printCompanyProfile(companyName);
}
void Interface::printSuggestedJobs(string userId)
{
    implement.printSuggestedJobs(userId);
}
void Interface::printSuggestedUsers(string companyName, string jobTitle)
{
    implement.printSuggestedUsers(companyName, jobTitle);
}
void Interface::printNetwork(string userId, int level)
{
    implement.printNetwork(userId, level);
}
