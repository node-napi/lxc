#include <napi.h>
#include <lxc/lxccontainer.h>
#include <string>

class StopContainerWorker : public Napi::AsyncWorker {
public:
    StopContainerWorker(Napi::Env& env, struct lxc_container* c, int shutdown_seconds)
        : Napi::AsyncWorker(env), deferred(Napi::Promise::Deferred::New(env)), c(c), shutdown_seconds(shutdown_seconds) {}

    void Execute() override {
        if (!this->c->shutdown(this->c, this->shutdown_seconds)) {
            if (!this->c->stop(this->c)) {
                SetError("Failed to stop the container");
            }
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