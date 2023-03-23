#ifndef FINALLYSITEF_H
#define FINALLYSITEF_H

#include "promise.cpp"
#include "../sitef.hpp"

class FinallyPromise : public Promise<bool>{
    public:
        static Value Create(const CallbackInfo &info){
            if (info.Length() < 5)
                return Reject(info.Env(), "MissingArgument");
            else if (!info[0].IsNumber() || !info[1].IsString() || !info[2].IsString() || !info[3].IsString() || !info[4].IsString())
                return Reject(info.Env(), "InvalidArgument");

            int confirma = info[0].As<Number>().Int32Value();
            string cupomFiscal = info[1].As<String>().Utf8Value();
            string dataFiscal = info[2].As<String>().Utf8Value();
            string horaFiscal = info[3].As<String>().Utf8Value();
            string paramAdicionais = info[4].As<String>().Utf8Value();

            FinallyPromise *worker = new FinallyPromise(info.Env(), confirma, cupomFiscal, dataFiscal, horaFiscal, paramAdicionais);
            worker->Queue();
            return worker->deferred.Promise();
    }

    protected:
        void Execute() override  {
            finallySiTef(confirma, cupomFiscal.c_str(), dataFiscal.c_str(), horaFiscal.c_str(), paramAdicionais.c_str());
            result = true;
        }

        virtual void OnOK() override  {
            deferred.Resolve(Boolean::New(Env(), result));
        }

    private:
        FinallyPromise(napi_env env,
                            int &p_confirma,
                            string &p_cupomFiscal,
                            string &p_dataFiscal,
                            string &p_horaFiscal,
                            string &p_paramAdicionais) : Promise(env),
                                                        confirma(p_confirma),
                                                        cupomFiscal(p_cupomFiscal),
                                                        dataFiscal(p_dataFiscal),
                                                        horaFiscal(p_horaFiscal),
                                                        paramAdicionais(p_paramAdicionais) {}

        int confirma;
        string cupomFiscal;
        string dataFiscal;
        string horaFiscal;
        string paramAdicionais;
};

#endif