#include <napi.h>
#include <lxc/lxccontainer.h>
#include <string>
#include <vector>

class GetIPsWorker : public Napi::AsyncWorker
{
public:
    GetIPsWorker(Napi::Env& env, lxc_container *c, const std::string &interface, const std::string &family, int scope)
        : Napi::AsyncWorker(env), deferred(Napi::Promise::Deferred::New(env)), c(c), interface(interface), family(family), scope(scope) {}

    void Execute() override
    {
        char **ips = c->get_ips(c, interface.c_str(), family.c_str(), scope);
        if (ips)
        {
            for (int i = 0; ips[i] != NULL; i++)
            {
                ipList.push_back(std::string(ips[i]));
            }
            if (ips)
                free(ips);
        }
    }

    void OnOK() override
    {
        Napi::HandleScope scope(Env());
        Napi::Array result = Napi::Array::New(Env(), ipList.size());
        for (size_t i = 0; i < ipList.size(); i++)
        {
            result[i] = Napi::String::New(Env(), ipList[i]);
        }
        deferred.Resolve(result);
    }

    Napi::Promise GetPromise()
    {
        return deferred.Promise();
    }

private:
    Napi::Promise::Deferred deferred;
    struct lxc_container *c;
    std::string interface;
    std::string family;
    int scope;
    std::vector<std::string> ipList;
};