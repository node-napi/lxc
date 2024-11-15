#ifndef CREATE_FROME_TEMPLATE_H
#define CREATE_FROME_TEMPLATE_H

#include <napi.h>
#include <lxc/lxccontainer.h>
#include <sstream>

class CreateFromTemplateWorker : public Napi::AsyncWorker {
public:
    CreateFromTemplateWorker(Napi::Env& env, struct lxc_container* c, std::string distro, std::string release, std::string arch)
        : Napi::AsyncWorker(env), deferred(Napi::Promise::Deferred::New(env)), c(c), distro(distro), release(release), arch(arch) {}

    void Execute() override {
        if (!c->createl(c, "download", NULL, NULL, LXC_CREATE_QUIET,
                       "-d", distro.c_str(), "-r", release.c_str(), "-a", arch.c_str(), NULL)) {
            std::ostringstream oss;
            oss << "Failed to create container rootfs" << " (Error " << c->error_num << ": " << c->error_string << ")";
            SetError(oss.str());
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
    std::string distro;
    std::string release;
    std::string arch;
};
#endif