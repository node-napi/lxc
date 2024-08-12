#ifndef ATTACH_RUN_WAIT_H
#define ATTACH_RUN_WAIT_H

#include <napi.h>
#include <lxc/lxccontainer.h>
#include <string>
#include <vector>

class AttachRunWaitWorker : public Napi::AsyncWorker {
public:
    AttachRunWaitWorker(Napi::Env& env, struct lxc_container* c, lxc_attach_options_t* options, const std::string& program, const std::vector<std::string>& argv)
        : Napi::AsyncWorker(env), deferred(Napi::Promise::Deferred::New(env)), c(c), options(options), program(program), argv(argv) {}


    void Execute() override {
        std::vector<const char*> c_argv;
        for (const auto& arg : argv) {
            c_argv.push_back(arg.c_str());
        }
        c_argv.push_back(nullptr);

        int result = c->attach_run_wait(c, options, program.c_str(), c_argv.data());
        if (result == -1) {
            SetError("Failed to run program inside container");
        } else {
            this->result = result;
        }
    }

    void OnOK() override {
        deferred.Resolve(Napi::Number::New(Env(), result));
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
    lxc_attach_options_t* options;
    std::string program;
    std::vector<std::string> argv;
    int result;
};
#endif