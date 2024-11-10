#ifndef WAIT_H
#define WAIT_H

#include <napi.h>
#include <lxc/lxccontainer.h>
#include <string>

class WaitWorker : public Napi::AsyncWorker {
public:
    WaitWorker(Napi::Env& env, struct lxc_container* c, std::string state, int timeout_seconds)
        : Napi::AsyncWorker(env), deferred(Napi::Promise::Deferred::New(env)), c(c), state(state), timeout_seconds(timeout_seconds) {}

    void Execute() override {
        if (!c->wait(c, state.c_str(), timeout_seconds)) {
            SetError("Failed to wait for container state");
        }
    }

    void OnOK() override {
        deferred.Resolve(Env().Undefined());
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
    std::string state;
    int timeout_seconds;
};
#endif