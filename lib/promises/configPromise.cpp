#ifndef CONFIGSITEF_H
#define CONFIGSITEF_H

    #include "promise.cpp"
    #include "../sitef.hpp"

    class ConfigPromise : public Promise<int>
    {
    public:
        static Value Create(const CallbackInfo &info)  {
            if (info.Length() < 5)
            return Reject(info.Env(), "MissingArgument");
            else if (!info[0].IsString() || !info[1].IsString() || !info[2].IsString() || !info[3].IsString() || !info[4].IsString())
            return Reject(info.Env(), "InvalidArgument");

            string ip = info[0].As<Napi::String>().Utf8Value();
            string loja = info[1].As<Napi::String>().Utf8Value();
            string terminal = info[2].As<Napi::String>().Utf8Value();
            string reservado = info[3].As<Napi::String>().Utf8Value();
            string parametrosAdicionais = info[4].As<Napi::String>().Utf8Value();
            ConfigPromise *worker = new ConfigPromise(info.Env(), ip, loja, terminal, reservado, parametrosAdicionais);
            worker->Queue();
            return worker->deferred.Promise();
        }

    protected:
        void Execute() override  {
            result = configSiTef(ip.c_str(), loja.c_str(), terminal.c_str(), reservado.c_str(), parametrosAdicionais.c_str());
        }

        virtual void OnOK() override  {
            deferred.Resolve(Number::New(Env(), result));
        }

    private:
        ConfigPromise(napi_env env, 
                        string &p_ip, 
                        string &p_loja, 
                        string &p_terminal, 
                        string &p_reservado, 
                        string &p_parametrosAdicionais) : Promise(env),
                                                        ip(p_ip),
                                                        loja(p_loja),
                                                        terminal(p_terminal),
                                                        reservado(p_reservado),
                                                        parametrosAdicionais(p_parametrosAdicionais) {}

        string ip;
        string loja;
        string terminal;
        string reservado;
        string parametrosAdicionais;
    };

#endif
