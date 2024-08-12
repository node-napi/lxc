#include <napi.h>
#include <errno.h>
#include <lxc/lxccontainer.h>
#include <string>
#include <iostream>
#include <sstream>
#include "../util/error_utils.h"

class QueryConsoleWorker : public Napi::AsyncWorker {
public:
    QueryConsoleWorker(Napi::Env& env, struct lxc_container* c, uint64_t max_read)
        : Napi::AsyncWorker(env), deferred(Napi::Promise::Deferred::New(env)), c(c), max_read(max_read) {}

    void Execute() override {
        struct lxc_console_log log;
        log.read_max = &(this->max_read);
        log.read = true;

        if (this->c->console_log(this->c, &log) != 0) {
            std::ostringstream oss;
            oss << "Failed to query console " << "(Error " << c->error_num << ": " << get_error_from_num(c->error_num) << ")";
            std::string error_message = oss.str();
            SetError(error_message);
        } else {
            std::cout << "Bytes retrieved " << *log.read_max << std::endl;
            this->log_output = std::string(log.data, *log.read_max);
        }
    }

    void OnOK() override {
        deferred.Resolve(Napi::String::New(Env(), this->log_output));
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
    uint64_t max_read;
    std::string log_output;
};