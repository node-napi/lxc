#include <napi.h>
#include <lxc/lxccontainer.h>
#include <string>

class StartContainerWorker : public Napi::AsyncWorker {
public:
    StartContainerWorker(Napi::Env& env, struct lxc_container* c)
        : Napi::AsyncWorker(env), deferred(Napi::Promise::Deferred::New(env)), c(c) {}

    void Execute() override {
        if (!this->c->start(this->c, 0, NULL)) {
		   SetError("Failed to start the container");
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
};