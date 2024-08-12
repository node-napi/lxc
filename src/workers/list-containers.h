#include <napi.h>
#include <lxc/lxccontainer.h>
#include <vector>
#include <string>

class ListContainersWorker : public Napi::AsyncWorker {
public:
    ListContainersWorker(Napi::Env& env, std::string lxc_path)
        : Napi::AsyncWorker(env), deferred(Napi::Promise::Deferred::New(env)), lxc_path(lxc_path) {}

    void Execute() override {
       char **names = nullptr;
        struct lxc_container **containers = nullptr;
        int num_containers = list_defined_containers(lxc_path.c_str(), &names, &containers);

        if (num_containers < 0) {
            SetError("Failed to list containers");
            return;
        }

        for (int i = 0; i < num_containers; ++i) {
            container_names.push_back(names[i]);
        }

        if (names) {
            for (int i = 0; i < num_containers; ++i) {
                free(names[i]);
            }
            free(names);
        }
        if (containers) {
            free(containers);
        }
    }

    void OnOK() override {
        Napi::Array result = Napi::Array::New(Env(), container_names.size());
        for (size_t i = 0; i < container_names.size(); ++i) {
            result[i] = Napi::String::New(Env(), container_names[i]);
        }
        deferred.Resolve(result);
    }

    void OnError(const Napi::Error& e) override {
        deferred.Reject(e.Value());
    }

    Napi::Promise GetPromise() {
        return deferred.Promise();
    }

private:
    Napi::Promise::Deferred deferred;
    std::string lxc_path;
    std::vector<std::string> container_names;
};