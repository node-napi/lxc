#include <napi.h>
#include <lxc/lxccontainer.h>
#include <string>
#include "workers/create-from-template.h"
#include "workers/stop-container.h"
#include "workers/start-container.h"
#include "workers/destroy-container.h"


class LxcContainer : public Napi::ObjectWrap<LxcContainer> {
public:
	static Napi::Object Init(Napi::Env env, Napi::Object exports);
	LxcContainer(const Napi::CallbackInfo& info);
	~LxcContainer();

private:
	static Napi::FunctionReference constructor;
	struct lxc_container *c;
	std::string config;
	std::string lxc_path;

	Napi::Value CreateFromTemplate(const Napi::CallbackInfo& info);
	Napi::Value Start(const Napi::CallbackInfo& info);
	Napi::Value Stop(const Napi::CallbackInfo& info);
	Napi::Value Destroy(const Napi::CallbackInfo& info);
	Napi::Value GetState(const Napi::CallbackInfo& info);
	Napi::Value GetPid(const Napi::CallbackInfo& info);
};

Napi::FunctionReference LxcContainer::constructor;

Napi::Object LxcContainer::Init(Napi::Env env, Napi::Object exports) {
	Napi::Function func = DefineClass(env, "LxcContainer", {
		InstanceMethod("createFromTemplate", &LxcContainer::CreateFromTemplate),
		InstanceMethod("start", &LxcContainer::Start),
		InstanceMethod("stop", &LxcContainer::Stop),
		InstanceMethod("destroy", &LxcContainer::Destroy),
		InstanceMethod("getState", &LxcContainer::GetState),
		InstanceMethod("getPid", &LxcContainer::GetPid),
	});

	constructor = Napi::Persistent(func);
	constructor.SuppressDestruct();

	exports.Set("LxcContainer", func);
	return exports;
}

LxcContainer::LxcContainer(const Napi::CallbackInfo& info) : Napi::ObjectWrap<LxcContainer>(info) {
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);

	if (!info[0].IsObject()) {
        Napi::TypeError::New(env, "Expected an object as the first argument").ThrowAsJavaScriptException();
        return;
    }

	Napi::Object params = info[0].As<Napi::Object>();

    std::string name = params.Get("name").As<Napi::String>().Utf8Value();
    this->lxc_path = params.Has("lxcPath") ? params.Get("lxcPath").As<Napi::String>().Utf8Value() : "";
    this->config = params.Has("config") ? params.Get("config").As<Napi::String>().Utf8Value() : "";

	this->c = lxc_container_new(name.c_str(), NULL);
	
	if (!this->c) {
		Napi::TypeError::New(env, "Failed to setup lxc_container struct").ThrowAsJavaScriptException();
	}
	if (!this->lxc_path.empty()) {
		if (!this->c->set_config_path(this->c, this->lxc_path.c_str())) {
			Napi::TypeError::New(env, "Failed to set lxc path").ThrowAsJavaScriptException();
            lxc_container_put(this->c);
            this->c = nullptr;
		}
	}
	if (!config.empty()) {
        if (!this->c->save_config(this->c, this->config.c_str())) {
            Napi::TypeError::New(env, "Failed to load LXC container config").ThrowAsJavaScriptException();
            lxc_container_put(this->c);
            this->c = nullptr;
        }
    }
}

LxcContainer::~LxcContainer() {
	if (this->c) {
		lxc_container_put(this->c);
	}
}

Napi::Value LxcContainer::CreateFromTemplate(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (!info[0].IsObject()) {
        Napi::TypeError::New(env, "Expected an object as the first argument").ThrowAsJavaScriptException();
    }

    Napi::Object params = info[0].As<Napi::Object>();


    std::string distro = params.Get("distro").As<Napi::String>().Utf8Value();
    std::string release = params.Get("release").As<Napi::String>().Utf8Value();
    std::string arch = params.Get("arch").As<Napi::String>().Utf8Value();

    CreateFromTemplateWorker* worker = new CreateFromTemplateWorker(env, this->c, distro, release, arch);
    worker->Queue();
    return worker->GetPromise();
}

Napi::Value LxcContainer::Start(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	StartContainerWorker* worker = new StartContainerWorker(env, this->c);
    worker->Queue();
    return worker->GetPromise();
}

Napi::Value LxcContainer::Stop(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
    int seconds = info[0].As<Napi::Number>().Uint32Value();
    StopContainerWorker* worker = new StopContainerWorker(env, this->c, seconds);
    worker->Queue();
    return worker->GetPromise();
}

Napi::Value LxcContainer::Destroy(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
    DestroyContainerWorker* worker = new DestroyContainerWorker(env, this->c);
    worker->Queue();
    return worker->GetPromise();
}

Napi::Value LxcContainer::GetState(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);

	const char* state = this->c->state(this->c);
	return Napi::String::New(env, state);
}

Napi::Value LxcContainer::GetPid(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);

	int pid = this->c->init_pid(this->c);
	return Napi::Number::New(env, pid);
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
	return LxcContainer::Init(env, exports);
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll)

