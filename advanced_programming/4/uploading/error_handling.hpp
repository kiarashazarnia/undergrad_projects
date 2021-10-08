#ifndef __ERR_H__
#define __ERR_H__

class not_found {};
class user_not_found : not_found {};
class company_not_found : not_found {};
class experience_not_found : not_found {};
class job_not_found : not_found {};
class skill_not_found : not_found {};   
class duplication {};
class bad_date {};

#endif