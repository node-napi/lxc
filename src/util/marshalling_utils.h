#ifndef MARSHALLING_UTILS_H
#define MARSHALLING_UTILS_H

#include <napi.h>
#include <lxc/lxccontainer.h>

lxc_attach_options_t get_attach_options(Napi::Object opts) {
    lxc_attach_options_t options = LXC_ATTACH_OPTIONS_DEFAULT;

    if (opts.Has("attachFlags") && opts.Get("attachFlags").IsNumber()) {
        options.attach_flags = opts.Get("attachFlags").As<Napi::Number>().Int32Value();
    }

    if (opts.Has("namespaces") && opts.Get("namespaces").IsNumber()) {
        options.namespaces = opts.Get("namespaces").As<Napi::Number>().Int32Value();
    }

    if (opts.Has("personality") && opts.Get("personality").IsNumber()) {
        options.personality = opts.Get("personality").As<Napi::Number>().Int64Value();
    }

    if (opts.Has("initialCwd") && opts.Get("initialCwd").IsString()) {
        std::string initial_cwd = opts.Get("initialCwd").As<Napi::String>();
        options.initial_cwd = strdup(initial_cwd.c_str());
    }

    if (opts.Has("uid") && opts.Get("uid").IsNumber()) {
        options.uid = opts.Get("uid").As<Napi::Number>().Int32Value();
    }

    if (opts.Has("gid") && opts.Get("gid").IsNumber()) {
        options.gid = opts.Get("gid").As<Napi::Number>().Int32Value();
    }

    if (opts.Has("envPolicy") && opts.Get("envPolicy").IsNumber()) {
        options.env_policy = static_cast<lxc_attach_env_policy_t>(opts.Get("envPolicy").As<Napi::Number>().Int32Value());
    }

    if (opts.Has("extraEnvVars") && opts.Get("extraEnvVars").IsArray()) {
        Napi::Array env_vars_array = opts.Get("extraEnvVars").As<Napi::Array>();
        options.extra_env_vars = new char*[env_vars_array.Length() + 1];
        for (uint32_t i = 0; i < env_vars_array.Length(); ++i) {
            std::string env_var = env_vars_array.Get(i).As<Napi::String>();
            options.extra_env_vars[i] = strdup(env_var.c_str());
        }
        options.extra_env_vars[env_vars_array.Length()] = nullptr;
    }

    if (opts.Has("extraKeepEnv") && opts.Get("extraKeepEnv").IsArray()) {
        Napi::Array keep_env_array = opts.Get("extraKeepEnv").As<Napi::Array>();
        options.extra_keep_env = new char*[keep_env_array.Length() + 1];
        for (uint32_t i = 0; i < keep_env_array.Length(); ++i) {
            std::string keep_env = keep_env_array.Get(i).As<Napi::String>();
            options.extra_keep_env[i] = strdup(keep_env.c_str());
        }
        options.extra_keep_env[keep_env_array.Length()] = nullptr;
    }

    if (opts.Has("stdinFd") && opts.Get("stdinFd").IsNumber()) {
        options.stdin_fd = opts.Get("stdinFd").As<Napi::Number>().Int32Value();
    }

    if (opts.Has("stdoutFd") && opts.Get("stdoutFd").IsNumber()) {
        options.stdout_fd = opts.Get("stdoutFd").As<Napi::Number>().Int32Value();
    }

    if (opts.Has("stderrFd") && opts.Get("stderrFd").IsNumber()) {
        options.stderr_fd = opts.Get("stderrFd").As<Napi::Number>().Int32Value();
    }

    if (opts.Has("logFd") && opts.Get("logFd").IsNumber()) {
        options.log_fd = opts.Get("logFd").As<Napi::Number>().Int32Value();
    }

    if (opts.Has("lsmLabel") && opts.Get("lsmLabel").IsString()) {
        std::string lsm_label = opts.Get("lsmLabel").As<Napi::String>();
        options.lsm_label = strdup(lsm_label.c_str());
    }

    if (opts.Has("groups") && opts.Get("groups").IsArray()) {
        Napi::Array groups_array = opts.Get("groups").As<Napi::Array>();
        options.groups.size = groups_array.Length();
        options.groups.list = new gid_t[groups_array.Length()];
        for (uint32_t i = 0; i < groups_array.Length(); ++i) {
            options.groups.list[i] = groups_array.Get(i).As<Napi::Number>().Int32Value();
        }
    }

    return options;
}
#endif // MARSHALLING_UTILS_H