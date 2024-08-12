#ifndef GET_INTERFACES_H
#define GET_INTERFACES_H

#include <napi.h>
#include <lxc/lxccontainer.h>
#include <string>

class GetInterfacesWorker : public Napi::AsyncWorker {
public:
    GetInterfacesWorker(Napi::Env& env, struct lxc_container* c)
        : Napi::AsyncWorker(env), deferred(Napi::Promise::Deferred::New(env)), c(c), interfaces(nullptr) {}

    void Execute() override {
        interfaces = c->get_interfaces(c);
        if (interfaces == nullptr) {
            SetError("Failed to get network interfaces");
        }
    }

    void OnOK() override {
        Napi::Env env = Env();
        Napi::Array result = Napi::Array::New(env);
        for (size_t i = 0; interfaces[i] != nullptr; ++i) {
            result.Set(i, Napi::String::New(env, interfaces[i]));
        }
        deferred.Resolve(result);
        free(interfaces);
    }

    void OnError(const Napi::Error& e) override {
        deferred.Reject(e.Value());
    }

    Napi::Promise GetPromise() {
        return deferred.Promise();
    }

private:
    Napi::Promise::Deferred deferred;
    struct lxc_container* c;
    char** interfaces;
};
#endif