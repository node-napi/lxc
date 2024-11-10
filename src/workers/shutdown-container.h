#ifndef SHUTDOWN_CONTAINER_H
#define SHUTDOWN_CONTAINER_H

#include <napi.h>
#include <lxc/lxccontainer.h>
#include <string>

class ShutdownContainerWorker : public Napi::AsyncWorker {
public:
    ShutdownContainerWorker(Napi::Env& env, struct lxc_container* c, int shutdown_seconds)
        : Napi::AsyncWorker(env), deferred(Napi::Promise::Deferred::New(env)), c(c), shutdown_seconds(shutdown_seconds) {}

    void Execute() override {
        if (!this->c->shutdown(this->c, this->shutdown_seconds)) {
            SetError("Failed to shutdown the container");
        }
    }

    void OnOK() override {
        Napi::HandleScope scope(Env());
        deferred.Resolve(Napi::Boolean::New(Env(), true));
    }

    void OnError(const Napi::Error& e) override {
        Napi::HandleScope scope(Env());
        deferred.Reject(e.Value());
    }

    Napi::Promise GetPromise() {
        return deferred.Promise();
    }

private:
    Napi::Promise::Deferred deferred;
    struct lxc_container* c;
    int shutdown_seconds;
};
#endif